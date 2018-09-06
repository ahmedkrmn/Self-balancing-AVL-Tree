#include "AVLTree.h"
#include <iostream>

AVLTree::Node::Node() {
    key = 0;
    h = 1;
    right_sum=0;
    left_sum =0;
    parent = nullptr;
    left_child = nullptr;
    right_child = nullptr;
}
AVLTree::~AVLTree() {
    delNodes(root);
}
AVLTree::AVLTree() {
    root=nullptr;
}

AVLTree::Node* AVLTree::rotateLeft(AVLTree::Node *x) {
    Node* y = x->right_child;
    Node* T = y->left_child;

    //Set T as the right child of x, and update the right_sum of x
    x->right_child = T;
    if(T) x->right_sum = T->key+T->right_sum+T->left_sum;
    else x->right_sum=0;

    //Set x as the left child of y, and update the left_sum of y
    y->left_child = x;
    y->left_sum = x->key+x->right_sum+x->left_sum;

    //Update the parents of all nodes
    y->parent = x->parent;
    if(T) T->parent = x; //check if T is not nullptr
    x->parent = y;

    //Update the height of affected nodes
    x->h = 1+std::max(getHeight(x->right_child), getHeight(x->left_child));
    y->h = 1+std::max(getHeight(y->right_child), getHeight(y->left_child));

    //return the new root
    return y;
}

AVLTree::Node* AVLTree::rotateRight(AVLTree::Node *x) {
    Node* y = x->left_child;
    Node* T = y->right_child;

    x->left_child = T;
    if(T) x->left_sum = T->key+T->right_sum+T->left_sum;
    else x->left_sum=0;

    y->right_child = x;
    y->right_sum = x->key+x->right_sum+x->left_sum;

    y->parent = x->parent;
    if(T) T->parent = x;
    x->parent = y;

    x->h = 1+std::max(getHeight(x->right_child), getHeight(x->left_child));
    y->h = 1+std::max(getHeight(y->right_child), getHeight(y->left_child));

    return y;
}

int AVLTree::getBalance(AVLTree::Node *root) {
    //Calculate the balance factor of node (root)
    if (root== nullptr) return 0;
    return getHeight(root->left_child) - getHeight(root->right_child);
}

void AVLTree::balanceNode(AVLTree::Node *&root) {
    //Balance the node (root) through the appropriate selection of rotations
    int balance=getBalance(root), leftBalance=getBalance(root->left_child), rightBalance=getBalance(root->right_child);

    //Right Right case
    if(balance < -1 && rightBalance <= 0){
        root = rotateLeft(root);
    }
        //Right Left case
    else if(balance < -1 && rightBalance >0){
        root->right_child = rotateRight(root->right_child);
        root = rotateLeft(root);
    }
        //Left Left case
    else if(balance > 1 && leftBalance>=0){
        root = rotateRight(root);
    }
        //Left Right case
    else if(balance >1 && leftBalance <0){
        root->left_child=rotateLeft(root->left_child);
        root = rotateRight(root);
    }
}

int AVLTree::getHeight(AVLTree::Node *root) {
    //return the height of the node (root)
    if(root == nullptr) return 0;
    return root->h;
}

AVLTree::Node* AVLTree::find(AVLTree::Node *root, unsigned long long k) {
    //return a pointer to the node whose key is "k", if not found, return null
    if (root== nullptr) return nullptr;
    if (k<root->key && root->left_child != nullptr) return find(root->left_child, k);
    else if(k>root->key && root->right_child != nullptr) return find(root->right_child, k);
    else return root;
}

void AVLTree::delNodes(AVLTree::Node *root) {
    //delete all the nodes in the tree
    if(root== nullptr) return;
    delNodes(root->left_child);
    delNodes(root->right_child);
    delete root;
}


AVLTree::Node* AVLTree::insert(AVLTree::Node* &root, unsigned long long k) {
    //insert a node in the tree and balance the tree if any imbalances occur.
    if (root == nullptr){
        root = new Node;
        root->key = k;
    }
    if(k<root->key) {
        root->left_child = insert(root->left_child, k);
        //Update the parent of the child
        root->left_child->parent = root;
        //Update the left_sum of the node (root)
        root->left_sum = root->left_child->key+root->left_child->left_sum+root->left_child->right_sum;
    }
    if(k>root->key){
        root->right_child = insert(root->right_child, k);
        //Update the parent of the child
        root->right_child->parent = root;
        //Update the right_sum of the node (root)
        root->right_sum = root->right_child->key+root->right_child->left_sum+root->right_child->right_sum;
    }
    //update the height of the node (root)
    root->h = 1+std::max(getHeight(root->right_child), getHeight(root->left_child));

    //balance the node (root)
    balanceNode(root);

    return root;
}

AVLTree::Node* AVLTree::del(AVLTree::Node* &root, unsigned long long k) {
    //insert a node in the tree and balance the tree if any imbalances occur.
    if(root == nullptr) return root;
    if (k<root->key) {
        root->left_child=del(root->left_child, k);
        Node* left = root->left_child;
        //Update the left_sum of the node (root)
        if(left) root->left_sum=left->key + left->right_sum + left->left_sum;
        else root->left_sum=0;
    }
    if (k>root->key) {
        root->right_child=del(root->right_child, k);
        Node* right = root->right_child;
        //Update the right_sum of the node (root)
        if(right) root->right_sum = right->key + right->left_sum +right->right_sum;
        else root->right_sum = 0;
    }
    /*This condition should be the last, if you're not using if else. If the node to be deleted has two children,
     *it will be replaced by the node following it which has a larger key.
     *If this condition was the first, it will the enter the condition (k<root->key) wasting unnecessary function calls.
     */
    if (k == root->key){
        //node has no children
        if(root->left_child == nullptr && root->right_child==nullptr) {
            delete root;
            /*root must be set to nullptr just in case the node to
             *be deleted is the only node in the tree as the root node is passed by reference when the function
             *delete is called, that's why we need to set it to nullptr.
             *
             * Otherwise, it doesn't matter since when the function returns to the call before it on the stack
             * the appropriate child will be set to nullptr if we just return nullptr.
             */
            root = nullptr;
            return root;
        }

            //node has only one child
        else if (root->left_child == nullptr) {
            Node* temp = root->right_child;
            temp->parent = root->parent;
            delete root;
            //once again we are passing by reference, that's why we set root to temp instead of directly returning temp
            root = temp;
            return root;
        }
        else if(root->right_child== nullptr){
            Node* temp = root->left_child;
            temp->parent = root->parent;
            delete root;
            root = temp;
            return root;
        }

            //node has two children
        else{
            Node* nextNode = next(root);
            root->key = nextNode->key;

            /*  It's guaranteed that the nextNode will be in the right subtree
             *  Setting nextNode = del(nextNode, nextNode->key) won't work because even if the nextNode pointer is set
             *  to null after deletion, it's still not updated to null in its parent, therefore, the parent will be
             *  pointing to an invalid location in memory.
             *  Also doing so won't balance the tree as the deletion process won't recurse back to the current node.
             */

            // Replace nextNode = del(nextNode, nextNode->key); with the following:
            root->right_child = del(root->right_child, root->key);

            /*Don't forget to update the right_sum of the current node
             *Use the code below instead of root->right_sum-=nextNode->key because nextNode will already be deleted !
             */
            root->right_sum-=root->key;
        }
    }
    //Update the height of the node (root)
    root->h = 1+std::max(getHeight(root->right_child), getHeight(root->left_child));

    //Balance the node (root)
    balanceNode(root);

    return root;
}

AVLTree::Node* AVLTree::next(AVLTree::Node *root) {
    //return a pointer to the first node with key "k" larger than root->key, if no such node exist, return null.

    if(root->right_child) {
        root = root->right_child;
        while (root->left_child) root = root->left_child;
        return root;
    }
    while(root->parent && root->parent->key<root->key) root=root->parent;
    return root->parent;
}

unsigned long long AVLTree::sum(unsigned long long a, unsigned long long b) {
    //return the sum off all node keys in the range of [a, b]

    //Naive Solution O(n)
    /*  Node* start = find(root, a);
     *  Node* s = start;
     *  unsigned long long sum=0;
     *  while(start && start->key<=b){
     *      sum+=start->key;
     *      start=next(start);
     *  }
     *  if(s && s->key<a) sum-=s->key;
     *  return sum;
     */

    //Efficient Solution O(log n)
    Node* start = find(root, a);
    Node* end = find(root, b);
    if ((start == end) && (end == nullptr)) return 0; //If there are nodes in the tree
    unsigned long long before_start_sum = start->left_sum, before_end_sum = end->left_sum;
    Node *s = start, *e = end;
    while(s->parent){
        if(s->parent->right_child == s) before_start_sum += (s->parent->left_sum + s->parent->key);
        s = s->parent;
    }
    while(e->parent){
        if(e->parent->right_child == e) before_end_sum += (e->parent->left_sum + e->parent->key);
        e = e->parent;
    }
    unsigned long long sum = end->key + before_end_sum - before_start_sum;
    if(end->key > b) sum-=end->key;
    if(start->key < a) sum-=start->key;
    return sum;
}

bool AVLTree::find(unsigned long long k) {
    //return true if a node with key "k" is found. Return false otherwise
    Node* temp = find(root, k);
    return (temp != nullptr && temp->key == k);
}