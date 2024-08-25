#include <iostream>
#include <stdexcept>


template<typename T>
class Queue{
T* niz_ = new T[kapacitet_];
size_t z = 0;
size_t p = 0;
size_t size_ = 0;
size_t kapacitet_ = 100;

public:
Queue() = default;
Queue(size_t size):kapacitet_{size}{}
Queue(const Queue& other):niz_{new T[kapacitet_]},z{other.z},p{other.p},size_{other.size_},kapacitet_{other.kapacitet_}{
    size_t a = p; 
    for(auto i(0); i<size_; i++){
        niz_[a] = other.niz_[a];
        a++;
        if(a == kapacitet_){
            a = 0;
        }
    }
}
Queue(Queue&& other):niz_{other.niz_},z{other.z},p{other.p},size_{other.size_},kapacitet_{other.kapacitet_}{
    delete[] other.niz_;
    other.z = 0; 
    other.p = 0; 
    other.size_ = 0; 
    other.kapacitet_ = 0;
}
Queue& operator=(const Queue& other){
    z = other.z;
    p = other.p;
    size_ = other.size_;
    kapacitet_ = other.kapacitet_; 
    delete[] niz_;
    T* niz_ = new T[kapacitet_];
    size_t a = p;
    for(auto i(0); i<size_; i++){
        niz_[a] = other.niz_[a];
        a++;
        if(a == kapacitet_){
            a = 0;
        }
    }
}
Queue& operator=(Queue&& other){
    z = std::move(other.z);
    p = std::move(other.p);
    size_ = std::move(other.size_);
    kapacitet_ = std::move(other.kapacitet_);
}
~Queue(){delete[] niz_;}

template<typename F>
void push(F&& element){
    if(size_ < kapacitet_){
        niz_[z++] = element;
        size_++;
    }else {
        throw std::out_of_range("ovaj red je pun!!!!");
    }
}

T pop(){
    if(size_ != 0){
        size_--;
        return niz_[p++];
    }
}
T top(){
    if(size_ != 0){
        return niz_[p];
    }
}
const T top()const{
    if(size_ != 0){
        return niz_[p];
    }
}
size_t capacity(){return kapacitet_;}
bool empty(){return size_ == 0;}
size_t size(){return size_;}

};

int main(){

    Queue<int> red;
    for(int i(0); i<123; i++){
        red.push(i);
    }
    

    return 0;
}

