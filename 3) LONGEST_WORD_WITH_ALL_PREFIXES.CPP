// PROBLEM LINK --- https://www.codingninjas.com/codestudio/problems/complete-string_2687860?utm_source=youtube&utm_medium=affiliate&utm_campaign=striver_tries_videos

#include <bits/stdc++.h> 
using namespace std ;

struct Node{
    Node *links[26] ;
    bool flag = false ;

    bool containsKey(char ch){ return links[ch-'a'] != NULL ; }
    Node *get(char ch){ return links[ch-'a'] ; }
    void put(char ch,Node *node){ links[ch-'a'] = node ; }
    void setEnd(){ flag = true ; }
    bool isEnd(){ return flag ; }
};

class Trie{
    private:
        Node *root ;
    public:
        Trie(){
            root = new Node() ;
        }
    public:
        void insert(string &word){
            Node *node = root ;
            for(int i=0 ; i<word.size() ; i++){
                // IF NOT THEN INSERT WORD
                if(!node -> containsKey(word[i])){
                    node -> put(word[i] , new Node()) ;
                }
                // THEN GET REFERENCE TRIE
                node = node -> get(word[i]) ;
            }
            node -> setEnd() ;
        }
    public:
        bool checkIfPrefixExists(string &word){
            Node *node = root ;
            for(int i=0 ; i<word.size() ; i++){
                if(node -> containsKey(word[i])){
                    node = node -> get(word[i]) ;
                    if(node -> isEnd() == false) return false ;
                }
                else return false ;
            }
            return true ;
        }
};

string completeString(int n, vector<string> &a){
    Trie *trie1 = new Trie() ;
    // STEP 1 --- INSERTING ALL STRINGS INTO TRIE 
    for(auto it:a) trie1->insert(it) ;
    // STEP 2 --- FIND LONGEST COMPLETE STRING
    string longest = "" ;
    for(auto it:a){
        if(trie1 -> checkIfPrefixExists(it)){
            if(it.size() > longest.size()) longest = it ;
            else if(it.size() == longest.size() && it < longest) 
                longest = it ; 
        }
    }
    if(longest == "") return "None" ;
    return longest ;
}

int main(){
  int t ; cin >> t ;
  while(t--){
    int n ; cin >> n ;
    vector<string> a(n) ;
    for(int i=0 ; i<n ; i++) cin >> a[i] ;
    cout << completeString(n,a) << endl ;
  }
  return 0 ;
}
