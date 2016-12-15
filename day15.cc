#include <iostream>
#include <array>

#define NUM_DISC_PART1 6
#define NUM_DISC_PART2 7

using std::cout;
using std::endl;

int main() {
  std::array<std::array<int,2>,NUM_DISC_PART2> data = {{{{1,13}}, {{10,19}}, {{2,3}}, {{1,7}}, {{3,5}}, {{5,17}}, {{0,11}}}};
  std::array<char,NUM_DISC_PART2> pos;

  unsigned long int t = 11;

  while(true) {
    t += 13;
    for(int i = 0; i < NUM_DISC_PART1; i++)
      pos[i] = (data[i][0] + t) % data[i][1];

    if(pos[0] == 12 && pos[1] == 17 && pos[2] == 0 && pos[3] == 3 && pos[4] == 0 && pos[5] == 11)
      break;
  }

  cout << "Time (part 1): " << t << endl;

  t = 11;
  while(true) {
    t += 13;
    for(int i = 0; i < NUM_DISC_PART2; i++)
      pos[i] = (data[i][0] + t) % data[i][1];

    if(pos[0] == 12 && pos[1] == 17 && pos[2] == 0 && pos[3] == 3 && pos[4] == 0 && pos[5] == 11 && pos[6] == 4)
      break;
  }

  cout << "Time (part 2): " << t << endl;

  return 0;
}