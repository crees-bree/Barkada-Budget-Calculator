#ifndef PROFILE_H_
#define PROFILE_H_

#include <iostream>

extern void profile_selection(FILE*, char, std::string*);
extern void add_profile(FILE*, char);
extern void open_profile(FILE*, char);
extern void delete_profile(FILE*, char);

#endif // PROFILE_H_