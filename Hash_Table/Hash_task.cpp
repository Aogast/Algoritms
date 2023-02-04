#include <iostream>
#include <vector>

using std::vector, std::cout, std::cin;

class HashTable {
  int64_t capacity_ = 5000011;
  vector<vector<int64_t>> table_;

  int64_t Find(uint64_t index, int64_t value) {
    for (uint64_t i = 0; i < table_[index].size(); ++i) {
      if (table_[index][i] == value) {
        return i;
      }
    }
    return -1;
  }

public:
  HashTable() : table_(capacity_ - 1){};

  void Insert(int64_t value) {
    uint64_t index = std::hash<int64_t>{}(value) % capacity_;
    if (table_[index].empty()) {
      table_[index].push_back(value);
      return;
    }
    if (Find(index, value) == -1) {
      table_[index].push_back(value);
    }
  }

  void Delete(int64_t value) {
    uint64_t index = std::hash<int64_t>{}(value) % capacity_;

    if (table_[index].empty()) {
      return;
    }
    int64_t ind = Find(index, value);
    if (ind == -1) {
      return;
    }
    std::swap(table_[index][table_[index].size() - 1], table_[index][ind]);
    table_[index].pop_back();
  }

  bool FindInTable(int64_t value) {
    uint64_t index = std::hash<int64_t>{}(value) % capacity_;
    return (Find(index, value) > -1);
  }
};

int main() {
  HashTable my_table;
  int num;
  cin >> num;
  for (int i = 0; i < num; ++i) {
    std::string type_question;
    int64_t value;
    cin >> type_question >> value;
    if (type_question == "+") {
      my_table.Insert(value);
    } else if (type_question == "-") {
      my_table.Delete(value);
    } else {
      if (my_table.FindInTable(value)) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
    }
  }
}