

#ifndef SCREEN_UTIL_H_
#define SCREEN_UTIL_H_

#include <iostream>

// displays loading indicator
void loading(std::string);

// pauses screen for 1 second if invalid input
void pause_invalid(std::string = "Invalid input. Please try again.");

// pauses the program until user enters an input
void pause_til_input();

// confirms user input
bool user_confirm(std::string);

// prints ascii art from a text file
void print_ascii(std::string);

#endif // SCREEN_UTIL_H