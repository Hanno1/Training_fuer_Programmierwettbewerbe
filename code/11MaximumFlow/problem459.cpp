#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

vector<int> breadth_first_search(vector<vector<int>> E, vector<int> visited, int start_node) {
    // slightly modified breath first search. Start the algorithm at the node start_node
    // and use the array visited
    // return the visited array to update it
    int n = E.size();
    queue<int> q;
    q.push(start_node);
    visited[start_node] = 1;
    int current_node;
    while (!q.empty()) {
        current_node = q.front();
        q.pop();
        for (int i=0; i<n; i++) {
            if (E[current_node][i] > 0) {
                if (visited[i] == 0) {
                    q.push(i);
                    visited[i] = 1;
                }
            }
        }
    }
    return visited;
}

int connection_counter(int nodes_counter, vector<vector<int>> adj_mat){
    // takes an adjazens matrix as well as the number of nodes.
    // counter contains the number of connectivity parts
    // visited keeps track of every visited node (gets updated in the breadth first search)
    // if there are no nodes we want to return 0
    // while there are zeros in visited we do a breadth search from one of the 0 nodes
    // set them to 1, search for another zero and increment the counter
    // if there is none we are done and return the counter
    int counter = 0;
    vector<int> visited(nodes_counter, 0);
    int start = 0;
    bool done = false;
    if (nodes_counter == 0){ done = true; }
    while (!done){
        visited = breadth_first_search(adj_mat, visited, start);
        done = true;
        for (int i = 0; i < nodes_counter; i++){
            if (visited[i] == 0){
                done = false;
                start = i;
                break;
            }
        }
        counter++;
    }
    return counter;
}

int string_to_int(string number){
    int new_number = 0;
    for (int index = 0; index < number.length(); index++){
        new_number = new_number * 10 + (int)number[index]-48;
    }
    return new_number;
}

void task_website(){
    int input;
    string real_input, edge, node;
    int node1, node2, node_counter;
    int res = 0;
    getline(cin, real_input);
    input = string_to_int(real_input);
    getline(cin, edge);
    for (int index = 0; index < input; index++){
        getline(cin, node);
        node_counter = (int)node[0] % 64;
        vector<vector<int>> adj_mat(node_counter, vector<int> (node_counter, 0));
        while (true){
            getline(cin, edge);
            if (edge.length() != 2){
                break;
            }
            node1 = (int)edge[0] % 65;
            node2 = (int)edge[1] % 65;
            adj_mat[node1][node2] = 1;
            adj_mat[node2][node1] = 1;
        }
        res = connection_counter(node_counter, adj_mat);
        cout << res << endl;
    }
}

int main(){
    {
        // example from the website
        vector<vector<int>> mat = {{0,1,0,0,0},{0,1,0,1,0},{0,0,0,0,1},{0,1,0,0,0},{0,0,1,0,0}};
        assert(connection_counter(5, mat) == 2);
    }
    {
        // no nodes
        assert(connection_counter(0, {}) == 0);
    }
    {
        // 5 nodes with no connections
        vector<vector<int>> mat = {{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
        assert(connection_counter(5, mat) == 5);
    }
    {
        // 5 nodes with all connections
        vector<vector<int>> mat = {{0,1,1,1,1},{1,0,1,1,1},{1,1,0,1,1},{1,1,1,0,1},{1,1,1,1,0}};
        assert(connection_counter(5, mat) == 1);
    }
    {
        // 5 nodes with B,D,E connected, rest not
        vector<vector<int>> mat = {{0,0,0,0,0},{0,0,0,1,1},{0,0,0,0,0},{0,1,0,0,1},{0,1,0,1,0}};
        assert(connection_counter(5, mat) == 3);
    }
    {
        // 5 nodes with B,D,E connected, and A,C
        vector<vector<int>> mat = {{0,0,1,0,0},{0,0,0,1,1},{1,0,0,0,0},{0,1,0,0,1},{0,1,0,1,0}};
        assert(connection_counter(5, mat) == 2);
    }
    {
        // 5 nodes with B,D,E connected, rest A, c and C with E
        vector<vector<int>> mat = {{0,0,1,0,0},{0,0,0,1,1},{1,0,0,0,1},{0,1,0,0,1},{0,1,1,1,0}};
        assert(connection_counter(5, mat) == 1);
    }
    cout << "All Tests passed!" << endl;
    return 1;
}
