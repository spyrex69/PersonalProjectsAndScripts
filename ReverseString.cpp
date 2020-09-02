#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
void Revers(string sen);
main()
{ string message;
cin>>message;
Revers(message);
}
void Revers(string sen)
{ size_t numofchar= sen.size();
   if(numofchar==1)
    cout<<sen<<endl;
   else
   {
  cout<<sen[numofchar-1];
   Revers(sen.substr(0,numofchar-1));
   }
}
