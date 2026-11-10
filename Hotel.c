#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100

struct reservation
{
    int room_no;
    char guest_name[50];
    char check_in[20];
    char check_out[20];
    float price;
};

struct reservation rooms[MAX_ROOMS];
int roomCount = 0;

void pause()
{
    printf("\nPress ENTER to continue...");
    while (getchar() != '\n'); // Clear input buffer properly
    getchar();
}

int login()
{
    char username[20];
    char password[20];
    int attempt = 3;

    while (attempt > 0)
    {
        system("cls");
        printf("===== ADMIN LOGIN =====\n");
        printf("Attempts Left: %d\n\n", attempt);

        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "Name") == 0 && strcmp(password, "1234") == 0)
        {
            printf("\nLogin Successful! Welcome Admin.\n");
            pause();
            return 1;
        }
        else
        {
            attempt--;
            printf("\nWrong Username or Password!\n");

            if (attempt == 0)
            {
                printf("\nToo many failed attempts.\nProgram exiting...\n");
                pause();
                return 0;
            }
            pause();
        }
    }
    return 0;
}

void addReservation()
{
    if (roomCount >= MAX_ROOMS)
    {
        printf("Error: Max room limit reached!\n");
        pause();
        return;
    }

    printf("Enter Room Number: ");
    scanf("%d", &rooms[roomCount].room_no);
    getchar(); // Clear newline from buffer

    printf("Enter Guest Name: ");
    fgets(rooms[roomCount].guest_name, sizeof(rooms[roomCount].guest_name), stdin);
    rooms[roomCount].guest_name[strcspn(rooms[roomCount].guest_name, "\n")] = 0; // Remove trailing newline

    printf("Enter Check-In Date: ");
    fgets(rooms[roomCount].check_in, sizeof(rooms[roomCount].check_in), stdin);
    rooms[roomCount].check_in[strcspn(rooms[roomCount].check_in, "\n")] = 0;

    printf("Enter Check-Out Date: ");
    fgets(rooms[roomCount].check_out, sizeof(rooms[roomCount].check_out), stdin);
    rooms[roomCount].check_out[strcspn(rooms[roomCount].check_out, "\n")] = 0;

    printf("Enter Price: ");
    scanf("%f", &rooms[roomCount].price);

    roomCount++;

    printf("\nReservation added successfully!\n");
    pause();
}

void displayReservations()
{
    if (roomCount == 0)
    {
        printf("No reservations available!\n");
        pause();
        return;
    }

    printf("\n%-10s %-20s %-15s %-15s %-10s\n",
           "Room No", "Guest Name", "Check In", "Check Out", "Price");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < roomCount; i++)
    {
        printf("%-10d %-20s %-15s %-15s %-10.2f\n",
               rooms[i].room_no,
               rooms[i].guest_name,
               rooms[i].check_in,
               rooms[i].check_out,
               rooms[i].price);
    }
    pause();
}

void updateReservation()
{
    int search_room;
    printf("Enter Room Number to update: ");
    scanf("%d", &search_room);

    int flag = 0;

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].room_no == search_room)
        {
            int ch;

            printf("\nWhat do you want to update?\n");
            printf("1. Room Number\n2. Guest Name\n3. Check In\n4. Check Out\n5. Price\n");
            printf("Enter choice: ");
            scanf("%d", &ch);
            getchar(); // Clear buffer

            switch (ch)
            {
            case 1:
                printf("Enter new Room Number: ");
                scanf("%d", &rooms[i].room_no);
                break;

            case 2:
                printf("Enter new Guest Name: ");
                fgets(rooms[i].guest_name, sizeof(rooms[i].guest_name), stdin);
                rooms[i].guest_name[strcspn(rooms[i].guest_name, "\n")] = 0;
                break;

            case 3:
                printf("Enter new Check-In Date: ");
                fgets(rooms[i].check_in, sizeof(rooms[i].check_in), stdin);
                rooms[i].check_in[strcspn(rooms[i].check_in, "\n")] = 0;
                break;

            case 4:
                printf("Enter new Check-Out Date: ");
                fgets(rooms[i].check_out, sizeof(rooms[i].check_out), stdin);
                rooms[i].check_out[strcspn(rooms[i].check_out, "\n")] = 0;
                break;

            case 5:
                printf("Enter new Price: ");
                scanf("%f", &rooms[i].price);
                break;

            default:
                printf("Invalid choice!\n");
            }

            printf("Reservation updated successfully!\n");
            flag = 1;
            break;
        }
    }

    if (!flag)
        printf("Reservation not found!\n");

    pause();
}

void deleteReservation()
{
    int room;
    printf("Enter Room Number to delete: ");
    scanf("%d", &room);

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].room_no == room)
        {
            for (int j = i; j < roomCount - 1; j++)
            {
                rooms[j] = rooms[j + 1];
            }
            roomCount--;

            printf("\nReservation deleted successfully!\n");
            pause();
            return;
        }
    }

    printf("Reservation not found!\n");
    pause();
}

void searchReservation()
{
    int room;
    printf("Enter Room Number to search: ");
    scanf("%d", &room);

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].room_no == room)
        {
            printf("\nReservation Found!\n");
            printf("Room No   : %d\n", rooms[i].room_no);
            printf("Guest     : %s\n", rooms[i].guest_name);
            printf("Check In  : %s\n", rooms[i].check_in);
            printf("Check Out : %s\n", rooms[i].check_out);
            printf("Price     : %.2f\n", rooms[i].price);
            pause();
            return;
        }
    }

    printf("Reservation not found!\n");
    pause();
}

void saveToFile()
{
    FILE *fp = fopen("hotel.txt", "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        fprintf(fp, "%d,%s,%s,%s,%.2f\n", rooms[i].room_no, rooms[i].guest_name,
                rooms[i].check_in, rooms[i].check_out, rooms[i].price);
    }

    fclose(fp);
    printf("Data saved to file successfully!\n");
    pause();
}

void loadFromFile()
{
    FILE *fp = fopen("hotel.txt", "r");
    if (fp == NULL)
    {
        return; // File doesn't exist yet, which is fine
    }

    while (fscanf(fp, "%d,%49[^,],%19[^,],%19[^,],%f\n", 
                  &rooms[roomCount].room_no, 
                  rooms[roomCount].guest_name, 
                  rooms[roomCount].check_in, 
                  rooms[roomCount].check_out, 
                  &rooms[roomCount].price) == 5)
    {
        roomCount++;
        if (roomCount >= MAX_ROOMS) break;
    }

    fclose(fp);
}

int main()
{
    loadFromFile(); // Load previous data when program starts

    if (!login())
    {
        exit(0);
    }

    int choice;

    while (1)
    {
        system("cls");
        printf("\n\tHOTEL RESERVATION MANAGEMENT SYSTEM\n");
        printf("\tADMIN PANEL\n\n");

        printf("1. Add Reservation\n");
        printf("2. Display Reservations\n");
        printf("3. Search Reservation\n");
        printf("4. Update Reservation\n");
        printf("5. Delete Reservation\n");
        printf("6. Save to File\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addReservation();
            break;

        case 2:
            displayReservations();
            break;

        case 3:
            searchReservation();
            break;

        case 4:
            updateReservation();
            break;

        case 5:
            deleteReservation();
            break;

        case 6:
            saveToFile();
            break;

        case 0:
            saveToFile(); // Auto-save on exit
            printf("\nThank you Admin!\n");
            exit(0);

        default:
            printf("Invalid choice!\n");
            pause();
            break;
        }
    }

    return 0;
}