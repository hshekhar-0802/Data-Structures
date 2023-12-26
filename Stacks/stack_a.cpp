#include"stack_a.h"
#include<iostream>
#include<stdexcept>
using namespace std;

Stack_A::Stack_A(){
    size=0;
}

//Pushing to a full stack
void Stack_A::push(int n){
        if(size>=1024){
            throw std::runtime_error("Stack Full");
        }
        else{
            stk[size]=n;
            size++;
        }
}

//Popping from an empty stack
int Stack_A::pop(){
    if(size==0){
        throw std::runtime_error("Empty Stack");
    }
    else{
        size--;
        return stk[size];
    }
}

//Index out of range
int Stack_A::get_element_from_bottom(int n){
    if(n>=size || n<0){
        throw std::runtime_error("Index out of range");
    }
    else{
        return stk[n];
    }
}

//Index out of range
int Stack_A::get_element_from_top(int n){
    if(n>=size || n<0){
        throw std::runtime_error("Index out of range");
    }
    else{
        return stk[size-1-n];
    }
}

//Size of the stack may be 0
void Stack_A::print_stack(bool top){
    if(size==0){
        cout<<endl;
    }
    else if(top==0){
        for(int i=size-1;i>=0;i++){
            cout<<stk[i]<<endl;
        }
    }
    else{
        for(int i=0;i<size;i++){
            cout<<stk[i]<<endl;
        }
    }
}

int* Stack_A::get_stack(){
    int* ptr= &stk[0];
    return ptr;
}

int Stack_A::get_size(){
    return size;
}

//Number of elements less than 2
int Stack_A::add(){
    if(size<2){
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
int Stack_A::subtract(){
    if(size<2){
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
int Stack_A::multiply(){
    if(size<2){
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
int Stack_A::divide(){
    if(size<2){
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