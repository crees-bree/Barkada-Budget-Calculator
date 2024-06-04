// BARKADA BUDGET CALCULATOR
// In Partial Completion for the Course CMSC 21

// Developers: Brillos, Christian C., Intern at UPC ITC
//             Lumbab, Jezreel Chad G., Senior Developer of Riot Games
//             Mijares, Jimmy Eleazar, Lead Developer of Roblox

// standard header files
#include <iostream>
#include <stdbool.h>
#include <windows.h>

// custom header files
#include "../lib/group_mode.h"
#include "../lib/person_mode.h"
#include "../lib/screen_util.h"

int main(){
    int option;
    char exit;
    bool loop = true;

    while (loop){
        print_ascii("main");

        std::cin >> option;

        switch(option){
            case 0:
                std::cout << "\nAre you sure you want to exit? (Enter Y to exit) ";
                std::cin >> exit;

                if (exit == 'Y') loop = false;

                break;
            case 1:
                loading("Loading PERSON MODE PROFILE SELECTION");
                person_mode();
                break;
            case 2:
                loading("Loading GROUP MODE PROFILE SELECTION");
                group_mode();
                break;
            default:
                pause_invalid();
                continue;
        }
    }

    return 0;
}


