#ifndef user_h
#define user_h

// Instance Member Function
void User :: accountDetails() {
	subHeading("Account Details");
	cout << "\nID: " << id << endl;
	cout << "Name: " << name << endl;
	cout << "Email: " << email << endl;
	separator(100);
}
void User::changeEmail() {
	subHeading("Change your Email");
	cout << "\nCurrent Email: " << email << endl;
	cout << "New Email: ";
	cin >> this->email;
	cout << "\nEmail has been changed successfully!" << endl;
	separator(100);
}
void User::decryptPass() {
	subHeading("Decrypt Password");
	cout << "\nEncrypted Password: " << password << endl;
	cout << "Decrypted Password: " << encryptDecrypt(password, true) << endl;
	separator(100);
}
void User::changePass() {
	subHeading("Change your Password");
	cout << "\nPlease enter your new Password" << endl;
	this->password = encryptDecrypt(enterPassword(), false);
	cout << "\nPassword has been changed successfully!" << endl;
	separator(100);
}
#endif