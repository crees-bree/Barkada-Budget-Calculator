// contains all functionalities for group mode

#include <iostream>
#include <errno.h>
#include <fstream>

#include "group_mode.h"
#include "member.h"
#include "profile.h"

#define MODE 'g'


// MEMBER FUNCTIONS

// edits a member
void edit_member(int members_size, Member *members);
// edit member menu
void edit_memberMenu();
// removes a member
void removeMem(int *members_size, Member *members);

// CASES MENU PROMPTS

// menu prompt for cases selection
void caseMenu();
// case one menu prompt
void case_oneMenu();
// case three menu prompt
void case_threeMenu();


// CASES MENU FUNCTIONS

// case one main menu
void case_one(int *members_size, Member *members);
// case two main menu
void case_two();
// case three main menu
void case_three();

// READING AND WRITING FUNCTIONS

void init(std::string, Member[], int*);
void save(std::string, Member[], int*);

// AUXILIARY FUNCTIONS

// returns 1 if file is empty, else returns 0
bool file_empty(std::ifstream&);


int group_mode(){
    Member members[20];
    int members_size = 0;      

    int open, option;
    char exit;
    bool loop = true;

    std::string file_name;

    // select a profile first
    open = profile_selection(MODE, &file_name);

    // exit program if open profile is not initiated
    if (!open){
        // program exited successfully
        return 0;
    }

    // read saved data from profile file
    init(file_name, members, &members_size);

    while (loop){
        // display cases selection menu prompt
        caseMenu();

        std::cin >> option;
        
        switch (option){
            case 0:
                std::cout << "\nAre you sure you want to exit? (Enter Y to confirm) ";
                std::cin >> exit;

                if (exit == 'Y'){
                    loop = false;
                }

                break;
            case 1:
                case_one(&members_size, members);
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                std::cout << "\nInvalid input. Please try again.\n" << std::endl;
                continue;
        }
    }

    save(file_name, members, &members_size);

    return 0;
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

void edit_memberMenu(){
    std::cout << "What do you want to edit?: " << std::endl;
    std::cout << "1. Name: " << std::endl;
    std::cout << "2. Bill: " << std::endl;
    std::cout << "3. Expense:  " << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void removeMem(int *members_size, Member *members){                 //have to debug for us to know for sure that it works
    std::string removeName;
    std::cout << "What is the name of the member you want to remove?: " << std::endl;
    std::cin >> removeName;
    for (int i = 0; i < *members_size; i++)
    {
        if(members[i].check_memName(removeName))
        {
            for (int j = i; j < *members_size - 1; j++) 
            {
                members[j] = members[j + 1];
            }
            (*members_size)--;
            break;
        }
    }
}

void caseMenu(){
    std::cout << "\n Case Menu:\n" << std::endl;
    std::cout << "1) Sukli sa Kinsa" << std::endl;          
    std::cout << "2) Utang Tracker" << std::endl;
    std::cout << "3) Gasto Mo Ang Limit" << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void case_oneMenu(){
    std::cout << "\n Case 1 Menu:" << std::endl;
    std::cout << "1. Add a new member" << std::endl;
    std::cout << "2. Edit a member" << std::endl;
    std::cout << "3. Delete a member" << std::endl;
    std::cout << "4. Display each member details" << std::endl;
    std::cout << "5. Display all member details" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void casethree_Menu(){
    std::cout << "\n Case 3 Menu: Gasto Mo Ang Limit!\n";
    std::cout << "1. Add Member.\n";
    std::cout << "2. Delete Member \n.";
    std::cout << "3. Add Expense for Member\n";
    std::cout << "4. Display Member Details.\n";
    std::cout << "5. Exit\n";
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
        removeMem(members_size, members);
        break;
    
    case 4:{
        std::string displayName;
        std::cout << "What is the name of the member you want the details to be displayed?: " << std::endl;
        std::cin >> displayName;
        for (int i = 0; i < *members_size; i++)
        {
            if (members[i].check_memName(displayName))
            {
                members[i].display_details(1, *members_size);
                return;
            }
        }
        break;
    }
    case 5:{
        for (int i = 0; i < *members_size; i++)
        {
            members[i].display_details(1, *members_size);
        }
        break;
    }

    case 6: return;

    default:
        break;
    }
}

void removeMem(int *members_size, Member *members){                 //have to debug for us to know for sure that it works
    std::string removeName;
    std::cout << "What is the name of the member you want to remove?: " << std::endl;
    std::cin >> removeName;
    for (int i = 0; i < *members_size; i++)
    {
        if(members[i].check_memName(removeName))
        {
            for (int j = i; j < *members_size - 1; j++) 
            {
                members[j] = members[j + 1];
            }
            (*members_size)--;
            break;
        }
    }
}

void case_oneMenu(){
    // - chan
    // group budget limiter lagi ni 
    // im high, removed na - conx
    std::cout << "\n Case 1 Menu:" << std::endl;
    std::cout << "1. Add a new member" << std::endl;
    std::cout << "2. Edit a member" << std::endl;
    std::cout << "3. Delete a member" << std::endl;
    std::cout << "4. Display each member details" << std::endl;
    std::cout << "5. Display all member details" << std::endl;
    std::cout << "6. Exit" << std::endl;
}

void caseMenu(){
    std::cout << "\n Case Menu:\n" << std::endl;
    std::cout << "1. Sukli sa Kinsa" << std::endl;          
    std::cout << "2. Utang Tracker" << std::endl;
    std::cout << "3. Gasto Mo Ang Limit" << std::endl;
    std::cout << "4. Exit" << std::endl;
}

void edit_memberMenu(){
    std::cout << "What do you want to edit?: " << std::endl;
    std::cout << "1. Name: " << std::endl;
    std::cout << "2. Bill: " << std::endl;
    std::cout << "3. Expense:  " << std::endl;
    std::cout << "4. Exit" << std::endl;
}


void case_two(Member *members){

}
void case_two(){
    
}

void case_three(Member *members, int *members_size, int option) {
    int member_choice;
    std::string name;
    double payment, bill;

    while (true) {
        members[*members_size].display_details(option, *members_size);
        case_threeMenu();
        std::cin >> member_choice;
        std::string displayName;

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
            case 2: //delete member
                    removeMem(members_size, members);
                break;
            case 3:
                std::cout << "Enter the name of member you want to add an expense to: " << std::endl;
                std::cin >> displayName;
                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        members[i].addExpense();
                        return;
                    }
                }
                break;
            case 4:
                std::cout << "Enter the name of member you want to display: " << std::endl;
                std::cin >> displayName;
                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        members[i].displayMember();
                        return;
                    }
                } 
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice. Please select again.\n";
                break;
        }
    }
}

void init(std::string file_name, Member members[], int* members_size){
    std::ifstream file;
    long int pos;

    // open file for reading
    file.open(file_name, std::ios::binary);

    if ( file.fail() ){
        perror("\nFile not found. Initialization failed."); // ERROR HANDLING (File not found)
        exit(EXIT_FAILURE);
    }

    // end initializing data if profile file is empty
    if (file_empty(file)){
        file.close();
        return;
    }

    // read members array size
    if ( !(file.read( (char *) members_size, sizeof(int) ) ) ){
        perror("\nReading members size failed."); // ERROR HANDLING (File reading failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    // get current file ptr position for continuous reading
    pos = file.tellg();

    file.close();

    // read members array
    for (int i = 0; i < *members_size; ++i){
        members[i].deserialize(file_name, &pos);
    }
}

void save(std::string file_name, Member members[], int* members_size){
    std::ofstream file;
    
    // open file for writing
    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::binary | std::ios::trunc);

    if ( file.fail() ){
        perror("\nSaving failed."); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // write members array size
    if ( !(file.write( (char *) members_size, sizeof(int) ) ) ){
        perror("\nWriting members size failed."); // ERROR HANDLING (File writing failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // write members array
    for (int i = 0; i < *members_size; ++i){
        members[i].serialize(file_name);
    }
}

bool file_empty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}













