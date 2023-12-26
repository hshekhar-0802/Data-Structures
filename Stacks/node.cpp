#include<iostream>
#include"node.h"
#include<stdexcept>
using namespace std;
Node::Node(bool sentinel){
    this->is_sentinel=true;
    this->prev=nullptr;
    this->next=nullptr;
}

Node::Node(int v, Node* nxt, Node* prv){
    this->value=v;
    this->is_sentinel=false;
    this->prev=prv;
    this->next=nxt;
}

bool Node::is_sentinel_node(){
    return this->is_sentinel;
}

int Node::get_value(){
    return this->value;
}