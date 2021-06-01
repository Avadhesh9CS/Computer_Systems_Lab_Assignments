/*
    Created by: Avadhesh Chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem
/*
Given n (1 <= n <= 30) arrays of integers A1, A2, ..., An of lengths l1, l2, ..., ln
respectively (1 <= li <= 1000), where each array is already sorted in non-decreasing
order. Design an efficient C program using ternary minimum heap (heap having three
children) that merges all the arrays into a single sorted array A of length l = l1+ l2 + ... +
ln in non-decreasing order.
*/

#include <iostream>
#include <vector>
using namespace std;

// Function to merge remaining last two arrays
vector<int> mergeTwoArrays(vector<int> l, vector<int> r){
    // array to store the result after merging l and r
    vector<int> ret;

    // variables to store the current indexes for l and r
    int l_in = 0, r_in = 0;

    // loop to merge l and r using two index variable
    while (l_in + r_in < l.size() + r.size()) {
        if (l_in != l.size() && (r_in == r.size() || l[l_in] < r[r_in])) {
            ret.push_back(l[l_in]);
            l_in++;
        }
        else {
            ret.push_back(r[r_in]);
            r_in++;
        }
    }
    return ret;
}

// Function to merge three arrays
vector<int> mergeThreeArrays(vector<int> l,vector<int> m, vector<int> r){
    // array to store the result after merging l,m and r
    vector<int> ret;

    // variables to store the current indexes for l , m and r
    int l_in = 0, m_in = 0,r_in=0;

    // loop to merge l ,m and r using three index variable
    while (l_in +m_in+ r_in < l.size() +m.size()+ r.size()) {

        if ((l_in != l.size() || m_in != m.size())
             && (r_in == r.size() || l[l_in] < r[r_in] || m[m_in] < r[r_in])){

            if(l_in != l.size() && (m_in == m.size() || l[l_in] < m[m_in])){
               ret.push_back(l[l_in]);
               l_in++;
               }

            else{
                ret.push_back(m[m_in]);
                m_in++;
            }

        }
        else {
            ret.push_back(r[r_in]);
            r_in++;
        }
    }

    return ret;
}

// Function to merge all the arrays
vector<int> mergeArrays(vector<vector<int> > arr){
    // 2D-array to store the results of
    // a step temporarily
    vector<vector<int> > arr_s;

    // Loop to make pairs of arrays and merge them
    while (arr.size() != 1) {

        // To clear the data of previous steps
        arr_s.clear();

        for (int i = 0; i < arr.size(); i += 3) {
            if (i == arr.size() - 1)
                arr_s.push_back(arr[i]);
            else if(i == arr.size() - 2)
                arr_s.push_back(mergeTwoArrays(arr[i],
                                               arr[i + 1]));
            else
                arr_s.push_back(mergeThreeArrays(arr[i],
                                               arr[i + 1],arr[i+2]));
        }

        arr = arr_s;
    }

    // Returning the required output array
    return arr[0];
}

// Driver Code
int main(){
    int n;
    cout<<"Enter no of arrays: ";
    cin>>n;
    cout<<"Enter size of each array: ";
    int arraySize[n];
    vector<vector<int>> arr(n);
    //Storing size of each array
    for(int i=0;i<n;i++){
        cin>>arraySize[i];
    }
    // Storing data in each array
    for(int i=0;i<n;i++){
        arr[i] = vector<int>(arraySize[i]);
        std::cout<<"Enter elements of "<<i<<"th array: ";
        for(int j=0;j<arraySize[i];j++){
            cin>>arr[i][j];
        }
    }
    // Merged sorted array
    vector<int> output = mergeArrays(arr);
    // Output of merged array
    std::cout<< std::endl << "       -----OUTPUT-----" << std::endl;
    for (int i = 0; i < output.size(); i++)
        cout << output[i] << " ";

    return 0;

}
