#include <functional>
#include <sstream>
#include <iomanip>
#include "tree.hpp"

template <typename T>
TreeNode<T>::TreeNode(const T& key) : key(key) {}

template <typename T>
Tree<T>::Tree(int k) : maxChildren(k), root(nullptr) {}

// Destructor
template <typename T>
Tree<T>::~Tree() {
    std::function<void(shared_ptr<TreeNode<T>>)> delete_nodes = [&](shared_ptr<TreeNode<T>> node) {
        if (node) {
            for (auto& child : node->children) {
                delete_nodes(child);
            }
            node->children.clear();
        }
    };
    delete_nodes(root);
    root = nullptr;
}

template <typename T>
void Tree<T>::add_root(const T& key) {
    root = make_shared<TreeNode<T>>(key);
}

template <typename T>
void Tree<T>::add_sub_node(const T& parent_key, const T& child_key) {
    queue<shared_ptr<TreeNode<T>>> q;
    q.push(root);
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        if (node->key == parent_key) {
            if (node->children.size() < maxChildren) {
                node->children.push_back(make_shared<TreeNode<T>>(child_key));
                return;
            }
        }
        for (auto& child : node->children) {
            q.push(child);
        }
    }
}

// Pre-Order Iterator
template <typename T>
Tree<T>::PreOrderIterator::PreOrderIterator(shared_ptr<TreeNode<T>> root) {
    if (root) stk.push(root);
}

template <typename T>
bool Tree<T>::PreOrderIterator::operator!=(const PreOrderIterator& other) const {
    return !stk.empty();
}

template <typename T>
typename Tree<T>::PreOrderIterator& Tree<T>::PreOrderIterator::operator++() {
    auto node = stk.top();
    stk.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stk.push(*it);
    }
    return *this;
}

template <typename T>
T Tree<T>::PreOrderIterator::operator*() const {
    return stk.top()->key;
}

template <typename T>
typename Tree<T>::PreOrderIterator Tree<T>::begin_pre_order() {
    return PreOrderIterator(root);
}

template <typename T>
typename Tree<T>::PreOrderIterator Tree<T>::end_pre_order() {
    return PreOrderIterator(nullptr);
}

// Post-Order Iterator
template <typename T>
Tree<T>::PostOrderIterator::PostOrderIterator(shared_ptr<TreeNode<T>> root) {
    if (root) {
        stk1.push(root);
        while (!stk1.empty()) {
            auto node = stk1.top();
            stk1.pop();
            stk2.push(node);
            for (auto& child : node->children) {
                stk1.push(child);
            }
        }
    }
}

template <typename T>
bool Tree<T>::PostOrderIterator::operator!=(const PostOrderIterator& other) const {
    return !stk2.empty();
}

template <typename T>
typename Tree<T>::PostOrderIterator& Tree<T>::PostOrderIterator::operator++() {
    stk2.pop();
    return *this;
}

template <typename T>
T Tree<T>::PostOrderIterator::operator*() const {
    return stk2.top()->key;
}

template <typename T>
typename Tree<T>::PostOrderIterator Tree<T>::begin_post_order() {
    return PostOrderIterator(root);
}

template <typename T>
typename Tree<T>::PostOrderIterator Tree<T>::end_post_order() {
    return PostOrderIterator(nullptr);
}

// In-Order Iterator
template <typename T>
void Tree<T>::InOrderIterator::pushLeft(shared_ptr<TreeNode<T>> node) {
    while (node) {
        stk.push(node);
        node = !node->children.empty() ? node->children[0] : nullptr;
    }
}

template <typename T>
Tree<T>::InOrderIterator::InOrderIterator(shared_ptr<TreeNode<T>> root) {
    pushLeft(root);
}

template <typename T>
bool Tree<T>::InOrderIterator::operator!=(const InOrderIterator& other) const {
    return !stk.empty();
}

template <typename T>
typename Tree<T>::InOrderIterator& Tree<T>::InOrderIterator::operator++() {
    auto node = stk.top();
    stk.pop();
    if (node->children.size() > 1) {
        pushLeft(node->children[1]);
    }
    return *this;
}

template <typename T>
T Tree<T>::InOrderIterator::operator*() const {
    return stk.top()->key;
}

template <typename T>
typename Tree<T>::InOrderIterator Tree<T>::begin_in_order() {
    return InOrderIterator(root);
}

template <typename T>
typename Tree<T>::InOrderIterator Tree<T>::end_in_order() {
    return InOrderIterator(nullptr);
}

// BFS Iterator
template <typename T>
Tree<T>::BFSIterator::BFSIterator(shared_ptr<TreeNode<T>> root) {
    if (root) q.push(root);
}

template <typename T>
bool Tree<T>::BFSIterator::operator!=(const BFSIterator& other) const {
    return !q.empty();
}

template <typename T>
typename Tree<T>::BFSIterator& Tree<T>::BFSIterator::operator++() {
    auto node = q.front();
    q.pop();
    for (auto& child : node->children) {
        q.push(child);
    }
    return *this;
}

template <typename T>
T Tree<T>::BFSIterator::operator*() const {
    return q.front()->key;
}

template <typename T>
typename Tree<T>::BFSIterator Tree<T>::begin_bfs() {
    return BFSIterator(root);
}

template <typename T>
typename Tree<T>::BFSIterator Tree<T>::end_bfs() {
    return BFSIterator(nullptr);
}

// DFS Iterator
template <typename T>
Tree<T>::DFSIterator::DFSIterator(shared_ptr<TreeNode<T>> root) {
    if (root) stk.push(root);
}

template <typename T>
bool Tree<T>::DFSIterator::operator!=(const DFSIterator& other) const {
    return !stk.empty();
}

template <typename T>
typename Tree<T>::DFSIterator& Tree<T>::DFSIterator::operator++() {
    auto node = stk.top();
    stk.pop();
    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
        stk.push(*it);
    }
    return *this;
}

template <typename T>
T Tree<T>::DFSIterator::operator*() const {
    return stk.top()->key;
}

template <typename T>
typename Tree<T>::DFSIterator Tree<T>::begin_dfs() {
    return DFSIterator(root);
}

template <typename T>
typename Tree<T>::DFSIterator Tree<T>::end_dfs() {
    return DFSIterator(nullptr);
}

// Heap Iterator
template <typename T>
void Tree<T>::HeapIterator::buildHeap(shared_ptr<TreeNode<T>> node) {
    if (!node) return;
    heap.push_back(node);
    for (auto& child : node->children) {
        buildHeap(child);
    }
    make_heap(heap.begin(), heap.end(), [](const shared_ptr<TreeNode<T>>& a, const shared_ptr<TreeNode<T>>& b) {
        return a->key > b->key;
    });
}

template <typename T>
Tree<T>::HeapIterator::HeapIterator(shared_ptr<TreeNode<T>> root) : index(0) {
    buildHeap(root);
}

template <typename T>
bool Tree<T>::HeapIterator::operator!=(const HeapIterator& other) const {
    return index < heap.size();
}

template <typename T>
typename Tree<T>::HeapIterator& Tree<T>::HeapIterator::operator++() {
    if (!heap.empty()) {
        pop_heap(heap.begin(), heap.end(), [](const shared_ptr<TreeNode<T>>& a, const shared_ptr<TreeNode<T>>& b) {
            return a->key > b->key;
        });
        heap.pop_back();
    }
    return *this;
}

template <typename T>
T Tree<T>::HeapIterator::operator*() const {
    return heap.front()->key;
}

template <typename T>
typename Tree<T>::HeapIterator Tree<T>::begin_heap() {
    return HeapIterator(root);
}

template <typename T>
typename Tree<T>::HeapIterator Tree<T>::end_heap() {
    return HeapIterator(nullptr);
}

// Visualization using SFML

template <typename T>
int getTreeWidth(const shared_ptr<TreeNode<T>>& node) {
    if (!node) return 0;
    if (node->children.empty()) return 1;
    int width = 0;
    for (const auto& child : node->children) {
        width += getTreeWidth(child);
    }
    return width;
}

template <typename T>
void drawTree(sf::RenderWindow& window, const shared_ptr<TreeNode<T>>& node, int x, int y, int totalWidth) {
    if (!node) return;

    const int radius = 20;
    sf::CircleShape circle(radius);
    circle.setPosition(x - radius, y - radius);
    circle.setFillColor(sf::Color::Green);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(2);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) { // Ensure this path is correct
        std::cerr << "Could not load font\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::White);
    text.setPosition(x - radius / 2, y - radius / 2);

    std::ostringstream stream;
    if constexpr (std::is_floating_point<T>::value) {
        stream << std::fixed << std::setprecision(2) << node->key;
    } else {
        stream << node->key;
    }
    text.setString(stream.str());

    int childX = x - totalWidth / 2;

    for (const auto& child : node->children) {
        if (child) {
            int subtreeWidth = getTreeWidth(child) * (500 / (node->children.size() + 1));

            int childPosX = childX + subtreeWidth / 2;

            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x, y + radius), sf::Color::Red),
                    sf::Vertex(sf::Vector2f(childPosX, y + 100 - radius), sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
            drawTree(window, child, childPosX, y + 100, subtreeWidth);
            childX += subtreeWidth;
        }
    }

    window.draw(circle);
    window.draw(text);
}

template <typename T>
ostream& operator<<(ostream& os, const Tree<T>& tree) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tree Visualization");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        drawTree(window, tree.root, 400, 50, 800);
        window.display();
    }

    return os;
}
