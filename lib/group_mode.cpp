// contains all functionalities for group mode

#include <iostream>
#include <errno.h>
#include <fstream>
#include <string>
#include <windows.h>

#include "group_mode.h"
#include "member.h"
#include "profile.h"
#include "screen_util.h"

#define MODE 'g'

// MEMBER FUNCTIONS

// edits a member
void edit_member(int members_size, Member *members, int caseType);
// removes a member
void removeMem(int *members_size, Member *members);

// CASES

// menu prompt for cases selection
void caseMenu();

// CASE 1

// case 1 main menu
void case_one(int *members_size, Member *members);
// case 1 menu prompt
void case_oneMenu();
// edit member menu for case 1
void edit_memberMenu();

// CASE 2

// case 2 main menu
void case_two(int *members_size, Member *members);
// case 2 menu prompt
void case_twoMenu();
// edit member menu for case 2
void edit_memberMenu2();

// CASE 3

// case thr3ee main menu
void case_three(Member *members, int *members_size, int option);
// case 3 menu prompt
void case_threeMenu();

// READING AND WRITING FUNCTIONS

void init(std::string, Member[], int*);
void save(std::string, Member[], int*);

// AUXILIARY FUNCTIONS

// returns 1 if file is empty, else returns 0
bool gmode_file_empty(std::ifstream&);


void group_mode(){
    Member members[20];
    int members_size = 0;      

    int open, option;
    bool loop = true;
    
    std::string file_name;

    open = profile_selection(MODE, &file_name);

    if (!open)
    {
        return;
    }

    // read saved data from profile file
    init(file_name, members, &members_size);

    while (loop){
        // display cases selection menu prompt
        caseMenu();
        std::cin >> option;
        
        switch (option){
            case 0:
                if ( !user_confirm("Are you sure you want to exit?") ) continue;

                loading("Returning to main menu");
                loop = false;
                break;
            case 1:
                loading("Loading SUKLI NI KINSA");
                case_one(&members_size, members);
                break;
            case 2:
                loading("Loading UTANG TRACKER");
                case_two(&members_size, members);
                break;
            case 3:
                loading("Loading GASTO MO ANG LIMIT!");
                case_three(members, &members_size, option);
                break;
            default:
                pause_invalid();
                continue;
        }
    }

    save(file_name, members, &members_size);
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
                        members[i].display_details(1);
                        
                        // display edit menu prompt
                        edit_memberMenu();

                        std::cin >> editCase;
                        
                        // edit member details
                        members[i].setCase1(editCase);

                        if (editCase == 0)
                        {
                            loading("Returning to menu");
                            break;
                        } 
                    }
                } 
            }

            if (!found){
                loading("Member not found. Returning to menu");
            }
        break;
    }

    case 2:{
        for (int i = 0; i < members_size; i++)
        {
            if(members[i].check_memName(editName))
                {
                    found = true;
                    
                    while(true) //continue until exit
                    {
                        members[i].display_details(2);
                        
                        edit_memberMenu2();
                        std::cin >> editCase;

                        members[i].setCase2(editCase);
                        if (editCase == 0)
                        {
                            loading("Returning to menu");
                            break;
                        } 
                    }
                }
        }

        if (!found){
            loading("Member not found. Returning to main menu");
        }
        break;
    }
        
    default:
        break;
    }
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

            if ( !user_confirm("Are you sure you want to delete this member?") ){
                loading("Member deletion cancelled. Returning to main menu");
                return;
            } 

            loading("Deleting member");

            for (int j = i; j < *members_size - 1; j++) 
            {
                members[j] = members[j + 1];
            }
            (*members_size)--;
            break;
        }
    }

    if (!found)
    {
        loading("Member not found. Returning to menu");
    }
}

void caseMenu(){
    std::cout << "\n\n";
    print_ascii("gmode");

    std::cout << "\n\nPick a use case:\n\n";
    std::cout << "1) Sukli sa Kinsa\n";
    std::cout << "  - Manages change calculation\n\n";  
    std::cout << "2) Utang Tracker\n";
    std::cout << "  - Tracks of who paid\n\n";
    std::cout << "3) Gasto Mo Ang Limit!\n";
    std::cout << "  - Limits spending\n\n";
    std::cout << "0) Exit\n\n";
}

void case_one(int *members_size, Member *members){
    int caseOneTask;
    int totalBill = 0;
    int bill;
    int totalPayment = 0;
    int payment;
    int totalChange = 0;
    std::string displayName;
    bool found, verify;

    do
    {
        found = false;
        
        // case 1 title
        std::cout << "\nUTANG NI KINSA\n\n";
        
        // display member details
        std::cout << "=====MEMBERS=====\n";
        for (int i = 0; i < *members_size; i++)
            {
                members[i].display_name_and_change();
            }
        std::cout << "\n=================\n\n";

        // prompt menu
        case_oneMenu();

        std::cin >> caseOneTask;

        switch (caseOneTask)
        {
        // add new member
        case 1:{
            do{
                if (*members_size == 20){
                    loading("Members limit already reached. Returning to main menu");
                    break;
                }
                
                members[*members_size].create_member();
                members[*members_size].initialize(1);

                verify = !user_confirm("Are you sure you've entered the correct information?");
            } while (verify);
            
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
        // display member details
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

                    pause_til_input();
                }
            }

            if (!found)
            {
                loading("Member not found. Returning to main menu");
                break;
            }

            break;
        }
        // display total details
        case 5:
            for (int i = 0; i < *members_size; i++)
            {
                bill = members[i].getBill();
                totalBill += bill;
                payment = members[i].getPayment();
                totalPayment += payment;
            }
            totalChange = totalPayment - totalBill;

            std::cout << "\nTotal Bill: " << totalBill << std::endl;
            std::cout << "\nTotal Payment: " << totalPayment << std::endl;
            std::cout << "\nTotal Change: " << totalChange << std::endl;

            pause_til_input();
            
            break;
        // exit
        case 0: 
            if ( !user_confirm("Are you sure you want to exit?") ) continue;
            
            loading("Return to use case menu");
            break;

        default:
            break;
        }
    } while (caseOneTask != 0);
    
}

void case_oneMenu(){
    std::cout << "\nWhat would you like to do?" << std::endl;
    std::cout << "1) Add a new member" << std::endl;
    std::cout << "2) Edit a member" << std::endl;
    std::cout << "3) Delete a member" << std::endl;
    std::cout << "4) Display member details" << std::endl;
    std::cout << "5) Display total bill, payment, and change" << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void edit_memberMenu(){
    std::cout << "\nWhat do you want to edit?" << std::endl;
    std::cout << "1) Name " << std::endl;
    std::cout << "2) Bill " << std::endl;
    std::cout << "3) Payment  " << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void case_two(int *members_size, Member *members){
    int caseTwoTask;
    bool found, verify;

    do
    {
        found = false;

        std::cout << "\nUTANG TRACKER\n\n";
        
        // display members and their contribution status
        std::cout << "=====MEMBERS=====\n";
        std::cout << "\nPaid:\n";
        for (int i = 0; i < *members_size; i++)
        {
            members[i].contributed();
        }
        std::cout << "\nDidn't pay yet:\n";
        for (int i = 0; i < *members_size; i++)
        {
            members[i].notContributed();
        }
        std::cout << "\nMembers:\n";
        for (int i = 0; i < *members_size; i++)
        {
            members[i].not_included_in_contributed();
        }
        std::cout << "\n=================\n\n";

        case_twoMenu();
        std::cin >> caseTwoTask;

        switch (caseTwoTask)
        {
        // add member
        case 1:{
            do{
                if (*members_size == 20){
                    loading("Members limit already reached. Returning to main menu");
                    break;
                }
                
                members[*members_size].create_member();
                members[*members_size].initialize(2);

                verify = !user_confirm("Are you sure you've entered the correct information?");
            } while (verify);
            
            (*members_size)++;
            break;
        }
        // update member
        case 2:{
            std::string updateName;

            std::cout << "\nWhat is the name of the member you want the details to be updated?: ";
            std::cin.ignore();
            getline(std::cin, updateName);

            for (int i = 0; i < *members_size; i++)
            {
                if (members[i].check_memName(updateName))
                {
                    found = true;
                    members[i].updateCase2();
                    break;
                }
            }

            if (!found){
                loading("Member not found. Returning to main menu");
            }
            break;
        }
        // edit member
        case 3:{
            edit_member(*members_size, members, 2);
            break;
        }  
        // delete member
        case 4:{
            removeMem(members_size, members);
            break;
        }
        // display member details
        case 5:{
            std::string displayName;

            std::cout << "\nWhat is the name of the member you want the details to be displayed?: ";
            std::cin.ignore();
            getline(std::cin, displayName);

            for (int i = 0; i < *members_size; i++)
            {
                if (members[i].check_memName(displayName))
                {
                    found = true;
                    members[i].display_details(2);

                    pause_til_input();
                    break;
                }
            }
            std::cout << std::endl;

            if (!found){
                loading("Member not found. Please try again");
            }
            break;
        }

        case 0: 
            if ( !user_confirm("Are you sure you want to exit?") ) continue;

            loading("Returning to use case menu");
            return;

        default:
            break;
        }
    } while (caseTwoTask != 0);
    
}

void case_twoMenu(){
    std::cout << "\nWhat would you like to do?" << std::endl;
    std::cout << "1) Add a new member" << std::endl;
    std::cout << "2) Update if the member has paid" << std::endl;
    std::cout << "3) Edit member details" << std::endl;
    std::cout << "4) Delete a member" << std::endl;
    std::cout << "5) Display member details" << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void edit_memberMenu2(){
    std::cout << "\nWhat do you want to edit?: " << std::endl;
    std::cout << "1) Name " << std::endl;
    std::cout << "2) Payment " << std::endl;
    std::cout << "3) Bill  " << std::endl;
    std::cout << "4) Date" << std::endl;
    std::cout << "0) Exit" << std::endl << std::endl;
}

void case_three(Member *members, int *members_size, int option) {
    int member_choice;
    std::string name, displayName;
    bool found;

    while (true) {
        found = false;
        
        std::cout << "\nGASTO MO ANG LIMIT!\n\n";

        std::cout << "=====MEMBERS=====\n";
        for (int i = 0; i < *members_size; i++){
            members[i].display_details(option);
        }
        std::cout << "\n================\n\n";

        case_threeMenu();
        std::cin >> member_choice;

        switch (member_choice) {
            // add member
            case 1:
                if (*members_size == 20){
                    loading("Members limit already reached. Returning to main menu");
                    break;
                }

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
                std::cout << "\nEnter the name of member you want to add an expense to: ";
                std::cin.ignore();
                getline(std::cin, displayName);

                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        found = true;
                        members[i].addExpense();
                    }
                }

                if (!found) {
                    loading("Member not found. Returning to main menu");
                    continue;
                }
                break;
            // display member details
            case 4:
                std::cout << "\nEnter the name of member you want to display: ";
                std::cin.ignore();
                getline(std::cin, displayName);

                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        found = true;
                        members[i].displayMember();

                        pause_til_input();
                    }
                } 

                if (!found)
                {
                    loading("Member not found. Returning to main menu");
                    continue;
                }
                break;
            // add budget
            case 5:                
                std::cout << "\nEnter the name of member to edit their budget: ";
                std::cin.ignore();
                getline(std::cin, displayName);
 
                for (int i = 0; i < *members_size; i++)
                {
                    if (members[i].check_memName(displayName))
                    {
                        found = true;
                    
                        members[i].add_budget();

                        loading("Budget updated. Returning to main menu");

                        break;
                    }
                } 

                if (!found) {
                    loading("Member not found. Returning to main menu");
                    continue;
                }

                break;
            case 0:
                if ( !user_confirm("Are you sure you want to exit?") ) continue;
                
                loading("Returning to use case menu");

                return;
            default:
                pause_invalid();
                continue;
        }
    }
}

void case_threeMenu(){
    std::cout << "\nWhat would you like to do?\n";
    std::cout << "1) Add Member\n";
    std::cout << "2) Delete Member\n";
    std::cout << "3) Add Expense for Member\n";
    std::cout << "4) Display Member Details\n";
    std::cout << "5) Add Budget (if budget is none)\n";
    std::cout << "0) Exit\n\n";
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