// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template <typename T> class Stack {
private:
    std::vector<T> data;
public:
    void push(T item) { this->data.push_back(item); }
    bool empty() { return this->data.empty(); }
    T top() { return this->data.back(); }
    void pop() { this->data.pop_back(); }
};

/************** begin assignment **************/
// In Reverse Polish Notation, the operators follow their operands; for
// instance, to add 3 and 4, one would write 3 4 + rather than 3 + 4. If there
// are multiple operations, operators are given immediately after their second
// operands; so the expression written 3 − 4 + 5 in conventional notation would be
// written 3 4 − 5 + in reverse Polish notation: 4 is first subtracted from 3,
// hen 5 is added to it. An advantage of reverse Polish notation is that it removes
// the need for parentheses that are required by infix notation. While 3 − 4 * 5
// can also be written 3 − (4 * 5), that means something quite different from (3 − 4) * 5.
// In reverse Polish notation, the former could be written 3 4 5 * −, which
// unambiguously means 3 (4 5 *) − which reduces to 3 20 − (which can further be reduced to -17);
// the latter could be written 3 4 − 5 * (or 5 3 4 − *, if keeping similar formatting),
// which unambiguously means (3 4 −) 5 *.
// see also: https://en.wikipedia.org/wiki/Reverse_Polish_notation
//
// Write a program that takes an arithmetical expression in Reverse Polish
// Notation (RPN) and returns the signed integer that the expression evaluates
// to.
// - allowed mathematical operators are: + - * /
// - numbers (operands) and operators are separated by spaces
// - use a "stringstream" for separating the input tokens (numbers and operators)
//   https://www.geeksforgeeks.org/stringstream-c-applications/
// - use a stack<int> for stacking the numbers
inline int string_to_int(const string &s) {
    // this function just converts an gib´ven string to
    // the corresponding integer
    // negative values has to be evaluated too
    bool is_negative = s[0] == '-';
    int result = 0;
    // if integer is negative start with index i = 1
    for (size_t i = is_negative; i < s.size(); ++i) {
        result = result * 10 + s[i] - '0';
    }
    return is_negative ? -result : result;
}

int eval_rpn(const string &rpn_expression) {
    // istringstream splits a given expression at the spaces
    // we can iterate over the result with get_line
    // the token is the entire line
    istringstream ss(rpn_expression);
    string token;

    Stack<int> s;

    while(std::getline(ss, token, ' ')) {
        // the token is a line of our splitted expression
        // it can be equal to either -,+,*,/ or its an Integer
        // our stack contains the values. if we get an operation token
        // we take the upper two numbers from the stack (pop), apply the
        // operation and pus the result
        // if the token is an normal string, we apply the string_to_int
        // function and push the result
        if (token == "-"){
            int one = s.top();
            s.pop();
            int two = s.top();
            s.pop();
            s.push(two - one);
        }
        else if (token == "+"){
            int one = s.top();
            s.pop();
            int two = s.top();
            s.pop();
            s.push(one + two);
        }
        else if (token == "/"){
            int one = s.top();
            s.pop();
            int two = s.top();
            s.pop();
            s.push(two / one);
        }
        else if (token == "*"){
            int one = s.top();
            s.pop();
            int two = s.top();
            s.pop();
            s.push(one * two);
        }
        else{
            s.push(string_to_int(token));
        }
    }
    return s.top();
}

/*************** end assignment ***************/

int main() {
  {
    string rpn_expression = "5";
    assert(eval_rpn(rpn_expression) == 5);
  }
  {
    string rpn_expression = "6 7 -";
    assert(eval_rpn(rpn_expression) == -1);
  }
  {
    string rpn_expression = "1 2 +";
    assert(eval_rpn(rpn_expression) == 3);
  }
  {
    string rpn_expression = "6 2 *";
    assert(eval_rpn(rpn_expression) == 12);
  }
  {
    string rpn_expression = "12 2 /";
    assert(eval_rpn(rpn_expression) == 6);
  }
  {
    string rpn_expression = "12 2 /";
    assert(eval_rpn(rpn_expression) == 6);
  }
  {
    string rpn_expression = "3 4 + 2 * 1 +"; // (3 + 4) * 2 + 1
    assert(eval_rpn(rpn_expression) == 15);
  }
  {
    string rpn_expression = "3 2 1 + *"; // (1 + 2) * 3
    assert(eval_rpn(rpn_expression) == 9);
  }
  {
    string rpn_expression =
        "4 2 5 * + 1 3 2 * + /"; // (4 + 2 * 5) / (1 + 3 * 2)
    assert(eval_rpn(rpn_expression) == 2);
  }
  {
    string rpn_expression =
        "2 5 * 4 + 3 2 * 1 + /"; // (2 * 5 + 4 ) / (3 * 2 + 1)
    assert(eval_rpn(rpn_expression) == 2);
  }
  {
    string rpn_expression = "3 5 6 + * 12 4 / -"; // ((5 + 6) * 3) - (12 / 4)
    assert(eval_rpn(rpn_expression) == 30);
  }
  {
    string rpn_expression =
        "100 10 2 -7 * * + 41 +"; // ((2 * (-7)) * 10) + 100 + 41
    assert(eval_rpn(rpn_expression) == 1);
  }
  {
    string rpn_expression = "-12 -56 -";
    assert(eval_rpn(rpn_expression) == 44);
  }
  cout << "all tests passed" << endl;
}
