#include <stdio.h>

int main() {
    int n, k, i, j;
    scanf("%d %d", &n, &k);
    int a[n], max, score_rohu = 0, score_ishu = 0;

    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    max = a[0];
    for (i = 1; i < k; i++) {
        if (a[i] > max) {
            max = a[i];
        }
    }
    score_ishu += max;

    for (i = 1; i <= n - k; i++) {
        if (a[i - 1] == max) {
            max = a[i];
            for (j = i + 1; j < i + k; j++) {
                if (a[j] > max) {
                    max = a[j];
                }
            }
        } else {
            if (a[i + k - 1] > max) {
                max = a[i + k - 1];
            }
        }
        if (i % 2 == 1) {
            score_rohu += max;
        } else {
            score_ishu += max;
        }
    }

    if (score_rohu > score_ishu) {
        printf("rohu\n");
    } else if (score_ishu > score_rohu) {
        printf("ishu\n");
    } else {
        printf("draw\n");
    }

    return 0;
}
