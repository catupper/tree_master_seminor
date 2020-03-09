#include<iostream>
#include<vector>

using namespace std;

struct UnionFind{
    vector<int> p;
    UnionFind(int n){
        p.resize(n, -1);
    }

    int find(int x){
        if(p[x] == -1)return x;
        else return find(p[x]);
    }
    
    void unite(int x, int y){
        x = find(x);
        y = find(y);
        if(x == y)return;
        p[x] = y;
    }
    
};

int main(){
    int n, q, com , x, y;
    cin >> n >> q;
    UnionFind uf(n);
    for(int i = 0;i < q;i++){
        cin >> com >> x >> y;
        if(com == 0){
            uf.unite(x, y);
        }
        if(com == 1){
            if(uf.find(x) == uf.find(y)){
                cout << "Yes" << endl;
            }else{
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
