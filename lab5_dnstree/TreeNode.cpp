//
//  TreeNode.cpp
//  lab5_dnstree
//
//  Created by 张经纬 on 2017/11/14.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//

#include "TreeNode.h"

// the constructor
TreeNode::TreeNode(DBentry* _entryPtr){
    entryPtr = _entryPtr;
}
// the destructor
TreeNode::~TreeNode(){
    if(entryPtr != NULL)
         delete entryPtr;
}
// the function to set left pointer
void TreeNode::setLeft(TreeNode* newLeft){
    left = newLeft;
}
// the function to set right pointer
void TreeNode::setRight(TreeNode* newRight){
    right = newRight;
}
// the function to get the left pointer
TreeNode* TreeNode::getLeft() const{
    return left;
}
// the function to get the right pointer
TreeNode* TreeNode::getRight() const{
    return right;
}

// the function to get the data entry
DBentry* TreeNode::getEntry() const{
    return entryPtr;
}


