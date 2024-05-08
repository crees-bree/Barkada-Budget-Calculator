// contains all functionalities necessary for managing profiles

// NOTES:
// - file format of a profile file: Profiles/<MODE>/<M>-<PROFILE_NAME>.txt
//                                  <MODE>: Person / Group
//                                  <M>   : p / g
//                                  e.g. Profiles/Person/p-SirNasvin.txt

#include <iostream>
#include <string>

#include "profile.h"


// asks user to add, open, and delete profiles
void profile_selection(FILE* profile, char profile_mode, std::string* file_name){
    int option;

    while (true){
        printf("PROFILE SELECTION MENU\n\n");
        
        // display list of profiles saved in directory
        //display_profiles(profile_mode);
        printf("Display\n");

        printf("What do you want to do?\n");
        printf("1) Create New Profile\n");
        printf("2) Open Profile\n");
        printf("3) Delete Profile\n");
        printf("0) Exit\n");

        std::cin >> option;

        switch (option){
            case 0:
                return;
            case 1:
                add_profile(profile, profile_mode);
                break;
            case 2:
                open_profile(profile, profile_mode);
                break;
            case 3:
                delete_profile(profile, profile_mode);
                break;
            default:
                printf("Invalid input. Please try again.\n");
                continue;
        }
    }
}

// adds a profile
void add_profile(FILE* profile, char profile_mode){
    // variables for file handling
    std::string file_name;
    std::string directory;
    
    // variables for profile management
    std::string profile_name;
    
    // ask user for new profile name
    printf("Profile Name: ");
    std::cin >> profile_name;

    // add functionality such that you can't give the new profile a name that already exists

    // set name of directory
    if (profile_mode == 'p'){
        directory = "Profiles/Person/";
    } else if (profile_mode == 'g'){
        directory = "Profiles/Group/";
    }

    // set name of file name
    file_name = directory + profile_mode + '-' + profile_name + ".txt";
}

// opens a profile
void open_profile(FILE* profile, char profile_mode){
    // variables for file manipulation
    std::string file_name;
    std::string directory;
    
    std::string profile_name;
    bool found;

    while (true){
        // asks user to enter profile name to open
        printf("Enter the profile name that you want to open:\n");
        std::cin >> profile_name;

        // search for profile name in list of profiles
        //found = search_profile(profile_name);
        found = true;

        if (found){
            // set name of directory
            if (profile_mode == 'p'){
                directory = "Profiles/Person/";
            } else if (profile_mode == 'g'){
                directory = "Profiles/Group/";
            }

            // set name of file name
            file_name = directory + profile_mode + '-' + profile_name + ".txt";
        } else {
            // FILE NOT FOUND error
            printf("File not found. Please try again.\n");
        }
    }
}

// deletes a profile
void delete_profile(FILE* profile, char profile_mode){
    // variables for file manipulation
    std::string file_name;
    std::string directory;
    
    std::string profile_name;
    bool found;

    while (true){
        // asks user to input profile name to delete
        printf("Enter the profile name that you want to delete:\n");
        std::cin >> profile_name;

        // search for profile name in list of profiles
        //found = search_profile(profile_name);
        found = true;

        if (found){
            // set name of directory
            if (profile_mode == 'p'){
                directory = "Profiles/Person/";
            } else if (profile_mode == 'g'){
                directory = "Profiles/Group/";
            }

            // set name of file name
            file_name = directory + profile_mode + '-' + profile_name + ".txt";
        } else {
            printf("File not found. Please try again.\n");
        }
    }
}

/*void display_profiles(char profile_mode){

}

bool search_profile(std::string profile_name){

}*/