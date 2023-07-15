#include <stdio.h>
// insertionsort
void insertionsort(int arr[],int n){
    int key,i,j;
    for(i=1;i<n;i++){
        key=arr[i];
        j=i-1;
        while (j>=0 && key<arr[j]){
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
    }
}
// bubblesort
void bubblesort(int arr[],int n){
    int i,j;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if( arr[j]>arr[j+1]){
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
// selectionsort
void selectionsort(int arr[],int n){
    int i,j,minidx,temp;
    for(i=0;i<n;i++){
        minidx=i;
        for(j=i+1;j<n;j++){
            if(arr[minidx]>arr[j]){
                minidx=j;
            }
        }
        temp=arr[i];
        arr[i]=arr[minidx];
        arr[minidx]=temp;
    }
}
// mergesort
void merge(int arr[], int left[], int left_size, int right[], int right_size) {
    int i = 0, j = 0, k = 0;
    while (i < left_size && j < right_size) {
        if (left[i] < right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < right_size) {
        arr[k] = right[j];
        j++;
        k++;
    }
}
void mergesort(int arr[], int n) {
    if (n < 2) {
        return;
    }
    int mid = n / 2;
    int left[mid];
    int right[n - mid];
    for (int i = 0; i < mid; i++) {
        left[i] = arr[i];
    }
    for (int i = mid; i < n; i++) {
        right[i - mid] = arr[i];
    }
    mergesort(left, mid);
    mergesort(right, n - mid);
    merge(arr, left, mid, right, n - mid);
}


// quicksort
int partition(int arr[],int low,int high){
    int pivot,i,j;
    pivot=arr[high];
    i=low-1;
    for(j=low;j<high;j++){
        if(arr[j]<=pivot){
            i++;
            int temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;
        }
    }
    int temp2=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp2;
    return i+1;
}

void quicksort(int arr[],int low,int high){
    int pivot;
    if(low<high){
        pivot=partition(arr,low,high);
        quicksort(arr,low,pivot-1);
        quicksort(arr,pivot+1,high);
    }
}


int main() {
    int arr[100], n, i;
    char choice;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("Enter the elements of the array:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the sorting algorithm you want to use (bubble, selection, insertion, merge, quick): ");
    scanf(" %c", &choice);
    switch (choice) {
        case 'b':
        case 'B':
            bubblesort(arr, n);
            break;

        case 's':
        case 'S':
            selectionsort(arr, n);
            break;
        
        case 'i':
        case 'I':
            insertionsort(arr, n);
            break;
        
        case 'm':
        case 'M':
            mergesort(arr, n);
            break;
        
        case 'q':
        case 'Q':
            quicksort(arr, 0, n-1);
            break;
        
        default:
            printf("Invalid choice.\n");
            return 1;
    }
    printf("Sorted array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}