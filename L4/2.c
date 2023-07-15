#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    long long paintings;
    long long boredom;
} ArtGallery;

void merge(ArtGallery* arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    ArtGallery L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        long long diffA = llabs(L[i].paintings - ceil(L[i].paintings / 2.0));
        long long diffB = llabs(R[j].paintings - ceil(R[j].paintings / 2.0));

        if (diffA < diffB || (diffA == diffB && L[i].boredom < R[j].boredom)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(ArtGallery* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, k;
        scanf("%d %d", &n, &k);

        ArtGallery* galleries = malloc(n * sizeof(ArtGallery));

        for (int i = 0; i < n; i++) {
            scanf("%lld", &galleries[i].paintings);
        }

        for (int i = 0; i < n; i++) {
            scanf("%lld", &galleries[i].boredom);
        }

        mergeSort(galleries, 0, n - 1);

        long long paintingsLeft = 0;
        long long totalBoredom = 0;

        for (int i = 0; i < n; i++) {
            long long seenPaintings = ceil(galleries[i].paintings / 2.0);
            paintingsLeft += galleries[i].paintings - seenPaintings;
            totalBoredom += galleries[i].boredom * seenPaintings;
        }

        printf("%lld %lld\n", paintingsLeft, totalBoredom);

        free(galleries);
    }

    return 0;
}
