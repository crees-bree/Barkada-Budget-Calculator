// contains functionalities for basic screen functions

#include <iostream>
#include <fstream>
#include <errno.h>
#include <windows.h>

#include "screen_util.h"

#define SEC 1000
#define TWO_SEC 2000
#define THREE_SEC 3000

void loading(std::string message){
    std::cout << std::endl << message;
    
    for (int i = 0; i < 3; ++i){
        std::cout << ".";
        Sleep(SEC);
    }

    std::cout << std::endl;
}

void pause_invalid(std::string message){
    std::cout << std::endl << message << std::endl;

    Sleep(SEC);
}

void pause_til_input(){
    std::string nig;
    Sleep(THREE_SEC);

    std::cout << "\nEnter any character to continue: ";
    std::cin.ignore();
    getline(std::cin, nig);
}

bool user_confirm(std::string message){
    char y;
    
    std::cout << std::endl << message << " (Enter Y to confirm) ";

    std::cin >> y;

    if (y == 'Y') return 1;
    else return 0;
}

void print_ascii(std::string file_name){
    std::ifstream file("../ascii/" + file_name + ".txt");
    std::string buffer;

    if ( file.fail() ){
        perror("Accessing ASCII main title failed.");
        return;
    }

    while ( getline(file, buffer) ){
        std::cout << buffer << std::endl;
    }

    file.close();
}