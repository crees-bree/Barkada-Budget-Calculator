# Barkada-Budget-Calculator
## Announcements
- disregard tung ver4.1 branch para pwede ta makarevert ani if need na irevise completely ang code

## For Contributors:
A few things to point out:  
- Please refer to `updates.md` for code updates.  
- `profile.cpp` is ready for testing and bug fixing. You can freely test profile selection functionalities with `profile_test.cpp`. Modify the code as needed.  
  - To compile,
    - (The tedious way that I recommend tbh):
      - Enter `g++ -o profile_test profile_test.cpp profile.cpp` on terminal to compile
      - Enter `.\profile_test` to run
      - I recommend copy-pasting the compile command because it might delete your .cpp files
        - e.g. `g++ -o profile_test.cpp profile.cpp` **THIS MIGHT DELETE `profile_test.cpp`. PROCEED WITH CAUTION**
    - (The easy way I don't really recommend since it can mess with your VSCode):
      - Open `tasks.json` under `.vscode` folder
      - Add `"profile.cpp",` in between `"${file}",` and `"-o",`, just like this:
        ```
        ${file},
        "profile.cpp",
        "-o",
        ```
      - Click `Run C/C++ File` on run button in VSCode
      - **NOTE:** Ensure that you're running `test.cpp` or `profile_test.cpp`, otherwise it would mess things up
  - Add your results to your testings on **Profile Selection** issue
- `account.cpp` and `person_mode.cpp` currently in development.
- For more questions and suggestions, ask me na lang hehe


## Description
**Barkada Budget Calculator (BBC)** is a **money- and budget- tracking console-based program** that aids in easy money tracking and management.
This program is highly usable by friend groups with BBC's Group Mode, which allows friend groups to keep track of their respective changes
when going out and keep track of your friends who didn't pay you back. The great thing about BBC is that it is not only highly usable
by friend groups, it is also highly usable by people who just want to keep track of how much money is going in and out of their wallets
thanks to BBC's Person Mode, wherein you can keep track of your incomes and expenses complete with dates, categories, and even some
personal notes such as *"Income I received from daddy"* or _"Spent just a little on valo skins"_. And BBC can be used by students, families, and
small companies in ensuring that no one overspends.  
As you can see, BBC is multi-featured and can be used anytime and anywhere by anyone, that's why you should rate us 5 stars on Google Play Store 
and App Store and subscribe to our YouTube channel (we are reaching 1 subscribers =>)

## Features
### Main Functionalities:
- The program can create 10 profiles at max

### Person Mode Features and Functionalities:
- A user can create a maximum of 10 accounts

### Group Mode Features and Functionalities:
- 3 Cases
- Case 1: Bill-Splitting Mode
- Case 2: Group Payment Checker
- Case 3: Group Budget Limiter
