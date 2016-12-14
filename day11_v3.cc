#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <bitset>

#define NUM_ITEMS 10 // 10 for the first part, 14 for the second part
#define NUM_FLOORS 4

#define GROUND_FLOOR_MASK 0xFFFF000000000000
#define GROUND_FLOOR_OBJ_MASK 0x0001000000000000

#define TOP_FLOOR_MASK 0x000000000000FFFF
#define TOP_FLOOR_OBJ_MASK 0x0000000000000001

#define GROUND_FLOOR_GENERATORS_MASK 0x5555000000000000
#define GROUND_FLOOR_MICROCHIPS_MASK 0xAAAA000000000000

#define LIST_SIZE 16

#define EMPTY -1
#define GENERATOR 0
#define MICROCHIP 1

using std::cout;
using std::endl;

void PrintBinary(unsigned long int k);

class State {
public:
  unsigned long int items;
  int level;
  int step;
  int distance;

  State() {
    if(NUM_ITEMS == 4) {
      items = 0x000A000100040000;
      distance = 13;
    }
    else if(NUM_ITEMS == 10) {
      items = 0x03D7002800000000;
      distance = 28;
    }
    else if(NUM_ITEMS == 14) {
      items = 0x3FD7002800000000;
      distance = 40;
    }

    step = 0;
    level = 0;

    return;
  }

  void Print() {
//    std::array<std::string,NUM_ITEMS/2> names {"He","Li"}; // NUM_ITEMS == 4
    std::array<std::string,7> names {"Co","Pm","Po","Ru","Tm","El","DL"}; // otherwise
    std::array<std::string,2> obj {"G","M"};

    unsigned long int mask_floor = TOP_FLOOR_MASK;
    unsigned long int mask_object = TOP_FLOOR_OBJ_MASK;
    unsigned long int floor;

    cout << "Step number: " << step << endl;
    cout << "Distance: " << distance << endl;

    for(int i = NUM_FLOORS - 1; i >= 0; i--) {
      floor = items & mask_floor;

      cout << "F" << i << "  ";
      if(level == i)
        cout << "E  ";
      else 
        cout << ".  ";

      for(int j = 0; j < NUM_ITEMS; j++) {
        if((floor & (mask_object << j)) == 0) // if no item
          cout << "... ";
        else {
          if(j % 2 == 0) // if generator present
            cout << names[j/2] << obj[0] << " ";
          else // if microchips present
            cout << names[j/2] << obj[1] << " ";
        }
      }

      mask_floor <<= LIST_SIZE;
      mask_object <<= LIST_SIZE;

      cout << endl;
    }
    cout << endl;

    return;
  }
 
  bool IsValid() {
    unsigned long int mask_floor = GROUND_FLOOR_MASK;
    unsigned long int mask_object = GROUND_FLOOR_OBJ_MASK;
    unsigned long int mask_generators = GROUND_FLOOR_GENERATORS_MASK;
    unsigned long int mask_microchips = GROUND_FLOOR_MICROCHIPS_MASK;
    unsigned long int floor;
    unsigned long int fl_gen_obj, fl_mic_obj;


    for(int i = 0; i < NUM_FLOORS; i++) {
      floor = items & mask_floor;

      for(int j = 1; j < NUM_ITEMS; j+=2) {
        fl_mic_obj = floor & (mask_object << j); 
        fl_gen_obj = floor & (mask_object << (j-1)); 
        if(fl_mic_obj != 0 && fl_gen_obj == 0 && (floor & mask_generators) != 0)
          return false;
      }

      mask_floor >>= LIST_SIZE;
      mask_object >>= LIST_SIZE;
      mask_generators >>= LIST_SIZE;
    }

    return true;
  }

  bool IsFinished() {
    unsigned long int mask_floor = TOP_FLOOR_MASK; // check only final floor
    
    if(__builtin_popcount(items & mask_floor) == NUM_ITEMS)
      return true;
    else
      return false;

  }

  void MoveUp(unsigned long int k) {
    level++;
    step++;

    if(level > NUM_FLOORS - 1) {
      cout << "Error moving up!" << endl;
      exit(1);
    }

    items = items^k;
    items = items | (k >> LIST_SIZE);

    if(__builtin_popcountl(k) == 1)
      distance -= 1;
    else if(__builtin_popcountl(k) == 2)
      distance -=2;

    return;
  } 

  void MoveDown(unsigned long int k) {
    level--;
    step++;

    if(level < 0) {
      cout << "Error moving down!" << endl;
      exit(1);
    }

    items = items^k;
    items = items | (k << LIST_SIZE);

    if(__builtin_popcountl(k) == 1)
      distance += 1;
    else if(__builtin_popcountl(k) == 2)
      distance +=2;

    return;
  }   

};

bool AreEquivalent(State st, State v);
bool AlreadyVisited(State st,std::vector<State> visited);

int main() {
  State state_curr;
  State state_prev;
  State state_tmp;

  int level;
  unsigned long int mask_floor,mask_obj;
  unsigned long int floor,item1,item2;

// queue for tracking future moves
  std::vector<State> qu; 
  qu.push_back(state_curr);

// keeping track of visited positions
  std::vector<State> visited; 

  cout << "Starting position:" << endl;
  qu[0].Print();

  int counter = 0;
  while(! qu[0].IsFinished() && state_prev.step < 100) {
    counter++;

    state_prev = qu[0];
    qu.erase(qu.begin());
    visited.push_back(state_prev);
    level = state_prev.level;

// generate moves
// generate moves with a single item
    mask_obj = GROUND_FLOOR_OBJ_MASK >> level*LIST_SIZE;
    floor = state_prev.items & (GROUND_FLOOR_MASK >> level*LIST_SIZE);
    for(int i = 0; i < NUM_ITEMS; i++) {
      item1 = floor & (mask_obj << i);
      if(item1 != 0) { // item present

        if(level < 3) { // try moving up
          state_curr = state_prev;
          state_curr.MoveUp(item1);
          if(state_curr.IsValid() && ! AlreadyVisited(state_curr,visited) && ! AlreadyVisited(state_curr,qu))
            qu.push_back(state_curr);
        }

        if(level > 0) { // try moving down
          state_curr = state_prev;
          state_curr.MoveDown(item1);
          if(state_curr.IsValid() && ! AlreadyVisited(state_curr,visited) && ! AlreadyVisited(state_curr,qu))
            qu.push_back(state_curr);
        }
      }
    } // loop over item on floor

// generate moves with two items        
    for(int i = 0; i < NUM_ITEMS - 1; i++) {
      item1 = floor & (mask_obj << i);
      if(item1 != 0) { // item 1
        for(int j = i + 1; j < NUM_ITEMS; j++) {
          item2 = floor & (mask_obj << j);
          if(item2 != 0) { // item 2

            if(level < 3) {
              state_curr = state_prev;
              state_curr.MoveUp((item1 | item2));
              if(state_curr.IsValid() && ! AlreadyVisited(state_curr,visited) && ! AlreadyVisited(state_curr,qu))
                qu.push_back(state_curr);
            }

            if(level > 0) {
              state_curr = state_prev;
              state_curr.MoveDown((item1 | item2));
              if(state_curr.IsValid() && ! AlreadyVisited(state_curr,visited) && ! AlreadyVisited(state_curr,qu))
                qu.push_back(state_curr);
            }
          }
        } // loop over item 2
      }
    } // loop over item 1

  } // while

  qu[0].Print();
  cout << "Number of states visited: " << counter << endl;
  cout << "Size of queue: " << qu.size() << endl;

  return 0;
}

bool AreEquivalent(State st, State v) {
  if(st.level == v.level && st.items == v.items)
    return true;

  if(st.level != v.level)
    return false;

  unsigned long int mask_floor = GROUND_FLOOR_MASK;
  unsigned long int mask_generators = GROUND_FLOOR_GENERATORS_MASK;
  unsigned long int mask_microchips = GROUND_FLOOR_MICROCHIPS_MASK;
  for(int i = 0; i < NUM_FLOORS; i++) { // check each floor
    if(__builtin_popcountl((st.items & mask_floor) & mask_generators) != __builtin_popcountl((v.items & mask_floor) & mask_generators))
      return false;

    if(__builtin_popcountl((st.items & mask_floor) & mask_microchips) != __builtin_popcountl((v.items & mask_floor) & mask_microchips))
      return false;

    mask_floor >>= LIST_SIZE;
    mask_generators >>= LIST_SIZE;
    mask_microchips >>= LIST_SIZE;
  }

  return true;
}

bool AlreadyVisited(State st,std::vector<State> visited) {
  for(int i = visited.size() - 1; i >= 0; i--)
    if(AreEquivalent(st,visited[i]))
      return true;

  return false;
}

void PrintBinary(unsigned long int k) {
  std::string measure = "0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF0123456789ABCDEF";

  cout << measure << endl;
  cout << std::bitset<64>(k) << endl;

  return;
}