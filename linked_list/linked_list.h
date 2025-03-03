#include<iostream>
#include<assert.h>

template<typename T>
class DLinkList{
public:
    struct Node{
        Node(){}
        Node(const T &d): data(d){}
        T data;
        Node *pre = nullptr;
        Node *next = nullptr;
    };

    class iterator{
    public:
        iterator(Node *cur = nullptr):cur_(cur){ }
        T &operator*() const { return cur_->data; }
        T *operator->() const { return &cur_->data; }

        //前置++
        iterator &operator++(){
            cur_ = cur_->next;
            return *this;
        }

        //后置++
        iterator operator++(int){
            iterator tmp = *this;
            cur_ = cur_->next;
            return tmp; 
        }

        //前置++
        iterator &operator--(){
            cur_ = cur_->pre;
            return *this;
        }
    
        //后置++
        iterator operator--(int){
            iterator tmp = *this;
            cur_ = cur_->pre;
            return tmp; 
        }
        
        bool operator==(const iterator &o){
            return cur_ == o.cur_;
        }

        bool operator!=(const iterator &o){
            return cur_ != o.cur_;
        }

        Node *cur_;
    };

    DLinkList(){
        pre_head_.next = new Node();
        pre_head_.next->pre = &pre_head_;
        p_tail_ = pre_head_.next;
        n_ = 0;
    }

    ~DLinkList(){
        auto &p = pre_head_.next;
        while(p != nullptr){
            auto t = p->next;
            delete p;
            p = t;
        }
    }

    size_t size(){
        return n_;
    }

    bool empty(){
        return n_ == 0;
    }

    iterator begin(){
        return iterator(pre_head_.next);
    }

    iterator end(){
        return iterator(p_tail_);
    }

    void erase(const iterator &iter){
        node_remove(iter.cur_);
    }

    template<typename ...Args>
    void emplace_back(Args&&... args){
        n_++;
        p_tail_->data = T(std::forward<Args>(args)...);
        p_tail_->next = new Node();
        p_tail_->next->pre = p_tail_;
        p_tail_ = p_tail_->next;
    }

    void push_back(const T &data){
        n_++;
        p_tail_->data = data;
        p_tail_->next = new Node();
        p_tail_->next->pre = p_tail_;
        p_tail_ = p_tail_->next;
    }

    void pop_back(){
        n_--;
        auto t = p_tail_->pre;
        p_tail_->pre = t->pre;
        p_tail_->pre->next = p_tail_;
        delete t;
    }

    template<typename ...Args>
    void emplace_front(Args&&... args){
        n_++;
        auto t = pre_head_.next;
        pre_head_.next = new Node(T(std::forward<Args>(args)...));
        pre_head_.next->next = t;
        t->pre = pre_head_.next;
        pre_head_.next->pre = &pre_head_;
    }

    void push_front(const T &data){
        n_++;
        auto t = pre_head_.next;
        pre_head_.next = new Node(data);
        pre_head_.next->next = t;
        t->pre = pre_head_.next;
        pre_head_.next->pre = &pre_head_;
    }

    void pop_front(){
        n_--;
        auto t = pre_head_->next;
        pre_head_->next = t->next;
        pre_head_->next->pre = &pre_head_;
        delete t;
    }

    T &front(){
        return pre_head_->next->data;
    }

    T &back(){
        return p_tail_->pre->data;
    }

    Node *node_detach(Node *p){
        n_--;
        p->pre->next = p->next;
        p->next->pre = p->pre;
        return p;
    }

    void node_remove(Node *p){
        n_--;
        p->pre->next = p->next;
        p->next->pre = p->pre;
        delete p;
    }

private:
    Node pre_head_;
    Node *p_tail_;
    size_t n_;
};
