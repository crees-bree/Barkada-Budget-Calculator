// contains all functionalities for person mode

// NOTES:

// In person mode, a user can add, modify, and delete a record


#include <iostream>
#include <errno.h>
#include <fstream>

#include "account.h"
#include "profile.h"

#define MODE 'p'

// reading and writing functions

void init(std::string, Account[], int*);
void save(std::string, Account[], int*);

// contains functionalities for person mode
int person_mode(){
    Account accounts[10]; // only a maximum of 10 accounts can be created
    int accounts_size = 0; // sets the current size of accounts array

    int open;

    std::fstream profile;
    std::string file_name;

    // select a profile first
    open = profile_selection(MODE, &file_name);

    // exit program if open profile is not initiated
    if (!open){
        // program exited successfully
        return 0;
    }

    // read saved data from profile file
    init(file_name, accounts, &accounts_size);

    // save data to profile file

    // program exited successfully
    return 0;
}

// initialize saved data from file reading
void init(std::string file_name, Account accounts[], int* accounts_size){
    std::ifstream file;

    // open file for reading
    file.open(file_name, std::ios::in | std::ios::binary);

    if (file.fail()){
        perror("\nFile not found. Initialization failed."); // ERROR HANDLING (File not found)
        exit(EXIT_FAILURE);
    }

    // read accounts array size
    if (!(file.read((char *) accounts_size, sizeof(*accounts_size)))){
        perror("\nReading accounts size failed."); // ERROR HANDLING (File reading failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // read accounts array
    for (int i = 0; i < *accounts_size; ++i){
        accounts[*accounts_size].deserialize(file_name);
    }
}

// save data to file
void save(std::string file_name, Account accounts[], int* accounts_size){
    std::ofstream file;
    
    // open file for writing
    // std::ios::trunc completely wipes out the contents of the file
    file.open(file_name, std::ios::out | std::ios::binary | std::ios::trunc);

    if (file.fail()){
        perror("\nFile cannot be opened. Saving failed."); // ERROR HANDLING (File cannot be opened)
        exit(EXIT_FAILURE);
    }

    // write accounts array size
    if (!(file.write((char *) accounts_size, sizeof(*accounts_size)))){
        perror("\nReading accounts size failed."); // ERROR HANDLING (File writing failed)
        file.close();
        exit(EXIT_FAILURE);
    }

    file.close();

    // write accounts array
    for (int i = 0; i < *accounts_size; ++i){
        accounts[*accounts_size].serialize(file_name);
    }
}






