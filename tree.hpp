#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <algorithm>
#include <SFML/Graphics.hpp>

using namespace std;

template <typename T>
class TreeNode {
public:
    //the type of the key (generic)
    T key;
    //array of children (depends on maxChildren)
    vector<shared_ptr<TreeNode<T>>> children;

    TreeNode(const T& key);
    T get_value() const { return key; }
};

template <typename T>
class Tree {
private:
    shared_ptr<TreeNode<T>> root;
    int maxChildren;

public:
    //default children is 2 (binary tree)
    Tree(int k = 2);
    ~Tree();

    void add_root(const T& key);
    void add_sub_node(const T& parent_key, const T& child_key);
    shared_ptr<TreeNode<T>> getRoot() const { return root; }

    void print();

    class PreOrderIterator {
    private:
        stack<shared_ptr<TreeNode<T>>> stk;
    public:
        PreOrderIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const PreOrderIterator& other) const;
        PreOrderIterator& operator++();
        T operator*() const;
    };

    PreOrderIterator begin_pre_order();
    PreOrderIterator end_pre_order();

    class PostOrderIterator {
    private:
        stack<shared_ptr<TreeNode<T>>> stk1, stk2;
    public:
        PostOrderIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const PostOrderIterator& other) const;
        PostOrderIterator& operator++();
        T operator*() const;
    };

    PostOrderIterator begin_post_order();
    PostOrderIterator end_post_order();

    class InOrderIterator {
    private:
        stack<shared_ptr<TreeNode<T>>> stk;
        void pushLeft(shared_ptr<TreeNode<T>> node);
    public:
        InOrderIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const InOrderIterator& other) const;
        InOrderIterator& operator++();
        T operator*() const;
    };

    InOrderIterator begin_in_order();
    InOrderIterator end_in_order();

    class BFSIterator {
    private:
        queue<shared_ptr<TreeNode<T>>> q;
    public:
        BFSIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const BFSIterator& other) const;
        BFSIterator& operator++();
        T operator*() const;
    };

    BFSIterator begin_bfs();
    BFSIterator end_bfs();

    class DFSIterator {
    private:
        stack<shared_ptr<TreeNode<T>>> stk;
    public:
        DFSIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const DFSIterator& other) const;
        DFSIterator& operator++();
        T operator*() const;
    };

    DFSIterator begin_dfs();
    DFSIterator end_dfs();

    class HeapIterator {
    private:
        vector<shared_ptr<TreeNode<T>>> heap;
        size_t index;
        void buildHeap(shared_ptr<TreeNode<T>> node);
    public:
        HeapIterator(shared_ptr<TreeNode<T>> root);
        bool operator!=(const HeapIterator& other) const;
        HeapIterator& operator++();
        T operator*() const;
    };

    HeapIterator begin_heap();
    HeapIterator end_heap();

    template <typename U>
    friend void drawTree(sf::RenderWindow& window, const shared_ptr<TreeNode<U>>& node, int x, int y, int totalWidth);

    template <typename U>
    friend ostream& operator<<(ostream& os, const Tree<U>& tree);
};

#include "tree.tpp"

#endif // TREE_HPP