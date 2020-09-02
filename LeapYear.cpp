#include <iostream>
using namespace std;
int main()
{ int n,i=0;
cout<<"Enter the how many years"<<endl;
cin>>n;
int years[n];
cout<<"Enter the years"<<endl;
for(i=0;i<n;i++) {cin>>years[i];}
for(i=0;i<n;i++)
{if(years[i]%4==0)
{
    if(years[i]%100==0)
    { if(years[i]%400==0)
    cout<<years[i]<<" Leap year"<<endl;
    else
        cout<<years[i]<<" not leap year"<<endl;
    }
    else
        cout<<years[i]<<" leap year"<<endl;
}
else
cout<<years[i]<<" not leap year"<<endl;
}
}
