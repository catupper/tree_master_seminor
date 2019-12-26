#include<iostream>
#include<vector>
#include<set>
#include<string>
using namespace std;

#define print_all(seq) for(auto elem:(seq))cout << elem << " ";cout << endl;

int main(){
    vector<int> vec = {3, 1, 4, 1, 5, 9 , 2};
    string str = "Hello World";
    set<int> st = {3, 1, 4, 1, 5, 9, 2};
    
    print_all(vec);
    print_all(str);
    print_all(st);
    
    return 0;
}
