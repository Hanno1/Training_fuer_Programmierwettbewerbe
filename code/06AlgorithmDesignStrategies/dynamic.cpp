#include <assert.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <cassert>

using namespace std;


// Dynamic programming is a very important problem solving strategy in
// competitive programming problems.
//
// In the backtracking assignment you had to work with code you didn't write.
// In this assignment you write everything yourself from the beginning.
//
// TODO: Read chapter 7 from the "Competitive Programmer’s Handbook"
// https://cses.fi/book/book.pdf --> pp. 65 - 76
// TODO: Choose one of the three following problems presented in the book:
//       - Longest increasing subsequence
//       - Paths in a grid
//       - Knapsack (all possible sums)
//       Implement for your chosen problem with dynamic programming
//       1. an iterative solution
//                and
//       2. a recursive solution
//       Test your implementations thoroughly. Start by writing your test cases
//       before you implement the algorithms.
//       Document your solutions thoroughly by writing meaningful comments.

/*************** Paths in a grid *******************/

void print_array(int n, int values[]){
    cout << "---------" << endl;;
    for (int i = 0; i < n; i++){
        cout << values[i] << endl;
    }
    cout << "---------" << endl;;
}

void print_vector(vector<int> vect){
    cout << "----------" << endl;
    for (int i = 0; i < vect.size(); i++){
        cout << vect[i] << endl;
    }
    cout << "----------" << endl;
}

int iter(int n, int values[]){
    // iterative is relatively simple
    // we do it inplace and just go through every grid part from left to right
    // in the first row we just take the element left and add the current element
    // in the first col we just take the element top and add the current element
    // in the normal grid we take the maximum of the top and left element
    // and add the current element
    //
    // it is possible to do this inplace if we go from left to right and then down into the next row
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // i is the row and j the column
            if (j == 0 && i == 0){}
            else if (i == 0){
                // first row -> we cant go up
                values[j] = values[j] + values[j-1];
            }
            else if (j == 0){
                // first col -> cant go left
                values[i*n] = values[i*n] + values[(i-1)*n];
            }
            else{
                values[i*n+j] = max(values[i*n+j-1], values[(i-1)*n+j]) + values[i*n+j];
            }
        }
    }
    return values[n*n-1];
}

int rek(int n, int values[], int row, int col, vector<int> &saved){
    // we need to view a few different cases:
    // if both indexes  are 0, we return the values of the first field in the grid
    // since values is a list we just take the first element and return it
    // if the row is 0, we just can go left, so we decrease the column and call rek again
    // if the col is 0, we can just go up, so we decrease the row and call rek
    // if we are in a normal field we take the maximum of the upper and left field
    // to compute this values we use rek
    // at the end we set the saved of row*n+col to the just computed value.
    // if we now call the function for the same row, col the values is not equal to zero
    // and we set it to this value
    int res;
    if (row == 0 && col == 0){
        res = values[0];
    }
    else if (row == 0){
        res = saved[col];
        if (!res){
            res = values[row*n+col] + rek(n,values,row,col-1,saved);
        }
    }
    else if (col == 0){
        res = saved[(row-1)*n + 1];
        if (!res){
            res = values[row*n+col] + rek(n,values,row-1,col,saved);
        }
    }
    else{
        res = saved[row*n+col];
        if (!res){
            res = values[row*n+col] + max(rek(n,values,row-1,col,saved), rek(n,values,row,col-1,saved));
        }
    }
    saved[row*n+col] = res;
    return res;
}

int rek_main(int n, int values[]){
    // the main recursion function
    // we need to catch the case n == 0 and only if this is not the case
    // we start the recursion
    // inside of the vector "vect" are our values we already computed
    // the recursion function needs the indexes of the place we want to compute
    // since we start at 0,0 we need to compute n-1,n-1
    if (n != 0){
        vector<int> vect(n*n,0);
        int res = rek(n,values,n-1,n-1,vect);
        return res;
    }
    return 0;
}


int main() {
    {
        int arr[] = {};
        int res_r = rek_main(0, arr);
        int res_i = iter(0, arr);
        assert(res_r == 0);
        assert(res_i == 0);
    }
    {
        int arr[] = {3};
        int res_r = rek_main(1, arr);
        int res_i = iter(1, arr);
        assert(res_r == 3);
        assert(res_i == 3);
    }
    {
        int arr[] = {3,7,9,2,7,9,8,3,5,5,1,7,9,8,5,3,8,6,4,10,6,3,9,7,8};
        int res_r = rek_main(5, arr);
        int res_i = iter(5, arr);
        assert(res_r == 67);
        assert(res_i == 67);
    }
    {
        int arr[]={1,1,9,1,1,1,2,1,1};
        int res_r = rek_main(3, arr);
        int res_i = iter(3,arr);
        assert(res_r == 13);
        assert(res_i == 13);
    }
    {
        int arr[]={1,1,9,2,1,1,3,1,1};
        int res_r = rek_main(3, arr);
        int res_i = iter(3,arr);
        assert(res_r == 13);
        assert(res_i == 13);
    }
    {
        int arr[]={1,1,9,4,3,1,4,4,1};
        int res_r = rek_main(3, arr);
        int res_i = iter(3,arr);
        assert(res_r == 14);
        assert(res_i == 14);
    }
    {
        int arr[]={1,1,3,2,8,2,3,1,1};
        int res_r = rek_main(3, arr);
        int res_i = iter(3,arr);
        assert(res_r == 14);
        assert(res_i == 14);
    }
    cout << "All Tests passed!" << endl;
    return 1;
}
