#include <deque>
#include <iostream>

using std::cout, std::cin, std::deque;

int main() {
  int len, num;
  char command;
  deque<int> deck1, deck2;
  cin >> len;
  for (int iteration = 0; iteration < len; iteration++) {
    cin >> command;
    if (command == '+') {
      cin >> num;
      deck2.push_back(num);
    } else if (command == '*') {
      cin >> num;
      deck2.push_front(num);
    } else {
      cout << deck1.front() << "\n";
      deck1.pop_front();
    }
    if (deck2.size() - deck1.size() == 1) {
      deck1.push_back(deck2.front());
      deck2.pop_front();
    }
  }
}