#include <iostream>
#include <vector>
#include <limits>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Node {
    int id;
    double key;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool marked;
    int degree;

    Node(int id, double key) : id(id), key(key), parent(nullptr), child(nullptr), left(this), right(this), marked(false), degree(0) {}
};

class FibonacciHeap {
private:
    Node* minNode;
    unordered_map<int, Node*> nodeMap;

public:
    FibonacciHeap() : minNode(nullptr) {}

    bool isEmpty() const {
        return minNode == nullptr;
    }

    void insert(Node* node) {
        if (minNode == nullptr) {
            minNode = node;
        } else {
            minNode->left->right = node;
            node->right = minNode;
            node->left = minNode->left;
            minNode->left = node;
            if (node->key < minNode->key) {
                minNode = node;
            }
        }
        nodeMap[node->id] = node;
    }

    Node* extractMin() {
        Node* z = minNode;
        if (z != nullptr) {
            if (z->child != nullptr) {
                Node* child = z->child;
                do {
                    Node* next = child->right;
                    minNode->left->right = child;
                    child->right = minNode;
                    child->left = minNode->left;
                    minNode->left = child;
                    child->parent = nullptr;
                    child = next;
                } while (child != z->child);
            }
            z->left->right = z->right;
            z->right->left = z->left;
            if (z == z->right) {
                minNode = nullptr;
            } else {
                minNode = z->right;
                consolidate();
            }
            nodeMap.erase(z->id);
        }
        return z;
    }

    void decreaseKey(Node* node, double newKey) {
        if (newKey > node->key) {
            cerr << "New key is greater than current key." << endl;
            return;
        }
        node->key = newKey;
        Node* y = node->parent;
        if (y != nullptr && node->key < y->key) {
            cut(node, y);
            cascadingCut(y);
        }
        if (node->key < minNode->key) {
            minNode = node;
        }
    }

    void cut(Node* node, Node* parent) {
        if (node == node->right) {
            parent->child = nullptr;
        } else {
            node->right->left = node->left;
            node->left->right = node->right;
            if (node == parent->child) {
                parent->child = node->right;
            }
        }
        parent->degree--;
        insert(node);
        node->parent = nullptr;
        node->marked = false;
    }

    void cascadingCut(Node* node) {
        Node* parent = node->parent;
        if (parent != nullptr) {
            if (!node->marked) {
                node->marked = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }

    void consolidate() {
        int maxDegree = static_cast<int>(log2(nodeMap.size())) + 1;
        vector<Node*> aux(maxDegree, nullptr);
        Node* current = minNode;
        do {
            Node* x = current;
            current = current->right;
            int degree = x->degree;
            while (aux[degree] != nullptr) {
                Node* y = aux[degree];
                if (x->key > y->key) {
                    swap(x, y);
                }
                link(y, x);
                aux[degree] = nullptr;
                degree++;
            }
            aux[degree] = x;
        } while (current != minNode);

        minNode = nullptr;
        for (Node* y : aux) {
            if (y != nullptr) {
                if (minNode == nullptr) {
                    minNode = y;
                } else {
                    y->left->right = y->right;
                    y->right->left = y->left;
                    y->left = minNode->left;
                    y->right = minNode;
                    minNode->left->right = y;
                    minNode->left = y;
                    if (y->key < minNode->key) {
                        minNode = y;
                    }
                }
            }
        }
    }

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->marked = false;
    }

    Node* getMinNode() const {
        return minNode;
    }

    bool contains(int id) const {
        return nodeMap.find(id) != nodeMap.end();
    }

    Node* getNode(int id) const {
        if (contains(id)) {
            return nodeMap.at(id);
        }
        return nullptr;
    }
};

struct Point {
    int id;
    double x, y;

    Point(int id, double x, double y) : id(id), x(x), y(y) {}
};

class DijkstraEuclidean {
private:
    int V;
    vector<Point> points;
    vector<vector<pair<int, double>>> adjList;

public:
    DijkstraEuclidean(const vector<Point>& p) : points(p), V(p.size()), adjList(V) {}

    void addEdge(int u, int v, double w) {
        double weight = calculateEuclideanDistance(points[u], points[v]);
        adjList[u].emplace_back(v, weight);
    }

    double calculateEuclideanDistance(const Point& p1, const Point& p2) {
        return sqrt(pow
