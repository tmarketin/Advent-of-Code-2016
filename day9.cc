#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

std::string StringDecompress(std::string str);
unsigned long int StringDecompress_v2(std::string str);

int main() {
  int counter = 0;

  std::ifstream fin("day9.dat");

  std::string input, output;

  fin >> input;

  output = StringDecompress(input);

  cout << "Total length is: " << output.size() << endl;
  cout << "Total length (part 2) is: " << StringDecompress_v2(input) << endl;

  return 0;
}

unsigned long int StringDecompress_v2(std::string str) {
  std::string tmp;
  unsigned long int count = 0;
  int lpos,xpos,rpos;
  unsigned int no_char,no_repeat;

  while(str.find_first_of("(") != std::string::npos) {
    lpos = str.find_first_of("(");

    if(lpos > 0) {
      count = count + lpos;

      str.erase(0,lpos);
      lpos = 0;
    }
    xpos = str.find_first_of("x");
    rpos = str.find_first_of(")");

    no_char = stoul(str.substr(lpos + 1,xpos - lpos - 1));
    tmp = StringDecompress(str.substr(0,rpos + 1 + no_char));

    str.erase(0,rpos + 1 + no_char);
    if(tmp.find_first_of("(") == std::string::npos) {
      count = count + tmp.size();
    }
    else
      str.insert(0,tmp); 
  }

  if(str.size() > 0)
    count = count + str.size();

  return count;
}

std::string StringDecompress(std::string str) {
  std::string tmp;
  std::string tmp_substr;

  int lpos,xpos,rpos;
  unsigned int no_char,no_repeat;

  if(str.find_first_of("(") == std::string::npos)
    return str;

  while(str.find_first_of("(") != std::string::npos) {
    lpos = str.find_first_of("(");
    xpos = str.find_first_of("x");
    rpos = str.find_first_of(")");

    if(lpos > 0)
      tmp = tmp + str.substr(0,lpos);

    no_char = stoul(str.substr(lpos + 1,xpos - lpos - 1));
    no_repeat = stoul(str.substr(xpos + 1,rpos - xpos - 1));
    tmp_substr = str.substr(rpos + 1,no_char);
    for(int i = 0; i < no_repeat; i++)
      tmp = tmp + tmp_substr;

    str.erase(0,rpos + 1 + no_char);
  }

  if(str.size() > 0)
    tmp = tmp + str;

  return tmp;
}