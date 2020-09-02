#include <iostream>

using namespace std;
void merg(int left[],int right[],int A[],int ln,int rn);
void mergsort(int A[],int n);
int print(int A[],int n);

int main()
{ int n;
cout<<"Enter the cap"<<endl;
cin>>n;
int A[n];
cout<<"Enter the values"<<endl;
for(int i=0;i<n;i++)
{
    cin>>A[i];
}
cout<<"before : "<<endl;
print(A,n);
cout<<"after : "<<endl;
mergsort(A,n);
print(A,n);

}
void merg(int left[],int right[],int A[],int ln=0,int rn=0)
{ int i=0,j=0,k=0;

    while(i<ln && j<rn)
    {
        if(left[i]<right[j])
        {
            A[k]=left[i];
            i++;  k++;
        }
        else{ A[k]=right[j]; j++;  k++; }

    }
    while(i<ln)
    {
        A[k]=left[i];
        i++;
        k++;
    }
     while(j<rn)
    {
        A[k]=right[j];
        j++;
        k++;
    }
}
void mergsort(int A[],int n)
{ if(n<2){
    return;}
int i;
 int mid=n/2;
 int left[mid];
 int right[n-mid];
 for(i=0;i<mid;i++){ left[i]=A[i]; }
 for(i=mid;i<n;i++){right[i-mid]=A[i];}
 mergsort(left,mid);
 mergsort(right,n-mid);
 merg(left,right,A,mid,n-mid);
}
int print(int A[],int n)
{
    for(int i=0;i<n;i++)
{
    cout<<A[i]<<endl;
}
}
