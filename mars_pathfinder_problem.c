#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>

pthread_mutex_t dataBusMutex = PTHREAD_MUTEX_INITIALIZER;

// Simulated functions for sending images, communicating, and retrieving meteorological data
void sendImages() {
    // Simulating sending images (high priority task)
    printf("Sending images to earth...\n");
    // Simulated delay for sending images
    sleep(2);
}

void communicate() {
    // Simulating communication task (medium priority)
    printf("Communicating with earth...\n");
    // Simulated delay for communication
    sleep(1);
}

void getMeteorologicalData() {
    // Simulating getting meteorological data (low priority task)
    printf("Retrieving meteorological data...\n");
    // Simulated delay for getting data
    while (1) {
        // This task keeps the mutex locked, causing an indefinite wait
        pthread_mutex_lock(&dataBusMutex);
    }
}

void* timerFunction(void* arg) {
    sleep(10); // Wait for 10 seconds
    printf("Resetting the system! All images are lost.\n");
    exit(0); // Reset the system
}

void* taskRunner(void* arg) {
    pthread_t timerThread;
    pthread_create(&timerThread, NULL, timerFunction, NULL);

    while (1) {
        sendImages();  // High priority task
        communicate(); // Medium priority task
        getMeteorologicalData(); // Low priority task (with an indefinite lock)
    }

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, taskRunner, NULL);

    pthread_join(thread, NULL);
    return 0;
}