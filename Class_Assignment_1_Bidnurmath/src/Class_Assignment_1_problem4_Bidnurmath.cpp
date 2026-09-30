#include <iostream>
#include <string>

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

int partition(int arr[], int low, int high, int &comparisons, int depth){
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
                if(depth == 0){ //only the first partition prints i, j and the array after every swap
                    cout<<"  i = "<<swapmarker<<", j = "<<currindex<<": ";
                    printArray(arr+low, high-low+1);
                }
            }
        }

    }
    swap(arr[swapmarker+1], arr[high]);
    if(depth == 0){
        cout<<"  pivot swapped into place, i + 1 = "<<swapmarker+1<<": ";
        printArray(arr+low, high-low+1);
        cout<<"  final position of pivot: index "<<swapmarker+1<<"\n";
    }
    return swapmarker+1;
   
}

void quickSort(int arr[], int low, int high, int &comparisons, int depth){
    if(low<high){
        cout<<string(depth*2, ' ')<<"pivot = "<<arr[high]<<": ";
        printArray(arr+low, high-low+1);
        int p = partition(arr, low, high, comparisons, depth);
        quickSort(arr,low,p-1,comparisons,depth+1);
        quickSort(arr,p+1,high,comparisons,depth+1);

    }

}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0;

    cout << "original: ";
    printArray(A, n);
    quickSort(A, 0, n - 1, comparisons, 0);
    cout << "sorted: ";
    printArray(A, n);
    cout << "comparisons: " << comparisons << "\n\n";

    //run again on an already sorted copy of A 
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;

    cout << "already sorted copy\n";
    cout << "original: ";
    printArray(S, n);
    quickSort(S, 0, n - 1, comparisons, 0);
    cout << "sorted: ";
    printArray(S, n);
    cout << "comparisons: " << comparisons << "\n";

    return 0;
}