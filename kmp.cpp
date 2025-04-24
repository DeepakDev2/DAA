#include <bits/stdc++.h> 

// Union Find Algorithm Almost O(1) for reasonable size N. O(log*N) to be precise
struct UnionFind
{
    int n;
    vector<int> rank;
    vector<int> parent;
    // store other info as required
    UnionFind(int n)
    {
        rank.resize(n);
        fill(rank.begin(), rank.end(), 0);
        parent.resize(n);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int get(int a)
    {
        return parent[a] = (parent[a] == a ? a : get(parent[a]));
    }
    void merge(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (a == b)
        {
            return;
        }
        if (rank[a] == rank[b])
        {
            rank[a]++;
        }
        if (rank[a] > rank[b])
        {
            parent[b] = a;
        }
        else
        {
            parent[a] = b;
        }
    }
};
vector<int> findPattern(string p, string s)
{
    // Write your code here.
    int m = p.length();
    vector<int> lps(m,0);
    int j=0;
    for(int i=1;i<m;i++){
        j=lps[i-1];
        while(j>0 && p[i]!=p[j]){
            j=lps[j-1];
        }
        if(p[i]==p[j]){
            lps[i]=j+1;
        }else{
            lps[i]=j;
        }
    }

    vector<int> ans;

    int idx = -1;
    int n = s.length();
    for(int i=0;i<n;){
        
        if(s[i]==p[idx+1]){
            idx++;
            i++; 
            if(idx+1==m){
                ans.push_back(i-m);

                idx = lps[idx];

            }
        }else if(idx!=-1){
            idx = lps[idx]-1;
        }
        else{
            i++;
        }
    }
    return ans;
}


int matrixMultiplication(vector<int> &arr, int N)
{
    // Write your code here.
    vector<vector<int>> dp(N+1,vector<int>(N+1,-1));

    function<int(int,int)> f = [&](int i,int j)->int{
        if(i==j){
            return dp[i][j]=0;
        }
        if(dp[i][j]!=-1){
            return dp[i][j];
        }
        int curr = 1e9;
        for(int k=i;k<j;k++){
            curr = min(curr,f(i,k)+f(k+1,j)+arr[i-1]*arr[k]*arr[j]);
        }
        return dp[i][j]=curr;
    };
    f(1,N-1);
    
    return dp[1][N-1];
}

vector<int> boyer(string p,string s){
    vector<int> occ(26,p.length());
    int m = p.length();
    for(int i=0;i<m-1;i++){
        occ[p[i]-'a']=m-i-1;
    }
    int j = m-1;
    int n = s.length();
    vector<int> ans;
    int i;
    for(i=m-1;i<n;){

        int t1 = i;
        int t2 = j;
        while(t2>=0 && s[t1]==p[t2]){
            t1--,t2--;
        }
        if(t2<0){
            ans.push_back(t1+1);
            i++;
        }else{
            i+=occ[s[i]-'a'];
        }
    }

    return ans;
}

vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0; 
    for (int i = 0; i < S; i++) 
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurrences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i+S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurrences.push_back(i);
    }
    return occurrences;
}

// g++ main.cpp add.cpp -o program
// g++ -pg -o test test.cpp
// ./test
// gprof test gmon.out > analysis.txt


vector<int> quickSort(vector<int> arr)
{
    // Write your code here.
    function<void(int,int)> f = [&](int s,int e){
        if(s>=e){
            return;
        }
        int pivot = arr[s];
        int pidx = s;
        int re = e;
        s++;
        while(s<=e){
            while(s<=e && arr[s]<pivot){
                s++;
            }
            while(s<=e && arr[e]>pivot){
                e--;
            }
            if(s>e){
                break;
            }
            swap(arr[s],arr[e]);
            s++;
            e--;
        }
        swap(arr[pidx],arr[e]);
        f(pidx,e-1);
        f(e+1,re);
    };
    f(0,arr.size()-1);
    return arr;
}
