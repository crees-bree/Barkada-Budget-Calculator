// FUNCTION DECLARATIONS OF ACCOUNT.CPP
// ACCOUNT CLASS DECLARATION


#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>

#include "date.h"

// keeps track of expenses and income for each account in person mode
class Account{
    private:
        struct record{
            Date date; // stores date of the record
            char record_type; // 'i' for income, 'e' for expense, 't' for transfer
            double amount; // stores the amount of money that will modify the account balance
            std::string category; // stores which category does the record belong to
            std::string note; // stores the note that the user might input
        }; 
        typedef struct record Record;

        // stores the name of the account
        std::string account_name;
        
        // account balance
        double balance;

        // using C++'s built-in vector to store records
        std::vector<Record> records;

        // allows the user to pick record type (income, expense, transfer)
        char select_record_type();

        // adds a record to the records vector
        // automatically sorts it according to recency
        void add_to_records(Record);

        // display the contents of a singular record
        void display_record(Record, bool, bool, int);

        // select a record to proceed
        int select_record_screen();

        // updates balance after a record is added/removed
        void update_balance(Record, bool);

    public:
        // initialize account object
        void initialize();

        // automatically initialize account object
        // doesn't require user input
        void auto_initialize(std::string);

        // obtain account name
        std::string get_account_name();

        // set account name
        void set_account_name(std::string);

        // obtain account balance
        double get_balance();

        // add a new record that sets balance
        void set_balance(double, bool transfer_call = false);

        // transfer balance
        // current is set to true if the account is the current destination
        // current is set to false if the accounts is the new destination
        void transfer_balance(double, bool);
        
        // adds a new record to the records[] array
        void add_record();

        // modify a record
        void modify_record(Record, bool);

        // modify record selection screen
        void modify_record_screen();

        // display records (perhaps list 5 recent records)
        void display_records();

        // deletes a record
        void delete_record();

        // READING AND WRITING METHODS

        // convert object data to 
        void serialize(std::string);

        // convert to object data
        void deserialize(std::string, long int*);

        // FILTERING METHODS

        // display only records with specified date
        bool filter_by_date(Date);

        // display only records with specified type (income or expense)
        bool filter_by_record_type(char);

        // display only records with specified amount range
        bool filter_by_amount_range(double, double);

        // display only records with specified category
        bool filter_by_category(std::string);

};

// creates a new account
void create_account(Account[], int*);

#endif // ACCOUNT_H_