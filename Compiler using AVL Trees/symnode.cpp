/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// #include<iostream>
//Write your code below this line

SymNode::SymNode(){
    key="";
    height=0;
}

SymNode::SymNode(string k){
    key=k;
    height=0;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* this_left=this->left;
    SymNode* par_left=this->par->left;
    SymNode* parent=this->par;
    this->par=parent->par;
    this->left=parent;
    parent->par=this;
    parent->right=this_left;
    if(this_left!=NULL){
        this_left->par=parent;
    }
    if(this->par!=NULL){
        if(this->par->key>this->key){
            this->par->left=this;
        }
        else{
            this->par->right=this;
        }
    }
    SymNode* ptr=this->left;
    while (ptr!=NULL)
    {
        int rightheight = -1, leftheight = -1;
        if (ptr->right != NULL)
        {
            rightheight = ptr->right->height;
        }
        if (ptr->left != NULL)
        {
            leftheight = ptr->left->height;
        }
        int max = rightheight;
        if (leftheight > max)
        {
            max = leftheight;
        }
        ptr->height = max+1;
        ptr=ptr->par;
    }
    return this;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* this_right=this->right;
    SymNode* par_right=this->par->right;
    SymNode* parent=this->par;
    this->par=parent->par;
    this->right=parent;
    parent->par=this;
    parent->left=this_right;
    if(this_right!=NULL){
        this_right->par=parent;
    }
    if(this->par!=NULL){
        if(this->par->key>this->key){
            this->par->left=this;
        }
        else{
            this->par->right=this;
        }
    }
    SymNode* ptr=this->right;
    while (ptr!=NULL)
    {
        int rightheight = -1, leftheight = -1;
        if (ptr->right != NULL)
        {
            rightheight = ptr->right->height;
        }
        if (ptr->left != NULL)
        {
            leftheight = ptr->left->height;
        }
        int max = rightheight;
        if (leftheight > max)
        {
            max = leftheight;
        }
        ptr->height = max+1;
        ptr=ptr->par;
    }
    return this;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* node=this->LeftLeftRotation();
    SymNode* node1=node->RightRightRotation();
    return this;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* node=this->RightRightRotation();
    SymNode* node1=this->LeftLeftRotation();
    return this;
}

SymNode::~SymNode(){
    //C++ compiler will take care of this
}

// int main(){
//     SymNode* A=new SymNode("A");
//     SymNode* B=new SymNode("B");
//     SymNode* C=new SymNode("C");
//     C->left=B;
//     B->par=C;
//     A->right=C;
//     C->par=A;
//     SymNode* kk=B->RightLeftRotation();
//     std::cout<<kk->left->height<<endl; 
//     std::cout<<kk->right->height<<endl; 
//     std::cout<<kk->height<<endl; 
//     delete A;
//     delete B;
//     delete C;
//     return 0;
// }

//For RR or LL rotation, the node to be used to call the function is one below the first unbalanced ancestor in the path from root to the newly inserted node.
//For RL or LR rotation, the node to be used to call the function is two below the first unbalanced ancestor in the path from root to the newly inserted node.
//In the destructor of SymTable, use postorder traversal to delete the tree completely.