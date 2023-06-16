#include <bits/stdc++.h>
using namespace std;
//--------------- MACROS ---------------
#define ll long long
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define mineq(a,n) a = min((a), (n)) 
#define maxeq(a,n) a = max((a), (n))
#define forn(i,a,n) for (int i = (a); (i < (n)); ++i) 
#define forb(i,a,n,b) for (int i = (a); (i < (n)) && (b); ++i) 
#define fors(i,a,n,s) for (int i = a; i < n; i+=s) 
#define fornn(i,n,a) for (int i = n; i >= a; --i) 
#define inf INT32_MAX
//--------------------------------------
// snippets : dsu, comp, gcd, factorizar, pow_mod, phi

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> v(n);
        forn(i, 0, n) cin >> v[i];
    }
}
