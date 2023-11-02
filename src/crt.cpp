// działa do 10^9 dla większych __int128 lub ruskie chłopy
int normalize(int x,int mod){
  x%=mod;
  if (x<0)x+=mod;
  return x;
}
 
struct GCD_POM{
  // d - to koncowe nwd, x i y to rozwiazania ax+by=nwd(a,b)
  int x,y,d;
};
GCD_POM EXT_GCD(int a,int b){
  if (b==0)return {1,0,a};
  GCD_POM syn=EXT_GCD(b,a%b);
  //b*x1+a%b*y1=g
  //b*x1+(a-(a/b)*b)*y1=g
  //b*x1+a*y1-b*(a/b)*y1
  //y1,(x1-(a/b)*y1)
  return {syn.y,syn.x-(a/b)*syn.y,syn.d};
}
 
int nww(int a,int b){
   return a/__gcd(a,b)*b;
}  
 
pii crt(vector<pii>c){
  // zwraca -1 kiedy nie ma rozwa, w przeciwnym wypadku wynik
  // wektor c postaci przystawanie, modulo w sensie x przystaje c[i].st mod c[i].nd 
  if (c.empty())return {-1,-1}; // opcjonalnie w zaleznosci od zadania
  for (auto &it:c)normalize(it.st,it.nd);
  int ans=c.back().st,lcm=c.back().nd;
  c.pop_back();
  while (!c.empty()){
    pii now=c.back();
    c.pop_back();
    auto pom=EXT_GCD(lcm,now.nd);
    int x1=pom.x,d=pom.d;
    if ((now.st-ans)%d!=0)return {-1,-1};
    ans=normalize(ans+x1*(now.st-ans)/d%(now.nd/d)*lcm,lcm*now.nd/d);
    lcm=nww(lcm,now.nd);
  }
  return {ans,lcm};
}