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

// PROFILE DETAILS STRUCTURE
struct profile_details{
    Account accounts[10]; // only a maximum of 10 accounts can be created
    int accounts_size; // sets the current size of accounts array
    double total_balance;
};
typedef struct profile_details ProfileDetails;

// READING AND WRITING FUNCTIONS

// initialize saved data from file reading
int init(std::string, ProfileDetails*);
// save data to file
void save(std::string, ProfileDetails*);

// FILTER FUNCTIONS

// display by date of transaction for all accounts
void filter_by_date(ProfileDetails*, Date);

// AUXILIARY FUNCTIONS

// display person menu prompt
void person_menu_prompt(ProfileDetails* details);
// add default accounts to accounts array
void add_default_accounts(ProfileDetails*);
// returns true if file is empty, else return false
bool file_empty(std::ifstream&);


int person_mode(){
    ProfileDetails details;
    details.accounts_size = 0; 
    details.total_balance

    int open, empty, option;
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
            case 0:
            case 1:
            case 2:
            case 3:
        }
    }

    // save data to profile file
    save(file_name, &details);

    // program exited successfully
    return 0;
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
    std::cout << "Total Balance: " << details->total_balance << std::endl;

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
    std::cout << ") Delete a record\n";
    std::cout << ") Display records by account\n";
    std::cout << ") Display records by date\n";
    std::cout << ") Display records by record type\n";
    std::cout << ") Display records by specified amount\n";
    std::cout << ") Display records by category\n";
    std::cout << "-----ACCOUNTS-----\n";
    std::cout << ") Add an account\n";
    std::cout << ") Modify an account\n";
    std::cout << ") Delete an account\n";
    std::cout << "0) Exit\n";
}

void filter_by_date(ProfileDetails* details, Date date){
    for (int i = 0; i < details->accounts_size; ++i){
        details->accounts[i].filter_by_date(date);
    }
}

void add_default_accounts(ProfileDetails* details){
    details->accounts[0].auto_initialize("Cash");
    details->accounts[1].auto_initialize("Card");
    details->accounts[2].auto_initialize("Savings");

    details->accounts = 3;
}

bool file_empty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}






