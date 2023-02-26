#include <iostream>
#include <queue>

using namespace std;

class MedianFinder {
private:
    priority_queue<pair<int, int>> max_heap; // stores the smaller half of the elements
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap; // stores the larger half of the elements

public:
    void insert(int num, int weight) {
        if (max_heap.empty() || num <= max_heap.top().first)
            max_heap.push({num, weight});
        else
            min_heap.push({num, weight});

        // Rebalance the heaps
        if (max_heap.size() > min_heap.size() + 1) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            min_heap.push(elem);
        }
        else if (min_heap.size() > max_heap.size()) {
            pair<int, int> elem = min_heap.top();
            min_heap.pop();
            max_heap.push(elem);
        }
    }

    void remove(int num) {
        if (!max_heap.empty() && num <= max_heap.top().first) {
            // Remove from the max heap
            priority_queue<pair<int, int>> tmp;
            while (!max_heap.empty()) {
                pair<int, int> elem = max_heap.top();
                max_heap.pop();
                if (elem.first != num)
                    tmp.push(elem);
            }
            while (!tmp.empty()) {
                pair<int, int> elem = tmp.top();
                tmp.pop();
                max_heap.push(elem);
            }
        }
        else {
            // Remove from the min heap
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tmp;
            while (!min_heap.empty()) {
                pair<int, int> elem = min_heap.top();
                min_heap.pop();
                if (elem.first != num)
                    tmp.push(elem);
            }
            while (!tmp.empty()) {
                pair<int, int> elem = tmp.top();
                tmp.pop();
                min_heap.push(elem);
            }
        }

        // Rebalance the heaps
        if (max_heap.size() > min_heap.size() + 1) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            min_heap.push(elem);
        }
        else if (min_heap.size() > max_heap.size()) {
            pair<int, int> elem = min_heap.top();
            min_heap.pop();
            max_heap.push(elem);
        }
    }

    pair<int, int> getMedian() {
        return max_heap.top();
    }
};

int main() {
    MedianFinder mf;

    // // Insert elements with weights
    // mf.insert(10, 4);
    // mf.insert(1, 1);
    // mf.insert(3, 2);
    // mf.insert(9, 3);
    // mf.insert(4, 10);

    // // Remove an element
    // // mf.remove(3);

    // // Get the median
    // pair<int, int> median = mf.getMedian();
    // cout << "Median: " << median.first << ", weight: " << median.second << endl;
    int choice;
    while(true) {
        cout<<"1. Insert\n2. Remove\n3. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        switch (choice)
        {
        case 1:
        {
            int num, weight;
            cout<<"Enter number and weight: ";
            cin>>num>>weight;
            mf.insert(num, weight);
            pair<int, int> median = mf.getMedian();
            cout<<"\n";
            cout << "Median: " << median.first << ", weight: " << median.second << endl;
            cout<<"\n";
            break;
        }
        case 2:
        {
            int num1;
            cout<<"Enter number to remove: ";
            cin>>num1;
            mf.remove(num1);
            pair<int, int> median = mf.getMedian();
            cout<<"\n";
            cout << "Median: " << median.first << ", weight: " << median.second << endl;
            cout<<"\n";
            break;
        }
        case 3:
            exit(0); 
        default:
            break;
        }
    }
    return 0;
}
