#include <assert.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stdio.h>
#include <limits.h>
#include <math.h>

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

int iter(int n, int values[]){
    int matrix_sol[n*n];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            // i is the row and j the column
            if (j == 0 && i == 0){
                matrix_sol[0] = values[0];
            }
            else if (i == 0){
                // first row -> we cant go up
                matrix_sol[j] = values[j] + matrix_sol[j-1];
            }
            else if (j == 0){
                // first col -> cant go left
                matrix_sol[i*n] = values[i*n] + matrix_sol[(i-1)*n];
            }
            else{
                matrix_sol[i*n+j] = max(matrix_sol[i*n+j-1], matrix_sol[(i-1)*n+j]) + values[i*n+j];
            }
        }
    }
    // print_array(n*n, matrix_sol);
    return matrix_sol[n*n-1];
}

int rek(int n, int values[], int row, int col, vector<int> &saved){
    int res;
    if (row == 0 && col == 0){
        return values[0];
    }
    else if (row == 0){
        res = saved[col-1];
        if (!res){
            res = values[row*n+col] + rek(n,values,row,col-1,saved);
        }
    }
    else if (col == 0){
        res = saved[(row-1)*n];
        if (!res){
            res = values[row*n+col] + rek(n,values,row-1,col,saved);
        }
    }
    else{
        res = saved[row*n+col];
        if (!res){
            res = values[row*n+col] + max(rek(n,values,row-1,col,saved), rek(n,values,row,col-1,saved));
        }
        cout << "Last else: " << res << endl;
    }
    saved[row*n+col] = res;
    return res;
}

int rek_main(int n, int values[]){
    vector<int> vect(n*n,0);
    int res = rek(n,values,n-1,n-1,vect);
    return res;
}


int main() {
    int arr[] = {3,7,9,2,7,9,8,3,5,5,1,7,9,8,5,3,8,6,4,10,6,3,9,7,8};
    //int arr[] = {3,1,1,3};
    int res = rek_main(5, arr);
    cout << res << endl;
    return 1;
}
