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

void case_three(Member members[],int members_size, int option){
    int member_choice;
    std::string member_name;
    double payment, bill;

    while (true){
        displayMembers(option);
        std::cout << "\n Case 3 Menu:\n";
        std::cout << "Group Budget Limiter\n";
        std::cout << "1. Add Member.\n";
        std::cout << "2. Add Expense for Member\n";
        std::cout << "3. Exit\n";
        std::cin >> member_choice;

        switch(member_choice){
            case 1:
                //add member logic
            case 2:
                //add expense logic
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid choice. Please select again.\n";
                break;
        }
    }
}

void displayMembers(Member members[],int members_size, int option){
    switch(option)
    case 1:

    case 2:

    case 3:
        std::cout << "Current Members and Their Budgets:\n";
        for (int i = 0; i < members_size; ++i) {
            //std::cout << i + 1 << ". " << members[i].name << ": " << members[i].budget << std::endl;
            //std::cout << std::endl; newline
        }
}


}
void init(){

}

void save(){

}