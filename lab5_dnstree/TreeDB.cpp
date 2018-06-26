//
//  TreeDB.cpp
//  lab5_dnstree
//
//  Created by 张经纬 on 2017/11/14.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//


#include "TreeDB.h"
#include <iostream>
TreeDB::TreeDB(){
    
}

TreeDB::~TreeDB(){
    deleteTree(root);
}

void TreeDB::clear(){
    deleteTree(root);
    root = NULL;
    cout << "Success" << endl;
}

void TreeDB::deleteTree(TreeNode* root){
    if(root!=NULL)
    {
        // using recursion
        deleteTree(root->getLeft());
        deleteTree(root->getRight());
        delete(root);
        // set pointers to NULL
        if(root->getLeft()!=NULL)
            root->setLeft(NULL);
        if(root->getRight()!=NULL)
            root->setRight(NULL);
        root=NULL;
    }
}

// the function to print all nodes using recursion
void TreeDB::printAll(TreeNode* printnode) const{
    if (printnode != NULL){
        printAll(printnode->getLeft());
        cout << printnode;
        printAll(printnode->getRight());
    }
}



bool TreeDB::insert(DBentry* newEntry){
    // if exist don't insert
    if (find(newEntry -> getName()) != NULL)
        return false;
    // insert the node
    getInsertPlace(newEntry -> getName(), newEntry);
    
    return true;
}

TreeNode* TreeDB::getInsertPlace(string name, DBentry* newEntry){
    TreeNode* temp = root;
    TreeNode* newnode = new TreeNode(newEntry);
    
    if (root == NULL){
        root = newnode;
        return NULL;
    }
    
    while (temp!=NULL){
        // name insert at left
        if (temp -> getLeft() == NULL && name < temp -> getEntry() ->getName()){
            temp -> setLeft(newnode);
            return NULL;
        }
        // name insert at right
        else if (temp -> getRight() == NULL && name > temp -> getEntry() ->getName()){
            temp -> setRight(newnode);
            return NULL;
        }
        // travel to next node
        else if (temp -> getRight() != NULL && name > temp -> getEntry() ->getName()){
            temp = temp -> getRight();
        }
        else if (temp -> getLeft() != NULL && name < temp -> getEntry() ->getName()){
            temp = temp -> getLeft();
        }
            
        
            }
    return NULL;
}





DBentry* TreeDB::find(string name){
    probesCount = 0;
    TreeNode* temp = root;
    while (temp != NULL){
        probesCount ++;
        if (name == temp -> getEntry() -> getName())
            return temp -> getEntry();
        if (name < temp -> getEntry() -> getName())
            temp = temp -> getLeft();
        else if (name > temp -> getEntry() -> getName())
            temp = temp ->getRight();
    }
    return NULL;
}
// The overload operator to print all nodes
ostream& operator<< (ostream& out, const TreeDB & rhs){
    rhs.printAll(rhs.root);
    return out;
}
// The overload operator to print all nodes
ostream& operator<< (ostream& out, TreeNode* rhs){
    out << *(rhs -> getEntry());
    return out;
}

// The function to call the private count active function
void TreeDB::countActive () const{
    int count = 0;
    cout << countAct(root, count) << endl;
}

// The private function to actually count the active node using recursion
int TreeDB::countAct(const TreeNode* node, int &count) const{
    if (node == NULL)
        return count;
    countAct(node-> getLeft(),count);
    if(node -> getEntry() -> getActive())
        count ++;
    countAct(node->getRight(), count);
    
    return count;
}

// The function to call the probe count function
void TreeDB::printProbes() const{
    cout << probesCount << endl;
    
}

// the function to remove a node by a given name
bool TreeDB::remove(string name){
    TreeNode* temp = root;
    TreeNode* beforetemp = root;
    int direction = 0;
    // get the position at and before the deleting node
    while (temp != NULL){
        
        if (name == temp -> getEntry() -> getName()){
            break;
        }
        beforetemp = temp;
        // remember the direction of the deleting node connected at the node before
        if (name < temp -> getEntry() -> getName()){
            direction = 0;
            temp = temp -> getLeft();
        }
        else if (name > temp -> getEntry() -> getName()){
            temp = temp ->getRight();
            direction = 1;
        }
        
    }
    // if node not found, do nothing
    if (temp == NULL)
        return false;
    
    // if the node is the root and both its left and right are empty
    if (temp == root && temp ->getRight() ==NULL && temp -> getLeft() == NULL){
        delete root;
        root = NULL;
    }
    // if node is root and both direction are not empty
    else if (temp == root && (temp ->getRight() !=NULL || temp -> getLeft() != NULL)){
        TreeNode* replacement = temp -> getLeft();
        TreeNode* beforereplacement = temp;
        bool firstLeft = true;
        // Get the largest node on its left
        if(replacement == NULL){
            root = temp -> getRight();
            delete temp;
            return true;
        }
        
        while (true){
            // find the largest node
            if (replacement -> getRight() == NULL)
                break;
            firstLeft = true;
            beforereplacement = replacement;
            replacement = replacement -> getRight();
        }
        
            // if the replacement is not the first left node
            if (!firstLeft)
               replacement -> setLeft(temp -> getLeft());
        
            replacement -> setRight(temp -> getRight());
            root = replacement;
            delete temp;
    }
    
    
    
    
    // if it has no leaf
    else if (temp ->getRight() ==NULL && temp -> getLeft() == NULL){
        if (direction == 0)
            beforetemp -> setLeft(NULL);
        else beforetemp -> setRight(NULL);
        delete temp;
    }
    // has two leaves
    else if (temp -> getRight() != NULL && temp -> getLeft() != NULL){
        TreeNode* replacement = temp -> getLeft();
        TreeNode* beforereplacement = temp;
        bool firstLeft = true;
        while (true){
            
            if (replacement -> getRight() == NULL)
                break;
            firstLeft = false;
            beforereplacement = replacement;
            replacement = replacement -> getRight();
        }
        
        
        
        
        
        // if the replacement is not the first left node
        if (!firstLeft){
            if (replacement -> getLeft() == NULL){
                beforereplacement -> setRight(NULL);}
            else beforereplacement -> setRight(replacement -> getLeft());
            replacement -> setLeft(temp -> getLeft());
        }
        replacement -> setRight(temp -> getRight());
        if (direction == 0)
            beforetemp -> setLeft(replacement);
        else beforetemp -> setRight(replacement);
        
        
        delete temp;

    }
    // if the node to be deleted has no left leaf
    else if (temp -> getLeft() == NULL){
        if (temp == root){
            root = temp -> getRight();
            delete temp;
            return true;
        }
        
        if (direction == 0)
            beforetemp -> setLeft(temp -> getRight());
        else beforetemp -> setRight(temp -> getRight());
        
        delete temp;
        
    }
    
    
    return true;
}






