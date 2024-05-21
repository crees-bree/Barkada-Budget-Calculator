// PROFILE.CPP UNIT TEST SOURCE CODE

// You can play around and unit test profile.cpp and profile.h using this source code

#include <iostream>
#include <fstream>

#include "profile.h"

#define PERSON 'p'
#define GROUP 'g'

int main(){
    std::string file_name;
    
    // call profile selection menu
    // note the function parameters 'mode', '&file_name'
    int open = profile_selection(PERSON, &file_name);

    // execution result

    // when opening a file, the ff. should be expected:
    // Open: TRUE
    // File Name: Profiles/folder/profile_name.file_extension (e.g. Profiles/Person/chad.dat)

    // when exiting profile selection menu, the ff. should be expected:
    // Open: FALSE
    // File Name:
    std::cout << "Open: " << (open ? "TRUE" : "FALSE") << std::endl;
    std::cout << "File Name: " << file_name << std::endl;

    return 0;
}