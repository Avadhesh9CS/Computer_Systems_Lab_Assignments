/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem Statement
/*
Given a two dimensional array A of m × n, print the array elements that appear in the spiral
order.
*/
#include<iostream>
using namespace std;
int main(){
   int m,n,i;
   cout<<"Enter no of rows: ";
   cin>>m;
   cout<<"Enter no of column: ";
   cin>>n;
   int a[m][n];
   for(i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
   }

   int r=0,c=0;
   while(r<m && c<n){
        for (i =c; i < n; ++i) {
			cout << a[c][i] << " ";
		}
		r++;

		for (i = r; i < m; ++i) {
			cout << a[i][n - 1] << " ";
		}
		n--;

		if (r < m) {
			for (i = n - 1; i >= c; --i) {
				cout << a[m - 1][i] << " ";
			}
			m--;
		}

		if (c < n) {
			for (i = m - 1; i >= r; --i) {
				cout << a[i][c] << " ";
			}
			c++;
		}
   }
return 0;
}
