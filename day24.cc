#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>

#define PUZZLE_POINTS 8
#define PART2_ACTIVE 1

using std::cout;
using std::endl;

class Position {
public:
  int r,c;

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
  bool GoNorth(std::vector<std::string> map) {
    if(r - 1 >= 1 && map[r-1][c] != '#') {
      r = r - 1;
      return true;
    }
    else 
      return false;
  }

  bool GoSouth(std::vector<std::string> map) {
    if(r + 1 <= map.size() - 1 && map[r+1][c] != '#') {
      r = r + 1;
      return true;
    }
    else 
      return false;
  }

  bool GoWest(std::vector<std::string> map) {
    if(c - 1 >= 1 && map[r][c-1] != '#') {
      c = c - 1;
      return true;
    }
    else 
      return false;
  }

  bool GoEast(std::vector<std::string> map) {
    if(c + 1 <= map[0].size() - 1 && map[r][c+1] != '#') {
      c = c + 1;
      return true;
    }
    else 
      return false;
  }

};

void MapPrint(std::vector<std::string> map);
int FindPath(Position p1,Position p2, std::vector<std::string> map);
Position FindPosition(std::vector<std::string> map, char c);
int FindShortest(std::array<std::array<int,PUZZLE_POINTS>, PUZZLE_POINTS> dist);
int GetDistance(std::array<std::array<int,PUZZLE_POINTS>, PUZZLE_POINTS> dist, std::string path);

int main() {
  std::vector<std::string> map;
  std::vector<Position> points;
  std::array<std::array<int,PUZZLE_POINTS>, PUZZLE_POINTS> dist = {0};
  Position start,target;

  std::string tmp;
  std::ifstream fin("day24.dat");
  while(fin >> tmp)
    map.push_back(tmp);

  MapPrint(map);

  for(int i = '0'; i < '0' + PUZZLE_POINTS; i++)
    points.push_back(FindPosition(map,i));

  for(int i = 0; i < PUZZLE_POINTS - 1; i++)
    for(int j = i + 1; j < PUZZLE_POINTS; j++) {
      dist[i][j] = FindPath(points[i],points[j],map);
      dist[j][i] = dist[i][j];
    }

  for(int i = 0; i < PUZZLE_POINTS; i++) {
    for(int j = 0; j < PUZZLE_POINTS; j++)
      cout << std::setw(4) << dist[i][j] << " ";
    cout << endl;
  }
  cout << endl;

  cout << "Shortest path: " << FindShortest(dist) << endl;

  return 0;
}

int FindPath(Position start,Position target, std::vector<std::string> map) {
  int rows = map.size();
  int cols = map[0].size();

//  cout << "Starting pos: " << start.r << " " << start.c << " Target pos: " << target.r << " " << target.c << endl;

  // map_tmp tracks the number of steps required for each position
  std::vector<std::vector<int> > map_tmp(rows, std::vector<int>(cols,-1));
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
    return 0;
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

/*  cout << "Part 1: " << endl;
  if(map_tmp[target.r][target.c] != -1) {
    cout << "Path length: " << static_cast<short int>(map_tmp[target.r][target.c]) << endl;
    pos_curr = target;
    while(pos_curr.r != start.r || pos_curr.c != start.c) {
      map[pos_curr.r][pos_curr.c] = '*';
      pos_curr = map_prev[pos_curr.r][pos_curr.c];
    }
    map[start.r][start.c] = '*';
    MapPrint(map);
  } */

  return static_cast<short int>(map_tmp[target.r][target.c]);
}

int FindShortest(std::array<std::array<int,PUZZLE_POINTS>, PUZZLE_POINTS> dist) {
  std::string perm;
  if(PUZZLE_POINTS == 5)
    perm = "1234";
  else
    perm = "1234567";
  std::string path;
  std::string min_perm;

  path = '0' + perm;
  if(PART2_ACTIVE)
    path = path + '0';
  int min_steps = GetDistance(dist,path);
  int steps;

  while(std::next_permutation(perm.begin(),perm.end())) {
    path = '0' + perm;
    if(PART2_ACTIVE)
      path = path + '0';
    steps = GetDistance(dist,path);
    if(steps < min_steps) {
      min_steps = steps;
      min_perm = perm;
    }
  }

  path = '0' + min_perm;
  if(PART2_ACTIVE)
    path = path + '0';
  cout << "Best path: " << path << ",  steps: " << min_steps << endl;

  return min_steps;
}

int GetDistance(std::array<std::array<int,PUZZLE_POINTS>, PUZZLE_POINTS> dist, std::string path) {
  int d = 0;

  for(int i = 0; i < path.size() - 1; i++)
    d = d + dist[path[i] - '0'][path[i+1] - '0'];

  return d;
}


void MapPrint(std::vector<std::string> map) {
  const char *CSI = "\33[";
  const char *color_lgray = "37m";
  const char *color_lpurple = "35m";

  cout << CSI << color_lpurple;  
  for(int row = 0; row < map.size(); row++)
    cout << map[row] << endl;
  cout << endl;

  cout << CSI << color_lgray;

  return;
}

Position FindPosition(std::vector<std::string> map, char ch) {
  Position pos;

  int rows = map.size();
  int cols = map[0].size();

  for(int r = 1; r < rows - 1; r++)
    for(int c = 1; c < cols - 1; c++)
      if(map[r][c] == ch) {
        pos.r = r;
        pos.c = c;
      }

  return pos;
}