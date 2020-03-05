#include<iostream>
using namespace std;    

#define SEG_LEN (1 << 18)

int seg[SEG_LEN * 2];

// one point
long long int get(int ind){
    ind += SEG_LEN;
    long long int sum = 0;
    sum += seg[ind];
    while(true){
        ind /= 2;
        if(ind == 0)break;
        sum += seg[ind];
    }
    return sum;
}

// range
void add(int l, int r, int x){
    l += SEG_LEN;
    r += SEG_LEN;
    while(l < r){
        if(l % 2 == 1){
            seg[l] += x;
            l++;
        }
        l /= 2;
        if(r % 2 == 1){
            seg[r-1] += x;
            r--;
        }
        r /= 2;
    }
}

int main(){
    int n, q, com, ind, v, l, r;
    cin >> n >> q;
    for(int i = 0;i < q;i++){
        cin >> com;
        if(com == 0){//add
            cin >> l >> r >> v;
            add(l, r+1, v);
        }
        if(com == 1){//get
            cin >> ind;
            cout << get(ind) << endl;
        }
    }
    return 0;
}
