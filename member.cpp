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
            // nachange na nako chad hehe mb
            // awa sa pinakataas ang formatting para ma guide-an
            std::cout << "Name: " << name << std::endl; 
            std::cout << "Bill: " << details.case1.bill << std::endl;
        }   
        break;
    case 2:
        break;
    case 3:
        for (int i = 0; i < members_size; i++)
        {
            if(details.case3.budget >= 0){
                std::cout << "Name: " << name << std::endl; 
                std::cout << "Budget: " << CURRENCY << details.case3.budget << std::endl;
            }
            else{
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

// specific to case 1

// specific to case 2

// specific to case 3