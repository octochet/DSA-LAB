#include <bits/stdc++.h>
using namespace std;

struct huffmanNode {
    string ch;
    int freq;
    huffmanNode *left;
    huffmanNode *right;

    huffmanNode(char c, int f) {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }

    huffmanNode(huffmanNode *l, huffmanNode *r) {
        ch = ' ';//"("+l->ch+"+"+r->ch+")";
        freq = l->freq + r->freq;
        left = l;
        right = r;
    }
};

//level order traversal
void levelOrder(huffmanNode *root) {
    if (root == NULL) {
        return;
    }
    queue<huffmanNode*> q;
    q.push(root);
    while (!q.empty()) {
        huffmanNode *temp = q.front();
        q.pop();
        cout << temp->ch << " ";
        if (temp->left != NULL) {
            q.push(temp->left);
        }
        if (temp->right != NULL) {
            q.push(temp->right);
        }
    }
}
class compare {
public:
    bool operator()(huffmanNode *l, huffmanNode *r) {
        return l->freq > r->freq;
    }
};

int main(int argc, char *argv[]) {
    // read and write binary files
    ifstream fin(argv[1], ios::binary);
    ofstream fout(argv[2], ios::binary);

    // read the file,store the freq and char in a pq and then build the tree while also saving the info from file
     priority_queue<huffmanNode*, vector<huffmanNode*>, compare> pq;
    char ch;
    int freq[256] = {0};
    while (fin.get(ch)) {
        freq[ch]++;
    }
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            huffmanNode *node = new huffmanNode(i, freq[i]);
            pq.push(node);
        }
    }
    while (pq.size() > 1) {
        huffmanNode *l = pq.top();
        pq.pop();
        huffmanNode *r = pq.top();
        pq.pop();
        huffmanNode *node = new huffmanNode(l, r);
        pq.push(node);
    }
    huffmanNode *root = pq.top();
    pq.pop();
    levelOrder(root);
    // write the tree to the file




    // write the encoded file
    fin.close();
    fout.close();
    return 0;
}