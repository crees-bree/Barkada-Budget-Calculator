// FUNCTION DECLARATIONS OF MEMBER.CPP
// MEMBER CLASS DECLARATION

#ifndef MEMBER_H_
#define MEMBER_H_

#include <vector>

// DATE STRUCTURE
struct date{
    int day;
    int month;
    int year;
};
typedef struct date Date;

// keeps track of expenses and income for each member in group mode
class Member{
    private:
        // EXPENSE STRUCTURE
        struct expense{
            double expense_payment;
            double expense_bill;
        };
        typedef struct expense Expense;
        
        // CASE 1 STRUCTURE
        struct case_one{
            double expense;
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

        struct transaction{
            CaseOne case1;
            CaseTwo case2;
            CaseThree case3;
        };
        typedef struct transaction Transaction;

        // stores the name of the member
        std::string name;
        
    public:
        // GENERAL USE
        
        // this will execute if you want to create a new member
        void create_member();

        // initializes depending on what case the user is in
        void initialize(int);

        // edit member details
        void edit_member(int);

        // display member details
        void Member::display_details(int, int, Member);
        
        // CASE 1

        // CASE 2

        // CASE 3


        void serialize();
        void deserialize();
};

#endif // MEMBER_H_