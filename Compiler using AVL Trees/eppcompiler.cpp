/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// #include <iostream>
//Write your code below this line

EPPCompiler::EPPCompiler(){
    memory_size=0;
    output_file="targCode";
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size=mem_limit;
    output_file=out_file;
    for(int i=0;i<memory_size;i++){
        least_mem_loc.push_heap(i);
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(int i=0; i<code.size();i++){
        // cout<<"Index:"<<i<<endl;
        targ.parse(code[i]);
        if(targ.expr_trees[targ.expr_trees.size()-1]->left->type=="VAR" && targ.symtable->search(code[i][0])!=-2){
            int idx=least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(code[i][0],idx);
        }
        write_to_file(generate_targ_commands());
        if(targ.expr_trees[targ.expr_trees.size()-1]->left->type=="DEL"){
            int idx=targ.symtable->search(code[i][2]);
            targ.symtable->remove(targ.expr_trees[targ.expr_trees.size()-1]->right->id);
            if(idx>=0){
                least_mem_loc.push_heap(idx);
            }
        }
    }
}

void RecursiveGenerate(ExprTreeNode* tree, vector<string>& targCommands, SymbolTable* symtable){
    string s;
    if(tree->right!=NULL){
        RecursiveGenerate(tree->right,targCommands, symtable);
    }
    if(tree->left!=NULL){
        RecursiveGenerate(tree->left, targCommands, symtable);
    }
    if(tree->type=="VAL"){
        s="PUSH "+to_string(tree->num);
    }
    else if(tree->type=="VAR"){
        s="PUSH mem["+to_string(symtable->search(tree->id))+"]";
    }
    else if(tree->type=="ADD"){
        s="ADD";
    }
    else if(tree->type=="SUB"){
        s="SUB";
    }
    else if(tree->type=="MUL"){
        s="MUL";
    }
    else if(tree->type=="DIV"){
        s="DIV";
    }
    targCommands.push_back(s);
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> targCommands;
    ExprTreeNode* tree=targ.expr_trees[targ.expr_trees.size()-1];
    if(tree->type=="EQUALS" && tree->left->type=="VAR"){
        RecursiveGenerate(tree->right,targCommands, targ.symtable);
        int idx=targ.symtable->search(tree->left->id);
        string s="mem["+to_string(idx)+"] = POP";
        targCommands.push_back(s);
    }
    else if(tree->type=="EQUALS" && tree->left->type=="DEL"){
        int idx=targ.symtable->search(tree->right->id);
        string s="DEL = mem["+to_string(idx)+"]";
        targCommands.push_back(s);
    }
    else if(tree->type=="EQUALS" && tree->left->type=="RET"){
        RecursiveGenerate(tree->right,targCommands, targ.symtable);
        string s="RET = POP";
        targCommands.push_back(s);
    }
    return targCommands;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream inFile;
    inFile.open(output_file, ios::app);
    for(int i=0;i<commands.size();i++){
        inFile<<commands[i]<<"\n";
    }
    inFile.close();
}

EPPCompiler::~EPPCompiler(){
    //No pointers created so no deletion required.
}

// int main(){
//     vector<vector<string>> code={{"b",":=","10"},{"a",":=","(","2","+","(","7","*","b",")",")"},{"ret",":=","(","a","+","b",")"}};
//     EPPCompiler EE("output",3);
//     EE.compile(code);
//     // cout<<"Done"<<endl;
// }