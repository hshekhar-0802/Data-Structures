/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>
// Write your code below this line

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

SymNode* getNode(SymNode* root,string k){
    SymNode* ptr=root;
    while(ptr!=NULL){
        if(k>ptr->key){
            ptr=ptr->right;
        }
        else if(k<ptr->key){
            ptr=ptr->left;
        }
        else{
            return ptr;
        }
    }
    return NULL;
}

SymNode* getSucc(SymNode* node){
    while(node->left!=NULL){
        node=node->left;
    }
    return node;
}

void SymbolTable::insert(string k)
{
    // Finding where to insert
    if(size==0){
        root=new SymNode(k);
        size=1;
        return;
    }
    SymNode *ptr = root;
    while (ptr != NULL)
    {
        if (k > ptr->key)
        {
            if(ptr->right==NULL){
                break;
            }
            ptr = ptr->right;
        }
        else if (ptr->key > k)
        {
            if(ptr->left==NULL){
                break;
            }
            ptr = ptr->left;
        }
        else{
            return;
        }
    }
    // Creating new node and inserting
    SymNode *node = new SymNode(k);
    if (k > ptr->key)
    {
        ptr->right = node;
        node->par = ptr;
        size++;
    }
    else if (k < ptr->key)
    {
        ptr->left = node;
        node->par = ptr;
        size++;
    }
    // Updating height
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
    //Finding imbalance
    ptr=node->par;
    int balance=0;
    while(ptr!=NULL){
        int leftheight=-1, rightheight=-1;
        if (ptr->right != NULL)
        {
            rightheight = ptr->right->height;
        }
        if (ptr->left != NULL)
        {
            leftheight = ptr->left->height;
        }
        balance=leftheight-rightheight;
        if(balance>1 || balance<-1){
            break;
        }
        ptr=ptr->par;
    }
    //Applying rotations
    if(balance>1 && k<ptr->left->key){
        SymNode* testnode=ptr->left->RightRightRotation();
    }
    else if(balance>1 && k>ptr->left->key){
        SymNode* testnode=ptr->left->right->LeftRightRotation();
    }
    else if(balance<-1 && k>ptr->right->key){
        SymNode* testnode=ptr->right->LeftLeftRotation();
    }
    else if(balance<-1 && k<ptr->right->key){
        SymNode* testnode=ptr->right->left->RightLeftRotation();
    }
    //Updating the root of the tree
    ptr=node;
    while(ptr->par!=NULL){
        ptr=ptr->par;
    }
    root=ptr;
}

int getBalance(SymNode* node){
    if(node==NULL){
        return 0;
    }
    int leftheight=-1;
    int rightheight=-1;
    if(node->left!=NULL){
        leftheight=node->left->height;
    }
    if(node->right!=NULL){
        rightheight=node->right->height;
    }
    return leftheight-rightheight;
}

SymNode* deleteNode(SymNode* root, string k){
    if(root==NULL){
        return root;
    }
    if(k<root->key){
        root->left=deleteNode(root->left,k);
    }
    else if(k>root->key){
        root->right=deleteNode(root->right,k);
    }
    else{
        if(root->left==NULL || root->right==NULL){
            SymNode* temp=root->left;
            if(temp==NULL){
                temp=root->right;
            }
            if(temp==NULL){
                temp=root;
                free(temp);
                root=NULL;
            }
            else{
                root->left=temp->left;
                root->right=temp->right;
                root->key=temp->key;
                root->height=temp->height;
                root->address=temp->address;
                free(temp);
            }
        }
        else{
            SymNode*temp=getSucc(root->right);
            root->key=temp->key;
            root->address=temp->address;
            root->right=deleteNode(root->right,temp->key);
        }
    }
    if(root==NULL){
        return root;
    }
    int leftheight=-1;
    int rightheight=-1;
    if(root->left!=NULL){
        leftheight=root->left->height;
    }
    if(root->right!=NULL){
        rightheight=root->right->height;
    }
    int max=leftheight;
    if(max<rightheight){
        max=rightheight;
    }
    root->height=max+1;
    int balance=getBalance(root);
    if(balance>1 && getBalance(root->left)>=0){
        return root->left->RightRightRotation();
    }
    if(balance>1 && getBalance(root->left)<0){
        return root->left->right->LeftRightRotation();
    }
    if(balance<-1 && getBalance(root->right)<=0){
        return root->right->LeftLeftRotation();
    }
    if(balance<-1 && getBalance(root->right)>0){
        return root->right->left->RightLeftRotation();
    }
    return root;
}

bool doesExist(SymNode* root,string k){
    while(root!=NULL){
        if(root->key<k){
            root=root->right;
        }
        else if(root->key>k){
            root=root->left;
        }
        else{
            return true;
        }
    }
    return false;
}

void SymbolTable::remove(string k)
{
    if(doesExist(root,k)){
        size--;
        root=deleteNode(root,k);
    }
}

int SymbolTable::search(string k)
{
    SymNode* ptr=root;
    while(ptr!=NULL){
        if(ptr->key<k){
            ptr=ptr->right;
        }
        else if(ptr->key>k){
            ptr=ptr->left;
        }
        else{
            return ptr->address;
        }
    }
    return -2;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode* ptr=root;
    while(ptr!=NULL){
        if(ptr->key<k){
            ptr=ptr->right;
        }
        else if(ptr->key>k){
            ptr=ptr->left;
        }
        else{
            ptr->address=idx;
            return;
        }
    }
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

void destructor(SymNode* root){
    if(root->left!=NULL){
        destructor(root->left);
    }
    if(root->right!=NULL){
        destructor(root->right);
    }
    delete root;
}

SymbolTable::~SymbolTable()
{
    if(root!=NULL){
        destructor(root);
    }
}

// int main(){
//     SymbolTable* table=new SymbolTable();
//     table->insert("9");
//     table->insert("5");
//     table->insert("4");
//     table->insert("7");
//     table->insert("6");
//     table->insert("1");
//     table->insert("8");
//     table->insert("2");
//     table->insert("3");
//     table->remove("3");
//     table->remove("9");
//     table->remove("5");
//     table->remove("4");
//     table->remove("7");
//     table->remove("6");
//     table->remove("1");
//     table->remove("8");
//     table->remove("2");
//     std::cout<<table->get_size()<<endl;
//     delete table;
// }