// FUNCTION DECLARATIONS OF ACCOUNT.CPP
// ACCOUNT CLASS DECLARATION


#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>

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
        void add_to_records(Record record);

        // display the contents of a singular record
        void display_record(Record record);

        // updates balance after a record is added/removed
        void update_balance(Record, bool);

    public:
        // initialize account object
        void initialize();

        // automatically initialize account object
        // doesn't require user input
        void auto_initialize(std::string);

        // display account name and balance
        
        // adds a new record to the records[] array
        void add_record();

        // modify a record
        void modify_record(Record, bool);

        // display records (perhaps list 20 recent records)
        void display_records();

        void delete_record();

        // READING AND WRITING METHODS

        // convert object data to 
        void serialize(std::string);

        // convert to object data
        void deserialize(std::string);

        // FILTERING METHODS

        // display only records with specified date
        void filter_by_date(Date);

};

// creates a new account
void create_account(Account[], int*);

#endif // ACCOUNT_H_