#include<stdcpp.h>
using namespace std;
string sliceString(string s,int a,int b){
    string k=s.substr(31-a,a-b+1);
    return k;
}
map < string, string > registers =
{{"00001","$at"},{"00000","$zero"},{"01000","$t0"},{"01001","$t1"},{"01010","$t2"},{"01011","$t3"},{"01100","$t4"},{"01101","$t5"},{"01110","$t6"},{"01111","$t7"},{"10000","$s0"},{"10001","$s1"},{ "10010","$s2"},{ "10011","$s3",},{"10100","$s4"},{ "10101","$s5"},{ "10110","$s6"},{"10111","$s7"},{ "11000","$t8"},{ "11001","$t9"}};
vector<pair<string,string> >instrMem1={{"4194380", "00000000000010110100000000100001"},
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
    vector<pair<string,string> >instrMem2=
{ 
     {"4194356","10001111000010000000000000000000"},  
     {"4194360","00100000000010110000000000000001"},  
     {"4194364","00000000000010000100100000100001"}, 
     {"4194368","00100001000010101111111111111111"},  
     {"4194372","00010001010000000000000000000111"}, 
     {"4194376","00100001010011000000000000000000"}, 
     {"4194380","00100001001011010000000000000000"}, 
     {"4194384","00100001010010101111111111111111"},  
     {"4194388","00010001100010111111111111111011"},  
     {"4194392","00100001100011001111111111111111"},  
     {"4194396","00000001001011010100100000100000"},  
     {"4194400","00010000000000001111111111111100"},  
     {"4194404","10101111001010010000000000000000"}
 };
vector<pair<string,string> >regValues={{"$at","0"},{"$zero", "00000"},{"$t0","0"},{"$t1", (bitset<32>(5)).to_string()},{"$t2", (bitset<32>(268501184)).to_string()},{"$t3", (bitset<32>(268501216)).to_string()},{"$t4", "0"},{"$t5", "0"},{"$t6", "0"},{"$t7", "0"},{"$s0", "0"},{"$s1", "0"},{"$s2", "0"},{"$s3", "0"},{"$s4", "0"},{"$s5", "0"},{"$s6", "0"},{"$s7", "0"},{"$t8", (bitset<32>(268501184)).to_string()},{"$t9", (bitset<32>(268501216)).to_string()}};//modify
string add_in="268501184";
vector<pair<string,string> > dataMem={{"268501184",(bitset<32>(5)).to_string()},{"268501188",(bitset<32>(52)).to_string()},{"268501192",(bitset<32>(-11)).to_string()},{"268501196",(bitset<32>(0)).to_string()},{"268501200",(bitset<32>(23)).to_string()},{"268501204",""},{"268501208",""},{"268501212",""},{"268501216",""},{"268501220",""},{"268501224",""},{"268501228",""},{"268501232",""}};//modify
int binaryToDecimal(const std::string& binaryStr) {
    bitset<32> bits(binaryStr); // Assuming a 32-bit binary string, adjust as needed
    return bits.to_ulong();
}
void regFile(string read1,string read2,string writeData,string writeReg,string& data1,string& data2,int RegWrite ){
    auto it1=registers.find(read1);
    auto IT1=it1->second; 
    auto it2=registers.find(read2);
    auto IT2=it2->second; 
    for(int i=0;i<regValues.size();i++){
        if(regValues[i].first==IT1)
        data1=regValues[i].second;
    }
    for(int i=0;i<regValues.size();i++){
        if(regValues[i].first==IT2)
        data2=regValues[i].second; 
    }
    if(RegWrite==1){
    auto it=registers.find(writeReg);
    auto IT=it->second;
    for(int i=0;i<regValues.size();i++){
        if(regValues[i].first==IT){
        regValues[i].second=writeData;
    }
    }
    }
}

string opcode(string instr){
    return sliceString(instr,31,26);
}
string rfunction(string instr){
    return sliceString(instr,5,0);
}
string shamt(string instr){
    return sliceString(instr,10,6);
}
void ALUcontrol(string instr,string ALUop,string& out){
    if(opcode(instr)=="100011"){
        out="010";
    }
    else if(opcode(instr)=="101011"){
        out="010";
    }
    else if(opcode(instr)=="000100"){
        out="011";
    }
    else if(opcode(instr)=="001000"){
        out="010";
    }
    else if(rfunction(instr)=="100000"){
        out="010";
    }
    else if(rfunction(instr)=="100010"){
        out="011";
    }
    else if(rfunction(instr)=="100100"){
        out="000";
    }
    else if(rfunction(instr)=="100101"){
        out="001";
    }
    else if(rfunction(instr)=="101010"){
        out="100";
    }
    else if(rfunction(instr)=="100001"){
        out="010";
    }
    else if(rfunction(instr)=="101010"){
        out="100";}//slt
    else if(rfunction(instr)=="000000"){
        out="101";}//sll
}
void ALU(string controlInput,string op1,string op2,int* Zero,string& ALUresult,string instr){
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
        *Zero=1;
    }
    else
    *Zero=0;
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
    return p+s;
}

void mux(int s0,string i0,string i1,string& out){
    if(s0==1)
    out=i1;
    if(s0==0)
    out=i0;
}

string InstrMem(string PC,vector<pair<string,string> >&instrMem){
    for(int i=0;i<instrMem.size();i++){
        if(instrMem[i].first==PC)
        return instrMem[i].second;
    }
    return "";
}

string shiftLeft(string s){
    return sliceString(s,29,0)+"00";
}



string fetch(string PC,vector<pair<string,string> >& instrMem){
    return InstrMem(PC,instrMem);
}

void decode(string instr,string& data1,string& data2,string& in1,int RegDest,string writeData,int RegWrite){
    in1 = signExtend(sliceString(instr,15,0));
    string out="";
    mux(RegDest,sliceString(instr,20,16),sliceString(instr,15,11),out);
    regFile(sliceString(instr,25,21),sliceString(instr,20,16),writeData,out,data1,data2,RegWrite);
}

void execute(int* zero,string sign_out,string data1,string data2,string ALUop,int ALUsrc,int* Zero,string& ALUresult,string PC,int branch,string instr,int jump,string& PC_bar){
    //pass the value of in1 from decode stage sugn extend output and data1 and data2
    string out="",ALU_out="";
    mux(ALUsrc,data2,sign_out,out);
    ALUcontrol(instr,ALUop,ALU_out);
    ALU(ALU_out,data1,out,Zero,ALUresult,instr);
    string op1=shiftLeft(sign_out);
    PC=bitset<32>(stoi(PC)+4).to_string();
    string in1="";
    string s=shiftLeft(sliceString(instr,25,0));
    s="0000"+s;
    ALU("010",op1,PC,zero,in1,instr);
    mux(branch&&(*Zero),PC,in1,PC);
    mux(jump,PC,s,PC_bar);
}

void Mem(string address,string writeData, string& readData,int MemWrite,int MemRead){
    if(MemRead==1 && MemWrite==0){
        for(int i=0;i<dataMem.size();i++){
            if(dataMem[i].first==to_string((binaryToDecimal(address)))){
                readData=dataMem[i].second;
            }
        }
    }
    else if(MemWrite==1){
        for(int i=0;i<dataMem.size();i++){
            if(dataMem[i].first==to_string((binaryToDecimal(address)))){
                dataMem[i].second=writeData;
            }
        }
    }
}

void writeBack(string ALUresult,string data2,string& readData,int MemWrite,int MemRead,int MemtoReg,int RegWrite,int RegDest,string instr){
    //ALUresult of the pvs fn should be taken as address
    //data2 is writedata
    string out="",s="";
    mux(MemtoReg,ALUresult,readData,out);
    string out2="";
    mux(RegDest,sliceString(instr,20,16),sliceString(instr,15,11),out2);
    if(RegWrite==1)
    regFile("","",out,out2,s,s,RegWrite);
}
void ControlPath(string instr,int* RegDest,int* branch,int* MemRead,int* MemtoReg,string& ALUop,int* MemWrite,int* ALUsrc,int* RegWrite,int* jump){
    string op=sliceString(instr,31,26);
    if(op=="000000"){
        *RegDest=1;*branch=0;*MemRead=0;*MemtoReg=0;*MemWrite=0;*ALUsrc=0;*RegWrite=1;*jump=0;
        if(rfunction(instr)=="100000")
            ALUop="00";//add
        if(rfunction(instr)=="100010")
        ALUop="00";//sub
        if(rfunction(instr)=="101010")
        ALUop="00";//slt
        if(rfunction(instr)=="100100")
        ALUop="00";//and
        if(rfunction(instr)=="100101")
        ALUop="00";//or
        if(rfunction(instr)=="000000")
        ALUop="00";//sll
        if(rfunction(instr)=="001000")
        ALUop="00";//jr
        if(rfunction(instr)=="100001")
        ALUop="00";
    }
    else if(op=="100011"){//lw
        *RegDest=0;*branch=0;*MemRead=1;*MemtoReg=1;ALUop="00";*MemWrite=0;*ALUsrc=1;*RegWrite=1;*jump=0;
    }
    else if(op=="101011"){//sw
        *RegDest=0;*branch=0;*MemRead=0;*MemtoReg=1;ALUop="00";*MemWrite=1;*ALUsrc=1;*RegWrite=0;*jump=0;
    }
    else if(op=="000100" || op=="000101"){//beq or bne
        *RegDest=0;*branch=1;*MemRead=0;*MemtoReg=1;ALUop="01";*MemWrite=0;*ALUsrc=0;*RegWrite=0;*jump=0;
    }
    else if(op=="000010"){//jump
        *RegDest=0;*branch=1;*MemRead=0;*MemtoReg=1;ALUop="01";*MemWrite=0;*ALUsrc=0;*RegWrite=0;*jump=1;
        }
    else if(op == "001000"){//addi
        *RegDest=0;*branch=0;*MemRead=0;*MemtoReg=0;ALUop="01";*MemWrite=0;*ALUsrc=1;*RegWrite=1;*jump=0;
    }
    
}
int main(){
    int clock=0;
    vector<string>instrs;
    vector<pair<string,string> >instrMem;
    string s;
    string PC,ALUop,read1,read2,data1,data2,writeData,writeReg,sign_extend,ALUresult="",PC_bar="",readData;
    cout<<"Enter 'Factorial' or 'Sort'"<<endl;
    cin>>s;
    if(s=="Factorial"){
        PC="4194356";
        instrMem=instrMem2;
    }
    if(s=="Sort"){
        PC="4194380";
        instrMem=instrMem1;
    }
    int RegDest,branch,MemRead,MemtoReg,MemWrite,ALUsrc,RegWrite,jump,Zero,zero,i=0;
    while(1){
        if(s=="Sort")
        if(PC=="4194536")
        break;
        if(s=="Factorial")
        if(PC=="4194408")
        break;
    instrs.push_back(fetch(PC,instrMem));
    clock++;
    ControlPath(instrs[i],&RegDest,&branch,&MemRead,&MemtoReg,ALUop,&MemWrite,&ALUsrc,&RegWrite,&jump);
    decode(instrs[i],data1,data2,sign_extend,RegDest,writeData,RegWrite);
    clock++;
    execute(&zero,sign_extend,data1,data2,ALUop,ALUsrc,&Zero,ALUresult,PC,branch,instrs[i],jump,PC_bar);
    clock++;
    int k=binaryToDecimal(PC_bar);
    PC=to_string(k);
    Mem(ALUresult,data2,readData,MemWrite,MemRead);
    clock++;    
    writeBack(ALUresult,data2,readData,MemWrite,MemRead,MemtoReg,RegWrite,RegDest,instrs[i]);
    clock++;
    i++;
    }
    cout<<"Register values:"<<endl;
    for(int i=0;i<regValues.size();i++){
        cout<<regValues[i].first<<" : "<<binaryToDecimal(regValues[i].second)<<endl;
    }
    cout<<""<<endl;
    cout<<"Data Memory:"<<endl;
    for(int i=0;i<dataMem.size();i++){
        cout<<dataMem[i].first<<" : "<<binaryToDecimal(dataMem[i].second)<<endl;
    }
    cout<<""<<endl;
    cout<<"CLOCK: "<<clock<<endl;
}
