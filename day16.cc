#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>

using std::cout;
using std::endl;

std::string GetChecksum(std::string res);

int main() {
  std::string input("01111001100111011");
//  int len = 272; // part 1
  int len = 35651584; // part 2

  std::string tmp,rev,res;

  res = input;
  while(res.size() < len) {
    rev = res;
    std::reverse(rev.begin(),rev.end());

    for(int i = 0; i < rev.size(); i++)
      if(rev[i] == '0')
        rev[i] = '1';
      else 
        rev[i] = '0';

    res = res + "0" + rev;
  }
  res = res.substr(0,len);
  cout << GetChecksum(res) << endl;

  return 0;
}

std::string GetChecksum(std::string res) {
  std::string tmp(res);
  std::string chk(res);
  int chksize = chk.size();

  while(tmp.size() % 2 == 0) {
    chksize = chksize/2;
    for(int i = 0; i < tmp.size(); i = i + 2)
      if(tmp[i] == tmp[i+1])
        chk[i/2] = '1';
      else
        chk[i/2] = '0';

    tmp = chk.substr(0,chksize);
  }

  return tmp;
}