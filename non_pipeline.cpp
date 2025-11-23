#include <bits/stdc++.h>
using namespace std;

enum InstrType { I_NOP, I_ADD, I_SUB, I_ADDI, I_LW, I_SW, I_BEQ, I_HALT };

// human-friendly instruction representation
struct Instr {
    InstrType type;
    int rd, rs, rt;
    int imm; // immediate or branch offset
    Instr() : type(I_NOP), rd(0), rs(0), rt(0), imm(0) {}
    static Instr halt() { Instr i; i.type = I_HALT; return i; }
};

// Pipeline register structures
struct IF_ID {
    int pc;
    Instr instr;
    bool bubble;
    IF_ID() : pc(0), instr(), bubble(true) {}
};

struct ID_EX {
    int pc;
    Instr instr;
    int rs_val, rt_val;
    int rd, rs, rt, imm;
    bool bubble;
    // control/simple signals
    bool isRegWrite, isMemRead, isMemWrite, isBranch, isALUSrc, isMemToReg;
    ID_EX() : pc(0), instr(), rs_val(0), rt_val(0), rd(0), rs(0), rt(0), imm(0), bubble(true),
              isRegWrite(false), isMemRead(false), isMemWrite(false), isBranch(false),
              isALUSrc(false), isMemToReg(false) {}
};

struct EX_MEM {
    int pc;
    Instr instr;
    int alu_result;
    int rt_val; // for store
    int rd; // destination reg index
    bool bubble;
    bool isRegWrite, isMemRead, isMemWrite, isMemToReg;
    EX_MEM() : pc(0), instr(), alu_result(0), rt_val(0), rd(0), bubble(true),
               isRegWrite(false), isMemRead(false), isMemWrite(false), isMemToReg(false) {}
};

struct MEM_WB {
    int pc;
    Instr instr;
    int mem_data;
    int alu_result;
    int rd;
    bool bubble;
    bool isRegWrite, isMemToReg;
    MEM_WB() : pc(0), instr(), mem_data(0), alu_result(0), rd(0), bubble(true),
               isRegWrite(false), isMemToReg(false) {}
};

// Simple CPU state
struct CPU {
    vector<Instr> imem;
    vector<int> dmem;
    int pc;
    int regs[32];
    bool halted;

    IF_ID if_id;
    ID_EX id_ex;
    EX_MEM ex_mem;
    MEM_WB mem_wb;

    // temporary new pipeline regs used to update at clock edge
    IF_ID new_if_id;
    ID_EX new_id_ex;
    EX_MEM new_ex_mem;
    MEM_WB new_mem_wb;

    // forwarding signals (values to forward if applicable)
    int forwardA_val; bool forwardA_used;
    int forwardB_val; bool forwardB_used;

    CPU(int imem_size=256, int dmem_size=1024) {
        imem.resize(imem_size);
        dmem.assign(dmem_size, 0);
        pc = 0;
        memset(regs, 0, sizeof(regs));
        halted = false;
    }

    // utility to load a simple program (vector of Instr)
    void load_program(const vector<Instr>& prog) {
        for (size_t i=0;i<prog.size() && i<imem.size();++i) imem[i] = prog[i];
    }

    // helper to print instruction (brief)
    string instr_str(const Instr &in) {
        switch (in.type) {
            case I_ADD: return "ADD";
            case I_SUB: return "SUB";
            case I_ADDI: return "ADDI";
            case I_LW: return "LW";
            case I_SW: return "SW";
            case I_BEQ: return "BEQ";
            case I_NOP: return "NOP";
            case I_HALT: return "HALT";
            default: return "UNK";
        }
    }

    // IF stage: fetch instruction (no stall handling here, handled in control)
    void IF_stage(bool stall) {
        if (halted) {
            new_if_id.bubble = true;
            return;
        }

        if (stall) {
            // hold IF/ID (i.e., insert bubble in IF_ID by not updating it)
            // We'll set new_if_id to current if_id to freeze it (effectively stalling PC)
            new_if_id = if_id;
            return;
        }

        // normal fetch
        Instr fetched = imem[pc];
        new_if_id.instr = fetched;
        new_if_id.pc = pc;
        new_if_id.bubble = false;
        // advance PC (we'll possibly overwrite PC on branch resolution in ID)
        pc += 1;
    }

    // ID stage: decode, read registers, produce control signals
    // returns whether a stall is requested by hazard detection unit (load-use case)
    bool ID_stage(bool &flush_next_if) {
        flush_next_if = false;
        // default set new_id_ex bubble, will fill if not bubble
        new_id_ex = ID_EX();
        if (if_id.bubble) { new_id_ex.bubble = true; return false; }
        Instr ins = if_id.instr;
        // HALT handling: pass HALT down
        if (ins.type == I_HALT) {
            new_id_ex.instr = ins;
            new_id_ex.bubble = false;
            // set signals to zero
            return false;
        }

        // decode into control signals & fields
        ID_EX nid;
        nid.bubble = false;
        nid.instr = ins;
        nid.pc = if_id.pc;
        nid.rs = ins.rs;
        nid.rt = ins.rt;
        nid.rd = ins.rd;
        nid.imm = ins.imm;
        // register reads (note: forwarding may override in EX)
        nid.rs_val = regs[nid.rs];
        nid.rt_val = regs[nid.rt];

        // simple control generation
        switch (ins.type) {
            case I_ADD:
            case I_SUB:
                nid.isRegWrite = true;
                nid.isALUSrc = false;
                nid.isMemRead = false;
                nid.isMemWrite = false;
                nid.isMemToReg = false;
                break;
            case I_ADDI:
                nid.isRegWrite = true;
                nid.isALUSrc = true;
                nid.isMemRead = false;
                nid.isMemWrite = false;
                nid.isMemToReg = false;
                break;
            case I_LW:
                nid.isRegWrite = true;
                nid.isALUSrc = true;
                nid.isMemRead = true;
                nid.isMemWrite = false;
                nid.isMemToReg = true;
                break;
            case I_SW:
                nid.isRegWrite = false;
                nid.isALUSrc = true;
                nid.isMemRead = false;
                nid.isMemWrite = true;
                nid.isMemToReg = false;
                break;
            case I_BEQ:
                nid.isBranch = true;
                nid.isRegWrite = false;
                nid.isMemRead = false;
                nid.isMemWrite = false;
                break;
            case I_NOP:
                // nothing
                break;
            default:
                break;
        }

        // Hazard detection: load-use stall
        // If ID needs a source (rs or rt) that's the destination of a load in ID_EX (i.e., previous instr is LW),
        // then stall one cycle: insert bubble into ID/EX, freeze IF/ID (stall IF), and keep PC unchanged.
        bool loadUseStall = false;
        if (!id_ex.bubble && id_ex.isMemRead) {
            int loadDst = id_ex.rd; // destination of LW in ID/EX
            // if current instruction uses loadDst as source (and loadDst != 0)
            if (loadDst != 0 && (loadDst == nid.rs || loadDst == nid.rt)) {
                loadUseStall = true;
            }
        }

        if (loadUseStall) {
            // Insert bubble in new_id_ex, and cause IF stage to stall (ID will request stall)
            new_id_ex = ID_EX(); // bubble
            // also need to freeze IF/ID by keeping new_if_id = current if_id in IF_stage via stall flag
            return true;
        }

        // Branch handling: simple approach - resolve branch in ID (assume branch target known here)
        if (nid.isBranch) {
            // BEQ: if regs equal -> branch taken
            if (nid.rs_val == nid.rt_val) {
                // taken: set PC = target (pc + imm) and flush IF stage (next instruction)
                pc = nid.pc + 1 + nid.imm; // imm is relative offset (in instructions)
                // flush IF/ID (we already advanced PC in IF stage normally, so we overwrite)
                flush_next_if = true;
            }
            // If branch not taken we do nothing special (PC already advanced)
        }

        // all good, write into new_id_ex
        new_id_ex = nid;
        return false;
    }

    // EX stage: ALU ops, apply forwarding
    void EX_stage() {
        new_ex_mem = EX_MEM();
        if (id_ex.bubble) { new_ex_mem.bubble = true; return; }

        Instr ins = id_ex.instr;
        EX_MEM nex;
        nex.bubble = false;
        nex.instr = ins;
        nex.pc = id_ex.pc;
        // default control signals propagated
        nex.isRegWrite = id_ex.isRegWrite;
        nex.isMemRead = id_ex.isMemRead;
        nex.isMemWrite = id_ex.isMemWrite;
        nex.isMemToReg = id_ex.isMemToReg;
        // destination register for writes: for R-type rd, for I-type rd (we use rd field for ADDI/LW)
        nex.rd = id_ex.rd;

        // Forwarding logic: check EX/MEM and MEM/WB for data hazards
        int opA = id_ex.rs_val;
        int opB = id_ex.rt_val;

        // EX/MEM forwarding (highest priority): if EX/MEM will write to a reg that ID/EX needs
        if (!ex_mem.bubble && ex_mem.isRegWrite && ex_mem.rd != 0) {
            if (ex_mem.rd == id_ex.rs) {
                opA = ex_mem.alu_result;
            }
            if (ex_mem.rd == id_ex.rt) {
                opB = ex_mem.alu_result;
            }
        }
        // MEM/WB forwarding (next priority)
        if (!mem_wb.bubble && mem_wb.isRegWrite && mem_wb.rd != 0) {
            int wb_val = mem_wb.isMemToReg ? mem_wb.mem_data : mem_wb.alu_result;
            if (mem_wb.rd == id_ex.rs) opA = wb_val;
            if (mem_wb.rd == id_ex.rt) opB = wb_val;
        }

        // ALU operation
        int alu_in2 = id_ex.isALUSrc ? id_ex.imm : opB;
        int alu_out = 0;
        switch (ins.type) {
            case I_ADD: alu_out = opA + opB; break;
            case I_SUB: alu_out = opA - opB; break;
            case I_ADDI: alu_out = opA + id_ex.imm; break;
            case I_LW:
            case I_SW:
                alu_out = opA + id_ex.imm; // address calc
                break;
            default:
                break;
        }

        nex.alu_result = alu_out;
        nex.rt_val = opB; // for store
        new_ex_mem = nex;
    }

    // MEM stage: memory access
    void MEM_stage() {
        new_mem_wb = MEM_WB();
        if (ex_mem.bubble) { new_mem_wb.bubble = true; return; }

        Instr ins = ex_mem.instr;
        MEM_WB nmem;
        nmem.bubble = false;
        nmem.instr = ins;
        nmem.pc = ex_mem.pc;
        nmem.alu_result = ex_mem.alu_result;
        nmem.rd = ex_mem.rd;
        nmem.isRegWrite = ex_mem.isRegWrite;
        nmem.isMemToReg = ex_mem.isMemToReg;

        if (ex_mem.isMemRead) {
            int addr = ex_mem.alu_result;
            if (addr >= 0 && addr < (int)dmem.size())
                nmem.mem_data = dmem[addr];
            else
                nmem.mem_data = 0;
        } else if (ex_mem.isMemWrite) {
            int addr = ex_mem.alu_result;
            if (addr >= 0 && addr < (int)dmem.size())
                dmem[addr] = ex_mem.rt_val;
        }

        new_mem_wb = nmem;
    }

    // WB stage: writeback to register file
    void WB_stage() {
        if (mem_wb.bubble) return;
        if (mem_wb.instr.type == I_HALT) {
            halted = true;
            return;
        }
        if (mem_wb.isRegWrite && mem_wb.rd != 0) {
            int val = mem_wb.isMemToReg ? mem_wb.mem_data : mem_wb.alu_result;
            regs[mem_wb.rd] = val;
        }
    }

    // Step: perform one cycle (WB->MEM->EX->ID->IF), compute new pipeline regs then update
    void step_cycle(int cycle) {
        // 1. WB stage
        WB_stage();

        // 2. MEM stage
        MEM_stage();

        // 3. EX stage
        EX_stage();

        // 4. ID stage (may request stall or flush)
        bool flush_next_if = false;
        bool stallIF = ID_stage(flush_next_if);

        // 5. IF stage (consider stall)
        IF_stage(stallIF);

        // If branch taken in ID, flush IF/ID by marking bubble
        if (flush_next_if) {
            new_if_id.bubble = true;
        }

        // Now update pipeline registers at clock edge
        if_id = new_if_id;
        id_ex = new_id_ex;
        ex_mem = new_ex_mem;
        mem_wb = new_mem_wb;

        // If HALT in pipeline and has reached WB, halted will be set in WB
        // Print status for debugging
        cout << "Cycle " << cycle << " PC=" << pc
             << " IF_ID.bubble=" << if_id.bubble
             << " ID_EX.bubble=" << id_ex.bubble
             << " EX_MEM.bubble=" << ex_mem.bubble
             << " MEM_WB.bubble=" << mem_wb.bubble << "\n";
    }

    // run simulation until halted or max cycles
    void run(int max_cycles=200) {
        int cyc=0;
        // Initialize IF stage to fetch from PC=0
        new_if_id.bubble = true;
        if_id.bubble = true;
        id_ex.bubble = true;
        ex_mem.bubble = true;
        mem_wb.bubble = true;

        while (!halted && cyc < max_cycles) {
            step_cycle(cyc);
            cyc++;
        }
        cout << "Simulation ended at cycle " << cyc << " halted=" << halted << "\n";
        // dump registers
        cout << "Registers:\n";
        for (int i=0;i<8;i++) {
            cout << "R" << i << "=" << regs[i] << " ";
        }
        cout << "\nMemory (first 16):\n";
        for (int i=0;i<16;i++) cout << dmem[i] << " ";
        cout << "\n";
    }
};

// Helper to create instructions easily
Instr make_add(int rd,int rs,int rt) { Instr i; i.type=I_ADD; i.rd=rd;i.rs=rs;i.rt=rt;return i; }
Instr make_sub(int rd,int rs,int rt) { Instr i; i.type=I_SUB; i.rd=rd;i.rs=rs;i.rt=rt;return i; }
Instr make_addi(int rd,int rs,int imm) { Instr i; i.type=I_ADDI; i.rd=rd;i.rs=rs;i.imm=imm;return i; }
Instr make_lw(int rd,int offset,int rs) { Instr i; i.type=I_LW; i.rd=rd;i.rs=rs;i.imm=offset; return i;}
Instr make_sw(int rt,int offset,int rs) { Instr i; i.type=I_SW; i.rt=rt;i.rs=rs;i.imm=offset; return i;}
Instr make_beq(int rs,int rt,int offset) { Instr i; i.type=I_BEQ; i.rs=rs;i.rt=rt;i.imm=offset; return i;}
Instr make_nop() { Instr i; i.type=I_NOP; return i; }
Instr make_halt() { return Instr::halt(); }

int main() {
    CPU cpu(64, 256);

    // Example program:
    // R0 always zero. We'll do:
    // ADDI R1, R0, 10    ; R1 = 10
    // ADDI R2, R0, 20    ; R2 = 20
    // ADD  R3, R1, R2    ; R3 = 30
    // SW   R3, 0(R0)     ; MEM[0] = 30
    // LW   R4, 0(R0)     ; R4 = 30 (load-use hazard after SW won't cause stall since SW does not create load)
    // BEQ  R4, R3, 2     ; branch taken? yes -> skip next ADDI (example)
    // ADDI R5, R0, 7     ; (may be skipped)
    // HALT
    vector<Instr> prog = {
        make_addi(1, 0, 10),
        make_addi(2, 0, 20),
        make_add(3,1,2),
        make_sw(3, 0, 0),
        make_lw(4, 0, 0),
        make_beq(4,3,2),   // if equal jump forward by 2 (skip next instr)
        make_addi(5,0,7),
        make_halt()
    };

    cpu.load_program(prog);
    cpu.run(200);

    return 0;
}
