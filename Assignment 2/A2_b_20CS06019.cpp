/*
    Created by: Avadhesh chamola
    Roll no: 20CS06019
    M.Tech 1 year
    School of Electrical Science
    IIT Bhubaneswar
*/
/*
This program consist of solution following problem
 Round-Robin Elimination Problem: There are n people standing in a circle.
 In the first step, the counting starts at person 1 and proceeds around the circle,
  and the k-th person is eliminated. Next, the counting starts from the person next
   to the eliminated one, then k-1 people are skipped and the k-th person is eliminated.
The elimination proceeds around the circle until the last person remains, who is the winner. Given n people and a number k, write a C program that outputs the winner.
*/
#include <iostream>
using namespace std;
struct Node {
   int data;
   struct Node *next;
};
struct Node* head = NULL;

void create(int no_of_element){
    struct Node *last = head;
    for(int i=1;i<=no_of_element;i++){
        struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
        newnode->data = i;
        if(head== NULL){
            head=newnode;
        }
        newnode->next = head;
        if(last!= NULL){
            last->next = newnode;
        }
        last=newnode;
    }
}
void display() {
   struct Node* ptr;
   ptr = head;
   do {
      cout<<ptr->data <<" ";
      ptr = ptr->next;
   } while(ptr != head);
}
int Round_Robin_Eliminator(int element,int round_robin_eliminator){
    int y=round_robin_eliminator-2;
    //std::cout << y << std::endl;
    struct Node *cur = head;
    struct Node *forw = cur->next;
    while(element!=1){
        while(y!=0){
            y--;
            cur=forw;
            forw=forw->next;
        }
        cur->next=forw->next;
        element--;
        //std::cout << forw->data << std::endl;
        cur=cur->next;
        forw=cur->next;
        //std::cout << cur->data<<" "<<forw->data << std::endl;
        y=round_robin_eliminator-2;
    }
    return cur->data;
}
int main() {
    int n,k,x;
    std::cout << "Enter no of element" << std::endl;
    std::cin >> n;
    std::cout << "Enter Round Robin Eliminator" << std::endl;
    std::cin >> k;
    create(n);
    cout<<"The list of person is: ";
    display();
    std::cout << std::endl;
    x=Round_Robin_Eliminator(n,k);
    cout<<"The winner is person "<<x;
   return 0;
}



