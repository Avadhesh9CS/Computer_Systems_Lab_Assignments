/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem Statement
/*
Given prices Price[] and volumes Volume[] of n different indivisible items, you are
asked to put them into a knapsack of volume Capacity such that the total price of the
items is maximized. Note that the total volume of all the items must be less than or equal to
the volume of the knapsack.
*/
#include<iostream>
using namespace std;
int main(){
    int no_of_element,capacity;
    cout<<"Enter no of element: ";
    cin>>no_of_element;
    int vol[no_of_element+1],profit[no_of_element+1];
    cout<<"Enter volume of each element: ";
    vol[0]=0;//there is no element at location 0
    for(int i=1;i<=no_of_element;i++){
        cin>>vol[i];
    }
    cout<<"Enter profit of each element: ";
    profit[0]=0;//there is no element at location 0
    for(int i=1;i<=no_of_element;i++){
        cin>>profit[i];
    }
    cout<<"Enter caapacity of knapsack: ";
    cin>>capacity;
    int a[no_of_element+1][capacity+1];
    for(int i=0;i<=no_of_element;i++){
        a[i][0]=0;
    }
    for(int i=0;i<=capacity;i++){
        a[0][i]=0;
    }

    for(int element=1;element<=no_of_element;element++){
        for(int remaining_capacity=1;remaining_capacity<=capacity;remaining_capacity++){
            int with,without;
            if(remaining_capacity>=vol[element]){
                with=profit[element]+a[element-1][remaining_capacity-vol[element]];
                without=a[element-1][remaining_capacity];
                a[element][remaining_capacity]=with>without?with:without;
            }else{
                a[element][remaining_capacity]=a[element-1][remaining_capacity];
            }
        }
    }

    std::cout<< std::endl << " -----OUTPUT-----" << std::endl;
    cout<<"Maximum profit is: "<<a[no_of_element][capacity]<<endl;

    for(int i=0;i<=no_of_element;i++){
    for(int j=0;j<=capacity;j++){
        cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

    return 0;
}
