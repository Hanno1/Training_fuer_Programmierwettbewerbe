// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <random>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// helper macros for timings
#define TIMERSTART(label)                                                      \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label;       \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                       \
  b##label = std::chrono::system_clock::now();                                 \
  std::chrono::duration<double> delta##label = b##label - a##label;            \
  std::cout << #label << ": " << std::setprecision(4) << delta##label.count()  \
            << " seconds" << std::endl;

// obfuscated code to test your solution (ignore this)
uint32_t obfuscated(uint32_t o_abab67357a45d416943cc4921e785b98) {
  if (o_abab67357a45d416943cc4921e785b98 == UINT32_MAX) {
    return (0x0000000000000040u + 0x0000000000000220u + 0x0000000000000820u -
            0x0000000000000A60u);
  }
  uint32_t o_0eb3e51cabf50b3d1a61f2d180a35aae =
      (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
       0x0000000000000A00u);
  uint32_t o_f5042e0723caca6ff1c0cace5d4569f4 =
      (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
       0x0000000000000A00u);
  uint32_t o_c37bf56dd800ab9798b3f82e74a0f6aa =
      (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
       0x0000000000000A00u);
  while (o_abab67357a45d416943cc4921e785b98) {
    uint32_t o_be7578e6b3e06edeb987145645ba05ea =
        o_abab67357a45d416943cc4921e785b98 &
        (0x0000000000000002u + 0x0000000000000201u + 0x0000000000000801u -
         0x0000000000000A03u);
    o_abab67357a45d416943cc4921e785b98 >>=
        (0x0000000000000002u + 0x0000000000000201u + 0x0000000000000801u -
         0x0000000000000A03u);
    if (o_be7578e6b3e06edeb987145645ba05ea) {
      o_f5042e0723caca6ff1c0cace5d4569f4++;
    } else if ((o_abab67357a45d416943cc4921e785b98 &
                (0x0000000000000002u + 0x0000000000000201u +
                 0x0000000000000801u - 0x0000000000000A03u)) ==
               (0x0000000000000000u + 0x0000000000000200u +
                0x0000000000000800u - 0x0000000000000A00u)) {
      o_c37bf56dd800ab9798b3f82e74a0f6aa =
          (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
           0x0000000000000A00u);
      o_f5042e0723caca6ff1c0cace5d4569f4 =
          (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
           0x0000000000000A00u);
    } else {
      o_c37bf56dd800ab9798b3f82e74a0f6aa = o_f5042e0723caca6ff1c0cace5d4569f4;
      o_f5042e0723caca6ff1c0cace5d4569f4 =
          (0x0000000000000000u + 0x0000000000000200u + 0x0000000000000800u -
           0x0000000000000A00u);
    }
    o_0eb3e51cabf50b3d1a61f2d180a35aae =
        std::max(o_0eb3e51cabf50b3d1a61f2d180a35aae,
                 o_f5042e0723caca6ff1c0cace5d4569f4 +
                     o_c37bf56dd800ab9798b3f82e74a0f6aa);
  }
  return o_0eb3e51cabf50b3d1a61f2d180a35aae +
         (0x0000000000000002u + 0x0000000000000201u + 0x0000000000000801u -
          0x0000000000000A03u);
}

/************** begin assignment **************/
// You have an integer and you can flip exactly one bit from a 0 to a 1. Write
// code to find the length of the longest sequence of 1s you could create.
// Actually, that's a hard one!
// No complexity requirements, as long as you solve it somehow.
// If you fail that's ok. You should at least try.
// Optimal: O(b) time, O(1) space, b is the number of bits in the integer.

// EXAMPLE
// Input: 1775 (or: 11011101111)
// Output: 8

// Hints:
// - Start with a brute force solution. Can you try all possibilities?
// - Flipping a O to a 1 can merge two sequences of 1s --- but only if the two
//   sequences are separated by only one 0.
// - Each sequence can be lengthened by merging it with an adjacent sequence
//   (if any) or just flipping the immediate neighboring zero. You just need to
//   find the best choice.

uint32_t count_sequence(bitset<32> bits) {
    // returns the maximum number of concatenated Ones in the bitset
    uint32_t seq = 0;
    uint32_t max_seq = 0;
    for (int i = 0; i < 32; i++) {
        if (bits[i]){ seq++; }
        else {
            if (seq > max_seq){ max_seq = seq; }
            seq = 0;
        }
    }
    // important if the number ends with an 1
    if (seq > max_seq){ max_seq = seq; }
    return max_seq;
}

uint32_t max_flip_sequence_size_brute_force(uint32_t n) {
    // time complexity: b^2
    bitset<32> b = n;
    uint32_t max_length = count_sequence(b);
    for (int i = 0; i < 32; i++){
        if (!b[i]){
            // set the bit b to 1
            b[i] = 1;
            // Now count the sequence
            uint32_t length = count_sequence(b);
            if (length > max_length){
                max_length = length;
            }
            // reset bit to zero
            b[i] = 0;
        }
    }
    // the time complexity is O(b^2) in worst case
    // the space complexity is O(b)
    return max_length;
}

uint32_t max_flip_sequence_size(uint32_t numb) {
    // max_length is the length of all ones in a row
    // is reseted to 0 if we find a zero
    uint32_t max_length = 0;
    uint32_t length_seq = 0;
    // counted sequence is the length of the sequence we have at the moment
    // eventually with one bit flipped
    uint32_t counted_seq = 0;
    // first is true if we cant flip another bit sine we already flipped one
    bool first = false;
    // go through every bit
    for (int i = 0; i < 32; i++){
        if (!((numb >> i)&1)){
            // we go here if the least significant bit is set to 0
            // I know there are better solutions then shifting by i (for example shift every loop by 1)
            // but I cant implement it somehow
            // if first is false we just flip the 0 to 1, increment the counted sequence and
            // set first to true since we did flip a bit
            if (!first){
                counted_seq++;
                first=true;
            }
            else {
                // if we already flipped a bit we have to start over
                // if the counted sequence up to this point is more than the max sequence we
                // replace the max sequence
                // counted Sequence now is the sequence of ones up to this point
                // AND the zero we flipped so it is equal to length sequence + 1
                // finally we set the length sequence to 0 since our chain of ones is broken
                if (counted_seq > max_length){
                    max_length = counted_seq;
                }
                counted_seq = length_seq + 1;
                first=true;
            }
            length_seq = 0;
        }
        else{
            // if the least significant bit is 1 we just count both sequences up
            counted_seq++;
            length_seq++;
        }
    }
    // bitset consists only of 1
    if (counted_seq > max_length){
        max_length = counted_seq;
    }
    // the time complexity is O(b)
    // the space complexity is O(1) since we only need the given integer and shift it
    return max_length;
}
/*************** end assignment ***************/

int main() {
  // test correctness
  int n = 100000;
  auto rand_uint32 = bind(uniform_int_distribution<uint32_t>{0, UINT32_MAX},
                          default_random_engine{std::random_device{}()});

  cout << "Brute Force" << endl;
  TIMERSTART(naive);
  assert(max_flip_sequence_size_brute_force(UINT32_MAX) == 32);
  assert(max_flip_sequence_size_brute_force(0) == 1);
  assert(max_flip_sequence_size_brute_force(1) == 2);
  assert(max_flip_sequence_size_brute_force(2) == 2);
  assert(max_flip_sequence_size_brute_force(UINT32_MAX - 1) == 32);
  assert(max_flip_sequence_size_brute_force(UINT32_MAX << 2u) == 31);

  for (int i = 0; i < n; ++i) {
    // generate a random unsigned integer
    uint32_t num = rand_uint32();
    // test if your solution is correct
    assert(max_flip_sequence_size(num) == obfuscated(num));
  }
  TIMERSTOP(naive);

  cout << "cool Solution" << endl;
  TIMERSTART(fast);
  assert(max_flip_sequence_size(UINT32_MAX) == 32);
  assert(max_flip_sequence_size(0) == 1);
  assert(max_flip_sequence_size(1) == 2);
  assert(max_flip_sequence_size(2) == 2);
  assert(max_flip_sequence_size(UINT32_MAX - 1) == 32);
  assert(max_flip_sequence_size(UINT32_MAX << 2u) == 31);

  for (int i = 0; i < n; ++i) {
    // generate a random unsigned integer
    uint32_t num = rand_uint32();
    // test if your solution is correct
    assert(max_flip_sequence_size(num) == obfuscated(num));
  }
  TIMERSTOP(fast);
  cout << "all tests passed" << endl;
}
