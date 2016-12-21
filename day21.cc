#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using std::cout;
using std::endl;

std::string Swap(std::string str, int a, int b);
std::string RotateLeft(std::string str, int k);
std::string RotateRight(std::string str, int k);
std::string Move(std::string str, int a, int b);
std::string Scramble(std::string str, std::string fname);

int main() {
  std::string pass = "abcdefgh";
  std::string cmd,cmd2,tmp;

  cout << "Part 1 solution: " << Scramble("abcdefgh","day21.dat") << endl;

  do {
    if(Scramble(pass,"day21.dat") == "fbgdceah") {
      cout << "Part 2 solution: " << pass << endl;
      break;
    }
  } while(std::next_permutation(pass.begin(),pass.end()));

  return 0;
}

std::string Scramble(std::string str, std::string fname) {
  std::ifstream fin(fname);

  std::string pass(str);
  std::string cmd, cmd2, tmp;

  char c1,c2;
  int pos1,pos2;

  while(fin >> cmd) {
    if(cmd == "swap") {
      fin >> cmd2;
      if(cmd2 == "position") {
        fin >> pos1 >> pos2;
      }
      else {
        fin >> c1 >> c2;
        pos1 = pass.find_first_of(c1);
        pos2 = pass.find_first_of(c2);
      }
      pass = Swap(pass,pos1,pos2);
    }

    if(cmd == "reverse") {
      fin >> pos1 >> pos2;
      tmp = pass.substr(pos1,pos2 - pos1 + 1);
      std::reverse(tmp.begin(),tmp.end());
      pass = pass.substr(0,pos1) + tmp + pass.substr(pos2+1);
    }

    if(cmd == "move") {
      fin >> pos1 >> pos2;
      pass = Move(pass,pos1,pos2);
    }

    if(cmd == "rotate") {
      fin >> cmd2;
      if(cmd2 == "left") {
        fin >> pos1;
        pass = RotateLeft(pass,pos1 % pass.size());
      }
      else if(cmd2 == "right" ) {
        fin >> pos1;
          pass = RotateRight(pass,pass.size() - (pos1 % pass.size()));
      }
      else if(cmd2 == "position") {
        fin >> c1;
        pos1 = pass.find_first_of(c1);
        pass = RotateRight(pass,pass.size() - ((1 + pos1 + (pos1 >= 4)) % pass.size()));
      }
    }
  }  

  return pass;
}

std::string Move(std::string str, int a, int b) {
  char c = str[a];

  str.erase(str.begin() + a);
  if(b > str.size())
    str.push_back(c);
  else {
    str = str.substr(0,b) + c + str.substr(b);
  }

  return str;
}

std::string RotateLeft(std::string str, int k) {
  return str.substr(k) + str.substr(0,k);
}

std::string RotateRight(std::string str, int k) {
  return str.substr(k) + str.substr(0,k);
}

std::string Swap(std::string str, int a, int b) {
  char c1;

  c1 = str[a]; 
  str[a] = str[b]; 
  str[b] = c1;

  return str;
}
