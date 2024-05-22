// contains Account class functionalities

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "account.h"

// AUXILIARY FUNCTIONS
 
// get current day, month, and year
// formatting: months as numbers, years as 4-digit numbers
void get_local_date(int*, int*, int*);

// PRIVATE METHODS DEFINITIONS

char Account::select_record_type(){
    int selection;
    
    while (true){
        std::cout << "\n\nSelect record type:\n";
        std::cout << "1) Income\n";
        std::cout << "2) Expense\n";
        std::cout << "3) Transfer\n";
        std::cin >> selection;

        std::cout << "\n";

        switch(selection){
            // select income
            case 1:
                return 'i';
            // select expense
            case 2:
                return 'e';
            // select transfer
            case 3:
                return 't';
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
                continue;
        }
    }
}

void Account::display_record(Record record){
    std::string record_type_str;
    
    // display date
    printf("\n\nDate: %i/%i/%i\n", record.date.month, record.date.day, record.date.year);

    // display record type
    switch(record.record_type){
        case 'i':
            record_type_str = "Income";
            break;
        case 'e':
            record_type_str = "Expense";
            break;
        case 't':
            record_type_str = "Transfer";
            break;
        default:
            record_type_str = ""; // ERROR HANDLING (Unexpected value)
    }

    std::cout << "Record Type: " << record_type_str << std::endl;

    // display amount in two decimal places
    printf("Amount: %.2lf\n", record.amount);

    // display category
    std::cout << "Category: " << record.category << std::endl;

    // display note
    std::cout << "Note: " << record.note << std::endl;
}

void Account::update_balance(Record record, int add){
    // add to balance if adding a new record,
    // subtract to balance if removing a record
    balance = (add) ? balance + record.amount : balance - record.amount;
}

// PUBLIC METHODS DEFINITIONS

void Account::initialize(){
    // initialize account name
    std::cout << "\nEnter account name: ";
    
    // prevents set_account_name() from skipping account name input
    std::cin.ignore();
    getline(std::cin, Account::account_name);

    // initialize balance to 0
    balance = 0;
}

void Account::add_record(){
    Record record;
    int selection;
    char exit;
    bool loop = true;
    
    // set date automatically to current date
    get_local_date(&record.date.day, &record.date.month, &record.date.year);

    // ask user to select a record type
    record.record_type = select_record_type();

    // ask user to enter amount
    std::cout << "Enter amount: ";
    std::cin >> record.amount;

    // ask user to enter category
    std::cout << "Enter category: ";
    std::cin >> record.category;

    // prevents add_record from skipping note input
    std::cin.ignore();

    // ask user to add a note
    std::cout << "Enter note (input NONE to leave as blank): ";
    getline(std::cin, record.note);

    if (record.note == "NONE"){
        record.note = "";
    }

    // allows to check the details of the record they're about to add
    modify_record(record, true);
}

void Account::modify_record(Record record, bool add_record = false){
    Record new_record = record;
    bool loop = true;
    int selection;
    char exit;
    
    while (loop){
        // display inputted record details
        display_record(new_record);

        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1) Modify date\n";
        std::cout << "2) Modify record type\n";
        std::cout << "3) Modify amount\n";
        std::cout << "4) Modify category\n";
        std::cout << "5) Modify note\n";
        std::cout << "6) Save\n";
        std::cout << "0) Discard\n";

        std::cin >> selection;

        switch(selection){
            // discard record
            case 0:
                std::cout << "\nAre you sure that you want to discard this record? (Enter Y to discard): ";
                std::cin >> exit;
                if (exit == 'Y'){
                    // break loop just in case
                    loop = false;
                    // quit add selection
                    return;
                }
            // modify date
            case 1:
                std::cout << "Enter date (mm dd yyyy): ";
                std::cin >> new_record.date.month;
                std::cin >> new_record.date.day;
                std::cin >> new_record.date.year;

                break;
            // modify record type
            case 2:
                new_record.record_type = select_record_type();
                break;
            // modify amount
            case 3:
                std::cout << "Enter amount: ";
                std::cin >> new_record.amount;
                break;
            // modify category
            case 4:
                std::cout << "Enter category: ";
                std::cin >> new_record.category;
                break;
            // modify note
            case 5:
                std::cout << "Enter note (input NONE to leave as blank): ";
            
                // prevents modify_record from skipping note input
                std::cin.ignore();
                getline(std::cin, new_record.note);

                if (new_record.note == "NONE"){
                    new_record.note = "";
                }

                break;
            // save record
            case 6:
                std::cout << "\nAre you sure that you want to save this record? (Enter Y to save): ";
                std::cin >> exit;

                if (exit == 'Y'){
                    if (add_record){
                        // if called from add_record(), add record to records vector
                        records.push_back(new_record);
                    } else {
                        // save newly edited record
                        record = new_record;
                    }
                    loop = false;
                }
                
                break;
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
        }
    }
}

void Account::display_records(){
            // initialize iterator for records vector
            // treat iter as i (i as in records[i])
            std::vector<Record>::iterator iter;
            
            // display content of at most 20 records
            // iter = records.begin() is equivalent to i = 0
            // iter != records.end() is equivalent to i < whatever size ur vector is
            // iter != (iter + 20) is equivalent to i < 20
            // ++iter is equivalent to ++i
            for (iter = records.begin(); iter != records.end() && iter != (iter + 20); ++iter){
                display_record( *(iter) );
            }
        }

// writing
void Account::serialize(std::string file_name){
    std::ofstream file;

    // buffers
    int records_size;
    const char* account_name_buffer;

    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    account_name_buffer = account_name.c_str();

    // serialize account name
    if ( !(file.write( account_name_buffer, sizeof(account_name_buffer) ) ) ){
        file.close();
        
        perror("Serializing account name failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize balance
    if ( !(file.write( reinterpret_cast<char *> (&balance), sizeof(balance) ) ) ){
        file.close();
        
        perror("Serializing balance failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    records_size = records.size();

    // serialize records vector size
    if ( !(file.write( reinterpret_cast<char *> (&records_size), sizeof(balance) ) ) ){
        file.close();
        
        perror("Serializing records size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize records vector
    for (int i = 0; i < records_size; ++i){
        if ( !(file.write( reinterpret_cast<char *> (&records[i]), sizeof(balance) ) ) ){
            file.close();
            
            perror("Serializing record failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }
    }

    std::cout << "\nData is serialized successfully.\n";

    file.close();
}

// reading
void Account::deserialize(std::string file_name){
    std::ifstream file;

    // buffers
    Record record_buffer;
    int records_size;
    char *account_name_buffer = NULL;

    file.open(file_name, std::ios::in | std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // deserialize account name
    if ( !(file.read( account_name_buffer, sizeof(account_name_buffer) ) ) ){
        file.close();
        
        perror("Deserializing account name failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // transfer data in buffer to account_name
    account_name = account_name_buffer;

    // deserialize balance
    if ( !(file.read( reinterpret_cast<char *> (&balance), sizeof(balance) ) ) ){
        file.close();
        
        perror("Deserializing balance failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector size
    if ( !(file.read( reinterpret_cast<char *> (&records_size), sizeof(balance) ) ) ){
        file.close();
        
        perror("Deserializing records size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector
    for (int i = 0; i < records_size; ++i){
        if ( !(file.read( reinterpret_cast<char *> (&record_buffer), sizeof(balance) ) ) ){
            file.close();
            
            perror("Deserializing record failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // add buffered record element to records vector
        records.push_back(record_buffer);
    }

    std::cout << "\nData is deserialized successfully.\n";

    file.close();
}

// AUXILIARY FUNCTION DEFINITIONS

void create_account(Account accounts[], int* accounts_size){
    accounts[*accounts_size].initialize();
    accounts[*accounts_size].add_record();
    (*accounts_size)++;
}

void get_local_date(int* day, int* month, int* year){
    time_t now = time(0);

    tm* date = localtime(&now);

    *day = date->tm_mday;
    *month = 1 + date->tm_mon;
    *year = 1900 + date->tm_year;
}

