#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl;

bool GetChecksum(std::string name, std::string checksum);
std::string Decrypt(std::string name, int k);

int main() {

  std::ifstream fin("day4.dat");

  std::string rname, rchecksum;
  int rID;

  int total = 0;

  while(fin >> rname >> rID >> rchecksum) {
    if(GetChecksum(rname,rchecksum))  {
      total = total + rID; // part 1

      cout << rname << " " << rID << " " << Decrypt(rname,rID) << endl;
    }
  }

  cout << "Total ID sum: " << total << endl;

  return 0;
}

std::string Decrypt(std::string name, int k) {
  std::string ans = "";
  int kmod = k % 26;

  for(int i = 0; i < name.size(); i++)
    ans.push_back(static_cast<char>((name[i] - 'a' + kmod) % 26 + 'a'));

  return ans;
}

bool GetChecksum(std::string name, std::string checksum) {
  std::string chk = "";

  int letters[26] = {0};

  for(int i = 0; i < name.size(); i++)
    letters[name[i]-'a']++;

  for(int i = 0; i < 5; i++) {
    int currmax = 0;
    for(int j = 0; j < 26; j++) {
      if(letters[j] > letters[currmax])
        currmax = j;
    }
    chk.push_back(static_cast<char>(currmax + 'a'));
    letters[currmax] = -1;
  }

  if(chk == checksum)
    return true;
  else
    return false;
}