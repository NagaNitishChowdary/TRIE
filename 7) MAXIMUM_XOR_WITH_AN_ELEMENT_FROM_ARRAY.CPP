// PROBLEM LINK --- https://leetcode.com/problems/maximum-xor-with-an-element-from-array/
// PROBLEM LINK --- https://www.codingninjas.com/codestudio/problems/max-xor-queries_1382020?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos&leftPanelTab=0

#include <bits/stdc++.h>
using namespace std;

struct Node{
    Node *lists[2] ;

    bool containsKey(int bit){ return lists[bit] != NULL ; }
    void put(int bit,Node *node){ lists[bit] = node ; }
    Node *get(int bit){ return lists[bit] ; }
};

class Trie{
    private: 
        Node *root ;
    public:
        Trie(){
            root = new Node() ;
        }

        void insert(int num){
            Node *node = root ;
            for(int i=31 ; i>=0 ; i--){
                int bit =  (num>>i)&1 ;
                if(!node -> containsKey(bit)){
                    node -> put(bit , new Node()) ;
                }
                node = node -> get(bit) ;
            }
        }

        int getMax(int num){
            Node *node = root ;
            int maxNum = 0 ;
            for(int i=31 ; i>=0 ; i--){
                int bit = (num >> i)&1 ;
                if (node->containsKey(1 - bit)) {
                  maxNum = maxNum | (1<<i) ;
                  node = node -> get(1-bit) ;
                }
                else{
                    node = node -> get(bit) ;
                }
            }
            return maxNum ;
        }
};

vector<int> maxXorQueries(vector<int> &arr, vector<vector<int>> &queries){
    //  Write your coode here.
    // BRUTEFORCE
    /*
    int size1 = arr.size() , size2 = queries.size() ;
    vector<int> ans ;
    for(auto it:queries){
      int maxi = -1 ;
      int first = it[0] , second = it[1] ;
      for(int i=0 ; i<size1 ; i++){
        if(arr[i] <= second) maxi = max(maxi , arr[i]^first) ;
      }
      ans.emplace_back(maxi) ;
    }
    return ans ;  
    */
    int size1 = arr.size() , size2 = queries.size() ;
    sort(arr.begin() , arr.end()) ;
    vector<pair<int,pair<int,int>>> offline_queries ;
    for(int i=0 ; i<size2 ; i++){
      offline_queries.push_back({queries[i][1] ,{queries[i][0] , i}}) ;
    }
    // TC --- QLOGQ
    sort(offline_queries.begin() , offline_queries.end()) ;
    vector<int> ans(size2) ;
    int index = 0 ;
    Trie *trie1 = new Trie() ;
    // TC --- O(Q*32 + N*32)
    for(int i=0 ; i<size2 ; i++){
      int ai = offline_queries[i].first ;
      int xi = offline_queries[i].second.first ;
      int qind = offline_queries[i].second.second ;
      while(index < size1 && arr[index] <= ai){
        trie1 -> insert(arr[index]) ;
        index++ ;
      }
      // IF U ARE STILL STANDING AT INDEX 0 
      if(index == 0) ans[qind] = -1 ;
      else ans[qind] = trie1 -> getMax(xi) ;
    }
    return ans ;
}

int main()
{
  int t ; cin >> t ;
  while (t--){
    int n , m ; cin >> n >> m ;
    vector<int> arr(n) ;
    for (int i = 0; i < n; i++) cin >> arr[i] ;
    vector<vector<int>> queries ;
    for(int i=0 ; i<m ; i++){
        vector<int> knnc(2) ;
        cin >> knnc[0] >> knnc[1] ;
        queries.push_back(knnc) ;
    }
    vector<int> ans = maxXorQueries(arr, queries) ;
    for(auto it:ans) cout << it << " " ;
    cout << endl ;
  }
}
