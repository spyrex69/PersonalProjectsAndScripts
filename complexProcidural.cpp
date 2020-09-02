#include <iostream>
using namespace std;
typedef struct complex
{   float real;
    float imag;
}complexnumber;
complexnumber addcomplex(complex,complex);
int main()
{ complex num1,num2,temporary;
 char signofImag;
    cout<<"Enter the first value of the complex number"<<endl;
    cout<<"Enter the real part :"<<endl;
    cin>>num1.real;
    cout<<endl;
    cout<<"Enter the imaginary part :"<<endl;
    cin>>num1.imag;
    cout<<"Enter the values of second complex number"<<endl;
     cout<<"Enter the real part : ";
     cin>>num2.real;
     cout<<endl;
     cout<<"Enter the imaginary part"<<endl;
     cin>>num2.imag;
     signofImag=(temporary.imag>0) ? '+': '-';
     temporary.imag=(temporary.imag>0) ? temporary.imag: -temporary.imag;

     temporary=addcomplex(num1,num2);
     cout<<"sum of complex number : "<<temporary.real<<" "<<signofImag<<" "<<temporary.imag<<" i";
}
complexnumber addcomplex(complex n1,complex n2)
{ complex temp;
  temp.real=n1.real+n2.real;
  temp.imag=n1.imag+n2.imag;
  return(temp);
}
