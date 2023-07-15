#include <stdio.h>

#define MAX_N 3000
#define MAX_Q 50

int n, q;
int a[MAX_N];
int freq[MAX_N + 1]; // frequency array

// function to count subarrays with k distinct elements in the range [l, r]
int count_subarrays(int l, int r, int k) {
    int i, j, cnt, ans;
    cnt = ans = 0;
    for (i = l, j = l; i <= r; i++) {
        while (j <= r && cnt < k) {
            if (++freq[a[j]] == 1) {
                cnt++;
            }
            j++;
        }
        if (cnt == k) {
            ans += r - j + 2;
        }
        if (--freq[a[i]] == 0) {
            cnt--;
        }
    }
    return ans;
}

int main() {
    int i, l, r, k;

    scanf("%d %d", &n, &q);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // process queries
    while (q--) {
        scanf("%d %d %d", &l, &r, &k);
        printf("%d\n", count_subarrays(l, r, k));
    }

    return 0;
}
