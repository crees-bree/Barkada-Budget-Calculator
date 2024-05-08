// PERSON MODE

#include <iostream>
#include <string>

struct date{
    int day;
    int month;
    int year;
};
typedef struct date Date;

void profile_selection(FILE*, std::string);


void person_mode(){
    FILE* profile;
    std::string profile_name;
    
    // profile selection menu
    profile_selection(profile, profile_name);

    // close profile file
    fclose(profile);
}

