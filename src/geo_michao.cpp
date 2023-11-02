const ld inf=1e18+9;
const ld eps=1e-12;
template<class T>
struct point{
  T x,y;
  point():x(0),y(0){} 
  point(const T &_x, const T &_y) : x(_x), y(_y) {}
  void swap(point& other) {swap(x, other.x); swap(y, other.y); }
  template<class T1>point& operator += (const point<T1>& other){
      x+=other.x;y+=other.y;
      return *this;
  }
  
  template<class T1>point& operator -= (const point<T1>& other){
      x-=other.x;y-=other.y;
      return *this;
  }
  
  template<class T1>point& operator *= (const point<T1>& other){
      x*=other.x;y*=other.y;
      return *this;
  }
  
  template<class T1>point& operator /= (const point<T1> & other){
      assert(other.x!=0);
      assert(other.y!=0);
      x/=other.x;y/=other.y;
      return *this;
  }
  
  template<class T1>point& operator *=(const T1 &factor){
   x*=factor;
   y*=factor;
   return *this;
  }  
  
  template<class T1>point& operator /=(const T1 &factor){
   x/=factor;
   y/=factor;
   return *this;
  }
  
};
const point<int>zero(1,0);
template<class T> constexpr point<T> makepoint(const T &x,const T &y){
   return point<T>(x,y);
}
 
template<class T>point <T> operator-(const point<T>&p){
   return makepoint(-p.x,-p.y);
}
 
template<class T> point<T> operator+(const point<T> &p1, const point<T> &p2){
  return makepoint<T>(p1.x+p2.x,p1.y+p2.y); 
}
 
template<class T> point<T> operator%(const point<T> &p1, const point<T> &p2){
  return makepoint<T>(p1.x*p2.x,p1.y*p2.y); 
}
 
template<class T> point<T> operator-(const point<T> &p1, const point<T> &p2){
  return makepoint<T>(p1.x-p2.x,p1.y-p2.y); 
}
 
template<class T> point<T> operator/(const point<T> &p1, const point<T> &p2){
  return makepoint<T>(p1.x/p2.x,p1.y/p2.y); 
}
 
template<class T> T operator ^(const point<T> &p1, const point<T> &p2){
  return p1.x*p2.y-p2.x*p1.y; 
}
 
template<class T> T operator *(const point<T> &p1, const point<T> &p2){
  return p1.x*p2.x+p1.x*p2.y; 
}
 
template<class T>bool operator ==(const point<T> &p1, const point<T> &p2){
  return p1.x==p2.x && p1.y==p2.y; 
}
 
template<class T>bool operator >(const point<T> &p1, const point<T> &p2){
  return p1.x>p2.x || (p1.x==p2.x && p1.y>p2.y); 
}
 
template<class T>bool operator <(const point<T> &p1, const point<T> &p2){
  return p1.x<p2.x || (p1.x==p2.x && p1.y<p2.y); 
}
 
template<class T>bool operator >=(const point<T> &p1, const point<T> &p2){
  return (p1>p2) || (p1==p2);
}
 
template<class T>bool operator <=(const point<T> &p1, const point<T> &p2){
  return (p1<p2) || (p1==p2);
}
 
template<class T> T distsqr (const point<T>&p1, const point<T> &p2){
   point<T> new_point=p1-p2;
   new_point*=new_point;
   T sum=new_point.x+new_point.y;
   return sum; 
}
 
template<class T> ld dist (const point<T>&p1, const point<T>&p2){
   ld sum=sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
   return sum;
}
 
template<class T>bool right(const point<T>&p,const point<T> &w){
  return ((w^p)<0);
}
 
template<class T>bool left(const point<T>&p,const point<T> &w){
  return ((w^p)>0);
}
 
template<class T>bool collinear(const point<T>&p,const point<T> &w){
  return ((w^p)==0);
}
template<class T>
struct line{
   point<T> p1,p2;
   line():p1(makepoint(0,0)),p2(makepoint(0,1)) { } 
   line<T>(const point<T> &_x, const point<T> &_y) : p1(_x), p2(_y) {
      if (p1.x>p2.x)swap(p1,p2);
      if (p1.x==p2.x && p1.y>p2.y)swap(p1,p2);
   }
   T a=p2.y-p1.y;
   T b=p1.x-p2.x;
   T c=a*p1.x+b*p1.y;
   bool pointvssline(const point<T>&p){
     point <T>checker1=p2-p1,checker2=p-p1;
     if ((checker1^checker2)==0)return true;
     return false;
   }
};
template<class T>
pair<point<ld>,point<ld>>gentopoint(const T &a,const T &b,const T &c){
  assert(a!=0 || b!=0);
  if (b==0){
    ld x=(ld)-c/a;
    ld y1=1,y2=2;
    point<ld>t1=makepoint(x,y1),t2=makepoint(x,y2);
    return mp(t1,t2);
  }
  else{
    ld x1=1;
    ld y1=(ld)(-c-a*x1)/b;
    T x2=2;
    ld y2=(ld)(-c-a*x2)/b;
  }
}
 
template<class T>
// -1 parallel, 0 pokrywają się, 1 przecinają
int inter(const line<T>&l1,const line<T>&l2){
   T a1=l1.a,b1=l1.b;
   T a2=l2.a,b2=l2.b;
   T xd1=(l1.p2-l1.p1)^(l2.p1-l1.p1);
   T xd2=(l1.p2-l1.p1)^(l2.p2-l1.p1);
   if (xd1==0 && xd2==0)return 0;
   int det=(a1*b2-a2*b1);
   if (det==0)return -1;
   return 1;
}

template<class T>
point<ld> operator*(const point<T> &p1, const ld &p2){
  return makepoint<ld>(p1.x*p2,p1.y*p2); 
}   
   
template<class T>point<ld> inter_point(const line<T>&l1,const line<T>&l2){ 
   assert(inter(l1,l2)==1);
   point<T>s2=l2.p2-l2.p1; // slope 2
   point<T>s1=l1.p2-l1.p1; // slope 1
   //l1.p1.x+s1.x*t=l2.p1.x+s2.x*t;
   //l1.p1.y+s1.y*t=l2.p1.y+s2.y*t;
   //t=(s2^l1.p1+s2^l2.p1)/(s1^s2)
   ld t=(ld)((s2^l1.p1)+(l2.p1^s2))/(s1^s2);
   point<ld>ans=makepoint((ld)0,(ld)0);
   ans+=(s1*t);
   ans+=l1.p1;
   return ans;
}

template<class T1,class T2>
bool in(T1 a,T2 l,T2 r){
   if (l>r)swap(l,r);
   //cout<<"WTF "<<l<<" "<<a<<" "<<r<<" "<<(a<=r)<<"\n";
   return (ld)a+eps>=(ld)l && (ld)a<=(ld)r+eps; 
}
 
template<class T>
struct segment{
  point<T> p1,p2;
   segment():p1(makepoint(0,0)),p2(makepoint(0,1)) { } 
   segment<T>(const point<T> &_x, const point<T> &_y) : p1(_x), p2(_y) {
      if (p1.x>p2.x)swap(p1,p2);
      if (p1.x==p2.x && p1.y>p2.y)swap(p1,p2);
   }
   T a=p2.y-p1.y;
   T b=p1.x-p2.x;
   T c=a*p1.x+b*p1.y;
   bool pointvsseg(const point<T>&p){
     //cout<<"ILE "<<p.x*a+p.y*b+c<<"\n";
     point <T>checker1=p2-p1,checker2=p-p1;
     //cout<<"ODPOCZATKU "<<(checker1^checker2)<<"\n";
     if ((checker1^checker2)==0){
       if (in(p.x,p1.x,p2.x) && in(p.y,p1.y,p2.y))return true;
       return false;
     }
     return false;
   }
};
 
template<class T>
int inter(const segment<T>&l1,const segment<T>&l2){
   T a1=l1.a,b1=l1.b;
   T a2=l2.a,b2=l2.b;
   T xd1=(l1.p2-l1.p1)^(l2.p1-l1.p1);
   T xd2=(l1.p2-l1.p1)^(l2.p2-l1.p1);
   if (xd1==0 && xd2==0 && ((in(l1.p1.x,l2.p1.x,l2.p2.x) && in(l1.p1.y,l2.p1.y,l2.p2.y)) ||
                           (in(l1.p2.x,l2.p1.x,l2.p2.x) && in(l1.p2.y,l2.p1.y,l2.p2.y)) ||
                           (in(l2.p1.x,l1.p1.x,l1.p2.x) && in(l2.p1.y,l1.p1.y,l1.p2.y)) ||
                           (in(l2.p2.x,l1.p1.x,l1.p2.x) && in(l2.p2.y,l1.p1.y,l1.p2.y))))return 0;//pokrywaja sie
   T det=(a1*b2-a2*b1);
   if (det==0)return -1;
   return 1;
}
   
template<class T>point<ld> inter_point(const segment<T>&l1,const segment<T>&l2){
   assert(inter(l1,l2)==1); 
   point<T>s2=l2.p2-l2.p1; // slope 2
   point<T>s1=l1.p2-l1.p1; // slope 1
   //l1.p1.x+s1.x*t=l2.p1.x+s2.x*t;
   //l1.p1.y+s1.y*t=l2.p1.y+s2.y*t;
   //t=(s2^l1.p1+s2^l2.p1)/(s1^s2)
   ld t=(ld)((s2^l1.p1)+(l2.p1^s2))/(s1^s2);
   point<ld>ans=makepoint((ld)0,(ld)0);
   ans+=(s1*t);
   ans+=l1.p1;
   if (!in(ans.x,l1.p1.x,l1.p2.x))return {inf,inf};
   if (!in(ans.y,l1.p1.y,l1.p2.y))return {inf,inf};
   if (!in(ans.x,l2.p1.x,l2.p2.x))return {inf,inf};
   if (!in(ans.y,l2.p1.y,l2.p2.y))return {inf,inf};
   return ans;
}
template<class T>
struct polygon{
   vector<point<T>>p;
   bool sorted=false;
   polygon(){}
   polygon(const vector<point<T>>&_p):p(_p){}
   vector<point<T>> convex_hull(){
     vector<point<T>> hull,pom,stos;
     for (auto &it:p)pom.pb(it);
     sort(pom.begin(),pom.end());
     pom.erase(unique(pom.begin(), pom.end()), pom.end());
     for (int iter=0;iter<2;iter++){
        for (auto v:pom){
           while (sz(stos)>=2){
             int xd=sz(stos);
             if (left(v-stos[xd-2],stos[xd-1]-stos[xd-2]))break;
             //if (collinear(v-stos[xd-2],stos[xd-1]-stos[xd-2]))break;
             stos.pop_back();
           }
           stos.pb(v);
        }
      for (int i=0;i<sz(stos)-1;i++)hull.pb(stos[i]);
      stos.clear(),reverse(pom.begin(),pom.end()); 
     }
     return hull;
   }
   
   static int dir(const point<T> &v) {
      // -1 prawo, 1 lewo
     if (v.y<0)return -1;
     if (v.y==0 && 0<=v.x)return 0;
     return 1;
   }
   
   static bool cmp1(const point<T> &p1,const point<T> &p2) {
      int a=dir(p1);
      int b=dir(p2);
      if (a!=b)return a<b;
      if ((p1^p2)!=0)return (p1^p2)>0;
      return p1.x<p2.x;
   }  
   
   void angle_sort(){
      sorted=true;
      sort(p.begin(),p.end(),cmp1);
   }
   
   T area(){ // trzymamy directed area x 2 
      //if (!sorted)
      //angle_sort(),sorted=true;
      T sum=0;
      for (int i=0;i<sz(p);i++){
         int j=(i+1);
         if (j==sz(p))j=0;
         sum+=p[i]^p[j];
      }
      return sum;
   }
   
   bool ipi(point <T> p1){
      //if (!sorted)
      //angle_sort(),sorted=true;
      int odp=0;
      point<T>pocz=makepoint((int)-1e9-9,(int)-1e9-8);
      for (int i=0;i<sz(p);i++){
         point <T>xd1=p[i];
         point <T>xd2=p[(i+1)%sz(p)];
         segment<T> s1(xd1,xd2);
         segment<T> s2(pocz,p1);
         if (inter(s1,s2)==1 && inter_point(s1,s2).x!=inf){
            odp++;
         }
      }
      //assert(abs(odp)<=1);
      return odp&1;
   } // is point inside
};