#define _CRT_SECURE_NO_WARNINGS // to use fopen_s 

#include <stdio.h>
#include <string.h>

int main() {
    char ch;
    char password[20];
    char saved_password[20];
    int n;

start:

    printf("Enter your password: ");

    // In case the password is entered incorrectly, reset password array so that the next attempt works without errors.
    memset(password, 0, sizeof(password));

    // A loop that reads the password with input validation 
    int i = 0;
    while ((ch = getchar()) != '\n' && i < 19) {
        password[i++] = ch;
        printf("*"); // Password secrecy
    }
    password[i] = '\0'; // Terminate with null character

    printf("\nYou entered %s \n", password);


    //Open password file with error handling
    FILE* ptr;
    errno_t error = fopen_s(&ptr, "password.txt", "r");
    if (error != 0 || ptr == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    // Read saved password from file with error handling
    if (fscanf(ptr, "%s", saved_password) != 1) {
        printf("Error reading password from file.\n");
        fclose(ptr);
        return 1;
    }
    fclose(ptr);

    // Terminate with null character
    saved_password[strlen(saved_password)] = '\0';


    // Password comparison with informative message
    n = strcmp(password, saved_password);

    if (n == 0) {
        printf("LOGIN SUCCESSFULLY\n");
    }
    else {
        printf("INCORRECT PASSWORD\n");
        goto start; // Jump back to password entry upon failure
    }

    return 0;
}
