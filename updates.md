# UPDATES

**Test Status**: *ERROR*, *empty*, *incomplete*, *not final*, *test pending*, *verify testing*, *done*

## UPDATE VERSION 4.5 (May 30,2024)
- In group_mode
  - Case 3 is finished *test pending*
    - added function to display member details (displays budget left and all recorded exenses) *test pending*
    - added function tor remove member *test pending*
    - added function for expenses (includes notes for expense) *test pending*
    - budget also updates according to expense,
    - display member will also dislay whether member has went over the budget
- In member
  - Case 3 functions added
    - everything mentioned above has their functions in member 
    
To-Do:
**FOR JIM:**
- Implement category percentage display (already made a function for this sa person_mode)

## UPDATE VERSION 4.4 (May 28, 2024)

- In person_mode
  - Added display_records_by_type() - *verify testing*
  - Added display_records_by_amount() - *verify testing*
  - Added display_records_by_category() - *verify testing*
  - Added display_category_percentages() - *empty*
  - Added add_account() - *verify testing*
  - Added modify_account() - *verify testing*
  - Added display_accounts() - *verify testing*
  - Added delete_account() - *verify testing*
  - Added transfer_balance() - *not final*
  - Updated person_mode() - *incomplete*
  - Updated modify_account_record() - *verify testing*
  - Updated delete_account_record() - *verify testing*
  - Updated person_menu_prompt() - *verify testing*
  - Updated filter_by_date() - *verify testing*
- In account
  - In Account class
    - Added private method select_record_screen() - *verify testing*
    - Added public method modify_record_screen() - *verify testing*
    - Added public method set_account_name() - *verify testing*
    - Added public method get_balance() - *verify testing*
    - Added public method set_balance() - *not final*
    - Added public method transfer_balance() - *incomplete*
    - Added public method filter_by_record_type() - *verify testing*
    - Added public method filter_by_amount_range() - *verify testing*
    - Added public method filter_by_category() - *verify testing*
    - Updated private method select_record_type() - *verify testing*
      - Removed transfer record category
    - Updated private method display_record() - *verify testing*
    - Updated public method modify_record() - *verify testing*
    - Updated public method delete_record() - *verify testing*
    - Updated public method display_records() - *verify testing*
- In date
  - Added date_is_valid() - *verify testing*
- In group_mode
  - Added removeMem() - *test pending*
  - Added case_three() - *incomplete*
    - forgot to add this one hihi
  - Updated case_one() - *test pending*
  - Updated case_oneMenu() - *test pending*
  - Updated edit_member() - *test pending*
- In member
  - In Member class
    - 
- Added program.cpp
  - NOT FINAL
  - Will opt to use ncurses for clear screen, pause, and some fancy display stuff

To-Do:
**FOR CHAD:**
- Test ur case 1 bro
- Implement case 2

**FOR JIM:**
- Finish case 3 plsplslpslpslpslsplsplsp
- Implement category percentage display (already made a function for this sa person_mode)

**FOR CHAN:**
- Finish transfer_balance() in account
- Get rid of initialize() in account since it's kind of pointless i think
- Also get rid of create_accounts() in account since it's also kind of pointless
- Check if the balance is updated correctly
- Create group mode main menu screen
- Implement reading and writing
  - Implement serializing and deserializing of Member class
- Try out ncurses (if u can and time will permit)
  - Pause the program on specified parts of code
  - Clear screen (use system("cls") or smth idk it's not recommended daw)

## UPDATE VERSION 4.3 (May 26, 2024)

- In person_mode
  - Added calculate_total_balance() - *test pending*
  - Updated person_mode() - *incomplete*
  - Updated init() - *test pending*
  - Updated save() - *test pending*
  - Updated select_account() - *test pending*
- In account
  - In Account class
    - Added public method get_balance() - *test pending*
    - Updated private method add_to_records() - *test pending*
    - Updated public method serialize() - *test pending*
    - Updated public method deserialize() - *test pending*
- In date
  - Updated op. over. func. for <= - *test pending*
  - Updated op. over. func. for >= - *test pending*
  - Updated op. over. func. for == - *test pending*
  - Added operator overloading function prototypes in date.h

## UPDATE VERSION 4.2 (May 25, 2024)

- Added ver4.2 git branch
- In person_mode
  - Added ProfileDetails structure
    - This is to easily track general profile data such as accounts and total balance
  - Added filter_by_date() - *not final*
  - Added person_menu_prompt() - *incomplete*
  - Added add_default_accounts() - *test pending*
  - Added file_empty() - *test pending*
  - Added add_account_record() - *test pending*
  - Added modify_account_record() - *empty*
  - Added delete_account_record() - *empty*
  - Added display_records_by_account() - *test pending*
  - Added display_records_by_date() - *test pending*
  - Added select_account() - *test pending*
  - Updated person_mode() - *incomplete*
  - Updated init() - *test pending*
  - Updated save() - *test pending*
  - Added default currency (Php)
- In account
  - In Account class
    - Added private method add_to_records() - *test pending*
    - Added public method auto_initialize() - *test pending*
    - Added public method delete_record() - *empty*
    - Added public method filter_by_date() - *test pending*
    - Added public method get_account_name() - *test pending*
  - Added default currency (Php)
- Added date.cpp and date.h
  - I dedicated a separate file for my Date structure and its functionalities  
    since I realized I'm going to have to do a lot of operations  
    with it
  - Unified all Date structure declarations into date
  - Unified all get_local_date() definitions into date
  - Updated get_current_date() - *test pending*
    - Previously get_local_date()
  - In Date structure
    - Added operator overloading function for <= - *test pending*
    - Added operator overloading function for >= - *test pending*
    - Added operator overloading function for == - *test pending*
- In group_mode
  - Added edit_member() - *incomplete*
  - Added edit_memberMenu() - *test pending*
  - Updated case_oneMenu() - *test pending*
  - Updated case_one() - *incomplete*
    - i think
- In member
  - Added default currency (Php)
  - Added check_memName() - *test pending*
  - Added setCase1() - *test pending*
  - Updated initialize() - *incomplete*
    - i think

To-Do:
- Test everything you guys just added
  - This is necessary before adding more sht

## UPDATE VERSION 4.1 (May 24, 2024)

- In group_mode
  - Added caseMenu() - *incomplete*
  - Added case_oneMenu() - *incompete*
  - Added displayMembers() - *incomplete*
  - Updated group_mode() - *incomplete*
  - Updated case_one() - *incomplete*
- In member
  - In Member class
    - Updated display_details() - *incomplete*
- In account
  - In Account class
    - Updated private method display_record() - *test pending*
    - Updated private method update_balance() - *test pending*
    - Updated public method serialize() - *test pending*
    - Updated public method deserialize() - *test pending*
    - Updated public method display_records() - *test pending*

## UPDATE VERSION 4.0 (May 22, 2024)

- Created member.cpp and member.h
  - Added Date structure
  - Added class Member
    - in private
      - Added Transaction structure (storing data for all cases)
        - Added structures for cases 1, 2, and 3
          - Added expense structure
      - Added name
    - in public
      - Added create_member() - *not final*
      - Added iniitalize() - *incomplete*
      - Added edit_member() - *empty*
      - Added display_details() - *empty*
      - Added serialize() - *empty*
      - Added deserialize() - *empty*
- In group_mode
  - Updated group_mode() - *incomplete*
  - Added case_one() - *empty*
  - Added case_two() - *empty*
  - Added case_three() - *incomplete*
  - Added init() - *empty*
  - Added save() - *empty*

## UDPATE VERSION 3.4 (May 21, 2024)

- In account.cpp  
  - Moved class declaration to account.h  
  - Class methods defined outside class declaration  
  - Moved necessary function declarations to account.h  
  - In Account class  
    - Added public method serialize() - *not final*
    - Added public method deserialize() - *not final*
  - Removed display_account_records()
    - ERROR 001 didn't emerge, however it could be because the method was called on a singular object
      and not an array of objects
- In profile.cpp  
  - **PROFILE SELECTION READY FOR TESTING**
  - Removed open_file()  
  - Moved necessary function declarations to profile.h
  - Updated add_profile() - *verify testing*
  - Updated open_profile() - *verify testing*
  - Updated delete_profile() - *verify testing*
- Added profile_test.cpp
  - This is to allow contributors to freely unit test and play around with profile.cpp functionalities

## UPDATE VERSION 3.3 (May 19, 2024)

- In profile.cpp  
  - Removed read_profile_file()  
    - Previously sync_profile_file()  
  - Removed save_profile()  
  - Changed file extension from .bin to .dat  
    - .dat is ideal for storing data unlike .bin  
- In person_mode.cpp  
  - Added init() - *incomplete*  
  - Added save() - *empty*  

To-Do:  
- Continue working on init() in person_mode.cpp  
- Add new methods serialize() and deserialize() in Account class in accounts.cpp  

## UPDATE VERSION 3.2

- In account.cpp  
  - In Account class  
    - Added initialize() public method - *not final*  
    - Updated modify_record() public method - *test pending*  
    - Updated select_record_type() private method - *verify testing*  
    - Updated create_account() - *incomplete*  
    - Moved private methods definition outside of function, specifically private methods  
      select_record_type, display_record(), and update_balance()
    - Updated display_records() public method - *not final*  

  - COMPILATION ERROR (ERROR 001):  
    - Error Details: Error occurred when compiling test.exe. Error message states it has something to do  
                     with the Account public method display_records()   
      - Compilation Command: g++ -o test test.cpp person_mode.cpp account.cpp
      - It is important to point out that test.exe will compile without errors if the display_records()
        method is not called in person_mode.cpp  
      - It is important to point out that other methods of Account class won't result in a compilation  
        error (e.g. acc_record() public method)  
    - Error Message: test.cpp account.cpp person_mode.cpp  
                     /usr/bin/ld: /tmp/ccvhLttZ.o: in function `person_mode()':  
                     person_mode.cpp:(.text+0x2f): undefined reference to `Account::display_records()'  
                     collect2: error: ld returned 1 exit status  
    - Theoretical Fix: Find an alternative compilation method  
    - Temporary Fix: added a new function in account.cpp named display_account_records()  
      - It is still recommended to push through the theoretical fix  

  - SEGMENTATION FAULT ERROR (ERROR 002): *FIXED*  
    - Error Details: Segmentation fault occurred at account.cpp, lines 20 and 54  
      - At line 20, a segmentation error was raised when modify_records() public method attempted to  
        add a new record to records vector  
      - At line 54, a segmentation error was raised when attempting to get user input for account_name  
        private member using std::cin.getline()  
    - Possible Cause: Private class members were not properly called by class methods  
    - Theoretical Fix: Search on how to properly call class members  
    - **FIX:** Declare necessary private members in account.h  

  - Updated create_account() - *incomplete*  
    - This is in response to ERROR 001  
  - Added display_account_records() - *not final*  
    - In response to ERROR 001  

## UDPATE VERSION 3.1

- In profile.cpp
  - Changed profile file extension from .txt to .bin
  - Added sync_profile_file() - *empty*
          save_profile() - *empty*
- Created account.cpp & account.h
  - Transferred class Account to account.cpp   
  - Transferred get_local_time() to account.cpp  

To-Do:
- Test add_record() 

## UPDATE VERSION 3.0

- In person_mode.cpp  
  - Added class Account  
    - Added structures Date and Record  
    - Added instance variables records vector and balance  
    - Added private methods select_record_type() - *not final*  
                            display_record() - *not final*  
                            update_balance() - *empty*  
    - Added public methods add_record() - *not final*  
                           modify_record() - *empty*  
                           display_records() - *empty*  
  - Updated person_mode() - *incomplete*  
  - Added get_local_time() - *verify testing*  
- Updated person_mode.h  

## UPDATE VERSION 2.3

- In profile.cpp  
  - Updated open_profile() - *verify testing*  

## UPDATE VERSION 2.2

- In profile.cpp
  - Updated profile_selection() - *test pending*  
            add_profile() - *verify testing*  
            delete_profile() - *verify testing*  
            display_profiles() - *done*  
            search_profiles() - *verify testing*  
  - Added open_file() - *verify testing*  
          set_directory() - *done*

To-Do:
- Implement open_profile()

## UPDATE VERSION 2.1

- In profile.cpp
  - Updated profile_selection() - *test pending*  
            add_profile() - *test pending*  
            open_profile() - *test pending*  
            delete_profile() - *test pending*  
- Added function declarations in profile.h
- Added test.cpp for testing purposes

To-Do:
- Ask help because i dunno what to do T_T

## UPDATE VERSION 2.0

- Added profile.cpp and profile.h
  - Added profile_selection() - *not final*  
          add_profile() - *not final*  
          open_profile() - *not final*  
          delete_profile() - *not final*  
          display_profiles() - *not final*  
          search_profile() - *empty*
- In person_mode.cpp
  - Updated person_mode() - *incomplete*
    - Added profile_selection from "profile"
- In group_mode.cpp
    - Created group_mode() - *empty*

To-Do:
- Test functions in profile.cpp

## UPDAYE VERSION 1.0

- Created main.cpp
  - Added main() - *test pending*
- Created person_mode.cpp and person_mode.h
  - Added person_mode() - *empty*
- Created group_mode.cpp and group_mode.h

