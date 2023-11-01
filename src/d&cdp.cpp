const int inf=(int)1e18+9;
vi dp_cur,dp_prev;
int sum(int l1,int r1,int l2,int r2){
	return pref[l2][r2]-pref[l1-1][r2]-pref[l2][r1-1]+pref[l1-1][r1-1];
}
 
int cost(int l,int r){
	return sum(l,l,r,r);
}
 
void rec(int l,int r,int optl,int optr){
	if (l>r)return;
	pair<int,int> mini={inf,inf};
	int mid=(l+r)>>1;
	for (int i=optl;i<=min(mid,optr);i++){
		mini=min(mini,{dp_prev[i-1]+cost(i,mid),i});
	}
	int opt=mini.nd;
	assert(opt>=optl && opt<=optr);
	dp_cur[mid]=mini.st;
	rec(l,mid-1,optl,opt);
	rec(mid+1,r,opt,optr);
}