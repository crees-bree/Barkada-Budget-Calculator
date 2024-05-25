// contains Account class functionalities

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include "account.h"

#define INCOME 'i'
#define EXPENSE 'e'
#define TRANSFER 't'

#define DISPLAY_RECORD_COUNT 20

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
                return INCOME;
            // select expense
            case 2:
                return EXPENSE;
            // select transfer
            case 3:
                return TRANSFER;
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
                continue;
        }
    }
}

void Account::add_to_records(Record record){
    std::vector<Record>::iterator iter;

    // insert record according to how new it is
    for (iter = records.begin(); iter != records.end(); ++iter){
        // if record date is younger than record in vector
        // insert the record before the record in vector
        if (record.date >= iter->date){
            records.insert(iter - 1, record);
            break;
        } // add record at end of vector if we reach the end
        else if (iter == records.end() - 1){
            records.push_back(record);
        }
    }
}

void Account::display_record(Record record){
    std::string record_type_str;
    
    // display separator
    std::cout << std::endl << "-------------------------------" << std::endl;

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

void Account::update_balance(Record record, bool inverse = false){
    // add to balance if adding a new record,
    // subtract to balance if removing a record
    if (record.record_type == INCOME){
        balance = (inverse) ? balance - record.amount : balance + record.amount;
    } else if (record.record_type == EXPENSE){
        balance = (inverse) ? balance + record.amount : balance - record.amount;
    }
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
                        add_to_records(new_record);

                        inverse_update = true;
                    } else {
                        // save newly edited record
                        record = new_record;

                        inverse_update = true;
                    }
                    // update balance
                    update_balance(new_record, inverse_update);

                    loop = false;
                }
                
                break;
            default:
                std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
        }
    }
}

void Account::display_records(){
    std::vector<Record>::iterator iter;
    int total_pages = records.size() / DISPLAY_RECORD_COUNT;
    int option;

    // add an extra page for the remaining records
    if (records.size() % DISPLAY_RECORD_COUNT != 0){
        ++total_pages;
    }

    for (int page = 1; page <= total_pages; ++page){
        for (iter = records.begin(); iter != records.end() && iter != (iter + DISPLAY_RECORD_COUNT); ++iter){
            display_record( *(iter) );
        }

        printf("\nDisplaying (%i) of (%i) pages\n", page, total_pages);

        if (page == total_pages){
            break;
        }

        std::cout << "\nDo you want to go to the next page? (Enter Y to proceed)" << std::endl;
        std::cin >> option;

        if (option != 'Y'){
            break;
        }
    }    
}

// writing :D
void Account::serialize(std::string file_name){
    std::ofstream file;

    account_name = "paul";

    // buffers
    int records_size_b = records.size();

    int account_name_size_b = account_name.size();
    int category_size_b;
    int note_size_b;


    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::binary | std::ios::trunc);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // serialize account name size
    if ( !(file.write( (char *) &account_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing account name size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize account name
    if ( !(file.write( account_name.c_str(), sizeof(char) * account_name_size_b ) ) ){
        file.close();
        
        perror("Serializing account name failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize balance
    if ( !(file.write( (char *) &balance, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing balance failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize records vector size
    if ( !(file.write( (char *) &records_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing records size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // serialize records vector
    for (int i = 0; i < records_size_b; ++i){
        // initialize buffers
        category_size_b = records[i].category.size();
        note_size_b = records[i].note.size();
        
        // serialize date
        if ( !(file.write( (char *) &records[i].date, sizeof(Date) ) ) ){
            file.close();
            
            perror("Serializing date failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize record type
        if ( !(file.write( &records[i].record_type, sizeof(char) ) ) ){
            file.close();
            
            perror("Serializing record type failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize amount
        if ( !(file.write( (char *) &records[i].amount, sizeof(double) ) ) ){
            file.close();
            
            perror("Serializing amount failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize category size
        if ( !(file.write( (char *) &category_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing category size failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize category
        if ( !(file.write( records[i].category.c_str(), sizeof(char) * category_size_b ) ) ){
            file.close();
            
            perror("Serializing category failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize note size
        if ( !(file.write( (char *) &note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing category size failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // serialize category
        if ( !(file.write( records[i].note.c_str(), sizeof(char) * note_size_b ) ) ){
            file.close();
            
            perror("Serializing category failed"); // ERROR HANDLING (File cannot be opened)
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
    char* account_name_buffer = NULL;
    char* category_buffer = NULL;
    char* note_buffer = NULL;

    int account_name_size_b;
    int records_size_b;
    int category_size_b;
    int note_size_b;

    file.open(file_name, std::ios::in | std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // deserialize account name size
    if ( !(file.read( (char *) &account_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Deserializing account name size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    account_name_buffer = new char [account_name_size_b + 1];

    // deserialize account name
    if ( !(file.read( account_name_buffer, sizeof(char) * account_name_size_b ) ) ){
        file.close();
        
        perror("Deserializing account name failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    account_name_buffer[account_name_size_b] = '\0';

    account_name.assign(account_name_buffer, account_name_size_b);

    delete [] account_name_buffer;

    // deserialize balance
    if ( !(file.read( (char *) &balance, sizeof(double) ) ) ){
        file.close();
        
        perror("Deserializing balance failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector size
    if ( !(file.read( (char *) &records_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Deserializing records size failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // deserialize records vector
    for (int i = 0; i < records_size_b; ++i){
        // initialize buffers
        Record buffer;

        category_buffer = NULL;
        note_buffer = NULL;

        // deserialize date
        if ( !(file.read( (char *) &buffer.date, sizeof(Date) ) ) ){
            file.close();
            
            perror("Deserializing date failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // deserialize record type
        if ( !(file.read( &buffer.record_type, sizeof(char) ) ) ){
            file.close();
            
            perror("Deserializing record type failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // deserialize amount
        if ( !(file.read( (char *) &buffer.amount, sizeof(double) ) ) ){
            file.close();
            
            perror("Deserializing amount failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // deserialize category size
        if ( !(file.read( (char *) &category_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing category size failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        category_buffer = new char [category_size_b + 1];

        // deserialize category
        if ( !(file.read( category_buffer, sizeof(char) * category_size_b ) ) ){
            file.close();
            
            perror("Deserializing category failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        // deserialize note size
        if ( !(file.read( (char *) &note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Deserializing category size failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        note_buffer = new char [note_size_b + 1];

        // deserialize category
        if ( !(file.read( note_buffer, sizeof(char) * note_size_b ) ) ){
            file.close();
            
            perror("Deserializing category failed"); // ERROR HANDLING (File cannot be opened)
            exit(EXIT_FAILURE);
        }

        category_buffer[category_size_b] = '\0';
        note_buffer[note_size_b] = '\0';

        buffer.category.assign(category_buffer, category_size_b);
        buffer.note.assign(note_buffer, note_size_b);

        delete [] category_buffer;
        delete [] note_buffer;

        records.push_back(buffer);

        std::cout << buffer.category.size() << std::endl;
    }

    std::cout << "\nData is deserialized successfully.\n";

    file.close();
}

void Account::filter_by_date(Date date){s
    for (auto record : records){
        if (date == record.date){
            display_record(record);
        }
    }
}

// AUXILIARY FUNCTION DEFINITIONS

void create_account(Account accounts[], int* accounts_size){
    accounts[*accounts_size].initialize();
    accounts[*accounts_size].add_record(); // may not be included
    (*accounts_size)++;
}


