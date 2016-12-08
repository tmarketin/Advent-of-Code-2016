#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <thread>
#include <chrono>

using std::cout;
using std::endl;

void ScreenPrint(std::vector<std::vector<bool> > screen);
int ScreenCount(std::vector<std::vector<bool> > screen);
void ScreenRect(std::vector<std::vector<bool> > &screen, int x, int y);
void ScreenRotateRow(std::vector<std::vector<bool> > &screen, int x, int y);
void ScreenRotateCol(std::vector<std::vector<bool> > &screen, int x, int y);

int main() {
  const char *CSI = "\33[";
  const char *color_lgray = "37m";
  const char *color_lpurple = "35m";

  int a,b;
  std::vector< std::vector<bool> > screen(6, std::vector<bool>(50));
  std::string command;

  cout << CSI << color_lpurple;

  std::ifstream fin("day8.dat");
  while(fin >> command) {
    if(command == "rect") {
      fin >> a >> b;
      ScreenRect(screen,b,a);
    }
    else if(command == "rotate") {
      fin >> command;
      if(command == "row") {
        fin >> a >> b;
        ScreenRotateRow(screen,a,b);
      }
      else if(command == "column") {
        fin >> a >> b;
        ScreenRotateCol(screen,a,b);
      }
    }
    ScreenPrint(screen);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  ScreenPrint(screen);
  cout << "\033[8B";

  cout << CSI << color_lgray;

  cout << "Total number of active pixels: " << ScreenCount(screen) << endl;

  return 0;
}

void ScreenRotateCol(std::vector<std::vector<bool> > &screen, int x, int y) {
  int col = x;
  int rows = screen.size();

  y = y % rows;

  std::vector<bool> tmp(rows);

  for(int r = 0; r < rows; r++)
    tmp[r] = screen[r][col];

  for(int r = 0; r < rows - y; r++)
    screen[r+y][col] = tmp[r];

  for(int r = 0; r < y; r++)
    screen[r][col] = tmp[rows - y + r];

  return;
}

void ScreenRotateRow(std::vector<std::vector<bool> > &screen, int x, int y) {
  int row = x;
  int cols = screen[row].size();

  std::vector<bool> tmp = screen[row];

  for(int c = 0; c < cols - y; c++)
    screen[row][c+y] = tmp[c];

  for(int c = 0; c < y; c++)
    screen[row][c] = tmp[cols - y + c];

  return;
}

void ScreenRect(std::vector<std::vector<bool> > &screen, int x, int y) {
  int rows = x < screen.size() ? x : screen.size();
  int cols = y < screen[0].size() ? y : screen[0].size();

  for(int r = 0; r < rows; r++)
    for(int c = 0; c < cols; c++)
      screen[r][c] = true;

  return;
}

void ScreenPrint(std::vector<std::vector<bool> > screen) {
  int rows = screen.size();
  int cols = screen[0].size();

  cout << endl;
  for(int r = 0; r < rows; r++) {
    for(int c = 0; c < cols; c++)
      if(screen[r][c])
        cout << "\u2588";
      else
        cout << " ";
    cout << endl;
  }
  cout << endl;
  cout << "\033[8A";

  return;
}

int ScreenCount(std::vector<std::vector<bool> > screen) {
  int count = 0;

  for(int r = 0; r < screen.size(); r++)
    for(int c = 0; c < screen[r].size(); c++)
      if(screen[r][c])
        count++;

  return count;
}