#include <iostream>
#include <algorithm>
using namespace std;
int BinarySearch(int A[],int n,int x);
int main()
{ int n=10;
    int A[n]={2,6,7,8,10,20,56,69,70,75};
   int x=698;
   int res=BinarySearch(A,n,x);
   cout<<res;
}
int BinarySearch(int A[],int n,int x)
{
    int start=0,End=n-1;
    while(start<=End){
        int mid=(start+End)/2;
        if(A[mid]==x)
            return mid;
        else if(A[mid]<x)
            start=mid+1;
        else
            End=mid-1;
    }
    return -1;
}

