// contains Member class functionalities

// you can refer to Account class functions implementation as a reference hehe

// FORMAT: details.case#.whatever_u_wanna_access

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "date.h"
#include "member.h"

#define CURRENCY "Php"

void Member::create_member(){
    std::cout<< "What is the name of the new member?: " << std::endl;
    std::cin >> name;
}

void Member::initialize(int case_type){               
    switch (case_type){
    case 1: {
        std::cout << "Hey " << name << ", what is your expense?: " << std::endl;
        std::cin >> details.case1.expense;

        std::cout << "And how much money did you give?: " << std::endl;
        std::cin >> details.case1.bill;

        // calculate user change
        details.case1.change = details.case1.bill - details.case1.expense;

        break;
    }

    case 2:

case 3: {
    char verify;
    do {
        std::cout << "How much is the budget you will allocate to " << name << "?" << std::endl;
        std::cin >> details.case3.budget;

        std::cout << "Are you sure with this budget? Enter Y if yes: ";
        std::cin >> verify;

    } while(verify != 'Y' && verify != 'y');

    std::cout << "Budget of " << CURRENCY << " " << details.case3.budget << " allocated to " << name << "." << std::endl;
    break;
}
    
    default:
        std::cout<< "Case Type Error!" << std::endl;
        break;
    }
}


bool Member::check_memName(std::string editName){
    int index;
    if (editName == name)
    {
        return true;
    }else return false;
}

void Member::setCase1(int editCase){
    switch (editCase)
            {
            case 1:{
                std::cout << "Enter the new name: ";
                std::cin >> name;
                break;
            }

            case 2:{
                std::cout << "Enter the new bill: ";
                std::cin >> details.case1.bill;
                details.case1.change = details.case1.bill - details.case1.expense;
                break;
            }

            case 3:{
                std::cout << "Enter the new expense: ";
                std::cin >> details.case1.expense;
                details.case1.change = details.case1.bill - details.case1.expense;
                break;
            }

            case 4: return;
            default:
                break;
            }
}

void Member::display_details(int case_type, int members_size){
    switch (case_type){
        case 1:
            for (int i = 0; i < members_size; i++){
                std::cout << "Name: " << name << std::endl; 
                std::cout << "Bill: " << details.case1.bill << std::endl;
                std::cout << "Expenses: " << details.case1.expense << std::endl;
                std::cout << "Change: " << details.case1.change << std::endl;
            }   
            break;
        case 2:
            break;
        case 3:
                if (details.case3.budget >= 0){
                    std::cout << " " << std::endl; 
                    std::cout << "Name: " << name << std::endl; 
                    std::cout << "Budget: " << CURRENCY << details.case3.budget << std::endl;
                } else {
                    std::cout << " " << std::endl; 
                    std::cout << "Name: " << name << " !! ATTENTION NEEDED !! " << std::endl; 
                    std::cout << "Budget: " << CURRENCY << details.case3.budget << std::endl;
                    std::cout << "WARNING! " << name << " has went over the budget limit." << std::endl;
                }
        break;
    default:
        break;
        }
}


// specific to case 1

// specific to case 2

// specific to case 3

void Member::addExpense(){
    double expenseAmount;
    std::string note;
    char confirm;

    std::cout << "Enter Expense Amount: ";
    std::cin >> expenseAmount;

    std::cout << "Enter a note for the expense: ";
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::getline(std::cin, note);

    std::cout << "You Entered:\n";
    std::cout << "Amount: " << expenseAmount << "\n";
    std::cout << "Note: " << note << "\n";
    std::cout << "Are you sure you want to add this expense? (y/n): ";
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        Expense newExpense;
        newExpense.expense_payment = expenseAmount;
        newExpense.note = note;

        details.case3.expenses.push_back(newExpense);
        details.case3.budget -= expenseAmount; 

        std::cout << "Expense added successfully.\n";
    } else {
        std::cout << "Expense not added.\n";
    }
}

void Member::displayMember() {
    std::cout << "---------------------\n";
    std::cout << "Member Name: " << name << "\n";
    std::cout << "Budget Left: " << details.case3.budget << "\n";
    
    if (details.case3.budget < 0) {
        std::cout << "Warning: Member is Over budget!" << std::endl;
    }
    
    std::cout << "Expenses:\n";
    
    for (const auto& expense : details.case3.expenses) {
        std::cout << "Amount: " << expense.expense_payment << ", Note: " << expense.note << "\n";
        std::cout << " " << std::endl; 
    }
    std::cout << "---------------------\n";
}

void Member::serialize(std::string file_name){
    std::fstream file;

    // buffers
    int name_size_b = name.size();

    int day_name_size_b = details.case2.payment_date.day;
    int month_name_size_b = details.case2.payment_date.month;

    int expenses_size_b = details.case3.expenses.size();
    int expense_note_size_b;

    file.open(file_name, std::ios::app | std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // serialize name size
    if ( !(file.write( (char *) &name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing member name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize name 
    if ( !(file.write( name.c_str(), sizeof(char) * name_size_b ) ) ){
        file.close();
        
        perror("Serializing member name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // CASE 1

    // serialize expense 
    if ( !(file.write( (char *) &details.case1.expense, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 expense failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize bill 
    if ( !(file.write( (char *) &details.case1.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 bill failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // no need to serialize change as it can be calculated

    // CASE 2

    // serialize payment date
    if ( !(file.write( (char *) &details.case2.payment_date.day, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &day_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( details.case2.payment_date.day_name.c_str(), sizeof(char) * day_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.payment_date.month, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &month_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( details.case2.payment_date.month_name.c_str(), sizeof(char) * month_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) details.case2.payment_date.year, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment year failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.payment, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 bill failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // no need to save contributed as it can be determined

    // CASE 3

    // serialize expenses size
    if ( !(file.write( (char *) &expenses_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 expenses size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize expenses
    for (int i = 0; i < expenses_size_b; ++i){
        expense_note_size_b = details.case3.expenses[i].note.size();
        
        // serialize expense payment
        if ( !(file.write( (char *) &details.case3.expenses[i].expense_payment, sizeof(double) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense payment failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize expense note size
        if ( !(file.write( (char *) &expense_note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize expense note
        if ( !(file.write( details.case3.expenses[i].note.c_str(), sizeof(char) * name_size_b ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }
    }

    // serialize budget
    if ( !(file.write( (char *) &details.case3.budget, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 budget failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    file.close();
}

void Member::deserialize(std::string file_name, long int* pos){
    std::fstream file;

    // buffers
    int name_size_b = name.size();

    int day_name_size_b = details.case2.payment_date.day;
    int month_name_size_b = details.case2.payment_date.month;

    int expenses_size_b = details.case3.expenses.size();
    int expense_note_size_b;

    file.open(file_name, std::ios::app | std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // serialize name size
    if ( !(file.write( (char *) &name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing member name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize name 
    if ( !(file.write( name.c_str(), sizeof(char) * name_size_b ) ) ){
        file.close();
        
        perror("Serializing member name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // CASE 1

    // serialize expense 
    if ( !(file.write( (char *) &details.case1.expense, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 expense failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize bill 
    if ( !(file.write( (char *) &details.case1.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 bill failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // no need to serialize change as it can be calculated

    // CASE 2

    // serialize payment date
    if ( !(file.write( (char *) &details.case2.payment_date.day, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &day_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( details.case2.payment_date.day_name.c_str(), sizeof(char) * day_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.payment_date.month, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &month_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( details.case2.payment_date.month_name.c_str(), sizeof(char) * month_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) details.case2.payment_date.year, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment year failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.payment, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.write( (char *) &details.case2.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 bill failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // no need to save contributed as it can be determined

    // CASE 3

    // serialize expenses size
    if ( !(file.write( (char *) &expenses_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 expenses size failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize expenses
    for (int i = 0; i < expenses_size_b; ++i){
        expense_note_size_b = details.case3.expenses[i].note.size();
        
        // serialize expense payment
        if ( !(file.write( (char *) &details.case3.expenses[i].expense_payment, sizeof(double) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense payment failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize expense note size
        if ( !(file.write( (char *) &expense_note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note size failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }

        // serialize expense note
        if ( !(file.write( details.case3.expenses[i].note.c_str(), sizeof(char) * name_size_b ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note failed"); // ERROR HANDLING (Data cannot be serialized)
            exit(EXIT_FAILURE);
        }
    }

    // serialize budget
    if ( !(file.write( (char *) &details.case3.budget, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 budget failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    file.close();
}