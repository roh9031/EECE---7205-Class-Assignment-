#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void siftDown(vector<int>& arr, int root, int size) {
    while (2 * root + 1 < size) {
        int child = 2 * root + 1;
        if (child + 1 < size && arr[child + 1] > arr[child]) {
            child = child + 1;
        }
        if (arr[root] >= arr[child]) {
            break;
        }
        swap(arr[root], arr[child]);
        root = child;
    }
}

void heapSort(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n);
    }
    for (int end = n - 1; end >= 1; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, 0, end);
    }
}

// i am assuming the arrival and dept times come in vector int pairs rather than 2 separate vectors named arr and dept
int findminchargers(const vector<pair<int,int>> vehicles) {
    int n = vehicles.size();
    vector<int> arr(n), dept(n);
    for(int i = 0; i < n; i++){
        arr[i] = vehicles[i].first;
        dept[i] = vehicles[i].second;
    }
    heapSort(arr, n);
    heapSort(dept, n);

    int i = 0, j = 0;
    int chargers = 0;
    int maxChargers = 0;
    while(i < n){
        if(arr[i] >= dept[j]){
            chargers--;
            j++;
        } else {
            chargers++;
            maxChargers = max(maxChargers, chargers);
            i++;
        }
    }
    return maxChargers;
}

int main() {
    cout<<"Test case: all arrive together - {900,1000},{900,1000},{900,1000},{900,1000}\n";
    vector<pair<int,int>> test1 = {{900,1000},{900,1000},{900,1000},{900,1000}};
    cout << "Chargers needed: " << findminchargers(test1)<<"\n" << endl;

    cout<<"Test case: all arrive back to back - {900,1000},{1000,1100},{1100,1200}\n"; 
    vector<pair<int,int>> test2 = {{900,1000},{1000,1100},{1100,1200}};
    cout << "Chargers needed: " << findminchargers(test2)<<"\n" << endl;

    cout<<"Test case: random timings - {800,900},{815,845},{830,1000},{845,930},{900,1015},{1000,1030}\n"; 
    vector<pair<int,int>> test3 = {{800,900},{815,845},{830,1000},{845,930},{900,1015},{1000,1030}};
    cout << "Chargers needed: " << findminchargers(test3) << endl;

    return 0;
}   