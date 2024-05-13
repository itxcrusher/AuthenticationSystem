#ifndef auth_h
#define auth_h

//						#################################### Program Interface ####################################

void AuthenticationSystem::run() {
	int choiceNo;
	bool isAuth, isSub, isAdmin, isExit;

	welcome("Authentication System");	// Welcome Message

	do {
		isExit = false;
		text("Authentication Required...Please enter a choice number from the following:");
		cout << "\n1- Signup" << endl;
		cout << "2- Login" << endl;
		cout << "0- Exit" << endl;
		cin >> choiceNo;
		switch (choiceNo) {
		case 1:
			signup();
			cout << "\nRedirecting to the Login Screen...Please wait..." << endl;
		case 2:
			do {
				isAuth = login();
				if (isAuth) {
					isSub = usersDatabase[currentUser]->getSub();
					if (isSub) {
						cout << "\nAuthentication Successful, Press any key to get redirected to the Dashboard!" << endl;
						_getch();
						system("cls");
						isAdmin = usersDatabase[currentUser]->getAdmin();
						(isAdmin) ? showMenu(isAdmin) : showMenu();
					}
					else {
						cout << "\nThis user has unsubscribed from our system, Please contact support for further details..." << endl;
					}
				}
				else {
					cout << "\nIncorrect Password for this ID, Please try Again!" << endl;
				}
			} while (true);
			break;
		case 0:
			farewell();	// Farewell Message
			isExit = true;
			break;
		default:
			cout << "\nPlease enter a valid choice number!" << endl;
		}
	} while (!isExit);
}

//						#################################### Sign Up ####################################

void AuthenticationSystem::signup() {
	heading("SignUp to System");
	cout << "\nPlease enter the following details to complete the signup process!" << endl;
	addNewUser();
}

//						------------------------------------ Add New User ------------------------------------

void AuthenticationSystem::addNewUser() {
	string userName, userEmail, userPassword, confirmPass;
	bool isStrong;
	cout << "Name: ";
	cin >> userName;
	cout << "Email address: ";
	cin >> userEmail;
	userPassword = enterPassword();

	increaseCapacity();
	usersDatabase[totalUsers] = new User;
	usersDatabase[totalUsers]->setData(totalUsers, userName, userEmail, userPassword);

	cout << "\nA new User Account has been created Successfully!" << endl;
	cout << "User ID: " << totalUsers << endl;
	totalUsers++;
	putchar('\n');
	separator(100);
}

//						#################################### Log In ####################################

bool AuthenticationSystem::login() {
	int userID;
	string userPassword;
	bool invalid;

	heading("Login to System");
	do {
		invalid = false;
		cout << "\nPlease enter your ID" << endl;
		cout << "ID: ";
		cin >> userID;
		if (userID < 0 || userID >= totalUsers) {
			cout << "\nInvalid ID, Please try again!" << endl;
			invalid = true;
		}
	} while (invalid);
	cout << "\nPlease enter your Password" << endl;
	userPassword = hiddenPassword();

	return auth(userID, userPassword);
}

//					------------------------------------ Password Verification ------------------------------------

bool AuthenticationSystem::auth(int id, string pass) {
	bool match;
	string password = encryptDecrypt(usersDatabase[id]->getPassword(), true);
	match = (password == pass) ? true : false;
	if (match) { currentUser = id; }
	return match;
}

//					------------------------------------ Add Dummy Users Data ------------------------------------

void AuthenticationSystem::startUsersData() {
	// Admin
	usersDatabase[totalUsers] = new User;
	usersDatabase[totalUsers]->setData(totalUsers, "Admin", "admin@mail.com", "123", true, true);
	totalUsers++;
	// User
	usersDatabase[totalUsers] = new User;
	usersDatabase[totalUsers]->setData(totalUsers, "User", "user@mail.com", "123", false, true);
	totalUsers++;
}

//					------------------------------------ Double Users Capacity ------------------------------------

void AuthenticationSystem::increaseCapacity() {
	if (totalUsers == initialCapacity) {
		int doubleCapacity = initialCapacity * 2;
		User** doubleUsersDatabase = new User * [doubleCapacity];
		for (int i = 0; i < totalUsers; i++) {
			doubleUsersDatabase[i] = usersDatabase[i];  // assigned all values of old array to new double array
		}
		delete[] usersDatabase;   // deleted old array
		usersDatabase = doubleUsersDatabase;    // assigned address of new double array to old pointer
	}
}

//					#################################### Menu for User ####################################

void AuthenticationSystem::showMenu(){
	int choiceNo;
	string welcomeMsg;
	bool goBack;
	do {
		welcomeMsg = "Welcome to the User Dashboard " + usersDatabase[currentUser]->getName();
		heading(welcomeMsg);
		goBack = false;

		cout << "\nPlease enter your choice number from the following list:" << endl;
		cout << "1- Account Details" << endl;
		cout << "2- Change Email" << endl;
		cout << "3- Show Password" << endl;
		cout << "4- Change Password" << endl;
		cout << "5- Logout" << endl;
		cout << "6- Unsubscribe" << endl;
		cin >> choiceNo;

		switch (choiceNo) {
		case 1:
			usersDatabase[currentUser]->accountDetails();
			break;
		case 2:
			usersDatabase[currentUser]->changeEmail();
			break;
		case 3:
			usersDatabase[currentUser]->decryptPass();
			break;
		case 4:
			usersDatabase[currentUser]->changePass();
			break;
		case 5:
			goBack = true;
			cout << "\nSaving Files...Logging Out..." << endl;
			break;
		case 6:
			cout << "\nAre you sure you want to unsubscribe from this system? (Press 1 to confirm)" << endl;
			cin >> choiceNo;
			if (choiceNo == 1) {
				goBack = true;
				usersDatabase[currentUser]->unsub();
			}
			else {
				cout << "\nProcess Cancelled by the User!" << endl;
			}
			break;
		default:
			cout << "\nPlease choose a valid choice number from the given list!" << endl;
		}
	} while (!goBack);
}

//					------------------------------------ Account Details ------------------------------------

//cout << "Encrypted Password: " << usersDatabase[userID]->getPassword() << endl;
//					#################################### Menu for Admin ####################################

void AuthenticationSystem::showMenu(bool isAdmin) {
	int choiceNo;
	string welcomeMsg;
	bool goBack;
	do {
		welcomeMsg = "Welcome to the Admin Dashboard " + usersDatabase[currentUser]->getName();
		heading(welcomeMsg);
		goBack = false;

		cout << "\nPlease enter your choice number from the following list:" << endl;
		cout << "1- Account Details" << endl;
		cout << "2- Add a User" << endl;
		cout << "3- Delete a User" << endl;
		cout << "4- Change your Email" << endl;
		cout << "5- Show Password" << endl;
		cout << "6- Change your Password" << endl;
		cout << "7- Change the Email of a given User" << endl;
		cout << "8- Decrypt Password of a User" << endl;
		cout << "9- Change the Password of a given User" << endl;
		cout << "10- Display the records of all Existing Users" << endl;
		cout << "11- Display the records of Deleted Users" << endl;
		cout << "0- Logout" << endl;
		cin >> choiceNo;

		switch (choiceNo) {
		case 1:
			usersDatabase[currentUser]->accountDetails();
			break;
		case 2:
			heading("Add new User");
			cout << "\nPlease enter the following details to add a new user account to the System!" << endl;
			addNewUser();
			break;
		case 3:
			deleteUser();
			break;
		case 4:
			usersDatabase[currentUser]->changeEmail();
			break;
		case 5:
			usersDatabase[currentUser]->decryptPass();
			break;
		case 6:
			usersDatabase[currentUser]->changePass();
			break;
		case 7:
			changeUserEmail();
			break;
		case 8:
			decryptUserPass();
			break;
		case 9:
			changeUserPass();
			break;
		case 10:
			showSubs();
			break;
		case 11:
			showDels();
			break;
		case 0:
			goBack = true;
			cout << "\nSaving Files...Logging Out..." << endl;
			break;
		default:
			cout << "\nPlease choose a valid choice number from the given list!" << endl;
		}
	} while (!goBack);
}

//					------------------------------------ Delete a User ------------------------------------
void AuthenticationSystem::deleteUser() {
	int choiceNo, userID;
	bool isAdmin, isSub;

	heading("Delete a User");
	cout << "Please enter the ID of the User that you want to remove from the System!" << endl;
	cout << "ID: ";
	cin >> userID;
	isSub = usersDatabase[userID]->getSub();
	isAdmin = usersDatabase[userID]->getAdmin();
	if (!isSub) {
		cout << "\nThis User's Account is deleted already!" << endl;
	}
	else if (isAdmin) {
		cout << "\nThis is an Admin account and cannot be deleted!" << endl;
	}
	else {
		cout << "\nFollowing are the details of the user ID: " << userID << endl;
		cout << "Name: " << usersDatabase[userID]->getName() << endl;
		cout << "Email: " << usersDatabase[userID]->getEmail() << endl;
		cout << "Encrypted Password: " << usersDatabase[userID]->getPassword() << endl;
		cout << "\nPress 1 to delete or Press any other key to skip" << endl;
		cin >> choiceNo;
		if (choiceNo == 1) {
			usersDatabase[userID]->setSub(false);
			cout << "\nThe User ID " << userID << " has been deleted!" << endl;
		}
		else {
			cout << "\nThis Process has been cancelled!" << endl;
		}
	}
}

//					------------------------------------ Change Email of a User ------------------------------------

void AuthenticationSystem::changeUserEmail() {
	int userID;
	string userEmail;
	bool isAdmin, isSub;

	heading("Change Email of a User");
	cout << "Please enter the ID of the User that you want to change the email of!" << endl;
	cout << "ID: ";
	cin >> userID;
	isSub = usersDatabase[userID]->getSub();
	isAdmin = usersDatabase[userID]->getAdmin();
	if (!isSub) {
		cout << "\nThis User's Account has been deleted!" << endl;
	}
	else if (isAdmin) {
		cout << "\nThis is an Admin account and its Email cannot be change by others!" << endl;
	}
	else {
		cout << "\nFollowing are the details of the user ID: " << userID << endl;
		cout << "Name: " << usersDatabase[userID]->getName() << endl;
		cout << "Email: " << usersDatabase[userID]->getEmail() << endl;
		cout << "Encrypted Password: " << usersDatabase[userID]->getPassword() << endl;
		cout << "\nPlease enter new email of this account!" << endl;
		cout << "New Email: ";
		cin >> userEmail;
		usersDatabase[userID]->setEmail(userEmail);
		cout << "\nThe Email Address of User ID: " << userID << " has been changed to " << usersDatabase[userID]->getEmail() << endl;
	}
}

//					------------------------------------ Decrypt Password of a User ------------------------------------
void AuthenticationSystem::decryptUserPass() {
	int choiceNo, userID;
	string userPass;
	bool isAdmin, isSub;

	heading("Decrypt Password of a User");
	cout << "Please enter the ID of the User that you want to decrypt the Password of!" << endl;
	cout << "ID: ";
	cin >> userID;
	isSub = usersDatabase[userID]->getSub();
	isAdmin = usersDatabase[userID]->getAdmin();
	if (!isSub) {
		cout << "\nThis User's Account has been deleted!" << endl;
	}
	else if (isAdmin) {
		cout << "\nThis is an Admin account and its Password cannot be decrypted!" << endl;
	}
	else {
		cout << "\nFollowing are the details of the user ID: " << userID << endl;
		cout << "Name: " << usersDatabase[userID]->getName() << endl;
		cout << "Email: " << usersDatabase[userID]->getEmail() << endl;
		cout << "Encrypted Password: " << usersDatabase[userID]->getPassword() << endl;
		cout << "\nPress 1 to decrypt or Press any other key to skip" << endl;
		cin >> choiceNo;
		if (choiceNo == 1) {
			userPass = encryptDecrypt(usersDatabase[userID]->getPassword(), true);
			cout << "\nDecrypted Password: " << userPass << endl;
		}
		else {
			cout << "\nThis Process has been cancelled!" << endl;
		}
	}
}

//					------------------------------------ Change Password of a User ------------------------------------
void AuthenticationSystem::changeUserPass() {
	int choiceNo, userID;
	string userPass;
	bool isAdmin, isSub;

	heading("Change Password of a User");
	cout << "Please enter the ID of the User that you want to change the Password of!" << endl;
	cout << "ID: ";
	cin >> userID;
	isSub = usersDatabase[userID]->getSub();
	isAdmin = usersDatabase[userID]->getAdmin();
	if (!isSub) {
		cout << "\nThis User's Account has been deleted!" << endl;
	}
	else if (isAdmin) {
		cout << "\nThis is an Admin account and its Password cannot be change by others!" << endl;
	}
	else {
		cout << "\nFollowing are the details of the user ID: " << userID << endl;
		cout << "Name: " << usersDatabase[userID]->getName() << endl;
		cout << "Email: " << usersDatabase[userID]->getEmail() << endl;
		cout << "Encrypted Password: " << usersDatabase[userID]->getPassword() << endl;
		cout << "\nPlease enter the new password of User ID: " << userID << endl;
		userPass = enterPassword();
		usersDatabase[userID]->setPass(userPass);
		cout << "\nThe Password of User ID: " << userID << " has been changed successfully!" << endl;
	}
}

//					------------------------------------ Display Subscribed Users ------------------------------------
void AuthenticationSystem::showSubs() {
	string role;
	bool isSub;

	heading("Subscribed Users");
	for (int i = 0; i < totalUsers; i++) {
		isSub = usersDatabase[i]->getSub();
		if (isSub) {
			role = (usersDatabase[i]->getAdmin()) ? "Admin" : "User";
			cout << "ID: " << i << endl;
			cout << "Name: " << usersDatabase[i]->getName() << endl;
			cout << "Email: " << usersDatabase[i]->getEmail() << endl;
			cout << "Encrypted Password: " << usersDatabase[i]->getPassword() << endl;
			cout << "Role: " << role << endl;
			separator(100);
		}
	}
}

//					------------------------------------ Display Deleted Users ------------------------------------
void AuthenticationSystem::showDels() {
	string role;
	bool isSub;

	heading("Deleted Users");
	for (int i = 0; i < totalUsers; i++) {
		isSub = usersDatabase[i]->getSub();
		if (!isSub) {
			role = (usersDatabase[i]->getAdmin()) ? "Admin" : "User";
			cout << "ID: " << i << endl;
			cout << "Name: " << usersDatabase[i]->getName() << endl;
			cout << "Email: " << usersDatabase[i]->getEmail() << endl;
			cout << "Encrypted Password: " << usersDatabase[i]->getPassword() << endl;
			cout << "Role: " << role << endl;
			separator(100);
		}
	}
}

#endif

// Task
// Confirmation Message for successful email and password setup
// Encryption & Decryption of Passwords