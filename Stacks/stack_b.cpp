#include<iostream>
#include"stack_b.h"
#include<stdexcept>
using namespace std;

Stack_B::Stack_B(){
    size=0;
    capacity=1;
    stk=new int[1];
}

Stack_B::~Stack_B(){
    delete stk;
}

//Pushing to a full stack
//new operator failure
void Stack_B::push(int n){
    try{
        if(size==capacity){
            int* arr=new int[2*capacity];
            for(int i=0;i<capacity;i++){
                arr[i]=*(stk+i);
            }
            arr[size]=n;
            size++;
            delete stk;
            stk=arr;
            capacity=2*capacity;
        }
        else{
            stk[size]=n;
            size++;
        }
    }
    catch(const std::bad_alloc& e){
        cerr<<"Out of Memory"<<endl;
    }
}

//Popping from an empty stack
//Reducing the size of the stack
//new operator failure
int Stack_B::pop(){
    if(size==0){
        throw std::runtime_error("Empty Stack");
    }
    else if(size==1){
        int k= stk[0];
        size--;
        capacity=1;
        return k;
    }
    else if(size>1){
        try{
            int k=stk[size-1];
            if((capacity-size+1)>capacity/4){
                int* arr=new int[size-1];
                for(int i=0;i<size-1;i++){
                    arr[i]=*(stk+i);
                }
                delete stk;
                stk=arr;
                size--;
                capacity=size;
                return k;
            }
            else{
                size--;
                return k;
            }
        }
        catch(const std::bad_alloc& e){
            cerr<<"Out of Memory"<<endl;
        }
    }
    return 0;
}

//Index out of range
int Stack_B::get_element_from_bottom(int n){
    if(n>=size || n<0){
        throw std::runtime_error("Index out of range");
    }
    else{
        return stk[n];
    }
}

//Index out of range
int Stack_B::get_element_from_top(int n){
    if(n>=size || n<0){
        throw std::runtime_error("Index out of range");
    }
    else{
        return stk[size-1-n];
    }
}

//Size of the stack may be 0
void Stack_B::print_stack(bool top){
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

int* Stack_B::get_stack(){
    return stk;
}

int Stack_B::get_size(){
    return size;
}

//Number of elements less than 2
int Stack_B::add(){
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
int Stack_B::subtract(){
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
int Stack_B::multiply(){
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
int Stack_B::divide(){
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