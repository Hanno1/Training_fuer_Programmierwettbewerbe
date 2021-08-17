// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <map>

using namespace std;

/************** begin assignment **************/
// given a smaller string s and a bigger string b, design an algorithm to count
// all permutation appearances of the shorter string within the longer string
// assumption: only the 26 characters from a to z are allowed in both strings
//
// example:
// s = abbc
// b = cbabadcbbabbcba
//     cbab
//           cbba
//             abbc
//               bcba
// answer: permutations of the shorter string s
//         appear 4 times in the longer string b

// An obvious brute force solution is to generate all permutations of s and then
// look for each in b. Since there are S! permutations, this will take O(S! * B)
// time, where S is the length of s and B is the length of b. This works, but
// it's an extraordinarily slow algorithm. It's actually worse than an
// exponential algorithm. If s has 14 characters, that's over 87 billion
// permutations. Add one more character into s and we have 15 times more
// permutations. -->  implement an algorithm that needs at most O(B * S^2) time
//
// Before you start coding: Try to find the places where the permutations appear
// on your own. Observe how you do this. This will help you to develop a decent
// algorithm quite easily.#

int count_permutations(const string &s, const string &b) {
    int count = 0;
    // length is in the following code the length of the shorter string s
    int length = s.length();
    // if the first string is bigger than the later we just return 0 (no permutation possible)
    // if length == 0, then there are no permutations as well
    if (length > b.length() || length == 0){
        return count;
    }
    // to keep track of used characters we use dictionaries for string s and a part of string b
    map<char, int> dict_s;
    map<char, int> dict_b;
    // create a dictionary for s and at the same time one for the first letters of b
    for (int index = 0; index < length; index++){
        dict_s[s[index]]++;
        dict_b[b[index]]++;
        // if we have a unknown character we create a new entry in dict_s so the comparison works
        if (!dict_s[b[index]]){
            dict_s[b[index]] = 0;
        }
    }
    // if now the dictionaries are the same it is a permutation and we add 1 to the counter
    count += (dict_s == dict_b);
    // now we go through the string b letter by letter
    // we already initialised the dictionary and now all we have to do is to
    // remove the first letter (index) and add one letter at the end (index + length)
    // after that we compare again and increment the index later
    // if there is a new letter in b which didnt occur in s we still have to
    // create a empty dictionary entry in dict_s
    for (int index = 0; index < b.length() - length; index++){
        dict_b[b[index]]--;
        dict_b[b[index + length]]++;
        if (!dict_s[b[index + length]]){
            dict_s[b[index + length]] = 0;
        }
        count += (dict_s == dict_b);
    }
    // The time complexity of the algorithm is O(B) because we obviously go through
    // the string b. For every iteration we increment and decrement two numbers in
    // the dictionary
    // additionally we add eventually a new entry to dict_s
    // Since there is a finite number of characters the time for this is constant
    return count;
}

/*************** end assignment ***************/

int main() {
  // longer string is not a permutation of shorter string
  assert(count_permutations("cbabadcbbabbcba", "abbc") == 0);

  assert(count_permutations("xyz", "xyz") == 1);
  assert(count_permutations("xyz", "xzy") == 1);

  // no common permutations
  assert(count_permutations("abzc", "cbabadcbbabbcba") == 0);
  assert(count_permutations("", "cbabadcbbabbcba") == 0);
  assert(count_permutations("cbabadcbbabbcba", "") == 0);

  assert(count_permutations("abbc", "cbabadcbbabbcba") == 4);
  assert(count_permutations("abbc", "cbabadcbbabbcbabaabccbabc") == 7);

  string s = "cat";
  string b =
      "ydwztctaaaatxocabnpgcircgysctattacqtklzypxzqtvmwejcbvqhgljulsopnldoifefp"
      "kjnvipxkfnamdsacaxosactbrnioabfxixseyetzackxhmuqnpjwfzesjwktacatfqlxxmqb"
      "jnaceobxyvqahrjdofrdhhciatcgaoueybnqsklwhfkzvltcaiacty";
  assert(count_permutations(s, b) == 9);

  // some longer word
  s = "Psychotomimetic";
  b = "PsychoxtomimetiPsycotomimehticcunyaschPoetcomyimtixkjnvipxkfnamdsacaxosa"
      "ctbrnioabfxixseyetzackxhmuqunyaschePocomtyimti";
  assert(count_permutations(s, b) == 3);
  cout << "all tests passed" << endl;
  return 1;
}
