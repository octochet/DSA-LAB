#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <functional>

using namespace std;

// A node of the Huffman tree
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
};

// Comparator function for priority queue
struct CompareNodes {
    bool operator()(HuffmanNode *a, HuffmanNode *b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman tree and codes from input file
void buildHuffmanTree(string inputFilePath, unordered_map<char, string> &huffmanCodes) {
    // Read input file and count character frequencies
    ifstream inputFile(inputFilePath);
    unordered_map<char, int> charFreq;
    char ch;
    while (inputFile.get(ch)) {
        charFreq[ch]++;
    }
    inputFile.close();

    // Build Huffman tree using priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;
    for (auto pair : charFreq) {
        HuffmanNode *node = new HuffmanNode;
        node->ch = pair.first;
        node->freq = pair.second;
        node->left = nullptr;
        node->right = nullptr;
        pq.push(node);
    }
    while (pq.size() > 1) {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();
        HuffmanNode *parent = new HuffmanNode;
        parent->ch = '\0';
        parent->freq = left->freq + right->freq;
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    // Generate Huffman codes from Huffman tree
    HuffmanNode *root = pq.top();
    pq.pop();
    string code = "";
    unordered_map<char, string> huffmanCodeMap;
    function<void(HuffmanNode*, string)> traverseTree = [&](HuffmanNode *node, string code) {
        if (node == nullptr) {
            return;
        }
        if (node->ch != '\0') {
            huffmanCodeMap[node->ch] = code;
        }
        traverseTree(node->left, code + "0");
        traverseTree(node->right, code + "1");
    };
    traverseTree(root, code);
    huffmanCodes = huffmanCodeMap;
}

// Encode input file using Huffman codes and write to output file
void encodeFile(string inputFilePath, string outputFilePath, unordered_map<char, string> &huffmanCodes) {
    ifstream inputFile(inputFilePath);
    ofstream outputFile(outputFilePath);
    char ch;
    while (inputFile.get(ch)) {
        outputFile << huffmanCodes[ch];
    }
    inputFile.close();
    outputFile.close();
}

// Write Huffman codes and compressed data to output file
void writeCompressedData(string inputFilePath, unordered_map<char, string> &huffmanCodes, string outputFilePath) {
    // Open input file for reading
    ifstream inputFile(inputFilePath, ios::binary);
    inputFile.seekg(0, ios::end);
    int fileSize = inputFile.tellg();
    inputFile.seekg(0, ios::beg);

    // Write Huffman codes to output file
    ofstream outputFile(outputFilePath, ios::binary);
    for (auto pair : huffmanCodes) {
        char ch = pair.first;
        string code = pair.second;
        int codeLength = code.length();
        outputFile.write(reinterpret_cast<const char*>(&ch), sizeof(ch));
        outputFile.write(reinterpret_cast<const char*>(&codeLength), sizeof(codeLength));
        for (char bit : code) {
            outputFile.write(reinterpret_cast<const char*>(&bit), sizeof(bit));
        }
    }

    // Compress data using Huffman codes and write to output file
    int bitsWritten = 0;
    char byte = 0;
    int byteIndex = 7;
    for (int i = 0; i < fileSize; i++) {
        char ch = inputFile.get();
        string code = huffmanCodes[ch];
        for (char bit : code) {
            if (bit == '1') {
                byte |= (1 << byteIndex);
            }
            byteIndex--;
            if (byteIndex < 0) {
                outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
                byte = 0;
                byteIndex = 7;
                bitsWritten += 8;
            }
        }
    }
    if (byteIndex != 7) {
        outputFile.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
        bitsWritten += (7 - byteIndex);
    }
    inputFile.close();
    outputFile.close();

    cout << "Compressed file written to " << outputFilePath << endl;
    cout << "Original file size: " << fileSize << " bytes" << endl;
    cout << "Compressed file size: " << bitsWritten / 8 << " bytes" << endl;
}

int main() {
    string inputFilePath = "input.txt";
    string outputFilePath = "output.bin";
    // Generate Huffman codes from input file
    unordered_map<char, string> huffmanCodes;
    buildHuffmanTree(inputFilePath, huffmanCodes);

    // Encode input file using Huffman codes and write to output file
    writeCompressedData(inputFilePath, huffmanCodes, outputFilePath);

    unordered_map<string, char> huffmanCodesMap;
    // reverse the huffman codes map and store it in huffmanCodesMap
    
    return 0;
}
