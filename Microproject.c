#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EVENTS 100
#define MAX_USERS 50
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

struct Event {
    char name[50];
    char date[20];
    char description[200];
};

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct Event events[MAX_EVENTS];
int eventCount = 0;

struct User users[MAX_USERS];
int userCount = 0;

int login();
void signup();
void saveEventsToFile();
void loadEventsFromFile();
void createEvent();
void viewEvents();
void updateEvent();
void registerParticipants();

int main() {
    loadEventsFromFile();

    printf("Welcome to Eventify - Your Event Management System!\n");

    int loggedIn = 0;
    while (!loggedIn) {
        printf("\nPlease choose an option:\n");
        printf("1. Log in\n");
        printf("2. Sign up\n");
        printf("3. Exit\n");

        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                loggedIn = login();
                break;
            case 2:
                signup();
                break;
            case 3:
                printf("\nExiting Eventify. Goodbye!\n");
                saveEventsToFile();
                exit(0);
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
                break;
        }
    }

    while (loggedIn) {
        printf("\nMain Menu:\n");
        printf("1. Create a new event\n");
        printf("2. View existing events\n");
        printf("3. Update event details\n");
        printf("4. Register participants for an event\n");
        printf("5. Log out\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createEvent();
                break;
            case 2:
                viewEvents();
                break;
            case 3:
                updateEvent();
                break;
            case 4:
                registerParticipants();
                break;
            case 5:
                printf("\nLogging out...\n");
                loggedIn = 0;
                break;
            default:
                printf("\nInvalid choice! Please enter a number between 1 and 5.\n");
                break;
        }
    }

    saveEventsToFile();
    printf("\nGoodbye!\n");

    return 0;
}

int login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("\nEnter username:  \n");
    scanf("%s", username);
    printf("Enter password: \n");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("\nLogin successful!\n");
            return 1;
        }
    }

    printf("\nLogin failed. Invalid username or password.\n");
    return 0;
}

void signup() {
    if (userCount >= MAX_USERS) {
        printf("\nCannot sign up more users. User limit reached.\n");
        return;
    }

    printf("\nEnter new username: ");
    scanf("%s", users[userCount].username);

    printf("Enter new password: ");
    scanf("%s", users[userCount].password);

    userCount++;
    printf("\nSign up successful! Please log in to continue.\n");
}

void saveEventsToFile() {
    FILE *fp = fopen("events.txt", "w");
    if (fp == NULL) {
        printf("\nError opening file to save events.\n");
        return;
    }

    for (int i = 0; i < eventCount; i++) {
        fprintf(fp, "%s,%s,%s\n", events[i].name, events[i].date, events[i].description);
    }

    fclose(fp);
}

void loadEventsFromFile() {
    FILE *fp = fopen("events.txt", "r");
    if (fp == NULL) {
        printf("\nNo events file found. Starting with no events.\n");
        return;
    }

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", events[eventCount].name, events[eventCount].date, events[eventCount].description) == 3) {
        eventCount++;
    }

    fclose(fp);
}

void createEvent() {
    if (eventCount >= MAX_EVENTS) {
        printf("\nCannot create more events. Event limit reached.\n");
        return;
    }

    printf("\nEnter event details:\n");
    printf("Event name: ");
    scanf(" %[^\n]", events[eventCount].name);

    printf("Event date (YYYY-MM-DD): ");
    scanf(" %s", events[eventCount].date);

    printf("Event description: ");
    scanf(" %[^\n]", events[eventCount].description);

    eventCount++;
    printf("\nEvent '%s' created successfully!\n", events[eventCount - 1].name);
}

void viewEvents() {
    if (eventCount == 0) {
        printf("\nNo events found.\n");
        return;
    }

    printf("\nList of Events:\n");
    for (int i = 0; i < eventCount; i++) {
        printf("\nEvent %d\n", i + 1);
        printf("Name: %s\n", events[i].name);
        printf("Date: %s\n", events[i].date);
        printf("Description: %s\n", events[i].description);
    }
}

void updateEvent() {
    if (eventCount == 0) {
        printf("\nNo events found to update.\n");
        return;
    }

    printf("\nEnter event number to update (1 to %d): ", eventCount);
    int eventNumber;
    scanf("%d", &eventNumber);
    eventNumber--; // Adjust for zero-indexed array

    if (eventNumber < 0 || eventNumber >= eventCount) {
        printf("\nInvalid event number.\n");
        return;
    }

    printf("\nCurrent event details:\n");
    printf("Name: %s\n", events[eventNumber].name);
    printf("Date: %s\n", events[eventNumber].date);
    printf("Description: %s\n", events[eventNumber].description);

    printf("\nEnter new event name: ");
    scanf(" %[^\n]", events[eventNumber].name);

    printf("Enter new event date (YYYY-MM-DD): ");
    scanf(" %s", events[eventNumber].date);

    printf("Enter new event description: ");
    scanf(" %[^\n]", events[eventNumber].description);

    printf("\nEvent details updated successfully!\n");
}  

void registerParticipants() {
    if (eventCount == 0) {
        printf("\nNo events found for participant registration.\n");
        return;
    }

    printf("\nEnter event number to register participants (1 to %d): ", eventCount);
    int eventNumber;
    scanf("%d", &eventNumber);
    eventNumber--; // Adjust for zero-indexed array

    if (eventNumber < 0 || eventNumber >= eventCount) {
        printf("\nInvalid event number.\n");
        return;
    }

    printf("\nParticipant registration for event '%s':\n", events[eventNumber].name);
    printf("Enter participant name: ");
    char participantName[50];
    scanf(" %[^\n]", participantName);
    printf("Participant '%s' registered successfully for event '%s'!\n", participantName, events[eventNumber].name);
}
