#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct line {
  int x1,y1;
  int x2,y2;
  char orientation; // horizontal or vertical
};

using std::cout;
using std::endl;
using std::min;
using std::max;

bool check_intersections(std::vector<struct line> lines);

int main() {
  char dirs[] = {'N','E','S','W'};

  std::fstream fin("day1.dat");

  int dir = 0;
  int ns = 0;
  int ew = 0;

  struct line tmpline;
  tmpline.x1 = 0;
  tmpline.y1 = 0;
  tmpline.x2 = 0;
  tmpline.y2 = 0;

  std::vector<struct line> lines;

  char turn;
  int distance;

  int counter = 0;
  while(fin >> turn >> distance) {
    if(turn == 'R') {
      dir++;
      if(dir == 4)
        dir = 0;
    }
    else {
      dir--;
      if(dir == -1)
        dir = 3;
    }

    switch(dir) {
      case(0):
        ns += distance;
        tmpline.y2 += distance;
        tmpline.orientation = 'v';
        break;
      case(1):
        ew -= distance;
        tmpline.x2 -= distance;
        tmpline.orientation = 'h';
        break;
      case(2):
        ns -= distance;
        tmpline.y2 -= distance;
        tmpline.orientation = 'v';
        break;
      case(3):
        ew += distance;
        tmpline.x2 += distance;
        tmpline.orientation = 'h';
        break;
    }

    lines.push_back(tmpline);
    tmpline.x1 = tmpline.x2;
    tmpline.y1 = tmpline.y2;

    counter++;
  }

  cout << "Distance is: " << abs(ns) + abs(ew) << endl << endl;

  check_intersections(lines);

  return 0;
}

bool check_intersections(std::vector<struct line> lines) {
  int n = lines.size();

  for(int j = 2; j < n; j++) {
    struct line tmpline = lines[j];
    for(int i = 0; i < j - 1; i++) {
      if(tmpline.orientation == 'v' && lines[i].orientation == 'h') {
        if(lines[i].y1 <= max(tmpline.y1,tmpline.y2) && lines[i].y1 >= min(tmpline.y1,tmpline.y2))
          if(tmpline.x1 <= max(lines[i].x1,lines[i].x2) && tmpline.x1 >= min(lines[i].x1,lines[i].x2)) {
            cout << "Intersection!" << endl;
            cout << tmpline.x1 << " " << lines[i].y1 << endl << "Distance: " << abs(tmpline.x1) + abs(lines[i].y1) << endl;
            return true;
          }
      }

      if(tmpline.orientation == 'h' && lines[i].orientation == 'v') {
        if(tmpline.y1 <= max(lines[i].y1,lines[i].y2) && tmpline.y1 >= min(lines[i].y1,lines[i].y2))
          if(lines[i].x1 <= max(tmpline.x1,tmpline.x2) && lines[i].x1 >= min(tmpline.x1,tmpline.x2)) {
            cout << "Intersection!" << endl;
            cout << lines[i].x1 << " " << tmpline.y1 << endl << "Distance: " << abs(lines[i].x1) + abs(tmpline.y1) << endl;
            return true;
          }
      }

      if(tmpline.orientation == 'h' && lines[i].orientation == 'h' && tmpline.y1 == lines[i].y1) {
        if(tmpline.x1 < min(lines[i].x1,lines[i].x2) && tmpline.x2 >= min(lines[i].x1,lines[i].x2)) {
          cout << "Intersection!" << endl;
          cout << min(lines[i].x1,lines[i].x2) << " " << lines[i].y1 << endl << "Distance: " << abs(min(lines[i].x1,lines[i].x2)) + abs(lines[i].y1) << endl;
          return true;
        }
        if(tmpline.x1 > max(lines[i].x1,lines[i].x2) && tmpline.x2 <= max(lines[i].x1,lines[i].x2)) {
          cout << "Intersection!" << endl;
          cout << max(lines[i].x1,lines[i].x2) << " " << lines[i].y1 << endl << "Distance: " << abs(max(lines[i].x1,lines[i].x2)) + abs(lines[i].y1) << endl;
          return true;
        }
      }

      if(tmpline.orientation == 'v' && lines[i].orientation == 'v' && tmpline.x1 == lines[i].x1) {
        if(tmpline.y1 < min(lines[i].y1,lines[i].y2) && tmpline.y2 >= min(lines[i].y1,lines[i].y2)) {
          cout << "Intersection!" << endl;
          cout << lines[i].x1 << " " << min(lines[i].y1,lines[i].y2) << endl << "Distance: " << abs(lines[i].x1) + abs(min(lines[i].y1,lines[i].y2)) << endl;
          return true;
        }
        if(tmpline.y1 > max(lines[i].y1,lines[i].y2) && tmpline.y2 <= max(lines[i].y1,lines[i].y2)) {
          cout << "Intersection!" << endl;
          cout << lines[i].x1 << " " << max(lines[i].y1,lines[i].y2) << endl << "Distance: " << abs(lines[i].x1) + abs(max(lines[i].y1,lines[i].y2)) << endl;
          return true;
        }
      }
    } // for i loop
  } // for j loop

  return false;
}
