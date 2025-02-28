#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>
#include "heap.h"
 
void println(std::string_view rem, const std::vector<int>& v){
    std::cout << rem;
    for (int e : v)
        std::cout << e << ' ';
    std::cout << '\n';
}
 
int main()
{
    std::vector<int> v{3, 1, 4, 1, 5, 9};
 
    std::make_heap(v.begin(), v.end(), std::greater<int>());
    println("after make_heap: ", v);
 
    v.push_back(6);
    println("after push_back: ", v);
 
    std::push_heap(v.begin(), v.end(), std::greater<int>());
    println("after push_heap: ", v);

    v[2] = 100;
    down_heap(v.data(), 2, v.size(), std::greater<int>());
    println("after down_heap: ", v);

}