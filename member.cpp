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
                } else{
                    std::cout << " " << std::endl; 
                    std::cout << "Name: " << name << " !! ATTENTION NEEDED !! " << std::endl; 
                    std::cout << "Budget: " << CURRENCY << details.case3.budget << std::endl;
                    std::cout << "WARNING! " << name << " has went over the budget limit." << std::endl;
                }
            }
        break;
    
    default:
        break;
        }
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

}

void Member::deserialize(std::string file_name, long int* pos){
    
}