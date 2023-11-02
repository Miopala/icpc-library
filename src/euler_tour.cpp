// bidirectional edges
vi edges;
vector<pii> P[MAX]; // second is number;
bool OE[MAX];
vi euler;
void euler_tour (int u){
	 while (sz(P[u])){
	  pii it=P[u].back();
	  P[u].pop_back();
	  if (!OE[it.nd]){
	    OE[it.nd]=true;
			euler_tour(it.st);
		}
	}
	euler.pb(u);
}