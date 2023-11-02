// remember to add '$' at the end of stirng
struct suffix_array{
   string s;
   int n,k;
   vi p,c,lcp;
   suffix_array(){}
   suffix_array(string _s){
      s=_s;
      n=sz(s);
      p.resize(n);
      c.resize(n);
      lcp.resize(n);
   }
   
   void count_sort(){
      vi cnt(n);
      for (auto it:c)cnt[it]++;
      vi p_new(n),pos(n);
      pos[0]=0;
      for (int i=1;i<n;i++)pos[i]=pos[i-1]+cnt[i-1];
      for (auto it:p){
         int i=c[it];
         p_new[pos[i]]=it;
         pos[i]++;
      }
      p=p_new;
   }
   
   void makeSA(){
     // phase 0
     vector<pair<char,int>>pom(n);
     for (int i=0;i<n;i++)pom[i]=mp(s[i],i);
     sort(pom.begin(),pom.end());
     for (int i=0;i<n;i++)p[i]=pom[i].nd;
     c[p[0]]=0;
     for (int i=1;i<n;i++){
       if (pom[i].st==pom[i-1].st)c[p[i]]=c[p[i-1]];
       else c[p[i]]=c[p[i-1]]+1;
     }
     // phase i->i+1
     k=0;
     while ((1<<k)<n){
       for (int i=0;i<n;i++)p[i]=(p[i]-(1<<k)+n)%n;
       count_sort();
       vi c_new(n);
       c_new[p[0]]=0;
       for (int i=1;i<n;i++){
         pii popr={c[p[i-1]],c[(p[i-1]+(1<<k))%n]};
         pii now={c[p[i]],c[(p[i]+(1<<k))%n]};
         if (now==popr)c_new[p[i]]=c_new[p[i-1]];
         else c_new[p[i]]=c_new[p[i-1]]+1;
       }
       c=c_new;
       k++;
     }
   }
   
   void printSA(){
     for (int i=0;i<n;i++){
      for (int j=p[i];j<sz(s);j++)cout<<s[j];
      cout<<"\n";
     }
   }
   
   void makeLCP(){
      k=0;
      for (int i=0;i<n-1;i++){
         int pi=c[i];
         int j=p[pi-1];
         while (s[i+k]==s[j+k])k++;
         lcp[pi]=k;
         k=max(k-1,0LL);
      }
   }
   void printLCP(){
      for (int i=1;i<=n-1;i++)cout<<lcp[i]<<" ";
      cout<<"\n";
   }  
};