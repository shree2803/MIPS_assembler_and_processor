#include<bits/stdc++.h>
using namespace std;
struct Mem
{
  string label;			//label represents the address of the instruction
  string instr;			//instr represents the assembly instruction
};
//maps of registers, opcodes, functions, labels
map < string, string > registers =
{
  {"$at", "00001"},
  {"$zero", "00000"},
  {"$t1", "01001"},
  {"$t2", "01010"},
  {"$t3", "01011"},
  {"$t4", "01100"},
  {"$t5", "01101"},
  {"$t6", "01110"},
  {"$t7", "01111"},
  {"$s0", "10000"},
  {"$s1", "10001"},
  {"$s2", "10010"},
  {"$s3", "10011"},
  {"$s4", "10100"},
  {"$s5", "10101"},
  {"$s6", "10110"},
  {"$s7", "10111"},
  {"$t8", "11000"},
  {"$t9", "11001"}};

map < string, string > opcodes =
{
  {"add", "000000"},
  {"addi", "001000"},
  {"beq", "000100"},
  {"bne", "000101"},
  {"j", "000010"},
  {"jal", "000011"},
  {"addu", "000000"},
  {"lw", "100011"},
  {"sw", "101011"},
  {"slt", "000000"},
  {"sll", "000000"}};

map < string, string > functions =
{
  {"add", "100000"},
  {"addu", "100001"},
  {"slt", "101010"},
  {"sll", "000000"}};

map < string, string > labels =
{
  {"loop2", "4194388"},
  {"loop2end", "4194416"},
  {"forloop", "4194456"},
  {"for2", "4194476"},
  {"update_min", "4194528"},
  {"inner_loop_continue", "4194532"},
  {"for2end", "4194540"},
  {"condn", "4194548"},
  {"endd", "4194612"}};

string text_add = "4194380";	//starting address of the text segment
string
instruction (struct Mem *mem1)
{
  // a function to return the type of instrutction i.e., r or i or j
  string inst = mem1->instr;
  int c = 0;
  int lp = inst.length () - 1;
  if (inst.find (':') != lp)
    {
      inst = inst.substr (inst.find (':') + 1);
    }
  stringstream ss (inst);
  string opc;
  ss >> opc;
  for (int i = 0; i < inst.length (); i++)
    {
      if (inst[i] == '$')
	c++;
    }
  if (c == 3 || opc == "sll")
    return "r";
  if (c == 2)
    return "i";
  if (c == 0)
    return "j";
  return "";
}

string
opcode (struct Mem * mem1)
{
  // function that returns 6 bit opcode of given instruction
  string inst = mem1->instr;
  int lp = inst.length () - 1;
  if (inst.find (':') != lp)
    {
      inst = inst.substr (inst.find (':') + 1);
    }
  stringstream ss (inst);
  string opc;
  ss >> opc;
  auto op = opcodes.find (opc);
  return op->second;
}

string
getReg (struct Mem * mem1)
{
  // function that returns rs+rt+rd+shamt+func for r type
  //return rs+rt+i for i-type
  //return add forj-type
  string inst = mem1->instr;
  int lp = inst.length () - 1;
  if (inst.find (':') != lp)
    {
      inst = inst.substr (inst.find (':') + 1);
    }
  string opc;
  stringstream ss (inst);
  ss >> opc;
  string op = opcode (mem1);
  string rt = "";
  string r2 = "";
  string rd = "";
  string r3 = "";
  if (instruction (mem1) == "r")
    {
      size_t c1 = inst.find (',');
      string r1 = inst.substr (inst.find ('$'), c1 - inst.find ('$'));	//extracting r1 from the instruction
      auto r1it = registers.find (r1);
      string rs = r1it->second;
      size_t c2 = inst.find (',', c1 + 1);
      r2 = inst.substr (c1 + 1, c2 - c1 - 1);	//extracting r2
      r3 = inst.substr (c2 + 1);	//extracting r3
      auto r2it = registers.find (r2);
      rt = r2it->second;
      string func;
      auto it = functions.find (opc);
      func = it->second;	//function mapping for r type instruction
      if (opc == "sll")
	{
	  for (int i = 0; i < r3.length (); i++)
	    rd += r3[i];
	  return "00000" + rt + rs + bitset < 5 >
	    (stoi (r3)).to_string () + func;
	}
      else
	{
	  auto r3it = registers.find (r3);
	  rd = r3it->second;
	  return rt + rd + rs + "00000" + func;
	}
    }
  else if (instruction (mem1) == "i" && opc == "addi")
    {
      size_t c1 = inst.find (',');
      string r1 = inst.substr (inst.find ('$'), c1 - inst.find ('$'));	//extracting r1
      auto r1it = registers.find (r1);
      string rs = r1it->second;
      size_t c2 = inst.find (',', c1 + 1);
      r2 = inst.substr (c1 + 1, c2 - c1 - 1);
      auto r2it = registers.find (r2);	//extracting r2
      rt = r2it->second;
      r3 = inst.substr (c2 + 1);	//taking immmediate value as r3
      return rt + rs + bitset < 16 > (stoi (r3)).to_string ();
    }
  else if (opc == "lw" || opc == "sw")
    {
      size_t c1 = inst.find (',');
      string r1 = inst.substr (inst.find ('$'), c1 - inst.find ('$'));	//extracting r1
      auto r1it = registers.find (r1);
      string rs = r1it->second;
      size_t b1 = inst.find ('(');
      size_t b2 = inst.find (')');
      string i = inst.substr (c1 + 1, b1 - c1 - 1);
      r2 = inst.substr (b1 + 1, b2 - b1 - 1);
      auto r2it = registers.find (r2);
      rt = r2it->second;	//extracting r2
      return rt + rs + bitset < 16 > (stoi (i)).to_string ();
    }
  else if (opc == "bne" || opc == "beq")
    {
      size_t c1 = inst.find (',');
      string r1 = inst.substr (inst.find ('$'), c1 - inst.find ('$'));	//extracting r1
      auto r1it = registers.find (r1);
      string rs = r1it->second;
      size_t c2 = inst.find (',', c1 + 1);
      r2 = inst.substr (c1 + 1, c2 - c1 - 1);
      string i = inst.substr (c2 + 1);
      auto r2it = registers.find (r2);
      rt = r2it->second;	//extracting r2
      int z = (stoi (labels[i]) - stoi (mem1->label)) / 4;
      return rs + rt + bitset < 16 > (z - 1).to_string ();
    }
  else
    {
      string label = inst.substr (inst.find (' ') + 1);
      auto labit = labels.find (label);
      string lab = labit->second;
      string k = bitset < 32 > (stoi (lab)).to_string ();
      string labn = "";
      for (int i = 4; i < 30; i++)
	{
	  labn += k[i];
	}
      return labn;		//address of the instruction to jump to
    }
}

string
binary (struct Mem * mem1)
{
  //returns binary code for given assembly instruction
  return opcode (mem1) + getReg (mem1);
}

int
main ()
{
  vector < string > input;
  fstream inputFile;
  string line;
  int i = 0;
  inputFile.open ("mips.txt", std::ios::in);	//opening the instruction file and storing each line in a vector of strings
  struct Mem *sa = (struct Mem *) malloc (sizeof (struct Mem));
  while (getline (inputFile, line))
    {
      input.push_back (line);
      sa->instr = input[i];
      sa->label = text_add;
      i++;
      int j = (stoi (text_add) + 4);	//as mips is byte addressable, each instruction takes 4 mem locations, hence increasing label by 4
      text_add = (to_string (j));
      ofstream fout;
      int k = 0;
      fout.open ("output.txt", std::ios::app);	//output binary code to the file output.txt
      fout << binary (sa) << endl;
      fout.close ();
    }

}