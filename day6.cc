#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using std::cout;
using std::endl;

int main() {
  std::string tmp;
  std::vector<std::string> data;
  std::vector<int> chartable(26);
  std::string code_part1 = "";
  std::string code_part2 = "";

  int maxval,minval;

  std::ifstream fin("day6.dat");

  while(fin >> tmp)
    data.push_back(tmp);

  for(int letter = 0; letter < data[0].size(); letter++) {
    for(int ch = 0; ch < 26; ch++)
      chartable[ch] = 0;

    for(int i = 0; i < data.size(); i++)
      chartable[data[i][letter] - 'a']++;

    maxval = 0; 
    minval = 0;
    for(int i = 0; i < chartable.size(); i++) {
      if(chartable[i] > chartable[maxval]) // part 1
        maxval = i;

      if(chartable[i] > 0 && (chartable[minval] == 0 || chartable[i] < chartable[minval])) // part 2
        minval = i;
    }

    code_part1.push_back(static_cast<char>(maxval + 'a'));
    code_part2.push_back(static_cast<char>(minval + 'a'));
  }

  cout << "Code (part 1) is: " << code_part1 << endl;
  cout << "Code (part 2) is: " << code_part2 << endl;

  return 0;
}