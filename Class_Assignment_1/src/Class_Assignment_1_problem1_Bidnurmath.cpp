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

void bubbleSort(int arr[], int n, int &comparisons, int &swaps){
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
                swaps++;
                swapped = true;
            }
        }
        cout<<"Pass "<<i+1<<": ";
        printArray(arr, n);
        if(!swapped){
            break;
        }
    }
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0, swaps = 0;

    cout << "Original: ";
    printArray(A, n);
    bubbleSort(A, n, comparisons, swaps);
    cout << "Sorted: ";
    printArray(A, n);
    cout << "Comparisons: " << comparisons << " Swaps: " << swaps << "\n\n";

    //run again on an already sorted copy of A 
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;
    swaps = 0;

    cout << "already sorted copy\n";
    cout << "original: ";
    printArray(S, n);
    bubbleSort(S, n, comparisons, swaps);
    cout << "sorted: ";
    printArray(S, n);
    cout << "comparisons: " << comparisons << " swaps: " << swaps << "\n";

    return 0;
}