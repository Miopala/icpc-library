// solving knapsack in s*sqrt(s)/32
dp[0]=true;
for (int i=1;i<=n;i++){
     if (ile[i]){
       int num=ile[i];
       vi noms;
       for (int j=0;j<20;j++){
        if (num>=(1LL<<j))noms.pb(1LL<<j),num-=(1LL<<j);
       }
       if (num>0LL)noms.pb(num);
       for (auto it:noms)dp=((dp<<(it*i))|dp);
     }
}