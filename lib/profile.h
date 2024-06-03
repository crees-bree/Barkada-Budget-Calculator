// FUNCTION DECLARATIONS OF PROFILE.CPP


#ifndef PROFILE_H_
#define PROFILE_H_

// asks user to add, open, and delete profiles
// returns 1 if program will open a profile, otherwise return 0
int profile_selection(char, std::string*);

// adds a profile
void add_profile(char);

// opens a profile
int open_profile(char, std::string*);

// deletes a profile
void delete_profile(char);

// display list of present profiles
void display_profiles(char);

// returns true if file exists in directory, else return false
bool search_profile(std::string profile_name, char profile_mode);

#endif // PROFILE_H_ 