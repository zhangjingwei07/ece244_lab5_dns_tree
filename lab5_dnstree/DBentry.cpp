//
//  DBentry.cpp
//  lab5_dnstree
//
//  Created by 张经纬 on 2017/11/14.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//


#include "DBentry.h"
#include <iostream>

// default constructor and destructor

DBentry::DBentry(){

}

DBentry::~DBentry(){
}

// the constructor with info
DBentry::DBentry(string _name, unsigned int _IPaddress, bool _active){
    name = _name;
    IPaddress = _IPaddress;
    active = _active;
}
// set the name
void DBentry::setName(string _name){
    name = _name;
}
// set the ip address of the node
void DBentry::setIPaddress(unsigned int _IPaddress){
    IPaddress = _IPaddress;
}
// set the status of the node
void DBentry::setActive (bool _active){
    active = _active;
}
// function to get the name of the node
string DBentry::getName() const{
    return name;
}
// function to get the IP of the node
unsigned int DBentry::getIPaddress() const{
    return IPaddress;
}
// funcition to get the status of the node
bool DBentry::getActive() const{
    return active;
}

// The overload operator to print all nodes
ostream& operator<< (ostream& out, const DBentry& rhs){
    out << rhs.name << " : " << rhs.IPaddress<< " : ";
    if (rhs.active)
        out << "active" << endl;
    else out << "inactive" << endl;
    
    return out;
}







