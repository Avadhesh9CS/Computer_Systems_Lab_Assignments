/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
/*
A professional robber is planning to rob houses along a street. Each house has a certain amount of money
 stashed.  All houses at this place are arranged in a circle.  That means the first house is the neighbor of
 the last one. Meanwhile, adjacent houses have a security system connected, and it will automatically
 contact the police if two adjacent houses were broken into on the same night.Given a list of n non-negative
  integers A representing the amount of money of each house,return the maximum amount of money you can rob
  tonight without alerting the police.
*/
#include<iostream>
using namespace std;
int main(){
    int N,t,revenue;
    cout<<"Enter no houses on a street: ";
    cin>>N;
    cout<<"Enter amount of money in each house:"<<endl;
    int money[N],stell[N+1][2];
    for(int i=0;i<N;i++){
        cin>>money[i];
        stell[i][0]=0;
        stell[i][1]=0;
    }
    stell[1][0]=money[0];
    stell[1][1]=1;

    //Same as it is linear street for n-1 element
    for(int i=2;i<N;i++){
        if(stell[i-2][0]+money[i-1]>=stell[i-1][0]){
           stell[i][0]=stell[i-2][0]+money[i-1];
           stell[i][1]=stell[i-2][1];
        }else{
           stell[i][0]=stell[i-1][0];
           stell[i][1]=stell[i-1][1];
        }
    }

    //Calculation for last element to make it circular street
    if(stell[N-2][0]+money[N-1]>stell[N-1][0] && stell[N-2][1]!=1 && N>1){
        stell[N][0]=stell[N-2][0]+money[N-1];
        stell[N][1]=stell[N-2][1];
    }else if(stell[N-2][0]+money[N-1]>stell[N-1][0] && stell[N-2][1]==1){
        if(stell[N-2][0]+money[N-1]-money[0]>=stell[N-2][0]){
            stell[N][0]=stell[N-2][0]+money[N-1]-money[0];
            stell[N][1]=0;
        }
        else{
            stell[N][0]=stell[N-2][0];
            stell[N][1]=stell[N-2][1];
        }
    }else{
        stell[N][0]=stell[N-1][0];
        stell[N][1]=stell[N-1][1];
    }
    std::cout<< std::endl<< "          ---------------OUTPUT--------------" <<endl;
    cout<<"Maximum amount of money robber can rob tonight without alerting the police: "<<stell[N][0]<<endl;
    return 0;
}
