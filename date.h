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

// obtain date today
Date get_current_date();

// obtain date yesterday
Date get_yesterday_date();

#endif // DATE_H_