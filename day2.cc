#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;

int main() {
  std::string input[5];
  std::vector< std::vector <int> > pad  { {1,2,3}, {4,5,6}, {7,8,9}};
  std::vector< std::vector <char> > pad2 { {' ',' ','1',' ',' '}, {' ','2','3','4',' '}, {'5','6','7','8','9'}, {' ','A','B','C',' '}, {' ',' ','D',' ',' '} };

  std::fstream fin("day2.dat");

  int col = 1;
  int row = 1;

  for(int i = 0; i < 5; i++)
    fin >> input[i];

  for(int i = 0; i < 5; i++) { // part 1
    for(int j = 0; j < input[i].size(); j++) { 
      switch(input[i][j]) {
        case('U'):
          if(row > 0)
            row--;
          break;
        case('R'):
          if(col < 2)
            col++;
          break;
        case('D'):
          if(row < 2)
            row++;
          break;
        case('L'):
        if(col > 0)
          col--;
        break;
      } // end switch
    } // end of string loop

    cout << pad[row][col] << " ";
  }
  cout << endl;

  row = 2;
  col = 0;
  for(int i = 0; i < 5; i++) { // part 2
    for(int j = 0; j < input[i].size(); j++) {
      switch(input[i][j]) {
        case('U'):
          if(abs(row - 1 - 2) + abs(col - 2) <= 2)
            row--;
          break;
        case('R'):
          if(abs(row - 2) + abs(col + 1 - 2) <= 2)
            col++;
          break;
        case('D'):
          if(abs(row + 1 - 2) + abs(col - 2) <= 2)
            row++;
          break;
        case('L'):
          if(abs(row - 2) + abs(col - 1 - 2) <= 2)
            col--;
          break;
      } // end switch
    } // end of string loop

    cout << pad2[row][col] << " ";
  }
  cout << endl;

  return 0;
}