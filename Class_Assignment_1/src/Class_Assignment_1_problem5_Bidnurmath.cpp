#include <iostream>

using namespace std;

void printArray(const int arr[], int n){
    for(int i=0;i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
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
void mergeSort(int arr[], int low, int high, int &comparisons, int &finalMerge){
    if(low<high){
        cout<<"split: ";
        printArray(arr+low, high-low+1);
        int mid = (low+high)/2; //base condition that is keep splitting until this condition is true
        mergeSort(arr, low, mid, comparisons, finalMerge);
        mergeSort(arr, mid+1, high, comparisons, finalMerge);
        int before = comparisons;
        merge(arr, low, mid, high, comparisons);
        finalMerge = comparisons - before; //the last merge to run is the top level one, so this ends up holding the final merge
        cout<<"merged: ";
        printArray(arr+low, high-low+1);
        
    }
    
}

int main(){
    int A[] = {34, 7, 23, 32, 5, 62, 14, 19};
    int n = sizeof(A) / sizeof(A[0]);
    int comparisons = 0, finalMerge = 0;

    cout << "original: ";
    printArray(A, n);
    mergeSort(A, 0, n - 1, comparisons, finalMerge);
    cout << "sorted: ";
    printArray(A, n);
    cout << "comparisons: " << comparisons << " (final merge: " << finalMerge << ")\n\n";

    // sorted copy and reversed copy of A 
    int S[] = {5, 7, 14, 19, 23, 32, 34, 62};
    comparisons = 0;
    finalMerge = 0;
    cout << "sorted copy\n";
    cout << "original: ";
    printArray(S, n);
    mergeSort(S, 0, n - 1, comparisons, finalMerge);
    cout << "sorted: ";
    printArray(S, n);
    cout << "comparisons: " << comparisons << " (final merge: " << finalMerge << ")\n\n";

    int R[] = {62, 34, 32, 23, 19, 14, 7, 5};
    comparisons = 0;
    finalMerge = 0;
    cout << "reversed copy\n";
    cout << "original: ";
    printArray(R, n);
    mergeSort(R, 0, n - 1, comparisons, finalMerge);
    cout << "sorted: ";
    printArray(R, n);
    cout << "comparisons: " << comparisons << " (final merge: " << finalMerge << ")\n";

    return 0;
}