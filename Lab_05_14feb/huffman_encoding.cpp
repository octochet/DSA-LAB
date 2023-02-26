//admin
//MACiittp@123
#include<iostream>
#include <fstream>
#include <string>
#include<queue>
#include <cstring>

#define MAX 27
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left,*right; 

    Node(char ch, int freq) {
        this->ch = ch;
        this->freq = freq;
        left = right = nullptr;
    }
};

void print_pq(priority_queue<pair<int,char>> pq) {
    cout<<"Priority queue:"<<endl;
    while(!pq.empty()) {
        cout<<-pq.top().first <<" " << pq.top().second << endl;
        pq.pop();
    }
}

void countFreq(string line, int freq[]) {
    for(int i=0; i<line.size(); i++) {
        if(!isblank(freq[i])) {
            freq[line[i]-'a']++;
        } else {
            freq[26]++;
        }
    }
}

int main() {
    int freq[MAX] ;
    for(int i=0; i<MAX; i++) {
        freq[i]=0;
    }
    string line;
    ifstream inputfile("input.txt");

    if(inputfile.is_open()) {
        while(getline(inputfile,line)){
            countFreq(line,freq);
        }
        inputfile.close();
    } else {
        cout<<"Unable to open input file !!!"<<endl;
    }

    priority_queue<pair<int,char>> pq;
    for(int i=0; i<MAX-1; i++) {
        if(freq[i]!=0) {
            pq.push(make_pair(-freq[i],i+'a'));
        }
    }
    if(freq[26]!=0) {
        pq.push(make_pair(-freq[26],' '));
    }
    print_pq(pq);
    return 0;
}