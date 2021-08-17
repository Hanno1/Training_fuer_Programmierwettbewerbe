#include <iostream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;

void print_mat(vector<vector<int>> mat){
    cout << "Matrix: " << endl;
    for (int i = 0; i < mat.size(); i++){
        for (int j = 0; j < mat.size(); j++){
            cout << mat[i][j] << ",     ";
        }
        cout << endl;
    }
}

vector<int> get_path(vector<vector<int>> E, int s, int t){
    // use BFS to find a path from s to t
    // initialize number of nodes:
    int n = E.size();
    // initialize a FIFO-queue:
    queue<int> q;
    // initialize data structure of visitied nodes:
    // -1: unvisited, >= 0: in queue or visited, this also stores the index of the parent node
    vector<int> visited(n, -1);

    // start with node s, set s as its own parent to mark that it has been visited
    q.push(s);
    visited[s] = s;
    // go through the graph until queue is empty or t is reached:
    int current_node = s;
    while (!q.empty() && current_node != t) {
        // get first element from queue and remove it from queue:;
        current_node = q.front();
        q.pop();

        // add all unqueued neighbors of the current node to the queue:
        for (int i=0; i < n; i++) {
            if (E[current_node][i] > 0) {
                if (visited[i] < 0) {
                    q.push(i);
                    // set neighbor as queued:
                    visited[i] = current_node;
                }
            }
        }
    }

    // case no path to t was found:
    if (current_node != t){
        // return empty path
        return vector<int>(0);
    }

    // else: reconstruct path from s to t by parents stored in visited:
    current_node = t;
    // init the path, it only contains t at first:
    vector<int> path(1, t);
    while (!(current_node == s)){
        current_node = visited[current_node];
        path.insert(path.begin(), current_node);
    }
    return path;
}

int compute_MaxFlow_EK(vector<vector<int>> E, int s, int t){
    // initialize number of nodes:
    int n = E.size();
    // initialize the data structure for the remaining capacities:
    vector<vector<int>> remaining_capacities = E;

    // initialize some variables for computing the flow:
    bool finished = false;
    int total_flow_so_far = 0;
    vector<int> current_path;
    int flow_of_current_path;
    while (!finished){
        // look for a new path that uses the remaining capacities:
        current_path = get_path(remaining_capacities, s, t);
        if (current_path.empty()){
            // case no path was found. Algorithm is finished:
            finished = true;
            break;
        }
        // compute maximum flow on current path: find edge with minimum remaining capacity
        flow_of_current_path = remaining_capacities[current_path[0]][current_path[1]];
        // iterate through path, check each edge of path and find the minimum remaining capacity:
        for (int i=1; i<current_path.size()-1; i++){
            if (flow_of_current_path > remaining_capacities[current_path[i]][current_path[i+1]]){
                flow_of_current_path = remaining_capacities[current_path[i]][current_path[i+1]];
            }
        }
        // add new flow to total flow:
        total_flow_so_far += flow_of_current_path;
        // adjust the remaining capacities:
        for (int i=0; i<current_path.size()-1; i++){
            remaining_capacities[current_path[i]][current_path[i+1]] -= flow_of_current_path;
            remaining_capacities[current_path[i+1]][current_path[i]] += flow_of_current_path;
        }
    }
    return total_flow_so_far;
}

int max_bandwidth(){
    /*
    we basically search the minimum cut in the graph

    even though a edge is double sided it will always
    only be used in one direction!!! since if we would have a
    flow in the over direction as well, we would have the same result
    by subtracting the flow that already existed by the value
    of the counter flow

    We use the maximum flow algorithm from chapter 4
    */
    int network_number = 1;
    int node_number, a, b, c;
    while (cin >> node_number){
        if (node_number == 0){ break; }
        int start, finish, total_con;
        // adjazens matrix
        vector<vector<int>> adj_mat(node_number,vector<int> (node_number,0));
        cin >> start >> finish >> total_con;
        // read all edges
        for (int i = 0; i < total_con; i++){
            cin >> a >> b >> c;
            adj_mat[a-1][b-1]+=c;
            adj_mat[b-1][a-1]+=c;
        }
        // compute max flow, since the flow is equal to the minimum cut
        int sol = compute_MaxFlow_EK(adj_mat, start-1, finish-1);
        // print solution
        cout << "Network " << network_number << endl;
        cout << "The Bandwidth is: " << sol << endl;
        cout << "\n" << endl;
        network_number += 1;
    }
}

int main(){
    //max_bandwidth();
    // additional Test cases
    {
        vector<vector<int>> adj_mat = {{0,1},
                                        {1,0}};
        assert(compute_MaxFlow_EK(adj_mat, 0, 1)==1);
    }
    {
        vector<vector<int>> adj_mat = {{0,20,10},
                                        {20,0,5},
                                        {10,5,0}};
        assert(compute_MaxFlow_EK(adj_mat, 0, 2)==15);
    }
    {
        vector<vector<int>> adj_mat = {{0,20,10,0},
                                        {20,0,8,10},
                                        {10,8,0,20},
                                        {0,10,20,0}};
        assert(compute_MaxFlow_EK(adj_mat, 0, 3)==28);
    }
    {
        vector<vector<int>> adj_mat = {{0,20,10,10},
                                        {20,0,8,10},
                                        {10,8,0,20},
                                        {10,10,20,0}};
        assert(compute_MaxFlow_EK(adj_mat, 0, 3)==38);
    }
    {
        vector<vector<int>> adj_mat = {{0,12,10,5},
                                       {12,0,2,12},
                                       {10,2,0,2},
                                       {5,12,2,0}};
        assert(compute_MaxFlow_EK(adj_mat, 0, 3)==19);
    }
    cout << "All Tests passed!" << endl;
    return 1;
}
