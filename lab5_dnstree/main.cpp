//
//  main.cpp
//  lab5_dnstree
//
//  Created by Jingwei Zhang on 2017/11/14.
//  Copyright © 2017年 Jingwei Zhang. All rights reserved.
//  Xcode 9.1 Beta Apple Inc.

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "TreeDB.h"
#include "TreeNode.h"
#include "DBentry.h"
using namespace std;

// Declare the function used
void Parser(TreeDB dns);
void printNode (string name, DBentry* printnode);

// The main function
int main(int argc, const char * argv[]) {
    
    // Create the tree root
    TreeDB dns;
    // The Parser function
    Parser(dns);
    return 0;
}


void Parser(TreeDB dns) {
    // Setup variables
    string line, command;
    
   
    bool endloop = false;

    
    getline (cin, line);  // Get a line from standard input
    cout << "> ";
    while ( !cin.eof () ) {
        // Put the line in a stringstream for parsing
        
        string test_space;
        stringstream lineStream (line);
        lineStream >> command;
        // insert a resistor
        if (command == "insert") {
            // Create a loop for break
            string name;
            unsigned int IP;
            string status;
            bool active;
            DBentry* newdb = NULL;
            
            while (!endloop){
                lineStream >> name;
                lineStream >> IP;
                lineStream >> status;
                // translate the string into a bool status
                if (status == "active")
                    active = true;
                else active = false;
                // create a new entry node
                newdb = new DBentry(name, IP, active);
                // check whether the entry already exists
                if(!dns.insert(newdb)){
                    delete newdb;
                    cout << "Error: entry already exists" << endl;
                }
                else cout << "Success" << endl;
                
                endloop = true;
            }
        }
        
        // to modify the value of an existing R
        else if (command == "find" ) {
            // Create a loop for break
            while (!endloop){
                string name;
                lineStream >> name;
                DBentry* printnode = dns.find(name);
                if (printnode == NULL){
                    cout << "Error: entry does not exist" << endl;
                    break;
                }
                printNode(name, printnode);
                
                
                endloop = true;
            }
        }
        
        
        // print r
        else if(command == "printall"){
            // Create while loop for using break
            while(endloop != true){
                cout << dns;
                endloop = true;
            }
        }
        
        
        // print node
        else if(command == "countactive"){
            // Create while loop for using break
            while(endloop != true){
                dns.countActive();
                endloop = true;
            }
        }
        
        
        // delete resistor
        else if(command== "updatestatus"){
            string name;
            string status;
            bool active = false;
            while(endloop != true){
                lineStream >> name;
                // Check whether the entry exists
                DBentry* temp = dns.find(name);
                if (temp == NULL){
                    cout << "Error: entry does not exist" << endl;
                    break;
                }
                // Translate string into bool
                lineStream >> status;
                if (status == "active")
                    active = true;
                
                // set the status of the node
                temp -> setActive(active);
                cout << "Success" << endl;
                endloop = true;
            }
        }
        
        else if(command == "printprobes"){
            string name;
            lineStream >> name;
            // Create while loop for using break
            while(endloop != true){
                // check the existence of the name
                if (dns.find(name) == NULL){
                    cout << "Error: entry does not exist" << endl;
                    break;
                }
                else dns.printProbes();
                endloop = true;
            }
        }
        
        
        else if(command == "remove"){
            string name;
            lineStream >> name;
            
            // Create while loop for using break
            while(endloop != true){
                // remove and check existence
                if(dns.remove(name))
                    cout << "Success" << endl;
                else cout << "Error: entry does not exist" << endl;
                
                
                endloop = true;
            }
        }
        else if(command == "removeall"){
            // Create while loop for using break
            while(endloop != true){
                dns.clear();
                endloop = true;
            }
        }
        
        // If the command is invalid
        else{
            cout << "Error: invalid command"<< endl;
        }
        
        // Get new command
        getline (cin, line);
        endloop = false;
        cout << "> ";
    }  // End input loop until EOF.
    
}

// the function to peint a certain node
void printNode (string name, DBentry *printnode){
    cout << printnode -> getName() << " : " << printnode  -> getIPaddress() <<
    " : ";
    // tanslate the bool status into string
    if (printnode -> getActive() == true)
        cout << "active" << endl;
    else cout << "inactive" << endl;
    
}



