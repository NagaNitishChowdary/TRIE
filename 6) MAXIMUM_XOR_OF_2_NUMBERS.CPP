// PROBLEM LINK --- https://www.codingninjas.com/codestudio/problems/maximum-xor_973113?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos&leftPanelTab=0
// PROBLEM LINK --- https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/

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

int max_xor(int arr[] , int n)
{
    // BRUTEFORCE
    /*
    int maxi = 0 ;
    for(int i=0 ; i<n ; i++){
        for(int j=i+1 ; j<n ; j++) maxi = max(maxi , arr[i]^arr[j]) ;
    }
    return maxi ;
    */
    // OPTIMIZED APPROACH 
    Trie *trie1 = new Trie() ;
    for(int i=0 ; i<n ; i++) trie1 -> insert(arr[i]) ;
    int maxi1 = 0 ;
    for(int i=0 ; i<n ; i++) maxi1 = max(maxi1 , trie1 -> getMax(arr[i])) ;
    return maxi1 ;
}

int main()
{
  int t ; cin >> t ;
  while (t--){
    int n ; cin >> n ;
    int a[n] ;
    for (int i = 0; i < n; i++) cin >> a[i] ;
    cout << max_xor(a, n) << endl;
  }
}
