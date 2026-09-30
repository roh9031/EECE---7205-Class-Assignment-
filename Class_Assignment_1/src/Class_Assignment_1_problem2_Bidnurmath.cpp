#include <iostream>

using namespace std;

void printArray(const int arr[], int n){
    for(int i=0;i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
}

void insertionSort(int arr[], int n, int &comparisons, int &shifts){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && (comparisons++, arr[j]>key)){
            arr[j+1]=arr[j];
            shifts++;
            j--;
        }
        arr[j+1]=key; 
        cout<<"i = "<<i<<", key = "<<key<<": ";
        printArray(arr, n);
    }
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0, shifts = 0;

    cout << "original: ";
    printArray(A, n);
    insertionSort(A, n, comparisons, shifts);
    cout << "sorted: ";
    printArray(A, n);
    cout << "comparisons: " << comparisons << " Shifts: " << shifts << "\n\n";

    //fewest shifts (already sorted) and most shifts (reversed)
    int best[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;
    shifts = 0;
    cout << "best case (sorted ordering)\n";
    cout << "original: ";
    printArray(best, n);
    insertionSort(best, n, comparisons, shifts);
    cout << "sorted: ";
    printArray(best, n);
    cout << "comparisons: " << comparisons << " Shifts: " << shifts << "\n\n";

    int worst[] = {62, 34, 32, 23, 19, 14, 7, 5};
    comparisons = 0;
    shifts = 0;
    cout << "worst case (reversed ordering)\n";
    cout << "original: ";
    printArray(worst, n);
    insertionSort(worst, n, comparisons, shifts);
    cout << "sorted: ";
    printArray(worst, n);
    cout << "comparisons: " << comparisons << " shifts: " << shifts << "\n";

    return 0;
}