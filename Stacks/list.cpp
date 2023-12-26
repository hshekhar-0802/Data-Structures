#include<iostream>
#include"node.h"
#include"list.h"
#include<stdexcept>
using namespace std;
List::List(){
    size=0;
    try{
        sentinel_head=new Node();
        sentinel_tail=new Node();
        sentinel_head->next=sentinel_tail;
        sentinel_tail->prev=sentinel_head;
        sentinel_head->prev=sentinel_tail;
    }
    catch(const std::bad_alloc& e){
        cerr<<"Out of Memory"<<endl;
    }
}

List::~List(){
    delete sentinel_head;
    delete sentinel_tail;
}

void List::insert(int v){
    try{
        Node* n=new Node(v,sentinel_tail,sentinel_tail->prev);
        sentinel_tail->prev->next=n;;
        sentinel_tail->prev=n;
        size++;
    }
    catch(const std::bad_alloc& e){
        cerr<<"Out of Memory"<<endl;
    }
}

int List::get_size(){
    return size;
}

Node* List::get_head(){
    return sentinel_head;
}

int List::delete_tail(){
    if(size>=1){
        int k=sentinel_tail->prev->get_value();
        Node* n=sentinel_tail->prev;
        n->prev->next=sentinel_tail;
        sentinel_tail->prev=n->prev;
        delete n;
        size--;
        return k;
    }
    else{
        return -1;
    }
}