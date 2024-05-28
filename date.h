// FUNCTION DECLARATIONS OF DATE.CPP
// DATE STRUCTURE DECLARATION AND DEFINITION

#ifndef DATE_H_
#define DATE_H_

// DATE STRUCTURE
struct date{
    int day;
    std::string day_name;
    int month;
    std::string month_name;
    int year;
};
typedef struct date Date;

// operator overloading functions

// is a older than b
bool operator<= (const Date& d1, const Date& d2);

// is a younger than b
bool operator>= (const Date& d1, const Date& d2);

// are dates a and b the same
bool operator== (const Date& d1, const Date& d2);


// obtain date today
Date get_current_date();

// obtain date yesterday
Date get_yesterday_date();

// check if date is valid
bool date_is_valid(Date);

#endif // DATE_H_