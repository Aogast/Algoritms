#include <iomanip>
#include <iostream>

using std::cout, std::cin, std::string, std::max;
const int kMin = -1000;
const int kMaxSize = 1000000;

class Tree {
  int64_t* tree_;
  int lft_;
  int rgt_;
  int64_t* indexes_;
  int real_size_;

public:
  Tree(int size) {
    lft_ = 1;
    real_size_ = 1;
    while (real_size_ < size + 1) {
      real_size_ *= 2;
    }
    rgt_ = real_size_;
    indexes_ = new int64_t[real_size_ + 1];
    tree_ = new int64_t[2 * real_size_];
    for (int i = 1; i <= real_size_; ++i) {
      indexes_[i] = real_size_ + i - 1;
    }
    for (int64_t i = 0; i < 2 * real_size_; ++i) {
      tree_[i] = kMin;
    }
  }

  void Update(int index, int value, bool f) {
    if (f) {
      tree_[indexes_[index]] = value;
      Update(indexes_[index] / 2, value, false);
      return;
    }
    if (index == 0) {
      return;
    }
    tree_[index] = max(tree_[index * 2], tree_[index * 2 + 1]);
    Update(index / 2, value, false);
  }

  int GetId(int lft, int rgt, int index, int value, int root) {
    int mid = (lft + rgt) / 2;
    if (lft == rgt && tree_[root] >= value) {
      return lft;
    }
    if (tree_[root] < value) {
      return -1;
    }
    if (index > mid) {
      return GetId(mid + 1, rgt, index, value, 2 * root + 1);
    }
    int left_id = GetId(lft, mid, index, value, 2 * root);
    if (left_id == -1) {
      return GetId(mid + 1, rgt, index, value, 2 * root + 1);
    }
    return left_id;
  }

  int GetLft() { return lft_; }

  int GetRgt() { return rgt_; }

  void Delete() {
    delete[] tree_;
    delete[] indexes_;
  }
};

int main() {
  int num, questions;
  cin >> num >> questions;
  Tree my_tree = Tree(kMaxSize);
  for (int index = 0; index < num; ++index) {
    int val;
    cin >> val;
    my_tree.Update(index + 1, val, true);
  }
  for (int iteration = 0; iteration < questions; ++iteration) {
    int type, index, rating;
    cin >> type >> index >> rating;
    if (type == 0) {
      my_tree.Update(index, rating, true);
    } else {
      cout << my_tree.GetId(my_tree.GetLft(), my_tree.GetRgt(), index, rating,
                            1)
           << "\n";
    }
  }
  my_tree.Delete();
}