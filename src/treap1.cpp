mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int losuj(int l,int r){
	return l+rng()%(r-l+1);
}	
struct treap{
	array<treap*,2> sons;
	int priority;
	int subtree;
	char c;
	int H,RH;
	treap(char _c){
		sons[0]=sons[1]=nullptr;
		subtree=1;
		priority=losuj(1,STALA);
		c=_c;
		H=((c-'a'+1))%mod;
		RH=H;
	}
	treap(){
		sons[0]=sons[1]=nullptr;
		subtree=1;
		priority=losuj(1,STALA);
		H=0;
		RH=0;
	}
};
 
int size(treap *t){
	if (!t)return 0;
	return t->subtree;
}
 
int Hash(treap *t){
	if (!t)return 0;
	return t->H;
}
 
int revhash(treap *t){
	if (!t)return 0;
	return t->RH;
}
 
void recalc(treap *&t){
	if (!t)return;
	t->subtree=1;
	t->H=0;
	t->RH=0;
	for (auto it:t->sons){
		if (!it)continue;
		t->subtree+=it->subtree;
	}
	
	int l=0;
	t->H=(t->H+Hash(t->sons[0]))%mod;
	l+=size(t->sons[0]);
	t->H=(t->H+((t->c)-'a'+1)*P[l])%mod;
	l++;
	t->H=(t->H+(Hash(t->sons[1]))*P[l])%mod;
	l=0;
	t->RH=(t->RH+revhash(t->sons[1]))%mod;
	l+=size(t->sons[1]);
	t->RH=(t->RH+((t->c)-'a'+1)*P[l])%mod;
	l++;
	t->RH=(t->RH+(revhash(t->sons[0]))*P[l])%mod;
}
array<treap*,2>split(treap *t,int ile){
	if (!t)return {nullptr,nullptr};
	if (size(t->sons[0])>=ile){
	  array<treap*,2>pom=split(t->sons[0],ile);
		t->sons[0]=pom[1];
		recalc(t);
		return {pom[0],t};
	}
	else{
		array<treap*,2>pom=split(t->sons[1],ile-size(t->sons[0])-1);
		t->sons[1]=pom[0];
		recalc(t);
		return {t,pom[1]};
	}
	assert(false);
	return {nullptr,nullptr};
}
 
treap *merge(treap *l,treap *r){
	if (!l)return r;
	if (!r)return l;
	if (l->priority<r->priority){
		l->sons[1]=merge(l->sons[1],r);
		recalc(l);
		return l;
	}
	else{
		r->sons[0]=merge(l,r->sons[0]);
		recalc(r);
		return r;
	}
}
treap *root;
void del(int l,int r){
	array<treap*,2>t1=split(root,l-1);
	array<treap*,2>t2=split(t1[1],r-l+1);
	root=merge(t1[0],t2[1]);
}
 
void wstaw(int pos,char c){
	if (pos>size(root)){
		root=merge(root,new treap(c));
		return;
	}
	array<treap*,2>t1=split(root,pos-1);
	root=merge(t1[0],merge(new treap(c),t1[1]));
}	
 
void pytaj(int l,int r){
	array<treap*,2>t1=split(root,l-1);
	array<treap*,2>t2=split(t1[1],r-l+1);
	if (Hash(t2[0])==revhash(t2[0])){
		cout<<"yes\n";
	}
	else cout<<"no\n";
	root=merge(merge(t1[0],t2[0]),t2[1]);
}	