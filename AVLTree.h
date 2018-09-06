#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {
private:
    struct Node{
        unsigned long long key;
        int h; //node height
        unsigned long long right_sum; //sum of all the nodes in the right subtree
        unsigned long long left_sum; //sum of all the nodes in the left subtree
        Node* parent;
        Node* left_child;
        Node* right_child;
        Node();
    };

    //Helper Functions
    Node* rotateRight(Node *x);
    Node* rotateLeft(Node *x);
    int getBalance(Node* root);
    void balanceNode(Node* &root);
    int getHeight(Node *root);
    Node* find (Node* root, unsigned long long k);
    void delNodes(Node* root);

public:
    Node* root;
    AVLTree();
    ~AVLTree();
    Node* insert (Node* &root, unsigned long long k);
    Node* del (Node* &root, unsigned long long k);
    Node* next (Node* root);
    bool find(unsigned long long k);
    unsigned long long sum(unsigned long long a, unsigned long long b);
};

#endif //AVLTREE_H