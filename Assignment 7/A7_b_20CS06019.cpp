/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*Consider a highway of M miles. Your task is to place toll plazas on the highway. The possible
sites for toll plazas are given by number x0 < x1 < : : : < xn-1, specifying positions in miles
measured from start end of the road. If a toll plaza is placed at position xi, a revenue of ri >
0 can be collected. There is a restriction that two toll plazas can be placed > t miles away.
Write a C program that maximizes the total revenue collection.*/
#include<iostream>
using namespace std;
int main(){
    int M,N,t,revenue;
    cout<<"Enter length of highway in miles: ";
    cin>>M;
    cout<<"Enter no of toll plaza on that highway: ";
    cin>>N;
    cout<<"Enter distance from start at which toll plaza is placed along with its profit:"<<endl;
    cout<<"Distance     Cost"<<endl;
    int X[N][2],profit[M+1];
    for(int i=0;i<N;i++){
        cin>>X[i][0]>>X[i][1];
    }
    cout<<"Enter restricted distance less than which two toll plazas can not be placed: ";
    cin>>t;
    profit[0]=0;
    int j=0,k,l;

    // main code that implement dynamic programming
    for(int i=1;i<=M ;i++){
        if(X[j][0]!=i-1 || j>=N){
            profit[i]=profit[i-1];
        }else{
            if(i-t-1>0){
                profit[i]=profit[i-1]>profit[i-t-1]+X[j][1]?profit[i-1]:profit[i-t-1]+X[j][1];
            }else{
                profit[i]=profit[i-1]>profit[0]+X[j][1]?profit[i-1]:profit[0]+X[j][1];
            }
        j++;
        }
    }
    std::cout<< std::endl << " -----OUTPUT-----" << std::endl;
    cout<<"Maximum profit is: "<<profit[M]<<endl;

return 0;
}
