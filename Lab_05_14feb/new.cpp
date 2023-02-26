#include<iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 28

int freq[MAX];

struct TreeNode{
    char c;
    int weight;
    TreeNode *left;
    TreeNode *right;

};

void countFreq(string line, int freq[]) {
    for(int i=0; i<line.size(); i++) {
        if(!isblank(freq[i])) {
            freq[line[i]-'a']++;
        } else {
            freq[26]++;
        }
    }
}

void readFile() {
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
}



int main() {
    priority_queue<TreeNode> pq;
    
}