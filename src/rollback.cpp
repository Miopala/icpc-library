void update(int a,int b,int u,int lo,int hi,int c){
  if (a>hi || lo>b)return;
  if (a<=lo && hi<=b){
    t[u].pb(c);
    return;
  }
  int mid=(lo+hi)>>1;
  update(a,b,u*2,lo,mid,c);
  update(a,b,u*2+1,mid+1,hi,c);
}
 
struct rollback{
  int *id;
  int val;
  rollback(){}
  rollback(int *_id,int _val){
    id=_id;
    val=_val;
  }
  
  void przywroc(){
    *id=val;
  }
};
 
struct roll_back_stack{
  vector<rollback>stos;  
  roll_back_stack(){}
  void wrzut(int *adres,int val){
    stos.pb(rollback(adres,*adres));
    *adres=val;
  }
  void zwroc(int threshold){
    while (sz(stos)>threshold){
      stos.back().przywroc();
      stos.pop_back();
    }
  }
};
 
roll_back_stack r;
 
int Find(int u){
  if (p[u]==u)return u;
  return Find(p[u]);
}
 
void Union(int u,int v){
  u=Find(u);
  v=Find(v);
  if (u==v)return;
  if (roz[u]<roz[v])swap(u,v);
  cnt++;
  int id1=lca[u],id2=lca[v];
  if (czy[id1] || czy[id2])czy[cnt]=true;
  r.wrzut(&roz[u],roz[u]+roz[v]);
  r.wrzut(&p[v],u);
  r.wrzut(&lca[u],cnt);
  r.wrzut(&lca[v],cnt);
  adj[cnt][0]=id1,adj[cnt][1]=id2;
}
 
void f(int u){
  r.wrzut(&active[u],1);
  for (auto it:P[u]){
    if (active[it])Union(u,it);
  }
}
void dfs(int u){
  int before=sz(r.stos);
  for (auto id:t[u]){
    f(id);
  }
  if (u<MAXN){
    dfs(2*u);
    dfs(2*u+1);
  }
  r.zwroc(before);
}