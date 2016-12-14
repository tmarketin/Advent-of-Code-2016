#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>

#define NUM_ITEMS 10 // 10 for the first part, 14 for the second part
#define NUM_FLOORS 4

#define EMPTY -1
#define GENERATOR 0
#define MICROCHIP 1

using std::cout;
using std::endl;

class Item {
public:
  int el; // -1 for empty, 0 for He, 1 for Li
  int type; // -1 for empty, 0 for generator, 1 for microchip

  Item(int s1 = -1, int s2 = -1): el {s1}, type {s2} {
  }

  void Print() {
    switch(el) {
      case -1:
        cout << "..";
        break;
      case 0:
        cout << "Co";
        break;
      case 1:
        cout << "Pm";
        break;
      case 2:
        cout << "Po";
        break;
      case 3:
        cout << "Ru";
        break;
      case 4:
        cout << "Tm";
        break;
      case 5:
        cout << "El";
        break;
      case 6:
        cout << "DL";
        break;
    }
    if(type == -1)
      cout << ". ";
    else if(type == 0)
      cout << "G ";
    else
      cout << "M ";

    return;
  }

  void Clear() {
    el = -1;
    type = -1;

    return;
  }

  bool IsEmpty(){
    if(el == -1 && type == -1)
      return true;
    else
      return false;
  }
};

class Elevator {
public:
  std::array<Item,NUM_ITEMS> items;
  int it1,it2;
  int level;

  Elevator() {
    level = 0;
    it1 = -1;
    it2 = -1;
  }

};

class State {
public:
  std::vector<std::vector<Item> > conf;
  Elevator lift;
  int step;
  int distance;

  State() {
    if(NUM_ITEMS == 4) {
      conf.push_back({ {-1,-1}, {0,1}, {-1,-1}, {1,1} });
      conf.push_back({ {0,0}, {-1,-1}, {-1,-1}, {-1,-1} });
      conf.push_back({ {-1,-1}, {-1,-1}, {1,0}, {-1,-1} });
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}}); 
    }
    else if(NUM_ITEMS == 10) {
      conf.push_back({ {0,0}, {0,1}, {1,0}, {-1,-1}, {2,0}, {-1,-1}, {3,0}, {3,1}, {4,0}, {4,1} });
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {1,1}, {-1,-1}, {2,1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} });    
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} });    
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }); 
    }
    else if(NUM_ITEMS == 14) {
      conf.push_back({ {0,0}, {0,1}, {1,0}, {-1,-1}, {2,0}, {-1,-1}, {3,0}, {3,1}, {4,0}, {4,1}, {5,0}, {5,1}, {6,0}, {6,1} });
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {1,1}, {-1,-1}, {2,1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} });    
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} });    
      conf.push_back({ {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} });
    }

    distance = 0;
    for(int i = 0; i < NUM_FLOORS; i++) {
      for(int j = 0; j < NUM_ITEMS; j++)
        if(! conf[i][j].IsEmpty())
          distance = distance + NUM_FLOORS - i;
    }

    step = 0;

    return;
  }

  void Print() {
    cout << "Step number: " << step << endl;
    cout << "Distance: " << distance << endl;
    for(int i = NUM_FLOORS - 1; i >= 0; i--) {
      cout << "F" << i << "  ";
      if(lift.level == i)
        cout << "E  ";
      else
        cout << ".  ";
      for(int j = 0; j < NUM_ITEMS; j++)
        conf[i][j].Print();
      cout << endl;
    }
    cout << endl;

    return;
  }

  bool IsValid() {
    for(int i = 0; i < NUM_FLOORS; i++) { // loop over floors
      for(int j = 1; j < NUM_ITEMS; j+=2) { // loop over microchips
        if(conf[i][j].type == MICROCHIP && conf[i][j-1].type == EMPTY) { // if not shielded
          for(int k = 0; k < NUM_ITEMS; k+=2) // look for generators
            if(conf[i][k].type != EMPTY)
              return false;
        }
      }
    }

    return true;
  }

  bool IsFinished() {
    int top = NUM_FLOORS - 1;
    for(int j = 0; j < NUM_ITEMS; j++)
      if(conf[top][j].type == -1)
        return false;

    return true;
  }

  bool AllEmptyBelow() {
    if(lift.level == 0)
      return false;

    for(int i = 0; i < lift.level; i++)
      for(int j = 0; j < NUM_ITEMS; j++)
        if(! conf[i][j].IsEmpty())
          return false;

    return true;
  }

  void Load(int k, int l) {
    lift.items[k] = conf[lift.level][k];
    lift.it1 = k;
    conf[lift.level][k].Clear();

    if(l > -1) {
      lift.items[l] = conf[lift.level][l];
      lift.it2 = l;
      conf[lift.level][l].Clear();
    }

    return;
  }

  void MoveUp() {
    lift.level++;
    step++;
    if(lift.level > NUM_FLOORS - 1) {
      cout << "Error moving up!" << endl;
      exit(1);
    }

    if(lift.it1 != -1) {
      conf[lift.level][lift.it1] = lift.items[lift.it1];
      lift.items[lift.it1].Clear();
      lift.it1 = -1;
      distance--;
    }

    if(lift.it2 != -1) {
      conf[lift.level][lift.it2] = lift.items[lift.it2];
      lift.items[lift.it2].Clear();
      lift.it2 = -1;
      distance--;
    }

    return;
  }

  void MoveDown() {
    lift.level--;
    step++;
    if(lift.level < 0) {
      cout << "Error moving down!" << endl;
      exit(1);
    }

    if(lift.it1 != -1) {
      conf[lift.level][lift.it1] = lift.items[lift.it1];
      lift.items[lift.it1].Clear();
      lift.it1 = -1;
      distance++;
    }

    if(lift.it2 != -1) {
      conf[lift.level][lift.it2] = lift.items[lift.it2];
      lift.items[lift.it2].Clear();
      lift.it2 = -1;
      distance++;
    }

    return;
  }

};

bool operator== (const Item &it1, const Item &it2);
bool operator== (const State &s1, const State &s2); 
bool AlreadyVisited(State st,std::vector<State> visited);
bool AreEquivalent(State st, State v);
bool CompareDistance(State st1, State st2);

int main() {
  State state_curr;
  State state_prev;
  State state_tmp;

// queue for tracking future moves
  std::vector<State> qu; 
  qu.push_back(state_curr);

// keeping track of visited positions
  std::vector<State> visited; 

  int level_curr; // current elevator level

  cout << "Starting position: " << endl;
  qu[0].Print();
  exit(1);

  int counter = 0;
  while(! qu[0].IsFinished() && state_prev.step < 200) {
    counter++;

    state_prev = qu[0];       
    visited.push_back(state_prev); // add current state to the list of visited states

    state_curr = state_prev; // take first state from queue
    level_curr = state_curr.lift.level;

// generate all moves
// first moves with a single item
    for(int i = 0; i < NUM_ITEMS; i++) {
    if(! state_curr.conf[level_curr][i].IsEmpty()) {

        state_curr = state_prev; // take first state from queue
        state_curr.Load(i,-1); // load item

        state_tmp = state_curr;
        if(level_curr < 3) { // if not at top floor try going up
          state_tmp.MoveUp();
          if(state_tmp.IsValid() && ! AlreadyVisited(state_tmp,visited) && ! AlreadyVisited(state_tmp,qu)) {// if move results with a valid configuration and not already visited
            qu.push_back(state_tmp);
          }
        } // if level < 3

        state_tmp = state_curr;
        if(level_curr > 0 && ! state_tmp.AllEmptyBelow()) { // if not at bottom floor try going down
          state_tmp.MoveDown();
          if(state_tmp.IsValid() && ! AlreadyVisited(state_tmp,visited) && ! AlreadyVisited(state_tmp,qu)) {// if move results with a valid configuration
            qu.push_back(state_tmp);
          }
        } // if level > 0
      } // if there is an item at position i
    } // loop through positions

// then moves with two items
    state_curr = state_prev;
    for(int i = 0; i < NUM_ITEMS - 1; i++) {
      if(! state_curr.conf[level_curr][i].IsEmpty()) {
        for(int j = i + 1; j < NUM_ITEMS; j++) {
          if(! state_curr.conf[level_curr][j].IsEmpty()) {
            state_curr = state_prev;
            if(state_curr.conf[level_curr][i].type != state_curr.conf[level_curr][j].type && state_curr.conf[level_curr][i].el != state_curr.conf[level_curr][j].el)
              continue;
            else
              state_curr.Load(i,j); // load both items in elevator (if different type, only load if equal element)

            state_tmp = state_curr;
            if(level_curr < 3) { // if not at top floor try going up
              state_tmp.MoveUp();
              if(state_tmp.IsValid() && ! AlreadyVisited(state_tmp,visited) && ! AlreadyVisited(state_tmp,qu)) {
                qu.push_back(state_tmp);
              }
            }

            state_tmp = state_curr;
            if(level_curr > 0 && ! state_tmp.AllEmptyBelow()) { // if not at bottom floor try going down
              state_tmp.MoveDown();
              if(state_tmp.IsValid() && ! AlreadyVisited(state_tmp,visited) && ! AlreadyVisited(state_tmp,qu))  {// if move results with a valid configuration
                qu.push_back(state_tmp);
              }
            } // if level > 0

          } // if j item is here
        } // for j loop
      } // if i item is here
    } // for i loop 
    

    qu.erase(qu.begin());
  } // while loop

  qu[0].Print();
  cout << "Number of states visited: " << counter << endl;
  cout << "Size of queue: " << qu.size() << endl;

  return 0;
}

bool operator== (const Item &it1, const Item &it2) {
  if(it1.el == it2.el && it1.type == it2.type)
    return true;
  else
    return false;
}

bool operator== (const State &s1, const State &s2) {
  if(s1.lift.level != s2.lift.level)
    return false;

  for(int i = 0; i < NUM_FLOORS; i++)
    if(s1.conf[i] != s2.conf[i])
      return false;

  return true;
}

bool AreEquivalent(State st, State v) {
  if(st == v)
    return true;

  if(st.lift.level != v.lift.level)
    return false;

  for(int i = 0; i < NUM_FLOORS; i++) { // check each floor
    int cm1 = 0;
    int cm2 = 0;
    int cg1 = 0;
    int cg2 = 0;
    for(int j = 0; j < NUM_ITEMS; j+=2) { // count generators
      if(st.conf[i][j].type == GENERATOR)
        cg1++;
      if(v.conf[i][j].type == GENERATOR)
        cg2++;
    }
    if(cg1 != cg2)
      return false;

    for(int j = 1; j < NUM_ITEMS; j+=2) { // count microchips
      if(st.conf[i][j].type == MICROCHIP)
        cm1++;
      if(v.conf[i][j].type == MICROCHIP)
        cm2++;
    }
    if(cm1 != cm2)
      return false;
  }

  return true;
}

bool AlreadyVisited(State st,std::vector<State> visited) {
  for(int i = visited.size() - 1; i >= 0; i--)
    if(AreEquivalent(st,visited[i]))
      return true;

  return false;
}

bool CompareDistance(State st1, State st2) {
  if(st1.distance < st2.distance)
    return true;
  else
    return false;
}