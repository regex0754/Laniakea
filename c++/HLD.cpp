#include <bits/stdc++.h>

using namespace std;
#define ll long long 

int c = 0;
int e[100001];
vector<int> adj[100001];

pair<int, int> lcaseg[1000001];
int position[100001];
pair<int,int> traverse[1000001];

ll hdlseg[1000001];
ll chainheads[100001];
ll chains[100001];
ll num[100001];
int currchain = 0;
int currcount = 0;
ll children[100001];
ll p[100001];
ll he[100001];

void updatelca(int node, int start, int end, int ind, int n, int h) {
    if (ind > end || ind < start) {
        return;
    }
    if (h < lcaseg[node].second) {
        lcaseg[node] = {n, h};
    }
    if (start == end) {
        return;
    }
    updatelca(2*node + 1, start, (start + end)/2, ind, n, h);
    updatelca(2*node + 2, (start + end)/2 + 1, end, ind, n, h);
}

void updatelca(int ind, int n, int h) {
    updatelca(0, 0, c, ind, n, h);
}

pair<int,int> getlca(int node, int start, int end, int a, int b) {
    if (a > end || b < start) {
        return pair<int,int>({-1, 10000000});
    }
    if (a <= start && b >= end) {
        return lcaseg[node];
    }
    pair<int, int> x = getlca(2*node + 1, start, (start + end)/2, a, b);
    pair<int, int> y = getlca(2*node + 2, (start + end)/2 + 1, end, a, b);
    if (x.second < y.second) {
        return x;
    }
    else {
        return y;
    }
}

int getlca(int a, int b) {
    if (position[b] < position[a]) {
        int temp = a;
        a = b;
        b = temp;
    }
    return getlca(0, 0, c, position[a], position[b]).first;
}

int genlca(int curr, int h, int parent) {
    he[curr] = h;
    traverse[c] = {curr, h};
    position[curr] = c++;
    p[curr] = parent;
    for (int i : adj[curr]) {
        if (i != parent) {
            children[curr] += genlca(i, h+1, curr);
            traverse[c] = {curr, h};
            position[curr] = c++;
        }
    }
    return children[curr] + 1;
}

void hdl(int curr, int parent) {
    int maxchild = -1;
    int ind = -1;
    chains[curr] = currchain;
    num[curr] = currcount++;
    for (int i : adj[curr]) {
        if (i != parent && children[i] > maxchild) {
            maxchild = children[i];
            ind = i;
        }
    }
    if (ind != -1) {
        hdl(ind, curr);
    }
    for (int i : adj[curr]) {
        if (i != parent && i != ind) {
            currchain++;
            chainheads[currchain] = i;
            hdl(i, curr);
        }
    }
}

void updatehdl(int node, int start, int end, int ind, int c) {
    if (ind > end || ind < start) {
        return;
    }
    if (start == end) {
        hdlseg[node] = c;
        return;
    }
    updatehdl(2*node + 1, start, (start + end)/2, ind, c);
    updatehdl(2*node + 2, (start + end)/2 + 1, end, ind, c);
    hdlseg[node] = hdlseg[2*node + 1] ^ hdlseg[2*node + 2];
}

void updatehdl(int ind, int c) {
    updatehdl(0,0, n, ind, c);
}

int gethdl(int node, int start, int end, int s, int en) {
    if (s > en) {
        int temp = en;
        en = s;
        s = temp;
    }
    if (s > end || en < start) {
        return -1;
    }
    if (s <= start && en >= end) {
        return hdlseg[node];
    }
    int a = gethdl(2*node + 1, start, (start + end)/2, s, en);
    int b = gethdl(2*node + 2, (start + end)/2 + 1, end, s, en);
    if (a == -1) {
        return b;
    }
    else if (b == -1) {
        return a;
    }
    return a ^ b;
}

int gethdl(int s, int en) {
    return gethdl(0, 0, n, s, en);
}

int getPath(int a, int b) {
    int lca = getlca(a, b);
    int curr = chains[a];
    int currnode = a;
    int alength = 0;
    while (curr != chains[lca]) {
        alength ^= gethdl(num[chainheads[curr]], num[currnode]);
        currnode = p[chainheads[curr]];
        curr = chains[currnode];
    }
    alength ^= gethdl(num[lca], num[currnode]);
    curr = chains[b];
    currnode = b;
    int blength = 0;
    while (curr != chains[lca]) {
        blength ^= gethdl(num[chainheads[curr]], num[currnode]);
        currnode = p[chainheads[curr]];
        curr = chains[currnode];
    }
    blength ^= gethdl(num[lca], num[currnode]);
    return alength ^ blength ^ gethdl(num[lca], num[lca]);
}

int main() {
    int n,q;
    cin>>n>>q;
    for (int i = 0; i < n; i++) {
        cin >> e[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int x,y;
        cin >> x >> y;
        adj[x-1].push_back(y-1);
        adj[y-1].push_back(x-1);
    }
    genlca(0, 0, -1);
    for (int i = 0; i < 1000001; i++) {
        lcaseg[i] = {-1, 10000000};
    }
    for (int i = 0; i < c; i++) {
        updatelca(i, traverse[i].first, traverse[i].second);
    }
    chainheads[0] = 0;
    hdl(0, -1);
    for (int i = 0 ; i < n; i++) {
        updatehdl(num[i], e[i]);
    }
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        if (a == 1) {
            updatehdl(num[b-1], c);
        }
        else {
            cout << getPath(b-1, c-1) << endl;
        }
    }
}
