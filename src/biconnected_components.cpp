
vector<vector<pii>>bi_coms; // krawedziowe
vector<pii>stos;
int n,m,pre=0,low[MAX],czas[MAX],fa[MAX];
bool O[MAX],O2[MAX];

void dfs(int u){
	O[u]=true;
	czas[u]=pre++;
	low[u]=czas[u];
	int sons=0;
	for (auto it:P[u]){
		if (!O[it]){
			fa[it]=u;
			sons++;
			stos.pb(mp(u,it));
			dfs(it);
			low[u]=min(low[u],low[it]);
			if (!fa[u] && sons>1){
				vector<pii>akt;
				while (true){
					pii x=stos.back();
					akt.pb(stos.back());
					stos.pop_back();
					if (x==mp(u,it))break;
				}
				bi_coms.pb(akt);
			}	
			else if (fa[u] && low[it]>=czas[u]){
				vector<pii>akt;
				while (true){
					pii x=stos.back();
					akt.pb(stos.back());
					stos.pop_back();
					if (x==mp(u,it))break;
				}
				bi_coms.pb(akt);
			}
		}
		else if (it!=fa[u] && czas[it]<low[u]){
			low[u]=min(low[u],czas[it]);
			stos.pb(mp(u,it));
		}
	}
}

void bi_comp()
{
    for (int i=1; i<=n; i++)
    {
        if (!O[i])
        {
            dfs(i);
            bi_coms.pb(stos);
            stos.clear();
        }
    }
    for (auto it:bi_coms)
      func(it);
}