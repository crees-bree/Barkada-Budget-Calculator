// FUNCTION DECLARATIONS OF ACCOUNT.CPP
// ACCOUNT CLASS DECLARATION


#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>

// DATE STRUCTURE
struct date{
    int day;
    int month;
    int year;
};
typedef struct date Date;

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

        // person bill (for group mode)

        // using C++'s built-in vector to store records
        std::vector<Record> records;

        // allows the user to pick record type (income, expense, transfer)
        char select_record_type();

        // display the contents of a singular record
        void display_record(Record record);

        // updates balance after a record is added/removed
        void update_balance(Record, int);

    public:
        // initialize account object
        void initialize();
        
        // adds a new record to the records[] array
        void add_record();

        // modify a record
        void modify_record(Record, bool);

        // display records (perhaps list 20 recent records)
        void display_records();

        // convert object data to 
        void serialize(std::string);

        // convert to object data
        void deserialize(std::string);
};

// creates a new account
void create_account(Account[], int*);

#endif // ACCOUNT_H_