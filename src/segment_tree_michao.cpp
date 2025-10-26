const int MAX=1<<19;
const int NEUTRAL=-1;
const int inf=1e18+9;
int LAZY[MAX*4],MINI[MAX*4];
int scal(int a,int b){
  if (b==NEUTRAL)return a;
  return b;
}
void push(int u){
  if (u<MAX){
    LAZY[2*u]=scal(LAZY[2*u],LAZY[u]);
    LAZY[2*u+1]=scal(LAZY[2*u+1],LAZY[u]);
  }
  MINI[u]=scal(MINI[u],LAZY[u]);
  LAZY[u]=NEUTRAL;
}
 
void update(int a,int b,int u,int lo,int hi,int c){
  if (b<lo || a>hi)return;
  push(u);
  if (a<=lo && b>=hi){
    LAZY[u]=scal(LAZY[u],c);
    return;
  }
  push(u);
  int mid=(lo+hi)>>1;
  update(a,b,2*u,lo,mid,c);
  update(a,b,2*u+1,mid+1,hi,c);
  push(2*u);
  push(2*u+1);
  MINI[u]=min(MINI[2*u],MINI[2*u+1]);
}
 
int getmin(int a,int b,int u,int lo,int hi){
  if (b<lo || a>hi)return inf;
  push(u);
  if (a<=lo && b>=hi)
    return MINI[u];
  int mid=(lo+hi)>>1;
  int L=getmin(a,b,2*u,lo,mid);
  int R=getmin(a,b,2*u+1,mid+1,hi);
  return min(L,R);
}
int32_t main(){
  BOOST;
  fill(MINI,MINI+4*MAX,NEUTRAL);
  int n,q;
  cin>>n>>q;
  for (int z=0;z<q;z++){
    int type;
    cin>>type;
    if (type==1){
      int a,b,c;
      cin>>a>>b>>c;
      update(a,b,1,1,MAX,c);
    }
    else{
      int a,b;
      cin>>a>>b;
      cout<<getmin(a,b,1,1,MAX)<<"\n";
    }
  }  
  return 0; 
}