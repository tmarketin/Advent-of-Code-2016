#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

bool CheckSSL(std::vector<std::string> supernet, std::vector<std::string> hypernet);
bool HasABBA(std::vector<std::string> net);

int main() {
  std::ifstream fin("day7.dat");

  std::string tmp;
  std::vector<std::string> valid_TLS;
  std::vector<std::string> valid_SSL;

  std::vector<std::string> supernet,hypernet;

  while(fin >> tmp) {
    supernet.clear();
    hypernet.clear();

    while(tmp.find_first_of('[') != std::string::npos) {
      supernet.push_back(tmp.substr(0,tmp.find_first_of('[')));
      hypernet.push_back(tmp.substr(tmp.find_first_of('[') + 1,tmp.find_first_of(']') - tmp.find_first_of('[') - 1));
      tmp.erase(0,tmp.find_first_of(']') + 1);
    }
    if(tmp.size() > 0)
      supernet.push_back(tmp);

    if(! HasABBA(hypernet) && HasABBA(supernet))
      valid_TLS.push_back(tmp);

    if(CheckSSL(supernet,hypernet))
      valid_SSL.push_back(tmp);
  }

  cout << "Number of TLS enabled addresses: " << valid_TLS.size() << endl;
  cout << "Number of SSL enabled addresses: " << valid_SSL.size() << endl;

  return 0;
}

bool CheckSSL(std::vector<std::string> supernet, std::vector<std::string> hypernet) {
  std::string chk;

  for(int i = 0; i < supernet.size(); i++) {
    for(int j = 0; j < supernet[i].size() - 2; j++)
      if(supernet[i][j] != supernet[i][j+1] && supernet[i][j] == supernet[i][j+2]) {
        chk = std::string() + supernet[i][j+1] + supernet[i][j] + supernet[i][j+1];
        for(int k = 0; k < hypernet.size(); k++)
          if(hypernet[k].find(chk) != std::string::npos)
            return true;
        chk.clear();
      }
  }

  return false;
}

bool HasABBA(std::vector<std::string> net) {
  for(int i = 0; i < net.size(); i++) {
    for(int j = 0; j < net[i].size() - 3; j++) {
      if(net[i][j] != net[i][j+1] && net[i][j] == net[i][j+3] && net[i][j+1] == net[i][j+2])
        return true;
    }
  }

  return false;
}
