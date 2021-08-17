// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

/************** begin assignment **************/
// Find k (= 8) brightest stars in a stream. To measure the brightness we use
// the visual magnitude (Vmag). The smaller Vmag the brighter the star appears
// to us. If you want to know more about Vmag read this:
// https://de.wikipedia.org/wiki/Scheinbare_Helligkeit
// We work with the file stars.txt. Look at the structure of the file, because
// you will parse it line by line to extract information about the stars.

struct Star {
  string name; // name of the star
  double vmag; // stars brightness (the smaller vmag the brighter the star)
};

inline double string_to_double(const string &s) {
    // just converts a string to a double value
    bool is_negative = s[0] == '-';
    double result = 0;
    bool done = false;
    int counter = 0;
    // if integer is negative start with index i = 1
    for (size_t i = is_negative; i < s.size(); ++i) {
        if (s[i] == '.'){
            done = true;
            continue;
        }
        result = result * 10 + s[i] - '0';
        // if we are behind the comma we increment the counter by 1
        counter += done;
    }
    // shift the commy
    result = result * pow(10, -counter);
    // return result;
    return is_negative ? -result : result;
}

void print_vector(vector<Star> v){
    cout << "-------------" << endl;
    for (int j = 0; j < v.size(); j++){
        cout << v[j].vmag << endl;
    }
    cout << "-------------" << endl;
}

// You get the input file stream "ifs" to the "stars.txt" file and a parameter
// "k". "k" is the amount of the brightest stars we wan't to extract from the
// stream. Try to extract the "k" brightest stars in O(n * log(k)) time with
// O(log n) extra space.
vector<Star> find_k_brightest_stars(ifstream &ifs, const size_t k) {
    // "result" contains in the end the k brightest stars in sorted order
    // (brightest first)
    vector<Star> result;
    string word;
    // go through input stream until we reach the word "Date"
    // This is not really clean, we could go through the data
    // line by line and see if the first char is a #
    // but then we would have needed to split the first line
    // and this is annoying
    while (ifs >> word){
        if (word == "Date"){
            break;
        }
    }
    // comparator and max heap declaration
    auto comparator = [](const Star &a, const Star &b) { return a.vmag < b.vmag; };
    priority_queue<Star, vector<Star>, decltype(comparator)> max_heap(comparator);

    // counter signals the column we are in
    int counter = 0;
    Star new_star;
    while (ifs >> word){
        // the begin of the end section is marked with a #
        // if the counter is 0 we are in the first column
        // the name. The only Problem is, that the name can consist
        // of 2 words. Since the next entry always has 2 Characters
        // and a second name has more we just read the next word as long as
        // it has not 2 characters
        // we save the name in new_star.name
        // if the counter equals 7 we are in the brightness column
        // so we just convert the string to a double
        // if the max heap size is smaller then k we just push the star
        // if the max heap is already full we check the brightness of the first element.
        // if it is smaller or equal we push the star.
        // Since the root is the minimum bright star in the heap, we need to swap this
        // one with the new star
        //
        // else we go to the next element.
        // if the max heap exceeds k elements we pop the top element
        if (word[0] == '#'){
            break;
        }
        if (counter == 0){
            new_star.name = word;
            while (ifs >> word){
                if (word.size() == 2){
                    break;
                }
                new_star.name = new_star.name + " " + word;
            }
        }
        else if (counter == 7){
            new_star.vmag = string_to_double(word);
            if (max_heap.size() < k || new_star.vmag <= max_heap.top().vmag){
                max_heap.push(new_star);
                if (max_heap.size() > k){ max_heap.pop(); };
            }
        }
        counter = (counter + 1) % 13;
    }
    // create result, result will contain all entries of the heap
    while (!max_heap.empty()){
        result.push_back(max_heap.top());
        max_heap.pop();
    }
    // Since we use a max heap the result contains all entries in the wrong order
    // so just reverse the vector
    for (int first = 0, last = result.size()-1; first < last; first++, last--){
        swap(result[first], result[last]);
    }
    // return stars in sorted order (brightest first)*/
    return result;
}
/*************** end assignment ***************/

int main() {
  string path = "stars.txt";
  ifstream ifs{path}; // open file as a stream
  if (ifs.fail()) {
    cerr << "cannot find: " << path << endl;
    return 1;
  }
  size_t k = 8; // k brightest stars
  vector<Star> brightest_stars = find_k_brightest_stars(ifs, k);

  vector<Star> correct_stars{{"Sirius", -1.45},   {"Canopus", -0.62},
                             {"Arcturus", -0.05}, {"Rigil Kentaurus", -0.01},
                             {"Vega", 0.03},      {"Capella", 0.08},
                             {"Rigel", 0.18},     {"Procyon", 0.4}};

  // test correctness of solution
  assert(brightest_stars.size() == correct_stars.size());
  const double epsilon = 1.0e-12; // almost 0
  for (size_t i = 0; i < brightest_stars.size(); ++i) {
    assert(abs(brightest_stars[i].vmag - correct_stars[i].vmag) < epsilon);
    assert(brightest_stars[i].name == correct_stars[i].name);
  }

  // output brightest stars
  for (const auto &star : brightest_stars) {
    cout << star.name << endl;
    cout << star.vmag << endl;
    cout << endl;
  }
  cout << "Done!" << endl;
}
