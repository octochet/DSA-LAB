#include <iostream>
#include <queue>

using namespace std;


class MedianFinder {
private:
    int max_heap_weight=0, min_heap_weight=0,total_weight=0;
    priority_queue<pair<int, int>> max_heap; // stores the smaller half of the elements
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap; 
    // stores the larger half of the elements
public:
    void insert(int num, int weight) {
        if(max_heap.empty()) {
            max_heap.push({num, weight});
            max_heap_weight+=weight;
            total_weight+=weight;
            return;
        }
        if (max_heap.empty() || num <= max_heap.top().first) {
            max_heap.push({num, weight});
            max_heap_weight+=weight;
            total_weight+=weight;
        }
        else {
            min_heap.push({num, weight});
            min_heap_weight+=weight;
            total_weight+=weight;
        }

        // Rebalance the heaps
        if (max_heap.size() > min_heap.size() + 1) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            max_heap_weight-=elem.second;
            min_heap.push(elem);
            min_heap_weight+=elem.second;
        }
        else if (min_heap.size() > max_heap.size()) {
            pair<int, int> elem = min_heap.top();
            min_heap.pop();
            min_heap_weight-=elem.second;
            max_heap.push(elem);
            max_heap_weight+=elem.second;
        }
        
        while(max_heap_weight>min_heap_weight) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            max_heap_weight-=elem.second;
            min_heap.push(elem);
            min_heap_weight+=elem.second;
        }
    }

    void remove(int num) {
        if (!max_heap.empty() && num <= max_heap.top().first) {
            // Remove from the max heap
            priority_queue<pair<int, int>> tmp;
            while (!max_heap.empty()) {
                pair<int, int> elem = max_heap.top();
                max_heap.pop();
                max_heap_weight-=elem.second;
                if (elem.first != num)
                    tmp.push(elem);
            }
            while (!tmp.empty()) {
                pair<int, int> elem = tmp.top();
                tmp.pop();
                max_heap.push(elem);
                max_heap_weight+=elem.second;
            }
        }
        else {
            // Remove from the min heap
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tmp;
            while (!min_heap.empty()) {
                pair<int, int> elem = min_heap.top();
                min_heap.pop();
                min_heap_weight-=elem.second;
                if (elem.first != num)
                    tmp.push(elem);
            }
            while (!tmp.empty()) {
                pair<int, int> elem = tmp.top();
                tmp.pop();
                min_heap.push(elem);
                min_heap_weight+=elem.second;
            }
        }

        // Rebalance the heaps
        if (max_heap.size() > min_heap.size() + 1) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            max_heap_weight-=elem.second;
            min_heap.push(elem);
            min_heap_weight+=elem.second;
        }
        else if (min_heap.size() > max_heap.size()) {
            pair<int, int> elem = min_heap.top();
            min_heap.pop();
            min_heap_weight-=elem.second;
            max_heap.push(elem);
            max_heap_weight+=elem.second;
        }
        while(max_heap_weight>min_heap_weight) {
            pair<int, int> elem = max_heap.top();
            max_heap.pop();
            max_heap_weight-=elem.second;
            min_heap.push(elem);
            min_heap_weight+=elem.second;
        }
    }

    pair<int, int> getMedian() {
        return max_heap.top();
    }

    void print() {
        cout << "Max heap: ";
        priority_queue<pair<int, int>> tmp = max_heap;
        while (!tmp.empty()) {
            pair<int, int> elem = tmp.top();
            tmp.pop();
            cout << elem.first << " ";
        }
        cout << endl;

        cout << "Min heap: ";
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tmp1 = min_heap;
        while (!tmp1.empty()) {
            pair<int, int> elem = tmp1.top();
            tmp1.pop();
            cout << elem.first << " ";
        }
        cout << endl;
    }
};

int main() {
    MedianFinder mf;

    // Insert elements with weights
    mf.insert(1, 5);
    mf.insert(2, 4);
    mf.insert(3, 3);
    mf.insert(4, 2);
    mf.insert(5, 1);
    mf.insert(6, 6);

    // Remove an element
    // mf.insert(1,1);
    // mf.insert(2,2);

    // Get the median
    pair<int, int> firstMedian = mf.getMedian();
    cout << "Median: " << firstMedian.first << ", weight: " << firstMedian.second << endl;
    mf.print();
    
    // mf.remove(6);
    // pair<int, int> SecondMedian = mf.getMedian();
    // cout << "Median: " << SecondMedian.first << ", weight: " << SecondMedian.second << endl;
    // mf.print();
    // int choice;
    // while(true) {
    //     cout<<"1. Insert\n2. Remove\n3. Exit\n";
    //     cout<<"Enter your choice: ";
    //     cin>>choice;
    //     switch (choice)
    //     {
    //     case 1:
    //     {
    //         int num, weight;
    //         cout<<"Enter number and weight: ";
    //         cin>>num>>weight;
    //         mf.insert(num, weight);
    //         pair<int, int> median = mf.getMedian();
    //         cout<<"\n";
    //         cout << "Median: " << median.first << ", weight: " << median.second << endl;
    //         cout<<"\n";
    //         break;
    //     }
    //     case 2:
    //     {
    //         int num1;
    //         cout<<"Enter number to remove: ";
    //         cin>>num1;
    //         mf.remove(num1);
    //         pair<int, int> median = mf.getMedian();
    //         cout<<"\n";
    //         cout << "Median: " << median.first << ", weight: " << median.second << endl;
    //         cout<<"\n";
    //         break;
    //     }
    //     case 3:
    //         exit(0); 
    //     default:
    //         break;
    //     }
    // }
    return 0;
}
