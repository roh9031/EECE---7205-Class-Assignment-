#include <iostream>

using namespace std;

void printArray(const int arr[], int n){
    for(int i=0;i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}

void siftDown(int arr[], int root, int size, int &swaps) {
    
    while (2 * root + 1 < size) {
        int child = 2 * root + 1; 

        
        if (child + 1 < size && arr[child + 1] > arr[child]) {
            child = child + 1;
        }

        
        if (arr[root] >= arr[child]) {
            break;
        }

        
        int temp = arr[root];
        arr[root] = arr[child];
        arr[child] = temp;
        swaps++; //only swaps made inside siftDown are counted

        
        root = child;
    }
}


void heapSort(int arr[], int n, int &swaps) {

    
    for (int i =n/2-1; i>= 0; i--) {
        siftDown(arr, i, n, swaps);
    }
    cout << "Heap: ";
    printArray(arr, n);

    
    for (int end = n-1; end>=1; end--) {
        
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;

        
        siftDown(arr, 0, end, swaps);
        cout << "end = " << end << ": heap:   ";
        printArray(arr, end);
        cout << "         sorted: ";
        printArray(arr + end, n - end);
    }
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int swaps = 0;

    cout << "original: ";
    printArray(A, n);
    heapSort(A, n, swaps);
    cout << "sorted: ";
    printArray(A, n);
    cout << "swaps in siftDown: " << swaps << "\n";

    return 0;
}