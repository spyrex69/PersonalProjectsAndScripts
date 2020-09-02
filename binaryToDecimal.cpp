#include <iostream>
#include <math.h>
using namespace std;
int decTobi(int);
int biTodec(long long );
int octToDec(long long);
int main()
{
    int n,n1,n2,n3;
    cin>>n;
    cin>>n1;
    cin>>n2;
    cin>>n3;
    int binary=decTobi(n);
    int deci=biTodec(n1);
    cout<<n<<" = "<<binary<<endl;
    cout<<n1<<" = "<<deci<<endl;
    deci=octToDec(n2);
    cout<<n2<<" = "<<deci<<endl;
/*    int oct=decTooct(n3);
    cout<<n3<<" = "<<oct<<endl;
    */
    }
int decTobi(int n)
{ int r=0,i=1,step=1,bi=0;
while(n!=0)
{
    r=n%2;
    cout<<"step : "<<step++<<"  "<<n<<"/2 "<<"Remainder= "<<r<<" qoutient = "<<n/2<<endl;
    n=n/2;
    bi+=i*r;
    i=i*10;
}
return bi;
}
int biTodec(long long num)
{ int r,i=0,deci=0;
while(num!=0)
{ r=num%10;
   num/=10;
   deci+=r*pow(2,i);
   i++;
}
return deci;
}
int octToDec(long long num)
{ int r=0,decnum=0,i=0;
    while(num!=0)
{  r=num%10;
   num/=10;
    decnum+=r*pow(8,i);
    i++;
}
return octnum;

}
