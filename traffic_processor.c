#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct
{
    unsigned char camera_id;
    unsigned char waiting_cars;
    unsigned char priority_vehicle;
} CameraData;

int main()
{
    char *last_side = "";                                        // create a variable that will hold the last side that was made to go
    int size = 10;                                               // Number of CameraData structures to read
    CameraData *camera_data = malloc(sizeof(CameraData) * size); // Allocate memory for 10 CameraData structures
    if (camera_data == NULL)
    {
        printf("Error allocating memory\n");
        return 1;
    }
    FILE *cameras_info = fopen("cameras_info.text", "w");
    FILE *cameras_file = fopen("cameras.bin", "rb");
    if (cameras_file == NULL || cameras_info == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    unsigned char camera_id;
    unsigned char waiting_cars;
    unsigned char priority_vehicle;

    int things_in_malloc = 0;

    while (fread(&camera_id, sizeof camera_id, 1, cameras_file) == 1 &&
           fread(&waiting_cars, sizeof waiting_cars, 1, cameras_file) == 1 &&
           fread(&priority_vehicle, sizeof priority_vehicle, 1, cameras_file) == 1)
    {
        if (size <= things_in_malloc)
        {
            size *= 2;
            camera_data = realloc(camera_data, sizeof(CameraData) * size);
            if (camera_data == NULL)
            {
                printf("Error reallocating memory\n");
                return 1;
            }
        }

        camera_data[things_in_malloc].camera_id = camera_id;
        camera_data[things_in_malloc].waiting_cars = waiting_cars;
        camera_data[things_in_malloc].priority_vehicle = priority_vehicle;

        things_in_malloc++;
    }
    for (int i = 0; i < things_in_malloc; i++)
    {
        fprintf(cameras_info, "Camera %d:\n", (i % 4) + 1);
        fprintf(cameras_info, "camera id: %hhu\n", camera_data[i].camera_id);
        fprintf(cameras_info, "waiting cars: %hhu\n", camera_data[i].waiting_cars);
        fprintf(cameras_info, "priority vehicle: %hhu\n\n", camera_data[i].priority_vehicle);

        if (i % 4 != 3)
        {
            continue; // Skip to the next iteration if not at the end of a group of 4 cameras
        }

        char *decision = "";

        fprintf(cameras_info, "Decision: ");
        decision = (camera_data[i - 3].priority_vehicle == 1) ? "north" : "no";
        decision = (camera_data[i - 2].priority_vehicle == 1) ? "south" : decision;
        if (strcmp(last_side, "north-south") != 0)
        {
            decision = (camera_data[i - 1].priority_vehicle == 1) ? "east" : decision;
            decision = (camera_data[i - 0].priority_vehicle == 1) ? "west" : decision;
        }
        if (strcmp(decision, "no") != 0)
        {

            if (strcmp(decision, "north") == 0 || strcmp(decision, "south") == 0)
            {
                last_side = "north-south";
            }
            else
            {
                last_side = "east-west";
            }

            fprintf(cameras_info, "%s is turned to green!\n\n", last_side);

            continue;
        }

        if (camera_data[i - 3].waiting_cars + camera_data[i - 2].waiting_cars > camera_data[i - 1].waiting_cars + camera_data[i].waiting_cars)
        {
            decision = "north-south";
        }
        else
        {
            decision = "east-west";
        }
        fprintf(cameras_info, "%s is turned to green!\n\n", decision);
    }

    printf("Data written to cameras_info.text\n");
    free(camera_data);
    fclose(cameras_file);
    fclose(cameras_info);
    return 0;
}