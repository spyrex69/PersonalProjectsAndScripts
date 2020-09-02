#include <iostream>
using namespace std;

int main()
{ int i=0,j=0; string lines[10];
cout<<"Enter the 10 words"<<endl;
for(i=0;i<9;i++){
   getline(cin,lines[i]);
}
for(i=0;i<9;i++){
    for(j=i+1;j<10;j++){
        if(lines[i]>lines[j]){
            swap(lines[i],lines[j]);
        }
    }
}
cout<<"In lexigraphic order"<<endl;
for(i=0;i<9;i++){
    cout<<lines[i]<<endl;
}
}



