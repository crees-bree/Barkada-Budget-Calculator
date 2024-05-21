# Barkada-Budget-Calculator

## For Contributors:
A few things to point out:  
- Please refer to `updates.md` for code updates.  
- `profile.cpp` is ready for testing and bug fixing. You can freely test profile selection functionalities with `profile_test.cpp`. Modify the code as needed.  
  - To compile,
    - (The tedious way that I recommend tbh):
      - Enter `g++ -o profile_test profile_test.cpp profile.cpp` on terminal to compile
      - Enter `.\profile_test` to run
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
Barkada Budget Calculator (BBC) is a blah blah blah blah

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

test test;