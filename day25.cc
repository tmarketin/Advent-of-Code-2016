#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;

void MapPrint(std::map<char,int> reg);
std::vector<int> Evaluate(std::map<char,int> reg, std::vector<std::string> inst);

int main() {
  std::ifstream fin("day25.dat");

  std::string tmp;
  std::vector<std::string> inst;
  std::vector<int> out;

  std::map<char,int> reg { {'a',0}, {'b',0}, {'c',0}, {'d',0} };

  for(std::string line; std::getline(fin,line);)
    inst.push_back(line);

  for(int i = 0; i < 200; i++) {
    reg['a'] = i;
    out = Evaluate(reg,inst);
    if(out[0] == 0 && out[1] == 1 && out[2] == 0 && out[3] == 1) {
      cout << "register: " << i << endl;
      for(auto a: out)
        cout << a << " ";
      cout << endl;
    }
  }

  MapPrint(reg);

  return 0;
}

std::vector<int> Evaluate(std::map<char,int> reg, std::vector<std::string> inst) {
  std::vector<int> output;
  int pos1,pos2,val;
  std::string tmp,arg1,arg2;

  int curr_inst = 0;
  while(curr_inst < inst.size()) {
//    cout << curr_inst << " " << inst[curr_inst] << "   ";
//    MapPrint(reg);

    tmp = inst[curr_inst].substr(0,3);
    pos1 = 3;
    if(tmp == "cpy") {
      pos2 = inst[curr_inst].size() - 2;
      arg1 = inst[curr_inst].substr(pos1 + 1,pos2 - pos1 - 1);
      arg2 = inst[curr_inst].substr(pos2 + 1);
      if(arg2 != "a" && arg2 != "b" && arg2 != "c" && arg2 != "d") {
        curr_inst++;
        continue;
      }

      if(arg1 == "a" || arg1 == "b" || arg1 == "c" || arg1 == "d")
        reg[arg2[0]] = reg[arg1[0]];
      else
        reg[arg2[0]] = std::stoi(arg1);
    }
    else if(tmp == "tgl") {
      pos1 = reg[inst[curr_inst][4]];
      if(curr_inst + pos1 < 0 || curr_inst + pos1 >= inst.size()) {
        curr_inst++;
        continue;
      }

      tmp = inst[curr_inst + pos1].substr(0,3);
      if(tmp == "inc")
        inst[curr_inst + pos1].replace(0,3,"dec");
      else if(tmp == "dec" || tmp == "tgl")
        inst[curr_inst + pos1].replace(0,3,"inc");
      else if(tmp == "jnz")
        inst[curr_inst + pos1].replace(0,3,"cpy");
      else if(tmp == "cpy")
        inst[curr_inst + pos1].replace(0,3,"jnz");
    }
    else if(tmp == "inc") {
      reg[inst[curr_inst][4]]++;
    } 
    else if(tmp == "dec") {
      reg[inst[curr_inst][4]]--;
    }
    else if(tmp == "jnz") {
      pos2 = 5;
      arg1 = inst[curr_inst].substr(pos1 + 1,pos2 - pos1 - 1);
      arg2 = inst[curr_inst].substr(pos2 + 1);
      if(arg1[arg1.size() - 1] >= 'a' && arg1[arg1.size() - 1] <= 'd')
        pos1 = reg[arg1[0]];
      else
        pos1 = std::stoi(arg1);

      if(arg2[arg2.size() - 1] >= 'a' && arg2[arg2.size() - 1] <= 'd')
        pos2 = reg[arg2[0]];
      else
        pos2 = std::stoi(arg2);

      if(pos1 != 0)
        curr_inst = curr_inst + pos2 - 1;
    }
    else if(tmp == "out") {
      output.push_back(reg['b']);
      if(output.size() > 10)
        return output;
    }
    curr_inst++;
  }

  return output;
}


void MapPrint(std::map<char,int> reg) {
  cout << "a: " << reg['a'] << " ";
  cout << "b: " << reg['b'] << " ";
  cout << "c: " << reg['c'] << " ";
  cout << "d: " << reg['d'] << endl;

  return;
}