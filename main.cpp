#include <iostream>
#include "AVLTree.h"

std::string suffix(int i);

int main(){
    auto *tree = new AVLTree;
    unsigned long long n, q1, q2;
    unsigned long long s;
    char op;
    std::cout << "Enter the number of operations you want to perform: ";
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cout << i << suffix(i%100) << " operation: ";
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

            default:{
                std::cout << "Invalid operation! \nPlease restart the program again." << std::endl;
                return 1;
            }
        }
    }
    delete tree;
}

std::string suffix(int i){
    if(!(i == 11 || i == 12 || i == 13)){
        switch (i%10){
            case 1: return "st";
            case 2: return "nd";
            case 3: return "rd";
        }
    }
    return "th";
}