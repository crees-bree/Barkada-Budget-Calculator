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
void caseMenu();
void case_oneMenu();


void case_one(int *members_size, Member *members);
void case_two();
void case_three();

void case_oneMenu();

// reading and writing functions

void init();
void save();

void group_mode(){
    Member members[20];
    int members_size = 0;               //I deleted members_size cin cos you can just ++ from create members to get total size
                                    
    int option;
    caseMenu();
    std::cin>> option;
    
    switch (option)
    {
    case 1:
        case_one(&members_size, members);
        break;
    
    default:
        break;
    }


    
}

void case_one(int *members_size, Member *members){
    int caseOneTask;
    case_oneMenu();
    std::cin >> caseOneTask;
    switch (caseOneTask)
    {
    case 1:
        members[*members_size].create_member();
        break;
    
    default:
        break;
    }
}


void case_oneMenu(){
    std::cout << "\n Case 1 Menu:" << std::endl;
    std::cout << "Group Budget Limiter" << std::endl;
    std::cout << "1. Add a new member" << std::endl;
    std::cout << "2. Edit a member" << std::endl;
    std::cout << "3. Delete a member" << std::endl;
    std::cout << "4. Display all member details" << std::endl;
}

void caseMenu(){
    std::cout << "\n Case Menu:" << std::endl;
    std::cout << "Case 1" << std::endl;             //maybe rename these into better describing unsa iya buhaton, case 1-3 lang sa cos i cant think
    std::cout << "Case 2" << std::endl;
    std::cout << "Case 3" << std::endl;
}



void case_two();
void case_three(){
    std::vector<Member> members;
    int member_choice;
    std::string member_name;

    while (true){
        std::cout << "\n Case 3 Menu:\n";
        std::cout << "Group Budget Limiter\n";
        std::cout << "1. Add Member.\n";
        std::cout << "2. Display All Member Budgets.\n";
        std::cout << "3. Add Expense for Member\n";
        std::cout << "4. Exit\n";
    }
}

void init(){

}

void save(){

}