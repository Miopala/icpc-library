#include <bits/stdc++.h>
//#define int long long
#define mp make_pair
#define pb push_back
#define ld long double
#define pii pair<int,int>
#define sz(x) (int)x.size()
#define piii pair<pii,pii>
#define precise cout<<fixed<<setprecision(10)
#define st first
#define nd second
#define ins insert
#define vi vector<int>
#define BOOST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
const int MAX=3e5+5;
const int SQRT=900;
const int SQRT2=549;
const int STALA=19;
static int a[MAX],st[MAX],en[MAX],gle[MAX];
static int A[MAX][STALA];
vi P[MAX];
int ans[MAX];
struct query{
    int segl,segr,l,r,lca;
    bool czylca;
    int id;
};
vector<query>Q;
vi trav;
void dfs(int u,int fa){
    trav.pb(u);
    A[u][0]=fa;
    for (auto it:P[u]){
      if (it==fa)continue;
      gle[it]=gle[u]+1;
      dfs(it,u);
    }
    trav.pb(u);
}
  
inline int LCA(int ass,int bss){
  if (gle[ass]>gle[bss])swap(ass,bss);
  for (int i=STALA-1;i>=0;i--){
    if (gle[A[bss][i]]>=gle[ass])bss=A[bss][i];
  } 
  if (ass==bss)return ass;
  for (int i=STALA-1;i>=0;i--){
    if (A[ass][i]!=A[bss][i])ass=A[ass][i],bss=A[bss][i];
  }
  return A[ass][0];
}
int L=1,R=0;
  
bool cmp(query q1,query q2){
    if (q1.segl/SQRT!=q2.segl/SQRT)return q1.segl/SQRT<q2.segl/SQRT;
    if ((q1.segl/SQRT)&1)
    return q1.segr<q2.segr;
    return q1.segr>q2.segr;
}
  
//int ile[MAX]; // ile dla danego i parzyscie lipstick nieparzyscie git
static int cnt[MAX]; // ile dla danego koloru
int sumkub[10005]; // suma dla kubelka
int sum[MAX]; // suma pojedynczego elementu
bitset<MAX>ile;
inline void dodajdokubla(int x){
  sumkub[x/SQRT2]++;
  sum[x]++;
  //assert(sum[x]==1);
}
  
inline void odejmijzkubla(int x){
  sumkub[x/SQRT2]--;
  sum[x]--;
  //assert(sum[x]==0);
}
inline void add(int pos){
  pos=trav[pos];
  ile[pos]=!ile[pos];
  if (cnt[a[pos]]&1)
  odejmijzkubla(a[pos]);
  if (ile[pos]){
    cnt[a[pos]]++;
  }
  else{
    cnt[a[pos]]--;
  }
  if (cnt[a[pos]]&1)
  dodajdokubla(a[pos]);
}
  
inline void del(int pos){
  pos=trav[pos];
  ile[pos]=!ile[pos];
  if (cnt[a[pos]]&1)
  odejmijzkubla(a[pos]);
  if (ile[pos]){
    cnt[a[pos]]++;
  }
  else{
    cnt[a[pos]]--;
  }
  if (cnt[a[pos]]&1)
  dodajdokubla(a[pos]);
}
int to=-1;
inline int ask(query& x){
  int l=x.l;
  int r=x.r;
  while (l%SQRT2!=0 && l<=r){
    if (sum[l]){
      return l;
    }
    l++;
  }
  
  while (l+SQRT2<r){
      if (sumkub[l/SQRT2]){
        while (true){
          if (sum[l])return l;
          l++;
        } 
        assert(false);
      }
      l+=SQRT2;
  }
  assert(r-l<SQRT2+5);
  if (sumkub[l/SQRT2]==0)return -1;
  while (l<=r){
    if (sum[l]){
      return l;
    }
    l++;
  }
  return -1;
}
  
int readInt () {
  bool minus = false;
  int result = 0;
  char ch;
  ch = getchar();
  while (true) {
    if (ch == '-') break;
    if (ch >= '0' && ch <= '9') break;
    ch = getchar();
  }
  if (ch == '-') minus = true; else result = ch-'0';
  while (true) {
    ch = getchar();
    if (ch < '0' || ch > '9') break;
    result = result*10 + (ch - '0');
  }
  if (minus)
    return -result;
  else
    return result;
}
  
int32_t main(){
  //BOOST;
  trav.pb(-1);
  int n=readInt(),q=readInt();
  // scanf("%d%d",&n,&q);
  to=n/SQRT2;
  for (int i=1;i<=n;i++)a[i]=readInt();
  for (int i=1;i<=n-1;i++){
    int l=readInt(),r=readInt();
    P[l].pb(r);
    P[r].pb(l);
  }
  dfs(1,1);
  int roz=sz(trav)-1;
  for (int i=1;i<=roz;i++)en[trav[i]]=i;
  for (int i=roz;i>=1;i--)st[trav[i]]=i;
  /*
  cerr<<"TRAVERSAL\n";
  for (int i=1;i<=roz;i++)cerr<<trav[i]<<" ";
  cerr<<"\n";
  cerr<<"END OF TRAVERSAL\n";
  cerr<<"ST EN=\n";
  for (int i=1;i<=n;i++){
    cerr<<i<<" "<<st[i]<<" "<<en[i]<<"\n";
  }
  cerr<<"END OF BLOCK\n";
  */
  for (int i=1;i<STALA;i++)   
    for (int j=1;j<=n;j++)
      A[j][i]=A[A[j][i-1]][i-1];
  /*
  cerr<<"CHECKLCA\n";
  cerr<<LCA(2,3)<<" "<<LCA(4,5)<<" "<<LCA(1,5)<<" "<<LCA(5,1)<<"\n";
  */
  for (int i=1;i<=q;i++){
    int u=readInt(),v=readInt(),l=readInt(),r=readInt();
    // scanf("%d%d%d%d",&u,&v,&l,&r);
    //cin>>u>>v>>l>>r;
    if (st[u]>st[v])swap(u,v);
    int segl=-1,segr=-1;
    if (LCA(u,v)==u){
      segl=st[u];
      segr=st[v];
      int lca=LCA(u,v);
      Q.pb({segl,segr,l,r,lca,false,i});
    }
    else{
      int lca=LCA(u,v);
      segl=en[u];
      segr=st[v];
      Q.pb({segl,segr,l,r,lca,true,i});
    } 
  }
  sort(Q.begin(),Q.end(),cmp);
  for (auto it:Q){
    while (L>it.segl)L--,add(L);
    while (R<it.segr)R++,add(R);
    while (L<it.segl)del(L),L++;
    while (R>it.segr)del(R),R--;
    if (it.czylca){
      add(st[it.lca]);
    } 
    ans[it.id]=ask(it);
    if (it.czylca){
      del(st[it.lca]);
    }
  }
  
  for (int i=1;i<=q;i++){
    printf("%d\n",ans[i]);
  }
  return 0; 
}