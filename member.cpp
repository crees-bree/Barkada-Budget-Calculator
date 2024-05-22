// contains Member class functionalities

#include <iostream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#include "member.h"

void Member::create_member(){
    std::cout<< "What is the name of the new member?: " << std::endl;
    std::cin >> name;
}

void Member::initialize(int case_type){                 //changed case to case_type since case is a reserved keyword
    switch (case_type)
    {
    case 1: {
        CaseOne caseoh;            //variable name i love caseoh
        std::cout<< "Hey " << name << ", what is your expense?: " << std::endl;
        std::cin >> caseoh.expense;
        std::cout<< "And how much money did you give?: " << std::endl;
        std::cin >> caseoh.bill;
        caseoh.change = caseoh.bill - caseoh.expense;
        break;
    }

    case 2:

    
    default:
        std::cout<< "Case Type Error!" << std::endl;
        break;
    }
}

void Member::edit_member(int case_type){

}

void Member::display_details(int case_type, int members_size, Member members){
    switch (case_type)
    {
    case 1:
        for (int i = 0; i < members_size; i++)
        {
            std::cout<< "Name: ", members[i].name;              //not sure why mag error siya
            std::cout<< "Bill: ", members[i].
        }   
        
        break;
    
    default:
        break;
    }
}

// specific to case 1

// specific to case 2

// specific to case 3