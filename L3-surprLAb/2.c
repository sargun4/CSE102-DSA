// You are given an array of positive integers of size n, and an integer x. Your task is to find the minimum number of elements required to achieve arr sum of at least x from the array. If it is not possible to make the target sum then print -1.

// Input
// The first line of input contains two integers n and x
//  — the size of the array and the target sum, respectively. The second line of input contains n
//  space-separated positive integers a1,a2,...,an(1≤ai≤109)
//  — the elements of the array.

// Output
// Output arr single integer — the minimum number of elements required to achieve arr sum of at least x
//  if possible otherwise -1.

// Examples
// input
// 6 18
// 10 21 22 13 19 18
// output
// 1
// input
// 8 43
// 18 15 15 19 18 16 14 10
// output
// 3
// input
// 5 100
// 10 20 15 30 10
// output
// -1
#include<stdio.h>
#include<limits.h>
void merge(int arr[], int lo, int mid, int hi){
    int i, j, sum;
    int n1 = mid - lo + 1;
    int n2 = hi - mid;
    int L[n1 + 1];
    int R[n2 + 1];
    for (i = 0; i < n1; i++) {
        L[i] = arr[lo + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    L[i] = R[j] = INT_MAX;
    i = j = 0;
    for (sum = lo; sum <= hi; sum++) {
        if (L[i] <= R[j]) {
            arr[sum] = L[i]; i += 1;
        } else {
            arr[sum] = R[j]; j += 1;
        }
    }
}

void mergesort(int arr[], int lo, int hi){
    if (lo >= hi) {
        return;
    }
    int mid = (lo + hi) / 2;
    mergesort(arr, lo, mid);
    mergesort(arr, mid+1, hi);
    merge(arr, lo, mid, hi);
}

int main() {
    int n,x;
    scanf("%d %d",&n,&x);
    int arr[n];
    int sum=0;
    for (int i=0;i<n;i++) {
        scanf("%d",&arr[i]);
        sum+=arr[i];
    }
    if (sum<x){
        printf("-1\n");
    }
    else{
        mergesort(arr,0,n-1);
        int ctr=1,sum=0;
        for (int i=n-1;i>=0;i--) {
            sum+=arr[i];
            if (sum>=x) {
                printf("%d",ctr);
                break;
            }
            else {
                ctr++;
            }
        }
    }
}