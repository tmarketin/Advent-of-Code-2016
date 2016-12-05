#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::endl;

int main() {
  std::vector<std::vector <int> > data;
  std::vector<int> triangle;

  std::fstream fin("day3.dat");

  int a,b,c;

  for(int i = 0; i < 1992; i++) {
    triangle.clear();
    fin >> a >> b >> c;
    triangle.push_back(a);
    triangle.push_back(b);
    triangle.push_back(c);
    data.push_back(triangle);
  }

  int count = 0;
  for(int i = 0; i < data.size(); i++)
    if(data[i][0] + data[i][1] > data[i][2] && data[i][0] + data[i][2] > data[i][1] && data[i][1] + data[i][2] > data[i][0])
      count++;

  cout << "Number of valid triangles (part 1): " << count << endl;

  count = 0;
  for(int i = 0; i < data.size(); i+=3) {
    for(int j = 0; j < 3; j++)
      if(data[i][j] + data[i+1][j] > data[i+2][j] && data[i][j] + data[i+2][j] > data[i+1][j] && data[i+1][j] + data[i+2][j] > data[i][j])
        count++;    
  }

  cout << "Number of valid triangles (part 2): " << count << endl;

  return 0;
}