#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// var declarations

// because by default c only support ASCII targeting enum dont get ⌖
// and im not going to redo half my code just so i can fit ⌖ into my fking strings
enum Space { Hit = 'O', Miss = 'X', Forfeit = 'i', Unknown = ' ', Targeting = '+' };

enum Space grid[10][10] = {
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
    {Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown, Unknown},
};
int lengths[5] = {2, 3, 3, 4, 5};

int targets_counter = 0;
int shotsFired = 0;
int hits = 0;

//flags
int doneShooting = 0;
int doneSelecting = 0;
int doneConfirm = 1;
int choosingTarget = 0;
int choosingColumn = 0;
int secondThreeLong = 0;

int main(void) {
    printf("loading...\n");

    //initialize the targets array size to total ship lengths
    int sumOfLengths = 0;
    int i = 0;
lengthSumLoop:
    if (i >= sizeof(lengths) / sizeof(lengths[0])) {
        goto lengthSumLoopEnd;
    }

    sumOfLengths += lengths[i];

    i++;
    goto lengthSumLoop;

lengthSumLoopEnd:

    int targets[sumOfLengths][2];

    // previously rngships()
    // used for ship generation
    i = 0;
rngShips:
    if (i >= sizeof(lengths) / sizeof(lengths[0])) {
        goto rngShipsEnd;
    }
    int done = 0;
rngDir:
    if (done) {
        goto rngDirDone;
    }
    // get current time in nanoseconds for rng seeding
    struct timespec tempTime;
    clock_gettime(CLOCK_REALTIME, &tempTime);
    srand(tempTime.tv_nsec);
    int rng[] = {rand() % 10, rand() % 10};
    clock_gettime(CLOCK_REALTIME, &tempTime);
    srand(tempTime.tv_nsec);

    // rng the direction of the ship
    switch (rand() % 4) {
        //if 0 go right
        //1 go down
        //2 go left
        //3 go up
        case 0:
            goto case0;
        case 1:
            goto case1;
        case 2:
            goto case2;
        case 3:
            goto case3;
        default:
            // should never happen bc this will only happen if the rng result is 4 which is almost impossible unless the rng gave almost the maximum value possible
            goto case0;
    }

    // right facing ship
case0:
    if ((rng[1] + lengths[i] - 1) >= 9) {
        goto case0OutOfBounds;
    }
    int nope = 0;
    int temp = rng[1];
    int j = 0;
case0OccupiedSpaceLoop:
    if (!(j <= targets_counter && !nope)) {
        goto case0OccupiedSpaceLoopEnd;
    }
    //loop thru each occupied square
    temp = rng[1];
    int k = 0;
case0CheckEmptySpaceLoop:
    if (k >= lengths[i]) {
        goto case0CheckEmptySpaceLoopEnd;
    }
    //loop thru each square the new ship would take up
    if (rng[0] == targets[j][0] && temp == targets[j][1]) {
        nope = 1;
    }
    temp++;
    k++;
    goto case0CheckEmptySpaceLoop;

case0CheckEmptySpaceLoopEnd:
    j++;
    goto case0OccupiedSpaceLoop;

case0OccupiedSpaceLoopEnd:
    if (nope) {
        goto dirEnd;
    }
    j = 0;
case0ApplyShipLoop:
    if (j >= lengths[i]) {
        goto case0ApplyShipLoopEnd;
    }
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[1]++;
    j++;
    goto case0ApplyShipLoop;

case0ApplyShipLoopEnd:
    done = !done;


case0OutOfBounds:

    goto dirEnd;

    // down facing ship
case1:
    if ((rng[0] + lengths[i] - 1) >= 9) {
        goto case1OutOfBounds;
    }
    nope = 0;
    temp = rng[0];
    j = 0;
case1OccupiedSpaceLoop:
    if (!(j <= targets_counter && !nope)) {
        goto case1OccupiedSpaceLoopEnd;
    }
    temp = rng[0];
    k = 0;
case1CheckEmptySpaceLoop:
    if (k >= lengths[i]) {
        goto case1CheckEmptySpaceLoopEnd;
    }
    if (temp == targets[j][0] && rng[1] == targets[j][1]) {
        nope = 1;
    }
    temp++;
    k++;
    goto case1CheckEmptySpaceLoop;

case1CheckEmptySpaceLoopEnd:
    j++;
    goto case1OccupiedSpaceLoop;

case1OccupiedSpaceLoopEnd:
    if (nope) {
        goto dirEnd;
    }

    j = 0;
case1ApplyShipLoop:
    if (j >= lengths[i]) {
        goto case1ApplyShipLoopEnd;
    }
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[0]++;

    j++;
    goto case1ApplyShipLoop;

case1ApplyShipLoopEnd:
    done = !done;

case1OutOfBounds:

    goto dirEnd;

    // left facing ship
case2:
    if ((rng[1] - lengths[i] + 1) <= 0) {
        goto case2OutOfBounds;
    }
    nope = 0;
    temp = rng[1];
    j = 0;
case2OccupiedSpaceLoop:
    if (!(j <= targets_counter && !nope)) {
        goto case2OccupiedSpaceLoopEnd;
    }
    temp = rng[1];
    k = 0;
case2CheckEmptySpaceLoop:
    if (k >= lengths[i]) {
        goto case2CheckEmptySpaceLoopEnd;
    }
    if (rng[0] == targets[j][0] && temp == targets[j][1]) {
        nope = 1;
    }
    temp--;
    k++;
    goto case2CheckEmptySpaceLoop;

case2CheckEmptySpaceLoopEnd:
    j++;
    goto case2OccupiedSpaceLoop;

case2OccupiedSpaceLoopEnd:
    if (nope) {
        goto dirEnd;
    }
    j = 0;
case2ApplyShipLoop:
    if (j >= lengths[i]) {
        goto case2ApplyShipLoopEnd;
    }
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[1]--;

    j++;
    goto case2ApplyShipLoop;

case2ApplyShipLoopEnd:
    done = !done;

case2OutOfBounds:

    goto dirEnd;

    // up facing ship
case3:
    if ((rng[0] - lengths[i] + 1) <= 0) {
        goto case3OutOfBounds;
    }
    nope = 0;
    temp = rng[0];
    j = 0;
case3OccupiedSpaceLoop:
    if (!(j <= targets_counter && !nope)) {
        goto case3OccupiedSpaceLoopEnd;
    }
    temp = rng[0];
    k = 0;
case3CheckEmptySpaceLoop:
    if (k >= lengths[i]) {
        goto case3CheckEmptySpaceLoopEnd;
    }
    if (temp == targets[j][0] && rng[1] == targets[j][1]) {
        nope = 1;
    }
    temp--;
    k++;
    goto case3CheckEmptySpaceLoop;

case3CheckEmptySpaceLoopEnd:
    j++;
    goto case3OccupiedSpaceLoop;

case3OccupiedSpaceLoopEnd:
    if (nope) {
        goto dirEnd;
    }
    j = 0;
case3ApplyShipLoop:
    if (j >= lengths[i]) {
        goto case3ApplyShipLoopEnd;
    }
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[0]--;

    j++;
    goto case3ApplyShipLoop;

case3ApplyShipLoopEnd:
    done = !done;

case3OutOfBounds:

dirEnd:
    goto rngDir;

rngDirDone:

    i++;
    goto rngShips;

rngShipsEnd:

    // at this point the game initializing is done and display the game start msg
    printf(
        "Welcome to battleships!\nIn this game you select a square to shoot\nto see if there is a ship hiding there.\nTry and sink all 5 ships with the lowest shots possible!\n");

    int gameOver = 0;
mainGameLoop:
    if (gameOver) {
        goto gameEnd;
    }

    // formerly printBoard()
    // code handling printing the board onto console
printBoard:
    printf("         1   2   3   4   5   6   7   8   9   10\n");

    i = 0;
horizontalArrowLoop:
    if (i >= 10) {
        goto horizontalArrowLoopEnd;
    }
    char output[50];
    snprintf(output, sizeof(output), "     %i | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", (i + 1),
             grid[i][0], grid[i][1], grid[i][2], grid[i][3], grid[i][4], grid[i][5], grid[i][6], grid[i][7],
             grid[i][8], grid[i][9]);

    if (i != 9) {
        goto horizontalArrowNotOn10;
    }
    j = 3;
horizontalArrowOffsetFor10Loop:
    if (j >= sizeof(output)) {
        goto horizontalArrowOffsetFor10LoopEnd;
    }
    output[j] = output[j + 1];
    j++;
    goto horizontalArrowOffsetFor10Loop;

horizontalArrowOffsetFor10LoopEnd:

horizontalArrowNotOn10:

    printf("       -----------------------------------------\n");
    printf("%s\n", output);

    i++;
    goto horizontalArrowLoop;

horizontalArrowLoopEnd:
    printf("       -----------------------------------------\n");
    // end of printBoard
    // personally the worst part of the program here
    // because C doesnt save the return line when you goto you have
    // to return to the correct line by crafting custom logic to make it return correctly
    // if you want examples of monke code theres no better example than this tbh
    // because I have absolutely 0 idea how does all of this somehow work
    if (hits == sizeof(lengths) / sizeof(lengths[0])) {
        goto printBoardReturnWin;
    }
    if (gameOver) {
        goto printBoardReturnForfeit;
    }
    if (!doneConfirm) {
        goto printBoardReturnConfirming;
    }
    if (choosingTarget) {
        goto printBoardReturnTarget;
    }

    // array for saving user input in menu
    // size is 6 becasue thats the length the game ever has to read (10,10\0)
    // effectively 5 size because the last slot lives the null terminator
    char input[6] = "-1";
    printf("Misses: %c\tHits: %c\nShots fired: %i\nPlease select from the following:\n1. shoot\n2. forfeit\n",
           Miss, Hit, shotsFired);
    fflush(stdin); // empty stdin before using it or it may contain junk
    fgets(input, sizeof(input), stdin);
    if (strcmp(input, "1\n") == 0) {
        // yes the enter key is also read, i loooooooovvvvvveeeeee C
        goto menuInput1;
    }
    if (strcmp(input, "2\n") == 0) {
        goto menuInput2;
    }
    goto invalidMenuInput;


menuInput1:
    doneShooting = 0;
shooting:
    if (doneShooting) {
        goto shootingEnd;
    }
    doneConfirm = 1;
selectingTarget:
    if (doneSelecting) {
        goto selectingTargetEnd;
    }
    choosingTarget = 1;
    goto printBoard;
printBoardReturnTarget:

    printf("Please enter the row and column in the format of : ROW,COLUMN\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);
    // count commas
    int count = 0;
    i = 0;
commaCheckLoop:
    if (!(i <= sizeof(input) / sizeof(input[0]) && input[i] != '\n' && input[i] != '\0')) {
        goto commaCheckLoopEnd;
    }
    if (input[i] != ',') {
        goto skipCommaCount;
    }
    count++;

    skipCommaCount:
    i++;
    goto commaCheckLoop;

commaCheckLoopEnd:

    if (count == 1) {
        goto foundOnlyOneComma;
    }

    // runs if cannot split input into 2 chunks with comma
    printf("Please enter in the format of : ROW,COLUMN\n");
    goto checkTargetInputEnd;

foundOnlyOneComma:
    char inputs[2][3];
    char *tempp = &input[0];
    char *temppp = &inputs[0][0];
stringCommaSplitLoop:
    if (!(*tempp != '\n' && *tempp != '\0')) {
        goto stringCommaSplitLoopEnd;
    }
    if (*tempp != ',') {
        goto ifNotComma;
    }
    *temppp = '\0';
    temppp = &inputs[1][0];
    goto ifComma;

ifNotComma:
    *temppp = *tempp;
    temppp++;

ifComma:

    tempp++;
    goto stringCommaSplitLoop;

    stringCommaSplitLoopEnd:
    *temppp++ = '\0';
    //split the 2 strings into 2 vars
    int row = strtol(inputs[0], &temppp, 10) - 1;
    if (!(temppp == inputs[0] || *temppp != '\0')) {
        goto rowValid;
    }

    printf("Please enter a valid row and/or column number\n");
    goto checkTargetInputEnd;

rowValid:
    int col = strtol(inputs[1], &temppp, 10) - 1;
    if (!(temppp == inputs[1] || *temppp != '\0')) {
        goto columnValid;
    }
    printf("Please enter a valid row and/or column number\n");
    goto checkTargetInputEnd;

columnValid:
    if (!(row > 9 || col > 9 || row < 0 || col < 0)) {
        goto numbersInRange;
    }
    printf("Please enter a valid row and/or column number\n");
    goto checkTargetInputEnd;

numbersInRange:
    enum Space original = grid[row][col];
    grid[row][col] = Targeting;
    doneSelecting = 1;

    doneSelecting = 1;
    choosingTarget = -1;

checkTargetInputEnd:
    goto selectingTarget;

selectingTargetEnd:

    doneSelecting = 0;

    doneConfirm = 0;

confirming:
    if (doneConfirm) {
        goto confirmingEnd;
    }
    goto printBoard;
printBoardReturnConfirming:

    printf("You sure you want to shoot there?(Y/N)\n");
    fflush(stdin);
    input[0] = tolower(fgetc(stdin));
    switch (input[0]) {
        case 'y':
            goto confirmYes;
        case 'n':
            goto confirmNo;
        default:
            goto invalidConfirm;
    }

confirmYes:
    i = 0;
checkIfHitLoop:
    if (i >= sizeof(lengths) / sizeof(lengths[0])) {
        goto checkIfHitLoopEnd;
    }
    if (!(targets[i][0] == row && targets[i][1] == col)) {
        goto miss;
    }
    grid[row][col] = Hit;
    hits++;
    shotsFired++;
    goto confirmSwitchEnd;

miss:
    grid[row][col] = Miss;

    i++;
    goto checkIfHitLoop;

checkIfHitLoopEnd:
    doneConfirm = 1;
    doneShooting = 1;
    row = -1;
    col = -1;
    shotsFired++;
    goto confirmSwitchEnd;

confirmNo:
    grid[row][col] = original;
    goto confirmSwitchEnd;

invalidConfirm:
    printf("invalid input!\n");

confirmSwitchEnd:
    doneConfirm = 1;
    doneShooting = 0;
    doneSelecting = 0;
    choosingTarget = 0;
    row = 0;
    choosingColumn = 0;
    col = 0;
    goto confirming;

confirmingEnd:
    printf("\n");

    goto mainGameLoop;

shootingEnd:

    doneShooting = 0;
    doneSelecting = 0;
    doneConfirm = 1;
    choosingTarget = 0;
    row = -1;
    choosingColumn = 0;
    col = -1;
    if (hits == sizeof(lengths) / sizeof(lengths[0])) {
        goto notWin;
    }
    goto printBoard;
printBoardReturnWin:
    printf("You win!\n");
    gameOver = 1;

notWin:
    goto mainMenuInputEnd;

    // the forfeit option
menuInput2:
    gameOver = 1;
    i = 0;
markingShipLocationsLoop:
    if (i >= targets_counter) {
        goto markingShipLocationsLoopEnd;
    }
    if (grid[targets[i][0]][targets[i][1]] != Hit) {
        grid[targets[i][0]][targets[i][1]] = Forfeit;
    }

    i++;
    goto markingShipLocationsLoop;;

markingShipLocationsLoopEnd:
    goto printBoard;
printBoardReturnForfeit:
    printf("you lost!");
    goto mainMenuInputEnd;

invalidMenuInput:
    printf("invalid input!\n");
mainMenuInputEnd:
    goto mainGameLoop;

gameEnd:

    return 0;
}
