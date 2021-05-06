// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <iostream>

using namespace std;

/************** begin assignment **************/
// The input is an array of n unsigned integers, where A[i] denotes the maximum
// you can advance from index i.
// Write a function to compute the minimum number
// of steps needed to advance beyond the last index of an array. If it's
// impossible to go beyond the last index of an array, your function should
// return 0.
// Optimal: O(n) time, O(1) space

// EXAMPLES
// Input: < 4, 1, 2, 3, 0, 2, 0 >
// Output: 3

// Input: < 4, 1, 2, 3, 0, 1, 0 >
// Output: 0


size_t min_steps_beyond_last_index(const vector<size_t> &A) {
    size_t range = 0;
    size_t new_range = 0;
    size_t jumps = 0;
    size_t furthest = 0;
    for (int i = 0; i <= furthest && i < A.size(); i++){
        if (A[i] + i > furthest){
            new_range = A[i];
            furthest = A[i] + i;
        }
        if (range == 0){
            range = new_range;
            jumps++;
        }
        range--;
        new_range--;
    }
    if (furthest >= A.size()){ return jumps; }
    else{ return 0; }
}
/*************** end assignment ***************/

int main() {
{
    vector<size_t> v;
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {1};
    assert(min_steps_beyond_last_index(v) == 1);
  }
  {
    vector<size_t> v = {0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {3, 3, 1, 0, 2, 0, 1};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {3, 3, 1, 0, 2, 0, 0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {3, 2, 0, 0, 2, 0, 1};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {2, 4, 1, 1, 0, 2, 3};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  {
    vector<size_t> v = {2, 1, 1, 3, 0, 2, 0};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {4, 1, 2, 3, 0, 1, 0};
    assert(min_steps_beyond_last_index(v) == 0);
  }
  {
    vector<size_t> v = {4, 1, 2, 3, 0, 2, 0};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  {
    vector<size_t> v = {1, 1, 5, 1, 1, 1, 1, 4, 1, 1, 1};
    assert(min_steps_beyond_last_index(v) == 4);
  }
  {
    vector<size_t> v = {3, 0, 0, 4, 1, 1, 1, 4, 1, 1, 1};
    assert(min_steps_beyond_last_index(v) == 3);
  }
  cout << "all tests passed" << endl;
}
