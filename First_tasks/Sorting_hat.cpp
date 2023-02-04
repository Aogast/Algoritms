#include <iostream>
using std::cout, std::cin, std::string, std::min;

const int INF = 1 << 16;

struct Node {
  int value;
  int min_stack = INF;
  Node* prev;
  Node(int value_input, Node* prev_input, int min_prev = INF) {
    value = value_input;
    prev = prev_input;
    min_stack = min_prev;
  }
};

struct Stack {
  Node* head = nullptr;
  int size = 0;
  int Back() { return head->value; }

  void Push(int value) {
    Node* new_head = nullptr;
    if (head != nullptr) {
      new_head = new Node(value, head, min(value, head->min_stack));
    } else {
      new_head = new Node(value, head, value);
    }
    size++;
    head = new_head;
  }

  int Pop() {
    Node* new_head = head->prev;
    int res = Back();
    delete head;
    head = new_head;
    size--;
    return res;
  }

  void Clear() {
    while (head != nullptr) {
      Pop();
    }
  }

  ~Stack() { Clear(); }
};

void DeleteFromQueue(Stack* stack1, Stack* stack2) {
  if (stack2->size > 0) {
    cout << stack2->Pop() << "\n";
  } else {
    while (stack1->size > 0) {
      stack2->Push(stack1->Pop());
    }
    if (stack2->size > 0) {
      cout << stack2->Pop() << "\n";
    } else {
      cout << "error\n";
    }
  }
}

void PrintFront(Stack* stack1, Stack* stack2) {
  if (stack2->size > 0) {
    cout << stack2->Back() << "\n";
  } else {
    while (stack1->size > 0) {
      stack2->Push(stack1->Pop());
    }
    if (stack2->size > 0) {
      cout << stack2->Back() << "\n";
    } else {
      cout << "error\n";
    }
  }
}

void PrintMin(Stack* stack1, Stack* stack2) {
  if (stack1->size > 0 && stack2->size > 0) {
    cout << min(stack1->head->min_stack, stack2->head->min_stack) << "\n";
  } else if (stack1->size > 0) {
    cout << stack1->head->min_stack << "\n";
  } else if (stack2->size > 0) {
    cout << stack2->head->min_stack << "\n";
  } else {
    cout << "error\n";
  }
}

int main() {
  Stack stack1, stack2;
  string command;
  int n, num;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> command;
    if (command == "enqueue") {
      cin >> num;
      stack1.Push(num);
      cout << "ok\n";
    } else if (command == "dequeue") {
      DeleteFromQueue(&stack1, &stack2);
    } else if (command == "front") {
      PrintFront(&stack1, &stack2);
    } else if (command == "size") {
      cout << stack1.size + stack2.size << "\n";
    } else if (command == "clear") {
      stack1.Clear(), stack2.Clear();
      cout << "ok\n";
    } else {
      PrintMin(&stack1, &stack2);
    }
  }
}