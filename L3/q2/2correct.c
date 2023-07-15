#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 10005

int n, a[MAXN];

int get_height() {
    int height = 0;
    for (int i = 1; i <= n; i = i * 2 + 1) {
        height++;
    }
    return height;
}

int get_diameter() {
    int diameter = 0;
    int l = 1, r = 1;
    for (int i = 1; i < n; i = i * 2 + 1) {
        r = r * 2 + 1;
    }
    for (int i = l; i <= r; i++) {
        int d1 = 0, d2 = 0;
        if (a[i] != -1) {
            for (int j = i + 1; j <= r; j++) {
                if (a[j] != -1) {
                    d1++;
                } else {
                    break;
                }
            }
            for (int j = i - 1; j >= l; j--) {
                if (a[j] != -1) {
                    d2++;
                } else {
                    break;
                }
            }
            diameter = fmax(diameter, d1 + d2 + 1);
        }
    }
    return diameter;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= 2 * n + 1; i++) {
        scanf("%d", &a[i]);
    }
    int height = get_height();
    int diameter = get_diameter();
    printf("%d\n", abs(height - diameter));
    return 0;
}
