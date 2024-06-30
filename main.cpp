#include "tree.hpp"

int main() {
    // Integer Tree
    Tree<int> int_tree;
    int_tree.add_root(1);
    int_tree.add_sub_node(1, 2);
    int_tree.add_sub_node(1, 3);
    int_tree.add_sub_node(2, 4);
    int_tree.add_sub_node(2, 5);
    int_tree.add_sub_node(3, 6);
    int_tree.add_sub_node(3, 7);

    cout << "Integer Tree Traversals:\n";

    cout << "Pre-Order: ";
    for (auto it = int_tree.begin_pre_order(); it != int_tree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-Order: ";
    for (auto it = int_tree.begin_post_order(); it != int_tree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-Order: ";
    for (auto it = int_tree.begin_in_order(); it != int_tree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS: ";
    for (auto it = int_tree.begin_bfs(); it != int_tree.end_bfs(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS: ";
    for (auto it = int_tree.begin_dfs(); it != int_tree.end_dfs(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap: ";
    for (auto it = int_tree.begin_heap(); it != int_tree.end_heap(); ++it) {
        cout << *it << " ";
    }
    cout << endl;



    cout << int_tree;

    // String Tree with 3 children per node
    Tree<string> string_tree(3);
    string_tree.add_root("animal");
    string_tree.add_sub_node("animal", "mammal");
    string_tree.add_sub_node("animal", "bird");
    string_tree.add_sub_node("animal", "reptile");
    string_tree.add_sub_node("mammal", "dog");
    string_tree.add_sub_node("mammal", "cat");
    string_tree.add_sub_node("mammal", "horse");
    string_tree.add_sub_node("bird", "sparrow");
    string_tree.add_sub_node("bird", "eagle");
    string_tree.add_sub_node("bird", "parrot");
    string_tree.add_sub_node("reptile", "snake");
    string_tree.add_sub_node("reptile", "lizard");
    string_tree.add_sub_node("reptile", "turtle");

    cout << "\nString Tree Traversals:\n";

    cout << "Pre-Order: ";
    for (auto it = string_tree.begin_pre_order(); it != string_tree.end_pre_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Post-Order: ";
    for (auto it = string_tree.begin_post_order(); it != string_tree.end_post_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "In-Order: ";
    for (auto it = string_tree.begin_in_order(); it != string_tree.end_in_order(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "BFS: ";
    for (auto it = string_tree.begin_bfs(); it != string_tree.end_bfs(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "DFS: ";
    for (auto it = string_tree.begin_dfs(); it != string_tree.end_dfs(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    cout << "Heap: ";
    for (auto it = string_tree.begin_heap(); it != string_tree.end_heap(); ++it) {
        cout << *it << " ";
    }
    cout << endl;



    cout << string_tree;

    return 0;
}