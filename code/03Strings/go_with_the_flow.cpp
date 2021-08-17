// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

// helper macros for timings
#define TIMERSTART(label)                                                      \
  std::chrono::time_point<std::chrono::system_clock> a##label, b##label;       \
  a##label = std::chrono::system_clock::now();

#define TIMERSTOP(label)                                                       \
  b##label = std::chrono::system_clock::now();                                 \
  std::chrono::duration<double> delta##label = b##label - a##label;            \
  std::cout << #label << ": " << std::setprecision(4) << delta##label.count()  \
            << " seconds" << std::endl;

using namespace std;

struct Input {
  string text; // only words and spaces
  vector<size_t> word_sizes; // contains for each word in the text the amount of characters
  size_t longest_word; // amount of characters in the longest word
};

struct Result {
  size_t line_width;   // line width that produces the longest river
  size_t river_length; //  length of the longest river

  // for testing equality of results (ignore this)
  bool operator==(const Result &rhs) const {
    return line_width == rhs.line_width && river_length == rhs.river_length;
  }
};

// one could easily tune the io speed, but io is not critical here,
// so we don't care about its speed
Input get_input(const string &path) {
  ifstream ifs(path);
  if(ifs.fail()){
    throw runtime_error("cannot open file " + path + "\n");
  }
  size_t words;
  ifs >> words; // read amount of words
  vector<size_t> word_sizes; // contains the size of each word
  string word;
  string text;
  size_t longest_word = 0;
  while (ifs >> word){
    text += word + " ";
    word_sizes.push_back(word.size());
    longest_word = max(longest_word, word.size());
  }
  text.resize(text.size() - 1);
  return Input{move(text), move(word_sizes), longest_word};
}

Result get_result(const string &path) {
  size_t line_width;
  size_t river_length;
  ifstream ifs(path);
  if(ifs.fail()){
    throw runtime_error("cannot open file " + path + "\n");
  }
  ifs >> line_width;
  ifs >> river_length;
  return Result{line_width, river_length};
}

/************** begin assignment **************/

// Read the detailed description of the problem in "exercise_go_with_the_flow.pdf.
// This is an actual problem from the "icpc world finals 2018".
// So some of the best programmers tried to solve this under time pressure.
// If you need some hints, read: hints_for_solution.pdf
//
// If you are interested in seeing more icpc problems that were used in the
// world finals, see here:
// https://icpc.baylor.edu/worldfinals/problems
//
// In a real competition you would also have to write the boilerplate code
// to parse the input.
// You don't have to write the boilerplate code here to parse the input.
// Here, you try to accomplish the actual task of finding the line width
// where the input text contains the longest possible river.
// If more than one line width yields this maximum,
// take the shortest line width.
// In the original task there is a time limit of 12 seconds.
// You don't have a time limit.
// But be aware that naive solutions will run "forever".
void print_array(size_t vec[], size_t length){
    cout << "-------------" << endl;
    for (int j = 0; j < length; j++){
        cout << vec[j] << endl;
    }
    cout << "-------------" << endl;
}

void print_vector(vector<size_t> v){
    cout << "-------------" << endl;
    for (int j = 0; j < v.size(); j++){
        cout << v[j] << endl;
    }
    cout << "-------------" << endl;
}

size_t ret_max_river_test(vector<size_t> vec, size_t line_length, size_t &line_breaks, size_t &overset){
    size_t max_river = 0;
    size_t rivers[line_length];
    size_t rivers_new[line_length];
    // initialise Arrays
    for (int i = 0; i < line_length; i++){
        rivers[i] = 0;
        rivers_new[i] = 0;
    }

    size_t last_pos = 0;
    size_t pos = 0;
    print_vector(vec);
    for (int i = 0; i < vec.size(); i++){
        pos += vec[i];

        if (pos > line_length){
            line_breaks++;
            overset = min(overset, pos % line_length);
            pos = vec[i];
            last_pos = 0;

            for (int j = 0; j < line_length; j++){
                if (rivers_new[j] == 0 && rivers[j] > 0){
                    if (rivers[j] > max_river){
                        max_river = rivers[j];
                    }
                }
                rivers[j] = rivers_new[j];
                rivers_new[j] = 0;
            }
        }
        if (last_pos){
            rivers_new[last_pos] = max(max(rivers[last_pos-1], rivers[last_pos]), rivers[last_pos+1]) + 1;
        }
        pos++;
        last_pos = pos-1;
    }


    if (line_breaks == 0){
         for (int j = 0; j < line_length; j++){
            if (rivers_new[j] > max_river){
                max_river = rivers_new[j];
            }
         }
    }
    else{
        for (int j = 0; j < line_length; j++){
            if (rivers[j] > max_river){
                max_river = rivers[j];
            }
        }
    }
    line_breaks++;
    return max_river;
}

size_t ret_max_river(vector<size_t> vec, size_t line_length, size_t &line_breaks){
    // this function takes a text as a vector, a line_length and returns the
    // maximum sized river as well as the line_breaaks needed
    // we go through the text line by line (we use a counter for this)
    // and save the current rivers in a size_t array with line_length
    // places
    // if we find a space we just have to check this array at the 3 possible spaces
    // we take the maximum and add one to it.
    // We sadly cant do it in place since we need to access the array
    // for every space in the river (especially if we have a single char surrounded by 2 spaces)
    // so we need a second array (rivers_new)
    //****************//
    // if we find a space we cant add it to the array yet since the space can be the end of the line
    // and therefore does not count.
    // so we add an additional variable last_pos. If we find a space we update the array
    // at the position of last_pos and set last_pos to the current pos
    size_t max_river = 0;
    size_t rivers[line_length];
    size_t rivers_new[line_length];
    // initialise Arrays
    for (int i = 0; i < line_length; i++){
        rivers[i] = 0;
        rivers_new[i] = 0;
    }

    size_t last_pos = 0;
    size_t pos = 0;

    for (int i = 0; i < vec.size(); i++){
        // we add the current word length to our position
        pos += vec[i];
        // if now the pos is greater then the line_length we need
        // to begin a new line
        // which means to update the lists (rivers has to be rivers_new and
        // rivers_new has to contain zeros
        // if we find a river in river in rivers but none in rivers new we know that
        // a river has ended. Therefore we compare the length to the max_river_length
        // and update it in case its bigger
        if (pos > line_length){
            line_breaks++;
            // set the new position
            // since we had a linebreak its now exactly the length of the current word
            pos = vec[i];
            last_pos = 0;
            // but we created a new line so we have to compare the rivers
            // and replace rivers with new_rivers
            for (int j = 0; j < line_length; j++){
                if (rivers_new[j] == 0 && rivers[j] > 0){
                    if (rivers[j] > max_river){
                        max_river = rivers[j];
                    }
                }
                rivers[j] = rivers_new[j];
                rivers_new[j] = 0;
            }
        }
        if (i < vec.size() - 1){
            if (last_pos > 0){
                // set new river or update existing, +1 because we are in a new line
                rivers_new[last_pos] = max(max(rivers[last_pos-1], rivers[last_pos]), rivers[last_pos+1]) + 1;
            }
            // since we have had a space we now need to increment the position by one
            pos++;
            if (pos >= line_length){
                // go to the next line
                pos = 0;
                line_breaks++;
                // reset the new line
                for (int j = 0; j < line_length; j++){
                    // we check for a max river
                    if (rivers_new[j] == 0 && rivers[j] > max_river){
                        max_river = rivers[j];
                    }
                    rivers[j] = rivers_new[j];
                    rivers_new[j] = 0;
                }
            }
            last_pos = pos-1;
        }
    }
    // at the end we have to compare the max_river with the
    // max entry in rivers_new
    if (last_pos > 0){
        // set new river or update existing, +1 because we are in a new line
        rivers_new[last_pos] = max(max(rivers[last_pos-1], rivers[last_pos]), rivers[last_pos+1]) + 1;
    }
    for (int j = 0; j < line_length; j++){
        if (rivers_new[j] > max_river){
            max_river = rivers_new[j];
        }
        else if (rivers[j] > max_river){
            max_river = rivers[j];
        }
    }
    line_breaks++;
    return max_river;
}

Result find_longest_river(Input &input) {
    // You have the following information to design your algorithm.
    // You don't have to use everything, use only what you need.

    // the actual text, text is cleaned and contains only words and spaces
    const string& text = input.text;
    cout << text << endl;
    // amount of characters in the longest word in the text
    const size_t longest_word = input.longest_word;
    // contains for each word in the text the amount of characters (same order of words as in the text)
    const vector<size_t>& word_sizes = input.word_sizes;
    print_vector(word_sizes);
    // the amount of all words in the text
    const size_t words_count = input.word_sizes.size();

    // When I solved the problem, the following thing was important,
    // which is not clearly mentioned in the task description:
    // --> a new line never starts with a space
    //     (if you would have a space after a line break, ignore the space and continue with the next word)
    // should contain in the end the "minimal" optimal line width
    size_t line_width = longest_word; // line width can't be shorter than the longest word
    size_t river_length = 0;
    size_t line_breaks;
    size_t overset = 100;
    for (size_t i = longest_word; i <= longest_word * word_sizes.size()+1; i++){
        line_breaks = 0;
        size_t res = ret_max_river_test(word_sizes, i, line_breaks, overset);
        cout << overset << endl;
        if (res > river_length){
            river_length = res;
            line_width = i;
        }
        if (line_breaks <= river_length){
            break;
        }
    }
    cout << line_width << endl;
    cout << river_length << endl;
    return Result{line_width, river_length};
}

/*************** end assignment ***************/

int main() {
  // set data_dir to folder with test data
  string data_dir = "./F-gowithflow/";
  // test texts in task description
  {
    string text = "The Yangtze is the third longest "
                  "river in Asia and the longest in "
                  "the world to flow "
                  "entirely in one country";
    vector<size_t> word_sizes{3, 7, 2, 3, 5, 7, 5, 2, 4, 3, 3,
                              7, 2, 3, 5, 2, 4, 8, 2, 3, 7};
    Input input{move(text), move(word_sizes), 8};
    Result result = find_longest_river(input);
    Result correct_result{15, 5};
    assert(result == correct_result);
  }
  {
    string text = "When two or more rivers meet at "
                  "a confluence other than the sea "
                  "the resulting merged river takes "
                  "the name of one of those rivers";
    vector<size_t> word_sizes{4, 3, 2, 4, 6, 4, 2, 1, 10, 5, 4, 3, 3,
                              3, 9, 6, 5, 5, 3, 4, 2, 3,  2, 5, 6};
    Input input{move(text), move(word_sizes), 10};
    Result result = find_longest_river(input);
    Result correct_result{21, 6};
    assert(result == correct_result);
  }

  TIMERSTART(total_time_on_test_data);
  // test now the texts provided by the organisers of the competition
  {
    string secret = "secret-";
    for (int i = 1000; i < 1030; ++i) {
      string in = secret + to_string(i).substr(1, 4) + ".in";
      string ans = secret + to_string(i).substr(1, 4) + ".ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    string secret = "secret-";
    for (int i = 1031; i <= 1047; ++i) {
      string in = secret + to_string(i).substr(1, 4) + "-per.in";
      string ans = secret + to_string(i).substr(1, 4) + "-per.ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    string secret = "secret-";
    for (int i = 1048; i <= 1062; ++i) {
      string in = secret + to_string(i).substr(1, 4) + "-dk.in";
      string ans = secret + to_string(i).substr(1, 4) + "-dk.ans";
      Input input = get_input(data_dir + in);
      Result correct_result = get_result(data_dir + ans);
      Result result = find_longest_river(input);
      assert(result == correct_result);
      cout << in.data() << " passed\n";
    }
  }
  {
    Input input = get_input(data_dir + "secret-099-small.in");
    Result correct_result = get_result(data_dir + "secret-099-small.ans");
    Result result = find_longest_river(input);
    assert(result == correct_result);
    cout << "secret-099-small.in passed\n";
  }
  TIMERSTOP(total_time_on_test_data);

  return 0;
}
