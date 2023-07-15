#include <stdio.h>

int main() {
    int n, q, a[50000];
    scanf("%d%d", &n, &q);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    while (q--) {
        int l, r, k, cnt = 0, freq[101] = {0};
        scanf("%d%d%d", &l, &r, &k);
        for (int i = l; i <= r; i++) {
            int j = i;
            while (j <= r && cnt < k) {
                freq[a[j]]++;
                if (freq[a[j]] == 1) cnt++;
                j++;
            }
            if (cnt == k) {
                freq[a[j]]++;
                j++;
                int ans = 1;
                while (j <= r && freq[a[j]] > 0) {
                    freq[a[j]]++;
                    j++;
                    ans++;
                }
                printf("%d\n", ans);
            }
            while (i < j) {
                freq[a[i]]--;
                if (freq[a[i]] == 0) cnt--;
                i++;
            }
        }
    }
    return 0;
}
