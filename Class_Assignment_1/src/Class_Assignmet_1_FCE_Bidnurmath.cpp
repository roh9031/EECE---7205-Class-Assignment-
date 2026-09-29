#include <iostream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <limits>

using namespace std;

void printarr(vector<int> &arr){
    int n = arr.size();
    cout<<"sorted array: ";
    for(int i=0;i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<"\n\n";
}
void swap(int &a,int &b){
    int temp = a;
    a=b;
    b=temp;
}

void bubblesort(vector<int> &arr, int n){
    for (int i=0;i<n-1; i++){
        bool swapped = false;
        for (int j=0; j<n-i-1; j++){
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

void insertionsort(vector<int>&arr, int n){
    for(int i=1; i<n; i++){
        int key = arr[i];
        int j = i-1;
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key; 
    }
}

void selectionsort(vector<int> &arr, int n){
    for(int i = 0; i<n-1; i++){
        int minidx = i;
        for (int j =i+1; j<n; j++){
            if(arr[j]<arr[minidx]){
                minidx = j;
            } 
        }
        swap(arr[i], arr[minidx]);
    }
}

int partition(vector<int> & arr, int l, int r){
    int pivot = arr[r];
    int swapmarker = l-1;
    for(int currindex=l; currindex<r; currindex++){
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
    swap(arr[swapmarker+1], arr[r]);
    return swapmarker+1;
   
}

void quicksort(vector<int> &arr, int l,int r){
    if(l<r){
        int p = partition(arr, l,r);
        quicksort(arr,l,p-1);
        quicksort(arr,p+1,r);

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

void merge(vector<int>&arr, int left, int mid, int right){
    vector<int> merged(right - left + 1);//temp array to store values
    int i = left;
    int j = mid+1;
    int k = 0;
    while(i <= mid && j<=right){
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

    while(j<=right){
        merged[k]=arr[j];
        j++;
        k++;
    }

    for(int p =0; p<merged.size(); p++){
        arr[left+p]=merged[p];
    }

}
void mergesort(vector<int> &arr, int left, int right){
    if(left<right){
        int mid = left +(right-left)/2; //base condition that is keep splitting until this condition is true
        mergesort(arr, left, mid);
        mergesort(arr, mid+1, right);
        merge(arr, left, mid, right);
        
    }
    
}

void siftdown(std::vector<int> &A, int root, int size) {
    
    while (2 * root + 1 < size) {
        int child = 2 * root + 1; 

        
        if (child + 1 < size && A[child + 1] > A[child]) {
            child = child + 1;
        }

        
        if (A[root] >= A[child]) {
            break;
        }

        
        int temp = A[root];
        A[root] = A[child];
        A[child] = temp;

        
        root = child;
    }
}


void heapsort(std::vector<int> &A) {
    int n = A.size(); 

    
    for (int i =n/2-1; i>= 0; i--) {
        siftdown(A, i, n);
    }

    
    for (int end = n-1; end>=1; end--) {
        
        int temp = A[0];
        A[0] = A[end];
        A[end] = temp;

        
        siftdown(A, 0, end);
    }
}

int main(){
    int choice;
    do{
     int n;
     while (true) {
     cout << "enter size of vector: ";
     string line;
     getline(cin, line);
     stringstream ss(line);
     char extra;
         if (!(ss >> n) || (ss >> extra) || n < 0) {
             cout << "invalid input: enter positive integer only\n";
             continue;
         }
    break;
     }

     if (n == 0) {
         cout << "array is empty\n\n";
         continue;
     }


     vector<int> arr(n);
     cout << "enter vector values:\n";
     for (int i = 0; i < n; i++) {
         while (true) {
             cout << "element " << i + 1 << ": ";
             string line;
             getline(cin, line);
             stringstream ss(line);
             int val;
             char extra;
             if (!(ss >> val) || (ss >> extra)) {
                 cout << "invalid input enter integers only\n";
                 continue;
        }
        arr[i] = val;
        break;
    }
    }

    cout <<"1. bubble sort\n";
    cout <<"2. insertion sort\n";
    cout <<"3. selection sort\n";
    cout <<"4. quick sort\n";
    cout <<"5. merge sort\n";
    cout <<"6. heap sort\n";
    cout <<"7. exit\n";

    cout <<"enter your choice\n"<<flush;

    if (!(cin >> choice) || choice < 1 || choice > 7) {
            cout << "\ninvalid input please enter a number from 1 to 7\n\n";
            cin.clear();               
            cin.ignore(10000, '\n');   
            this_thread::sleep_for(chrono::seconds(2));
            choice = 0;                
            continue;                  
        }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

     switch (choice){
         case 1: 
             bubblesort(arr, n); 
             printarr(arr); 
             break;
         case 2: 
             insertionsort(arr, n); 
             printarr(arr); 
             break;
         case 3: 
             selectionsort(arr, n); 
             printarr(arr); 
             break;
         case 4: 
             quicksort(arr, 0, n - 1); 
             printarr(arr); 
             break;
         case 5: 
             mergesort(arr, 0, n - 1); 
             printarr(arr); 
             break;
         case 6: 
             heapsort(arr); 
             printarr(arr); 
             break;
         case 7: 
             cout<<"exiting program\n"; 
             break;
         default: 
             cout<<"Invalid enter 1 to 7\n";
     }}while(choice!=7);

/*for(int i=0;i<n;i++){
    cout<<arr[i]<<" ";
}
*/

return 0;
}