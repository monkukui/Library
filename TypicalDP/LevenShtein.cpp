#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
#include <bitset>

using namespace std;

int LevenShtein(const string &s, const string &t){
    int n = (int)s.size();
    int m = (int)t.size();
    
    vector<vector<int> > dp(n + 1, vector<int> (m + 1, 0));
    for(int i = 0; i < n + 1; i++) dp[i][0] = i;
    for(int j = 0; j < m + 1; j++) dp[0][j] = j;

    for(int i = 1; i < n + 1; i++){
        for(int j = 1; j < m + 1; j++){
            int cost = 1;
            if(s[i - 1] == t[j - 1]) cost = 0;
            dp[i][j] = min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, dp[i - 1][j - 1] + cost});
        }
    }

    return dp[n][m];
}
