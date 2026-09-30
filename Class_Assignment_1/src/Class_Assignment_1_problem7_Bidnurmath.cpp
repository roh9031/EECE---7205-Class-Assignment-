#include <iostream>
#include <iomanip>
#include <chrono>
#include <random>
#include <string>

using namespace std;

//step by step printing is turned off in this file, only printArray on the first 10 sorted elements is used

void printArray(const int arr[], int n){
    for(int i=0;i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}

void swap(int &a,int &b){
    int temp = a;
    a=b;
    b=temp;
}

void bubbleSort(int arr[], int n, int &comparisons){
    for (int i=0;i<n-1; i++){
        bool swapped = false;
        for (int j=0; j<n-i-1; j++){
            comparisons++;
            if (arr[j]>arr[j+1]){
                /* or do
                int temp = arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
                which is basically what the built in fucntion swap does
                */
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(!swapped){
            break;
        }
    }
}

void insertionSort(int arr[], int n, int &comparisons){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && (comparisons++, arr[j]>key)){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key; 
    }
}

void selectionSort(int arr[], int n, int &comparisons){
    for(int i = 0; i<n-1; i++){
        int minidx = i;
        for (int j =i+1; j<n; j++){
            comparisons++;
            if(arr[j]<arr[minidx]){
                minidx = j;
            } 
        }
        if(minidx != i){
            swap(arr[i], arr[minidx]);
        }
    }
}

int partition(int arr[], int low, int high, int &comparisons){
    int pivot = arr[high];
    int swapmarker = low-1;
    for(int currindex=low; currindex<high; currindex++){
        comparisons++;
        if (arr[currindex]>pivot){
            continue;
        }
        if (arr[currindex]<=pivot){
            swapmarker++;
            if(swapmarker == currindex){
                continue;
            }
            if(currindex>swapmarker){
                swap(arr[swapmarker], arr[currindex]);
            }
        }

    }
    swap(arr[swapmarker+1], arr[high]);
    return swapmarker+1;
   
}

void quickSort(int arr[], int low, int high, int &comparisons){
    if(low<high){
        int p = partition(arr, low, high, comparisons);
        quickSort(arr,low,p-1,comparisons);
        quickSort(arr,p+1,high,comparisons);

    }

}

/* i am not sure if push_back can be used so i will use a third pointer pointing to the temp merged array and copy
the value instead

void merge(vector<int> &arr, int left, int mid, int right){
    vector<int> merged; //temp to hold merged arrays
    int i = left;
    int j = mid+1;
    while(i<=mid && j<=right){
        if(arr[i]<=arr[j]){
            merged.push_back(arr[i]);
            i++;
        }
        else{
            merged.push_back(arr[j]);
        }
    }
    while(i<=mid){
        merged.push_back(arr[i]);
        i++;
    }
    while(j<=mid){
        merged.push_back(arr[j]);
        j++;
    }
    for(int i=0; i<merged.size(); i++){
        arr[left+i]=merged[i];
    }

} */

void merge(int arr[], int low, int mid, int high, int &comparisons){
    int *merged = new int[high - low + 1];//temp array to store values
    int i = low;
    int j = mid+1;
    int k = 0;
    while(i <= mid && j<=high){
        comparisons++;
        if(arr[i]<=arr[j]){
            merged[k]=arr[i];
            i++;
            k++;
        }
        else{
            merged[k]=arr[j];
            j++;
            k++;
        }
    }

    while(i<=mid){
        merged[k]=arr[i];
        i++;
        k++;
    }

    while(j<=high){
        merged[k]=arr[j];
        j++;
        k++;
    }

    for(int p =0; p<high-low+1; p++){
        arr[low+p]=merged[p];
    }

    delete[] merged;

}
void mergeSort(int arr[], int low, int high, int &comparisons){
    if(low<high){
        int mid = (low+high)/2; //base condition that is keep splitting until this condition is true
        mergeSort(arr, low, mid, comparisons);
        mergeSort(arr, mid+1, high, comparisons);
        merge(arr, low, mid, high, comparisons);
        
    }
    
}

void siftDown(int arr[], int root, int size, int &comparisons) {
    
    while (2 * root + 1 < size) {
        int child = 2 * root + 1; 

        
        if (child + 1 < size) {
            comparisons++;
            if (arr[child + 1] > arr[child]) {
                child = child + 1;
            }
        }

        
        comparisons++;
        if (arr[root] >= arr[child]) {
            break;
        }

        
        int temp = arr[root];
        arr[root] = arr[child];
        arr[child] = temp;

        
        root = child;
    }
}


void heapSort(int arr[], int n, int &comparisons) {

    
    for (int i =n/2-1; i>= 0; i--) {
        siftDown(arr, i, n, comparisons);
    }

    
    for (int end = n-1; end>=1; end--) {
        
        int temp = arr[0];
        arr[0] = arr[end];
        arr[end] = temp;

        
        siftDown(arr, 0, end, comparisons);
    }
}

int main(){
    string names[6] = {"bubble sort", "insertion sort", "selection sort", "quick sort", "merge sort", "heap sort"};
    int comparisons;

    // comparisons on A, sorted copy of A and reversed copy of A 
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    int R[] = {62, 34, 32, 23, 19, 14, 7, 5};
    int *inputs[3] = {A, S, R};

    cout << "comparisons (n = 8)\n";
    cout << setw(16) << "algorithm" << setw(10) << "A" << setw(10) << "sorted" << setw(10) << "reversed" << "\n";
    for (int k = 0; k < 6; k++) {
        cout << setw(16) << names[k];
        for (int t = 0; t < 3; t++) {
            int c[8];
            for (int i = 0; i < n; i++) {
                c[i] = inputs[t][i];
            }
            comparisons = 0;
            switch (k) {
                case 0: bubbleSort(c, n, comparisons); break;
                case 1: insertionSort(c, n, comparisons); break;
                case 2: selectionSort(c, n, comparisons); break;
                case 3: quickSort(c, 0, n - 1, comparisons); break;
                case 4: mergeSort(c, 0, n - 1, comparisons); break;
                case 5: heapSort(c, n, comparisons); break;
            }
            cout << setw(10) << comparisons;
        }
        cout << "\n";
    }
    cout << "\n";

    // timing on random arrays, same data copied for every algorithm 
    int sizes[3] = {1000, 5000, 10000};
    mt19937 rng(42);
    uniform_int_distribution<int> dist(1, 100000);

    for (int s = 0; s < 3; s++) {
        int size = sizes[s];
        int *base = new int[size];
        int *c = new int[size];
        for (int i = 0; i < size; i++) {
            base[i] = dist(rng);
        }

        cout << "size " << size << "\n";
        for (int k = 0; k < 6; k++) {
            for (int i = 0; i < size; i++) {
                c[i] = base[i];
            }
            comparisons = 0;

            auto start = chrono::high_resolution_clock::now();
            switch (k) {
                case 0: bubbleSort(c, size, comparisons); break;
                case 1: insertionSort(c, size, comparisons); break;
                case 2: selectionSort(c, size, comparisons); break;
                case 3: quickSort(c, 0, size - 1, comparisons); break;
                case 4: mergeSort(c, 0, size - 1, comparisons); break;
                case 5: heapSort(c, size, comparisons); break;
            }
            auto end = chrono::high_resolution_clock::now();

            double ms = chrono::duration<double, milli>(end - start).count();
            cout << setw(16) << names[k] << setw(12) << fixed << setprecision(3) << ms << " ms   first 10: ";
            printArray(c, 10);
        }
        cout << "\n";

        delete[] base;
        delete[] c;
    }

    return 0;
}