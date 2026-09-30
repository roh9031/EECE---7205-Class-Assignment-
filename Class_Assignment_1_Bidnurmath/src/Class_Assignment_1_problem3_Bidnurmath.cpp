#include <iostream>

using namespace std;

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

void selectionSort(int arr[], int n, int &comparisons, int &swaps){
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
            swaps++;
        }
        cout<<"Pass "<<i+1<<": min = "<<arr[i]<<" at index "<<minidx<<" -> ";
        printArray(arr, n);
    }
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0, swaps = 0;

    cout << "original: ";
    printArray(A, n);
    selectionSort(A, n, comparisons, swaps);
    cout << "sorted: ";
    printArray(A, n);
    cout << "comparisons: " << comparisons << " swaps: " << swaps << "\n";

    return 0;
}