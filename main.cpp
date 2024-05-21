// BARKADA BUDGET CALCULATOR
// In Partial Completion for the Course CMSC 21

// Developers: Brillos, Christian C., Intern at UPC ITC
//             Lumbab, Jezreel Chad G., Senior Developer at Microsoft
//             Mijares, Jimmy Eleazar, Lead Developer at Riot Games

// standard header files
#include <iostream>
#include <stdbool.h>

// custom header files
#include "group_mode.h"
#include "person_mode.h"

int main(){
    int option;

    while (true){
        printf("BARKADA BUDGET CALCULATOR\n\n");
        printf("Select a mode:\n");
        printf("1) Person Mode\n");
        printf("2) Group Mode\n");
        printf("0) Exit\n");

        std::cin >> option;

        switch(option){
            case 0:
                return 0;
            case 1:
                person_mode();
                break;
            case 2:
                group_mode();
                break;
            default:
                printf("Invalid input. Please try again.\n\n");
                continue;
        }
    }
}

