#include <algorithm>
#include <iostream>
#include <vector>
using std::cout, std::cin, std::string, std::pair, std::sort, std::vector;
const int64_t kMaxnum = 1000000000;

class SparseTable {
  vector<vector<int64_t>> table_;
  vector<int64_t> array_;
  vector<int64_t> log2_;

public:
  SparseTable(vector<int64_t> array) {
    int64_t num = array.size();
    log2_.resize(num);
    log2_[0] = 0;
    for (int64_t i = 1; i < num; ++i) {
      log2_[i] = log2_[i - 1];
      if (i + 1 >= 2 * (1 << log2_[i])) {
        ++log2_[i];
      }
    }

    table_.resize(log2_[num - 1] + 1);
    array_.resize(num);
    std::copy(array.begin(), array.end(), array_.begin());
    for (int64_t l = 0; l < log2_[num - 1]; l++) {
      table_[i].reserve(num);
    }
    for (int64_t i = 0; i < num; ++i) {
      table_[0].push_back(i);
    }
    for (int64_t l = 0; l < log2_[num - 1]; l++) {
      for (int64_t i = 0; i + (2 << l) <= num; i++) {
        if (array_[table_[l][i]] <= array_[table_[l][i + (1 << l)]]) {
          table_[l + 1].push_back(table_[l][i]);
        } else {
          table_[l + 1].push_back(table_[l][i + (1 << l)]);
        }
      }
    }
  }

  int64_t GetFirstStatistic(int64_t left, int64_t right) {
    int64_t ln = log2_[right - left];
    if (array_[table_[ln][left]] < array_[table_[ln][right - (1 << ln) + 1]]) {
      return table_[ln][left];
    }
    return table_[ln][right - (1 << ln) + 1];
  }

  int64_t GetSecondStatistic(int64_t left, int64_t right) {
    int64_t firststat = GetFirstStatistic(left, right);
    if (firststat == left) {
      return GetFirstStatistic(firststat + 1, right);
    }
    if (firststat == right) {
      return GetFirstStatistic(left, firststat - 1);
    }
    int64_t secondstatpret1 = GetFirstStatistic(left, firststat - 1);
    int64_t secondstatpret2 = GetFirstStatistic(firststat + 1, right);
    if (array_[secondstatpret1] <= array_[secondstatpret2]) {
      return secondstatpret1;
    }
    return secondstatpret2;
  }
};

int main() {
  int64_t num, questions;
  cin >> num >> questions;
  vector<int64_t> array;
  array.reserve(num);
  for (int64_t i = 0; i < num; ++i) {
    int64_t number;
    cin >> number;
    array.push_back(number);
  }
  SparseTable table = SparseTable(array);
  for (int64_t i = 0; i < questions; ++i) {
    int64_t left, right;
    cin >> left >> right;
    int ind = table.GetSecondStatistic(left - 1, right - 1);
    cout << array[ind] << "\n";
  }
}