#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <openssl/md5.h>

#define REPEAT 2016

using std::cout;
using std::endl;

int main() {
  unsigned char digest[MD5_DIGEST_LENGTH];

  std::string name = "zpqevtbw";
  std::string testcase = "";

  std::vector<int> hash_counts;
  std::vector<int> hash_matches;
  std::vector<std::string> hashes;

  char fullname[30];
  char mdString[33];

  int count = 0;
  int count_p1 = 0;
  int count_p2 = 0;
  bool found = false;
  while(count_p1 < 64) {
    if(count > static_cast<int>(hashes.size()) - 1) { // if hash not in vector, generate and push in
      strncpy(fullname,(name + std::to_string(count)).c_str(),sizeof(fullname));

      MD5((unsigned char*)&fullname, strlen(fullname), (unsigned char*)&digest);   

      for(int i = 0; i < 16; i++)
        sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);

      for(int i = 0; i < REPEAT; i++) {
        MD5((unsigned char*)&mdString, strlen(mdString), (unsigned char*)&digest);   

        for(int j = 0; j < 16; j++)
          sprintf(&mdString[j*2], "%02x", (unsigned int)digest[j]);        
      }
      hashes.push_back(std::string(mdString));
    }

    for(int i = 0; i < hashes[count].size() - 2; i++)
      if(hashes[count][i] == hashes[count][i+1] && hashes[count][i] == hashes[count][i+2]) {
        testcase = std::string() + hashes[count][i] + hashes[count][i] + hashes[count][i] + hashes[count][i] + hashes[count][i];
        found = true;
        break;
      }

    if(found) {
      for(int j = count + 1; j <= count + 1000; j++) {
        int vsize = static_cast<int>(hashes.size());
        if(j > vsize - 1) {
          strncpy(fullname,(name + std::to_string(j)).c_str(),sizeof(fullname));

          MD5((unsigned char*)&fullname,strlen(fullname),(unsigned char*)&digest);

          for(int k = 0; k < 16; k++)
            sprintf(&mdString[k*2], "%02x", (unsigned int)digest[k]);

          for(int i = 0; i < REPEAT; i++) {
            MD5((unsigned char*)&mdString, strlen(mdString), (unsigned char*)&digest);   

            for(int l = 0; l < 16; l++)
              sprintf(&mdString[l*2], "%02x", (unsigned int)digest[l]);        
          }
          hashes.push_back(std::string(mdString));
        }

        if(hashes[j].find(testcase) != std::string::npos) {
          count_p1++;
          hash_counts.push_back(count);
          hash_matches.push_back(j);
          found = false;
          break;
        }
      }
      found = false;
    }

    count++;
  }

  cout << "Hash count: " << hash_counts.back() << endl << endl;
  for(int i = 0; i < hash_counts.size(); i++)
    cout << i << " " << hash_counts[i] << " " << hashes[hash_counts[i]] << " " << hash_matches[i] << endl;

  return 0;
}