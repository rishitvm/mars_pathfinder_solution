#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t dataBusMutex = PTHREAD_MUTEX_INITIALIZER;

void sendImages() {
    // Simulating sending images (high priority task)
    printf("Sending images to Earth...\n");
    for(int i=1;i<11;i++)
    {
        printf("\t%d",i);
    }
    printf("\n");
    // Simulated delay for sending images
    sleep(2);
}

void communicate() {
    // Simulating communication task (medium priority)
    printf("Ongoing communication with Earth...\n");
    printf("Hello, this message is from Mars Pathfinder\n");
    // Simulated delay for communication
    sleep(1);
}

void getMeteorologicalData() {
    // Simulating getting meteorological data (low priority task)
    printf("Sending meterological data to Earth...\n");
    printf("\tTemperature: 32\n");
    printf("\tWeather: 12\n");
    printf("\tHumidity: 67\n");
    // Simulate priority inheritance
    pthread_mutex_lock(&dataBusMutex);

    // Simulated delay for getting data
    sleep(10); // Simulate holding the mutex for 10 seconds

    pthread_mutex_unlock(&dataBusMutex); // Release the mutex
}

void* taskRunner(void* arg) {
    while (1) {
        sendImages();  // High priority task
        communicate(); // Medium priority task
        getMeteorologicalData(); // Low priority task with mutex
        printf("Maximum waiting time completed.\n");
        printf("Resource released. Rover continuing high priority tasks.\n");
    }

    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, taskRunner, NULL);

    pthread_join(thread, NULL);
    return 0;
}