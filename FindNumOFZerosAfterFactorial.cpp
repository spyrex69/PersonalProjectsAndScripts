#include <iostream>
using namespace std;
unsigned long fact(int);
int checkzeros(unsigned long *);
int main()
{ int n;
  cin>>n;
  int res=fact(n);
  cout<<res<<endl;
  cout<<checkzeros(&res)<<endl;
}
 unsigned long fact(int n)
{
    if(n==1)
        return n;
    else
        return n*fact(n-1);
}
 int checkzeros(unsigned long *n)
{ int counter=0,rev=0;
   while(*n!=0)
   { int r=*n%10;
       rev=(rev*10)+r;
       if(r==0){
        counter++;
       }
       *n=*n/10;
   }
   return counter;
}
