#include <cmath>
#include <iostream>

using std::cout, std::cin;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number_of_mandragors, number_of_response, left_bond_of_response, right_bond_of_response;
  cin >> number_of_mandragors;
  double* array = new double[number_of_mandragors];
  double* prefix_array = new double[number_of_mandragors + 1];
  prefix_array[0] = 1;
  for (int index = 0; index < number_of_mandragors; ++index) {
    cin >> array[index];
  }
  for (int index = 1; index <= number_of_mandragors; ++index) {
    prefix_array[index] = pow(array[index - 1], static_cast<double>(1) / number_of_mandragors) * prefix_array[index - 1];
  }
  cin >> number_of_response;
  for (int iterstion = 0; iterstion < number_of_response; ++iterstion) {
    cin >> left_bond_of_response >> right_bond_of_response;
    cout.precision(10);
    cout << pow(prefix_array[right_bond_of_response + 1] / prefix_array[left_bond_of_response],
                static_cast<double>(number_of_mandragors) / static_cast<double>(right_bond_of_response
                                                                                - left_bond_of_response + 1))
         << "\n";
  }
  delete[] array;
  delete[] prefix_array;
}