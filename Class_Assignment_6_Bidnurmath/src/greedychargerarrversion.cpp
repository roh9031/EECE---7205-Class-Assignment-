#include <iostream>
#include <algorithm>
using namespace std;
void siftDown(int arr[], int root, int size) {
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
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        siftDown(arr, i, n);
    }
    for (int end = n - 1; end >= 1; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, 0, end);
    }
}
// array version the assignment asks for plain arrays (no vector) and input read with cin
// input format n then the n arrival times then the n departure times
int findminchargers(int arr[], int dept[], int n) {
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
    int n;
    int arr[100], dept[100];   // n is at most 100
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    for(int i = 0; i < n; i++){
        cin >> dept[i];
    }
    cout << "Chargers needed: " << findminchargers(arr, dept, n) << endl;
    return 0;
}