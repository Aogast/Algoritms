#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair;
using std::min, std::swap, std::endl;

inline int Median(vector<int>& array, int lft, int rgh) {
  for (int i = lft; i <= rgh; ++i) {
    for (int j = lft; j <= rgh - i - 1; ++j) {
      if (array[j] > array[j + 1]) {
        swap(array[j], array[j + 1]);
      }
    }
  }
  return array[(lft + rgh) / 2];
}

inline pair<int, int> Partition(vector<int>& array, int lft, int rgh, int pivot) {
  int indl = lft, indr;
  for (int i = lft; i <= rgh; ++i) {
    if (array[i] < pivot) {
      swap(array[i], array[indl]);
      ++indl;
    }
  }
  indr = indl;
  for (int i = indl; i <= rgh; ++i) {
    if (array[i] == pivot) {
      swap(array[i], array[indr]);
      ++indr;
    }
  }
  return {indl, indr - 1};
}

int QuickSelect(vector<int>& array, int lft, int rgt, int stat) {
  if (lft >= rgt) {
    return array[lft];
  }
  vector<int> array_medians;
  array_medians.reserve(rgt - lft + 1);
  while (lft != rgt) {
    array_medians.clear();
    for (int i = lft; i <= rgt; i += 5) {
      array_medians.push_back(Median(array, i, min(i + 4, rgt)));
    }
    int pivot = QuickSelect(array_medians, 0, array_medians.size() - 1, array_medians.size() / 2);
    pair<int, int> borders = Partition(array, lft, rgt, pivot);
    if (borders.first <= stat && borders.second >= stat) {
      return pivot;
    }
    if (stat < borders.first) {
      rgt = borders.first - 1;
    } else {
      lft = borders.second + 1;
    }
  }
  return array[lft];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int num, statistic, a0, a1;
  cin >> num >> statistic >> a0 >> a1;
  vector<int> array = {a0, a1};
  array.reserve(num + 1);
  for (int i = 2; i < num; i++) {
    array.push_back((array[i - 1] * 123 + array[i - 2] * 45) % (10000000 + 4321));
  }
  cout << QuickSelect(array, 0, num - 1, statistic - 1);
}