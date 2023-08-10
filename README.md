# Payment Application

The Payment Application is a simulation of the payment process when making purchases using a bank card. It allows users to enter their cardholder name, card expiration date, and PAN (Primary Account Number) to proceed with the payment. The application is equipped with a database file (`database.txt`) that stores card information for validation.

## Functionality

1. **Card Expiration Date Validation:**
   - Upon entering the card expiration date in the format `MM/YY`, the application checks if the entered date is greater than the system date. If the date is in the past, the program exits with an error message, indicating that the card has expired.

2. **Cardholder Name and PAN Validation:**
   - The user is prompted to enter their cardholder name and PAN. The application then checks whether this data exists in the `database.txt` file, which acts as the system's database. If the cardholder's name and PAN are not found in the database, an error message is displayed, and the user is asked to re-enter the correct information.

3. **Payment Process:**
   - After validating the cardholder's information, the application requests the user to enter the payment amount. If the entered amount exceeds the available balance in the user's account, the program returns an error message, indicating that the current balance is insufficient to complete the payment.

4. **Updating Account Balance:**
   - If the entered payment amount is valid, the application deducts the payment from the account balance stored in the `database.txt` file. It then displays a success message along with the updated account balance.

## Usage

1. **Compilation:**
   - Ensure you have a C compiler (e.g., GCC) installed on your system.
   - Compile the source files (`main.c`, `card.c`, `server.c`, `terminal.c`, `GetTime.c`) using the following command:
     ```
     gcc main.c card.c server.c terminal.c GetTime.c -o payment_app
     ```
   - This will generate an executable file named `payment_app`.

2. **Running the Application:**
   - Execute the application by running the generated executable:
     ```
     ./payment_app
     ```

3. **Payment Process:**
   - Follow the instructions displayed on the console to enter the required cardholder information and the payment amount.
   - The application will provide appropriate feedback at each step, ensuring a smooth payment process.

## Database (`database.txt`)

The `database.txt` file serves as the system's database, containing cardholder information. It is formatted with each line representing a different card entry. Each line includes the cardholder name, expiration date, PAN, and the account balance.

**Database Structure:**
```
<Cardholder Name> <Expiration Date> <PAN> <Account Balance>
```

**Example Entry:**
```
John Doe 07/24 1234567890123456 5000
```

## Note

The Payment Application is designed for educational purposes and simulation only. It does not perform actual financial transactions and should not be used for real-world payment processing.

## License

This Payment Application is distributed under the MIT License. Please refer to the [LICENSE](LICENSE) file for more information.

## Author

This Payment Application was created by Eng. Mahmoud Abdelraoof Mahmoud.

**Thank you for using the Payment Application!**
