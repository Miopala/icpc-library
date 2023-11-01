struct _2SAT{
   int n;
   vector<pii>clause;
   vector<vi>P,R;
   vector<bool> ans;
   vi topo;
   vi comp;
   vector<bool>O;
   // zmienne numerujemy od 1
   _2SAT(const int & _n,const vector<pii> & _clause){
      n=_n,clause=_clause;
   }
   // x-ta zmienna i jej negat zajmuja pozycje 2x-2,2x-1
   int negat(int variable){
      if (variable%2==0)return variable+1;
      return variable-1;
   }
   
   int conv(int variable){
      bool minus=false;
      if (variable<0)minus=true;
      variable=abs(variable);
      if (minus)return variable*2-1;
      return variable*2-2;
   }
   void generate_graph(){
     P.resize(2*n+1);
     R.resize(2*n+1);
     for (int i=0;i<=2*n;i++)P[i].clear(),R[i].clear();
     for (auto it:clause){
       int a=it.st,b=it.nd;
       a=conv(a),b=conv(b);
       P[negat(a)].pb(b);
       P[negat(b)].pb(a);
       R[b].pb(negat(a));
       R[a].pb(negat(b));
     }
   }
   
   void dfs1(int u){
      O[u]=true;
      for (auto it:P[u]){
         if (!O[it])dfs1(it);
      }
      topo.pb(u);
   }
   
   void dfs2(int u,int c){
     comp[u]=c;
     for (auto it:R[u]){
       if (comp[it]==-1){
         dfs2(it,c);
       }
     }
   }
      
   bool solve_2SAT(){
      int cnt=0;
      O.resize(2*n+1);
      ans.resize(2*n+1);
      comp.resize(2*n+1);
      fill(O.begin(),O.end(),false);
      fill(comp.begin(),comp.end(),-1);
      fill(ans.begin(),ans.end(),false);
      for (int i=0;i<2*n;i++){
         if (!O[i])dfs1(i);
      } 
      
      while (!topo.empty()){
         int u=topo.back();
         topo.pop_back();
         if (comp[u]==-1){
           dfs2(u,cnt++);  
         }
      }
      for (int i=0;i<2*n;i+=2){
         if (comp[i]==comp[i+1])return false;
         ans[i/2]=comp[i]>comp[i+1];
      }
      return true;
   }
   
};