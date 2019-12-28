#include<iostream>
using namespace std;

struct SplayNode{
    SplayNode *left, *right, *parent;
    int size, value;

    SplayNode(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
    }

    void rotate(){
        SplayNode *pp, *p, *c;
        p = this->parent;
        pp = p->parent;

        if(p->left == this){
            c = this->right;
            this->right = p;
            p->left = c;
        }
        else{
            c = this->left;
            this->left = p;
            p->right = c;
        }
        if(pp && pp->left == p)pp->left = this;
        if(pp && pp->right == p)pp->right = this;
        this->parent = pp;
        p->parent = this;
        if(c)c->parent = p;

        p->update();
        this->update();
    }

    int state(){
        if(!this->parent)return 0;
        if(this->parent->left == this)return 1;
        if(this->parent->right == this)return -1;
        return 0;
    }
    
    void splay(){
        while(this->state() != 0){
            if(this->parent->state() == 0){
                this->rotate();
            }
            else if(this->state() == this->parent->state()){
                this->parent->rotate();
                this->rotate();
            }else{
                this->rotate();
                this->rotate();
            }
        }
    }
    
    void update(){
        this->size = 1;
        if(this->left)this->size += this->left->size;
        if(this->right)this->size += this->right->size;
    }    
};

SplayNode *get(int ind, SplayNode *root){
    SplayNode *now = root;
    while(true){
        int lsize = now->left ? now->left->size : 0;
        if(ind < lsize){
            now = now->left;
        }
        if(ind == lsize){
            now->splay();
            return now;
        }
        if(ind > lsize){
            now = now->right;
            ind = ind - lsize - 1;
        }
    }
}

SplayNode node[220000];

int main(){
    int q, ord, x;
    cin >> q;
    int vecsize = 0;

    for(int i = 0;i < q;i++){
        node[i].parent = &node[i+1];
        node[i+1].left = &node[i];
        node[i+1].update();
    }
    
    SplayNode *root = &node[q];
    
    for(int i = 0;i < q;i++){
        cin >> ord;
        if(ord == 0){
            cin >> x;
            root = get(vecsize++, root);
            root->value = x;
        }
        if(ord == 1){
            cin >> x;
            root = get(x, root);
            cout << root->value << endl;
        }
        if(ord == 2){
            vecsize--;
        }
    }
}
