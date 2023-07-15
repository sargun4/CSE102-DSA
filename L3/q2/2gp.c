#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 10001

int a[MAXN];

struct node {
    int val;
    struct node *left;
    struct node *right;
};

int max(int a, int b) {
    return a > b ? a : b;
}

int height(int i, int n) {
    if (n == 0) {
        return 0;
    }
    if (i >= n || a[i] == -1) {
        return 0;
    }
    int lht = height(2 * i + 1, n);
    int rht = height(2 * i + 2, n);
    return max(lht, rht) + 1;
}

int diameter(int i, int n) {
    if (n == 0) {
        return 0;
    }
    if (i >= n || a[i] == -1) {
        return 0;
    }
    int lht = height(2 * i + 1, n);
    int rht = height(2 * i + 2, n);
    int ldiam = diameter(2 * i + 1, n);
    int rdiam = diameter(2 * i + 2, n);
    return max(lht + rht + 1, max(ldiam, rdiam));
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int ht = height(0, n);
    printf("%d\n", ht);
    int diam = diameter(0, n);
    printf("%d\n", diam);
    printf("%d\n", abs(ht - diam));
    return 0;
}
