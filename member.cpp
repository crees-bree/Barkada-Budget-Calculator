// contains Member class functionalities

// you can refer to Account class functions implementation as a reference hehe

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
        CaseOne caseoh;            //variable name i love caseoh
        std::cout << "Hey " << name << ", what is your expense?: " << std::endl;
        std::cin >> caseoh.expense;

        std::cout << "And how much money did you give?: " << std::endl;
        std::cin >> caseoh.bill;

        // calculate user change
        caseoh.change = caseoh.bill - caseoh.expense;

        break;
    }

    case 2:

    case 3:
        CaseThree membah;
        char verify;
        std::cout << "How much is the budget you will allocate to " << name << "?" << std::endl;
        std::cin >> membah.budget;

        do{
            std::cout << "Are you sure with this budget? Enter Y if yes: ";
            std::cin >> verify;
                std::cin >> membah.budget;
        }while(verify != 'Y' && verify != 'y');

        // - chan: ako gi ilisdan ang P nimo into Php hehe
        std::cout << "Budget of " << CURRENCY << " " << membah.budget << " allocated to " << name << "." << std::endl;
        
        break;
    
    default:
        std::cout<< "Case Type Error!" << std::endl;
        break;
    }
}

void Member::edit_member(int case_type){

}

void Member::display_details(int case_type, int members_size){
    switch (case_type){
    case 1:
        for (int i = 0; i < members_size; i++)
        {
            // - chan
            // u can't use this way of printing
            // kay this isn't a general function
            // it's a function attached to the member variable (or object)s

            // so like what u can only do in this function is print the details of this member ra 
            // (like only for one member, which is kani)
            // no need to pass a Members array and iterate

            // also diay since naka private man ang name
            // kay u can't also do this using a general function
            // hence why this function exists, para maka access siya sa name
            
            // just remember lang na only functions sulod sa class
            // can access private variables of that class
            std::cout << "Name: " << name << std::endl; 
            std::cout << "Bill: ",  << std::endl;
        }   
        
        break;
    
    default:
        break;
    }
}

// specific to case 1

// specific to case 2

// specific to case 3