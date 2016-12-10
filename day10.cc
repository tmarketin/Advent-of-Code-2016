#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

class Bot {
private:
  int val_lo,val_hi;
  int num_val;
  int lo_to, hi_to;
  std::string lo,hi;

public:
  Bot() : val_lo {0}, val_hi {0}, lo_to {-1}, hi_to {0}, lo {""}, hi {""}, num_val {0} {
  }

  void BotSetValue(int k) {
    if(num_val == 0) {
      val_lo = k;
      num_val++;
    }
    else {
      if(k > val_lo)
        val_hi = k;
      else {
        val_hi = val_lo;
        val_lo = k;
      }
      num_val++;
    }
    return;
  }

  void BotClear() {
    num_val = 0;
    val_lo = 0;
    val_hi = 0;

    return;
  }

  int BotGetNumVal() {
    return num_val;
  }

  void BotSetOutputLow(std::string out, int k) {
    lo_to = k;
    lo = out;

    return;
  }

  void BotSetOutputHigh(std::string out, int k) {
    hi_to = k;
    hi = out;

    return;
  }

  std::string BotGetOutputLow() {
    return lo;
  }

  std::string BotGetOutputHigh() {
    return hi;
  }

  int BotGetValLo() {
    return val_lo;
  }

  int BotGetValHi() {
    return val_hi;
  }

  int BotGetToLo() {
    return lo_to;
  }

  int BotGetToHi() {
    return hi_to;
  }

};

int main() {
  std::vector<Bot> bots(210);
  std::vector<unsigned short int> output(210,0.0);
  std::string tmp;
  int a,b;

  std::ifstream fin("day10.dat");

  while(fin >> tmp) {
    if(tmp == "value") {
      fin >> a >> b;
      bots[b].BotSetValue(a);
    }
    else {
      fin >> a >> tmp >> b;
      bots[a].BotSetOutputLow(tmp,b);
      fin >> tmp >> b;
      bots[a].BotSetOutputHigh(tmp,b);
    }
  }

  bool is_finished = false;
  int count = 1;
  while(count > 0) {
    count = 0;
    for(int loop = 0; loop < 210; loop++) {
      if(bots[loop].BotGetNumVal() == 2) {
        count++;
        a = bots[loop].BotGetValLo();
        b = bots[loop].BotGetValHi();
        if(a == 17 && b == 61) {
          cout << "Bot number " << loop << " compares values " << a << " and " << b << endl;
          is_finished = true;
        }
        if(bots[loop].BotGetOutputLow() == "output")
          output[bots[loop].BotGetToLo()] = bots[loop].BotGetValLo();
        else
          bots[bots[loop].BotGetToLo()].BotSetValue(bots[loop].BotGetValLo());

        if(bots[loop].BotGetOutputHigh() == "output")
          output[bots[loop].BotGetToHi()] = bots[loop].BotGetValHi();
        else
          bots[bots[loop].BotGetToHi()].BotSetValue(bots[loop].BotGetValHi());

        bots[loop].BotClear();
      }
    }
  }

  cout << "Final outputs: " << endl;
  for(int loop = 0; loop < 210; loop++) 
    if(output[loop] > 0)
      cout << loop << " " << output[loop] << endl;

  return 0;
}