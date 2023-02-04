#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair, std::min;
using std::swap, std::endl, std::string;

const int64_t kMaxsize = 200000;

class Heap {
  int64_t* heap_;
  int64_t size_;
  bool type_;

  bool Compare(int64_t var1, int64_t var2) {
    return ((type_ && var1 > var2) || (!type_ && var2 > var1));
  }

  void SiftUp(int64_t index) {
    if (index == 1) {
      return;
    }
    if (Compare(heap_[index], heap_[index / 2])) {
      swap(heap_[index], heap_[index / 2]);
      SiftUp(index / 2);
    }
  }

  void SiftDown(int64_t index) {
    if (index * 2 > size_) {
      return;
    }
    if (index * 2 + 1 > size_) {
      if (Compare(heap_[index * 2], heap_[index])) {
        swap(heap_[index * 2], heap_[index]);
        return;
      }
    }
    if (Compare(heap_[index * 2], heap_[index * 2 + 1])) {
      if (Compare(heap_[index * 2], heap_[index])) {
        swap(heap_[index * 2], heap_[index]);
        SiftDown(index * 2);
      }
    } else {
      if (Compare(heap_[index * 2 + 1], heap_[index])) {
        swap(heap_[index * 2 + 1], heap_[index]);
        SiftDown(index * 2 + 1);
      }
    }
  }

public:
  Heap(bool type_of_heap) {
    heap_ = new int64_t[kMaxsize];
    size_ = 0;
    type_ = type_of_heap;
  }

  void Insert(int64_t x) {
    ++size_;
    heap_[size_] = x;
    SiftUp(size_);
  }

  int64_t GetTop() { return heap_[1]; }

  int64_t GetSize() { return size_; }

  void ExtractTop() {
    heap_[1] = heap_[size_];
    --size_;
    SiftDown(1);
  }

  void Clear() { size_ = 0; }

  void Delete() { delete[] heap_; }
};

class SuperHeap {
  Heap RealHeapMin_ = Heap(false);
  Heap RealHeapMax_ = Heap(true);
  Heap DeleteHeapMin_ = Heap(false);
  Heap DeleteHeapMax_ = Heap(true);

public:
  void Insert(int64_t x) {
    RealHeapMin_.Insert(x);
    RealHeapMax_.Insert(x);
    cout << "ok\n";
  }

  void Clear() {
    RealHeapMin_.Clear();
    RealHeapMax_.Clear();
    DeleteHeapMin_.Clear();
    DeleteHeapMax_.Clear();
    cout << "ok\n";
  }

  int64_t GetSize() {
    return RealHeapMax_.GetSize() - DeleteHeapMax_.GetSize();
  }

  void Clean() {
    while (DeleteHeapMax_.GetSize() > 0 &&
           RealHeapMax_.GetTop() == DeleteHeapMax_.GetTop()) {
      RealHeapMax_.ExtractTop();
      DeleteHeapMax_.ExtractTop();
    }
    while (DeleteHeapMin_.GetSize() > 0 &&
           RealHeapMin_.GetTop() == DeleteHeapMin_.GetTop()) {
      RealHeapMin_.ExtractTop();
      DeleteHeapMin_.ExtractTop();
    }
  }

  void GetMax() {
    if (GetSize() == 0) {
      cout << "error\n";
    } else {
      Clean();
      cout << RealHeapMax_.GetTop() << "\n";
    }
  }

  void GetMin() {
    if (GetSize() == 0) {
      cout << "error\n";
    } else {
      Clean();
      cout << RealHeapMin_.GetTop() << "\n";
    }
  }

  void ExtractMax() {
    if (GetSize() == 0) {
      cout << "error\n";
    } else {
      GetMax();
      DeleteHeapMax_.Insert(RealHeapMax_.GetTop());
      DeleteHeapMin_.Insert(RealHeapMax_.GetTop());
    }
  }

  void ExtractMin() {
    if (GetSize() == 0) {
      cout << "error\n";
    } else {
      GetMin();
      DeleteHeapMax_.Insert(RealHeapMin_.GetTop());
      DeleteHeapMin_.Insert(RealHeapMin_.GetTop());
    }
  }

  void Delete() {
    RealHeapMax_.Delete();
    RealHeapMin_.Delete();
    DeleteHeapMax_.Delete();
    DeleteHeapMin_.Delete();
  }
};

int main() {
  SuperHeap heapy;
  int64_t num_of_commands;
  cin >> num_of_commands;
  for (int iteration = 0; iteration < num_of_commands; ++iteration) {
    string command;
    cin >> command;
    if (command == "insert") {
      int num;
      cin >> num;
      heapy.Insert(num);
    } else if (command == "extract_min") {
      heapy.ExtractMin();
    } else if (command == "extract_max") {
      heapy.ExtractMax();
    } else if (command == "get_min") {
      heapy.GetMin();
    } else if (command == "get_max") {
      heapy.GetMax();
    } else if (command == "size") {
      cout << heapy.GetSize() << "\n";
    } else if (command == "clear") {
      heapy.Clear();
    }
  }
  heapy.Delete();
}