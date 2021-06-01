/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
/*
This program consist of following problem
program that takes an Infix mathematical expression as input, and produces its equivalent Postfix expression as a comma separated form.*/

/* C++ implementation to convert infix expression to postfix*/
// Note that here we use std::stack for Stack operations
#include<bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

//Function to return precedence of operators
int prec(char c)
{
	if(c == '^')
	return 3;
	else if(c == '*' || c == '/')
	return 2;
	else if(c == '+' || c == '-')
	return 1;
	else
	return -1;
}

// The main function to convert infix expression
//to postfix expression
void infixToPostfix(string s)
{
	std::stack<char> st;
	st.push('N');
	int l = s.length();
	string ns;
	for(int i = 0; i < l; i++)
	{
		// If the scanned character is an operand, add it to output string.
		if((s[i] >= 'a' && s[i] <= 'z')||(s[i] >= 'A' && s[i] <= 'Z'))
		{ns+=s[i];
		ns+=',';}


		// If the scanned character is an ‘(‘, push it to the stack.
		else if(s[i] == '(')

		st.push('(');

		// If the scanned character is an ‘)’, pop and to output string from the stack
		// until an ‘(‘ is encountered.
		else if(s[i] == ')')
		{
			while(st.top() != 'N' && st.top() != '(')
			{
				char c = st.top();
				st.pop();
			    ns += c;
			    ns+=',';
			}
			if(st.top() == '(')
			{
				char c = st.top();
				st.pop();
			}
		}

		//If an operator is scanned
		else{
			while(
			     st.top() != 'N' &&
			         (
			             ( prec(s[i])!=3 && prec(s[i]) <= prec(st.top()) ) ||
			                  ( prec(s[i])==3 && prec(s[i]) < prec(st.top()) )
			                  )
			                  )
			{
				char c = st.top();
				st.pop();
				ns += c;
				ns+=',';
			}
			st.push(s[i]);
		}

	}
	//Pop all the remaining elements from the stack
	while(st.top() != 'N')
	{
		char c = st.top();
		st.pop();
		ns += c;
		if(st.top() != 'N')
		        ns+=',';
	}

	cout << ns << endl;

}

//Driver program to test above functions
int main()
{
    cout << "Please enter the infix expression that is to be converted to expression" << endl;
	string exp;// = "(a-b)/c-d*e^(f-g)^(p+q)";
	getline(cin, exp);
	infixToPostfix(exp);
	return 0;
}

