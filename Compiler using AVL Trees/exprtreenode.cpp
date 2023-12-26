/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="EQUALS";
}

ExprTreeNode::ExprTreeNode(string t,int v){
    if(t==":="){
        type="EQUALS";
    }
    else if(t=="+"){
        type="ADD";
    }
    else if(t=="-"){
        type="SUB";
    }
    else if(t=="*"){
        type="MUL";
    }
    else if(t=="/"){
        type="DIV";
    }
    else if(t=="ret"){
        type="RET";
    }
    else if(t=="del"){
        type="DEL";
    }
    else if((t[0]=='-' && t.length()>1) || (t[0]>=48 && t[0]<=57)){
        type="VAL";
        if(t[0]=='-'){
            t=t.substr(1,t.length()-1);
            num=stoi(t);
            num*=-1;
        }
        else{
            num=stoi(t);
        }
    }
    else{
        type="VAR";
        id=t;
    }
}

ExprTreeNode::~ExprTreeNode(){
    //C++ compiler will take care of this.
}

