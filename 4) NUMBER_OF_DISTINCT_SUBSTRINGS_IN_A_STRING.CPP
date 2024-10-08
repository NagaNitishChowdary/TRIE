// PROBLEM LINK --- https://www.codingninjas.com/codestudio/problems/count-distinct-substrings_985292?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos

#include<bits/stdc++.h>
using namespace std;

struct Node{
    Node *links[26] ;

    bool containsKey(char ch){ return links[ch-'a'] != NULL ; }
    void put(char ch,Node *node){ links[ch-'a'] = node ; }
    Node* get(char ch){ return links[ch-'a'] ; }
};


int countDistinctSubstring(string s)
{
    //Your code here
    // BRUTEFORCE
    /*
    set<string> st ;
    int size = s.size() ;
    for(int i=0 ; i<size ; i++){
        string str = "" ;
        for(int j=i ; j<size ; j++){
            str += s[j] ;
            st.insert(str) ;
        }
    }
    return st.size()+1 ;
    */
    
    int cnt = 0 ;
    Node *root = new Node() ;
    for(int i=0 ; i<s.size() ; i++){
        Node *node = root ;
        for(int j=i ; j<s.size() ; j++){
            if(!node -> containsKey(s[j])){
                cnt++ ;
                node -> put(s[j],new Node()) ;
            }
            node = node -> get(s[j]) ;
        }
    }
    return cnt+1 ;
}

int main()
{
    int t,l,i,j ; 
    int temp ;
    cin >> t ;
    while(t--){
    string s ; cin >> s ;
    cout << countDistinctSubstring(s) << endl ;
   }
}
