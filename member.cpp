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

void Member::init_default_values(){
    // CASE 1 Initialization
    details.case1.expense = 0.0;
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
        std::cin >> details.case1.expense;

        std::cout << "\nAnd how much money did you give?: ";
        std::cin >> details.case1.bill;

        // calculate user change
        details.case1.change = details.case1.bill - details.case1.expense;

        break;
    }

    case 2: {
        std::cout << "Enter the amount paid: " << std::endl;
        std::cin >> details.case2.payment;
        std::cout << "Enter bill: " << std::endl;
        std::cin >> details.case2.bill;
        details.case2.payment_date = get_current_date();
        if (details.case2.bill >= details.case2.payment)
        {
            details.case2.contributed = true;
        }else details.case2.contributed = false;
        break;
    }

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
            std::cin.ignore();
            getline(std::cin, name);
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

        default: break;
    }
}

void Member::setCase2(int editCase){
    switch (editCase)
        {
        case 1:{
            std::cout << "Enter the new name: ";
            std::cin >> name;
            break;
        }

        case 2:{
            std::cout << "Enter the new payment: ";
            std::cin >> details.case2.payment;
            if (details.case2.bill >= details.case2.payment)
            {
                details.case2.contributed = true;
            }else details.case2.contributed = false;
            break;
        }

        case 3:{
            std::cout << "Enter the new bill: ";
            std::cin >> details.case2.bill;
            if (details.case2.bill >= details.case2.payment)
            {
                details.case2.contributed = true;
            }else details.case2.contributed = false;
            break;
        }

        case 4:{ 
            std::cout << "Enter month (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.month;
            std::cout << "Enter day (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.day;
            std::cout << "Enter year (in digits): " << std::endl;
            std::cin >> details.case2.payment_date.year;
            break;
        }

        case 5: return;
        default:
            break;
        }
}


void Member::display_details(int case_type){
    switch (case_type){
        case 1:
            std::cout << "\nName: " << name << std::endl; 
            std::cout << "Bill: " << details.case1.bill << std::endl;
            std::cout << "Expenses: " << details.case1.expense << std::endl;
            std::cout << "Change: " << details.case1.change << std::endl;
            break;

        case 2:
            std::cout << "\nName: " << name << std::endl; 
            std::cout << "Payment so far: " << details.case2.payment << std::endl;
            std::cout << "Bill: " << details.case2.bill << std::endl;
            std::cout << "Date: " << details.case2.payment_date.month_name << " " << details.case2.payment_date.day << details.case2.payment_date.year << std::endl;
            std::cout << "Contributed: " << details.case2.contributed << std::endl;
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

void Member::updateCase2(){
    char verify;
    do
    {
        int paymentUpdate;
        std::cout << "Enter the amount paid: " << std::endl;
        std::cin >> paymentUpdate;
        details.case2.payment += paymentUpdate;
        details.case2.payment_date = get_current_date();

        std::cout << "You entered: " << paymentUpdate << CURRENCY << std::endl;
        std::cout << "Total paid so far: " << details.case2.payment << CURRENCY << std::endl;
        std::cout << "Date today: " << details.case2.payment_date.month_name << " " << details.case2.payment_date.day << details.case2.payment_date.year << std::endl;
        std::cout << "Are all of the information correct? Enter Y if yes, N if no: " << std::endl;
        std::cin >> verify;
    } while (verify != 'Y');

}

void Member::contributed(){
    if (details.case2.contributed == true)
    {
        std::cout << name << std::endl;
    }
}

void Member::notContributed(){
    if (details.case2.contributed == false)
    {
        std::cout << name << std::endl;
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
    if ( !(file.read( (char *) &details.case1.expense, sizeof(double) ) ) ){
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
        if ( !(file.read( expense_note_buffer, sizeof(char) * name_size_b ) ) ){
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