// contains all functionalities for person mode

// NOTES:

// In person mode, a user can add, modify, and delete a record


#include <iostream>
#include <errno.h>
#include <fstream>


#include "account.h"
#include "date.h"
#include "person_mode.h"
#include "profile.h"

#define MODE 'p'

#define CURRENCY "Php"

// PROFILE DETAILS STRUCTURE
struct profile_details{
    Account accounts[10]; // only a maximum of 10 accounts can be created
    int accounts_size; // sets the current size of accounts array
    double total_balance;
};
typedef struct profile_details ProfileDetails;

// MENU FUNCTIONS

// adds new record
void add_account_record(ProfileDetails*);
// modify a record
void modify_account_record(ProfileDetails*);
// delete a record
void delete_account_record(ProfileDetails*);
// display records by account
void display_records_by_account(ProfileDetails);
// display records by date
void display_records_by_date(ProfileDetails);

// READING AND WRITING FUNCTIONS

// initialize saved data from file reading
int init(std::string, ProfileDetails*);
// save data to file
void save(std::string, ProfileDetails*);

// FILTER FUNCTIONS

// display by date of transaction for all accounts
void filter_by_date(ProfileDetails, Date);

// AUXILIARY FUNCTIONS

// display person menu prompt
void person_menu_prompt(ProfileDetails* details);
// add default accounts to accounts array
void add_default_accounts(ProfileDetails*);
// select account to use
int select_account(ProfileDetails);
// returns true if file is empty, else return false
bool file_empty(std::ifstream&);


int person_mode(){
    ProfileDetails details;
    details.accounts_size = 0; 
    details.total_balance

    int open, empty, option;
    char c_option;
    bool loop = true;

    std::fstream profile;
    std::string file_name;

    // select a profile first
    open = profile_selection(MODE, &file_name);

    // exit program if open profile is not initiated
    if (!open){
        // program exited successfully
        return 0;
    }

    // read saved data from profile file
    empty = init(file_name, &details);

    // if file is empty, add default accounts to accounts array
    // default accounts: cash, card, savings
    if (empty){
        add_default_accounts(&details);
    }

    // person mode main menu
    while(loop){
        person_menu_prompt();

        cin >> option;

        switch(option){
            // exit menu
            case 0:
                std::cout << "Are you sure you want to exit? (Enter Y to confirm)\n";
                cin >> c_option;
                if (c_option == 'Y'){
                    loop = false;
                }
                break;
            // add a record
            case 1:
                add_account_record(&details);
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
        }
    }

    // save data to profile file
    save(file_name, &details);

    // program exited successfully
    return 0;
}

void add_account_record(ProfileDetails* details){
    int index;

    index = select_account(*details);

    if (index == -1){
        std::cout << "\nAccount not found.\n";
        return;
    }

    details.accounts[index].add_record();
}

void display_records_by_account(ProfileDetails details){
    int index;

    index = select_account(*details);

    if (index == -1){
        std::cout << "\nAccount not found.\n";
        return;
    }

    details.accounts[index].display_records();
}

void display_records_by_date(ProfileDetails details){
    Date date;

    std::cout << "Enter date (mm dd yyyy): ";
    std::cin >> date.month;
    std::cin >> date.day;
    std::cin >> date.year;

    filter_by_date(details, date);
}

int init(std::string file_name, ProfileDetails* details){
    std::ifstream file;

    // open file for reading
    file.open(file_name, std::ios::binary);

    if ( file.fail() ){
        perror("\nFile not found. Initialization failed."); // ERROR HANDLING (File not found)
        exit(EXIT_FAILURE);
    }

    if (file_empty(file)){
        return 1;
    }

    // read accounts array size
    if ( !(file.read( (char *) details->accounts_size, sizeof(int) ) ) ){
        perror("\nReading accounts size failed."); // ERROR HANDLING (File reading failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // read accounts array
    for (int i = 0; i < details->accounts_size; ++i){
        details->accounts[details->accounts_size].deserialize(file_name);
    }

    return 0;
}

void save(std::string file_name, ProfileDetails* details){
    std::ofstream file;
    
    // open file for writing
    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::binary | std::ios::trunc);

    if ( file.fail() ){
        perror("\nFile cannot be opened. Saving failed."); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // write accounts array size
    if ( !(file.write( (char *) details->accounts_size, sizeof(int) ) ) ){
        perror("\nReading accounts size failed."); // ERROR HANDLING (File writing failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // write accounts array
    for (int i = 0; i < details->accounts_size; ++i){
        details->accounts[details->accounts_size].serialize(file_name);
    }
}

void person_menu_prompt(ProfileDetails* details){
    Date current_date, yesterday;
    
    // set dates
    current_date = get_current_date();
    yesterday = get_yesterday_date();
    
    // display menu title
    std::cout << "=====PERSON MODE=====\n\n";
    printf("Today is %s, %s %i %i\n", current_date.day_name, current_date.month_name, current_date.day, current_date.year);
    std::cout << "Total Balance: " + CURRENCY + " " << details->total_balance << std::endl;

    // display today's records for all accounts
    std::cout << "\nToday's Transactions:\n";
    filter_by_date(current_date);

    // display yesterday's records for all accounts
    std::cout << "\nYesterday's Transactions:\n";
    filter_by_date(yesterday);

    std::cout << "====================\n\n";

    std::cout << "What would you like to do?\n";
    std::cout << "------RECORDS-----\n";
    std::cout << "1) Add a record\n";
    std::cout << "2) Modify a record\n";
    std::cout << "3) Delete a record\n";
    std::cout << "4) Display records by account\n";
    std::cout << "5) Display records by date\n";
    std::cout << "6) Display records by record type\n";
    std::cout << "7) Display records by specified amount\n";
    std::cout << "8) Display records by category\n";
    std::cout << "-----ACCOUNTS-----\n";
    std::cout << "9) Add an account\n";
    std::cout << "10) Modify an account\n";
    std::cout << "11) Delete an account\n";
    std::cout << "0) Exit\n\n";
}

void filter_by_date(ProfileDetails details, Date date){
    for (int i = 0; i < details.accounts_size; ++i){
        details.accounts[i].filter_by_date(date);
    }
}

void add_default_accounts(ProfileDetails* details){
    details->accounts[0].auto_initialize("Cash");
    details->accounts[1].auto_initialize("Card");
    details->accounts[2].auto_initialize("Savings");

    details->accounts = 3;
}

int select_account(ProfileDetails details){
    std::string input;
    
    // display accounts available
    std::cout << "\n-----ACCOUNTS-----\n";
    for (int i = 0; i < details.accounts_size; ++i){
        std::cout << details.accounts[i].get_account_name() << std::endl;
    }
    std::cout << "------------------\n";
    
    // ask user input for account name
    std::cout << "\nEnter account name: ";
    std::cin >> input;

    // checks if input account name is present (case sensitive)
    // if yes, returns the index of the account
    for (int i = 0; i < details.accounts_size; ++i){
        if (input == details.accounts[i].get_account_name){
            return i;
        }
    }

    // if not found, return -1 (indicating not found)
    return -1;
}

bool file_empty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}






