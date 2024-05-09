// Verification: https://codeforces.com/problemset/submission/1181/260078595

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
 
using namespace std;

const int M = 18;
 
struct BIT{
    int n;
    vector<int> tree;
    BIT(int n) {
        tree.resize(n+1);
        tree.assign(n+1, 0);
        this->n = n;
    }
    void update(int ind, int val) {
        for(;ind<=n;ind+=ind&(-ind)) tree[ind] += val;
    }
    int query(int ind) {
        int ans = 0;
        for(;ind>0;ind-=ind&(-ind)) ans += tree[ind];
        return ans;
    }
    int lower_bound(int x) {
        int ind = 0;
        int sum = 0;
        for(int p=(1<<M);p>0;p>>=1) {
            if(ind+p<=n && sum + tree[ind+p]<x) {
                ind = ind + p;
                sum += tree[ind];
            }
        }
        return ind+1;
    }
};