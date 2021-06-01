/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem Statement
/*
Given a string str and a pattern pat that consists of uppercase English alphabets [A-Z],
write a C program that finds the number of ways the pattern pat appears as a subsequence
in the string str.
*/
#include<iostream>
using namespace std;
int main(){
    string str,pat;
    cout<<"Enter the String: ";
    cin>>str;
    cout<<"Enter the Pattern: ";
    cin>>pat;
    int strleng=str.length();
    int patleng=pat.length();
    int a[patleng+1][strleng+1];

    for(int i=0;i<=patleng;i++){
        a[i][0]=0;
    }
    for(int i=0;i<=strleng;i++){
        a[0][i]=1;
    }

    for(int i=1;i<=patleng;i++){
        for(int j=1;j<=strleng;j++){
            if(str[j-1]==pat[i-1]){
                a[i][j]=a[i-1][j-1]+a[i][j-1];
            }
            else{
                a[i][j]=a[i][j-1];
            }
        }
    }
     /*for(int i=0;i<=patleng;i++){
        for(int j=0;j<=strleng;j++){
            cout<<a[i][j]<<" ";
            }
            cout<< endl;
        }
*/
    std::cout<< std::endl << " -----OUTPUT-----" << std::endl;
    cout<<"The number of ways the pattern appears as a subsequence in the string is-> "<<a[patleng][strleng]<<endl;



    return 0;
}
