#include <iostream>
#include <string>
#include <vector>
#include <cstring>

#include <openssl/md5.h>

using std::cout;
using std::endl;

class Position {
public:
  int posx,posy;
  std::string path;

  Position(int a = 1, int b = 1, std::string p = ""): posx {a}, posy {b}, path {p} {
  }

  bool MoveUp() {
    if(posy == 1)
      return false;

    path = path + 'U';
    posy--;
    return true;
  }

  bool MoveDown() {
    if(posy == 4)
      return false;

    path = path + 'D';
    posy++;
    return true;
  }

  bool MoveLeft() {
    if(posx == 1)
      return false;

    path = path + 'L';
    posx--;
    return true;
  }

  bool MoveRight() {
    if(posx == 4)
      return false;

    path = path + 'R';
    posx++;
    return true;
  }

  void Print() {
    cout << "x: " << posx << ", y: " << posy << endl;
    cout << path << endl << endl;

    return;
  }

};

int main() {
  unsigned char digest[MD5_DIGEST_LENGTH];
  std::string input = "mmsxrhfx"; // part 1 input

  char targetx = 4;
  char targety = 4;
  int counter = 0;
  std::string code;
  Position start(1,1,input);
  Position current,prev;

  char fullname[30];
  char mdString[33];
  char *p_code;

  std::vector<Position> qu;
  qu.push_back(start);

  while(qu.size() > 0) {
    counter++;
    current = qu[0];
    p_code = &(current.path[0]);
    qu.erase(qu.begin());

// part 2
    if(current.posx == targetx && current.posy == targety) {
      current.Print();
      cout << "Path length: " << current.path.size() - 8 << endl;
      continue;
    }
//    current.Print();

    MD5((unsigned char*)p_code, current.path.size(), (unsigned char*)&digest);   

    for(int i = 0; i < 16; i++)
      sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);  
//    cout << mdString << endl << endl;

    prev = current;
    if(mdString[0] >= 'b' && mdString[0] <= 'f')
      if(current.MoveUp())
        qu.push_back(current);

    current = prev;
    if(mdString[1] >= 'b' && mdString[1] <= 'f')
      if(current.MoveDown())
        qu.push_back(current);

    current = prev;
    if(mdString[2] >= 'b' && mdString[2] <= 'f')
      if(current.MoveLeft())
        qu.push_back(current);

    current = prev;
    if(mdString[3] >= 'b' && mdString[3] <= 'f')
      if(current.MoveRight())
        qu.push_back(current);

  }
/*
  cout << "Queue: " << endl;
  for(int i = 0; i < qu.size(); i++)
    qu[i].Print(); */

  cout << "Number of steps: " << counter << endl;
  qu[0].Print();

  return 0;
}