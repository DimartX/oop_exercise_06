#include <iostream>
#include <algorithm>
#include <cstddef>

#include "stack.hpp"
#include "triangle.hpp"
#include "allocator.hpp"

void help() {
    std::cout << "usage:\n";
    std::cout << " push <elem> \n insert <index> \n pop \n erase <index> \n";
    std::cout << " top \n print \n count_if <max_area> \n exit \n";
}

int main() {
    bad::stack<Triangle<int>, my_allocator<Triangle<int>, 200> > stack_tri;
    while (std::cin) {
        std::string perform;
        std::cin >> perform;

        try {
            if (perform == "push") {
                Triangle<int> tmp(std::cin);
                try {
                    stack_tri.push(tmp);
                }
                catch(std::bad_alloc& e) {
                    std::cout << e.what() << std::endl;
                    continue; 
                }
            }
            else if (perform == "insert") {
                size_t index;
                std::cin >> index;
                Triangle<int> tmp(std::cin);
                try {
                    stack_tri.insert(stack_tri.begin() + index, tmp);
                }
                catch(std::bad_alloc& e) {
                    std::cout << e.what() << std::endl;
                    continue; 
                }
            }
            else if (perform == "pop") {
                try {
                    stack_tri.pop();
                }
                catch(std::bad_alloc& e) {
                    std::cout << e.what() << std::endl;
                    continue; 
                }
            }
            else if (perform == "erase") {
                int index;
                std::cin >> index;
                try {
                    stack_tri.erase(stack_tri.begin() + index);
                }
                catch(std::bad_alloc& e) {
                    std::cout << e.what() << std::endl;
                    continue; 
                }
            }
            else if (perform == "top") {
                std::cout << stack_tri.top();
            }
            else if (perform == "print") {
                for (auto& tri : stack_tri) {
                    std::cout << tri;
                }
            }
            else if (perform == "count_if") {
                int area;
                std::cin >> area;
                std::cout << std::count_if(stack_tri.begin(), stack_tri.end(),
                                           [area](const Triangle<int>& tri) {
                                               return tri.double_area() < area * 2;
                                           }) << std::endl;
            }
            else if (perform == "exit") {
                return 0;
            }
            else if (perform == "help") {
                help();
            }
            else {
                std::cout << "Wrong command\n";
            }
        }
        catch (int n) {
            std::cout << "Caught exception " << std::endl;
            // something
        }
        std::cout << "OK!\n";
    }
}
