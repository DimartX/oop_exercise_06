#include <iostream>
#include <map>

#include "allocator.hpp"

int main() {
    std::map<int, int, std::less<int>,
             my_allocator<std::pair<const int, int>, 100>> mp;
    for(int i = 0; i < 2; ++i){
        mp[i] = i * i;
    }
    for(int i = 2; i < 10; ++i){
        mp.erase(i - 2);
        mp[i] = i * i;
    }
    std::cout << "WORKED SUCCESSFULL\n";
}
