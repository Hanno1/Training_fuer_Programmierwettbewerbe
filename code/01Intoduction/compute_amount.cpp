// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <chrono>
#include <iostream>
#include <map>

using namespace std;

// helper macros for timing
#define TIMERSTART(label)                                                      \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label;       \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                       \
  b##label = std::chrono::system_clock::now();                                 \
  std::chrono::duration<double> delta##label = b##label - a##label;            \
  std::cout << #label << ": " << delta##label.count() << " seconds"            \
            << std::endl;

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
    // we use a map with every possible result of a^3 + b^3 and the amount of
    // pairs which result in the same results
    // for every result we get we search in the map how many pairs already had
    // the same result
    // we increase the amount by 2 * m[result] + 1
    // the 1 comes because for every value of a or b the equation a^3+b^3=a^3+b^3
    // is correct. Every new pair we can put together with an old pair and
    // change the order
    // for example for the pairs (x,y) and (c,v) we can write x^3+y^3=c^3+v^3 or
    // c^3+v^3=x^3+y^3
    // Since the pair (v,c) is as well in m[result] we get every other possible combination

    int amount = 0;
    map<int, int> m;
    for (int a = 1; a <= n; ++a){
        for (int b = 1; b <= n; b++){
            int result = a * a * a + b * b * b;
            amount = amount + 2 * m[result] + 1;
            // increase the amount of pairs by 1
            m[result]++;
        }
    }
    // The Time complexity is O(n^2) because we have two for-loops iterating other every
    // number between 1 to n. Searching a hashmap is O(1) and we only have constant many operations.
    return amount;
}

int compute_amount_leif(const int n) {
    int amount = 0;
    // stores the values of a^3+b^3 and how often they appear
    map <int,int> known_values;
    for (int a = 1; a <= n; ++a) {
        for (int b = 1; b <= n; ++b) {
            // count the appearence
            known_values[a * a * a + b * b * b]++;
        }
    }
    // adding the possible combinations of those valuses
    // the formel is (n choose 2)*2
    for (const auto& [value, num] : known_values){
        amount = amount + num * (num-1);
    }
    return amount + n*n;
}
/*************** end assignment ***************/

int main() {
  // test correctness of implementation
  for (int n = 1; n < 100; ++n) {
    assert(compute_amount_brute_force(n) == compute_amount(n));
  }

  // compare execution times for n = 500
  int n = 200;
  cout << "n = " << n << endl;
  TIMERSTART(brute_force)
  int result_bf = compute_amount_brute_force(n);
  TIMERSTOP(brute_force)

  TIMERSTART(improved)
  int result = compute_amount(n);
  TIMERSTOP(improved)

  TIMERSTART(leif)
  int result2 = compute_amount_leif(n);
  TIMERSTOP(leif)

  assert(result_bf == result);
}
