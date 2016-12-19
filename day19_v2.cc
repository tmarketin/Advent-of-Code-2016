#include <iostream>

#define PUZZLE_INPUT 5

using std::cout;
using std::endl;

class Node {
public:
  int elf;
  static int generator;
  Node *next;

  Node() {
    elf = generator++;
    next = nullptr;
  }

};

class List {
public:
  Node *head,*tail;
  int size;

  List() {
    head = nullptr;
    tail = nullptr;
  }

  void GenerateList(int k) {
    Node::generator = 1;

    head = new Node;
    tail = head;
    for(int i = 1; i < k; i++) {
      tail->next = new Node;
      tail = tail->next;
    }
    tail->next = head;

    size = k;

    return;    
  }

  void Delete() {
    Node *tmp;
    Node *tmp2 = this->head;

    while(tmp2 != this->tail) {
      tmp = tmp2;
      tmp2 = tmp2->next;
      delete tmp;
    }
    delete tmp2;

    this->head = nullptr;
    this->tail = nullptr;

    return;
  }

  void Print() {
    Node *tmp = head;

    while(tmp->next != head) {
      cout << tmp->elf << " ";
      tmp = tmp->next;
    }
    cout << tail->elf << endl;

    return;
  }

  int EvaluatePart1() {
    Node *tmp = head;
    Node *tmp_del;

    while(tmp != tmp->next) {
      tmp_del = tmp->next;
      tmp->next = tmp->next->next;
      delete tmp_del;
      tmp = tmp->next;
    }

    head = tmp;
    tail = tmp;
    return tmp->elf;
  }

  int EvaluatePart2() {
    Node *mid = head;
    Node *tmp = head;
    Node *tmp_del;

    for(int i = 1; i < size/2; i++)
      mid = mid->next; // Node before opposite

    bool odd = true;
    while(tmp != tmp->next) {
      tmp_del = mid->next;
      mid->next = mid->next->next;
      delete tmp_del;
      if(odd) {
        mid = mid->next;
        odd = false;
      }
      else
        odd = true;
      tmp = tmp->next;
    }

    head = tmp;
    tail = tmp;

    return tmp->elf;
  }
};

int Node::generator = 1;

int main() {
  List llist;

// part 1
  llist.GenerateList(3004953);
  cout << llist.EvaluatePart1() << endl;
  llist.Delete();

// part 2
  llist.GenerateList(3004953);
  cout << llist.EvaluatePart2() << endl;
  llist.Delete();

  return 0;
}

