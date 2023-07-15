#include<stdio.h>
#include<stdlib.h>

struct listnode{
    int data;
    struct listnode* next;
};
struct stack *createstack(){
    return NULL;
};
void push(struct stack **top,int data){
    struct stack *temp;
    temp=malloc(sizeof(struct stack));
    if(!temp){
        return NULL;
    }
    temp->data=data;
    temp->next=*top;
    *top=temp;
}
int isemptystack(struct stack **top){
    return top==NULL;
}
int pop(struct stack **top){
    int data;
    struct stack*temp;
    if(isemptystack(top)){
        return INT_MIN;
    }
    
}