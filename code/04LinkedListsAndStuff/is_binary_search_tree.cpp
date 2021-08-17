    // enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <limits.h>
#include <iostream>

using namespace std;

struct Binary_Tree_Node {
  int data;
  Binary_Tree_Node *left;
  Binary_Tree_Node *right;
};

/************** begin assignment **************/
// Implement a function to check if a binary tree is a binary search tree (BST).
// A binary search tree satisfies the condition:
// left->data <= current->data < right->data.
// More precisely, the condition is that all left nodes must be less than or
// equal to the current node, which must be less than all the right nodes.
//
// Let's state again clearly the properties for a binary search tree:
// - The left subtree of a node contains only nodes with keys lesser than the
//   node's key.
// - The right subtree of a node contains only nodes with keys greater than the
//   node's key.
// - The left and right subtree each must also be a binary search tree.
//
// Be careful with duplicate values:
//    20                  20
//   /    valid BST         \    invalid BST
// 20                       20
//
// Optimal: O(n) time, if binary tree is balanced O(log n) space,
// worst case O(n) space
// --> It's challenging to do it optimal although there is not much code ...
// Try to solve it somehow.
//
// Before you start coding the function "is_binary_search_tree", write test
// cases in the main function to test the "is_binary_search_tree" function.
// Start with simple tests (like nullptr, one node, two nodes, three nodes)
// before writing more complicated tests.
// The style of writing tests before actual coding is called "Test-driven
// development" (TDD). You have indirectly familiarized yourself with it in the
// first exercises of this course, now you can try TDD yourself.
// (If you need an idea how to start writing tests, take a look at the main
// function in "is_symmetric.cpp".)

// write a helper function if you need to
// TODO: write code here
bool inorder_rek(Binary_Tree_Node *node, int mini, int maxi){
    // we compare the value in the node with min and max. it has to be greater
    // or equal to min and smaller then max. If this is the case we walk to the right
    // and to the left of the node and compare them again to min and max
    // if one of these comparisons fails we return false
    // if we go left, the data there has to be samller or equal then the data in our
    // current node, so we set the max to node->data
    // if we go right the value should be bigger, so we set the min to node->data.
    if (node){
        if (node->data <= mini || node->data > maxi){
            return false;
        }
        return inorder_rek(node->left, mini, node->data) && inorder_rek(node->right, node->data, maxi);
    }
    // if the node is null we just return true, since a empty node
    // is always a binary tree
    return true;
}

bool is_binary_search_tree(Binary_Tree_Node *node) {
    // we use recursion for the solution
    // for each node we give the minimum and maximum borders
    // in those the value of the node should be
    // since the root can be everything we initialise the values
    // min, max with the smallest and biggest possible integer
    bool res = inorder_rek(node, INT_MIN, INT_MAX);
    return res;
}

int main() {
    {
        assert(is_binary_search_tree(NULL) == true);
    }
    {
        Binary_Tree_Node head{10, nullptr};
        assert(is_binary_search_tree(&head) == true);
    }
    {
        Binary_Tree_Node head{5, nullptr};
        Binary_Tree_Node node_left{6, nullptr};
        head.left = &node_left;
        assert(is_binary_search_tree(&head) == false);
    }
    {
        Binary_Tree_Node head{5, nullptr};
        Binary_Tree_Node node_left{5, nullptr};
        head.left = &node_left;
        assert(is_binary_search_tree(&head) == true);
    }
    {
        Binary_Tree_Node head{5, nullptr};
        Binary_Tree_Node node_left{5, nullptr};
        Binary_Tree_Node node_right{5, nullptr};
        head.right = &node_right;
        head.left = &node_left;
        assert(is_binary_search_tree(&head) == false);
    }
    {
        Binary_Tree_Node head{5, nullptr};
        Binary_Tree_Node node_right{5, nullptr};
        head.right = &node_right;
        assert(is_binary_search_tree(&head) == false);
    }
    {
        Binary_Tree_Node head{10, nullptr};
        Binary_Tree_Node node_left{5, nullptr};
        Binary_Tree_Node node_left_right{20, nullptr};
        head.left = &node_left;
        node_left.right = &node_left_right;
        assert(is_binary_search_tree(&head) == false);
    }
    {
        Binary_Tree_Node head{10, nullptr};
        Binary_Tree_Node node_right{11, nullptr};
        Binary_Tree_Node node_right_left{10, nullptr};
        head.right = &node_right;
        node_right.left = &node_right_left;
        assert(is_binary_search_tree(&head) == false);
    }
    {
        Binary_Tree_Node head{10, nullptr};
        Binary_Tree_Node node_left{5, nullptr};
        Binary_Tree_Node node_left_right{10, nullptr};
        head.left = &node_left;
        node_left.right = &node_left_right;
        assert(is_binary_search_tree(&head) == true);
    }
    {
        Binary_Tree_Node head{12, nullptr};
        Binary_Tree_Node node_l{10, nullptr};
        Binary_Tree_Node node_l_l{9, nullptr};
        Binary_Tree_Node node_l_r{11, nullptr};
        Binary_Tree_Node node_r{14, nullptr};
        Binary_Tree_Node node_r_r{15, nullptr};
        Binary_Tree_Node node_r_l{13, nullptr};
        head.left = &node_l;
        head.right = &node_r;
        node_l.left = &node_l_l;
        node_l.right = &node_l_r;
        node_r.right = &node_r_r;
        node_r.left = &node_r_l;
        assert(is_binary_search_tree(&head) == true);
    }
    cout << "All tests passed!" << endl;
}
/*************** end assignment ***************/
