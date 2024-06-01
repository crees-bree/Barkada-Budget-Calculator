// contains Account class functionalities

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "account.h"
#include "date.h"

#define INCOME 'i'
#define EXPENSE 'e'
#define TRANSFER 't'

#define DISPLAY_RECORD_COUNT 5
#define CURRENCY "Php"

// PRIVATE METHODS DEFINITIONS
 
char Account::select_record_type(){
    int selection;
    
    while (true){
        std::cout << "\n\nSelect record type:\n";
        std::cout << "1) Income\n";
        std::cout << "2) Expense\n";
        std::cin >> selection;

        std::cout << "\n";

        switch(selection){
            // select income
            case 1:
                return INCOME;
            // select expense
            case 2:
                return EXPENSE;
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
                continue;
        }
    }
}

void Account::add_to_records(Record record){
    std::vector<Record>::iterator iter;

    // if records is empty, just add the record
    if (records.empty()){
        records.push_back(record);
        return;
    }

    // insert record according to how new it is
    for (iter = records.begin(); iter != records.end(); ++iter){
        // if record date is younger than record in vector
        // insert the record before the record in vector
        if ((record.date >= iter->date) && iter != records.begin()){
            records.insert(iter, record);
            break;
        } 
        // add record at end of vector if we reach the end
        else if (iter == records.end() - 1){
            records.push_back(record);
            break;
        }
    }
}

void Account::display_record(Record record, bool account = false, bool select = false, int i = -1){
    std::string record_type_str;
    
    // display separator
    std::cout << std::endl << "-------------------------------" << std::endl;

    // display account name (optional)
    if (account) std::cout << "Account: " << account_name << std::endl;

    // display select index (for selection menu)
    if (select) std::cout << "RECORD #" << i << ":\n";

    if (record.record_type == EXPENSE) record.amount = record.amount - record.amount - record.amount;

    // display date
    printf("Date: %i/%i/%i\n", record.date.month, record.date.day, record.date.year);

    // display record type
    switch(record.record_type){
        case INCOME:
            record_type_str = "Income";
            break;
        case EXPENSE:
            record_type_str = "Expense";
            break;
        case TRANSFER:
            record_type_str = "Transfer";
        default:
            record_type_str = ""; // ERROR HANDLING (Unexpected value)
    }

    std::cout << "Record Type: " << record_type_str << std::endl;

    // display amount in two decimal places
    printf("Amount: %s %.2lf\n", CURRENCY, record.amount);

    // display category
    std::cout << "Category: " << record.category << std::endl;

    // display note
    std::cout << "Note: " << record.note << std::endl;
}

int Account::select_record_screen(){
    std::vector<Record>::iterator iter, prev;
    int total_pages, page = 0;
    int option, i;
    bool loop = true;

    // set iter to beginning of records
    iter = records.begin();

    // determine totasl number of pages
    total_pages = records.size() / DISPLAY_RECORD_COUNT;

    // add an extra page for the remaining records
    if (records.size() % DISPLAY_RECORD_COUNT != 0){
        ++total_pages;
    }

    while (page <= total_pages){  
        ++page;
        
        prev = iter;
        
        while (loop){
            i = 1;
            
            iter = prev;
            
            // display records up to specified number for each page
            for (; iter != records.end() && i <= 5; ++iter){
                display_record( *(iter) );
                ++i;
            }

            // display current page
            printf("\nDisplaying (%i) of (%i) pages\n", page, total_pages);

            std::cout << "Enter 0 to proceed to previous page\n";
            std::cout << "Enter 6 to proceed to next page\n";
            std::cout << "Enter -1 to exit\n\n";
            std::cin >> option;

            if (option >= 1 && option <= DISPLAY_RECORD_COUNT){
                return (DISPLAY_RECORD_COUNT * (page - 1)) + (option - 1);
            }
            // go back to previous page
            else if (option == 0){
                if (page == 1){
                    std::cout << "\nYou cannot go to previous page. Please try again.\n"; // ERROR HANDLING (Out of bounds)
                    continue;
                }
                
                iter = iter - ( (i - 1) + DISPLAY_RECORD_COUNT);
                page -= 2;

                break;
            }
            // proceed to next page
            else if (option == 6){
                if (page == total_pages){
                    std::cout << "\nYou cannot go to next page. Please try again.\n"; // ERROR HANDLING (Out of bounds)
                    continue;
                }
                
                break;
            }
            // exit select record screen
            else if (option == -1){
                return option;
            }
            else {
                std::cout << "\nInvalid input. Please try again.\n"; // ERROR HANDLING (Invalid user input)
            }
        }
    }   

    return -1;
}

void Account::update_balance(Record record, bool inverse = false){
    // add to balance if adding a new record,
    // subtract to balance if removing a record
    /*if (record.record_type == INCOME){
        balance = (inverse) ? balance - record.amount : balance + record.amount;
    } else if (record.record_type == EXPENSE){
        balance = (inverse) ? balance + record.amount : balance - record.amount;
    }*/

    balance = (inverse) ? balance - record.amount : balance + record.amount;
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

void Account::auto_initialize(std::string acc_name){
    account_name = acc_name;
    balance = 0;
}

std::string Account::get_account_name(){
    return account_name;
}

void Account::set_account_name(std::string acc_name){
    account_name = acc_name;
}

double Account::get_balance(){
    return balance;
}

void Account::set_balance(double bal, bool transfer_call){
    Record record_diff;
    double diff;
    char option;

    diff = balance - bal;

    if (diff > 0){
        record_diff.record_type = EXPENSE;
    } else if (diff < 0){
        record_diff.record_type = INCOME;
    } else {
        std::cout << "\nBalance didn't change. Returning to main menu...\n";
        return;
    }

    record_diff.date = get_current_date();
    record_diff.amount = diff - diff - diff;
    record_diff.category = "UPDATE BALANCE";
    record_diff.note = "";

    
    std::cout << "\nThe following record will be added to " << account_name << " to modify the balance\n";
    display_record(record_diff);
    std::cout << "\nEnter Y to proceed with the changes\n\n";

    std::cin >> option;

    if (option == 'Y'){
        add_to_records(record_diff);
        update_balance(record_diff);
    } else {
        std::cout << "\nModifying cancelled. Returning to main menu...\n";
    }
}

void Account::transfer_balance(double bal, bool current){
    Record record_diff;
    double diff;

    // calculate difference
    diff = balance - bal;

    // sets signs based on account location
    // if current is true (transferring from current account),
    // sets amount to negative (to subtract)
    // if current is false (transferring to new account),
    // sets amount to positive (to add)
    if ( (diff > 0 && current) || (diff < 0 && !current) ){
        diff = -diff;
    }

    // set transfer record details
    record_diff.date = get_current_date();
    record_diff.record_type = TRANSFER;
    record_diff.amount = diff;
    record_diff.category = "TRANSFERRED AMOUNT";

    // display what will be added to records to allow transfer
    std::cout << "\nThe following record will be added to " << account_name << " in transferring amount\n";
    display_record(record_diff);
    std::cout << std::endl;

    // add to records and update balance
    add_to_records(record_diff);
    update_balance(record_diff);

    return;

}

void Account::add_record(){
    Record record;
    int selection;
    char exit;
    bool loop = true;
    
    // set date automatically to current date
    record.date = get_current_date();

    // ask user to select a record type
    record.record_type = select_record_type();

    // ask user to enter amount
    std::cout << "Enter amount: ";
    std::cin >> record.amount;

    // essentially sets amount to negative if its an expense record
    record.amount = (record.record_type == INCOME) ? record.amount : record.amount - record.amount - record.amount;

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
    bool loop = true, loop2 = true;
    int selection;
    bool inverse_update;
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
                std::cout << "\nAre you sure that you want to discard your changes? (Enter Y to discard): ";
                std::cin >> exit;
                if (exit == 'Y'){
                    // break loop just in case
                    if (add_record == false){
                        add_to_records(record);
                        update_balance(record);
                    }

                    loop = false;
                }
                break;
            // modify date
            case 1:
                while (loop2){
                    std::cout << "Enter date (mm dd yyyy): ";
                    std::cin >> new_record.date.month;
                    std::cin >> new_record.date.day;
                    std::cin >> new_record.date.year;

                    if ( !date_is_valid(new_record.date) ){
                        std::cout << "\nInvalid date. Please try again.\n"; // ERROR HANDLING (Invalid input)
                        continue;
                    }

                    loop2 = false;
                }
                
                break;
            // modify record type
            case 2:
                new_record.record_type = select_record_type();
                
                if ( (new_record.record_type == INCOME && new_record.amount < 0) || 
                     (new_record.record_type == EXPENSE && new_record.amount > 0) ){
                    new_record.amount = new_record.amount - new_record.amount - new_record.amount;
                } 
                break;
            // modify amount
            case 3:
                std::cout << "Enter amount: ";
                std::cin >> new_record.amount;

                if (new_record.record_type == EXPENSE){
                    new_record.amount = new_record.amount - new_record.amount - new_record.amount;
                }
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
                    // condition when modifying an already existing record
                    if (add_record == false) {
                        // revert to previous balance value
                        update_balance(record, true);
                    }
                    add_to_records(new_record);

                    // update balance
                    update_balance(new_record);

                    loop = false;
                }
                
                break;
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
        }
    }
}

void Account::modify_record_screen(){
    Record buffer;
    int index;

    index = select_record_screen();

    if (index == -1){
        return;
    }

    // transfer record to be edited to buffer
    buffer = records[index];

    // delete unmodified record (so that we can sort the modified record)
    records.erase(records.begin() + index);
    
    // proceed with modifying
    modify_record(buffer);
}

void Account::delete_record(){
    int index;
    char option;

    index = select_record_screen();

    if (index == -1){
        return;
    }

    std::cout << "\nDo you want to delete this record?";

    display_record(records[index]);

    std::cout << "\nEnter Y to proceed\n";
    std::cout << "Enter anything else to cancel\n\n";
    std::cin >> option;

    if (option == 'Y'){
        update_balance(records[index], true);

        records.erase(records.begin() + index);
    }
}

void Account::display_records(){
    std::vector<Record>::iterator iter, prev;
    int total_pages, page = 0;
    int option;
    int count;
    bool loop;

    // initialize iter at start of records
    iter = records.begin();

    // set total no. of pages
    total_pages = records.size() / DISPLAY_RECORD_COUNT;

    // add an extra page for the remaining records
    if (records.size() % DISPLAY_RECORD_COUNT != 0){
        ++total_pages;
    }

    while (page <= total_pages){  
        loop = true;
        
        ++page;
        
        prev = iter;
        
        while (loop){
            count = 1;
            
            iter = prev;
            
            // display records up to specified number for each page
            for (; iter != records.end() && count <= 5; ++iter){
                display_record( *(iter) );
                ++count;
            }

            // display current page
            printf("\nDisplaying (%i) of (%i) pages\n", page, total_pages);

            std::cout << "Enter 1 to proceed to previous page\n";
            std::cout << "Enter 2 to proceed to next page\n";
            std::cout << "Enter 0 to exit\n\n";
            std::cin >> option;

            switch (option){
                // exit selection screen
                case 0:
                    return;
                // go back to previous page
                case 1:
                    if (page == 1){
                        std::cout << "\nYou cannot go to previous page. Please try again.\n"; // ERROR HANDLING (Out of bounds)
                        continue;
                    }
                    iter = iter - ( (count - 1) + DISPLAY_RECORD_COUNT);
                    page -= 2;
                    loop = false;
                    break;
                // go to next page
                case 2:
                    if (page == total_pages){
                        std::cout << "\nYou cannot go to next page. Please try again.\n"; // ERROR HANDLING (Out of bounds)
                        continue;
                    }
                    loop = false;
                    break;
                default:
                    std::cout << "\nInvalid input. Please try again.\n"; // ERROR HANDLING (Invalid user input)
                    continue;
            }
        }
    }   
}

void Account::filter_Percent_Records(Date start_date, Date end_date){
        std::vector<Record> filtered_records;
    for (size_t i = 0; i < filtered_records.size(); ++i) {
        const Record& record = filtered_records[i];
        if (record.date >= start_date && record.date <= end_date) {
            filtered_records.push_back(record);
        }
    }
    std::vector<std::pair<std::string, double>> category_expenses;
    for (size_t i = 0; i < filtered_records.size(); ++i) {
        if (filtered_records[i].record_type == 'e') {
            bool found = false;
            for (size_t j = 0; j < category_expenses.size(); ++j) {
                if (category_expenses[j].first == filtered_records[i].category) {
                    category_expenses[j].second += filtered_records[i].amount;
                    found = true;
                    break;
                }
            }
            if (!found) {
                category_expenses.push_back({filtered_records[i].category, filtered_records[i].amount});
            }
        }
    }

    double total_expenses = 0.0;
    for (int i = 0; i < category_expenses.size(); ++i) {
        total_expenses += category_expenses[i].second;
    }

    // Calculate and display percentage of expenses for each category
    std::cout << "Category\tPercentage\n";
    for (int i = 0; i < category_expenses.size(); ++i) {
        double percentage = (category_expenses[i].second / total_expenses) * 100.0;
        std::cout << category_expenses[i].first << "\t\t" << percentage << "%\n";
    }
}


void Account::serialize(std::string file_name){
    std::fstream file;

    // buffers
    int records_size_b = records.size();

    int account_name_size_b = account_name.size();
    int day_name_size_b;
    int month_name_size_b;
    int category_size_b;
    int note_size_b;

    file.open(file_name, std::ios::app | std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // serialize account name size
    if ( !(file.write( (char *) &account_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing account name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize account name
    if ( !(file.write( account_name.c_str(), sizeof(char) * account_name_size_b ) ) ){
        file.close();
        
        perror("Serializing account name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize balance
    if ( !(file.write( (char *) &balance, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing balance failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize records vector size
    if ( !(file.write( (char *) &records_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing records size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize records vector
    for (int i = 0; i < records_size_b; ++i){
        // initialize buffers
        day_name_size_b = records[i].date.day_name.size();
        month_name_size_b = records[i].date.month_name.size();
        category_size_b = records[i].category.size();
        note_size_b = records[i].note.size();
        
        // serialize date
        if ( !(file.write( (char *) &records[i].date.day, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing day failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( (char *) &day_name_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing day name size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( records[i].date.day_name.c_str(), sizeof(char) * day_name_size_b ) ) ){
            file.close();
            
            perror("Serializing day name failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( (char *) &records[i].date.month, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing month failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( (char *) &month_name_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing month name size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( records[i].date.month_name.c_str(), sizeof(char) * month_name_size_b ) ) ){
            file.close();
            
            perror("Serializing month name failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.write( (char *) &records[i].date.year, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing year failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize record type
        if ( !(file.write( &records[i].record_type, sizeof(char) ) ) ){
            file.close();
            
            perror("Serializing record type failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize amount
        if ( !(file.write( (char *) &records[i].amount, sizeof(double) ) ) ){
            file.close();
            
            perror("Serializing amount failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize category size
        if ( !(file.write( (char *) &category_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing category size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize category
        if ( !(file.write( records[i].category.c_str(), sizeof(char) * category_size_b ) ) ){
            file.close();
            
            perror("Serializing category failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize note size
        if ( !(file.write( (char *) &note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing category size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize category
        if ( !(file.write( records[i].note.c_str(), sizeof(char) * note_size_b ) ) ){
            file.close();
            
            perror("Serializing category failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }
    }

    file.close();
}

// reading :DDDDDDDDDDDDDDDDDD
void Account::deserialize(std::string file_name, long int* pos){
    std::ifstream file;

    // buffers
    char* account_name_buffer = NULL;
    char* day_name_buffer = NULL;
    char* month_name_buffer = NULL;
    char* category_buffer = NULL;
    char* note_buffer = NULL;

    int day_name_size_b;
    int month_name_size_b;
    int account_name_size_b;
    int records_size_b;
    int category_size_b;
    int note_size_b;

    file.open(file_name, std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // set file ptr position to when the program stopped reading previously
    file.seekg(*pos, std::ios::beg); 

    // deserialize account name size
    if ( !(file.read( (char *) &account_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Deserializing account name size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // allocate memory to account name buffer
    account_name_buffer = new char [account_name_size_b + 1];

    // deserialize account name
    if ( !(file.read( account_name_buffer, sizeof(char) * account_name_size_b ) ) ){
        file.close();
        
        perror("Deserializing account name failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // transfer account name buffer to account name 
    account_name_buffer[account_name_size_b] = '\0';

    account_name.assign(account_name_buffer, account_name_size_b);

    delete [] account_name_buffer;

    // deserialize balance
    if ( !(file.read( (char *) &balance, sizeof(double) ) ) ){
        file.close();
        
        perror("Deserializing balance failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector size
    if ( !(file.read( (char *) &records_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Deserializing records size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector
    for (int i = 0; i < records_size_b; ++i){
        // initialize buffers
        Record buffer;
        
        day_name_buffer = NULL;
        month_name_buffer = NULL;
        category_buffer = NULL;
        note_buffer = NULL;

        // deserialize date
        if ( !(file.read( (char *) &buffer.date.day, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing day failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.read( (char *) &day_name_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing day name size failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // allocate memory to day name buffer
        day_name_buffer = new char [day_name_size_b + 1];

        if ( !(file.read( day_name_buffer, sizeof(char) * day_name_size_b ) ) ){
            file.close();
            
            perror("Deserializing day name failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.read( (char *) &buffer.date.month, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing month failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.read( (char *) &month_name_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing month name size failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // allocate memory to month name buffer
        month_name_buffer = new char [month_name_size_b + 1];

        if ( !(file.read( month_name_buffer, sizeof(char) * month_name_size_b ) ) ){
            file.close();
            
            perror("Deserializing month name failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        if ( !(file.read( (char *) &buffer.date.year, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing year failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // deserialize record type
        if ( !(file.read( &buffer.record_type, sizeof(char) ) ) ){
            file.close();
            
            perror("Deserializing record type failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // deserialize amount
        if ( !(file.read( (char *) &buffer.amount, sizeof(double) ) ) ){
            file.close();
            
            perror("Deserializing amount failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // deserialize category size
        if ( !(file.read( (char *) &category_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing category size failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // allocate memory to category buffer
        category_buffer = new char [category_size_b + 1];

        // deserialize category
        if ( !(file.read( category_buffer, sizeof(char) * category_size_b ) ) ){
            file.close();
            
            perror("Deserializing category failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // deserialize note size
        if ( !(file.read( (char *) &note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing category size failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // allocate memory to note buffer
        note_buffer = new char [note_size_b + 1];

        // deserialize category
        if ( !(file.read( note_buffer, sizeof(char) * note_size_b ) ) ){
            file.close();
            
            perror("Deserializing category failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // transfer string buffers to their designated string variables
        day_name_buffer[day_name_size_b] = '\0';
        month_name_buffer[month_name_size_b] = '\0';
        category_buffer[category_size_b] = '\0';
        note_buffer[note_size_b] = '\0';

        buffer.date.day_name.assign(day_name_buffer, day_name_size_b);
        buffer.date.month_name.assign(month_name_buffer, month_name_size_b);
        buffer.category.assign(category_buffer, category_size_b);
        buffer.note.assign(note_buffer, note_size_b);

        delete [] day_name_buffer;
        delete [] month_name_buffer;
        delete [] category_buffer;
        delete [] note_buffer;

        // add read record to records
        records.push_back(buffer);
    }

    // update file ptr position to where the program last read file
    *pos = file.tellg();

    file.close();
}

bool Account::filter_by_date(Date date){
    bool found = false;
    
    for (auto record : records){
        if (date == record.date){
            display_record(record, true);

            if (!found) found = true;
        }
    }

    return found;
}

bool Account::filter_by_record_type(char record_type){
    bool found = false;
    
    for (auto record : records){
        if (record_type == record.record_type){
            display_record(record, true);

            if (!found) found = true;
        }
    }

    return found;
}

bool Account::filter_by_amount_range(double low, double high){
    bool found = false;
    
    for (auto record : records){
        if (record.amount >= low && record.amount <= high){
            display_record(record, true);

            if (!found) found = true;
        }
    }

    return found;
}

bool Account::filter_by_category(std::string category){
    bool found = false;
    
    for (auto record : records){
        if (category == record.category){
            display_record(record, true);

            if (!found) found = true;
        }
    }

    return found;
}



