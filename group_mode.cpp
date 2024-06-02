// contains all functionalities for group mode

#include <iostream>
#include <errno.h>
#include <fstream>
#include <string>

#include "group_mode.h"
#include "member.h"
#include "profile.h"

#define MODE 'g'


// MEMBER FUNCTIONS

// edits a member
void edit_member(int members_size, Member *members, int caseType);
// edit member menu
void edit_memberMenu();
void edit_memberMenu2();
// removes a member
void removeMem(int *members_size, Member *members);

// CASES MENU PROMPTS

// menu prompt for cases selection
void caseMenu();
// case one menu prompt
void case_oneMenu();
//case two menu prompt
void case_twoMenu();
// case three menu prompt
void case_threeMenu();


// CASES MENU FUNCTIONS

// case one main menu
void case_one(int *members_size, Member *members);
// case two main menu
void case_two(int *members_size, Member *members);
// case three main menu
void case_three(Member *members, int *members_size, int option);

// READING AND WRITING FUNCTIONS

void init(std::string, Member[], int*);
void save(std::string, Member[], int*);

// AUXILIARY FUNCTIONS

// returns 1 if file is empty, else returns 0
bool gmode_file_empty(std::ifstream&);


int group_mode(){
    Member members[20];
    int members_size = 0;      

    int open, option;
    char exit;
    bool loop = true;
    
    std::string file_name;

    open = profile_selection(MODE, &file_name);
    if (!open)
    {
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
                case_two(&members_size, members);
                break;
            case 3:
                case_three(members, &members_size, option);
                break;
            default:
                std::cout << "\nInvalid input. Please try again.\n" << std::endl;
                continue;
        }
    }

    save(file_name, members, &members_size);

    return 0;
}


void edit_member(int members_size, Member *members, int caseType){
    std::string editName;
    int editCase;
    bool found;

    std::cout << "\nWhat is the name of the member you wish to edit?: ";
    std::cin.ignore();
    getline(std::cin, editName);

    switch (caseType)
    {
    case 1:{
        for (int i = 0; i < members_size; i++)
            {
                if(members[i].check_memName(editName))
                {
                    found = true;
                    
                    while(true) //continue until exit
                    {
                        // display edit menu prompt
                        edit_memberMenu();

                        std::cin >> editCase;
                        
                        // edit member details
                        members[i].setCase1(editCase);

                        if (editCase == 0)
                        {
                            break;
                        } 
                    }
                } 
            }

            if (!found){
                std::cout << "\nMember not found. Returning to main menu...\n";
            }
        break;
    }

    case 2:{
        for (int i = 0; i < members_size; i++)
        {
            if(members[i].check_memName(editName))
                {
                    while(true) //continue until exit
                    {
                        edit_memberMenu2();
                        std::cin >> editCase;
                        members[i].setCase2(editCase);
                        if (editCase == 5)
                        {
                            break;
                        } 
                    }
                }
        }
        break;
    }
        
    default:
        break;
    }
}

void edit_memberMenu2(){
    std::cout << "What do you want to edit?: " << std::endl;
    std::cout << "1. Name " << std::endl;
    std::cout << "2. Payment " << std::endl;
    std::cout << "3. Bill  " << std::endl;
    std::cout << "4. Date" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

void edit_memberMenu(){
    std::cout << "\nWhat do you want to edit?" << std::endl;
    std::cout << "1) Name " << std::endl;
    std::cout << "2) Bill " << std::endl;
    std::cout << "3) Expense  " << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void removeMem(int *members_size, Member *members){                 
    std::string removeName;
    bool found = false;

    std::cout << "\nWhat is the name of the member you want to remove: ";
    std::cin.ignore();
    getline(std::cin, removeName);

    for (int i = 0; i < *members_size; i++)
    {
        if(members[i].check_memName(removeName))
        {
            found = true;

            for (int j = i; j < *members_size - 1; j++) 
            {
                members[j] = members[j + 1];
            }
            (*members_size)--;
            break;
        }
    }

    if (!found) std::cout << "\nMember not found. Returning to main menu...\n";
}

void case_oneMenu(){
    std::cout << "\nWhat would you like to do?" << std::endl;
    std::cout << "1) Add a new member" << std::endl;
    std::cout << "2) Edit a member" << std::endl;
    std::cout << "3) Delete a member" << std::endl;
    std::cout << "4) Display member details" << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void case_twoMenu(){
    std::cout << "\nCase 2 Menu:" << std::endl;
    std::cout << "1. Add a new member" << std::endl;
    std::cout << "2. Update if the member has paid" << std::endl;
    std::cout << "3. Edit member details" << std::endl;
    std::cout << "4. Delete a member" << std::endl;
    std::cout << "5. Display all member details" << std::endl;
    std::cout << "6. Display paid status" << std::endl;
    std::cout << "7. Exit" << std::endl;
}

void case_threeMenu(){
    std::cout << "\n Gasto Mo Ang Limit!\n";
    std::cout << "1. Add Member.\n";
    std::cout << "2. Delete Member. \n";
    std::cout << "3. Add Expense for Member\n";
    std::cout << "4. Display Member Details.\n";
    std::cout << "5. Exit\n\n";
}

void case_one(int *members_size, Member *members){
    int caseOneTask;
    std::string displayName;
    bool found;
    char exit;

    do
    {
        found = false;
        
        // case 1 title
        std::cout << "\nUTANG NI KINSA\n\n";
        
        // display member details
        std::cout << "=====MEMBERS=====\n";
        for (int i = 0; i < *members_size; i++)
            {
                members[i].display_details(1);
            }
        std::cout << "=================\n\n";

        // prompt menu
        case_oneMenu();

        std::cin >> caseOneTask;

        switch (caseOneTask)
        {
        // add new member
        case 1:{
            char verify;

            do{
                members[*members_size].create_member();
                members[*members_size].initialize(1);
                std::cout << "\nAre you sure you've entered the correct information? (Enter Y to confirm) ";
                std::cin >> verify;
            } while (verify != 'Y' && verify != 'y');
            
            (*members_size)++;
            break;
        }
        // edit member
        case 2: {
            edit_member(*members_size, members, 1);
            break;
        }
        // delete member
        case 3:
            removeMem(members_size, members);
            break;
        
        case 4:{
            std::cout << "\nWhat is the name of the member you want the details to be displayed?: ";
            std::cin.ignore();
            getline(std::cin, displayName);

            for (int i = 0; i < *members_size; i++)
            {
                if (members[i].check_memName(displayName))
                {
                    found = true;
                    
                    members[i].display_details(1);
                }
            }

            if (!found)
            {
                std::cout << "\nMember not found. Returning to main menu...\n";
                continue;
            }

            break;
        }
        // exit
        case 0: 
            std::cout << "\nAre you sure you want to exit? (Enter Y to continue) ";
            std::cin >> exit;

            if (exit == 'Y') break;
            
            continue;

        default:
            break;
        }
    } while (caseOneTask != 0);
    
}

void caseMenu(){
    std::cout << "\n\n=====GROUP MODE=====\n\n";
    std::cout << "Pick a use case:\n\n";
    std::cout << "1) Sukli sa Kinsa\n";
    std::cout << "  - Manages change calculation\n\n";  
    std::cout << "2) Utang Tracker\n";
    std::cout << "  - Tracks of who paid\n\n";
    std::cout << "3) Gasto Mo Ang Limit\n";
    std::cout << "  - Limits spending\n\n";
    std::cout << "0) Exit\n\n";
}

void case_two(int *members_size, Member *members){
    int caseTwoTask;
    do
    {
        case_twoMenu();
        std::cin >> caseTwoTask;

        switch (caseTwoTask)
        {
        case 1:{
            char verify;
            do{
                members[*members_size].create_member();
                members[*members_size].initialize(2);
                std::cout << "Are you sure you've entered the correct information? Enter Y if yes, N if no:" << std::endl;
                std::cin >> verify;
            }while(verify != 'Y' && verify != 'y');
            
            (*members_size)++;
            break;
        }

        case 2:{
            std::string updateName;
            std::cout << "What is the name of the member you want the details to be updated?: " << std::endl;
            std::cin >> updateName;
            for (int i = 0; i < *members_size; i++)
            {
                if (members[i].check_memName(updateName))
                {
                    members[i].updateCase2();
                    break;
                }
            }
            break;
        }

        case 3:{
            edit_member(*members_size, members, 2);
            break;
        }

        case 4:{
            removeMem(members_size, members);
            break;
        }

        case 5:{
            std::string displayName;
            std::cout << "What is the name of the member you want the details to be displayed?: " << std::endl;
            std::cin >> displayName;
            for (int i = 0; i < *members_size; i++)
            {
                if (members[i].check_memName(displayName))
                {
                    members[i].display_details(2);
                    break;
                }
            }
            std::cout << std::endl;
            break;
        }

        case 6:{
            std::cout << "\nPaid: " << std::endl;
            for (int i = 0; i < *members_size; i++)
            {
                members[i].contributed();
            }
            std::cout << "Didn't pay yet: " << std::endl;
            for (int i = 0; i < *members_size; i++)
            {
                members[i].notContributed();
            }
            break;
        }

        case 7:return;

        default:
            break;
        }
    } while (caseTwoTask != 7);
    
}

void case_three(Member *members, int *members_size, int option) {
    int member_choice;
    std::string name, displayName;
    double payment, bill;
    bool found;

    while (true) {
        found = false;
        
        for (int i = 0; i < *members_size; i++){
            members[i].display_details(option);
        }

        case_threeMenu();
        std::cin >> member_choice;

        switch (member_choice) {
            // add member
            case 1:
            
                members[*members_size].create_member();
                members[*members_size].initialize(3);

                (*members_size)++;
                break;
            // delete member
            case 2: 
                    removeMem(members_size, members);
                break;
            // add expense for member
            case 3:
                std::cout << "Enter the name of member you want to add an expense to: " << std::endl;
                std::cin >> displayName;
                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        members[i].addExpense();
                    }
                }
                break;
            // display member details
            case 4:
                std::cout << "\nEnter the name of member you want to display: ";
                std::cin >> displayName;

                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        found = true;
                        members[i].displayMember();
                    }
                } 

                if (!found)
                {
                    std::cout << "\nMember not found. Returning to main menu...\n";
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
    if (gmode_file_empty(file)){
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

bool gmode_file_empty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}














