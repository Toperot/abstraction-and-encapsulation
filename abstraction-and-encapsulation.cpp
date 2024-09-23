#include <iostream>
#include <limits>

using namespace std;

//Coded by Kristoffer Ludovice

class Account {
protected:
    double balance;

public:
    Account(double initial_balance) 
	{
        if (initial_balance >= 0) 
		{
            balance = initial_balance;
        } 
		else 
		{
            balance = 0;
            cout << "Invalid initial balance. Setting balance to 0." << endl;
        }
    }

    virtual void deposit(int amount) 
	{
        if (amount > 0) 
		{
            balance += amount;
            cout << "Amount deposited: " << amount << endl;
        } 
		else 
		{
            cout << "Invalid deposit amount!" << endl;
        }
    }

    virtual void withdraw(int amount) = 0;

    void checkBalance() const 
	{
        cout << "Current balance: " << balance << endl;
    }
};

class SavingsAccount : public Account {
    const double minimum_balance = 1000;

public:
    SavingsAccount(double initial_balance) : Account(initial_balance) 
	{
        if (balance < minimum_balance) 
		{
            cout << "Initial balance below minimum. Setting balance to minimum: " << minimum_balance << endl;
            balance = minimum_balance;
        }
    }

    void withdraw(int amount) override 
	{
        if (amount <= 0) 
		{
            cout << "Invalid withdrawal amount!" << endl;
        } 
		else if (balance - amount < minimum_balance) 
		{
            cout << "Withdrawal denied. Minimum balance of " << minimum_balance << " must be maintained." << endl;
        } 
		else 
		{
            balance -= amount;
            cout << "Amount withdrawn: " << amount << endl;
        }
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(double initial_balance) : Account(initial_balance) {}

    void withdraw(int amount) override 
	{
        if (amount <= 0) 
		{
            cout << "Invalid withdrawal amount!" << endl;
        } 
		else if (amount > balance) 
		{
            cout << "Withdrawal denied. Insufficient funds." << endl;
        } 
		else 
		{
            balance -= amount;
            cout << "Amount withdrawn: " << amount << endl;
        }
    }
};

void mainMenu() 
{
    cout << "\nMain Menu" << endl;
    cout << "1 - Savings Account" << endl;
    cout << "2 - Current Account" << endl;
    cout << "3 - Exit" << endl;
    cout << "Choose an option: ";
}

void accountSubMenu() 
{
    cout << "\nSub Menu" << endl;
    cout << "1 - Deposit" << endl;
    cout << "2 - Withdraw" << endl;
    cout << "3 - Check Balance" << endl;
    cout << "4 - Back" << endl;
    cout << "Choose an option: ";
}

int getValidIntegerInput(const string& prompt) 
{
    int input;
    while (true) 
	{
        cout << prompt;
        cin >> input;

        if (cin.fail()) 
		{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a valid integer." << endl;
        } 
		else 
		{
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
    }
}

int main() 
{
    char mainChoice, subChoice;
    SavingsAccount savings(2000);
    CurrentAccount current(1000);

    do 
	{
        mainMenu();
        cin >> mainChoice;

        switch (mainChoice) 
		{
            case '1': 
			{
                Account* account = &savings;
                cout << "\nSavings Account Selected" << endl;

                do 
				{
                    accountSubMenu();
                    cin >> subChoice;

                    switch (subChoice) 
					{
                        case '1': 
						{
                            int amount = getValidIntegerInput("Enter amount to deposit: ");
                            account->deposit(amount);
                            break;
                        }
                        case '2': 
						{
                            int amount = getValidIntegerInput("Enter amount to withdraw: ");
                            account->withdraw(amount);
                            break;
                        }
                        case '3': 
						{
                            account->checkBalance();
                            break;
                        }
                        case '4':
                        {	
                            cout << "Returning to Main Menu..." << endl;
                            break;
                    	}
                        default:
                        {
                            cout << "Invalid option! Try again." << endl;
                            break;
                        }
                    }
                } while (subChoice != '4');
                break;
            }

            case '2': 
			{
                Account* account = &current;
                cout << "\nCurrent Account Selected" << endl;

                do 
				{
                    accountSubMenu();
                    cin >> subChoice;

                    switch (subChoice) 
					{
                        case '1': 
						{
                            int amount = getValidIntegerInput("Enter amount to deposit: ");
                            account->deposit(amount);
                            break;
                        }
                        case '2': 
						{
                            int amount = getValidIntegerInput("Enter amount to withdraw: ");
                            account->withdraw(amount);
                            break;
                        }
                        case '3': 
						{
                            account->checkBalance();
                            break;
                        }
                        case '4':
                    	{
                            cout << "Returning to Main Menu..." << endl;
                            break;
                    	}
                        default:
                        {
                            cout << "Invalid option! Try again." << endl;
                            break;
                        }
                    }
                } while (subChoice != '4');
                break;
            }

            case '3': 
			{
                cout << "Exiting program. Goodbye!" << endl;
                break;
            }

            default: 
			{
                cout << "Invalid option! Try again." << endl;
            }
        }
    } while (mainChoice != '3');

    return 0;
}
