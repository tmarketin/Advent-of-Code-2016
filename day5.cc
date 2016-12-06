#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <openssl/md5.h>

using std::cout;
using std::endl;

int main() {
  unsigned char digest[MD5_DIGEST_LENGTH];

  std::string name = "cxdnnyjw";
  std::string number = "0";
  std::string code_part1 = "";
  std::string code_part2 = "________";

  char fullname[30];
  char mdString[33];

  int count = 0;
  int count_p2 = 0;
  while(code_part1.size() < 8 || count_p2 < 8) {
    number = std::to_string(count);
    strncpy(fullname,(name+number).c_str(),sizeof(fullname));

    MD5((unsigned char*)&fullname, strlen(fullname), (unsigned char*)&digest);   

    for(int i = 0; i < 16; i++)
      sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

    if(strncmp(mdString,"00000",5) == 0 && code_part1.size() < 8) {
      code_part1.push_back(mdString[5]);
//      cout << count << " " << fullname << " " << mdString << endl;
    }

    if(strncmp(mdString,"00000",5) == 0 && count_p2 < 8) {
      if(mdString[5] >= '0' && mdString[5] <= '7' && code_part2[mdString[5] - '0'] == '_') {
        code_part2[mdString[5] - '0'] = mdString[6];
        cout << count << " " << mdString << " " << code_part2 << endl;
        count_p2++;
      }
    }

    count++;
  }

  cout << "Part 1 code: " << code_part1 << endl;
  cout << "Part 2 code: " << code_part2 << endl;

  return 0;
}