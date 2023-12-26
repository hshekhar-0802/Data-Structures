#include<iostream>
#include"stack_c.h"
#include "node.h"
#include"list.h"
#include<stdexcept>
using namespace std;
Stack_C::Stack_C(){
    try{
        stk=new List();
    }
    catch(std::bad_alloc& e){
        cerr<<"Out of Memory"<<endl;
    }
}

Stack_C::~Stack_C(){
    delete stk;
}

void Stack_C::push(int n){
    stk->insert(n);
}

//Popping from an empty stack
int Stack_C::pop(){
    if(stk->get_size()==0){
        throw std::runtime_error("Empty Stack");
    }
    else{
        int k=stk->delete_tail();
        return k;
    }
    return 0;
}

//Index out of range
int Stack_C::get_element_from_bottom(int n){
    if(n>=stk->get_size() || n<0){
        throw std::runtime_error("Index out of range");
    }
    else{
        Node* nod=stk->get_head();
        for(int i=0;i<=n;i++){
            nod=nod->next;
        }
        int k=nod->get_value();
        return k;
    }
    return 0;
}

//Index out of range
int Stack_C::get_element_from_top(int n){
    n=stk->get_size()-n-1;
    return get_element_from_bottom(n);
}

//Size of the array may be 0
void Stack_C::print_stack(bool top){
    int siz=stk->get_size();
    if(siz==0){
        cout<<endl;
    }
    else if(top==0){
        Node* nod=stk->get_head()->prev;
        for(int i=0;i<siz;i++){
            nod=nod->prev;
            cout<<nod->get_value()<<endl;
        }
    }
    else{
        Node* nod=stk->get_head();
        for(int i=0;i<siz;i++){
            nod=nod->next;
            cout<<nod->get_value()<<endl;
        }
    }
}

List* Stack_C::get_stack(){
    return stk;
}

int Stack_C::get_size(){
    return stk->get_size();
}

//Number of elements less than 2
int Stack_C::add(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    else{
        int a,b,sum;
        a=this->pop();
        b=this->pop();
        sum=a+b;
        this->push(sum);
        return sum;
    }
}

//Number of elements less than 2
int Stack_C::subtract(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    else{
        int a, b, diff;
        a=this->pop();
        b=this->pop();
        diff=b-a;
        this->push(diff);
        return diff;
    }
}

//Number of elements less than 2
int Stack_C::multiply(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    else{
        int a, b, mul;
        a=this->pop();
        b=this->pop();
        mul=a*b;
        this->push(mul);
        return mul;
    }
}

//Number of elements less than 2
//Divide by zero error
int Stack_C::divide(){
    if(stk->get_size()<2){
        throw std::runtime_error("Not Enough Arguments");
    }
    else{
        int a, b, div;
        a=this->pop();
        b=this->pop();
        if(a==0){
            throw std::runtime_error("Divide by Zero Error");
        }
        else if(a*b>=0){
            div=b/a;
            this->push(div);
            return div;
        }
        else{
            float d=b/a-1;
            div=int(d);
            this->push(div);
            return div;
        }
    }
}