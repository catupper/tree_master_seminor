#include<iostream>
using namespace std;

struct SplayNode{
    SplayNode *left, *right, *parent;
    int size, value, minimum;

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
        this->minimum = this->value;
        if(this->left){
            this->size += this->left->size;
            this->minimum = min(this->minimum, this->left->minimum);
        }
        if(this->right){
            this->size += this->right->size;
            this->minimum = min(this->minimum, this->right->minimum);
        }
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

typedef SplayNode SN;

SN *merge(SN *lroot, SN *rroot){
    if(!lroot)return rroot;
    if(!rroot)return lroot;
    lroot = get(lroot->size-1, lroot);
    lroot->right = rroot;
    rroot->parent = lroot;
    lroot->update();
    return lroot;
}
pair<SN*, SN*> split(int left_cnt, SN *root){
    if(left_cnt == 0)return{nullptr, root};
    if(left_cnt == root->size)return {root, nullptr};
    root = get(left_cnt, root);
    SN *lroot, *rroot;
    lroot = root->left;
    rroot = root;
    rroot->left = nullptr;
    lroot->parent = nullptr;
    rroot->update();
    return {lroot, rroot};
}
SN *insert(int ind, SN *node, SN *root){
    auto trees = split(ind, root);
    SN* lroot = trees.first;
    SN* rroot = trees.second;
    return merge( merge(lroot, node), rroot);
}
pair<SN*, SN*> remove(int ind, SN *root){
    root = get(ind, root);
    SN* lroot = root->left;
    SN* rroot = root->right;
    if(lroot)lroot->parent = nullptr;
    if(rroot)rroot->parent = nullptr;
    root->left = nullptr;
    root->right = nullptr;
    root->update();
    return {merge(lroot, rroot), root};
}

SN* shift(int l, int r, SN* root){
    auto tmp = remove(r, root);
    root = tmp.first;
    SN* node = tmp.second;
    return insert(l, node, root);
}

pair<SN*, int> rmq(int l, int r, SN* root){
    SN *lroot, *croot, *rroot;
    auto tmp = split(r+1, root);
    rroot = tmp.second;
    tmp = split(l, tmp.first);
    lroot = tmp.first;
    croot = tmp.second;
    int ans = croot->minimum;
    return {merge(merge(lroot, croot), rroot), ans};
}

SplayNode node[220000];

int main(){
    int n, q;
    cin >> n >> q;
    int vecsize = 0;

    for(int i = 0;i < n-1;i++){
        node[i].parent = &node[i+1];
        node[i+1].left = &node[i];
        node[i+1].update();
    }

    for(int i = 0;i < n;i++){
        cin >> node[i].value;
        node[i].update();
    }
    
    SplayNode *root = &node[n-1];
    
    for(int i = 0;i < q;i++){
        int ord, l, r, pos, val;
        cin >> ord;
        if(ord == 0){
            cin >> l >> r;
            root = shift(l, r, root);
        }
        if(ord == 1){
            cin >> l >> r;
            auto tmp = rmq(l, r, root);
            root = tmp.first;
            cout << tmp.second << endl;
        }
        if(ord == 2){
            cin >> pos >> val;
            root = get(pos, root);
            root->value = val;
            root->update();
        }
    }
}
