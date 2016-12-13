#include <iostream>
#include <vector>

#define PUZZLE_INPUT 1352

using std::cout;
using std::endl;

class Position {
public:
  int r,c;

  Position(int a = 1, int b = 1): c {a}, r{b} {
  }

  void Print() {
    cout << c << " " << r << endl;

    return;
  }

  void Set(int a, int b) {
    c = a;
    r = b;

    return;
  }

// these functions check if a move is valid, and if so perform it
  bool GoNorth(std::vector<std::vector<char> > map) {
    if(r - 1 >= 0 && map[r-1][c] == 0) {
      r = r - 1;
      return true;
    }
    else 
      return false;
  }

  bool GoSouth(std::vector<std::vector<char> > map) {
    if(r + 1 <= map.size() && map[r+1][c] == 0) {
      r = r + 1;
      return true;
    }
    else 
      return false;
  }

  bool GoWest(std::vector<std::vector<char> > map) {
    if(c - 1 >= 0 && map[r][c-1] == 0) {
      c = c - 1;
      return true;
    }
    else 
      return false;
  }

  bool GoEast(std::vector<std::vector<char> > map) {
    if(c + 1 <= map[0].size() && map[r][c+1] == 0) {
      c = c + 1;
      return true;
    }
    else 
      return false;
  }

};

void MapPrint(std::vector<std::vector<char> > map);
void MapFill(std::vector<std::vector<char> > &map);
long unsigned int CoordFunc(int x, int y);
void FindPath(Position p1,Position p2, std::vector<std::vector<char> > map);

int main() {
  std::vector<std::vector<char> > map(50, std::vector<char>(50));
  Position start,target(31,39);

  MapFill(map);

  FindPath(start,target,map);

  return 0;
}

void FindPath(Position start,Position target, std::vector<std::vector<char> > map) {
  int rows = map.size();
  int cols = map[0].size();

  // map_tmp tracks the number of steps required for each position
  std::vector<std::vector<char> > map_tmp(rows, std::vector<char>(cols,-1));
  map_tmp[start.r][start.c] = 0;

  // map_prev tracks the position previous to each map position
  std::vector<std::vector<Position> > map_prev(rows, std::vector<Position>(cols));

  // queue for position handling, initially only has starting position
  std::vector<Position> qu;
  qu.push_back(start);

  Position pos_curr, pos_prev;

  if(start.c == target.c && start.r == target.r) { // already there
    cout << "Starting position is on the target." << endl;
    cout << "Path length equal to 0." << endl;
    return;
  }

  int step_count = 0;
  while(qu.size() > 0 && map_tmp[target.r][target.c] == -1) {
    step_count++;
    pos_curr = qu[0];
    qu.erase(qu.begin());
    pos_prev = pos_curr;
    if(pos_curr.GoNorth(map) && map_tmp[pos_curr.r][pos_curr.c] == -1) { // first we try going north
      map_tmp[pos_curr.r][pos_curr.c] = map_tmp[pos_prev.r][pos_prev.c] + 1;
      qu.push_back(pos_curr);
      map_prev[pos_curr.r][pos_curr.c] = pos_prev;
    }

    pos_curr = pos_prev;
    if(pos_curr.GoSouth(map) && map_tmp[pos_curr.r][pos_curr.c] == -1) { // then south
      map_tmp[pos_curr.r][pos_curr.c] = map_tmp[pos_prev.r][pos_prev.c] + 1;
      qu.push_back(pos_curr);
      map_prev[pos_curr.r][pos_curr.c] = pos_prev;
    }

    pos_curr = pos_prev;
    if(pos_curr.GoEast(map) && map_tmp[pos_curr.r][pos_curr.c] == -1) { // then east
      map_tmp[pos_curr.r][pos_curr.c] = map_tmp[pos_prev.r][pos_prev.c] + 1;
      qu.push_back(pos_curr);
      map_prev[pos_curr.r][pos_curr.c] = pos_prev;
    }

    pos_curr = pos_prev;
    if(pos_curr.GoWest(map) && map_tmp[pos_curr.r][pos_curr.c] == -1) { // and finally west
      map_tmp[pos_curr.r][pos_curr.c] = map_tmp[pos_prev.r][pos_prev.c] + 1;
      qu.push_back(pos_curr);
      map_prev[pos_curr.r][pos_curr.c] = pos_prev;
    }
  }

  cout << "Part 1: " << endl;
  if(map_tmp[target.r][target.c] != -1) {
    cout << "Path length: " << static_cast<short int>(map_tmp[target.r][target.c]) << endl;
    pos_curr = target;
    while(pos_curr.r != start.r || pos_curr.c != start.c) {
      map[pos_curr.r][pos_curr.c] = 2;
      pos_curr = map_prev[pos_curr.r][pos_curr.c];
    }
    map[start.r][start.c] = 2;
    MapPrint(map);
  }

  int counter = 0;
  for(int r = 0; r < map_tmp.size(); r++)
    for(int c = 0; c < map_tmp[0].size(); c++)
      if(map_tmp[r][c] != -1 && map_tmp[r][c] <= 50)
        counter++;

  cout << "Part 2: " << endl;
  cout << "Number of locations within 50 steps: " << counter << endl;

  return;
}

void MapFill(std::vector<std::vector<char> > &map) {
  for(int row = 0; row < map.size(); row++)
    for(int col = 0; col < map[0].size(); col++)
      if(__builtin_popcount(CoordFunc(col,row) + PUZZLE_INPUT) % 2 == 1)
        map[row][col] = 1;

  return;
}

long unsigned int CoordFunc(int x, int y) {
  return x*x + 3*x + 2*x*y + y + y*y;
}

void MapPrint(std::vector<std::vector<char> > map) {
  const char *CSI = "\33[";
  const char *color_lgray = "37m";
  const char *color_lpurple = "35m";

  cout << CSI << color_lpurple;  
  for(int row = 0; row < map.size(); row++) {
    for(int col = 0; col < map[0].size(); col++)
      if(map[row][col] == 1)
        cout << "\u2588";
      else if(map[row][col] == 2)
        cout << "*";
      else if(map[row][col] > 2)
        cout << ".";
      else
        cout << " ";
    cout << endl;
  }
  cout << CSI << color_lgray;

  return;
}