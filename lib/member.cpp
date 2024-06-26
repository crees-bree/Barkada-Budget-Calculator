// contains Member class functionalities

// you can refer to Account class functions implementation as a reference hehe

// FORMAT: details.case#.whatever_u_wanna_access

#include <iostream>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>

#include "date.h"
#include "member.h"
#include "screen_util.h"

#define CURRENCY "Php"

void Member::init_default_values(){
    // CASE 1 Initialization
    details.case1.payment = 0.0;
    details.case1.bill = 0.0;
    details.case1.change = 0.0;

    // CASE 2 Initialization
    details.case2.payment_date.day = 0;
    details.case2.payment_date.day_name = "";
    details.case2.payment_date.month = 0;
    details.case2.payment_date.month_name = "";
    details.case2.payment_date.year = 0;
    details.case2.payment = 0.0;
    details.case2.bill = 0.0;

    // CASE 3 Initialization
    details.case3.budget = 0.0;
}

void Member::create_member(){
    // initialize values when creating a member
    init_default_values();
    
    std::cout<< "\nWhat is the name of the new member?: ";
    std::cin.ignore();
    getline(std::cin, name);
}

void Member::initialize(int case_type){               
    switch (case_type){
        case 1: {
            std::cout << "\nHey " << name << ", what is your bill?: ";
            std::cin >> details.case1.bill;

            std::cout << "\nAnd how much money did you give?: ";
            std::cin >> details.case1.payment;

            // calculate user change
            details.case1.change = details.case1.payment - details.case1.bill;

            if (details.case1.change < 0) details.case1.change = 0;

            break;
        }

        case 2: {
            std::cout << "\nEnter the amount paid: ";
            std::cin >> details.case2.payment;

            std::cout << "\nEnter bill: ";
            std::cin >> details.case2.bill;

            details.case2.payment_date = get_current_date();

            break;
        }

        case 3: {
            bool verify;

            do {
                std::cout << "\nHow much is the budget you will allocate to " << name << "? ";
                std::cin >> details.case3.budget;

                verify = !user_confirm("Are you sure with this budget?");

            } while(verify);

            std::cout << "\nBudget of " << CURRENCY << " " << details.case3.budget << " allocated to " << name << "." << std::endl;

            break;
        }
        
        default:
            std::cout<< "\nInvalid input. Returning to main menu...\n" << std::endl;
            Sleep(2000); // PAUSE WHEN RETURNING TO MAIN MENU
            break;
    }
}

void Member::display_details(int case_type){
    std::string cont;
    
    switch (case_type){
        case 1:
            std::cout << "\nName: " << name << std::endl; 
            std::cout << "Bill: " << CURRENCY << " " << details.case1.bill << std::endl;
            std::cout << "Payment: " << CURRENCY << " " << details.case1.payment << std::endl;
            std::cout << "Change: " << CURRENCY << " " << details.case1.change << std::endl;
            break;

        case 2:
            std::cout << "\nName: " << name << std::endl; 
            std::cout << "Payment so far: " << CURRENCY << " " << details.case2.payment << std::endl;
            std::cout << "Bill: " << CURRENCY << " " << details.case2.bill << std::endl;

            std::cout << "Date: ";
            if (details.case2.payment_date.day == 0 && details.case2.payment_date.year == 0){
                std::cout << "NONE" << std::endl;
            } else {
            std::cout << details.case2.payment_date.month_name << " " << details.case2.payment_date.day << " " << details.case2.payment_date.year << std::endl;
            }

            if (details.case2.payment >= details.case2.bill && details.case2.bill != 0){
                cont = "YES";
            } else if (details.case2.payment < details.case2.bill && details.case2.bill != 0){
                cont = "NO";
            } else if (details.case2.bill == 0){
                cont = "NOT INCLUDED";
            }
            std::cout << "Contributed: " << cont << std::endl;

            break;

        case 3:
            if (details.case3.budget >= 0){
                std::cout << " " << std::endl; 
                std::cout << "Name: " << name << std::endl; 
                std::cout << "Budget: " << CURRENCY << " " << details.case3.budget << std::endl;
            } else {
                std::cout << " " << std::endl; 
                std::cout << "Name: " << name << " !! ATTENTION NEEDED !! " << std::endl; 
                std::cout << "Budget: " << CURRENCY << " " << details.case3.budget << std::endl;
                std::cout << "WARNING! " << name << " has went over the budget limit." << std::endl;
            }
            break;

        default:
            break;
    }
}

bool Member::check_memName(std::string editName){
    if (editName == name) return true;
    else return false;
}

// specific to case 1

void Member::setCase1(int editCase){
    switch (editCase)
        {
        case 1:{
            std::cout << "\nEnter the new name: ";
            std::cin.ignore();
            getline(std::cin, name);
            break;
        }

        case 2:{
            std::cout << "\nEnter the new bill: ";
            std::cin >> details.case1.bill;

            // update change
            details.case1.change = details.case1.payment - details.case1.bill;

            if (details.case1.change < 0) details.case1.change = 0;

            break;
        }

        case 3:{
            std::cout << "\nEnter the new payment: ";
            std::cin >> details.case1.payment;

            // update change
            details.case1.change = details.case1.payment - details.case1.bill;

            if (details.case1.change < 0) details.case1.change = 0;

            break;
        }

        case 4:{
            loading("Returning to menu");
            return;
        }

        default: break;
    }
}

void Member::display_name_and_change(){
    std::cout << "\nName: " << name << std::endl; 
    std::cout << "Change: " << CURRENCY << " " << details.case1.change << std::endl;
}

int Member::getBill(){
    int bill = details.case1.bill;
    return bill;
}

int Member::getPayment(){
    int payment = details.case1.payment;
    return payment;
}

// specific to case 2

void Member::setCase2(int editCase){
    switch (editCase)
        {
        case 1:{
            std::cout << "\nNote that after editing the name, cannot edit further details since the name of the member is now different" << std::endl;

            std::cout << "Enter the new name: ";
            std::cin.ignore();
            getline(std::cin, name);

            break;
        }

        case 2:{
            std::cout << "\nEnter the new payment: ";
            std::cin >> details.case2.payment;
            break;
        }

        case 3:{
            std::cout << "\nEnter the new bill: ";
            std::cin >> details.case2.bill;
            break;
        }

        case 4:{ 
            std::cout << "\nEnter month (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.month;
            std::cout << "Enter day (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.day;
            std::cout << "Enter year (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.year;
            break;
        }

        case 0: 
            return;

        default:
            break;
        }
}

void Member::updateCase2(){
    bool verify;

    do
    {
        int paymentUpdate;
        std::cout << "\nEnter the amount paid: ";
        std::cin >> paymentUpdate;
        
        details.case2.payment += paymentUpdate;
        details.case2.payment_date = get_current_date();

        std::cout << "\nYou entered: " << CURRENCY << " " << paymentUpdate << std::endl;
        std::cout << "Total paid so far: " << CURRENCY << " " << details.case2.payment << std::endl;
        std::cout << "Date today: " << details.case2.payment_date.month_name << " " << details.case2.payment_date.day << " " << details.case2.payment_date.year << std::endl;
        
        verify = !user_confirm("Are all of the information correct?");
    } while (verify);

    loading("Returning to menu");
}

void Member::contributed(){
    if (details.case2.payment >= details.case2.bill && details.case2.bill != 0)
    {
        std::cout << std::endl << name << std::endl;
    }
}

void Member::notContributed(){
    if (details.case2.payment < details.case2.bill && details.case2.bill != 0)
    {
        std::cout << std::endl << name << std::endl;
    }
}

void Member::not_included_in_contributed(){
    if (details.case2.bill == 0){
        std::cout << std::endl << name << std::endl;
    }
}

// specific to case 3

void Member::addExpense(){
    double expenseAmount;
    std::string note;

    std::cout << "\nEnter Expense Amount: ";
    std::cin >> expenseAmount;

    std::cout << "\nEnter a note for the expense: ";
    std::cin.ignore(); // To ignore the newline character left in the buffer
    std::getline(std::cin, note);

    std::cout << "\nYou Entered:\n";
    std::cout << "Amount: " << expenseAmount << "\n";
    std::cout << "Note: " << note << "\n";


    if ( user_confirm("Are you sure you want to add this expese?") ) {
        Expense newExpense;

        newExpense.expense_payment = expenseAmount;
        newExpense.note = note;

        details.case3.expenses.push_back(newExpense);
        details.case3.budget -= expenseAmount; 

        loading("Expense added successfully. Returning to main menu");
    } else {
        loading("Expense not added. Returning to main menu");
    }
}

void Member::displayMember() {
    std::cout << "---------------------\n";
    std::cout << "Member Name: " << name << "\n";
    std::cout << "Budget Left: " << CURRENCY << " " << details.case3.budget << "\n";
    
    if (details.case3.budget < 0) {
        std::cout << "Warning: Member is Over budget!" << std::endl;
    }
    
    std::cout << "Expenses:\n";
    
    for (const auto& expense : details.case3.expenses) {
        std::cout << "Amount: " << CURRENCY << " " << expense.expense_payment << ", Note: " << expense.note << "\n";
        std::cout << " " << std::endl; 
    }
    std::cout << "---------------------\n";
}

void Member::add_budget(){
    if (details.case3.budget > 0){
        loading("This member already has a budget. Returning to main menu");
        return;
    }


    std::cout << "\nEnter budget: ";
    std::cin >> details.case3.budget;

    details.case3.expenses.clear();
}

void Member::serialize(std::string file_name){
    std::fstream file;

    // buffers
    int name_size_b = name.size();

    int day_name_size_b = details.case2.payment_date.day_name.size();
    int month_name_size_b = details.case2.payment_date.month_name.size();

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
    if ( !(file.write( (char *) &details.case1.payment, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 payment failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize bill 
    if ( !(file.write( (char *) &details.case1.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 bill failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

    // serialize change
    if ( !(file.write( (char *) &details.case1.change, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 change failed"); // ERROR HANDLING (Data cannot be serialized)
        exit(EXIT_FAILURE);
    }

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

    if ( !(file.write( (char *) &details.case2.payment_date.year, sizeof(int) ) ) ){
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
    std::ifstream file;

    // buffers
    char* name_buffer = NULL;
    int name_size_b;

    char* day_name_buffer = NULL;
    char* month_name_buffer = NULL;
    int day_name_size_b;
    int month_name_size_b;

    int expenses_size_b;
    char* expense_note_buffer = NULL;
    int expense_note_size_b;

    file.open(file_name, std::ios::binary);

    if ( file.fail() ){
        perror("Initialization failed"); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    } 

    // set file ptr position to when the program stopped reading previously
    file.seekg(*pos, std::ios::beg); 

    // deserialize name size
    if ( !(file.read( (char *) &name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing member name size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    name_buffer = new char [name_size_b + 1];

    // deserialize name 
    if ( !(file.read( name_buffer, sizeof(char) * name_size_b ) ) ){
        file.close();
        
        perror("Serializing member name failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // CASE 1

    // deserialize expense 
    if ( !(file.read( (char *) &details.case1.payment, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 expense failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // deserialize bill 
    if ( !(file.read( (char *) &details.case1.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 bill failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // deserialize change
    if ( !(file.read( (char *) &details.case1.change, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 1 change failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // CASE 2

    // deserialize payment date
    if ( !(file.read( (char *) &details.case2.payment_date.day, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &day_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    day_name_buffer = new char [day_name_size_b + 1];

    if ( !(file.read( day_name_buffer, sizeof(char) * day_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment day name failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &details.case2.payment_date.month, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &month_name_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    month_name_buffer = new char [month_name_size_b + 1];

    if ( !(file.read( month_name_buffer, sizeof(char) * month_name_size_b ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment month name failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &details.case2.payment_date.year, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment year failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &details.case2.payment, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 payment failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    if ( !(file.read( (char *) &details.case2.bill, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 2 bill failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // no need to save contributed as it can be determined

    // CASE 3

    // deserialize expenses size
    if ( !(file.read( (char *) &expenses_size_b, sizeof(int) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 expenses size failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }

    // deserialize expenses
    for (int i = 0; i < expenses_size_b; ++i){
        Expense buffer;
        
        // deserialize expense payment
        if ( !(file.read( (char *) &buffer.expense_payment, sizeof(double) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense payment failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        // deserialize expense note size
        if ( !(file.read( (char *) &expense_note_size_b, sizeof(int) ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note size failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        expense_note_buffer = new char [expense_note_size_b + 1];

        // deserialize expense note
        if ( !(file.read( expense_note_buffer, sizeof(char) * expense_note_size_b ) ) ){
            file.close();
            
            perror("Serializing CASE 3 expense note failed"); // ERROR HANDLING (Data cannot be deserialized)
            exit(EXIT_FAILURE);
        }

        expense_note_buffer[expense_note_size_b] = '\0';

        buffer.note.assign(expense_note_buffer, expense_note_buffer);

        delete [] expense_note_buffer;

        details.case3.expenses.push_back(buffer);
    }

    // deserialize budget
    if ( !(file.read( (char *) &details.case3.budget, sizeof(double) ) ) ){
        file.close();
        
        perror("Serializing CASE 3 budget failed"); // ERROR HANDLING (Data cannot be deserialized)
        exit(EXIT_FAILURE);
    }
    
    name_buffer[name_size_b] = '\0';
    day_name_buffer[day_name_size_b] = '\0';
    month_name_buffer[month_name_size_b] = '\0';

    name.assign(name_buffer, name_size_b);
    details.case2.payment_date.day_name.assign(day_name_buffer, day_name_size_b);
    details.case2.payment_date.month_name.assign(month_name_buffer, month_name_size_b);

    delete [] name_buffer;
    delete [] day_name_buffer;
    delete [] month_name_buffer;

    // update file ptr position to where the program last read file
    *pos = file.tellg();

    file.close();
}