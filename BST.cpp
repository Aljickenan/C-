#include <iostream>
#include <queue>
#include <stack>

template<typename T>
class BST {
    struct node{
        node(T v):element{v}{}
        T element;
        node* lijevi = nullptr;
        node* desni = nullptr;
    };
    node* root = nullptr;
    int size_ = 0;
    void PrintST(node* root_){
        if(root_ == nullptr){
            return;
        }
        std::cout << root_->element << " ";
        PrintST(root_->lijevi);
        PrintST(root_->desni);
    }
    int depth(node* temp){
        if(temp == nullptr){
            return 0;
        }else{
            int dubinal = depth(temp->lijevi);
            int dubinar = depth(temp->desni);
            return 1 + std::max(dubinal,dubinar);

        }
    }
    void clearST(node* temp){
        if(temp == nullptr){
            return;
        }
        clearST(temp->lijevi);
        clearST(temp->desni);
        delete temp;
    }
    void insertST(node* temp){
        if(temp == nullptr){
            return;
        }
        insert(temp->element);
        insertST(temp->lijevi);
        insertST(temp->desni);
    }
    void eraseST(node*& e){
        if(!e){
            return;
        }else if(!e->lijevi && !e->desni){
            auto temp = e;
            e = nullptr;
            delete temp;
        }else if(!e->desni){
            auto temp = e;
            e = e->lijevi;
            delete temp;
        }else if(!e->lijevi){
            auto temp = e;
            e = e->desni;
            delete temp;
        }else{
            //dvoje djece
            node* prosli = nullptr;
            auto trenutni = e->lijevi;

            while(trenutni->desni){
                prosli = trenutni;
                trenutni = trenutni->desni;
            }
            e->element = trenutni->element;         
            if(prosli){  
            prosli->desni = trenutni->desni;
            }else { 
                e->lijevi = trenutni ->lijevi;
            }
            delete trenutni;
        }
        size_--;
    }

    void postfixst(node* temp){
        if(!temp){
            return;
        }
        postfixst(temp->lijevi);
        postfixst(temp->desni);
        std::cout << temp->element << " ";
    }
    void infixst(node* temp){
        if(!temp){
            return;
        }
        infixst(temp->lijevi);
        std::cout << temp->element << " ";
        infixst(temp->desni);
    }
    public:
    BST(){};
    BST(const BST& other){
        insertST(other.root);
    }
    BST(BST&& other): root{other.root},size_{other.size_}{
        other.root = nullptr;
        other.size_ = 0;
    }
    BST& operator=(const BST& other){
        clear();
        insertST(other.root);
        return *this;
    }
    BST& operator=(BST&& other){
        clear();
        root = other.root;
        size_ = other.size_;
        other.root = nullptr;
        other.size_ = 0;
        return *this;
    }

~BST(){
    clear();
}

void Prefix(){
    //pomocu queue
    std::queue<node*> red;
    red.push(root);
    while(!red.empty()){
        auto temp = red.front();
        std::cout << temp->element << " ";
        if(temp->lijevi){red.push(temp->lijevi);}
        if(temp->desni) {red.push(temp->desni);}
        red.pop();
    }
    std::cout << std::endl;
}
void Postfix(){
    // bezz stacka ili queue
        postfixst(root); 
        std::cout << std::endl;
    }

void Infix(){
    infixst(root);
    std::cout << std::endl;
}

void clear(){
    clearST(root);
    size_ = 0;
    root = nullptr;
}

    int size()const {
        return size_;
    }

    int depth(){
        return depth(root);
    }
    bool empty(){
        return root == nullptr;
    }

    const node* find(const T& ele) const {
        node* temp = root;
        while(temp != nullptr){
            if(temp->element == ele){
                return temp;
            }else if(temp->element > ele){
                temp = temp->lijevi;
            }else{
                temp = temp->desni;
            }
        }
        return 0 ;
    }

    void Print(){
        PrintST(root);
        std::cout<<std::endl;
    }

    void insert(T ele){
        if(empty()){
            root = new node{ele};
            size_++;
        }else{
            node* prosli = nullptr;
            node* trenutni = root;
            while(trenutni != nullptr){
                if(ele < trenutni->element){
                    prosli = trenutni;
                    trenutni = trenutni->lijevi;
                }else if(ele > trenutni->element){
                    prosli = trenutni;
                    trenutni = trenutni->desni;
                }else{
                    //kad su jednaki
                }
            }                
                node* Ncvor = new node{ele};

                if(ele < prosli->element){
                    prosli->lijevi = Ncvor;
                    size_++;
                }else if(ele > prosli->element){
                    prosli->desni = Ncvor;
                    size_++;
                }else{
                    //kad su jenaki
                }
 
        }

    }
    
    void erase(const T& element){
        node* prosli = nullptr;
        node* temp = root;
        while(temp != nullptr){
            if(temp->element == element){
                break;
            }else if(temp->element > element){
                prosli = temp;
                temp = temp->lijevi;
            }else{
                prosli = temp;
                temp = temp->desni;
            }
        }
        if(!prosli){
            eraseST(root);
        }else if(prosli->desni){
            eraseST(prosli->desni);
        }else{
            eraseST(prosli->lijevi);
        }
    }




};

int main() {

    BST<int> stablo;
    stablo.insert(10);
    stablo.insert(32);
    stablo.insert(2);
    stablo.insert(52);
    stablo.insert(63);
    stablo.insert(5);
    stablo.Print();
    stablo.erase(5);
    stablo.Print();
    stablo.erase(10);
    stablo.Print();
    stablo.erase(2);
    stablo.erase(32);
    stablo.erase(52);
    stablo.erase(63);
    stablo.Print();
    stablo.insert(10);
    stablo.insert(32);
    stablo.insert(2);
    stablo.insert(52);
    stablo.insert(63);
    stablo.insert(5);
    stablo.Prefix(); 
    stablo.Postfix();
    stablo.Infix();

    return 0;
}




