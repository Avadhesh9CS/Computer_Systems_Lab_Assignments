/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem Statement
/*
Write a program that takes as input an array A of n non-negative integers and prints a histogram
(with vertical orientation) using ‘#’ character, without using extra storage (such as
a 2-D array).
*/

#include<iostream>
using namespace std;
int main(){
    int n,max=0;
    cout<<"Enter no of Element of array: ";
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
        if(max<a[i]){
            max=a[i];
        }
    }
    for(int i=max;i>0;i--){
        for(int j=0;j<n;j++){
            if(a[j]==i){
                cout<<"#";
                a[j]--;
            }
            else
                cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}
