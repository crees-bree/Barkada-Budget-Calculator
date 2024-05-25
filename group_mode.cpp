// contains all functionalities for group mode

#include <iostream>
#include <errno.h>
#include <fstream>

#include "member.h"

#define MODE 'g'


// CASES MENU PROMPTS


// menu prompt for cases selection
void caseMenu();

// case one menu prompt
void case_oneMenu();

void edit_memberMenu();


// CASES MENU FUNCTIONS


// contains all functionalities for case 1
void case_one(int *members_size, Member *members);
void edit_member(int members_size, Member *members);

// contains all functionalities for case 2
void case_two();

// contains all functionalities for case 3
void case_three();


// AUXILIARY FUNCTIONS

// READING AND WRITING FUNCTIONS

void init();
void save();

// contains functionalities for group mode
void group_mode(){
    Member members[20];
    int members_size = 0;               //I deleted members_size cin cos you can just ++ from create members to get total size
                                    
    int option;

    // display cases selection menu prompt
    caseMenu();

    std::cin >> option;
    
    switch (option)
    {
    case 1:
        case_one(&members_size, members);
        break;
    
    default:
        std::cout << "Invalid input" << std::endl;
        break;
    }
}

void case_one(int *members_size, Member *members){
    int caseOneTask;

    // prompt menu
    case_oneMenu();

    std::cin >> caseOneTask;

    switch (caseOneTask)
    {
    case 1:{
        members[*members_size].create_member();
        members[*members_size].initialize(1);

        char verify;
        std::cout << "Are you sure you've entered the correct information? Enter Y if yes:" << std::endl;
        std::cin >> verify;

        do{
            members[*members_size].create_member();
            members[*members_size].initialize(1);   
        }while(verify != 'Y' && verify != 'y');
        
        (*members_size)++;
        break;
    }
    
    case 2: {
        edit_member(*members_size, members);
        break;
    }
    
    case 3:
        break;
    
    case 4:
        members[*members_size].display_details(1, *members_size);
        break;

    case 5: return;

    default:
        break;
    }
}


void case_oneMenu(){
    // - chan
    // group budget limiter lagi ni
    std::cout << "\n Case 1 Menu:" << std::endl;
    std::cout << "Group Budget Limiter" << std::endl;
    std::cout << "1. Add a new member" << std::endl;
    std::cout << "2. Edit a member" << std::endl;
    std::cout << "3. Delete a member" << std::endl;
    std::cout << "4. Display all member details" << std::endl;
    std::cout << "5. Exit" << std::endl;
    // add sad option para maka exit ang user
    // done -conx
}

void caseMenu(){
    // - chan
    // sa ato-ato ra nang case 1-3 sht
    // ato idisplay sa user ang name sa case
    // awa daw if goods ra ang suggested names below
    std::cout << "\n Case Menu:\n" << std::endl;
    std::cout << "1) Sukli sa Kinsa" << std::endl;             //maybe rename these into better describing unsa iya buhaton, case 1-3 lang sa cos i cant think
    std::cout << "2) Utang Tracker" << std::endl;
    std::cout << "3) Gasto Mo Ang Limit" << std::endl;
    // add sad option para maka exit ang user
}

void edit_memberMenu(){
    std::cout << "What do you want to edit?: " << std::endl;
    std::cout << "1. Name: " << std::endl;
    std::cout << "2. Bill: " << std::endl;
    std::cout << "3. Expense:  " << std::endl;
    std::cout << "4. Exit" << std::endl;
}


void case_two();

void case_three(Member *members, int *members_size, int option) {
    int member_choice;
    std::string name;
    double payment, bill;

    while (true) {
        members[*members_size].display_details(option, *members_size);
        std::cout << "\nCase 3 Menu:\n";
        std::cout << "Gasto Mo Ang Limit!\n";
        std::cout << "1. Add Member.\n";
        std::cout << "2. Add Expense for Member\n";
        std::cout << "3. Exit\n";
        std::cin >> member_choice;

        switch (member_choice) {
            case 1:
                members[*members_size].create_member();
                members[*members_size].initialize(3);

                char verify;
                    do{
                    std::cout << "Are you sure you've entered the correct information? Enter Y if yes: ";
                    std::cin >> verify;
                        members[*members_size].create_member();
                        members[*members_size].initialize(3);   
                    }while(verify != 'Y' && verify != 'y'); 

                (*members_size)++;

                break;
            case 2:
                // Add expense logic
                break;
            case 3:
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

void edit_member(int members_size, Member *members){
    std::string editName;
    int editCase;
    std::cout << "What is the name of the member you wish to edit?: " << std::endl;
    std::cin >> editName;
    for (int i = 0; i < members_size; i++)
    {
        if(members[i].check_memName(editName))
        {
            while(true) //continue until exit
            {
                edit_memberMenu();
                std::cin >> editCase;
                members[i].setCase1(editCase);
                if (editCase == 4)
                {
                    break;
                } 
            }
        }
    }

}
