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
bool operator<= (const Date& d1, const Date& d2){
    if (d1.year != d2.year){
        return d1.year < d2.year;
    }
    if (d1.month != d2.month){
        return d1.month < d2.month;
    }
    if (d1.day != d2.day){
        return d1.day < d2.day;
    }

    return true;
}

// is a younger than b
bool operator>= (const Date& d1, const Date& d2){
    if (d1.year != d2.year){       
        return d1.year > d2.year;
    }
    if (d1.month != d2.month){
        return d1.month > d2.month;
    }
    if (d1.day != d2.day){
        return d1.day > d2.day;
    }

    return true;
}

// are dates a and b the same
bool operator== (const Date& d1, const Date& d2){
    if (d1.year != d2.year){
        return false;
    }
    if (d1.month != d2.month){
        return false;
    }
    if (d1.day != d2.day){
        return false;
    }

    return true;
}

// AUXILIARY FUNCTIONS

Date get_current_date(){
    Date date;
    
    // get current time
    time_t now = time(0);

    // convert to tm struct
    tm* sys_date = localtime(&now);

    // obtain date details
    date.day = sys_date->tm_mday;
    date.month = 1 + sys_date->tm_mon;
    date.year = 1900 + sys_date->tm_year;
    date.day_name = days[sys_date->tm_wday];
    date.month_name = months[date.month - 1];

    return date;
}

Date get_yesterday_date(){
    Date date;

    // get current time
    time_t yest = time(0);

    // convert to tm struct
    tm* sys_date = localtime(&yest);

    // move to yesterday
    --(sys_date->tm_mday);

    // normalize tm struct (in case day becomes 0)
    mktime(sys_date);

    // obtain date details
    date.day = sys_date->tm_mday;
    date.month = 1 + sys_date->tm_mon;
    date.year = 1900 + sys_date->tm_year;
    date.day_name = days[sys_date->tm_wday];
    date.month_name = months[date.month - 1];
    
    return date;
}

Date get_last_week_date(){
    Date date;

    // get current time
    time_t lw_date = time(0);

    lw_date -= (3600 * 24 * 7);

    // convert to tm struct
    tm* sys_date = localtime(&lw_date);

    // normalize tm struct (in case day becomes 0)
    mktime(sys_date);

    // obtain date details
    date.day = sys_date->tm_mday;
    date.month = 1 + sys_date->tm_mon;
    date.year = 1900 + sys_date->tm_year;
    date.day_name = days[sys_date->tm_wday];
    date.month_name = months[date.month - 1];
    
    return date;
}

bool date_is_valid(Date date){
    // big bang denotes the beginning of time, well for computers at least uwu -><-
    Date bigbang = { .day = 1, .month = 1, .year = 1970};
    Date now = get_current_date();

    const int thirty_one[] = {1, 3, 5, 7, 8, 10, 12};
    const unsigned int thirty_one_size = sizeof(thirty_one) / sizeof(int);

    const int thirty[] = {4, 6, 9, 11};
    const unsigned int thirty_size = sizeof(thirty) / sizeof(int);

    // check if month is valid
    if ( !(date.month >= 1 && date.month <= 12) ) return false;
    
    // check if day is valid
    for (int i = 0; i < thirty_one_size; ++i){
        if (date.month == thirty_one[i]){
            if ( !(date.day >= 1 && date.day <= 31) ) return false;
        }
    }

    for (int i = 0; i < thirty_size; ++i){
        if (date.month == thirty[i]){
            if ( !(date.day >= 1 && date.day <= 30) ) return false;
        }
    }

    if (date.month == 2){
        if ( !(date.day >= 1 && date.day <= 29) && date.year % 4 == 0) return false;

        if ( !(date.day >= 1 && date.day <= 28) ) return false;
    }

    // check if date is within January 1, 1970 to now
    if ( !(bigbang <= date && now >= date) ) return false;

    return true;
}

std::string getMonthName(int index){
    return months[index-1];
}