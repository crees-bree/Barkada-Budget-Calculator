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

// namespace for filesystem
namespace fs = std::filesystem;

void add_profile(char);
void open_profile(std::fstream*, char);
void delete_profile(char);
void display_profiles(char);
bool search_profile(std::string, char);
std::string set_directory(char);
void open_file(std::fstream*, std::string, char);

// asks user to add, open, and delete profiles
void profile_selection(std::fstream* profile, char profile_mode, std::string* file_name){
    int option;

    while (true){
        std::cout << "\n\nPROFILE SELECTION MENU\n\n";
        
        // display list of profiles saved in directory
        display_profiles(profile_mode);

        std::cout << "\nWhat do you want to do?\n";
        std::cout << "1) Create New Profile\n";
        std::cout << "2) Open Profile\n";
        std::cout << "3) Delete Profile\n";
        std::cout << "0) Exit\n";

        std::cin >> option;

        switch (option){
            case 0:
                return;
            case 1:
                add_profile(profile_mode);
                break;
            case 2:
                open_profile(profile, profile_mode);
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

// adds a profile
void add_profile(char profile_mode){
    // variables for file handling
    std::fstream file;
    std::string file_name;
    std::string directory;
    
    // variables for profile management
    std::string profile_name;
    
    // ask user for new profile name
    std::cout << "Profile Name: ";
    std::cin >> profile_name;

    // this is to prevent creating two profiles with same name
    if (search_profile(profile_name, profile_mode) == true){
        std::cout << "File already exists.\n";
        return;
    }

    // set name of directory
    directory = set_directory(profile_mode);

    // set name of file name
    file_name = directory + profile_name + ".txt";

    // create file by opening it
    open_file(&file, file_name, 'w');

    // close it if opened
    if (file.is_open() == true){
        file.close();
    }
}

// opens a profile
void open_profile(std::fstream* profile, char profile_mode){
    // variables for file manipulation
    std::string file_name;
    std::string directory;
    
    std::string profile_name;
    bool found;

    // asks user to enter profile name to open
    std::cout << "Enter the profile name that you want to open:\n";
    std::cin >> profile_name;

    // search for profile name in list of profiles
    //found = search_profile(profile_name);
    found = true;

    if (found){
        // set name of directory
        directory = set_directory(profile_mode);

        // set name of file name
        file_name = directory + profile_name + ".txt";

        // open file
        // the file will be opened in read mode since 
        // BBC will read the contents of the file when first opened
        open_file(profile, file_name, 'r'); 

        // perhaps add some functionality to read the contents of a file

        // NOTE: File is not closed. Proceed with caution.
    } else {
        std::cout << "File not found.\n"; // ERROR HANDLING (File is not found)
    }
}

// deletes a profile
void delete_profile(char profile_mode){
    // variables for file manipulation
    std::string file_name;
    std::string directory;
    
    std::string profile_name;
    bool found;
    bool removed;

    // asks user to input profile name to delete
    std::cout << "Enter the profile name that you want to delete:\n";
    std::cin >> profile_name;

    // search for profile name in list of profiles
    found = search_profile(profile_name, profile_mode);

    if (found){
        // set name of directory
        directory = set_directory(profile_mode);

        // set name of file name
        file_name = directory + profile_name + ".txt";

        // deletes the specified file
        removed = fs::remove(file_name);

        // tells user if file is deleted/not deleted
        if (removed){
            std::cout << "File removed succesfully.\n";
        } else {
            std::cout << "File not removed successfully.\n"; // ERROR HANDLING (File cannot be deleted)
        }
    } else {
        std::cout << "File not found.\n"; // ERROR HANDLING (File is not found)
    }
}

// display list of present profiles
void display_profiles(char profile_mode){
    std::string directory;
    std::string file_name;
    
    // set directory based on current profile mode
    directory = set_directory(profile_mode);

    // obtain file names in mode directory
    for (const auto &entry: fs::directory_iterator(directory)){
        // convert path to string
        file_name = entry.path().generic_string();

        // delete directory name
        file_name.erase(0, (profile_mode == 'p') ? 16 : 15);
        
        // delete .txt extension
        file_name.erase(file_name.length() - 4, 4);

        // display profile name
        std::cout << file_name << std::endl;
    }
}

// returns true if file exists in directory, else return false
bool search_profile(std::string profile_name, char profile_mode){
    std::ifstream file;
    std::string file_name;
    std::string directory;

    // set directory path based on current profile mode
    directory = set_directory(profile_mode);

    // set file name of profile
    file_name = directory + profile_name + ".txt";

    // attempt to open file
    file.open(file_name);

    // file is in directory if file can be opened, thus return true
    // else then file isn't in directory, thus return false
    if (file.is_open() == true){
        file.close();
        return true;
    } else {
        return false;
    }
}

// set directory path depending on current profile mode
std::string set_directory(char profile_mode){
    if (profile_mode == 'p'){
        return "Profiles/Person/";
    } else if (profile_mode == 'g'){
        return "Profiles/Group/";
    } else {
        return ""; // ERROR HANDLING (Invalid profile mode input)
    }
}

// opens a file
void open_file(std::fstream* file, std::string file_name, char operation){
    switch(operation){
        // opens file in read mode
        case 'r':
            file->open(file_name, std::ios::in);
            break;
        // opens file in write mode
        case 'w':
            file->open(file_name, std::ios::out);
            break;
        // opens file in append/edit mode
        case 'a':
            file->open(file_name, std::ios::app);
            break;
        default:
            return; // ERROR HANDLING (Invalid profile mode input)
    }
}

