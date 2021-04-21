// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include <map>
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

#define M 32

// parse input file and create baskets vector
vector<set<string>> get_baskets(const string &file_name) {
  ifstream ifs(file_name);
  if (ifs.fail()) {
    cerr << "failed to open " << file_name << endl;
    exit(-1);
  }
  string line;
  string word;
  vector<set<string>> baskets;
  while (getline(ifs, line)) {
    stringstream iss(line);
    set<string> basket;
    while (iss >> word)
      basket.insert(word);
    baskets.push_back(basket);
  }
  return baskets;
}

// count the common items between two sets of words
size_t intersection_count(const set<string> &b1, const set<string> &b2) {
  vector<string> v;
  set_intersection(begin(b1), end(b1), begin(b2), end(b2),
                   std::back_inserter(v));
  return v.size();
}

/************** begin assignment **************/
// The "vector baskets" contains 5000 baskets of fruits, for example baskets[5]
// contains the following fruits {Coconut, Watermelon, Apricot}.
// The "vector preferences" contains preferences for fruits of 1000 people, for
// example the person in preferences[2] prefers {Strawberry, Melon, Avocado,
// Jackfruit}. Count the baskets for each person that have at least 3 fruits of
// a person's preferences. A basket can contain 3 to 7 different (unique)
// fruits. Also the preferences of the persons are between 3 to 7 different
// (unique) fruits. There are only 28 different fruits.

// A naive solution uses sets of strings to compute intersections between
// baskets and preferences.
// It also iterates over all baskets for each user.
vector<size_t> count_matches_naive(const vector<set<string>> &baskets,
                                   const vector<set<string>> &preferences) {
  // matches_count contains the matches count for each person
  vector<size_t> matches_count(
      preferences.size()); // create vector of all zeros
  // iterate over all persons
  for (size_t i = 0; i < preferences.size(); ++i) {
    // iterate over all possible baskets
    for (const auto &basket : baskets) {
      // if a basket contains at least 3 fruits of a person's preferences, then
      // we have a match
      if (intersection_count(preferences[i], basket) >= 3) {
        matches_count[i]++;
      }
    }
  }
  return matches_count;
}

// TODO: implement a "fast matches counter" using bit operations
// Voluntary (not required): If you are really interested in speeding up the
// code, also develop a strategy to avoid iterating over all the baskets each
// time. (In a real speed competition this would be essential for winning!)
vector<size_t> count_matches_fast(const vector<set<string>> &baskets,
                                  const vector<set<string>> &preferences) {
    /* the solution is much prettier and faster using a binary tree
    // since we do not have to compare a preference to every basket because we
    // can just go through the tree and if we find three ones we just take the
    // value of the node in the tree (the value is every preference that has this three ones)
    //
    // TODO: Code it if I have time
    */

    vector<size_t> matches_count(preferences.size());
    // map maps a string to an unique index in the bit_string
    // we will use it to create an order of the fruits using the index
    map<string, int> m;
    // right index is the index we start the indexing
    int rigth_index = 1;
    vector<bitset<M>> baskets_bool;
    for (int index = 0; index < baskets.size(); index++){
        // create an bitset consisting of zeroes, get the string at set of fruits at index
        // create an iterator to iterate over it
        bitset<M> new_basket(0);
        set<string> basket = baskets[index];
        set<string>:: iterator it;
        for (it = basket.begin(); it != basket.end(); it++){
            string ans = *it;
            // if the fruit is new we create a new map entry and increment the right index
            if (m[ans] == 0){
                m[ans] = rigth_index;
                rigth_index++;
            }
            // we set the bit in the new bitstring to 1 at the position we find in the map
            // -1 because the right index started at 1 (thats because we have to check m[ans]==0
            // so we cant set the right index to 0
            new_basket[m[ans] - 1] = 1;
        }
        // basket bool consists of 5000 bitsets
        // every bitset now represents the fruit basket at the index
        baskets_bool.push_back(new_basket);
    }

    // go through every preference and create the array according t the map
    // Since there might be fruits only in preferences and not in the baskets
    // we still have to append them to the map to not get an error
    // There is another Solution of course to just ignore this fruit because
    // obviously it does not matter since no basket contains the fruit
    for (int index = 0; index < preferences.size(); index++){
        bitset<M> new_pref(0);
        set<string> pref = preferences[index];
        set<string>:: iterator it;
        for (it = pref.begin(); it != pref.end(); it++){
            string ans = *it;
            if (m[ans] == 0){
                m[ans] = rigth_index;
                rigth_index++;
            }
            new_pref[m[ans] - 1] = 1;
        }
        // Go through every basket, compute the & relation between the bitstrings
        // and count the entries with one
        for (int j = 0; j < baskets_bool.size(); j++){
            if ((baskets_bool[j] & new_pref).count()>=3){
                matches_count[index]++;
            }
        }
    }
    // n be the number of entries in baskets, m be the number of entries in preferences
    // Time complexity: We need the time to create the basket bool set O(n)
    // after that we go through every pref and for the we go again through every basket
    // --> O(n * m)
    // Space complexity: We save a additional vector of sets of bitsets O(n)
    // and we save the matches count O(m)
    // For the preferences we only need constant space since we compare the bitset immedeatly
    // so we dont have to save them --> O(n + m) = O(n)
    return matches_count;
}
/*************** end assignment ***************/

int main() {
  vector<set<string>> baskets = get_baskets("baskets.txt");
  vector<set<string>> preferences = get_baskets("preferences.txt");

  TIMERSTART(naive)
  auto results_naive = count_matches_naive(baskets, preferences);
  TIMERSTOP(naive)

  TIMERSTART(fast)
  auto results_fast = count_matches_fast(baskets, preferences);
  TIMERSTOP(fast)

  assert(results_naive == results_fast);

  // naive: 3.24 seconds
  // fast: 0.1136 seconds

  printf("All Test passed!");
}
