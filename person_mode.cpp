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
// display records by record type
void display_records_by_type(ProfileDetails);
// display records by specified amount range
void display_records_by_amount(ProfileDetails);
// display records by category
void display_records_by_category(ProfileDetails);
// display category percentages
void display_category_percentages(ProfileDetails);
// add account
void add_account(ProfileDetails*);
// modify account
void modify_account(ProfileDetails*);
// display accounts
void display_accounts(ProfileDetails, bool balance = true);
// delete account
void delete_account(ProfileDetails*);
// transfer balance from one account to another
void transfer_balance(ProfileDetails*);

// READING AND WRITING FUNCTIONS

// initialize saved data from file reading
int init(std::string, ProfileDetails*);
// save data to file
void save(std::string, ProfileDetails*);

// FILTER FUNCTIONS

// display by date of transaction for all accounts
void filter_by_date(ProfileDetails, Date, bool display_call = false);

// AUXILIARY FUNCTIONS

// display person menu prompt
void person_menu_prompt(ProfileDetails details);
// add default accounts to accounts array
void add_default_accounts(ProfileDetails*);
// select account to use
int select_account(ProfileDetails, bool modify_call = false);
// calculate total balance
void calculate_total_balance(ProfileDetails*);
// returns true if file is empty, else return false
bool pmode_file_empty(std::ifstream&);


int person_mode(){
    ProfileDetails details;
    details.accounts_size = 0; 

    int open, empty, option;
    char c_option;
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
    empty = init(file_name, &details);

    // if file is empty, add default accounts to accounts array
    // default accounts: cash, card, savings
    if (empty){
        add_default_accounts(&details);
    }

    // person mode main menu
    while (loop){
        person_menu_prompt(details);

        std::cin >> option;

        switch (option){
            // exit menu
            case 0:
                std::cout << "\nAre you sure you want to exit? (Enter Y to confirm) ";
                std::cin >> c_option;
                if (c_option == 'Y'){
                    loop = false;
                }
                break;
            // add a record
            case 1:
                add_account_record(&details);
                break;
            // modify a record
            case 2:
                modify_account_record(&details);
                break;
            // delete a record
            case 3:
                delete_account_record(&details);
                break;
            // display records by account
            case 4:
                display_records_by_account(details);
                break;
            // display records by date
            case 5:
                display_records_by_date(details);
                break;
            // display records by type
            case 6:
                display_records_by_type(details);
                break;
            // display records by amount range
            case 7:
                display_records_by_amount(details);
                break;
            // display records by category
            case 8:
                display_records_by_category(details);
                break;
            // display percentages of category occurrences
            case 9:
                //display_category_percentages(details);
                break;
            // add new account
            case 10:
                add_account(&details);
                break;
            // modify account details
            case 11:
                modify_account(&details);
                break;
            // display all accounts
            case 12:
                display_accounts(details);
                break;
            // delete account
            case 13:
                delete_account(&details);
                break;
            // transfer balance
            case 14:
                transfer_balance(&details);
                break;
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
        std::cout << "\nAccount not found. Returning to main menu...\n";
        return;
    }

    details->accounts[index].add_record();
}

void modify_account_record(ProfileDetails* details){
    int index;

    index = select_account(*details);

    if (index == -1){
        std::cout << "\nAccount not found. Returning to main menu...\n";
        return;
    }

    details->accounts[index].modify_record_screen();
}

void delete_account_record(ProfileDetails* details){
    int index;

    index = select_account(*details);

    if (index == -1){
        std::cout << "\nAccount not found. Returning to main menu...\n";
        return;
    }

    details->accounts[index].delete_record();
}

void display_records_by_account(ProfileDetails details){
    int index;

    index = select_account(details);

    if (index == -1){
        std::cout << "\nAccount not found. Returning to main menu...\n"; // ERROR HANDLING (Cannot be found)
        return;
    }

    details.accounts[index].display_records();
}

void display_records_by_date(ProfileDetails details){
    Date date;
    bool loop = true;

    while (loop){
        std::cout << "\nEnter date (mm dd yyyy): ";
        std::cin >> date.month;
        std::cin >> date.day;
        std::cin >> date.year;

        if ( !date_is_valid(date) ){
            std::cout << "\nInputted date is invalid. Please try again.\n";
            continue;
        }

        loop = false;
    }

    filter_by_date(details, date, true);
}

void display_records_by_type(ProfileDetails details){
    std::string input;
    char record_type;
    bool found = false;

    std::cout << "\nEnter record type ( Income / Expense ): ";
    std::cin >> input;

    if (input == "Income"){
        record_type = 'i';
    } else if (input == "Expense"){
        record_type = 'e';
    } else {
        std::cout << "\nInvalid input. Returning to main menu...\n";
        return;
    }

    for (int i = 0; i < details.accounts_size; ++i){
        if (details.accounts[i].filter_by_record_type(record_type) && !found) found = true;
    }

    if (!found){
        std::cout << "\nNo records satisfy the inputted type. Returning to main menu...\n"; // ERROR HANDLING (Cannot be found)
    }
}

void display_records_by_amount(ProfileDetails details){
    double amount, low, high;
    int option;
    bool loop = true, found = false;

    std::cout << "\nEnter...\n";
    std::cout << "1) Exact Amount\n";
    std::cout << "2) Amount Range\n\n";
    std::cin >> option;

    switch(option){
        case 1:
            std::cout << "\nEnter amount: ";
            std::cin >> amount;

            low = amount;
            high = amount;
            break;
        case 2:
            while (loop){
                std::cout << "\nEnter minimum for amount range: ";
                std::cin >> low;

                std::cout << "Enter maximum for amount range: ";
                std::cin >> high;

                if (low > high){
                    std::cout << "\nInputted minimum is greater than inputted maximum. Please try again.\n"; // ERROR HANDLING (Invalid input range)
                    continue;
                }

                loop = false;
            }
            break;
        default:
            std::cout << "\nInvalid input. Returning to main menu...\n"; // ERROR HANDLING (Invalid user input)
            return;
    }

    for (int i = 0; i < details.accounts_size; ++i){
        if (details.accounts[i].filter_by_amount_range(low, high) && !found) found = true;
    }

    if (!found){
        std::cout << "\nNo records satisfy the specified amount range. Returning to main menu...\n"; // ERROR HANDLING (Cannot be found)
    }
}

void display_records_by_category(ProfileDetails details){
    std::string category;
    bool found = false;

    std::cout << "\nEnter a category: ";
    std::cin >> category;

    for (int i = 0; i < details.accounts_size; ++i){
        if (details.accounts[i].filter_by_category(category) && !found) found = true;
    }

    if (!found){
        std::cout << "\nCategory " << category << " not found. Returning to main menu...\n"; // ERROR HANDLING (Cannot be found)
    }
}

void display_category_percentages(ProfileDetails details){

}

void add_account(ProfileDetails* details){
    if (details->accounts_size >= sizeof(details->accounts) / sizeof(Account)){
        std::cout << "\nMaximum account limit reached. Returning to main menu...\n";
        return;
    }
    
    details->accounts[details->accounts_size].initialize();
    details->accounts_size++;
}

void modify_account(ProfileDetails* details){
    std::string account_name;
    double balance;
    int index, option, exit;
    bool loop = true;

    // returns to man menu if there are no accounts
    if (details->accounts_size <= 0){
        std::cout << "\nThere are no accounts to modify. Returning to man menu...\n";
        return;
    }

    // select account
    index = select_account(*details, true);

    // return to main menu if account name isnt found
    if (index == -1){
        std::cout << "\nAccount not found. Returning to main menu...\n";
        return;
    }

    while (loop){
        // display account details
        std::cout << std::endl << "Account Name: " << details->accounts[index].get_account_name() << std::endl;
        std::cout << "Balance: " << CURRENCY << " " << details->accounts[index].get_balance() << std::endl;
        
        // display menu option prompts
        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1) Modify account name\n";
        std::cout << "2) Modify balance\n";
        std::cout << "0) Exit\n\n";
        std::cin >> option;

        switch(option){
            // exit
            case 0:
                std::cout << "\nAre you sure that you want to discard your changes? (Enter Y to discard): ";
                std::cin >> exit;
                if (exit == 'Y'){
                    loop = false;
                }
                break;
            // modify account name
            case 1:
                std::cout << "\nEnter new account name: ";
                std::cin >> account_name;

                details->accounts[index].set_account_name(account_name);

                loop = false;
                break;
            // modify balance
            case 2:
                std::cout << "\nEnter new balance: ";
                std::cin >> balance;

                details->accounts[index].set_balance(balance);

                loop = false;
                break;
        }
    }
}

void display_accounts(ProfileDetails details, bool balance){
    std::cout << "\n-----ACCOUNTS-----\n";
    for (int i = 0; i < details.accounts_size; ++i){
        std::cout << details.accounts[i].get_account_name() << std::endl;
        
        if (balance){
            std::cout << "Balance: " << CURRENCY << " " << details.accounts[i].get_balance() << std::endl << std::endl;
        }
    }
    std::cout << "------------------\n";
}

void delete_account(ProfileDetails* details){
    int index;
    char option;

    // return to main menu if there are no accounts to delete
    if (details->accounts_size <= 0){
        std::cout << "\nThere are no accounts to delete. Returning to main menu...\n";
        return;
    }

    // select account
    index = select_account(*details, true);

    // return to main menu if account name isnt found
    if (index == -1){
        std::cout << "\nAccount not found. Returning to main menu...\n";
        return;
    }

    // display account details
    std::cout << std::endl << "Account Name: " << details->accounts[index].get_account_name() << std::endl;
    std::cout << "Balance: " << CURRENCY << " " << details->accounts[index].get_balance() << std::endl;

    std::cout << "\nDo you want to delete this record? (Enter Y to proceed) ";
    std::cin >> option;

    if (option == 'Y'){
        // deleting an account by shifting accounts right of deleted account to the left
        for (int i = index + 1; i < details->accounts_size; ++i){
            details->accounts[i - 1] = details->accounts[i];
        }
        // decrease accounts size
        --details->accounts_size;
        std::cout << "\nAccount has been deleted. Returning to main menu...\n";
    } else {
        std::cout << "\nAccount deletion canceled. Returning to main menu...\n";
    }
}

void transfer_balance(ProfileDetails* details){
    std::string current, destination;
    double amount;
    int curr_index = -1, dest_index = -1;
    bool found, loop = true;

    while (loop){
        found = false;
        
        // display account details
        display_accounts(*details);

        // enter current destination
        std::cout << "\nEnter current account destination: ";
        std::cin >> current;

        // check if account name exists
        for (int i = 0; i < details->accounts_size; ++i){
            if ( current == details->accounts[i].get_account_name() ){
                found = true;
                curr_index = i;
            }
        }

        // if it doesnt, let the user input again
        if (curr_index == -1 && !found){
            std::cout << "\nInvalid account name. Please try again.\n"; // ERROR HANDLING (Invalid user input)
            continue;
        }

        found = false;

        // enter new destination
        std::cout << "\nEnter new account destination: ";
        std::cin >> destination;

        // look for account if it exists
        for (int i = 0; i < details->accounts_size; ++i){
            if ( destination == details->accounts[i].get_account_name() ){
                found = true;
                dest_index = i;
            }
        }

        // allow user to input again if not found
        if (dest_index == -1 && !found){
            std::cout << "\nInvalid account name. Please try again.\n"; // ERROR HANDLING (Invalid user input)
            continue;
        }

        // enter amount to transfer
        std::cout << "\nEnter amount to transfer: ";
        std::cin >> amount;

        // you can't transfer 0 or negative money 
        if (amount <= 0){
            std::cout << "\nAmount entered is invalid.\n";
            continue;
        }

        // add transfer record to records
        details->accounts[curr_index].transfer_balance(amount, true);
        details->accounts[dest_index].transfer_balance(amount, false);

        std::cout << "\nReturning to main menu...\n";

        loop = false;
    }
}

int init(std::string file_name, ProfileDetails* details){
    std::ifstream file;
    long int pos;

    // open file for reading
    file.open(file_name, std::ios::binary);

    if ( file.fail() ){
        perror("\nFile not found. Initialization failed."); // ERROR HANDLING (File not found)
        exit(EXIT_FAILURE);
    }

    // returns 1 when file is empty
    // to add default accounts (cash, card, savings)
    if (pmode_file_empty(file)){
        return 1;
    }

    // read accounts array size
    if ( !(file.read( (char *) &details->accounts_size, sizeof(int) ) ) ){
        perror("\nReading accounts size failed."); // ERROR HANDLING (File reading failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    // get current file ptr position for continuous reading
    pos = file.tellg();

    file.close();

    // read accounts array
    for (int i = 0; i < details->accounts_size; ++i){
        details->accounts[i].deserialize(file_name, &pos);
    }

    return 0;
}

void save(std::string file_name, ProfileDetails* details){
    std::ofstream file;
    
    // open file for writing
    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::binary | std::ios::trunc);

    if ( file.fail() ){
        perror("\nSaving failed."); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // write accounts array size
    if ( !(file.write( (char *) &(details->accounts_size), sizeof(int) ) ) ){
        perror("\nWriting accounts size failed."); // ERROR HANDLING (File writing failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // write accounts array
    for (int i = 0; i < details->accounts_size; ++i){
        details->accounts[i].serialize(file_name);
    }
}

void person_menu_prompt(ProfileDetails details){
    Date current_date, yesterday;
    
    // set dates
    current_date = get_current_date();
    yesterday = get_yesterday_date();

    // calculate total balance
    calculate_total_balance(&details);

    // display menu title
    std::cout << "\n\n=====PERSON MODE=====\n\n";
    printf("Today is %s, %s %i %i\n", current_date.day_name.c_str(), current_date.month_name.c_str(), current_date.day, current_date.year);
    std::cout << "Total Balance: " << CURRENCY << " " << details.total_balance << std::endl;

    // display today's records for all accounts
    std::cout << "\nToday's Transactions:\n";
    filter_by_date(details, current_date);

    // display yesterday's records for all accounts
    std::cout << "\nYesterday's Transactions:\n";
    filter_by_date(details, yesterday);

    std::cout << "\n=====================\n\n";

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
    std::cout << "9) Display category percentages\n";
    std::cout << "-----ACCOUNTS-----\n";
    std::cout << "10) Add an account\n";
    std::cout << "11) Modify an account\n";
    std::cout << "12) Display all accounts\n";
    std::cout << "13) Delete an account\n";
    std::cout << "14) Transfer balance\n";
    std::cout << "0) Exit\n\n";
}

void filter_by_date(ProfileDetails details, Date date, bool display_call){
    bool found = false;
    
    // display records for all accounts according to date
    for (int i = 0; i < details.accounts_size; ++i){
        if (details.accounts[i].filter_by_date(date) && !found) found = true;
    }

    if (!found && display_call){
        std::cout << "\nNo records satisfy the inputted date. Returning to main menu...\n";
    }
}

void add_default_accounts(ProfileDetails* details){
    details->accounts[0].auto_initialize("Cash");
    details->accounts[1].auto_initialize("Card");
    details->accounts[2].auto_initialize("Savings");

    details->accounts_size = 3;
}

int select_account(ProfileDetails details, bool modify_call){
    std::string input;
    
    // display accounts available
    display_accounts(details, modify_call);
    
    // ask user input for account name
    std::cout << "\nEnter account name: ";
    std::cin >> input;

    // checks if input account name is present (case sensitive)
    // if yes, returns the index of the account
    for (int i = 0; i < details.accounts_size; ++i){
        if (input == details.accounts[i].get_account_name()){
            return i;
        }
    }

    // if not found, return -1 (indicating not found)
    return -1;
}

void calculate_total_balance(ProfileDetails* details){
    double total_balance = 0;

    // add balance of all accounts into total_balance
    for (int i = 0; i < details->accounts_size; ++i){
        total_balance += details->accounts[i].get_balance();
    }

    details->total_balance = total_balance;
}

bool pmode_file_empty(std::ifstream& file){
    return file.peek() == std::ifstream::traits_type::eof();
}






