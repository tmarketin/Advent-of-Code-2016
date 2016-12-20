#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

int main() {
  std::ifstream fin("day20.dat");

  unsigned long int lo,hi;
  unsigned long int count = 0;
  unsigned long int lo_curr = 0;
  bool first = false;

  while(fin >> lo >> hi) {
    if(lo > lo_curr + 1) {
      count = count + (lo - lo_curr - 1);
      if(! first) {
        cout << "First IP address: " << lo_curr + 1 << endl;
        first = true;
      }
    }
    if(hi > lo_curr)
      lo_curr = hi;
  }

  cout << "Total number of valid IP addresses: " << count << endl;

  return 0;
}