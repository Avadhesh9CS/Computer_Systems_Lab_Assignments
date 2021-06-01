/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
// Problem Statement
/*
write a C/C++ program that decides whether G generates w or not. You are
supposed to implement Cocke-Younger-Kasami (CYK) algorithm.
*/

#include<iostream>
#include<vector>
#include<set>
#include<string.h>
using namespace std;
vector<string>* Production;
vector<string> table[100][100];
int nP,l;

vector<string> breakProduction(string str){
	string word = "";
  	vector<string> a;
	for (auto x : str){
		if (x == ' ' || x == '>'){
            a.push_back(word);
			word = "";
		}
		else{
			word = word + x;
		}
	}
    a.push_back(word);
    return a;
}

set<string> gen_comb(vector<string> a,vector<string> b,set<string> res){
    for(auto x : a){
        for(auto y : b){
            int k=0;
            while(k<nP){
                if(Production[k][1]==x && Production[k][2]==y){
                    res.insert(Production[k][0]);
                }
                k++;
             }
         }
     }
    return res;
}

vector<string> addData(vector<string> a,set<string> b){
    for(auto y : b){
        a.push_back(y);
    }
    return a;
}

void printOutput(){
    int i,j,t,k;
    for(i=0;i<l;i++){
        cout<<"   |";
        for(j=0;j<l;j++){
            t=0;
            if(table[i][j].empty()){
                cout<<"          ";
            }
            else{
                cout<<" ";
                for (auto y : table[i][j]){
                   cout<<y<<" ";
                   t++;
                 }
                 if(t==1){
                    cout<<"      ";
                 }else if(t==2){
                    cout<<"   ";
                    }
                }
                cout<<"|";
            }
        cout<<endl;
    }
}

int main(){
    int nV,nSigma,pt,j;
    string p,start,str;
    cout<<"Enter no of Non Terminal, Terminal and Production in Language ";
    cin>>nV>>nSigma>>nP;
    Production=new vector<string>[nP];
    cin.ignore();
    cout<<"Enter each Production in prescribed format as A0>A1 A2 OR A0>a1"<<endl;
    while(j<nP){
        cout<<"Enter production "<<j+1<<": ";
        getline(cin, p);
        Production[j++]=breakProduction(p);
       }
    cout<<"Enter start symbol: ";
    getline(cin, start);
    cout<<"String should be enter as a0 a1 a5 a2, space should be there b/w each terminal"<<endl;
    cout<<"Enter string which is to be checked that it can generate from given grammar : ";
    getline(cin, p);
    vector<string> st=breakProduction(p);
    l=st.size();
    for(int i=0;i<l;i++){
		string s= "";
		s+=st[i];
		for(int j=0;j<nP;j++){
            string x=Production[j][1];
            if(x==s){
                table[i][i].push_back(Production[j][0]);
            }
		}
	}
	set<string> re;
    vector<string> pr;
    vector<string> r;
    for(int i=1;i<l;i++){
        for(int j=i;j<l;j++){
            re.clear();
            for(int k=j-i;k<j;k++){
                re= gen_comb(table[j-i][k],table[k+1][j],re);
            }
            table[j-i][j]=addData(table[j-i][j],re);
        }
    }
    std::cout<< std::endl<< "          ---------------OUTPUT--------------" <<endl<<endl;
	printOutput();
	cout<<endl;
	for(auto x:table[0][l-1]){
        if(x==start){
            cout<<"String can be generated";
            return 0;
        }
	}
	cout<<"String w can NOT be generated";
    return 0;
}
