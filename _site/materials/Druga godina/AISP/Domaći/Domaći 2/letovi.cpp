#include <iostream>
#include <vector>

using namespace std;

void mergee(vector<pair<int, int>>& a ,int l1, int r1, int l2 , int r2, vector<int>& cnt) {
    vector<pair<int,int>> help(r2 - l1 + 1);
    int index = 0, lind = l1, rind = l2, curcnt = 0;
    while(lind <= r1 && rind <= r2)
        if(a[lind].first <= a[rind].first) {
            curcnt++;
            help[index++] = a[rind++];
        }
        else {
            cnt[a[lind].second] += curcnt;
            help[index++] = a[lind++];
        }
    while (lind <= r1) {
        cnt[a[lind].second] += curcnt;
        help[index++] = a[lind++];
    }
    while(rind <= r2)
        help[index++] = a[rind++];
    for(int i = l1; i <= r2; i++)
        a[i] = help[i - l1];
}

void merge_sort(vector<pair<int, int>>& a, int l, int r, vector<int>& cnt) {
    if(l >= r)
        return;
    int mid = (l + r) / 2;
    merge_sort(a, l, mid, cnt);
    merge_sort(a, mid + 1, r, cnt);
    mergee(a, l, mid, mid + 1, r, cnt);
}

int main() {
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for( int i = 0; i < n; i++ ) {
        cin >> a[i].first;
        a[i].first -= i;
        a[i].second = i;
    }
    vector<int> cnt(n);
    merge_sort(a, 0, n - 1, cnt);
    int sol = 0;
    for( int i = 0; i < n; i++ )
        sol += cnt[i];
    cout << sol;
}