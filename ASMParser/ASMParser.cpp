#include "ASMParser.h"
#include<iostream>

ASMParser::ASMParser(string filename)
  // Specify a text file containing MIPS assembly instructions. Function
  // checks syntactic correctness of file and creates a list of Instructions.
{
  Instruction i;
  myFormatCorrect = true;

  myLabelAddress = 0x400000;

  ifstream in;
  in.open(filename.c_str());
  if(in.bad()){
    myFormatCorrect = false;
  }
  else{
    string line;
    while( getline(in, line)){
      string opcode("");
      string operand[80];
      int operand_count = 0;

      getTokens(line, opcode, operand, operand_count);

      if(opcode.length() == 0 && operand_count != 0){
        // No opcode but operands
        myFormatCorrect = false;
        break;
      }

      Opcode o = opcodes.getOpcode(opcode);      
      if(o == UNDEFINED){
        // invalid opcode specified
        myFormatCorrect = false;
        break;
      }

      bool success = getOperands(i, o, operand, operand_count);
      if(!success){
        myFormatCorrect = false;
        break;
      }

      string encoding = encode(i);
      i.setEncoding(encoding);

      myInstructions.push_back(i);

    }
  }

  myIndex = 0;
}


Instruction ASMParser::getNextInstruction()
  // Iterator that returns the next Instruction in the list of Instructions.
{
  if(myIndex < (int)(myInstructions.size())){
    myIndex++;
    return myInstructions[myIndex-1];
  }

  Instruction i;
  return i;

}

void ASMParser::getTokens(string line,
    string &opcode,
    string *operand,
    int &numOperands)
  // Decomposes a line of assembly code into strings for the opcode field and operands, 
  // checking for syntax errors and counting the number of operands.
{
  // locate the start of a comment
  string::size_type idx = line.find('#');
  if (idx != string::npos) // found a ';'
    line = line.substr(0,idx);
  int len = line.length();
  opcode = "";
  numOperands = 0;

  if (len == 0) return;
  int p = 0; // position in line

  // line.at(p) is whitespace or p >= len
  while (p < len && isWhitespace(line.at(p)))
    p++;
  // opcode starts
  while (p < len && !isWhitespace(line.at(p)))
  {
    opcode = opcode + line.at(p);
    p++;
  }
  //    for(int i = 0; i < 3; i++){
  int i = 0;
  while(p < len){ 
    while ( p < len && isWhitespace(line.at(p)))
      p++;

    // operand may start
    bool flag = false;
    while (p < len && !isWhitespace(line.at(p)))
    {
      if(line.at(p) != ','){
        operand[i] = operand[i] + line.at(p);
        flag = true;
        p++;
      }
      else{
        p++;
        break;
      }
    }
    if(flag == true){
      numOperands++;
    }
    i++;
  }


  idx = operand[numOperands-1].find('(');
  string::size_type idx2 = operand[numOperands-1].find(')');

  if (idx == string::npos || idx2 == string::npos ||
      ((idx2 - idx) < 2 )){ // no () found
  }
  else{ // split string
    string offset = operand[numOperands-1].substr(0,idx);
    string regStr = operand[numOperands-1].substr(idx+1, idx2-idx-1);//TODO

    operand[numOperands-1] = offset;
    operand[numOperands] = regStr;
    numOperands++;
  }



  // ignore anything after the whitespace after the operand
  // We could do a further look and generate an error message
  // but we'll save that for later.
  return;
}

bool ASMParser::isNumberString(string s)
  // Returns true if s represents a valid decimal integer
{
  int len = s.length();
  if (len == 0) return false;
  if ((isSign(s.at(0)) && len > 1) || isDigit(s.at(0)))
  {
    // check remaining characters
    for (int i=1; i < len; i++)
    {
      if (!isdigit(s.at(i))) return false;
    }
    return true;
  }
  return false;
}


int ASMParser::cvtNumString2Number(string s)
  // Converts a string to an integer.  Assumes s is something like "-231" and produces -231
{
  if (!isNumberString(s))
  {
    cerr << "Non-numberic string passed to cvtNumString2Number"
      << endl;
    return 0;
  }
  int k = 1;
  int val = 0;
  for (int i = s.length()-1; i>0; i--)
  {
    char c = s.at(i);
    val = val + k*((int)(c - '0'));
    k = k*10;
  }
  if (isSign(s.at(0)))
  {
    if (s.at(0) == '-') val = -1*val;
  }
  else
  {
    val = val + k*((int)(s.at(0) - '0'));
  }
  return val;
}


bool ASMParser::getOperands(Instruction &i, Opcode o, 
    string *operand, int operand_count)
  // Given an Opcode, a string representing the operands, and the number of operands, 
  // breaks operands apart and stores fields into Instruction.
{

  if(operand_count != opcodes.numOperands(o))
    return false;

  int rs, rt, rd, imm;
  imm = 0;
  rs = rt = rd = NumRegisters;

  int rs_p = opcodes.RSposition(o);
  int rt_p = opcodes.RTposition(o);
  int rd_p = opcodes.RDposition(o);
  int imm_p = opcodes.IMMposition(o);

  if(rs_p != -1){
    rs = registers.getNum(operand[rs_p]);
    if(rs == NumRegisters)
      return false;
  }

  if(rt_p != -1){
    rt = registers.getNum(operand[rt_p]);
    if(rt == NumRegisters)
      return false;

  }

  if(rd_p != -1){
    rd = registers.getNum(operand[rd_p]);
    if(rd == NumRegisters)
      return false;

  }

  if(imm_p != -1){
    if(isNumberString(operand[imm_p])){  // does it have a numeric immediate field?
      imm = cvtNumString2Number(operand[imm_p]);
      if(((abs(imm) & 0xFFFF0000)<<1))  // too big a number to fit
        return false;
    }
    else{ 
      if(opcodes.isIMMLabel(o)){  // Can the operand be a label?
        // Assign the immediate field an address
        imm = myLabelAddress;
        myLabelAddress += 4;  // increment the label generator
      }
      else  // There is an error
        return false;
    }

  }

  i.setValues(o, rs, rt, rd, imm);

  return true;
}


string ASMParser::encode(Instruction i)
  // Given a valid instruction, returns a string representing the 32 bit MIPS binary encoding
  // of that instruction.
{
  ofstream outfile;
  outfile.open("outfile.mach");
  string tmp;

  if(opcodes.getInstType(i.getOpcode()) == ITYPE) {
    tmp = encodeI(i);
  }
  else if(opcodes.getInstType(i.getOpcode()) == JTYPE) {
    tmp = encodeJ(i);
  }
  else {
    tmp = encodeR(i);
  }

  outfile << tmp << endl;

  return tmp;
}

string ASMParser::encodeR(Instruction i) {
  string value = "";
  Opcode tmp = i.getOpcode();
  value += opcodes.getOpcodeField(tmp);
  cout << "RType" << endl;
  value += toBinary(i.getRS(), 5);
  value += toBinary(i.getRT(), 5);
  value += toBinary(i.getRD(), 5);
  value += toBinary(i.getImmediate(), 5);
  value += opcodes.getFunctField(tmp);
  
  return value;
}

string ASMParser::encodeI(Instruction i) {
  string value = "";
  Opcode tmp = i.getOpcode();
  value += opcodes.getOpcodeField(tmp);
  cout << "IType" << endl;
  value += toBinary(i.getRT(), 5);
  value += toBinary(i.getRS(), 5);
  value += toBinary(i.getImmediate(), 16);
  return value;
}

string ASMParser::encodeJ(Instruction i) {
  string value = "";
  Opcode tmp = i.getOpcode();
  cout << "JType" << endl;
  value += opcodes.getOpcodeField(tmp);
  value += "00";
  value += toBinary(i.getImmediate(), 26).substr(0, 24);
  return value;
}

string ASMParser::toBinary(int i, int size) {
  if(i == 32) {i = 0;}
  cout << i << " : ";
  string binary = "";
  int divisor = 2;
  for(int j = 1; j < size-1; j++) {
    divisor *= 2;
  }
  while(divisor >= 1) {
    if((i/divisor) >= 1) {
      binary += "1";
      i -= divisor;
    }
    else {
      binary += "0";
    }
    divisor /= 2;
  }
  cout << binary << endl;
  return binary;
}


