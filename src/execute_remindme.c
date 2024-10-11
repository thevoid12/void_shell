#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep()
#include <string.h> 
#include <pthread.h> // For threading

typedef struct {
    int time;          // Time to wait in seconds
    const char *message; // Message to print after the wait
} ReminderArgs;

// Function to be executed in a separate thread
void* reminder_thread(void *args) {
    ReminderArgs *reminder = (ReminderArgs *)args;

    // Sleep for the specified time
    sleep(reminder->time);

    // Print the reminder message
    printf("Reminder: %s\n", reminder->message);

    // Free the allocated memory for reminder args
    free(reminder);
    return NULL;
}

void execute_remindme(int time, const char *message) {
    // Prepare the message for printing
    const char *result;

    if (message[0] == '"') {
        char *start = (char *)message + 1;  // Skip the opening double quote
        char *end = strrchr(start, '"');  // Find the last closing double quote
        if (end != NULL) {
            // Temporarily replace the closing quote with a null terminator to print the value inside the quotes
            *end = '\0';
            result = start;
        } else {
            // No closing quote found
            printf("Reminder: missing closing double quote\n");
            return; // Exit early since there's no valid message
        }
    } else {
        // No quotes, print the arguments as they are
        result = message;      
    }

    // Create a thread for the reminder
    ReminderArgs *args = malloc(sizeof(ReminderArgs));
    if (args == NULL) {
        fprintf(stderr, "Failed to allocate memory for reminder args\n");
        return;
    }
    args->time = time;
    args->message = result;

    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, reminder_thread, args) != 0) {
        fprintf(stderr, "Failed to create thread\n");
        free(args); // Clean up allocated memory on error
        return;
    }

    // Detach the thread so we don't need to join it later
    pthread_detach(thread_id);

    printf("Waiting for the reminder...\n"); // Optional message
}
