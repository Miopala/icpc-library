#include <bits/stdc++.h>
#define int long long
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
const int MAX=1e5+5;
const int PIER1=(int)sqrt(100000)*2LL+5;
const int PIER2=(int)pow(100000,(ld)2/3)*2LL;
int ans[MAX];
int a[MAX],b[MAX];
struct query{
  int l,r,czas,id;
};
 
 
struct update{
   int pos,c,popr;
};
int cnt=-1;
vector<update>updates;
vector<query>queries;
set<int>pom;
map<int,int>mapa;
int licz=1;
 
bool cmp(query q1, query q2){
   if (q1.l/PIER2!=q2.l/PIER2)return q1.l/PIER2<q2.l/PIER2;
   if (q1.r/PIER2!=q2.r/PIER2)return q1.r/PIER2<q2.r/PIER2;
   return q1.czas<q2.czas;
}
int zlicz[MAX*3];
int domexa[MAX*3];
 
int L=1,R=0,czas=-1;
 
void add(int pos){
  domexa[zlicz[b[pos]]]--;
  zlicz[b[pos]]++;
  domexa[zlicz[b[pos]]]++;
}
 
void del(int pos){
  domexa[zlicz[b[pos]]]--;
  zlicz[b[pos]]--;
  domexa[zlicz[b[pos]]]++; 
}
 
int mex(){
  for (int i=1;i<=100000000000000;i++)if(!domexa[i])return i;
  assert(false);
  return -1; 
}
 
void cofaj(int pos){
  int pozycja=updates[pos].pos;
  int liczba=updates[pos].popr;
  if (L<=pozycja && R>=pozycja){
    del(pozycja);
    b[pozycja]=liczba;
    add(pozycja);
  }
  else
   b[pozycja]=liczba;
}
 
void ruszaj(int pos){
  int pozycja=updates[pos].pos;
  int liczba=updates[pos].c;
  if (L<=pozycja && R>=pozycja){
    del(pozycja);
    b[pozycja]=liczba;
    add(pozycja);
  }
  else
   b[pozycja]=liczba;
}
int32_t main(){
  BOOST;
  int n,q;
  cin>>n>>q;
  for (int i=1;i<=n;i++)cin>>a[i];
  for (int i=1;i<=q;i++){
    int type;
    cin>>type;
    if (type==1){
      int l,r;
      cin>>l>>r;
      queries.pb({l,r,cnt,i});
    }
    else{
      int p,x;
      cin>>p>>x;
      updates.pb({p,x,-1});
      pom.ins(x);
      cnt++;
    }
  }
  for (int i=1;i<=n;i++)pom.ins(a[i]);
  for (auto it:pom)mapa[it]=licz++;
  for (int i=1;i<=n;i++)a[i]=mapa[a[i]];
  for (auto &it:updates)it.c=mapa[it.c];
  //////////////////////////////////////////////
  for (int i=1;i<=n;i++)b[i]=a[i];
  for (auto &it:updates){
    it.popr=b[it.pos];
    b[it.pos]=it.c;
  }
  for (int i=1;i<=n;i++)b[i]=a[i];
  sort(queries.begin(),queries.end(),cmp);
  for (int i=1;i<=q;i++)ans[i]=-1;
  for (auto it:queries){
    while (L>it.l)L--,add(L);
    while (R<it.r)R++,add(R);
    while (L<it.l)del(L),L++;
    while (R>it.r)del(R),R--;
    while (czas<it.czas)czas++,ruszaj(czas);
    while (czas>it.czas)cofaj(czas),czas--;
    ans[it.id]=mex();
  }
  for (int i=1;i<=q;i++){
    if (ans[i]!=-1)cout<<ans[i]<<"\n";
  }
  return 0; 
}