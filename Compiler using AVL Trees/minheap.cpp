/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// #include <iostream>
//Write your code below this line

MinHeap::MinHeap(){
    //Already defined in the .h file
}

void MinHeap::push_heap(int num){
    if(size==0){
        size=1;
        root=new HeapNode(num);
        // cout<<"Root node inserted"<<endl;
    }
    else{
        size++;
        int k=size;
        int cnt=0;
        string s="";
        while(k>1){
            s+=to_string(k%2);
            k=k/2;
        }
        // cout<<"String s is :"<<s<<endl;
        HeapNode* ptr=root;
        for(int i=s.length()-1;i>0;i--){
            if(s[i]=='1'){
                ptr=ptr->right;
            }
            else{
                ptr=ptr->left;
            }
        }
        if(s[0]=='1'){
            ptr->right=new HeapNode(num);
            ptr->right->par=ptr;
            ptr=ptr->right;
            // cout<<ptr->val<<" inserted at right with parent "<<ptr->par->val<<endl;
        }
        else{
            ptr->left=new HeapNode(num);
            ptr->left->par=ptr;
            ptr=ptr->left;
            // cout<<ptr->val<<" inserted at left with parent "<<ptr->par->val<<endl;
        }
        //Heapify up
        while(ptr->par!=NULL){
            if(ptr->par->val>ptr->val){
                int a=ptr->val;
                int b=ptr->par->val;
                ptr->par->val=a;
                ptr->val=b;
                ptr=ptr->par;
            }
            else{
                break;
            }
        }
        if(ptr->par==NULL){
            root=ptr;
        }
    }
}

int MinHeap::get_min(){
    if(root==NULL){
        return -1;
    }
    return root->val;
}

void HeapifyDown(HeapNode* root){
    if(root==NULL){
        return;
    }
    HeapNode* smallest=root;
    if(root->left!=NULL && root->left->val<smallest->val){
        smallest=root->left;
    }
    if(root->right!=NULL && root->right->val<smallest->val){
        smallest=root->right;
    }
    if(smallest->val!=root->val){
        int a=root->val;
        int b=smallest->val;
        root->val=b;
        smallest->val=a;
        HeapifyDown(smallest);
    }
}

void MinHeap::pop(){
    if(size==1){
        delete root;
        size--;
        root=NULL;
    }
    else if(size>1){
        //Find the last node
        int k=size;
        int cnt=0;
        string s="";
        while(k>1){
            s+=to_string(k%2);
            k=k/2;
        }
        HeapNode* ptr=root;
        for(int i=s.length()-1;i>=0;i--){
            if(s[i]=='1'){
                ptr=ptr->right;
            }
            else{
                ptr=ptr->left;
            }
        }
        // cout<<"Found the last node with value "<<ptr->val<<endl;
        //Copying value to the root
        root->val=ptr->val;
        //Deleting the last node
        if(s[0]=='0'){
            ptr->par->left=NULL;
        }
        else{
            ptr->par->right=NULL;
        }
        delete ptr;
        ptr=NULL;
        //Heapify down
        HeapifyDown(root);
        size--;
    }
}

void deleteHeap(HeapNode* root){
    if(root==NULL){
        return;
    }
    else{
        deleteHeap(root->left);
        deleteHeap(root->right);
        // cout<<"Deleting root with value "<<root->val<<endl;
        delete root;
    }
}

MinHeap::~MinHeap(){
    deleteHeap(root);
}

// int main(){
//     MinHeap* heap= new MinHeap();
//     heap->push_heap(10);
//     heap->push_heap(13);
//     heap->push_heap(11);
//     heap->push_heap(19);
//     heap->push_heap(22);
//     heap->push_heap(16);
//     heap->push_heap(17);
//     heap->push_heap(23);
//     heap->push_heap(125);
//     heap->push_heap(12);
//     heap->pop();
//     std::cout<<heap->root->right->right->val<<endl;
//     delete heap;
// }
//size aur root attributes ko wapas private me daalna hai