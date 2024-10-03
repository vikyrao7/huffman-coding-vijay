#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

// A Huffman Tree node
struct MinHeapNode {
    char data;             // One of the input characters
    int freq;              // Frequency of the character
    MinHeapNode *left, *right; // Left and right children

    MinHeapNode(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparison object for min heap
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r) {
        return (l->freq > r->freq);
    }
};

// Preorder traversal to print Huffman codes
void printCodes(struct MinHeapNode* root, string str) {
    if (!root)
        return;

    // If this is a leaf node, then it contains a character
    if (root->data != '#')
        cout << root->data << ": " << str << "\n";

    // Traverse the left and right children
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Function to build the Huffman tree and generate codes
void HuffmanCodes(vector<char>& data, vector<int>& freq) {
    struct MinHeapNode *left, *right, *top;

    // Create a min-heap and insert all characters of data[]
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

    for (int i = 0; i < data.size(); ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while the size of the heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two nodes with the lowest frequency
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes' frequencies
        top = new MinHeapNode('#', left->freq + right->freq);

        // Set the two extracted nodes as left and right children
        top->left = left;
        top->right = right;

        // Add this node to the min-heap
        minHeap.push(top);
    }

    // The remaining node is the root of the Huffman Tree
    printCodes(minHeap.top(), "");
}

int main() {
    string S = "abcdef";
    vector<int> freq = {5, 9, 12, 13, 16, 45};
    
    vector<char> data(S.begin(), S.end());

    // Build Huffman Tree and print codes
    HuffmanCodes(data, freq);

    return 0;
}
