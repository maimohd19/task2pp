#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} NormalUser;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int accessLevel;
} AdminUser;

typedef union {
    NormalUser normalUser;
    AdminUser adminUser;
} UserData;

typedef struct {
    bool isActive;
    UserData userData;
} User;

User users[MAX_USERS];
int numUsers = 0;

void registerUser() {
    if (numUsers >= MAX_USERS) {
        printf("Maximum number of users reached.\n");
        return;
    }

    User newUser;

    printf("Enter username: ");
    scanf("%s", newUser.userData.normalUser.username);

    // Check if the username already exists
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].userData.normalUser.username, newUser.userData.normalUser.username) == 0) {
            printf("Username already exists. Please choose a different username.\n");
            return;
        }
    }

    printf("Enter password: ");
    scanf("%s", newUser.userData.normalUser.password);

   char active_flag[6];
    bool valid_flag = false;

    while (!valid_flag) {
        printf("Set the active flag (1 or true to activate, 0 or false to deactivate): ");
        scanf("%s", active_flag);

        for (int i = 0; i < strlen(active_flag); i++) {
            active_flag[i] = tolower(active_flag[i]);
        }

        if (strcmp(active_flag, "1") == 0 || strcmp(active_flag, "true") == 0) {
            newUser.isActive = true;
            valid_flag = true;
        } else if (strcmp(active_flag, "0") == 0 || strcmp(active_flag, "false") == 0) {
           newUser.isActive = false;
            valid_flag = true;
        } else {
            printf("Invalid active flag. Please enter 1, 0, true, or false.\n");
        }
    }


    users[numUsers++] = newUser;

    printf("Registration successful.\n");
}

void loginUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].userData.normalUser.username, username) == 0 &&
            strcmp(users[i].userData.normalUser.password, password) == 0) {
            if (users[i].isActive) {
                printf("Login successful.\n");
                return;
            } else {
                printf("User is inactive. Login denied.\n");
                return;
            }
        }
    }

    printf("Invalid username or password.\n");
}

int main() {
    int choice;

    while (1) {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}
