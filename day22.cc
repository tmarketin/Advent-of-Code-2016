#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#define SIZEX 37
#define SIZEY 25

using std::cout;
using std::endl;

class Node {
public:
  int total;
  int used;
  bool goal;
};

class Grid {
public:
  std::array<std::array<Node,SIZEX>,SIZEY> grid;
  int step;
  std::array<int,2> goal,empty;

  Grid() {
  }

  Grid(std::string fname) {
    std::ifstream fin(fname);
    int col,row,tmp1, tmp2;

    while(fin >> col >> row) {
      fin >> grid[row][col].total >> grid[row][col].used >> tmp1 >> tmp2;
      if(grid[row][col].used == 0)
        empty = {row,col};
      grid[row][col].goal = false;
    }

    grid[0][SIZEX - 1].goal = true;
    goal = {0,SIZEX - 1};

    step = 0;

    return;
  }

  void Print() {
    cout << "Step: " << step << ", G: " << goal[0] << " " << goal[1] << ", E: " << empty[0] << " " << empty[1] << endl;
    for(int r = 0; r < SIZEY; r++) {
      for(int c = 0; c < SIZEX; c++)
        if(grid[r][c].used == 0)
          cout << " _ ";
        else if(grid[r][c].goal)
          cout << " G ";
        else {
          if(grid[r][c].used > 200)
            cout << " # ";
          else
            cout << " . ";
        }
      cout << endl;
    }
    cout << endl;
    return;
  }

  bool IsFinished() {
    if(grid[0][0].goal)
      return true;
    else
      return false;
  }

  bool MoveUp() {
    if(empty[0] == 0 || grid[empty[0] - 1][empty[1]].used > grid[empty[0]][empty[1]].total)
      return false;

    Node tmp = grid[empty[0]-1][empty[1]];
    grid[empty[0]-1][empty[1]] = grid[empty[0]][empty[1]];
    grid[empty[0]][empty[1]] = tmp;

    empty[0]--;
    if(grid[empty[0]+1][empty[1]].goal)
      goal[0]++;
    step++;

    return true;
  }

  bool MoveDown() {
    if(empty[0] > 2 || empty[0] == SIZEY - 1 || grid[empty[0] + 1][empty[1]].used > grid[empty[0]][empty[1]].total)
      return false;

    Node tmp = grid[empty[0]+1][empty[1]];
    grid[empty[0]+1][empty[1]] = grid[empty[0]][empty[1]];
    grid[empty[0]][empty[1]] = tmp;

    empty[0]++;
    if(grid[empty[0]-1][empty[1]].goal)
      goal[0]--;
    step++;

    return true;
  }

  bool MoveLeft() {
    if(empty[1] == 0 || grid[empty[0]][empty[1]-1].used > grid[empty[0]][empty[1]].total)
      return false;

    Node tmp = grid[empty[0]][empty[1]-1];
    grid[empty[0]][empty[1]-1] = grid[empty[0]][empty[1]];
    grid[empty[0]][empty[1]] = tmp;

    empty[1]--;
    if(grid[empty[0]][empty[1]+1].goal)
      goal[1]++;
    step++;

    return true;
  }

  bool MoveRight() {
    if(empty[0] > 2 || empty[1] == SIZEX - 1 || grid[empty[0]][empty[1]+1].used > grid[empty[0]][empty[1]].total)
      return false;

    Node tmp = grid[empty[0]][empty[1]+1];
    grid[empty[0]][empty[1]+1] = grid[empty[0]][empty[1]];
    grid[empty[0]][empty[1]] = tmp;

    empty[1]++;
    if(grid[empty[0]][empty[1]-1].goal)
      goal[1]--;
    step++;

    return true;
  }

};

bool AreEquivalent(Grid curr, std::vector<Grid> vec);

int main() {
  Grid map("day22.dat");

  cout << "Starting position: " << endl;
  map.Print();

  Grid map_curr,map_prev;

  std::vector<Grid> visited,qu;
  qu.push_back(map);

  int count = 0;
  while(! qu[0].IsFinished() && qu.size() > 0) {
    map_prev = qu[0];
    qu.erase(qu.begin());
    visited.push_back(map_prev);

//    map_prev.Print();

    map_curr = map_prev;
    if(map_curr.MoveUp() && ! AreEquivalent(map_curr,visited) && ! AreEquivalent(map_curr,qu))
      qu.push_back(map_curr);

    map_curr = map_prev;
    if(map_curr.MoveDown() && ! AreEquivalent(map_curr,visited) && ! AreEquivalent(map_curr,qu))
      qu.push_back(map_curr);

    map_curr = map_prev;
    if(map_curr.MoveLeft() && ! AreEquivalent(map_curr,visited) && ! AreEquivalent(map_curr,qu))
      qu.push_back(map_curr);

    map_curr = map_prev;
    if(map_curr.MoveRight() && ! AreEquivalent(map_curr,visited) && ! AreEquivalent(map_curr,qu))
      qu.push_back(map_curr);
  }

  cout << "Solution: " << endl;
  qu[0].Print();

  return 0;
}

bool AreEquivalent(Grid curr, std::vector<Grid> vec) {
  for(int i = vec.size() - 1; i >= 0; --i)
    if(curr.goal[0] == vec[i].goal[0] && curr.goal[1] == vec[i].goal[1] && curr.empty[0] == vec[i].empty[0] && curr.empty[1] == vec[i].empty[1])
      return true;

  return false;
}