// BARKADA BUDGET CALCULATOR
// In Partial Completion for the Course CMSC 21

// Developers: Brillos, Christian C., Intern at UPC ITC
//             Lumbab, Jezreel Chad G., Senior Developer of Riot Games
//             Mijares, Jimmy Eleazar, Lead Developer of Roblox

// standard header files
#include <iostream>
//#include <ncurses/ncurses.h>
#include <stdbool.h>

// custom header files
#include "group_mode.h"
#include "person_mode.h"

int main(){
    int option, exit;
    bool loop = true;

    //initscr();

    while (loop){

        printf("BARKADA BUDGET CALCULATOR\n\n");
        printf("Select a mode:\n");
        printf("1) Person Mode\n");
        printf("2) Group Mode\n");
        printf("0) Exit\n");

        std::cin >> option;

        switch(option){
            case 0:
                loop = false;
                break;
            case 1:
                exit = person_mode();
                break;
            case 2:
                exit = group_mode();
                break;
            default:
                std::cout << "\nInvalid input. Please try again.\n";
                continue;
        }
    }

    //endwin();
}

