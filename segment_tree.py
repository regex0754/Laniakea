import sys
import math
from collections import defaultdict,Counter

input=sys.stdin.readline

def print_(x):
    sys.stdout.write(str(x)+" ")
def rInt():
    return int(input())
def rList():
    arr = input().split()
    return arr
def cInt(arr):
    res = []
    for itr in arr:
        res.append(int(itr))
    return res
def pList(arr):
    for _ in arr:
        print_(_)
def iniList(size,ini_val):
    arr = [ ini_val for _ in range(size)]
    return arr

# point add update
# range add update
# point sum query
# range sum query
# All are O(logn)

class Segment_Tree:
    tree=[]# 0 indexed
    lazy=[]
    vals=[]
    n = 0
    def __init__(self,arr=[]):
        self.n = len(arr)
        self.vals = arr
        self.tree = iniList(4*self.n,0)
        self.lazy = iniList(4*self.n,0)
        
    def inputVals(self,arr):
        self.vals=arr
        self.n = len(arr)
        self.tree = iniList(4*self.n,0)
        self.lazy = iniList(4*self.n,0)
        
    def buildSeg(self,node,lft,rht):
        if lft==rht:
            self.tree[node]=self.vals[lft]
            return
        else:
            mid = lft + (rht-lft)//2
            self.buildSeg(node*2+1,lft,mid)
            self.buildSeg(node*2+2,mid+1,rht)
            self.tree[node]=self.tree[(node*2)+1]+self.lazy[(node*2)+1]*(mid-lft+1)
            self.tree[node]+=self.tree[(node*2)+2]+self.lazy[(node*2)+2]*(rht-mid)
        
    def build(self):
        self.buildSeg(0,0,self.n-1)
    
    def upd(self,node,lft,rht,L,R,new_val):
        if rht<L or lft>R:
            return
        elif L<=lft and rht<=R:
            self.lazy[node]+=new_val
        else:
            mid = lft + (rht-lft)//2
            if lft<=R and mid>=L: 
                self.upd((node*2)+1,lft,mid,L,R,new_val)
            if mid+1<=R and rht>=L: 
                self.upd((node*2)+2,mid+1,rht,L,R,new_val)
            self.tree[node]=self.tree[(node*2)+1]+self.lazy[(node*2)+1]*(mid-lft+1)
            self.tree[node]+=self.tree[(node*2)+2]+self.lazy[(node*2)+2]*(rht-mid)
    
    def updatePoi(self,idx,new_val):
        self.upd(0,0,self.n-1,idx,idx,new_val)
    def updateRng(self,L,R,new_val):
        self.upd(0,0,self.n-1,L,R,new_val)
    
    def push(self,node):
        tochild = self.lazy[node]
        self.lazy[node]=0
        self.lazy[node*2+1]+=tochild
        self.lazy[node*2+2]+=tochild
    
    def qry(self,node,lft,rht,L,R):
        if rht<L or lft>R:
            return 0
        elif L<=lft and rht<=R:
            return (self.tree[node]+(self.lazy[node]*(rht-lft+1)))
        res = 0
        self.push(node)
        mid = lft + (rht-lft)//2
        if mid<L or lft>R:
            res+=0
        else:  
            res = self.qry(node*2+1,lft,mid,L,R)
        if rht<L or mid+1>R:
            res+=0
        else:  
            res += self.qry(node*2+2,mid+1,rht,L,R)
        self.tree[node]=self.tree[(node*2)+1]+self.lazy[(node*2)+1]*(mid-lft+1)
        self.tree[node]+=self.tree[(node*2)+2]+self.lazy[(node*2)+2]*(rht-mid)
        return res
    
    def queryPoi(self,idx):
        return self.qry(0,0,self.n-1,idx,idx)
    def queryRng(self,L,R):
        return self.qry(0,0,self.n-1,L,R)

test_cases=rInt()
for test_case in range(test_cases):
    inp = rList()
    inp = cInt(inp)
    n = inp[0]
    q = inp[1]
    
    arr = iniList(n,0)
    seg = Segment_Tree(arr)

    ans = []
    for qq in range(q):
        rus = rList()
        rus = cInt(rus)
        if rus[0]==1:
            ans.append(seg.queryRng(rus[1]-1,rus[2]-1))
        else:
            seg.updateRng(rus[1]-1,rus[2]-1,rus[3])
    for _ in ans:
        print(_)
    