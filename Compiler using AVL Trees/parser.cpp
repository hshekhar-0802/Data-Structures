/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// #include <iostream>
//Write your code below this line

Parser::Parser(){
    symtable=new SymbolTable();
    last_deleted=-1;
}

ExprTreeNode* buildTree(vector<string>expr, SymbolTable* symtable){
    if(expr.size()==3 && expr[0]!="("){
        ExprTreeNode* leftnode=new ExprTreeNode(expr[0],0);
        ExprTreeNode* node=new ExprTreeNode(expr[1],0);
        ExprTreeNode* rightnode= new ExprTreeNode(expr[2],0);
        node->right=rightnode;
        node->left=leftnode;
        return node;
    }
    else if(expr.size()==1){
        ExprTreeNode* node=new ExprTreeNode(expr[0],0);
        return node;
    }
    else if(expr.size()>0){
        vector<string> expr1, expr2;
        int pos=0,cnt=0;
        for(int i=1;i<expr.size()-1;i++){
            if(expr[i] == "+" || expr[i] == "-" ||expr[i] == "*" ||expr[i] == "/" ){
                if(cnt==0){
                    pos=i;
                    break;
                }
            }
            else if(expr[i]==")"){
                cnt--;
            }
            else if(expr[i]=="("){
                cnt++;
            }
            expr1.push_back(expr[i]);
        }
        for(int i=pos+1;i<expr.size()-1;i++){
            expr2.push_back(expr[i]);
        }
        ExprTreeNode* node=new ExprTreeNode(expr[pos],0);
        node->left=buildTree(expr1,symtable);
        node->right=buildTree(expr2,symtable);
        return node;
    }
    return NULL;
}

void Parser::parse(vector<string> expression){
    vector<string> expr;
    for(int i=2;i<expression.size();i++){
        expr.push_back(expression[i]);
    }
    ExprTreeNode* root=new ExprTreeNode(expression[1],0);
    ExprTreeNode* leftnode=new ExprTreeNode(expression[0],0);
    ExprTreeNode* rightnode=buildTree(expr, symtable);
    root->right=rightnode;
    root->left=leftnode;
    expr_trees.push_back(root);
    if(leftnode->type=="VAR"){
        symtable->insert(leftnode->id);
    }
    else if(leftnode->type=="DEL"){
        last_deleted=symtable->search(rightnode->id);
        // symtable->remove(rightnode->id);
    }
}

void deleteTree(ExprTreeNode* root){
    if(root==NULL){
        return;
    }
    else{
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

Parser::~Parser(){
    delete symtable;
    for(int i=0;i<expr_trees.size();i++){
        deleteTree(expr_trees[i]);
    }
    // expr_trees.clear();
}

// void printTraversal(ExprTreeNode* root){
//     if(root->right!=NULL){
//         printTraversal(root->right);
//     }
//     if(root->left!=NULL){
//         printTraversal(root->left);
//     }
//     cout<<root->type<<endl;
// }

// int main(){
//     vector<string> exp={"a",":=","(","2","+","(","7","*","8",")",")"};
//     Parser* P=new Parser();
//     P->parse(exp);
//     ExprTreeNode* root=P->expr_trees[0];
//     printTraversal(root);
//     delete P;
// }