#include <iostream>
using namespace std;


typedef struct node_{
    int val;
    struct node_* next;
}node;

int removeLastN(node* head, int n ){
    if (n <=0) return 0;
    node* p1 = head;
    node *p2 = head;
    for (int i =0;i<n+1;i++){
        p2 = p2->next;
        cout << "out of range" << endl;
        if(!p2) return -1;
    }
    while(p2){
        p1 = p1->next;
        p2 = p2->next;
    }
    p1->next = p1->next->next;
};

int main(){
    return 0;
}