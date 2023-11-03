void insvec(int x)
{
	for (int i=0;i<30;i++)
  {
  	if (!(x&(1<<i)))continue;
  	if (!basis[i])
  	{
  		ile++;
  		basis[i]=x;
  		return; 
  	}
  	x^=basis[i];
  }
}
 
bool check(int x)
{
	for (int i=0;i<30;i++)
	{
		if (!(x&(1<<i)))continue;
		if (!basis[i])return false;
		x^=basis[i];
	}
  return true;
}