// FUNCTION DECLARATIONS OF MEMBER.CPP
// MEMBER CLASS DECLARATION

#ifndef MEMBER_H_
#define MEMBER_H_

#include <vector>

#include "date.h"

// keeps track of expenses and income for each member in group mode
class Member{
    private:
        // EXPENSE STRUCTURE
        struct expense{
            double expense_payment;
            std::string note;
        };
        typedef struct expense Expense;
        
        // CASE 1 STRUCTURE
        struct case_one{
            double payment;
            double bill;
            double change;
        };
        typedef struct case_one CaseOne;

        // CASE 2 STRUCTURE
        struct case_two{
            Date payment_date;
            double payment;
            double bill;
            bool contributed;
        };
        typedef struct case_two CaseTwo;

        // CASE 3 STRUCTURE
        struct case_three{
            std::vector<Expense> expenses;
            double budget;
        };
        typedef struct case_three CaseThree;

        struct memberdetails{ 
            CaseOne case1;
            CaseTwo case2;
            CaseThree case3;
        };
        typedef struct memberdetails MemberDetails;

        // store necessary details of member object
        MemberDetails details;

        // stores the name of the member
        std::string name;
        
    public:
        // GENERAL USE
        
        // initialize details to their default values (to prevent any errors in saving/display)
        void init_default_values();

        // this will execute if you want to create a new member
        void create_member();

        // initializes depending on what case the user is in
        void initialize(int);

        // display member details
        void display_details(int);

        // to iterate which member you want to edit
        bool check_memName(std::string);  

        // CASE 1

        //This is for accessing the values inside the class so we can edit
        void setCase1(int);

        // CASE 2

        void updateCase2();

        void setCase2(int);

        void contributed();

        void notContributed();

        // CASE 3

        void addExpense();
        
        void displayMember();

        // READING AND WRITING METHODS
        
        // convert object data to binary data
        void serialize(std::string);

        // convert binary data to object data
        void deserialize(std::string, long int*);
};

#endif // MEMBER_H_