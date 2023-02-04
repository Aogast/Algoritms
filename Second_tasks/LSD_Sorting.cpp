#include <iostream>
#include <vector>
using std::cout, std::cin, std::vector, std::pair, std::min;
using std::swap, std::endl, std::string;

int64_t ConvertToByte(int64_t number, int index_byte) {
  return ((number >> (index_byte * 8)) & 255);
}
int64_t* CounterLSDSort(int64_t* numbers, int64_t size, int index_byte) {
  int n = 257;
  int64_t* ans = new int64_t[size];
  int* array = new int[n];
  for (int i = 0; i < n; ++i) {
    array[i] = 0;
  }
  for (int i = 0; i < size; ++i) {
    ++array[ConvertToByte(numbers[i], index_byte) + 1];
  }
  for (int i = 1; i < n; ++i) {
    array[i] += array[i - 1];
  }
  for (int i = 0; i < size; ++i) {
    ans[array[ConvertToByte(numbers[i], index_byte)]] = numbers[i];
    ++array[ConvertToByte(numbers[i], index_byte)];
  }
  delete[] array;
  delete[] numbers;
  return ans;
}

int main() {
  int n;
  cin >> n;
  int64_t* numbers = new int64_t[n];
  for (int i = 0; i < n; ++i) {
    cin >> numbers[i];
  }
  for (int i = 0; i < 8; ++i) {
    numbers = CounterLSDSort(numbers, n, i);
  }
  for (int i = 0; i < n; ++i) {
    cout << numbers[i] << "\n";
  }
  delete[] numbers;
}