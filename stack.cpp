#include<iostream>

template<typename T>
class stack{
    private:
    size_t capacity_;
    size_t size_;
    T* p_;
    public:
    stack():capacity_{100},size_{0},p_{new T[capacity_]}{};
    stack(const stack& other):capacity_{other.capacity_},size_{other.size_}{
        p_ = new T[capacity_];
        for(size_t i(0);i<size_;++i){
            p_[i] = other.p_[i];
        }
    }
    stack(stack&& other):capacity_{std::move(other.capacity_)},size_{std::move(other,size_)},p_{std::move(other.p_)}{};
    stack& operator=(const stack& other){
        delete[] p_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        p_ = new T[capacity_];
        for(size_t i(0);i<size_;++i){
            p_[i] = other.p_[i];
        }

        return *this; 
    }
    stack& operator=(stack&& other){
        capacity_ = std::move(other.capacity_);
        size_ = std::move(other.size_);
        p_ = std::move(other.p_);
        return *this;
    }
    ~stack(){
        delete[] p_;
            p_ = nullptr; 
    }

    size_t size()const{return size_;}
    bool empty()const{return size_ == 0;}
    T& top(){
        return p_[size()-1];
    }
    void pop(){
        --size_;
    }
    void reallocate(){
        capacity_ = capacity_ * 2;
        auto temp = p_;
        delete p_;
        p_ = new T[capacity_];
        for(size_t i(0);i<size_;++i){
            p_[i] = temp[i];
        }
    }
    void push(const T& other){
        if(size_ == capacity_){
            reallocate();
        } 
        p_[size_] = other;
        size_++;
    }
 

};

int main(){
    stack<int> a;
    a.push(2);
    a.push(53);
    std::cout<< a.top()<< std::endl;
    a.pop();
    std::cout << a.top();
    return 0;
}


