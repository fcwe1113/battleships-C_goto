#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char grid[10][10] = {
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};
int targets[17][2] = {
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1},
    {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}
};
int targets_counter = 0;
int seed = 0;
int shotsFired = 0;
int hits = 0;

//flags
int doneShooting = 0;
int doneSelecting = 0;
int doneConfirm = 1;
int choosingRow = 0;
int chosenRow = -1;
int choosingColumn = 0;
int chosenColumn = -1;
int secondThreeLong = 0;

int main(void) {
    printf("loading...\n");

    //previously rngships()
    int size = 2;
rngShips:
    if (!(size <= 5)) {
        goto rngShipsEnd;
    }
    //for (int size = 2; size <= 5; size++) {
    int done = 0;
rngDir:
    if (done) {
        goto rngDirDone;
    }
    srand(time(NULL) + (seed * 2));
    //printf("%i %i\n", rand() % 10, rand() % 10);
    int rng[] = {rand() % 10, rand() % 10};
    //printf("%i\n", rand() % 4);
    srand(time(NULL) + seed);
    int dir = rand() % 4;
    //printf("%i %i %i %i\n", rng[0], rng[1], dir, size);

    //2 long ship
    switch (dir) {
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
    }

case0:
    if (!((rng[1] + size - 1) < 9)) {
        goto case0OutOfBounds;
    }
    int nope = 0;
    int temp = rng[1];
    int i = 0;
case0OccupiedSpaceLoop:
    if (!(i <= targets_counter && !nope)) {
        goto case0OccupiedSpaceLoopEnd;
    }
    //loop thru each occupied square
    //printf("%i %i %i %i %i %i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
    temp = rng[1];
    int j = 0;
case0CheckEmptySpaceLoop:
    if (!(j < size)) {
        goto case0CheckEmptySpaceLoopEnd;
    }
    //loop thru each square the new ship would take up
    if (rng[0] == targets[i][0] && temp == targets[i][1]) {
        nope = 1;
    }
    // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
    temp++;
    j++;
    goto case0CheckEmptySpaceLoop;

case0CheckEmptySpaceLoopEnd:
    i++;
    goto case0OccupiedSpaceLoop;

case0OccupiedSpaceLoopEnd:
    if (nope) {
        //printf("hi");
        seed++;
        goto dirEnd; //CHECK IF THIS REBOOTS THE WHILE LOOP
    }
    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
    i = 0;
case0ApplyShipLoop:
    if (!(i < size)) {
        goto case0ApplyShipLoopEnd;
    }
    //grid[rng[0]][rng[1]] = 'O';
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[1]++;
    i++;
    goto case0ApplyShipLoop;

case0ApplyShipLoopEnd:
    done = !done;
    seed++;

case0OutOfBounds:
    seed++;

    goto dirEnd;
case1:
    if (!((rng[0] + size - 1) < 9)) {
        goto case1OutOfBounds;
    }
    nope = 0;
    temp = rng[0];
    i = 0;
case1OccupiedSpaceLoop:
    if (!(i <= targets_counter && !nope)) {
        goto case1OccupiedSpaceLoopEnd;
    }
    temp = rng[0];
    j = 0;
case1CheckEmptySpaceLoop:
    if (!(j < size)) {
        goto case1CheckEmptySpaceLoopEnd;
    }
    if (temp == targets[i][0] && rng[1] == targets[i][1]) {
        nope = 1;
    }
    //temp++;
    // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", temp, targets[i][0], rng[1], targets[i][1], nope, i);
    temp++;
    j++;
    goto case1CheckEmptySpaceLoop;

case1CheckEmptySpaceLoopEnd:
    i++;
    goto case1OccupiedSpaceLoop;

case1OccupiedSpaceLoopEnd:
    if (nope) {
        //printf("hi");
        seed++;
        goto dirEnd; //CHECK IF THIS REBOOTS THE WHILE LOOP
    }
    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);

    i = 0;
case1ApplyShipLoop:
    if (!(i < size)) {
        goto case1ApplyShipLoopEnd;
    }
    //grid[rng[0]][rng[1]] = 'O';
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[0]++;

    i++;
    goto case1ApplyShipLoop;

case1ApplyShipLoopEnd:
    done = !done;
    seed++;

case1OutOfBounds:
    seed++;
    goto dirEnd;
case2:
    if (!((rng[1] - size + 1) > 0)) {
        goto case2OutOfBounds;
    }
    nope = 0;
    temp = rng[1];
    i = 0;
case2OccupiedSpaceLoop:
    if (!(i <= targets_counter && !nope)) {
        goto case2OccupiedSpaceLoopEnd;
    }
    //printf("hi\n");
    temp = rng[1];
    j = 0;
case2CheckEmptySpaceLoop:
    if (!(j < size)) {
        goto case2CheckEmptySpaceLoopEnd;
    }
    if (rng[0] == targets[i][0] && temp == targets[i][1]) {
        nope = 1;
    }
    //temp--;
    // printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", rng[0], targets[i][0], temp, targets[i][1], nope, i);
    temp--;
    j++;
    goto case2CheckEmptySpaceLoop;

case2CheckEmptySpaceLoopEnd:
    i++;
    goto case2OccupiedSpaceLoop;

case2OccupiedSpaceLoopEnd:
    if (nope) {
        //printf("hi");
        seed++;
        goto dirEnd; //CHECK IF THIS REBOOTS THE WHILE LOOP
    }
    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
    i = 0;
case2ApplyShipLoop:
    if (!(i < size)) {
        goto case2ApplyShipLoopEnd;
    }
    //grid[rng[0]][rng[1]] = 'O';
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[1]--;

    i++;
    goto case2ApplyShipLoop;

case2ApplyShipLoopEnd:
    done = !done;
    seed++;

case2OutOfBounds:
    seed++;
    goto dirEnd;
case3:
    if (!((rng[0] - size + 1) > 0)) {
        goto case3OutOfBounds;
    }
    nope = 0;
    temp = rng[0];
    i = 0;
case3OccupiedSpaceLoop:
    if (!(i <= targets_counter && !nope)) {
        goto case3OccupiedSpaceLoopEnd;
    }
    temp = rng[0];
    j = 0;
case3CheckEmptySpaceLoop:
    if (!(j < size)) {
        goto case3CheckEmptySpaceLoopEnd;
    }
    if (temp == targets[i][0] && rng[1] == targets[i][1]) {
        nope = 1;
    }
    //temp--;
    //printf("rngX:%i listX:%i rngY:%i listY:%i nope:%i i:%i\n", temp, targets[i][0], rng[1], targets[i][1], nope, i);

    temp--;
    j++;
    goto case3CheckEmptySpaceLoop;

case3CheckEmptySpaceLoopEnd:
    i++;
    goto case3OccupiedSpaceLoop;

case3OccupiedSpaceLoopEnd:
    if (nope) {
        //printf("hi");
        seed++;
        goto dirEnd; //CHECK IF THIS REBOOTS THE WHILE LOOP
    }
    // printf("%i %i %i %i\n", rng[0], rng[1], dir, size);
    i = 0;
case3ApplyShipLoop:
    if (!(i < size)) {
        goto case3ApplyShipLoopEnd;
    }
    //grid[rng[0]][rng[1]] = 'O';
    targets[targets_counter][0] = rng[0];
    targets[targets_counter][1] = rng[1];
    targets_counter++;
    rng[0]--;

    i++;
    goto case3ApplyShipLoop;

case3ApplyShipLoopEnd:
    done = !done;
    seed++;

case3OutOfBounds:
    seed++;
    //goto dirEnd;
dirEnd:
    //}
    //break;
    goto rngDir;

rngDirDone:
    //}
    //printf("%i\n", size);
    if (!secondThreeLong && size == 3) {
        size--;
        secondThreeLong = 1;
    }
    //}
    size++;
    goto rngShips;

rngShipsEnd:

    // rngShip(2);
    // rngShip(3);
    // rngShip(3);
    // rngShip(4);
    // rngShip(5);


    printf(
        "Welcome to battleships!\nIn this game you select a square to shoot\nto see if there is a ship hiding there.\nTry and sink all 5 ships with the lowest shots possible!\n");


    // for (int i = 0; i < 17; i++) {
    //     printf("%i %i\n", targets[i][0], targets[i][1]);
    //     grid[targets[i][0]][targets[i][1]] = 'O';
    // }
    //printf("%i\n", targets_counter);
    int gameOver = 0;
mainGameLoop:
    if (!(!gameOver)) {
        goto gameEnd;
    }
    //printBoard();
    //formerly printBoard()
printBoard:
    if (!(choosingColumn || choosingColumn == -1)) {
        goto noColumnArrow;
    }
    char symbol = '|';
    i = 0;
verticalArrowLoop:
    if (!(i < 2)) {
        goto verticalArrowLoopEnd;
    }
    printf("      ");
    j = 0;
verticalArrowAllColumnsLoop:
    if (!(j < 10)) {
        goto verticalArrowAllColumnsLoopEnd;
    }
    if (j == chosenColumn || chosenColumn == -1) {
        printf("   %c", symbol);
    } else {
        printf("    ");
    }

    j++;
    goto verticalArrowAllColumnsLoop;

verticalArrowAllColumnsLoopEnd:
    symbol = 'v';
    printf("\n");

    i++;
    goto verticalArrowLoop;

verticalArrowLoopEnd:

noColumnArrow:
    printf("         1   2   3   4   5   6   7   8   9   10\n");

    i = 0;
horizontalArrowLoop:
    if (!(i < 10)) {
        goto horizontalArrowLoopEnd;
    }
    char output[50];
    snprintf(output, sizeof(output), "     %i | %c | %c | %c | %c | %c | %c | %c | %c | %c | %c |", (i + 1),
             grid[i][0], grid[i][1], grid[i][2], grid[i][3], grid[i][4], grid[i][5], grid[i][6], grid[i][7],
             grid[i][8], grid[i][9]);

    if ((choosingRow || choosingRow == -1) && (i == chosenRow || chosenRow == -1)) {
        output[0] = '-';
        output[1] = '-';
        output[2] = '>';
    }


    if (!(i == 9)) {
        goto horizontalArrowNotOn10;;
    }
    j = 3;
horizontalArrowOffsetFor10Loop:
    if (!(j < sizeof(output))) {
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
    //end of printBoard
    if (hits == 17) {
        goto printBoardReturnWin;
    } else if (gameOver) {
        goto printBoardReturnForfeit;
    } else if (!doneConfirm) {
        goto printBoardReturnConfirming;
    } else if (choosingColumn) {
        goto printBoardReturnColumn;
    } else if (choosingRow) {
        goto printBoardReturnRow;
    }

    char input[3] = "-1";
    printf("Misses: X\tHits: O\nShots fired: %i\nPlease select from the following:\n1. shoot\n2. forfeit\n",
           shotsFired);
    fflush(stdin);
    fgets(input, sizeof(input), stdin);
    //printf("%s, %i\n", input, input == "1");
    //printf("%i\n", input);
    //printf("%i\n", input);
    if (strcmp(input, "1\n") == 0) {
        goto menuInput1;
    } else if (strcmp(input, "2\n") == 0) {
        goto menuInput2;
    } else {
        goto invalidMenuInput;
    }
    // switch (input) {
    //     case "1"://shoot

menuInput1:
    fflush(stdin);
    doneShooting = 0;
shooting:
    if (!(!doneShooting)) {
        goto shootingEnd;
    }
    doneConfirm = 1;
selectingRow:
    if (!(!doneSelecting)) {
        goto selectingRowEnd;
    }
    choosingRow = 1;
    chosenRow = -1;
    goto printBoard;
printBoardReturnRow:

    printf("Please select the row number to shoot:\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);
    if (!(strcmp(input, "1\n") == 0 || strcmp(input, "2\n") == 0 || strcmp(input, "3\n") == 0 ||
          strcmp(input, "4\n") == 0 || strcmp(input, "5\n") == 0 || strcmp(input, "6\n") == 0 ||
          strcmp(input, "7\n") == 0 || strcmp(input, "8\n") == 0 || strcmp(input, "9\n") == 0 || strcmp(
              input, "10") == 0)) {
        goto rowInvalid;
    }
    // switch (input) {
    //     case "1":
    //     case "2":
    //     case "3":
    //     case "4":
    //     case "5":
    //     case "6":
    //     case "7":
    //     case "8":
    //     case "9":
    //     case "10":
    chosenRow = atoi(input) - 1;
    doneSelecting = 1;
    choosingRow = -1;
    goto checkRowInputEnd;

rowInvalid:
    //printf("%i\n", chosenRow);
    // break;

    // default:
    printf("Please select a valid row number!\n");
    // break;

checkRowInputEnd:
    goto selectingRow;

selectingRowEnd:
    fflush(stdin);


    doneSelecting = 0;
selectingColumn:
    if (!(!doneSelecting)) {
        goto selectingColumnEnd;
    }
    choosingColumn = 1;
    chosenColumn = -1;
    //printf("%i", choosingRow);
    goto printBoard;
printBoardReturnColumn:

    printf("Please select the column number to shoot:\n");
    fflush(stdin);
    fgets(input, sizeof(input), stdin);
    //input = fgetc(stdin) - 48;
    if (!(strcmp(input, "1\n") == 0 || strcmp(input, "2\n") == 0 || strcmp(input, "3\n") == 0 ||
          strcmp(input, "4\n") == 0 || strcmp(input, "5\n") == 0 || strcmp(input, "6\n") == 0 ||
          strcmp(input, "7\n") == 0 || strcmp(input, "8\n") == 0 || strcmp(input, "9\n") == 0 || strcmp(
              input, "10") == 0)) {
        goto invalidColumn;
    }
    // switch (input) {
    //     case "1":
    //     case "2":
    //     case "3":
    //     case "4":
    //     case "5":
    //     case "6":
    //     case "7":
    //     case "8":
    //     case "9":
    //     case "10":

    chosenColumn = atoi(input) - 1;
    //printf("%i", doneConfirm);
    doneSelecting = 1;
    choosingColumn = -1;
    goto checkColumnInputEnd;

invalidColumn:
    //printf("%i\n", chosenRow);
    // break;

    // default:
    printf("Please select a valid column number!\n");
    // break;

checkColumnInputEnd:
    goto selectingColumn;

selectingColumnEnd:
    fflush(stdin);


    //printf("%i %i\n", choosingColumn, chosenColumn);
    doneConfirm = 0;
confirming:
    if (!(!doneConfirm)) {
        goto confirmingEnd;
    }
    //printf("hi");
    goto printBoard;
printBoardReturnConfirming:

    printf("You sure you want to shoot there?(Y/N)\n");
    fflush(stdin);
    input[0] = fgetc(stdin);
    switch (input[0]) {
        case 'y':
        case 'Y':
            goto confirmYes;

        case 'N':
        case 'n':
            goto confirmNo;
        default:
            goto invalidConfirm;
    }

    //printf("yes");
confirmYes:
    i = 0;
checkIfHitLoop:
    if (!(i < 17)) {
        goto checkIfHitLoopEnd;
    }
    if (!(targets[i][0] == chosenRow && targets[i][1] == chosenColumn)) {
        goto miss;
    }
    grid[chosenRow][chosenColumn] = 'O';
    hits++;
    shotsFired++;
    goto confirmSwitchEnd;

miss:
    grid[chosenRow][chosenColumn] = 'X';


    i++;
    goto checkIfHitLoop;

checkIfHitLoopEnd:
    doneConfirm = 1;
    doneShooting = 1;
    chosenRow = -1;
    chosenColumn = -1;
    shotsFired++;
    goto confirmSwitchEnd;

confirmNo:
    //printf("no");
    goto confirmSwitchEnd;

invalidConfirm:
    //printf("lol");
    printf("invalid input!\n");

confirmSwitchEnd:
    doneConfirm = 1;
    doneShooting = 0;
    doneSelecting = 0;
    choosingRow = 0;
    chosenRow = 0;
    choosingColumn = 0;
    chosenColumn = 0;
    fflush(stdin);
    goto confirming;

confirmingEnd:
    printf("\n");

    goto mainGameLoop;

shootingEnd:

    doneShooting = 0;
    doneSelecting = 0;
    doneConfirm = 1;
    choosingRow = 0;
    chosenRow = -1;
    choosingColumn = 0;
    chosenColumn = -1;
    if (hits == 17) {
        goto notWin;
    }
    goto printBoard;
printBoardReturnWin:
    printf("You win!\n");
    gameOver = 1;

notWin:
    goto mainMenuInputEnd;

    // break;
    // case 2://forfeit
menuInput2:
    gameOver = 1;
    i = 0;
markingShipLocationsLoop:
    if (!(i < 17)) {
        goto markingShipLocationsLoopEnd;
    }
    if (grid[targets[i][0]][targets[i][1]] != 'O') {
        grid[targets[i][0]][targets[i][1]] = 'i';
        //printf("%i %i\n", targets[i][0], targets[i][1]);
    }

    i++;
    goto markingShipLocationsLoop;;

markingShipLocationsLoopEnd:
    goto printBoard;
printBoardReturnForfeit:
    printf("you lost!");
    goto mainMenuInputEnd;
    //show end board with ship locations here

invalidMenuInput:
    printf("invalid input!\n");
    // goto mainMenuInputEnd;

    // break;
mainMenuInputEnd:
    goto mainGameLoop;

gameEnd:

    return 0;
}
