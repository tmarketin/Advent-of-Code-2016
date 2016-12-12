#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;

void MapPrint(std::map<char,int> reg);

int main() {
  std::ifstream fin("day12.dat");

  std::string tmp;
  std::vector<std::string> inst;

  int pos1,pos2,val;
  std::string arg1,arg2;
  std::map<char,int> reg { {'a',0}, {'b',0}, {'c',0}, {'d',0} };

  for(std::string line; std::getline(fin,line);)
    inst.push_back(line);

  int curr_inst = 0;
  while(curr_inst < inst.size()) {
    tmp = inst[curr_inst].substr(0,3);
    pos1 = 3;
    if(tmp == "cpy") {
      pos2 = inst[curr_inst].size() - 2;
      arg1 = inst[curr_inst].substr(pos1 + 1,pos2 - pos1 - 1);
      arg2 = inst[curr_inst].substr(pos2 + 1);
      if(arg1 == "a" || arg1 == "b" || arg1 == "c" || arg1 == "d")
        reg[arg2[0]] = reg[arg1[0]];
      else
        reg[arg2[0]] = std::stoi(arg1);
    }
    else if(tmp == "inc") {
      reg[inst[curr_inst][4]]++;
    } 
    else if(tmp == "dec") {
      reg[inst[curr_inst][4]]--;
    }
    else if(tmp == "jnz") {
      pos2 = 5;
      arg1 = inst[curr_inst][4];
      arg2 = inst[curr_inst].substr(6);
      if(inst[curr_inst][4] == '1')
        val = 1;
      else
        val = reg[inst[curr_inst][4]];

      if(val != 0)
        curr_inst = curr_inst + std::stoi(arg2) - 1;
    }
    curr_inst++;
  }

  MapPrint(reg);

  return 0;
}

void MapPrint(std::map<char,int> reg) {
  cout << "a: " << reg['a'] << endl;
  cout << "b: " << reg['b'] << endl;
  cout << "c: " << reg['c'] << endl;
  cout << "d: " << reg['d'] << endl;

  return;
}