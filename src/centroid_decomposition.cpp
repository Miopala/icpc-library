const int MAX=1e5+5;
const int STALA=17;
const int inf=(int)1e18+9;
int gle[MAX];
int A[MAX][STALA];
vi P[MAX];
int rwdc[MAX];
bool blocked[MAX];
int sub[MAX];
 
void suby(int u,int fa){
	sub[u]=1;
	for (auto it:P[u]){
		if (it==fa || blocked[it])continue;
		suby(it,u);
		sub[u]+=sub[it];
	}
}
 
int find_centroid(int u,int fa,int rozmiar){
	for (auto it:P[u]){
		if (blocked[it] || it==fa)continue;
		if (sub[it]>rozmiar/2){
			return find_centroid(it,u,rozmiar);
		}
	}
	return u;
}
 
void centroid_decomp(int u,int cenfa,int fa){
	suby(u,fa);
	int rozmiar=sub[u];
	int centroid=find_centroid(u,-1,rozmiar);
	blocked[centroid]=true;
	rwdc[centroid]=cenfa;
	for (auto it:P[centroid]){
		if (blocked[it])continue;
		centroid_decomp(it,centroid,it);
	}
}
 
void dfs1(int u,int fa){
	A[u][0]=fa;
	for (auto it:P[u]){
		if (it==fa)continue;
		gle[it]=gle[u]+1;
		dfs1(it,u);
	}
}
 
int lca(int a,int b){
	if (gle[a]>gle[b]){
		swap(a,b);
	}
	for (int i=STALA-1;i>=0;i--){
		if (gle[A[b][i]]>=gle[a])b=A[b][i];
	}
	if (a==b)return a;
	for (int i=STALA-1;i>=0;i--){
		if (A[a][i]!=A[b][i])a=A[a][i],b=A[b][i];
	}
	return A[a][0];
}
 
int dist(int a,int b){
	return gle[a]+gle[b]-gle[lca(a,b)]*2;
}

/*
  for (int i=1;i<=n-1;i++){
		int a,b;
		cin>>a>>b;
		P[a].pb(b);
		P[b].pb(a);
  }
  dfs1(1,1);
  for (int i=1;i<STALA;i++)for (int j=1;j<=n;j++)A[j][i]=A[A[j][i-1]][i-1];
  centroid_decomp(1,-1,-1);
*/