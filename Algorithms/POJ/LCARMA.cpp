// RMA
// 1. Segment Tree
// 2. Sparse Table

// LCA->RMA
// 1. Euler Tour on Given Tree -> Get an Array E of Size 2n-1
// 2. Every index's level Corresponding to E's value of same index -> L (2n-1)
// 3. Every index's first appearance in E -> R(n)
// 4. Given Two Nodes, Find the first occurrence of two nodes -> We can use that in L
// 5. Find the minimum value in L between two nodes' first appearance in E( Using RMA )

// Now Lets discuss RMA
# define MAXN 1000
# define LOGMAXN 10
void SparseTable(int M[MAXN][LOGMAXN], int A[MAXN], int N) {
    int i, j;

    //initialize M for the intervals with length 1
    for (i = 0; i < N; i++)
      M[i][0] = i;
    //compute values from smaller to bigger intervals
    for (j = 1; 1 << j <= N; j++)
      for (i = 0; i + (1 << j) - 1 < N; i++)
        if (A[M[i][j - 1]] < A[M[i + (1 << (j - 1))][j - 1]])
          M[i][j] = M[i][j - 1];
        else
          M[i][j] = M[i + (1 << (j - 1))][j - 1];
  }// DP方程： M[i][j] = M[i][j-1] if A[M[i][j-1]] < A[M[i+2^(j-1)][j-1]] ELSE M[i][j] = M[i+2^(j-1)][j-1]
  // So RMQ(i,j) = min(M[i][k],M[j-2^k+1][k]) 
//   O(nlogn)预处理，O(1)查询

// 线段树最大数组为4n
// 通过Array建树 每个元素是当前结点表达的区间的最小值
void build(int node, int b, int e, int M[4*(MAXN)] , int A[MAXN],int N){
    if (b == e){
        M[node] = b;
        return;
    }
    build(2*node, b , (b+e)>>1 , M, A,N);
    build(2*node+1, ((b+e)>>1)+1 , e , M, A,N);
    if (A[M[2*node]] <= A[M[2*node+1]])
        M[node] = M[2*node];
    else
        M[node] = M[2*node+1];
}

// Query
int Query(int node,int b,int e, int M[4*(MAXN)],int A[MAXN],int i,int j){
    if(i > e || j < b) return -1;
    if(b>=i && e <= j) return M[node];
    int p1 = Query(2*node, b, (b+e)>>1,M,A,i,j);
    int p2 = Query(2*node+1,((b+e)>>1) + 1,e,M,A,i,j);

    if(p1 == -1) return p2;
    if(p2 == -1) return p1;
    if(A[p1] <= A[p2]) return M[node] = p1;
    return M[node] = p2;
}