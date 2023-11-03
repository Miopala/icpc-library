const int MAX=105;
const int mod=998244353;
int fact[MAX];
int fastpow(int a,int b){
	if (a<0 || b<0)return 0;
	if (b==0)return 1;
	if (a==0)return 0;
	int wyn=1;
	while (b){
		if (b&1)wyn=(wyn*a)%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return wyn;
}
 
int inv(int x){
	return fastpow(x,mod-2);
}
 
int binom(int a,int b){
	if (a<0 || b<0 || b>a)return 0;
	int x=fact[a];
	int y=(fact[b]*fact[a-b])%mod;
	return (x*inv(y))%mod;
}
vector<pii>points;
 
int sub(int a,int b){
	a-=b;
	a+=mod;
	a%=mod;
	return a;
}
int eval(int x){
	int ans=0;
	for (int i=0;i<sz(points);i++){
		int sum=points[i].nd;
		for (int j=0;j<sz(points);j++){
			if (i==j)continue;
			sum=(sum*(sub(x,points[j].st)))%mod;
			sum=(sum*inv(sub(points[i].st,points[j].st)))%mod;
		}
		ans=(ans+sum)%mod;
	}
	return ans;
}
int32_t main()
{
  BOOST;
	int n,k;
	cin>>n>>k;
	fact[0]=1;
	for (int i=1;i<=MAX-1;i++)fact[i]=(fact[i-1]*i)%mod;
	for (int x=1;x<=n+3;x++){
		int y=0;
		for (int pos=1;pos<=n;pos++){
			for (int lsl=0;lsl<=pos-1;lsl++){
				for (int grr=lsl+1;grr<=n-pos;grr++){
					int sum=binom(pos-1,lsl);
					sum=(sum*fastpow(x-1,lsl))%mod;
					sum=(sum*fastpow(k+1-x,pos-1-lsl))%mod;
					sum=(sum*binom(n-pos,grr))%mod;
					sum=(sum*fastpow(k-x,grr))%mod;
					sum=(sum*fastpow(x,n-pos-grr))%mod;
					y=(y+sum)%mod;
				}
			}
		}
		y=(y*x)%mod;
		points.pb(mp(x,y));
	}
  // to z suma tylko do problemu
	int sum=0;
	for (auto &it:points){
		sum=(sum+it.nd)%mod;
		it.nd=sum;
		//cout<<"TERAZ "<<it.st<<" "<<it.nd<<"\n";
	}
	cout<<eval(k);
  return 0;
}