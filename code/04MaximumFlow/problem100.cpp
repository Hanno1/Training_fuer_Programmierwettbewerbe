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

void compute_maxi(){
    int a, b;
    // later implement a map for saving computed values
    map<int, int> m;
    int solution, maxi;
    while (cin >> a >> b){
        maxi = 0;
        for (int index = a; index <= b; index++){
            solution = compute_sol(index, 0);
            if (solution > maxi){ maxi = solution; }
        }
        cout << a << " " << b << " " << maxi << "\n";
    }
}

int main(){
    // Test cases can be written here
    compute_maxi();
    return 1;
}
