#include "header.h"

string enterPassword();

//						#################################### User Class ####################################

class User {
private:
	int id;
	string name, email, password;
	bool isAdmin, isSub;
public:
	void setData(int id, string name, string email, string password, bool isAdmin = false, bool isSub = true) {
		this->id = id;
		this->name = name;
		this->email = email;
		this->password = encryptDecrypt(password, false);
		this->isAdmin = isAdmin;
		this->isSub = isSub;
	}
	// Getter Functions
	string getName() { return name; }
	string getEmail() { return email; }
	string getPassword() { return password; }
	bool getAdmin() { return isAdmin; }
	bool getSub() { return isSub; }

	// Setter Functions
	void setEmail(string email) { this->email = email; }
	void setPass(string pass) { this->password = encryptDecrypt(pass, false); }
	void setSub(bool sub) { this->isSub = sub; }

	// Instance Member Function
	void accountDetails();
	void changeEmail();
	void decryptPass();
	void changePass();
	void unsub() { this->isSub = false; }
	
	// Friend Function
	friend string enterPassword();
};

#include "user.h"	// Header file for User

//						#################################### Authentication System Class ####################################

class AuthenticationSystem {
private:
	int initialCapacity = 20;
	User** usersDatabase = new User * [initialCapacity];
	int totalUsers = 0, currentUser;

	// Private Functions
	void increaseCapacity();	// Double Users Capacity
	bool auth(int, string);		// Authenticate Password

public:
	void run();		// Program Interface
	void signup();	// Signup Process
	bool login();	// Login Process
	void showMenu();	// User Dashboard
	void showMenu(bool);	// Admin Dashboard
	void startUsersData();	// Admin and initial Users Data

	// Admin Functions
	void addNewUser();
	void deleteUser();
	void changeUserEmail();
	void decryptUserPass();
	void changeUserPass();
	void showSubs();
	void showDels();

	// Friend Function
	friend string enterPassword();
};

#include "auth.h"	// Header file for Authentication System

//				#################################### Main Function ####################################

int main() {
	AuthenticationSystem auth;
	auth.startUsersData();		// Add Dummy Data
	auth.run();
	return 0;
}

//				#################################### Friend Function for Password Process ####################################

string enterPassword() {
	int passPoints;
	string userPassword, confirmPass;
	do {	// loop Until Password is confirmed
		do {	// Prompt until user enters a strong Password
			cout << "\nPlease enter a Strong Password!" << endl;
			userPassword = hiddenPassword();
			passPoints = passwordStrength(userPassword);

			cout << "\nThe entered Password ";
			switch (passPoints) {
			case 1:
				cout << "is Weak!" << endl;
				break;
			case 2:
				cout << "is Medium!" << endl;
				break;
			case 3:
				cout << "is Strong!" << endl;
				break;
			case 0:
				cout << "must contain 1 Capital, 1 Numeric, and 1 Special Character!" << endl;
				break;
			default:
				cout << "must contain at least 8 characters!" << endl;
			}
			if (passPoints != 3) {
				putchar('\n');
				separator(100);
			}
		} while (passPoints != 3);

		// Prompt for Password Confirmation
		cout << "\nPlease confirm the Password!" << endl;
		confirmPass = hiddenPassword();

		if (userPassword == confirmPass) { return userPassword; }
	} while (true);
}