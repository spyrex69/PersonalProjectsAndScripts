#include <iostream>
using namespace std;
char sign='+';
class ComplexNum{
private:
    int real;
    float imag;
public:
    ComplexNum(){
    }
    ComplexNum(int newReal,float newImag){
    real=newReal;
    imag=newImag;
    }
    void display(){
   cout<<"complex number is : "<<real<<" "<<sign<<" "<<imag<<"i"<<endl;
    }
    int getReal(){
    return real;}
    float getImag(){
    return imag;
    }
    ComplexNum operator +(ComplexNum &obj){
    int r=0; float i=0;
    r=this->getReal()+obj.getReal();
    i=this->getImag()+obj.getImag();
    sign=(i<0) ? '-' : sign;
    i = (i<0) ? (-1*i) : i;
    ComplexNum temp(r,i);
    return temp;
    }
};
ComplexNum addcomplex(ComplexNum n1,ComplexNum n2){
 int r=0; float i=0;
 r=n1.getReal()+n2.getReal();
 i=n1.getImag()+n2.getImag();
 sign=(i<0) ? '-' : sign;
 i = (i<0) ? (-1*i) : i;
 ComplexNum temp(r,i);
 return temp;
}
int main(){
    int real,imaginary;
    cout<<"Enter first number's real and imaginary part"<<endl;
    cin>>real; cin>>imaginary;
    ComplexNum comp1(real,imaginary);
    cout<<"Enter second number's real and imaginary part"<<endl;
    cin>>real; cin>>imaginary;
    ComplexNum comp2(real,imaginary);
    ComplexNum comp3;
comp1.display();
comp2.display();
cout<<"addition :"<<endl;
comp3=(comp1+comp2);
comp3.display();
//ComplexNum *ptr=&comp1;
//ptr->display();
//ptr=&comp3;
//ptr->display();
}
