// contains all functionalities for group mode

#include <iostream>
#include <errno.h>
#include <fstream>

#include "member.h"

// init
// save
//members array, size, limit to 20 members

// group

// menu for case 1, case 2, case 3, and default
//case 1: split the change


#define MODE 'g'

// cases menus

void case_one();
void case_two();
void case_three();

// reading and writing functions

void init();
void save();

void group_mode(){
    Member members[20];
    int members_size = 0;
    std::cout<< "How many members are in your group?: "<< std::endl;
    std::cin>> members_size;

    int option;

    
}

void case_one(){
    

}
void case_two();
void case_three(){
    std::vector<Member> members;
    int member_choice;
    std:string member_name;

    while (true){
        std::cout << "\n Case 3 Menu:\n";
        std::cout << "Group Budget Limiter\n";
        std::cout << "1. Add Member.\n";
        std::cout << "2. Display All Member Budgets.\n";
        std::cout << "3. Add Expense for Member\n";
        std::cout << "4. Exit\n";
        std::cin >> member_choice;

        switch(member_choice){
            case 1:
                //add members code will also ask for initial budget
            case 2:
                //add expense logic
                break;
            case 3:
                displayAllMembers(); //function to display all members with their budgets undefined pa FOR NOW
            case 4:
                return;
            default:
                std::cout << "Invalid choice. Please select again.\n";
                break;
        }
    }
}

void init(){

}

void save(){

}