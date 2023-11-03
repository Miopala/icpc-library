struct pt
{
	public:
		int x,y;
		void in() {scanf("%d%d", &x, &y);}
		pt& operator += (const pt& o) {x+=o.x, y+=o.y; return *this;}
		pt& operator -= (const pt& o) {x-=o.x, y-=o.y; return *this;}
 
		friend pt operator + (pt a, const pt& b) {return a+=b;}
		friend pt operator - (pt a, const pt& b) {return a-=b;}
 
		int operator / (const pt& o) const {return x*o.y-y*o.x;}
 
		bool operator == (const pt& o) {return x==o.x&&y==o.y;}
		bool operator < (const pt& o) const {return x < o.x || !(o.x < x) && y < o.y;}
};
 
int dist(const pt& a, const pt& b) {return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
 
const int MN = 1e5+10;
 
int N;
pt a[MN];
std::vector<pt> hull;
 
int main()
{
	scanf("%d", &N);
	for(int i=0;i<N;++i)
		scanf("%d", &a[i].x);
	for(int i=0;i<N;++i)
		scanf("%d", &a[i].y);
	std::sort(a, a+N);
 
	hull.push_back(a[0]);
	for(int i=1;i<N;++i)
	{
		for(size_t n;(n=hull.size())>1 && (hull[n-1]-hull[n-2])/(a[i]-hull[n-1])>=0;) hull.pop_back();
		hull.push_back(a[i]);
	}
	for(int i=N-2;i>=0;--i)
	{
		for(size_t n;(n=hull.size())>1 && (hull[n-1]-hull[n-2])/(a[i]-hull[n-1])>=0;) hull.pop_back();
		hull.push_back(a[i]);
	}
 
	assert(hull[0] == *hull.rbegin());
	int M=hull.size();
 
	int f=0;
	for(int i=0,j=0;i<M;++i)
	{
		if(j<i) j=i;
		int p=dist(hull[i], hull[j]);
		for(;j+1<M && p<dist(hull[i], hull[j+1]);++j)
		{
			p=dist(hull[i], hull[j+1]);
			if(f<p)f=p;
		}
		--j;
	}
	printf("%d\n", f);
	return 0;
}