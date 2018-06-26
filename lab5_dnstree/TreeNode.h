#pragma once
#include "DBentry.h"

#include <cstdio>

class TreeNode {
private:
    DBentry* entryPtr = NULL;
    TreeNode* left = NULL;
    TreeNode* right = NULL;
    
public:
    // A useful constructor
    TreeNode(DBentry* _entryPtr);
    
    // the destructor
    ~TreeNode();

    // sets the left child of the TreeNode.
    void setLeft(TreeNode* newLeft);

    // sets the right child of the TreeNode
    void setRight(TreeNode* newRight);

    // gets the left child of the TreeNode.
    TreeNode* getLeft() const;

    // gets the right child of the TreeNode
    TreeNode* getRight() const;

    // returns a pointer to the DBentry the TreeNode contains. 
    DBentry* getEntry() const;
};



