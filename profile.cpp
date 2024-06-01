// contains all functionalities necessary for managing profiles

// NOTES:

// - file format of a profile file: Profiles/<MODE>/<PROFILE_NAME>.txt
//                                  <MODE>: Person / Group
//                                  e.g. Profiles/Person/SirNasvin.txt

// - functions that opens and closes a file: add_profile()
//                                           search_profile()
//                                           open_profile()

// - when using open_profile(), it is important to ALWAYS PAIR IT WITH FILE.CLOSE() otherwise some terrible stuff will happen


#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

#include "profile.h"

// FILESYSTEM NAMESPACE
namespace fs = std::filesystem;

// DEFAULT FILE EXTENSION OF PROFILE FILE (DATA FILE)
#define FILE_EXTENSION ".dat"

// profile directory
const std::string dir = "../Profiles/";
const std::string pdir = "Person/";
const std::string gdir = "Group/";

// PERSON AND GROUP MODE MACROS
#define PERSON 'p'
#define GROUP 'g'

// AUXILIARY FUNCTION DECLARATIONS

// set directory path depending on current profile mode
std::string set_directory(char);

// FUNCTION DEFINITIONS

int profile_selection(char profile_mode, std::string* file_name){
    int option;

    while (true){
        std::cout << "\n\nPROFILE SELECTION MENU\n\n";
        
        // display list of profiles saved in directory
        display_profiles(profile_mode);

        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1) Create New Profile\n";
        std::cout << "2) Open Profile\n";
        std::cout << "3) Delete Profile\n";
        std::cout << "0) Exit\n\n";

        std::cin >> option;

        switch (option){
            case 0:
                return 0;
            case 1:
                add_profile(profile_mode);
                break;
            case 2:
                if ( open_profile(profile_mode, file_name) ){
                    return 1;
                };
                break;
            case 3:
                delete_profile(profile_mode);
                break;
            default:
                std::cout << "Invalid input. Please try again.\n"; // ERROR HANDLING (Invalid user input)
                continue;
        }
    }
}

void add_profile(char profile_mode){
    // variables for file handling
    std::fstream file;
    std::string file_name;
    std::string directory;

    // variables for profile management
    std::string profile_name;
    
    // ask user for new profile name
    std::cout << "\nProfile Name: ";
    std::cin.ignore();
    getline(std::cin, profile_name);


    // this is to prevent creating two profiles with same name
    if (search_profile(profile_name, profile_mode) == true){
        std::cout << "\nFile already exists.\n";
        return;
    }

    // set name of directory
    directory = set_directory(profile_mode);

    // set name of file name
    file_name = directory + profile_name + FILE_EXTENSION;

    // create file by opening it
    file.open(file_name, std::ios::out);

    // close it if opened
    if (file.is_open() == true){
        file.close();
    }
}

int open_profile(char profile_mode, std::string* file_name){
    std::string profile_name;
    std::string directory;
    
    bool found;

    // asks user to enter profile name to open
    std::cout << "\nEnter the profile name that you want to open: ";
    std::cin.ignore();
    getline(std::cin, profile_name);

    // search for profile name in list of profiles
    found = search_profile(profile_name, profile_mode);

    if (found){
        // set name of directory
        directory = set_directory(profile_mode);

        // set name of file name
        *file_name = directory + profile_name + FILE_EXTENSION;

        // go signal to read profile file
        return 1;
    } else {
        std::cout << "\nFile not found.\n"; // ERROR HANDLING (File is not found)

        return 0;
    }
}

void delete_profile(char profile_mode){
    // variables for file manipulation
    std::string file_name;
    std::string directory;
    
    std::string profile_name;
    bool found;

    // asks user to input profile name to delete
    std::cout << "\nEnter the profile name that you want to delete: ";
    std::cin.ignore();
    getline(std::cin, profile_name);

    // search for profile name in list of profiles
    found = search_profile(profile_name, profile_mode);

    if (found){
        // set name of directory
        directory = set_directory(profile_mode);

        // set name of file name
        file_name = directory + profile_name + FILE_EXTENSION;

        // delete file
        if (fs::remove(file_name)){
            // displays if file is successfully deleted
            std::cout << "\nFile removed succesfully.\n";
        } else {
            perror("File deletion failed"); // ERROR HANDLING (File cannot be deleted)
        }
    } else {
        std::cout << "\nFile not found.\n"; // ERROR HANDLING (File is not found)
    }
}

void display_profiles(char profile_mode){
    std::string directory;
    std::string file_name;
    
    // set directory based on current profile mode
    directory = set_directory(profile_mode);

    // obtain file names in mode directory
    for ( const auto &entry: fs::directory_iterator(directory) ){
        // convert path to string
        file_name = entry.path().generic_string();

        // delete directory name
        file_name.erase(0, (profile_mode == PERSON) ? dir.length() + pdir.length() : dir.length() + gdir.length());
        
        // delete .txt extension
        file_name.erase(file_name.length() - 4, 4);

        // display profile name
        std::cout << file_name << std::endl;
    }
}

bool search_profile(std::string profile_name, char profile_mode){
    std::ifstream file;
    std::string file_name;
    std::string directory;

    // set directory path based on current profile mode
    directory = set_directory(profile_mode);

    // set file name of profile
    file_name = directory + profile_name + FILE_EXTENSION;

    // attempt to open file
    file.open(file_name);

    // file is in directory if file can be opened, thus return true
    // else then file isn't in directory, thus return false
    if (file.is_open()){
        file.close();
        return true;
    } else {
        return false;
    }
}

// AUXILIARY FUNCTION DEFINITIONS

std::string set_directory(char profile_mode){
    if (profile_mode == PERSON){
        return dir + pdir;
    } else if (profile_mode == GROUP){
        return dir + gdir;
    } else {
        return ""; // ERROR HANDLING (Invalid profile mode input)
    }
}



