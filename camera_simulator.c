#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(NULL)); // Seed the random number generator
    FILE *cameras_file = fopen("cameras.bin", "wb");
    if (cameras_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    for (int i = 0; i < 12; i++) {
        /* Creating and adding random values for the camera
        1. Camera ID - number 0-3; ID 0: North, 1: South, 2: East, 3: West
        2. Number of cars waiting at the traffic light - random number 0-255
        3. Whether a priority vehicle is present - random number 0-1; 0: no, 1: yes
        */
        unsigned char camera_id = i % 4; // camera ID between 0 and 3
        unsigned char waiting_cars = rand() % 256; // Random number of waiting cars
        unsigned char priority_vehicle = rand() % 4; // Random number for priority vehicle (0 or 1)
        if (priority_vehicle > 1) {
            priority_vehicle = 0; // Ensure priority vehicle is either 0 or 1
        }

        
        fwrite(&camera_id, sizeof(unsigned char), 1, cameras_file);
        fwrite(&waiting_cars, sizeof(unsigned char), 1, cameras_file);
        fwrite(&priority_vehicle, sizeof(unsigned char), 1, cameras_file);



    }

    fclose(cameras_file);
    return 0;
}