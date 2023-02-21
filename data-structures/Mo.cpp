/**
*   author: lazyhash(yashkundu)
*   created: 21 Feb, 2023 | 11:45:09
*   description: answers offline range queries in O((N+Q)Sqrt(N))
*   arrange offline queries using sqrt decomposition
**/

// the main concept is to store a particular range (l, r) in some type of data structure and move l and r to answer for the current query range
// all the segments will first be sorted on the block in which their left endpoints lie, secondly in the same block segments will be sorted according to their right endpoints
// if add and remove are of constant complexity
// NO. of add and remove operations for the left pointer - QSqrt(N)
// NO. of add and remove operations for the right pointer - NSqrt(N)

#include <vector>

using namespace std;

void add(int idx);  // adds idx to the range data structure
void remove(int idx);    // removes idx from the range data structure
int get_answer();

const int K = 100;          // Sqrt(N)  block_size

void mo(vector<pair<int, int>> &queries) {
    vector<int> ans;
    // change the direction of sort of r in consecutive block from left to right, right to left and so on to improve efficiency
    sort(queries.begin(), queries.end(), [](pair<int, int> s1, pair<int, int> s2) {
        if(s1.first/K!=s2.first/K)
            return s1<s2;
        return (s1.first/K & 1)? s1.second<s2.second : s2.second<s1.second;
    });

    int l = 0, r = -1;
    for(auto query: queries) {
        while(l>query.first) add(--l);
        while(r<query.second) add(++r);
        while(l<query.first) remove(l++);
        while(r>query.second) remove(r--);
        ans.push_back(get_answer());
    }

}