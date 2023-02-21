/**
*   author:  lazyhash(yashkundu)
*   created: 08 Jan,2023
*   description: compute partial sums (a[0]+a[1]... + a[k-1]) and does point updates a[i]
*   time: add, get takes O(logn)
**/

template<typename T>
struct bit{
    int n;
    vector<T> v;
    bit(int n): n(n) {v.resize(n+1);}ß
    void add(int ind, T val) {
        ind++; for(;ind<=n;ind+=ind&(-ind)) v[ind] += val;
    }
    T get(int ind) {
        ind++; T ans = T(); 
        for(;ind>0;ind-=ind&(-ind)) ans += v[ind]; return ans; 
    }
    T get(int l, int r) {
        return get(r) - get(l-1);
    }
    T lower_bound(T x) {
        int ind = 0, sum = T();
        for(int pw=1<<25;pw>0;pw>>=1) if(ind+pw<=n && sum + v[ind+pw]<x) ind = ind +  pw, sum += v[ind+pw];
        return ind;
    }
};