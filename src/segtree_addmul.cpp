const int MAX=5e5+5;
const int mod=998244353;
const int MAXT=1<<30;
const int STALA=1e9;
struct Node{
	Node *l,*r;
	int sum,lazy,mul=1;
	Node(){
		l=nullptr;
		r=nullptr;
		lazy=0;
		sum=0;
		mul=1;
	}
};
Node *root=new Node();
void check(Node *&u){
	if (u==nullptr)u=new Node();
}
 
void dod(int &a,int b){
	a+=b;
	while (a<0)a+=mod;
	while (a>=mod)a-=mod;
}
 
void mult(int &a,int b){
  dod(a,0);
  dod(b,0);
	a*=b;
	a%=mod;
}
 
int mult2(int a,int b){
	dod(a,0);
	dod(b,0);
	a*=b;
	a%=mod;
	return a;
}
 
// mul znaczy ax , lazy znaczy b
 
void push(Node *u,int lo,int hi){
  check(u->l);
  check(u->r);
  mult(u->l->lazy,u->mul);
  mult(u->r->lazy,u->mul);
	dod(u->l->lazy,u->lazy);
	dod(u->r->lazy,u->lazy);
	mult(u->l->mul,u->mul);
	mult(u->r->mul,u->mul);
	mult(u->sum,u->mul);
	dod(u->sum,mult2((hi-lo+1),u->lazy));
	u->mul=1;
	u->lazy=0;
}
 
void add(int a,int b,Node *u,int lo,int hi,int c){
	if (a>hi || b<lo)return;																																																										
	push(u,lo,hi);
	if (lo>=a && hi<=b){
		u->lazy+=c;
		u->lazy%=mod;
		return;
	}
	int mid=(lo+hi)>>1;
	check(u->l);
	check(u->r);
	add(a,b,u->l,lo,mid,c);
	add(a,b,u->r,mid+1,hi,c);
	push(u->l,lo,mid);
	push(u->r,mid+1,hi);
	u->sum=(u->l->sum+u->r->sum)%mod;
}
 
void multiply(int a,int b,Node *u,int lo,int hi,int c){
	if (a>hi || b<lo)return;
	push(u,lo,hi);
	if (lo>=a && hi<=b){
		u->mul*=c;
		u->mul%=mod;
		return;
	}
	int mid=(lo+hi)>>1;
	check(u->l);
	check(u->r);
	multiply(a,b,u->l,lo,mid,c);
	multiply(a,b,u->r,mid+1,hi,c);
	push(u->l,lo,mid);
	push(u->r,mid+1,hi);
	u->sum=(u->l->sum+u->r->sum)%mod;
}
 
int query(int a,int b,Node *u,int lo,int hi){
	check(u);
	if (a>hi || b<lo)return 0;
	push(u,lo,hi);
	if (lo>=a && hi<=b)return u->sum;
	int mid=(lo+hi)>>1;
  int L=query(a,b,u->l,lo,mid);
  int R=query(a,b,u->r,mid+1,hi);
  return (L+R)%mod;
}
 
int a[MAX];
 
 
void ustaw(int l,int r,int c){
	multiply(l,r,root,1,MAXT,0);
	add(l,r,root,1,MAXT,1);
}
 
void pomnoz(int l,int r,int c){
	multiply(l,r,root,1,MAXT,c);
}
 
void dodaje(int l,int r,int c){
	add(l,r,root,1,MAXT,c);
}
 
int suma(int l,int r){
	return query(l,r,root,1,MAXT);
}