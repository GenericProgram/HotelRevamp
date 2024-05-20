/*
Dean Leon
5/15/24
Hotel assingment for engr 103
(Used AI and Doxyegn for documentation of some functions)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#define HOTEL_SIZE 30

typedef struct { //create room struct
    int occupancy; // number of occupants (should not exceed 4)
    char names[32];
    int nightlyRate;
    int roomNumber;
} Rooms;

Rooms hotel[3][10]; //Create 2d array, 3 rows for 3 floors and 10 columns for 10 rooms
bool running = true; //bool to keep user from escaping
int input; //number that the user inputs
char strInput[32]; //user input for strings

/*
IMPORTANT NOTES TO REMEMBER:
-floor 0 in the array is floor 1, all floors entered by user should be subtracted by 1 when working in the arrays
*/

/**
 * @brief Checks if a string contains any numbers or special characters.
 *
 * @param str The string to be checked.
 * @return Returns true if the string contains a number or a special character, false otherwise.
 *
 * @brief This function iterates over each character in the string. If it encounters a character that is not an alphabetic letter (i.e., a number or a special character), it immediately returns true. If it checks all characters and all of them are alphabetic letters, it returns false.
 */
bool containsNumberOrSpecialCharacter(char *str) {
    while (*str) {
        if (!isalpha((unsigned char)*str)) { //cast unsigned char to ensure isalpha behaves normally, is alpha return non-zero value if the number is numeric
            return true;
        }
        str++; //incrment pointer to point at next char
    }
    return false;
}

/**
 * Function: isValidNumericalInput
 * -------------------------------
 * Checks if a given input is a valid numerical option within a specified range.
 *
 * Parameters:
 * - numberOfOptions: The total number of valid options. This is the upper limit of the range.
 * - input: The input to check.
 *
 * Returns:
 * - true if the input is a valid option (i.e., it is an integer between 1 and numberOfOptions, inclusive).
 * - false otherwise.
 *
 * Example:
 * If numberOfOptions is 5, then the function returns true for inputs 1, 2, 3, 4, and 5, and false for any other input.
 */
bool isValidNumericalInput(int numberOfOptions, int input){
    if(input > numberOfOptions || input < 1){
        return false;
    } else {
        return true;
    }
}

/**
 * Function: getIntegerInput
 * -------------------------
 * Reads a line of input from the user and checks if the entered string can be converted to an integer in the range.
 * If it cannot, it prompts the user to enter an integer again.
 *
 * Parameters:
 * - range: the range in which to allow inputs.
 *
 * Returns:
 * - The entered integer.
 */
int getIntegerInput(int range) {
    char buffer[256];
    int number;
    char *end;

    do {
        fgets(buffer, sizeof(buffer), stdin);
        number = strtol(buffer, &end, 10);
    } while (end == buffer || *end != '\n' || number < 1 || number > range);
            //end == buffer: This means that no digits were found at the beginning of the buffer, so no conversion could be performed
            //*end != '\n': This means that after converting the number, the next character in the buffer is not a newline character ('\n'). This indicates that the user entered additional non-numeric characters after the number.
    return number;
}

/**
 * Function: getStringInput
 * ------------------------
 * Reads a line of input into a buffer and checks if the entered string contains any digits.
 * If it does, it prompts the user to enter a string again.
 * This continues until a valid string with no digits is entered.
 *
 * Parameters:
 * - buffer: A pointer to the buffer to store the input string.
 * - size: The size of the buffer.
 *
 * Returns:
 * - None. The entered string is stored in the buffer passed as a parameter. 
 * */
void getStringInput(char *buffer, int size) {
    do {
        fgets(buffer, size, stdin);

        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = 0;
    } while (containsNumberOrSpecialCharacter(buffer));
    //while(1) acts like while(true)
}

/**
 * Function: printMenu
 * -------------------
 * Prints a menu of options for the hotel management system and prompts the user to select an option.
 *
 * Parameters:
 * - None.
 *
 * Returns:
 * - None.
 *
 * Behavior:
 * - This function first prints a welcome message and a list of options.
 * - It then calls the getIntegerInput function to prompt the user to select an option. In this case 6 options are availible.
 * - The selected option is returned by the function.
 */
void printMenu(){
    printf("\nWelcome to your hotel! (Use numerical inputs when prompted and string inputs for guest names)\n");
    printf("1. Add guest\n2. Remove guest\n3. Quick info\n4. View room\n5. Exit\n6. Save/Load hotel\n");
    input = getIntegerInput(6);
}

/**
 * @brief This function prints the details of a room.
 *
 * The function takes a `Rooms` structure as an argument and prints its details,
 * including the room number, occupancy, nightly rate, and the names of the occupants.
 *
 * @param room A `Rooms` structure containing the details of the room.
 */
void printRoom(Rooms room){
    // Print the room number
    printf("Room number: %d\n", room.roomNumber);
    // Print the room occupancy
    printf("Room occupancy: %d/4\n", room.occupancy);
    // Print the room cost per night
    printf("Room cost/night: $%d/night\n", room.nightlyRate);
    // Print the names of the room occupants
    if(room.occupancy > 0){
        printf("Room booked under: %s\n", room.names);
    } else {
        printf("Room is empty.");
    }
}

/**
 * @brief This function prints the billing details of all rooms.
 *
 * The function takes an array of `Rooms` structures and its size as arguments.
 * It iterates over each room in the array and prints its room number, occupancy,
 * and the total revenue generated from the room (calculated as the nightly rate
 * multiplied by the occupancy).
 *
 * @param room An array of `Rooms` structures containing the details of the rooms.
 * @param size The number of elements in the `room` array.
 */
void printBilling(Rooms room[], int size) {
    for(int i = 0;i<size;i++){
         printf("Room %d:  Occupancy: %d/4  Total revenue from room: %d\n", room[i].roomNumber, room[i].occupancy, room[i].nightlyRate*room[i].occupancy);
    }
}

/**
 * @brief Prints the details of all rooms on a specific floor of the hotel.
 *
 * @param floor The floor number whose rooms' details are to be printed.
 *
 * This function iterates over each room on the specified floor and prints its details. For each room, it prints the room's number (relative to the floor), the room's absolute number, and the room's occupancy out of a maximum of 4.
 */
void printFloor(int floor) {
    for(int i = 0;i<10;i++){
         printf("%d. Room %d:  Occupancy: %d/4\n", i+1,hotel[floor][i].roomNumber, hotel[floor][i].occupancy);
    }
}

/**
 * @brief This function counts the total number of occupants in all rooms.
 *
 * The function takes an array of `Rooms` structures and its size as arguments.
 * It iterates over each room in the array and adds its occupancy to a total count.
 * The function returns the total count of occupants in all rooms.
 *
 * @param room An array of `Rooms` structures containing the details of the rooms.
 * @param size The number of elements in the `room` array.
 * @return The total count of occupants in all rooms.
 */
int countOccupants(Rooms room[], int size) {
    int count = 0;
    for(int i = 0;i<size;i++){
        count += room[i].occupancy;
    }
    return count;
}

/**
 * @brief This function sets up the rooms in the hotel.
 * 
 * The hotel has three floors, each with ten rooms. 
 * The room numbers and nightly rates are set as follows:
 * - First floor rooms have numbers from 101 to 110 and a nightly rate of 80.
 * - Second floor rooms have numbers from 201 to 210 and a nightly rate of 90.
 * - Third floor rooms have numbers from 301 to 310 and a nightly rate of 100.
 */
void setUpRooms(){
    for(int i = 0; i < 3; i++){
        for(int j=0;j<10;j++){
            if(i==0){
                hotel[i][j].roomNumber = 101 + j;
                hotel[i][j].nightlyRate = 80;
                hotel[i][j].occupancy = 0;
            } else if(i==1){
                hotel[i][j].roomNumber = 201 + j;
                hotel[i][j].nightlyRate = 90;
                hotel[i][j].occupancy = 0;
            } else {
                hotel[i][j].roomNumber = 301 + j;
                hotel[i][j].nightlyRate = 100;
                hotel[i][j].occupancy = 0;
            }
        }
    }
}

//functionally does same as last function but does not touch occuoancy, should only be used when loading and saving
void setUpRoomsWithoutOccupancy(){
    for(int i = 0; i < 3; i++){
        for(int j=0;j<10;j++){
            if(i==0){
                hotel[i][j].roomNumber = 101 + j;
                hotel[i][j].nightlyRate = 80;
            } else if(i==1){
                hotel[i][j].roomNumber = 201 + j;
                hotel[i][j].nightlyRate = 90;
            } else {
                hotel[i][j].roomNumber = 301 + j;
                hotel[i][j].nightlyRate = 100;
            }
        }
    }
}

/*
void loadHotel(Room rooms[], int size)
rooms[]: An array of Room structures to be filled by data loaded from hotel.tsv
size: The number of items to be loaded from hotel.tsv. Do not exceed the size of rooms[] array
returns nothing
*/
void loadHotel(Rooms rooms[], int size){
    FILE* fp = fopen("hotel.tsv","r");
    char buf[80], c;
    int line = 0;
    char* token;
    while (fgets (buf, sizeof buf, fp) && line < HOTEL_SIZE) { //Read in line by line to be processed
        token = strtok(buf, "\t");
        rooms[line].roomNumber = atoi(token);
        
        token = strtok(NULL, "\t");
        rooms[line].occupancy = atoi(token);
        
        token = strtok(NULL, "\t");
        strcpy(rooms[line].names, token);
        
        token = strtok(NULL, "\t");
        rooms[line].nightlyRate = atof(token);
        line++;
    }
    fclose(fp);
}

/**
 * @brief This function saves the details of hotel rooms into a file.
 *
 * @param room[] An array of Rooms structures that hold the details of each room.
 * @param size The number of rooms in the array.
 *
 * @brief The function opens the file "hoteledit.tsv" in write mode and writes the details of each room into the file.
 * Each line in the file corresponds to a room and contains the room number, occupancy status, names of occupants, and the nightly rate, separated by tabs.
 * If the file cannot be opened, an error message is printed to the standard output.
 */
void saveHotel(Rooms room[], int size) {
    FILE* fp = fopen("hoteledit.tsv", "w");
    if(fp == NULL) {
        printf("Error, cannot find file.\n");
    } 
    for(int i=0;i<size;i++) {
        fprintf(fp, "%d\t%d\t%s\t%d\n", room[i].roomNumber, room[i].occupancy, room[i].names, room[i].nightlyRate);
    }
    fclose(fp);
}

/**
 * @brief This function adds a guest to a specific room in the hotel.
 *
 * @param name[] A character array representing the name of the guest.
 * @param floor The floor number where the room is located.
 * @param occupants The number of occupants in the room.
 * @param roomNumber The room number on the specified floor.
 *
 * The function adds a guest to a specific room in the hotel by copying the guest's name to the `names` field of the `Room` structure corresponding to the specified floor and room number. It also sets the `occupancy` field of the `Room` structure to the specified number of occupants.
 */
void addGuest(char name[32], int floor, int occupants, int roomNumber) {
    strcpy(hotel[floor][roomNumber].names, name);
    hotel[floor][roomNumber].occupancy = occupants;
}

/**
 * @brief This function resets the hotel to its initial state.
 *
 * The function first calls the `setUpRooms` function to initialize the rooms in the hotel. 
 * Then it iterates over each room in the hotel and clears the `names` field of the `Room` structure corresponding to each room, effectively removing all guests from the hotel.
 */
void wipeHotel() {
    setUpRooms();
    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            memset(hotel[i][j].names, '\0', sizeof(hotel[i][j].names));
        }
    }
}

/**
 * @brief This function checks if a specific floor in the hotel is fully occupied.
 *
 * @param floor The floor number to be checked.
 * @return Returns true if all rooms on the specified floor are occupied, false otherwise.
 *
 * The function iterates over each room on the specified floor and counts the number of rooms that are occupied (i.e., the `occupancy` field of the `Room` structure is greater than or equal to 1). If all rooms on the floor are occupied (i.e., the count is 10), the function returns true. Otherwise, it returns false.
 */
bool isFloorFull(int floor){
    int counter = 0;
    for(int i=0;i<10;i++){
        if(hotel[floor][i].occupancy >= 1) {
            counter++;
        }
    }
    if(counter == 10) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief This function checks if the entire hotel is fully occupied.
 *
 * @return Returns true if all floors in the hotel are fully occupied, false otherwise.
 *
 * The function calls the `isFloorFull` function for each floor in the hotel. If all floors are fully occupied (i.e., `isFloorFull` returns true for all floors), the function returns true. Otherwise, it returns false.
 */
bool isHotelFull() {
    if(isFloorFull(0) == true && isFloorFull(1) == true && isFloorFull(2) == true) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief This function removes a guest from a specific room in the hotel.
 *
 * @param floor The floor number where the room is located.
 * @param roomNumber The room number on the specified floor.
 *
 * The function removes a guest from a specific room in the hotel by setting the `occupancy` field of the `Room` structure corresponding to the specified floor and room number to 0 and clearing the `names` field.
 */
void removeGuest(int floor, int roomNumber){
    hotel[floor][roomNumber].occupancy = 0;
    memset(hotel[floor][roomNumber].names, '\0', sizeof(hotel[floor][roomNumber].names));
}

/**
 * @brief Calculates the total income from all occupied rooms in the hotel.
 *
 * @return Returns the total income.
 *
 * This function iterates over each room in the hotel and adds the product of the room's nightly rate and its occupancy to a total income counter. The function then returns this total income.
 */
int findIncome(){
    int money=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            money += (hotel[i][j].nightlyRate * hotel[i][j].occupancy);
        }
    }
    return money;
}

/**
 * @brief Calculates the total number of occupied rooms in the hotel.
 *
 * @return Returns the total number of occupied rooms.
 *
 * This function iterates over each room in the hotel and increments a counter if the room's occupancy is greater than zero (indicating the room is occupied). The function then returns this count.
 */
int findOccupiedRooms(){
    int count = 0;
    for(int i=0;i<3;i++){
        for(int j=0;j<10;j++){
            if(hotel[i][j].occupancy > 0){
                count++;
            }
        }
    }
    return count;
}


int main() {
    setUpRooms(); //setup initial rooms
    printf("\e[1;1H\e[2J"); //clear terminal using regex
    srand(time(NULL)); //seed random numeber to current time

    while(running) {
        printMenu(); //print initial options
        switch(input) {
            case 1: //Add guest
                if(isHotelFull() == true) { //prevent overbooking of a full hotel
                    printf("Hotel is full!");
                } else {
                    printf("Choose floor for guest accomodation:\n1. Economy ($80/night)\n2. Business ($90/night)\n3. Executive ($100/night)\n"); //prompt user with floors
                    int floor = getIntegerInput(3); //limit input to 1,2,3 and save floors
                    printf("Choose how many occupants there are: 1-4: \n"); //get occupancy from user
                    int occupants = getIntegerInput(4); //save occupancy
                    printf("Enter guest name: (No numbers or special characters)\n"); //get name
                    getStringInput(strInput, sizeof(strInput)); //save name to strInput
                    if(isFloorFull(floor-1)==true){ //check to see if desired floor is full, floor-1 because arrays count from 0
                        printf("Desired floor is full!\n"); //if floor is full go onto other floors
                        for(int i=0;i<3;i++){
                            for(int j=0;j<10;j++){
                                if(hotel[i][j].occupancy == 0){
                                    addGuest(strInput, i, occupants, j);
                                    printf("%s added to room %d on floor %d\n", strInput, hotel[i][j].roomNumber, i+1); //notify user of new guest location
                                    i = j = 11; //break the nested loop, clunky but better than using goto
                                } 
                            }
                        }
                    } else {
                        while(true) {
                            int roomNumber = rand() % 10; //if everything is ok then just add guest normal to random empty room
                            if(hotel[floor-1][roomNumber].occupancy == 0) {
                                addGuest(strInput, floor-1, occupants, roomNumber);
                                printf("%s added to room %d on floor %d\n", strInput, hotel[floor-1][roomNumber].roomNumber, floor); //notify user of guest location
                                break;
                            }
                        }
                    }
                }
                break;
            case 2: //remove guest
                printf("Choose floor:\n1. Economy\n2. Business\n3. Executive\n"); //prompt user
                int floor = getIntegerInput(3);  //save floor
                printFloor(floor-1); //floor-1 because arrays count from 0
                printf("Choose room 1-10: \n"); //get room
                input = getIntegerInput(10); //save room
                if(hotel[floor-1][input-1].occupancy==0) { //-1 from both inputs because arrays start from 0
                    printf("Room is already empty"); //if room is already empty notify user
                } else {
                    removeGuest(floor-1, input-1); //remove guest
                }
                break;
            case 3: //quick info
                printf("Quick info menu:\n1. Guest lookup\n2. Count number of guests\n3. Find total income\n4. Find ratio of full rooms to empty rooms\n"); //prompt info
                input = getIntegerInput(4); //save info
                if(input == 1){ //guest lookup
                    bool guestFound = false; //create guestfound boolean
                    fflush(stdin); //clear trailing newline character
                    printf("Enter guest name (case and space sensitive): ");
                    getStringInput(strInput, sizeof(strInput)); //get name from user
                    for(int i=0;i<3;i++){ //iterate through hotel until we find a match
                        for(int j=0;j<10;j++){
                            if(strcmp(hotel[i][j].names, strInput) == 0) { //strcmp will return 0 if it is an exact match
                                guestFound = true; //set to true
                                printf("%s found in room %d on floor %d.\n", strInput, hotel[i][j].roomNumber, i+1); //notify user of location
                                printRoom(hotel[i][j]); //print the room where the guest is per assingment instructions
                            }
                        }
                    }
                    if(guestFound == false){
                        printf("Guest by name: %s not found in hotel.", strInput); //if guest is not found, print to screen results
                    }
                } else if(input == 2){//number of guests
                    printf("Total number of guests: %d", countOccupants(hotel, HOTEL_SIZE)); //count the total number of guests (see countOccupants documentation)
                } else if(input == 3) { //find income
                    printBilling(hotel, HOTEL_SIZE); //find the income of guests (see findIncome and printBilling documentation)
                    printf("Total income added is $%d/night\n", findIncome());
                } else if(input == 4) { //ratio of full to empty rooms
                    for(int i=0;i<3;i++){ //iterate theought the hotel and print each room
                        for(int j=0;j<10;j++){
                            printf("Room %d: Occupancy: %d/4\n", hotel[i][j].roomNumber, hotel[i][j].occupancy);
                        }
                    }
                    printf("Full/empty room ratio: %d/%d", findOccupiedRooms(),HOTEL_SIZE-findOccupiedRooms());//print number of filled rooms, then subtract that number from total rooms to find the empty rooms
                }
                break;
            case 4: //view room
                printf("Choose floor:\n1. Economy\n2. Business\n3. Executive\n");
                floor = getIntegerInput(3); //get and save floor and room numbers
                printFloor(floor-1); //floor-1 because arrays count from 0
                printf("Choose room 1-10: \n");
                input = getIntegerInput(10);
                printRoom(hotel[floor-1][input-1]); //seee printroom function above, subtract becuase the inputs from the user are 1 ahead of the array indecies
                break;
            case 5: //exit
                running = false; //simply terminate program
                return 0;
            case 6: //save/load
                printf("1. Save\n2. Load\n"); //get user choice
                input = getIntegerInput(2);
                if(input == 1) {
                    setUpRoomsWithoutOccupancy(); //see documentation above for these functions
                    saveHotel(hotel, HOTEL_SIZE); //save the hotel
                    printf("Hotel saved to 'hoteledit.tsv'\n");// notify hotel save location and name
                } else {
                    printf("Are you sure? Loading will wipe all non-saved data that you currently have.\n1. Yes\n2. No\n"); //confirmation
                    input = getIntegerInput(2);
                    if(input == 1){
                        wipeHotel(); //obliterate current hotel state
                        loadHotel(hotel, HOTEL_SIZE); //load new state
                        setUpRoomsWithoutOccupancy(); //"fix" rooms and nightlyIncome
                    } 
                }
                break; 
        }
    }
}