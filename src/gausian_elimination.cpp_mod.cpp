int add(int a,int b){
	a+=b;
	while (a>=mod)a-=mod;
	return a;
}
 
int sub(int a,int b){
	a-=b;
	while (a<0)a+=mod;
	return a;
}
int mul(int a,int b){
	a*=b;
	while (a>=mod)a-=mod;
	return a;
}
int divide(int a,int b){
	return mul(a,b);
}
 
int gauss(vector<vi>a,vi &ans){ // inf nieskonczenie wiele 1 jedno 0 zero
	int n=sz(a);
	int m=sz(a[0])-1;
	int row=0;
	vi where(m,-1);
	for (int col=0;col<m && row<n;col++){
		int sel=row;
		for (int i=row;i<n;i++)if (a[i][col]>a[sel][col])sel=i;
		if (a[sel][col]==0)continue;
		for (int i=col;i<=m;i++)swap(a[row][i],a[sel][i]);
		where[col]=row;
		for (int i=0;i<n;i++){
			if (i==row)continue;
			int c=divide(a[i][col],a[row][col]);
			for (int j=col;j<=m;j++){
				a[i][j]=sub(a[i][j],mul(a[row][j],c));
			}	
		}	
		row++;
	}
	for (int i=0;i<m;i++){
		if (where[i]==-1){
			ans[i]=0;
			continue;
		}
		ans[i]=divide(a[where[i]][m],a[where[i]][i]);
	}
	for (int i=0;i<n;i++){
		int sum=0;
		for (int j=0;j<m;j++)sum=add(sum,mul(ans[j],a[i][j]));
		if (sum!=a[i][m])return 0;
	}
	
	for (int i=0;i<m;i++){
		if (where[i]==-1)return inf;
	}
	return 1;
}