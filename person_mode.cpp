// contains all functionalities for person mode

// NOTES:

// In person mode, a user can add, modify, and delete a record


#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <vector>

void get_local_date(int*, int*, int*);

class Account{
    private:
        struct date{
            int day;
            int month;
            int year;
        };
        typedef struct date Date;

        struct record{
            Date date;
            char record_type; // 'i' for income, 'e' for expense, 't' for transfer
            double amount;
            std::string category;
            std::string note;
        };
        typedef struct record Record;

        // account balance
        double balance = 0;

        // using C++'s built-in vector to store records
        std::vector<Record> records;

        char select_record_type(){
            int selection;
            
            while (true){
                std::cout << "Select record type:\n";
                std::cout << "1) Income\n";
                std::cout << "2) Expense\n";
                std::cout << "3) Transfere\n";
                std::cin >> selection;

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

        void display_record(Record record){
            std::string record_type_str;
            
            // display date
            printf("Date: %i/%i/%i\n", record.date.month, record.date.day, record.date.year);

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

        void update_balance(){

        }
    public:
        // adds a new record to the records[] array
        void add_record(){
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
            while (loop){
                // display inputted record details
                display_record(record);

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
                        std::cout << "Enter date (mm md yyy): ";
                        std::cin >> record.date.month;
                        std::cin >> record.date.day;
                        std::cin >> record.date.year;

                        break;

                    // modify record type
                    case 2:
                        record.record_type = select_record_type();

                        break;

                    // modify amount
                    case 3:
                        std::cout << "Enter amount: ";
                        std::cin >> record.amount;

                        break;

                    // modify category
                    case 4:
                        std::cout << "Enter category: ";
                        std::cin >> record.category;

                        break;

                    // modify note
                    case 5:
                        std::cout << "Enter note (input NONE to leave as blank): ";
                        getline(std::cin, record.note);

                        if (record.note == "NONE"){
                            record.note = "";
                        }

                        break;

                    // save record
                    case 6:
                        std::cout << "\nAre you sure that you want to save this record? (Enter Y to save): ";
                        std::cin >> exit;

                        if (exit == 'Y'){
                            // add new record to records vector after the last element in the vector
                            records.push_back(record);
                            
                            loop = false;
                        }
                        
                        break;
                        
                    default:
                        std::cout << "Invalid input. Please try again\n"; // ERROR HANDLING (Invalid user input)
                }
            }
        }

        // modify a record
        void modify_record(){
            
        }

        // display records (perhaps list 20 recent records)
        void display_records(){

        }
};

int person_mode(){
    Account account;

    account.add_record();
}

// get current day, month, and year
// formatting: months as numbers, years as 4-digit numbers
void get_local_date(int* day, int* month, int* year){
    time_t now = time(0);

    tm* date = localtime(&now);

    *day = date->tm_mday;
    *month = 1 + date->tm_mon;
    *year = 1900 + date->tm_year;
}


