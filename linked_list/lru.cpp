#include <iostream>
#include <list>
#include <unordered_map>

template<typename T>
class LruCache{
public:
    static int64_t now(){
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    LruCache(int capacity, int ttl): capacity_(capacity), ttl_(ttl){
    }

    struct Item{
        Item(){}
        Item(int64_t _id, int64_t _ts, const T &_data){
            id = _id;
            ts = _ts;
            data = _data;
        }
        int64_t id;
        int64_t ts;
        T data;
    };


    void set(int64_t id, const T &data){
        auto ts = now();
        expire(ts);
        list_.emplace_front(id, ts, data);
        auto ret = m_.insert({id, list_.begin()});
        if(ret.second){ // new key
            if(list_.size() > capacity_){
                m_.erase(list_.rbegin()->id);
                list_.pop_back();
            }
        }else{
            list_.erase(ret.first->second);
            ret.first->second = list_.begin();
        }
    }

    bool get(int64_t id, T &data){
        auto ts = now();
        expire(ts);
        auto iter = m_.find(id);
        if(iter == m_.end()){
            return false;
        }
        data = std::move(iter->second->data);
        list_.erase(iter->second);
        list_.emplace_front(id, ts, data);
        iter->second = list_.begin();
        return true;
    }

private:
    void expire(int64_t ts){
        while(!list_.empty() && ts - list_.back().ts > ttl_){
            m_.erase(list_.back().id);
            list_.pop_back();
        }
    }
    int64_t ttl_;
    int64_t capacity_;
    std::list<Item> list_;
    std::unordered_map<int64_t, typename std::list<Item>::iterator > m_;
};

int main(){

    LruCache<int> cache(10, 100000);
    int a;
    cache.set(1, 2);
    cache.get(1, a);
    return 0;
}