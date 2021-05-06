// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>

#include <bits/stdc++.h>

using namespace std;

/************** begin assignment **************/
// Sudoku is a popular logic-based combinatorial number placement puzzle. The
// objective is to fill a 9 x 9 grid with digits subject to the constraint that
// each column, each row, and each of the nine 3 x 3 sub-grids that compose the
// grid contains unique integers.
// In case you need an introduction to Sudoku:
// https://www.learn-sudoku.com/sudoku-rules.html

// We define three different states in which a Sudoku board can be.
enum class state { invalid, valid, solved };
// invalid --> board violates the Sudoku rules
// valid --> board corresponds to the Sudoku rules
// solved --> the puzzle is solved

// Note that the only valid characters are "123456789" and the space ' ' meaning
// an empty field.
// Note that we do not care if a board can actually be solved, we only check if
// it violates the rules, or is valid, or is in a solved state.
// Of course a solved board is also valid, but we only return solved.

// TODO: implement a function that returns the state of a Sudoku board
state compute_sudoku_state(const string &board) {
    if (board.size() != 81){
        return state::invalid;
    }
    bitset<81> rows = 0;
    bitset<81> cols = 0;
    bitset<81> blocks = 0;
    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++){
            int val = board[r * 9 + c] - '0';
            if ((val < 10 && val > 0) || val == ' '){
                // check row
                if (rows[r * 9 + val]){ return state::invalid; }
                else{ rows[r * 9 + val] = 1; }

                // check column
                if (cols[c * 9 + val]){ return state::invalid; }
                else{ cols[c * 9 + val] = 1; }

                // check blocks
                if (blocks[(3 * (r / 3) + (c / 3)) * 9 + val]){return state::invalid; }
                else{ blocks[(3 * (r / 3) + (c / 3)) * 9 + val] = 1; }
            }
            else if (val != -16) { return state::invalid; }
        }
    }
    if (rows.count() == 81){
        return state::solved;
    }
    return state::valid;
}
/*************** end assignment ***************/

int main() {
    {
    string board = "274935168"
                   "198726435"
                   "563814729"
                   "356187294"
                   "419562873"
                   "782493516"
                   "821349657"
                   "947651382"
                   "63527894"; // invalid size
    assert(compute_sudoku_state(board) == state::invalid);
    }
    {
    string board = "274935168"
                   "198726435"
                   "563814729"
                   "356187294"
                   "419562873"
                   "782493516"
                   "821349657"
                   "947651382"
                   "6352789412"; // invalid size
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "   9  1 4"
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   " : 4  631" // |:|
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "586937124"
                   "129654783"
                   "734182596"
                   "372819465"
                   "865743912"
                   "491526308" // |0|
                   "618375249"
                   "257498631"
                   "943261857";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "586937124"
                   "129654783"
                   "734182596"
                   "372819465"
                   "865743912"
                   "4915263a8" // |a|
                   "618375249"
                   "257498631"
                   "943261857";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "145673829"
                   "389215674"
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436218"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::solved);
  }
  {
    string board = "495287163"
                   "821369547"
                   "367145298"
                   "179854632"
                   "634972815"
                   "582613974"
                   "216438759"
                   "953721486"
                   "748596321";
    assert(compute_sudoku_state(board) == state::solved);
  }
  {
    string board = "145673829"
                   "381215674" // 38|1|
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436218"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "145673829"
                   "38 215674"
                   "762948135"
                   "296157483"
                   "814369752"
                   "573824961"
                   "957436 18"
                   "628591347"
                   "431782596";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  4 7  6"
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 192 "
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  6 7  6" // 9  |6|
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 192 "
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = " 4    897"
                   " 379   52"
                   "8 27  3  "
                   "9  4 7  6"
                   " 8  9  3 "
                   "6 3 18 49"
                   "  83 193 " //   83 19|3|
                   "26   4  3"
                   " 142596  ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "   9  1 4"
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   "   4  631"
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "2  9  1 4" // |2|
                   " 2  5 7  "
                   "     25 6"
                   "    194 5"
                   " 6574391 "
                   "4 1 26  8"
                   " 18375 4 "
                   "   4  631"
                   " 4  6    ";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         "
                   "         ";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   4     "
                   "    5    "
                   "     6   "
                   "      7  "
                   "       8 "
                   "        9";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::valid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "      32 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1    7"
                   "    2 7  "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "  4   1  "
                   " 4     2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2 1     "
                   "  3      "
                   "   1     "
                   "    2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   "   1 6   "
                   "   62    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  {
    string board = "1        "
                   " 2       "
                   "  3      "
                   " 5 1     "
                   "5   2    "
                   "     3   "
                   "      1  "
                   "       2 "
                   "        3";
    assert(compute_sudoku_state(board) == state::invalid);
  }
  cout << "all tests passed" << endl;
}
