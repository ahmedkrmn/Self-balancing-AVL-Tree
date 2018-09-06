#include <iostream>
#include "AVLTree.h"

int main(){
    auto *tree = new AVLTree;
    unsigned long long n, q1, q2;
    unsigned long long s;
    char op;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> op;
        switch (op){
            case '?' :{
                std::cin >> q1;
                bool found = tree->find(q1);
                if(found) std::cout << "Found\n";
                else std::cout << "Not Found\n";
            } break;

            case '+' :{
                std::cin >> q1;
                tree->insert(tree->root, q1);
            } break;

            case '-' :{
                std::cin >> q1;
                tree->del(tree->root, q1);
            } break;

            case 's' :{
                std::cin >> q1 >> q2;
                s = tree->sum(q1, q2);
                std::cout << s << "\n";
            }
            default:break;
        }
    }
    delete tree;
}