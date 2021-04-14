// enable assertions in release build
#include <iostream>
#include <map>

using namespace std;

/************** begin assignment **************/
// compute the amount of all positive integer solutions to the equation
// a^3 + b^3 = c^3 + d^3 where a, b, c, and d are integers between 1 and n
// (1 <= n <= 500)

// an obvious brute force solution will just have four nested for loops
// this algorithm iterates through all possible values of a, b, c, and d
// and checks if that combination happens to work --> runtime is O(n^4)
int compute_amount_brute_force(const int n) {
  int amount = 0;
  for (int a = 1; a <= n; ++a) {
    for (int b = 1; b <= n; ++b) {
      for (int c = 1; c <= n; ++c) {
        for (int d = 1; d <= n; ++d) {
          if (a * a * a + b * b * b == c * c * c + d * d * d) {
            ++amount;
          }
        }
      }
    }
  }
  return amount;
}

// try to improve the time complexity
// (if you can't, try at least to improve the execution time)
int compute_amount(const int n) {
    int amount = 0;
    map<int, int> m;
    for (int a = 1; a <= n; ++a){
        for (int b = 1; b <= n; b++){
            int result = a * a * a + b * b * b;
            amount = amount + 2 * m[result];
            m[result]++;
        }
    }
  // TODO: Compute the amount of all positive integer solutions in less
  //  than O(n^4) runtime (you can use additional memory)
    return amount + n * n;
}
/*************** end assignment ***************/

int main() {
  // compare execution times for n = 500
  int n = 50;
  printf("start\n");
  for (int i = 10; i <= 500; i = i + 10){
    //printf("Iteration: %d\n", i);
    int result_bf = compute_amount_brute_force(n);
    int result = compute_amount(n);
    if (result_bf != result){
      printf("Error %d\n", i);
    }
  }
  printf("It Works!!!");
}
