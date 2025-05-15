#include<stdcpp.h>
using namespace std;
vector<pair<string,string> > dataMem={{"268501184",(bitset<32>(15)).to_string()},{"268501188",(bitset<32>(52)).to_string()},{"268501192",(bitset<32>(-11)).to_string()},{"268501196",(bitset<32>(0)).to_string()},{"268501200",(bitset<32>(5)).to_string()},{"268501204",""},{"268501208",""},{"268501212",""},{"268501216",(bitset<32>(15)).to_string()},{"268501220",(bitset<32>(52)).to_string()},{"268501224",(bitset<32>(-11)).to_string()},{"268501228",(bitset<32>(0)).to_string()},{"268501232",(bitset<32>(5)).to_string()}};
vector<pair<string,string> >if_id_next={//2
    {"pc","0"},
    {"instruction","0"},
};

vector<pair<string,string> >id_ex_next={//17
    {"instruction","0"},
    {"pc","0"},
    {"data_1","0"},
    {"data_2","0"},
    {"sign_ext","00"},
    {"rs","0"},
    {"rt","0"},
    {"rd","0"},
    {"RegDest","0"},//control signals
    {"ALUsrc","0"},//ex control signsals
    {"branch","0"},
    {"ALUop","0"},
    {"jump","0"},
    {"MemRead","0"},//mem control signals
    {"RegWrite","0"},
    {"MemtoReg","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >ex_mem_next={
    {"instruction","0"},
    {"alu_res","0"},//
    {"data_write","0"},
    {"rd","0"},
    {"ALUsrc","0"},//ex control signsals
    {"branch","0"},
    {"ALUop","0"},
    {"jump","0"},
    {"MemRead","0"},//mem control signals
    {"MemtoReg","0"},
    {"RegDest","0"},
    {"RegWrite","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >mem_wb_next={
    {"instruction","0"},
    {"extracted_mem","0"},
    {"alu_res","0"},
    {"write_data","0"},
    {"rd","0"},
    {"MemRead","0"},//mem control signals
    {"MemtoReg","0"},
    {"RegDest","0"},
    {"RegWrite","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >if_id={
    {"pc","0"},
    {"instruction","0"},
};

vector<pair<string,string> >id_ex={
    {"instruction","0"},
    {"pc","0"},
    {"data_1","0"},
    {"data_2","0"},
    {"sign_ext","00"},
    {"rs","0"},
    {"rt","0"},
    {"rd","0"},
    {"RegDest","0"},
    {"ALUsrc","0"},//ex control signsals
    {"branch","0"},
    {"ALUop","0"},
    {"jump","0"},
    {"MemRead","0"},//mem control signals
    {"RegWrite","0"},
    {"MemtoReg","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >ex_mem={
    {"instruction","0"},
    {"zero","0"},
    {"branch","0"},
    {"alu_res","0"},
    {"data_write","0"},
    {"rd","0"},
    {"ALUsrc","0"},//ex control signsals
    {"branch","0"},
    {"ALUop","0"},
    {"jump","0"},
    {"MemRead","0"},//mem control signals
    {"MemtoReg","0"},
    {"RegDest","0"},
    {"RegWrite","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >mem_wb={
    {"instruction","0"},
    {"extracted_mem","0"},
    {"alu_res","0"},
    {"write_data","0"},
    {"rd","0"},
    {"MemRead","0"},//mem control signals
    {"MemtoReg","0"},
    {"RegDest","0"},
    {"RegWrite","0"},
    {"MemWrite","0"}
};
vector<pair<string,string> >instrMem={{"4194380", "00000000000010110100000000100001"},
    {"4194384", "00000000000000001011100000100001"},
    {"4194388", "00100000000101100000000000000001"},
    {"4194392", "00000001001101101011000000100010"},
    {"4194396", "00010010111010010000000000000110"},
    {"4194400", "10001101010101010000000000000000"},
    {"4194404", "10101101011101010000000000000000"},
    {"4194408", "00100001010010100000000000000100"},
    {"4194412", "00100001011010110000000000000100"},
    {"4194416", "00100010111101110000000000000001"},
    {"4194420", "00001000000100000000000000010111"},
    {"4194424", "00000000000010000101100000100001"}, 
    {"4194428", "00000000000000001011100000100001"},
    {"4194432", "00010010111101100000000000011000"}, 
    {"4194436", "00000000000101110110000000100001"},
    {"4194440", "00100010111011010000000000000001"},
    {"4194444", "00010001101010010000000000001011"},
    {"4194448", "00000000000011001100000010000000"},
    {"4194452", "00000001011110001100000000100000"},  
    {"4194456", "10001111000100000000000000000000"},
    {"4194460", "00000000000011011100100010000000"},
    {"4194464", "00000011001010111100100000100000"},
    {"4194468", "10001111001100010000000000000000"},
    {"4194472", "00000010001100000000100000101010"},
    {"4194476", "00010100001000000000000000000001"},
    {"4194480", "00000000000011010110000000100001"},
    {"4194484", "00100001101011010000000000000001"},
    {"4194488", "00001000000100000000000000100011"},
    {"4194492", "00000000000011000111100010000000"},
    {"4194496", "00000001011011110111100000100000"},
    {"4194500", "00000000000101110111000010000000"},
    {"4194504", "00000001110010110111000000100000"},
    {"4194508", "10001101111100100000000000000000"},
    {"4194512", "10001101110101000000000000000000"},
    {"4194516", "10101101110100100000000000000000"},
    {"4194520", "10101101111101000000000000000000"},
    {"4194524", "00100010111101110000000000000001"},
    {"4194528", "00001000000100000000000000100000"},
    {"4194532", "00000000000010000101100000100001"}};
map<string, string>registers = {
        {"00001", "$at"},
        {"00000", "$zero"},
        {"01001", "$t1"},
        {"01010", "$t2",},
        {"01011", "$t3"},
        {"01100", "$t4"},
        {"01101", "$t5"},
        {"01110", "$t6"},
        {"01111", "$t7"},
        {"10000", "$s0"},
        {"10001", "$s1"},
        {"10010", "$s2"},
        {"10011", "$s3"},
        {"10100", "$s4"},
        {"10101", "$s5"},
        {"10110", "$s6"},
        {"10111", "$s7"},
        {"11000", "$t8"},
        {"11001", "$t9"}
    };
vector<pair<string,string> >regValues={{"$at","0"},{"$zero", "00000"},{"$t0","0"},{"$t1", (bitset<32>(5)).to_string()},{"$t2", (bitset<32>(268501184)).to_string()},{"$t3", (bitset<32>(268501216)).to_string()},{"$t4", "0"},{"$t5", "0"},{"$t6", "0"},{"$t7", "0"},{"$s0", "0"},{"$s1", "0"},{"$s2", "0"},{"$s3", "0"},{"$s4", "0"},{"$s5", "0"},{"$s6", "0"},{"$s7", "0"},{"$t8", (bitset<32>(268501184)).to_string()},{"$t9", (bitset<32>(268501216)).to_string()}};//modify//values stored in register

vector<pair<string,int> >control_signal={
    {"RegDest",0},
    {"branch",0},
    {"MemRead",0},
    {"MemtoReg",0},
    {"MemWrite",0},
    {"ALUsrc",0},
    {"RegWrite",0},
    {"jump",0},
    {"ALUop",0}
};
string sliceString(string s,int a,int b){
    string k=s.substr(31-a,a-b+1);
    return k;
}
string opcode(string instr){
    return sliceString(instr,31,26);
}
// int counter=0;//global variable programme counter 
// int pc(){
//     int pc_old=counter;
//     counter+=4;
//     if(pc_halt){//change
//         counter-=4;
//     }
//     return pc_old;
// }

int binaryToDecimal(const std::string& binaryStr) {
    bitset<32> bits(binaryStr); // Assuming a 32-bit binary string, adjust as needed
    return bits.to_ulong();
}
void mux(int s0,string i0,string i1,string& out){
    if(s0==1)
    out=i1;
    if(s0==0)
    out=i0;
}
int pc_halt=0;
int if_id_write=0;
string counter=(bitset<32>(4194380)).to_string();//global variable programme counter 
string pc(){
    //cout<<"func pc statr"<<endl;
    //cout<<"counter"<<(counter)<<endl;
    string pc_old=(bitset<32>(binaryToDecimal(counter))).to_string();
    //cout<<"in pc"<<endl;
    counter=(bitset<32>(binaryToDecimal(counter)+4)).to_string();
    //cout<<"pc_old "<<pc_old<<endl;
    if(pc_halt){
        counter=(bitset<32>(binaryToDecimal(counter)-4)).to_string();
    }
    //cout<<"counter"<<binaryToDecimal(counter)<<endl;
    return pc_old;
}

void regFile(){
    //cout<<"in reg file"<<endl;
    //cout<<if_id[1].second<<endl;
    string read1=sliceString(if_id[1].second,25,21);
    string read2=sliceString(if_id[1].second,20,16);
    /*auto IT1=registers[read1] ;

    auto IT2=registers[read2];*/
    auto it1=registers.find(read1);
    auto IT1=it1->second; 
    auto it2=registers.find(read2);
    auto IT2=it2->second; 
    for(int i=0;i<regValues.size();i++){
        if(regValues[i].first==IT1)
        id_ex_next[2].second=regValues[i].second;
    }
    for(int i=0;i<regValues.size();i++){
        if(regValues[i].first==IT2)
        id_ex_next[3].second=regValues[i].second;
    }
    
    
    if(mem_wb[8].second=="1"){
        string writereg="";
        mux(stoi(mem_wb[7].second),sliceString(mem_wb[0].second,20,16),sliceString(mem_wb[0].second,15,11),writereg);
        auto it=registers.find(writereg);
        auto IT=it->second;
        for(int i=0;i<regValues.size();i++){
            if(regValues[i].first==IT){
            regValues[i].second=mem_wb[3].second;
        }
    }
    id_ex_next[5].second=read1;
    id_ex_next[6].second=read2;
    id_ex_next[7].second=sliceString(if_id[1].second,15,11);
   
    }
}

string rfunction(string instr){
    return sliceString(instr,5,0);
}

string shamt(string instr){
    return sliceString(instr,10,6);
}

// string ALUop="00";

void control_unit(string instr){
    string op=sliceString(instr,31,26);
    if(op=="000000"){
        control_signal[0].second=1;control_signal[1].second=0;control_signal[1].second=0;control_signal[2].second=0;control_signal[3].second=0;control_signal[4].second=0;control_signal[5].second=0;control_signal[6].second=1;
        if(rfunction(instr)=="100000")
            control_signal[8].second=0;//add
        if(rfunction(instr)=="100010")
        control_signal[8].second=0;//sub
        if(rfunction(instr)=="101010")
        control_signal[8].second=0;//slt
        if(rfunction(instr)=="100100")
        control_signal[8].second=0;//and
        if(rfunction(instr)=="100101")
        control_signal[8].second=0;//or
        if(rfunction(instr)=="000000")
        control_signal[8].second=0;//sll
        if(rfunction(instr)=="001000")
        control_signal[8].second=0;//jr
        if(rfunction(instr)=="100001")
        control_signal[8].second=0;
    }
    else if(op=="100011"){//lw
        control_signal[0].second=0;
        control_signal[1].second=0;
        control_signal[2].second=1;
        control_signal[3].second=1;
        control_signal[4].second=0;
        control_signal[5].second=1;
        control_signal[6].second=1;
        control_signal[7].second=0;
        control_signal[8].second=0;
    }
    else if(op=="101011"){//sw
        control_signal[0].second=0;
        control_signal[1].second=0;
        control_signal[2].second=0;
        control_signal[3].second=1;
        control_signal[8].second=0;
        control_signal[4].second=1;
        control_signal[5].second=1;
        control_signal[6].second=0;
        control_signal[7].second=0;
    }
    else if(op=="000100" || op=="000101"){//beq or bne
        control_signal[0].second=0;
        control_signal[1].second=1;
        control_signal[2].second=0;
        control_signal[3].second=1;
        control_signal[8].second=1;
        control_signal[4].second=0;
        control_signal[5].second=0;
        control_signal[6].second=0;
        control_signal[7].second=0;
    }
    else if(op=="000010"){//jump
        control_signal[0].second=0;
        control_signal[1].second=1;
        control_signal[2].second=0;
        control_signal[3].second=1;
        control_signal[8].second=1;
        control_signal[4].second=0;
        control_signal[5].second=0;
        control_signal[6].second=0;
        control_signal[7].second=1;
        }
    else if(op == "101000"){//addi
        control_signal[0].second=0;
        control_signal[1].second=0;
        control_signal[2].second=0;
        control_signal[3].second=0;
        control_signal[8].second=1;
        control_signal[4].second=0;
        control_signal[5].second=1;
        control_signal[6].second=1;
        control_signal[7].second=0;
    }
    /*for(int i=0;i<8;i++){
        cout<<control_signal[i].second<<endl;
    }*/
}

string signExtend(string s){
    char k=s[0];
    string p="";
    if(k=='0')
    return bitset<32>((binaryToDecimal(s))).to_string();
    else
    for(int i=0;i<16;i++){
        p+="1";
    }
    id_ex_next[4].second=(p+s);//store in pipeline
    return p+s;
}

string shift_left_2(string s){
    return sliceString(s,29,0)+"00";
}

void ALUcontrol(string instr,string ALUop,string& out){
    if(opcode(instr)=="100011"){
        out="010";
    }
    if(opcode(instr)=="101011"){
        out="010";
    }
    if(opcode(instr)=="000100"){
        out="011";
    }
    if(rfunction(instr)=="100000"){
        out="010";
    }
    if(rfunction(instr)=="100010"){
        out="011";
    }
    if(rfunction(instr)=="100100"){
        out="000";
    }
    if(rfunction(instr)=="100101"){
        out="001";
    }
    if(rfunction(instr)=="101010"){
        out="100";
    }
    if(rfunction(instr)=="100001"){
        out="010";
    }
    //if(rfunction(instr)=="100000")//add
    //if(rfunction(instr)=="100010")//sub
    if(rfunction(instr)=="101010"){
        out="100";}//slt
    //if(rfunction(instr)=="100100")//and
    //if(rfunction(instr)=="100101")//or
    if(rfunction(instr)=="000000"){
        out="101";}//sll
}

int Zero=0;
void ALU(string controlInput,string op1,string op2,string& ALUresult,string instr){
    int result;
    string sh_amt=shamt(instr);
    int k=binaryToDecimal(sh_amt);
    if(controlInput=="000"){
        ALUresult=(bitset<32>(op1) & bitset<32>(op2)).to_string();
    }
    if(controlInput=="001"){
        ALUresult=(bitset<32>(op1) | bitset<32>(op2)).to_string();
    }
    if(controlInput=="010"){
        result=(binaryToDecimal(op1) + binaryToDecimal(op2));
        ALUresult=bitset<32>((result)).to_string();
    }
    if(controlInput=="011"){
        result=(binaryToDecimal(op1) - binaryToDecimal(op2));
        ALUresult=bitset<32>((result)).to_string();
    }
    if(controlInput=="100"){
        if(binaryToDecimal(op1)<binaryToDecimal(op2)){
            ALUresult=(bitset<32>(1)).to_string();
        }
        else
        ALUresult=(bitset<32>(0)).to_string();
    }
    if(controlInput=="101"){
       result=(binaryToDecimal(op2)<<k);
       ALUresult=(bitset<32>(result)).to_string();
    }
    if(ALUresult==(bitset<32>(0)).to_string()){
        Zero=1;
    }
    else
    Zero=0;
}

int forward_a=0;
int forward_b=0;

void hazard_unit(){
    if(id_ex[13].second=="1" and ((id_ex[6].second==sliceString(if_id[0].second,25,21)) or (id_ex[6].second==sliceString(if_id[0].second,20,16)))){
        pc_halt=1;
        if_id_write=1;
        for(int i=0;i<control_signal.size();i++){
            control_signal[i].second=0;
        }
    }
}

void instruction_fetch(){
    string mem_add=pc();
    //cout<<"in_fetch"<<endl;
    string instruction="";
    //string instruction=instrMem[to_string((binaryToDecimal(mem_add)))];
    for(int i=0;i<instrMem.size();i++){
        if(instrMem[i].first==to_string(binaryToDecimal(mem_add)))
        instruction=instrMem[i].second;
    }
    if_id_next[0].second=(mem_add); //loading values in ref if/id
    if_id_next[1].second=instruction;
    cout<<"fetch_end"<<endl;
}
void instruction_deocde(){
   if(if_id[1].second=="0"){   
   /*for(int i=0;i<if_id_next.size();i++){
        if_id[i].second=if_id_next[i].second;
    }*/
   return;}
    string instr=if_id[1].second;

    control_unit(instr);
    // generates control signals
    for(int i=0;i<id_ex_next.size();i++){
        for(int j=0;j<control_signal.size();j++){
            if(id_ex_next[i].first==control_signal[j].first){
                id_ex_next[i].second=to_string(control_signal[j].second);
            }
        }
    }
    
    string insrt=if_id[1].second;
    id_ex_next[0].second=if_id[1].second;
    id_ex_next[1].second=if_id[0].second;
    id_ex_next[4].second=sliceString(instr,15,0);
    id_ex_next[5].second=sliceString(instr,25,21);
    id_ex_next[6].second=sliceString(instr,20,16);
    id_ex_next[7].second=sliceString(instr,15,11); 
    regFile();
    string s=signExtend(sliceString(if_id[1].second,15,0));
    hazard_unit();//if id stalling
    for(int i=0;i<if_id_next.size();i++){
        if_id[i].second=if_id_next[i].second;
    }
    cout<<"dec_end"<<endl;
}
void mux3(int ctrl,string i0,string i1,string i2,string& out){
    if(ctrl==0)
    out=i0;
    else if(ctrl==1)
    out=i1;
    else if(ctrl==2)
    out=i2;
}

void instruction_exe(){//include forward1 and forward2
    if(id_ex[0].second=="0"){
    /*for(int i=0;i<id_ex_next.size();i++){
        for(int j=0;j<id_ex.size();j++){
            if(id_ex[j].first==id_ex_next[i].first)
            id_ex[j].second=id_ex_next[i].second;
        }
    }*/ 
    return;
    }
    mux(stoi(mem_wb[7].second),id_ex[6].second,id_ex[7].second,ex_mem[5].second);
    string out="",ALU_out="",OP1="",OP2="",instr=id_ex[0].second;
    ALUcontrol(instr,"",ALU_out);
    mux(stoi(mem_wb[6].second),mem_wb[2].second,mem_wb[1].second,out);
    mux3(forward_a,id_ex[2].second,out,ex_mem[3].second,OP1);
    mux3(forward_b,id_ex[3].second,out,ex_mem[3].second,OP2);
    cout<<"A   "<<forward_a<<endl;
    cout<<"B   "<<forward_b<<endl;
    cout<<"op1 "<<OP1<<endl;
    cout<<"op2 "<<OP2<<endl;
    ALU(ALU_out,OP1,OP2,ex_mem_next[1].second,id_ex[0].second);
    cout<<"ALU result"<<ex_mem_next[1].second<<endl;
    string op1=shift_left_2(id_ex[4].second);
    id_ex[1].second=bitset<32>(binaryToDecimal(id_ex[1].second)+4).to_string();
    string in1="";
    string s=shift_left_2(sliceString(id_ex[0].second,25,0));
    s="0000"+s;
    ALU("010",op1,id_ex[1].second,in1,id_ex[0].second);
    mux(id_ex[10].second=="1" && (Zero),id_ex[1].second,in1,id_ex[1].second);
    string x="";
    mux(id_ex[12].second=="1",id_ex[1].second,s,x); 
    counter=(x);
    if(id_ex[10].second=="1" or id_ex[12].second=="1"){
        for(int i=0;i<id_ex.size();i++){
            id_ex[i].second="0";
        }
        for(int j=0;j<if_id.size();j++){
            if_id[j].second="0";
        }
    }
    ex_mem_next[2].second=id_ex[3].second;
    for(int i=0;i<id_ex.size();i++){
        for(int j=0;j<ex_mem_next.size();j++){
            if(ex_mem_next[j].first==id_ex[i].first)
            ex_mem_next[j].second=id_ex[i].second;
        }
    }
    for(int i=0;i<id_ex_next.size();i++){
        for(int j=0;j<id_ex.size();j++){
            if(id_ex[j].first==id_ex_next[i].first)
            id_ex[j].second=id_ex_next[i].second;
        }
    }  
    cout<<"exe_end"<<endl; 
}

void memory_access(){
    if(ex_mem[0].second=="0"){
    /*for(int i=0;i<ex_mem.size();i++){
        for(int j=0;j<ex_mem_next.size();j++){
            if(ex_mem_next[j].first==ex_mem[i].first)
            ex_mem[i].second=ex_mem_next[j].second;
        }
    }*/
    return;
    }
    if(ex_mem[10].second=="1" and ex_mem[14].second=="0"){
        for(int i=0;i<dataMem.size();i++){
            if(dataMem[i].first==ex_mem[3].second){//convrert them to int
                mem_wb_next[1].second=dataMem[i].second;
            }
        }
    }
    else if(ex_mem[14].second=="1"){
        for(int i=0;i<dataMem.size();i++){
            if(dataMem[i].first==ex_mem[3].second){//convert them to int
            dataMem[i].second=ex_mem[4].second;

            }          
        }
    }
    if(ex_mem[10].second=="1" and ex_mem_next[12].second=="1"){
        ex_mem_next[2].second=mem_wb_next[1].second;///changes
    }
    for(int i=0;i<mem_wb_next.size();i++){
        for(int j=0;j<ex_mem.size();j++){
            if(ex_mem[j].first==mem_wb_next[i].first)
            mem_wb_next[i].second=ex_mem[j].second;
        }
    }
    for(int i=0;i<ex_mem.size();i++){
        for(int j=0;j<ex_mem_next.size();j++){
            if(ex_mem_next[j].first==ex_mem[i].first)
            ex_mem[i].second=ex_mem_next[j].second;
        }
    }
    cout<<"mem_access"<<endl;
}

void write_back(){
    if(mem_wb[0].second=="0"){
    /*for(int i=0;i<mem_wb.size();i++){
        for(int k=0;k<mem_wb_next.size();k++){
            if(mem_wb_next[k].first==mem_wb[i].first){
                mem_wb[i].second=mem_wb_next[k].second;
            }
        }
    }*/
    return;
    }
    string out="",s="";
    mux(stoi(mem_wb[6].second),mem_wb[2].second,mem_wb[1].second,out);
    mem_wb[3].second=out;
    if(mem_wb[8].second=="1"){
        regFile();
    }
    for(int i=0;i<mem_wb.size();i++){
        for(int k=0;k<mem_wb_next.size();k++){
            if(mem_wb_next[k].first==mem_wb[i].first){
                mem_wb[i].second=mem_wb_next[k].second;
            }
        }
    }
    cout<<"write back"<<endl;
}

int main(){
    int clock=0,i=0;
    while(1){
        if(binaryToDecimal(counter)==4194536){
            break;
        }
        cout<<"clock "<<i<<endl;
        cout<<binaryToDecimal(counter)<<endl;
        instruction_fetch();
        instruction_deocde();
        instruction_exe();
        memory_access();
        i++;
    }
    for(int i=0;i<regValues.size();i++){
        cout<<regValues[i].first<<" : "<<binaryToDecimal(regValues[i].second)<<endl;
    }
    cout<<""<<endl;
    cout<<"Data Memory:"<<endl;
    for(int i=0;i<dataMem.size();i++){
        cout<<dataMem[i].first<<" : "<<binaryToDecimal(dataMem[i].second)<<endl;
    }
}