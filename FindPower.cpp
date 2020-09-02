#include <iostream>
using namespace std;
int calculatepower(int base,int raisedto);
main()
{ int base,raisedto,result=0;
    cin>>base;
    cin>>raisedto;
    result=calculatepower(base,raisedto);
    cout<<base<<" raised to "<<raisedto<<" = "<<result<<endl;
}
int calculatepower(int base,int raisedto)
{
    if(raisedto!=0)
   return base*calculatepower(base,raisedto-1);
   else
    return 1;
}

