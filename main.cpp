// BARKADA BUDGET CALCULATOR
// In Partial Completion for the Course CMSC 21

// Developers: Brillos, Christian C., Intern at UPC ITC
//             Lumbab, Jezreel Chad G., Senior Developer of Riot Games
//             Mijares, Jimmy Eleazar, Lead Developer of Roblox

// standard header files
#include <iostream>
#include <stdbool.h>

// custom header files
#include "group_mode.h"
#include "person_mode.h"


int main(){
    int option, status;
    char exit;
    bool loop = true;

    while (loop){
        std::cout << "\nBARKADA BUDGET CALCULATOR\n\n";
        std::cout << "Select a mode:\n";
        std::cout << "1) Person Mode\n";
        std::cout << "2) Group Mode\n";
        std::cout << "0) Exit\n\n";

        std::cin >> option;

        switch(option){
            case 0:
                std::cout << "\nAre you sure you want to exit? (Enter Y to exit) ";
                std::cin >> exit;
                if (exit == 'Y') loop = false;
                break;
            case 1:
                status = person_mode();
                break;
            case 2:
                status = group_mode();
                break;
            default:
                std::cout << "\nInvalid input. Please try again.\n";
                continue;
        }
    }

    return 0;
}


