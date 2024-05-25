// contains functionalities for handling with dates

#include <iostream>
#include <ctime>

#include "date.h"

#define NUM_SEC_IN_DAY 3600 * 24

// DAY AND MONTH NAMES

const std::string days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
                                "Friday", "Saturday"};
const std::string months[] = {"January", "February", "March", "April", "May", "June",
                            "July", "August", "September", "October", "November", "December"};

// OPERATOR OVERLOADING FUNCTIONS

// is a older than b
bool operator<= (const Date& d1, const Date& d2) const {
    if (d1.year <= d2.year){
        return d1.year <= d2.year;
    }
    if (d1.month <= d2.month){
        return d1.month <= d2.month;
    }
    if (d1.day <= d2.day){
        return d1.day <= d2.day;
    }
}

// is a younger than b
bool operator>= (const Date& d1, const Date& d2) const {
    if (d1.year >= d2.year){
        return d1.year >= d2.year;
    }
    if (d1.month >= d2.month){
        return d1.month >= d2.month;
    }
    if (d1.day >= d2.day){
        return d1.day >= d2.day;
    }
}

// are dates a and b the same
bool operator== (const Date& d1, const Date& d2) const {
    if (d1.year == d2.year){
        return d1.year == d2.year;
    }
    if (d1.month == d2.month){
        return d1.month == d2.month;
    }
    if (d1.day == d2.day){
        return d1.day == d2.day;
    }
}

// AUXILIARY FUNCTIONS

Date get_current_date(){
    Date date;
    
    time_t now = time(0);

    tm* sys_date = localtime(&now);

    date.day = sys_date->tm_mday;
    date.month = 1 + sys_date->tm_mon;
    date.year = 1900 + sys_date->tm_year;
    date.day_name = days[sys_date->tm_wday];
    date.month_name = months[date->month - 1];

    return date;
}

Date get_yesterday_date(){
    Date date;

    time_t yest = time(0);

    yest -= NUM_SEC_IN_DAY;

    tm* sys_date = localtime(&yest);

    date.day = sys_date->tm_mday;
    date.month = 1 + sys_date->tm_mon;
    date.year = 1900 + sys_date->tm_year;
    date.day_name = days[sys_date->tm_wday];
    date.month_name = months[date->month - 1];
    
    return date;
}

