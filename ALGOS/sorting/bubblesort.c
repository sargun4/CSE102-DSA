// Time Complexity: O(N^2)-avg,worstcase ;bestcase-O(n)
// Space complexity: O(1) 
// stable
// maxno of swaps=(n*(n-1))/2
#include <stdio.h>
void bubblesort(int arr[],int n){
    int i,j,temp;
    // n=len(arr)
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}
int main(){
    int arr[]={1,2,35,1,4,2};
    int n=sizeof(arr)/sizeof(arr[0]);
    bubblesort(arr,n);
    int i;
    for(i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    return 0;
}


//2
// Optimized implementation of Bubble sort
#include <stdio.h>
#include <stdbool.h>

void swap(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void bubbleSort(int arr[], int n){
int i, j;
bool swapped;
for (i = 0; i < n-1; i++){
	swapped = false;
	for (j = 0; j < n-i-1; j++)
	{
		if (arr[j] > arr[j+1])
		{
		swap(&arr[j], &arr[j+1]);
		swapped = true;
		}	}
	// IF no two elements were swapped by inner loop, then break
	if (swapped == false)
		break;
}}
void printArray(int arr[], int size){ 
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);}
int main(){
	int arr[] = {64, 34, 25, 12, 22, 11, 90};
	int n = sizeof(arr)/sizeof(arr[0]);
	bubbleSort(arr, n);
	printf("Sorted array: \n");
	printArray(arr, n);
	return 0;  }
