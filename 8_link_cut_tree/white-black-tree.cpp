#include<iostream>
using namespace std;

struct LinkCutNode{
    LinkCutNode *left, *right, *parent;
    int size, value;

    LinkCutNode(){
        left = nullptr;
        right = nullptr;
        parent = nullptr;
        size = 1;
    }

    void rotate(){
        LinkCutNode *pp, *p, *c;
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

typedef LinkCutNode LCN;

void access(LCN *v){
    while(true){
        v->splay();
        v->right = nullptr;
        v->update();
        if(v->parent == nullptr)break;
        v->parent->splay();
        v->parent->right = v;
        v->parent->update();
    }
}

void link(LCN *c, LCN *p){
    c->parent = p;
}

void cut(LCN *c){
    access(c);
    c->left->parent = nullptr;
    c->left = nullptr;
    c->update();
}

LCN *root(LCN *v){
    access(v);
    LCN *now = v;
    while(now->left != nullptr)now = now->left;
    now->splay();
    return now;                    
}

int p[110000], c[110000];
LCN node[110000];

int main(){
    int n;
    cin >> n;
    for(int i = 2;i <= n;i++){
        cin >> p[i];
    }
    for(int i = 1;i <= n;i++){
        cin >> c[i];
    }

    for(int i = 2;i <= n;i++){
        if(c[i] != c[p[i]]){
            link(&node[i], &node[p[i]]);
        }
    }
    int q, ord, u, v;
    cin >> q;
    for(int i = 0;i < q;i++){
        cin >> ord;
        if(ord == 1){
            cin >> u;
            if(u == 1)continue;
            if(root(&node[u]) == root(&node[p[u]])){
                cut(&node[u]);
            }
            else{
                link(&node[u], &node[p[u]]);
            }
        }
        if(ord == 2){
            cin >> u >> v;
            if(root(&node[u]) == root(&node[v]))cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
    return 0;
}
