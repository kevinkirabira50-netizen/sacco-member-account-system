#pragma once
#include "Member.h"
#include <algorithm>
#include <vector>

struct AVLNode {
    Member data;
    AVLNode* left = nullptr;
    AVLNode* right = nullptr;
    int height = 1;
    explicit AVLNode(const Member& m) : data(m) {}
};

// Self-balancing tree ordered by savings balance, then account number.
class AVLTree {
public:
    AVLTree() = default;
    AVLTree(const AVLTree&) = delete;             // copying would double-free nodes
    AVLTree& operator=(const AVLTree&) = delete;
    ~AVLTree() { destroy(root); }

    void insert(const Member& m) { root = insertRec(root, m); }
    void remove(const Member& m) { root = removeRec(root, m); }

    std::vector<Member> inOrder() const {
        std::vector<Member> out;
        inOrderRec(root, out);
        return out;
    }

    int getHeight() const { return height(root); }

    void clear() {
        destroy(root);
        root = nullptr;
    }

private:
    AVLNode* root = nullptr;

    static int height(const AVLNode* n) { return n ? n->height : 0; }

    static int getBalance(const AVLNode* n) {
        return n ? height(n->left) - height(n->right) : 0;
    }

    static void updateHeight(AVLNode* n) {
        n->height = 1 + std::max(height(n->left), height(n->right));
    }

    static AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        y->left = x->right;
        x->right = y;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    static AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        x->right = y->left;
        y->left = x;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Restores the AVL property at a node after an insert or delete below it.
    static AVLNode* rebalance(AVLNode* node) {
        updateHeight(node);
        int bal = getBalance(node);
        if (bal > 1) {                                   // left-heavy
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);     // left-right case
            return rotateRight(node);
        }
        if (bal < -1) {                                  // right-heavy
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);  // right-left case
            return rotateLeft(node);
        }
        return node;
    }

    static bool lessThan(const Member& a, const Member& b) {
        if (a.savingsBalance != b.savingsBalance)
            return a.savingsBalance < b.savingsBalance;
        return a.accountNo < b.accountNo;
    }

    static AVLNode* insertRec(AVLNode* node, const Member& m) {
        if (!node) return new AVLNode(m);
        if (lessThan(m, node->data))      node->left  = insertRec(node->left, m);
        else if (lessThan(node->data, m)) node->right = insertRec(node->right, m);
        else return node;                                // already present
        return rebalance(node);
    }

    static AVLNode* minNode(AVLNode* node) {
        while (node && node->left) node = node->left;
        return node;
    }

    static AVLNode* removeRec(AVLNode* node, const Member& m) {
        if (!node) return nullptr;
        if (lessThan(m, node->data))      node->left  = removeRec(node->left, m);
        else if (lessThan(node->data, m)) node->right = removeRec(node->right, m);
        else {
            if (!node->left || !node->right) {
                AVLNode* child = node->left ? node->left : node->right;
                delete node;
                return child;                            // may be nullptr
            }
            // Two children: replace with in-order successor, then delete it.
            AVLNode* successor = minNode(node->right);
            Member key = successor->data;                // copy, not a reference into a node we will delete
            node->data = key;
            node->right = removeRec(node->right, key);
        }
        return rebalance(node);
    }

    static void inOrderRec(const AVLNode* node, std::vector<Member>& out) {
        if (!node) return;
        inOrderRec(node->left, out);
        out.push_back(node->data);
        inOrderRec(node->right, out);
    }

    static void destroy(AVLNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};