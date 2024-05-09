#ifndef PROFILE_H_
#define PROFILE_H_

#include <iostream>

extern void profile_selection(std::fstream*, char, std::string*);
extern void add_profile(char);
extern void open_profile(std::fstream*, char);
extern void delete_profile(char);
extern void display_profiles(char);

#endif // PROFILE_H_