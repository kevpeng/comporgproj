/* 
 * Parses mips instruction file into binary encoding. Supports add, addi, sub, 
 * slt,lw, sw,beq,and j instructions.Assumes format is correct. Stores all 
 * instructions in map data structure and assign correct address (starts with 
 * 0x00400000 and increment by 4)
 * 
 * Author: Tiancahng Yang
 * Date: 11/30/17
 */
#include "InstructionParser.h"

InstructionParser::InstructionParser(string file){
  myAddress = "00400000";
  ifstream in;
  in.open(file.c_str());
  if (in.bad()) {

  } else {
    string line;
    while(getline(in, line)) {
      if (!isEmpty(line) && !isComment(line)) {
        unsigned int i = 0;
        while (i < line.length() && isWhitespace(line.at(i))) {
          i++;
        }
        line = line.substr(i, line.length()); //taking care of the leading whitespaces
        //cout << line << endl;
        myOriginal[myAddress] = line;

        i = 0;
        while (i < line.length() && !isWhitespace(line.at(i))) {
          i++;
        }
        string operation = line.substr(0, i);
        //cout << operation << endl;

        line.erase(std::remove(line.begin(), line.end(), ','), line.end());
        //cout<<line<<endl;

        if (operation == "ADD" || operation == "add") {
          isADD(line);
          increment();
        }
        if (operation == "SUB" || operation == "sub") {
          isSUB(line);
          increment();
        }
        if (operation == "ADDI" || operation == "addi") {
          isADDI(line);
          increment();
        }
        if (operation == "SLT" || operation == "slt") {
          isSLT(line);
          increment();
        }
        if (operation == "LW" || operation == "lw") {
          isLW(line);
          increment();
        }
        if (operation == "SW" || operation == "sw") {
          isSW(line);
          increment();
        }
        if (operation == "BEQ" || operation == "beq") {
          isBEQ(line);
          increment();
        }
        if (operation == "J" || operation == "j") {
          isJ(line);
          increment();
        }
      }
    }
  }
}

void InstructionParser::isADD(string line){
  //cout << "ADD" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rdStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rd = stoi(rdStr);
  //cout<<rd<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rsStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rs = stoi(rsStr);
  //cout<<rs<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;

  rdStr = bitset<5>(rd).to_string();
  rsStr = bitset<5>(rs).to_string();
  rtStr = bitset<5>(rt).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "000000";
  encoding += rsStr;
  encoding += rtStr;
  encoding += rdStr;
  encoding += "00000100000";

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}


void InstructionParser::isSUB(string line){
  //cout << "SUB" << endl;
  //cout << "ADD" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rdStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rd = stoi(rdStr);
  //cout<<rd<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rsStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rs = stoi(rsStr);
  //cout<<rs<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;

  rdStr = bitset<5>(rd).to_string();
  rsStr = bitset<5>(rs).to_string();
  rtStr = bitset<5>(rt).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "000000";
  encoding += rsStr;
  encoding += rtStr;
  encoding += rdStr;
  encoding += "00000100010";

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}


void InstructionParser::isADDI(string line){
  //cout << "ADDI" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  //line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != ' ') {
    i++;
  }
  string rsStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rs = stoi(rsStr);
  //cout<<rs<<endl;
  //cout << line <<endl;
  //cout << i << endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  //cout << i <<endl;
  string immStr = line.substr(1,i);
  //cout<<immStr<<endl;
  int imm = stoi(immStr);
  //cout<<imm<<endl;

  rtStr = bitset<5>(rt).to_string();
  rsStr = bitset<5>(rs).to_string();
  immStr = bitset<16>(imm).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "001000";
  encoding += rsStr;
  encoding += rtStr;
  encoding += immStr;

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}


void InstructionParser::isSLT(string line){
  //cout << "SLT" << endl;
  //cout << "ADD" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rdStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rd = stoi(rdStr);
  //cout<<rd<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rsStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rs = stoi(rsStr);
  //cout<<rs<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;

  rdStr = bitset<5>(rd).to_string();
  rsStr = bitset<5>(rs).to_string();
  rtStr = bitset<5>(rt).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "000000";
  encoding += rsStr;
  encoding += rtStr;
  encoding += rdStr;
  encoding += "00000101010";

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}


void InstructionParser::isLW(string line){
  //cout << "LW" << endl;

  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  //line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != ' ') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '(') {
    i++;
  }
  string immStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int imm = stoi(immStr);
  //cout<<imm<<endl;
  //cout << line <<endl;
  //cout << i << endl;


  line = line.substr(i+1, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != ')') {
    i++;
  }
  //cout << i <<endl;
  string rsStr = line.substr(1,i);
  //cout<<immStr<<endl;
  int rs = stoi(rsStr);
  //cout<<imm<<endl;

  rtStr = bitset<5>(rt).to_string();
  rsStr = bitset<5>(rs).to_string();
  immStr = bitset<16>(imm).to_string();

  string encoding = "100011";
  encoding += rsStr;
  encoding += rtStr;
  encoding += immStr;

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}

void InstructionParser::isSW(string line){
  //cout << "SW" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());

  i = 1;
  while (i < line.length() && line.at(i) != ' ') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '(') {
    i++;
  }
  string immStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int imm = stoi(immStr);
  //cout<<imm<<endl;
  //cout << line <<endl;
  //cout << i << endl;


  line = line.substr(i+1, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != ')') {
    i++;
  }
  string rsStr = line.substr(1,i);
  int rs = stoi(rsStr);

  rtStr = bitset<5>(rt).to_string();
  rsStr = bitset<5>(rs).to_string();
  immStr = bitset<16>(imm).to_string();

  string encoding = "101011";
  encoding += rsStr;
  encoding += rtStr;
  encoding += immStr;

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}

void InstructionParser::isBEQ(string line){
  //cout << "BEQ" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  //line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  string rtStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rt = stoi(rtStr);
  //cout<<rt<<endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != ' ') {
    i++;
  }
  string rsStr = line.substr(1,i);
  //cout<<rdStr<<endl;
  int rs = stoi(rsStr);
  //cout<<rs<<endl;
  //cout << line <<endl;
  //cout << i << endl;


  line = line.substr(i, line.length());
  //cout<<line<<endl;
  i = 1;
  while (i < line.length() && line.at(i) != '$') {
    i++;
  }
  //cout << i <<endl;
  string immStr = line.substr(1,i);
  //cout<<immStr<<endl;
  int imm = stoi(immStr,nullptr,16);

  //cout<<imm<<endl;

  rtStr = bitset<5>(rt).to_string();
  rsStr = bitset<5>(rs).to_string();
  immStr = bitset<16>(imm).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "000100";
  encoding += rsStr;
  encoding += rtStr;
  encoding += immStr;

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}

void InstructionParser::isJ(string line){
  //cout << "J" << endl;
  unsigned int i = 0;
  while (i < line.length() && !isWhitespace(line.at(i))) {
    i++;
  }
  while (i < line.length() && isWhitespace(line.at(i))) {
    i++;
  }
  line = line.substr(i, line.length());
  //cout<<line<<endl;

  //line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  //line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());


  i = 1;
  while (i < line.length()) {
    i++;
  }
  string immStr = line.substr(0,i);
  //cout << immStr<<endl;
  int imm = stoi(immStr,nullptr,16);
  immStr = bitset<26>(imm).to_string();

  //cout<<rdStr<<endl;
  //cout<<rsStr<<endl;
  //cout<<rtStr<<endl;

  string encoding = "000010";
  encoding += immStr;

  //cout <<encoding <<endl;

  myInstruction[myAddress] = encoding;
}

void InstructionParser::increment(){
  //cout << myAddress << endl;
  string bin = hex2Bin(myAddress);
  //cout << bin << endl;
  bin = add(bin, "00000000000000000000000000000100");
  //cout << bin << endl;
  myAddress = bin2Hex(bin);
  //cout << myAddress << endl;
}

// Helper mathod to determine if a string contains only whitespaces
bool InstructionParser::isEmpty(string s) {
  bool result = true;
  char c;
  for(unsigned int i = 0; i < s.length(); i++) {
    c = s[i]; 
    if (!isspace(c)) {
      result = false;
    }
  }
  return result;
}

// Helper method to determine if a string is a comment 
// (ignnoring whitespaces, starts with a "#")
bool InstructionParser::isComment(string s) {
  char c;
  for(unsigned int i = 0; i < s.length(); i++) {
    c = s[i]; 
    if (!isspace(c)) {
      if (c == '#') {
        return true;
      } else {
        return false;
      }
    }
  }
  return false;
}

string InstructionParser::hex2Bin(string s) {
  string result;
  for (unsigned int i = 0; i < s.length(); i++) {
    char c = s[i];
    if (c == '0')  result += "0000";
    if (c == '1')  result += "0001";
    if (c == '2')  result += "0010";
    if (c == '3')  result += "0011";
    if (c == '4')  result += "0100";
    if (c == '5')  result += "0101";
    if (c == '6')  result += "0110";
    if (c == '7')  result += "0111";
    if (c == '8')  result += "1000";
    if (c == '9')  result += "1001";
    if (c == 'A')  result += "1010";
    if (c == 'B')  result += "1011";
    if (c == 'C')  result += "1100";
    if (c == 'D')  result += "1101";
    if (c == 'E')  result += "1110";
    if (c == 'F')  result += "1111";
  }
  return result;
}

char InstructionParser::getHexCharacter(string str)
{
  if(str.compare("1111") == 0) return 'F';
  else if(str.compare("1110") == 0) return 'E';
  else if(str.compare("1101")== 0) return 'D';
  else if(str.compare("1100")== 0) return 'C';
  else if(str.compare("1011")== 0) return 'B';
  else if(str.compare("1010")== 0) return 'A';
  else if(str.compare("1001")== 0) return '9';
  else if(str.compare("1000")== 0) return '8';
  else if(str.compare("0111")== 0) return '7';
  else if(str.compare("0110")== 0) return '6';
  else if(str.compare("0101")== 0) return '5';
  else if(str.compare("0100")== 0) return '4';
  else if(str.compare("0011")== 0) return '3';
  else if(str.compare("0010")== 0) return '2';
  else if(str.compare("0001")== 0) return '1';
  else if(str.compare("0000")== 0) return '0';
  return ' ';
}

string InstructionParser::bin2Hex(string s)
{
  string endresult = "";
  for(unsigned int i = 0; i < s.length(); i = i+4)
  {
    endresult += getHexCharacter(s.substr(i,4));
  }
  return endresult;
}

string InstructionParser::add(string operand1, string operand2) {
  //cout << "operand1\t" << operand1 << "\tlength:\t"<< operand1.length () << endl;
  //cout << "operand2\t" << operand2 << "\tlength:\t"<< operand2.length () << endl;
  char carry = '0'; //carry bit
  string result = "00000000000000000000000000000000";
  for (int i = 31; i > -1; i--) {
    //cout << i << carry << myOperand1[i] << myOperand2[i] << endl;
    if (operand1[i] == '0' && operand2[i] == '0' && carry == '0') {
      //ignore overflow

      //cout << i << "\tcarry = 0 result = 0" << endl;
      result[i] = '0';
      carry = '0';
    } else if ((operand1[i] == '0' && operand2[i] == '0' && carry == '1')
        || (operand1[i] == '0' && operand2[i] == '1' && carry == '0')
        || (operand1[i] == '1' && operand2[i] == '0' && carry == '0')) {
      //cout << i << "\tcarry = 0 result = 1" << endl;
      result[i] = '1';
      carry = '0';
    } else if ((operand1[i] == '1' && operand2[i] == '1' && carry == '0')
        || (operand1[i] == '1' && operand2[i] == '0' && carry == '1')
        || (operand1[i] == '0' && operand2[i] == '1' && carry == '1')) {
      //cout << i << "\tcarry = 1 result = 0" << endl;
      result[i] = '0';
      carry = '1';
    } else if (operand1[i] == '1' && operand2[i] == '1' && carry == '1') {
      //cout << i << "\tcarry = 1 result = 1" << endl;
      result[i] = '1';
      carry = '1';
    }
  }
  //cout << "result\t\t" << result << endl;
  return result;
}
