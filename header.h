#ifndef header_h   // If not defined
#define header_h   // Define

// include Libraries
#include <iostream>	// cin cout
#include <cmath>	// math functions
#include <string>	// string operations
#include <conio.h>	// getch

using namespace std;    // use namespace standard

// Welcome Message
void welcome(string message) {
    int messageLength = message.length() + 32;
    cout << "\n\t\t";
    for (int i = 0; i < messageLength; i++) {
        putchar('#');
    }
    cout << "\n\t\t### Welcome to the " << message << " Program! ###\n\t\t";
    for (int i = 0; i < messageLength; i++) {
        putchar('#');
    }
    cout << "\n" << endl;
}

// Heading
void heading(string heading) {
    int headingLength = heading.length() + 6;
    cout << "\n\t\t";
    for (int i = 0; i < headingLength; i++) {
        putchar('=');
    }
    cout << "\n\t\t|| " << heading << " ||\n\t\t";
    for (int i = 0; i < headingLength; i++) {
        putchar('=');
    }
    putchar('\n');
}

// Sub-Heading
void subHeading(string subHeading) {
    int subHeadingLength = subHeading.length() + 4;
    cout << "\n\t";
    for (int i = 0; i < subHeadingLength; i++) {
        putchar('-');
    }
    cout << "\n\t| " << subHeading << " |\n\t";
    for (int i = 0; i < subHeadingLength; i++) {
        putchar('-');
    }
    putchar('\n');
}

// Text box
void text(string text) {
    int textLength = text.length();
    putchar('\n');
    for (int i = 0; i < textLength; i++) {
        putchar('-');
    }
    putchar('\n');
    cout << text << endl;
    for (int i = 0; i < textLength; i++) {
        putchar('-');
    }
    putchar('\n');
}

// Dash Separator
void separator(int count) {
    for (int i = 0; i < count; i++) {
        putchar('-');
    }
    putchar('\n');
}

// Farewell Message
void farewell() {
    int messageLength = 57;
    cout << "\n\t\t";
    for (int i = 0; i < messageLength; i++) {
        putchar('#');
    }
    cout << "\n\t\t### Thank you for using our Program, have a nice day! ###\n\t\t";
    for (int i = 0; i < messageLength; i++) {
        putchar('#');
    }
    putchar('\n');
}

// Hidden Password
string hiddenPassword() {
    string password = "";
    char pass;

    cout << "Password: ";
    while (true) {
        pass = _getch();
        if (pass == '\r') {
            break;
        }
        password += pass;
        cout << "*";
    }
    putchar('\n');
    return password;
}

// Check Password Strength
int passwordStrength(string password) {
    int size = password.size(), points = -1;
    bool strength[3] = { false, false, false };

    if (size >= 8) {
        points++;
        for (int i = 0; i < size; i++) {
            if (isupper(password[i])) { strength[0] = true; }   // Uppercase Letter
            if (isdigit(password[i])) { strength[1] = true; }   // Numeric
            if (!isalnum(password[i])) { strength[2] = true; }  //  Special Character
        }
        if (strength[0]) { points++; }
        if (strength[1]) { points++; }
        if (strength[2]) { points++; }
    }
    return points;
}

// Encryption/Decryption
string encryptDecrypt(string text, bool isEncrypted) {   // text, false to encrypt
    int size = text.size();
    if (isEncrypted) {
        for (int i = 0; (i < size && text[i] != '\0'); i++) {
            text[i] = text[i] - 3;
        }
    }
    else {
        for (int i = 0; (i < size && text[i] != '\0'); i++) {
            text[i] = text[i] + 3;
        }
    }
    return text;
}

#endif  // End If