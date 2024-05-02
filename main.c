#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Passenger
{
    char name[50];          // name of passenger
    char surname[50];       // surname of passenger
    char citizenship[50];   // name of passenger's country
    int age;                // passenger's age
    double weight_baggage;  // passenger's baggage weight
};

void createPassenger(struct Passenger *passenger)
{
    printf("Enter passenger name: ");
    scanf(" %49[^\n]", passenger->name);

    printf("Enter passenger surname: ");
    scanf(" %49[^\n]", passenger->surname);

    printf("Enter passenger citizenship: ");
    scanf(" %49[^\n]", passenger->citizenship);

    printf("Enter passenger age: ");
    scanf("%d", &(passenger->age));

    printf("Enter passenger baggage weight: ");
    scanf("%lf", &(passenger->weight_baggage));
}

void displayPassenger(const struct Passenger *passenger)
{
    printf("Passenger Name: %s %s\n", passenger->name, passenger->surname);
    printf("Citizenship: %s\n", passenger->citizenship);
    printf("Age: %d\n", passenger->age);
    printf("Baggage Weight: %.2lf\n", passenger->weight_baggage);
    printf("---------------------------------\n");
}

void displayAllPassengers(const struct Passenger *passengers, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("Passenger %d:\n", i + 1);
        displayPassenger(&passengers[i]);
    }
}

double computeAverageAge(const struct Passenger *passengers, int count, int threshold)
{
    int sum = 0;
    int validPassengerCount = 0;

    for (int i = 0; i < count; i++)
    {
        if (passengers[i].age < threshold)
        {
            sum += passengers[i].age;
            validPassengerCount++;
        }
    }

    if (validPassengerCount > 0)
    {
        return (double)sum / validPassengerCount;
    }
    else
    {
        return 0.0;
    }
}

struct Passenger findPassengerWithLowestBaggage(const struct Passenger *passengers, int count)
{
    struct Passenger lowestBaggagePassenger = passengers[0];

    for (int i = 1; i < count; i++)
    {
        if (passengers[i].weight_baggage < lowestBaggagePassenger.weight_baggage)
        {
            lowestBaggagePassenger = passengers[i];
        }
    }

    return lowestBaggagePassenger;
}

int main()
{
    int option;
    printf("Choose an option:\n");
    printf("1. Enter passenger data interactively\n");
    printf("2. Read passenger data from a text file\n");
    printf("Option: ");
    scanf("%d", &option);

    int n;
    struct Passenger *passengers;

    if (option == 1)
    {
        printf("Enter the number of passengers: ");
        scanf("%d", &n);
        if(n<=0){
            printf("invalid value!");
            return 0;
        }
        passengers = (struct Passenger *)malloc(n * sizeof(struct Passenger));

        // Get passenger data from the user
        for (int i = 0; i < n; i++)
        {
            printf("\nPassenger %d:\n", i + 1);
            createPassenger(&passengers[i]);
        }
    }
    else if (option == 2)
    {
        char filename[50];
        printf("Enter the name of the text file (e.g. passenger_data.txt): ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Error opening the file.\n");
            return 1;
        }

        fscanf(file, "%d", &n);
        passengers = (struct Passenger *)malloc(n * sizeof(struct Passenger));

        char line[100];
        fgets(line, sizeof(line), file); // Discard the newline character

        for (int i = 0; i < n; i++)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, "%s %s %s %d %lf", passengers[i].name, passengers[i].surname, passengers[i].citizenship, &(passengers[i].age), &(passengers[i].weight_baggage));
        }

        fclose(file);
    }
    else
    {
        printf("Invalid option.\n");
        return 1;
    }

    printf("\nAll Passengers:\n");
    displayAllPassengers(passengers, n);

    int threshold;
    printf("\nEnter an age threshold: ");
    scanf("%d", &threshold);

    double averageAge = computeAverageAge(passengers, n, threshold);
    printf("Average age of passengers with age less than %d: %.2lf\n", threshold, averageAge);

    struct Passenger lowestBaggagePassenger = findPassengerWithLowestBaggage(passengers, n);
    printf("\nPassenger with the lowest baggage weight:\n");
    displayPassenger(&lowestBaggagePassenger);

    free(passengers);
    return 0;
}
