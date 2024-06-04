# Barkada-Budget-Calculator
## Announcements
Barkada Budget Calculator Pre-Release Version 0.1.0-Alpha is released on June 4, 2024 and is already available! Refer to Releases to view this release.

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
- BBC features two mode: **Person Mode** and **Group Mode**.
  - **Person Mode** is suitable for _personal use_. In person mode, the user can keep track of their daily income and expenses without hassle.
  - **Group Mode** is suitable for _small groups_ such as families, friend groups, and small businesses. In group mode, groups can keep track of their transaction changes, debt of their members, and expenses and budget.
- The user can create _profiles_ to separate accounting records between different people or groups of people.
  - The user also has the option to remove profiles.
  - Profiles created in Person Mode and Group Mode are separate.
  - User data is stored in a `.dat` file because of its versatility.

### Person Mode Features and Functionalities:
- In the **Person Mode** menu, the user is able to see five recent records added today and yesterday.
- The user can keep track of their income and expenses with the use of records. A _record_ details a certain transaction or transfer of money.
  - A record consists of a _date of transaction_, _record type_, _amount transferred_, _category_, and a _note_.
    - The date of transaction keeps track of on what day did that record get added to the program.
    - The record type denotes the type of transaction, whether it is an expense, income, or transfer (transferring money from one account to another)
    - The category aids in organizing records into a cluster of related records, whether it would be by purpose or circumstance
    - The note helps the user specify the contextual and purposal details of that transaction
  - The user has the ability to add, modify, delete, display, and filter records.
    - Upon adding a record, the user has the option to modify that record to ensure that the user is able to enter the correct details of that record
    - Records can be filter according to the account they belong to, their date, their record type, their amount (which can be filtered by a specific amount or a range of amounts), and their category.
  - When there are no available accounts, the user is not permitted to add, modify, delete, display, or filter records.
  - The user is able to see the percentage of their expenses by category.
- The user can store their records in an _account_, which represents a money source or destination.
  - The user can only create a maximum of _ten_ accounts. When the number of accounts reaches its limit, the user is not permitted to add more accounts.
  - The program automatically creates three default accounts for the user: _Cash_, _Card_, and _Savings_.
  - The user can add, modify, delete, and display accounts.
    - Whenever a user adds, modifies, or deletes an account, the user is prompted with an account names display tallying the available accounts.
    - The user can modify the account's name and balance.
      - When a user modifies an account's balance, the program will create a new record that updates the balance to the amount specified by the user.
    - The user is able to see all the available accounts and their current balances with the displaying accounts feature.
  - The user can transfer an amount from one account to the other. When performing a transfer, a transfer record is added to the current account destination and the new account destination to update the transfer.

### Group Mode Features and Functionalities:
- **Group Mode** has _members_ that represents the members of a group. The user can add, modify, and delete members (if the user hates that specific member). This functionality is in general to all use cases. Speaking of use cases...
  - The modify member feature depends on what use case the user is on (e.g. if the user is using use case 2, the user can only modify details in use case 2).
  - The number of members is capped at _20_.
  - Members are generalized for all use cases. A member added on use case 1 will be visible on use cases 2 and 3.
- In **Group Mode**, the user is prompted with a use case selection menu. The user can select a use case depending on their purposes. The details for each use case is listed below:
  - **Use Case 1: Sukli sa Kinsa**
    - **Sukli sa Kinsa** allows the user to keep track of the _bills_, _payments_, and _change_ of each member.
    - The change of all members will be automatically displayed in the Sukli sa Kinsa menu.
    - The user is able to display a member's bill, payment, and change.
    - The user can display the total payment, bill, and change of the group.
  - **Use Case 2: Utang Tracker**
    - **Utang Tracker** allows the user to keep track of which members have _pending debt_ and have _paid their debt_.
    - The payment status of all members will be automatically displayed in the **Utang Tracker** menu.
      - In cases wherein a member is added on **Sukli sa Kinsa** or **Gasto Mo ang Limit!**, they will be displayed on the `Members` category since these members are not included in **Utang Tracker**'s debt tracking.
    - The user is able to display a member's bill, payment, and their recent payment date
  - **Use Case 3: Gasto Mo ang Limit!**
    - **Gasto Mo ang Limit!** allows the user to keep track of the members' _current budget_.
    - The program will indicate which members exceeded their budget in cases wherein some members exceeded their budget.
    - The budget of all members as well as their indicators (in case that they exceeded their budget) will be displayed automatically on the **Gasto Mo ang Limit!** menu.
    - The user can add an _expense_ for a member. An expense tracks the amount spent and details for that expense.
      - The user can add multiple expenses for a member.
      - When an expense is added, the budget will automatically update.
    - The user is able to display a member's current budget and all their expenses.
    - In cases wherein a member is added on **Sukli sa Kinsa** or **Utang Tracker** or a member ran out of budget / exceeded their budget, the user can add a new budget to that member, given that the member ran out or exceeded their budget.

## For Contributors:
A few things to point out:  
- Please refer to `updates.md` for code updates.  

### Recommendations
- An actual GUI instead of a console-based UI
- Create category options and default categories
- Add a default case in Group Mode
