#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair, std::min, std::swap;
using std::endl, std::string;

const int64_t kMaxsize = 100000;

class Heap {
  pair<int64_t, int64_t> heapy_[kMaxsize];
  int64_t index_in_heap_[kMaxsize];
  int64_t size_ = 0;

  void SiftUp(int64_t index) {
    if (index == 1) {
      return;
    }
    if (heapy_[index].first < heapy_[index / 2].first) {
      swap(heapy_[index], heapy_[index / 2]);
      swap(index_in_heap_[heapy_[index].second],
           index_in_heap_[heapy_[index / 2].second]);
      SiftUp(index / 2);
    }
  }

  void SiftDown(int64_t index) {
    if (index * 2 > size_) {
      return;
    }
    int64_t child = index * 2;
    if (index * 2 + 1 <= size_ &&
        heapy_[index * 2 + 1].first < heapy_[child].first) {
      child = index * 2 + 1;
    }
    if (heapy_[child].first < heapy_[index].first) {
      swap(heapy_[index], heapy_[child]);
      swap(index_in_heap_[heapy_[index].second],
           index_in_heap_[heapy_[child].second]);
      SiftDown(child);
    }
  }

public:
  void Insert(int64_t x, int64_t index) {
    ++size_;
    heapy_[size_].first = x;
    heapy_[size_].second = index;
    index_in_heap_[index] = size_;
    SiftUp(size_);
  }

  int64_t GetMin() { return heapy_[1].first; }

  void ExtractMin() {
    swap(heapy_[1], heapy_[size_]);
    swap(index_in_heap_[heapy_[1].second], index_in_heap_[heapy_[size_].second]);
    --size_;
    SiftDown(1);
  }

  void DecreaseKey(int64_t index, int64_t delta) {
    heapy_[index_in_heap_[index]].first -= delta;
    SiftUp(index_in_heap_[index]);
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t num_of_reqests;
  cin >> num_of_reqests;
  Heap My_Heap;
  for (int64_t index = 0; index < num_of_reqests; ++index) {
    string response;
    cin >> response;
    if (response == "insert") {
      int64_t x;
      cin >> x;
      My_Heap.Insert(x, index + 1);
    } else if (response == "getMin") {
      cout << My_Heap.GetMin() << "\n";
    } else if (response == "extractMin") {
      My_Heap.ExtractMin();
    } else {
      int64_t index_of_changing, delta;
      cin >> index_of_changing >> delta;
      My_Heap.DecreaseKey(index_of_changing, delta);
    }
  }
  return 0;
}