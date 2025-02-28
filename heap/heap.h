#include <iostream>

template<class T, class CMP>
void up_heap(T *data, int pos, int n, CMP is_down){
    for(int p = (pos-1)/2; p >= 0; p = (pos-1)/2){
        if(is_down(data[pos], data[p])){
            break;
        }
        std::swap(data[pos], data[p]);
        pos = p;
    }
}

template<class T, class CMP>
void down_heap(T *data, int pos, int n, CMP is_down){
    for(int c = (pos<<1) + 1; c < n; c = (pos<<1) + 1){
        if(c + 1 < n && is_down(data[c], data[c+1])){
            c = c + 1;
        }
        if(!is_down(data[pos], data[c])){
            break;
        }
        std::swap(data[pos], data[c]);
        pos = c;
    }
}