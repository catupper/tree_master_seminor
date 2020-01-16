#include<iostream>
using namespace std;    

#define SEG_LEN (1 << 18)

int seg[SEG_LEN * 2];

void add(int ind, int v){
    ind += SEG_LEN;
    seg[ind] += v;
    while(true){
        ind /= 2;
        if(ind == 0)break;
        seg[ind] = seg[ind * 2] + seg[ind * 2 + 1];
    }
}

int sum(int l, int r){
    l += SEG_LEN;
    r += SEG_LEN;
    int ans = 0;
    while(l < r){
        if(l % 2 == 1){
            ans += seg[l];
            l++;
        }
        l /= 2;
        if(r % 2 == 1){
            ans += seg[r-1];
            r--;
        }
        r /= 2;
    }
    return ans;
}

int main(){
    int n, q, com, ind, v, l, r;
    cin >> n >> q;
    for(int i = 0;i < q;i++){
        cin >> com;
        if(com == 0){//add
            cin >> ind >> v;
            add(ind, v);
        }
        if(com == 1){//get sum
            cin >> l >> r;
            cout << sum(l, r+1) << endl;
        }
    }
    return 0;
}
