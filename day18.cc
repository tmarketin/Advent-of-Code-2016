#include <iostream>
#include <string>

#define NUMBER_ROWS_PART1 40
#define NUMBER_ROWS_PART2 400000

using std::cout;
using std::endl;

int main() {
  std::string input  = "##.#..#.....#..#..##...##.#....###.#.##....#.###...####.####.#..####.##.#.#.#.#.##...##..###..#.####";
  std::string prev,curr;
  int safe = 48;

  curr = '.' + input + '.';
  for(int i = 1; i < NUMBER_ROWS_PART2; i++) {
    prev = curr;
    curr = '.';
    for(int j = 1; j < prev.size() - 1; j++) {
      if(prev[j-1] != prev[j+1])
        curr.push_back('#');
      else {
        curr.push_back('.');
        safe++;
      }
    }
    curr.push_back('.');
  }

  cout << "Number of safe tiles: " << safe << endl;

  return 0;
}
