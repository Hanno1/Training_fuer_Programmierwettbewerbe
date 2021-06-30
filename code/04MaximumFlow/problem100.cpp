#include <iostream>
#include <math.h>
#include <map>

using namespace std;

int compute_sol(int numb, int counter){
    counter++;
    if (numb == 1){ return counter; }
    if (floor(log2(numb)) == log2(numb)) { return counter + (int)log2(numb); }
    else{
        if (numb % 2 == 0){ compute_sol(numb / 2, counter); }
        else{ compute_sol(3 * numb + 1, counter); }
    }
}

int compute_big_solution(int mini, int maxi){
    if (mini < 0 || maxi < 0){
        cout << " Values have to be greater then 0! ";
        return -1;
    }
    int ret_max = 0;
    int solution;
    for (int index = mini; index <= maxi; index++){
        solution = compute_sol(index, 0);
        if (solution > ret_max){
            ret_max = solution;
        }
    }
    return ret_max;
}

void compute_maxi(){
    int a, b;
    // later implement a map for saving computed values
    map<int, int> m;
    int solution, maxi;
    while (cin >> a >> b){
        maxi = compute_big_solution(a, b);
        cout << a << " " << b << " " << maxi << "\n";
    }
}

int main(){
    // Test cases can be written here
    // compute_maxi();
    // additional Testcases
    {
        // same number
        cout << "10 10 " << compute_big_solution(10, 10) << "\n";
    }
    {
        // negative number
        cout << "-1 10 " << compute_big_solution(-1, 10) << "\n";
    }
    {
        // maxi < mini
        cout << "11 8 " << compute_big_solution(11, 8) << "\n";
    }
    {
        // many numbers
        cout << "1 1000 " << compute_big_solution(1, 1000) << "\n";
    }
    return 1;
}
