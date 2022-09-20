# Payment-Application
1. This program simulates the process of paying when you buy something with a bank card.
2. This project has a database file as .txt file which we can add new data in.
3. This project as the user to enter the Holder name, expiration date of the card and the PAN.
- Firstly, the expiration date the user has entered is greater or less than the system date. If it's greater than he will assume that the card is valid else, he will exit and return error message. 
- Secondly, the program will check if the cardholder's name and PAN the user has entered exist on the database.txt file or not if he found them, he will ask the user to enter the amount of money he want to pay, if the amount the user has entered greater than his amount is in account the program will return error message, else he will take the amount he want to pay the will go to the database.txt file and he will update the amount of this account through The result of subtracting the withdrawn amount from the principal amount.
