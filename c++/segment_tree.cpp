#include <bits/stdc++.h>
using namespace std;

#define ll long long int 
int tree[2000005],a[100005];

void build(int node, int start, int end){
    if(start == end){
        // Leaf node will have a single element
        tree[node] = a[start];
    }
    else{
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        tree[node] = tree[2*node] + tree[2*node+1];
    }
}

void update(int node,int start,int end,int idx,int val){
    
	if(start==end){
		a[idx]=val;
		tree[node]=val;
	}
	else{
    	int mid=(start+end)/2;
    	
    	if(idx>=start&&idx<=mid)
    		update(2*node,start,mid,idx,val);
    	else
    		update(2*node+1,mid+1,end,idx,val);
    
    	if(tree[2*node]<tree[2*node+1])
    		tree[node]=tree[2*node];
    	else
    		tree[node]=tree[2*node+1];
	}
}
int query(int node, int start, int end, int l, int r)
{
    if(r < start or end < l){
        return 0;
    }
    if(l <= start and end <= r){
        cout<<start<<" "<<end<<" "<<tree[node]<<endl;
        return tree[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}
int main(){

	int n,q;
	cin>>n>>q;
	
	for(int i=1;i<=n;i++)
		cin>>a[i];
		
	build(1,1,n);

	while(q--){
    	char b;
    	int x,y;
    	cin>>b>>x>>y;
    	if(b=='q'){
    		int c=query(1,1,n,x,y);
    		cout<<c<<endl;
    	}
    	else
    		update(1,1,n,x,y);
	}
	return 0;
}