#include <iostream>

template<typename T>
class List {
    private:
        struct node{
            T element;
            node* next = nullptr;
            node* previous = nullptr;
        };
        node* front_ = nullptr;
        node* back_ = nullptr;
        size_t size_= 0;
        public:
        class iterator{
            private:
            node* p_;
            public:
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;
            friend List;
            iterator(node* p):p_(p){};

            iterator& operator++(){
                if(p_ != nullptr){
                    p_ = p_->next;
                }
                    return *this;
            }
        
            iterator operator++(int){
                auto temp = *this;
                if(p_ != nullptr){
                    p_ = p_->next;
                }
                    return temp;
                 
            }

            iterator& operator--(){
                if(p_ != nullptr){
                    p_ = p_->previous;
                } 
                    return *this;
            }
            iterator operator--(int){
                auto temp = *this; 
                if(p_ != nullptr){
                    p_ = p_->previous;
                } 
                    return temp;
            }

            T& operator*(){return p_->element;}


        };
        
        List() = default;
        
        List(const List& other){
            auto temp = other.front_;
            while(temp == nullptr){
                push_back(temp->element);
                temp = temp->next;
            }
        }
        List(List&& other){
            auto temp = other.front_;
            while(temp == nullptr){
                push_back(temp->element);
                temp = temp->next;
            }
            other.back_ = nullptr;
            other.front_ = nullptr;
            other.size_ = 0; 
        }

        List& operator=(const List& other){
            clear();
            auto temp = other.front_;
            while(temp == nullptr){
                push_back(temp->element);
                temp = temp->next;
            }
            return *this; 
        }

        List& operator=(List&& other){
            clear();
            auto temp = other.front_;
            while(temp == nullptr){
                push_back(temp->element);
                temp = temp->next;
            }
            other.back_= nullptr;
            other.front_= nullptr;
            other.size_ = 0;
            return *this; 
        }

        ~List(){
            auto temp = front_;
            while(temp != nullptr){
                temp = temp->next;
                delete front_; 
                front_ = temp; 
            }

        }
        
        iterator begin(){return front_;}   
        iterator end(){return back_->next;}
       
        void push_back(const T& e){
            if(front_==nullptr){
                front_ = new node{e,nullptr,nullptr};
                back_ = front_; 
            }
            else{
                back_->next = new node{e,nullptr,nullptr};
                back_ = back_->next;
            } 
            ++size_;
        }
        void push_back(T&& e){
            if(front_==nullptr){
                front_ = new node{e,nullptr,nullptr};
                back_ = front_; 
            }
            else{
                back_->next = new node{e,nullptr,nullptr};
                back_ = back_->next;
            } 
            ++size_;
        }

        void pop_back(){
            if(back_ == nullptr){return;}
            auto temp = back_->previous;
            delete back_;
            back_ = temp;
            --size_;
        }

        void push_front(const T& e){
            auto temp = new node{e,nullptr,nullptr};
            if(front_ == nullptr){
                front_ = temp;
                back_ = temp;
            }else{
            temp->next = front_;
            front_->previous = temp;
            front_ = temp; 
            } 
            ++size_; 
        } 
        void push_front(T&& e){
            auto temp = new node{e,nullptr,nullptr};
            if(front_ == nullptr){
                front_ = temp;
                back_ = temp;
            }else{
            temp->next = front_;
            front_->previous = temp;
            front_ = temp; 
            front_->previous= nullptr;
            } 
            ++size_; 
        } 



        void pop_front(){
            if(front_== nullptr){
                return;
            }
            auto temp = front_->next;
            delete front_;
            front_ = temp;     
            --size_; 
        }

        void clear(){
            while(front_ != nullptr){
                auto temp = front_->next;
                delete front_;
                front_ = temp;     
            }
            back_ = nullptr;
            size_ = 0; 
        }

        void insert(iterator poz,const T& e){
            auto temp = new node{e,poz.p_->next->next,poz.p_};
            poz.p_->next= temp;
            poz.p_->next->next->previous = temp;
            ++size_;
        
        } 

        void remove(iterator& poz){
            if(poz.p_ == front_){pop_front();}
            if(poz.p_ == back_){pop_back();} 
            auto temp = poz.p_;
            poz.p_->previous->next = poz.p_->next;
            poz.p_->next->previous = poz.p_->previous;
            delete temp; 
            --size_;
        } 

};


int main(int argc, char const *argv[])
{
    List<int> l;
    l.push_back(2);
    l.push_back(1); 
    l.push_back(3);
    l.push_front(6);
    List<int>::iterator it = l.begin();
    ++it;
    l.insert(it,9); 
    std::cout << *it << std::endl;
    l.remove(it);
    ++it;
    --it;
    std::cout << *it;
    return 0;
}



