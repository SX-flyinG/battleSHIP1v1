#include <iostream>
#include <conio.h>

using namespace std;

void fillArray(char polePlayer[11][11]);
void PrintPole(char pole[11][11]);
void PlaceDestroyers(int& letterKey, int& numKey, int destroyer, char polePlayer[11][11]);
void PlaceCruiser(int letterKey, int numKey, int wayKey, int cruiser, char pole[11][11]);
void PlaceSubmarine(int letterKey, int numKey, int wayKey, int submarine, char pole[11][11]);
void PlaceBattleShip(int letterKey, int numKey, int wayKey, int submarine, char pole[11][11]);
void MarkSurroundings(int letterKey, int numKey, char pole[11][11]);
void WriteRow(int& letterKey);
void WriteColumn(int& numKey);
void PlayerMove(char field[11][11], char field2[11][11], char viewField[11][11], int& countOfMoves, int& switchSides, int& countOfShips, int letterKey, int numKey);
bool GameMode(char field[11][11], char field2[11][11], char field3[11][11], char field4[11][11], int& countOfMoves, int& swichSides, int countOfShipsPL1, int countOfShipsPL2, int letterKey, int numKey);

void fillArray(char polePlayer[11][11]) {

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            polePlayer[i][j] = '.';

            if (i == 0 && j != 0) {
                polePlayer[i][j] = char(47 + j);
            }
            if (j == 0 && i != 0) {
                polePlayer[i][j] = char(65 + i - 1);
            }
            if (i == 0 && j == 0) {
                polePlayer[i][j] = 'X';
            }
        }
    }
}

void PrintPole(char pole[11][11]) {
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            cout << pole[i][j] << " ";
        }
        cout << endl;
    }
}

void MarkSurroundings(int letterKey, int numKey, char pole[11][11]) {
    for (int i = letterKey - 1; i <= letterKey + 1; i++) {
        for (int j = numKey - 1; j <= numKey + 1; j++) {
            if (i >= 1 && i <= 10 && j >= 1 && j <= 10 && pole[i][j] == '.') {
                pole[i][j] = 'x';
            }
        }
    }
}

void PlaceDestroyers(int& letterKey, int& numKey, int destroyer, char pole[11][11]) {
    cout << "Firstly place ur destroyer's ships : " << endl;
    for (destroyer; destroyer > 0; destroyer--) {
        WriteRow(letterKey);
        WriteColumn(numKey);

        while (pole[letterKey][numKey] != '.') {
            cout << "\nThis position is already occupied, please choose another.\n";
            WriteRow(letterKey);
            WriteColumn(numKey);
        }

        pole[letterKey][numKey] = 'D';
        MarkSurroundings(letterKey, numKey, pole);
        PrintPole(pole);
    }
}

void PlaceCruiser(int letterKey, int numKey, int wayKey, int cruiser, char pole[11][11]) {
    cout << "\nSecondly place your cruiser's ships: \n" << endl;
    
    for (int c = 0;  c < cruiser; c++) {
        WriteRow(letterKey);
        WriteColumn(numKey);

        while (pole[letterKey][numKey] != '.') {
            cout << "\nThis position is already occupied, please choose another.\n";
            WriteRow(letterKey);
            WriteColumn(numKey);
        }

        bool validPlacement = false;
        while (!validPlacement) {
            cout << "\nWrite direction (W, w - up; A, a - left; S, s - down; D, d - right OR E , e - for replace): \n";
            wayKey = _getch();
            wayKey = toupper(wayKey);
            switch (wayKey) {
            case 'A':
                if (numKey - 1 >= 1 && pole[letterKey][numKey] == '.' && pole[letterKey][numKey - 1] == '.') {
                    pole[letterKey][numKey] = 'C';
                    pole[letterKey][numKey - 1] = 'C';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey - 1, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'S':
                if (letterKey + 1 <= 10 && pole[letterKey][numKey] == '.' && pole[letterKey + 1][numKey] == '.') {
                    pole[letterKey][numKey] = 'C';
                    pole[letterKey + 1][numKey] = 'C';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey + 1, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'D':
                if (numKey + 1 <= 10 && pole[letterKey][numKey] == '.' && pole[letterKey][numKey + 1] == '.') {
                    pole[letterKey][numKey] = 'C';
                    pole[letterKey][numKey + 1] = 'C';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey + 1, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'W':
                if (letterKey - 1 >= 1 && pole[letterKey][numKey] == '.' && pole[letterKey - 1][numKey] == '.') {
                    pole[letterKey][numKey] = 'C';
                    pole[letterKey - 1][numKey] = 'C';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey - 1, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'E':
                cout << "You chose to replace the cruiser. Choose a new position and direction.\n";
                if (c == 0) {
                    PlaceCruiser(letterKey, numKey, wayKey, cruiser, pole);
                 }
                else if (c == 1) {
                    PlaceCruiser(letterKey, numKey, wayKey, cruiser - 2, pole);
                }
                else {
                    PlaceCruiser(letterKey, numKey, wayKey, cruiser - 3, pole);
                }
                
            default:
                cout << "Invalid direction. Please use W, A, S, or D. Or E for replace the position.\n";
                break;
            }
        }
        
        PrintPole(pole);
        
    }
}


void PlaceSubmarine(int letterKey, int numKey, int wayKey, int submarine, char pole[11][11]) {
    cout << "\nSecondly place your submarine's ships: \n" << endl;

    for (int c = 0; c < submarine; c++) {  // Fixed loop condition
        WriteRow(letterKey);
        WriteColumn(numKey);

        while (pole[letterKey][numKey] != '.') {
            cout << "\nThis position is already occupied, please choose another.\n";
            WriteRow(letterKey);
            WriteColumn(numKey);
        }

        bool validPlacement = false;
        while (!validPlacement) {
            cout << "Write direction (W, w - up; A, a - left; S, s - down; D, d - right): \n";
            wayKey = _getch();
            wayKey = toupper(wayKey);

            switch (wayKey) {
            case 'A':
                if (numKey - 2 >= 1 && pole[letterKey][numKey] == '.'
                    && pole[letterKey][numKey - 1] == '.'
                    && pole[letterKey][numKey - 2] == '.') {
                    pole[letterKey][numKey] = 'S';
                    pole[letterKey][numKey - 1] = 'S';
                    pole[letterKey][numKey - 2] = 'S';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey - 1, pole);
                    MarkSurroundings(letterKey, numKey - 2, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'S':
                if (letterKey + 2 <= 10 && pole[letterKey][numKey] == '.'
                    && pole[letterKey + 1][numKey] == '.'
                    && pole[letterKey + 2][numKey] == '.') {
                    pole[letterKey][numKey] = 'S';
                    pole[letterKey + 1][numKey] = 'S';
                    pole[letterKey + 2][numKey] = 'S';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey + 1, numKey, pole);
                    MarkSurroundings(letterKey + 2, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'D':
                if (numKey + 2 <= 10 && pole[letterKey][numKey] == '.'
                    && pole[letterKey][numKey + 1] == '.'
                    && pole[letterKey][numKey + 2] == '.') {
                    pole[letterKey][numKey] = 'S';
                    pole[letterKey][numKey + 1] = 'S';
                    pole[letterKey][numKey + 2] = 'S';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey + 1, pole);
                    MarkSurroundings(letterKey, numKey + 2, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'W':
                if (letterKey - 2 >= 1 && pole[letterKey][numKey] == '.'
                    && pole[letterKey - 1][numKey] == '.'
                    && pole[letterKey - 2][numKey] == '.') {
                    pole[letterKey][numKey] = 'S';
                    pole[letterKey - 1][numKey] = 'S';
                    pole[letterKey - 2][numKey] = 'S';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey - 1, numKey, pole);
                    MarkSurroundings(letterKey - 2, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            default:
                cout << "Invalid direction. Please use W, A, S, or D.\n";
            }
        }

        PrintPole(pole);
    }
}

void PlaceBattleShip(int letterKey, int numKey, int wayKey, int battleShip, char pole[11][11]) {
    cout << "\nSecondly place your battleship's ships: \n" << endl;

    for (int c = 0; c < battleShip; c++) {  // Fixed loop condition
        WriteRow(letterKey);
        WriteColumn(numKey);

        while (pole[letterKey][numKey] != '.') {
            cout << "\nThis position is already occupied, please choose another.\n";
            WriteRow(letterKey);
            WriteColumn(numKey);
        }

        bool validPlacement = false;
        while (!validPlacement) {
            cout << "Write direction (W, w - up; A, a - left; S, s - down; D, d - right): \n";
            wayKey = _getch();
            wayKey = toupper(wayKey);

            switch (wayKey) {
            case 'A':
                if (numKey - 3 >= 1 && pole[letterKey][numKey] == '.'
                    && pole[letterKey][numKey - 1] == '.'
                    && pole[letterKey][numKey - 2] == '.'
                    && pole[letterKey][numKey - 3] == '.') {
                    pole[letterKey][numKey] = 'B';
                    pole[letterKey][numKey - 1] = 'B';
                    pole[letterKey][numKey - 2] = 'B';
                    pole[letterKey][numKey - 3] = 'B';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey - 1, pole);
                    MarkSurroundings(letterKey, numKey - 2, pole);
                    MarkSurroundings(letterKey, numKey - 3, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'S':
                if (letterKey + 3 <= 10 && pole[letterKey][numKey] == '.'
                    && pole[letterKey + 1][numKey] == '.'
                    && pole[letterKey + 2][numKey] == '.'
                    && pole[letterKey + 3][numKey] == '.') {
                    pole[letterKey][numKey] = 'B';
                    pole[letterKey + 1][numKey] = 'B';
                    pole[letterKey + 2][numKey] = 'B';
                    pole[letterKey + 3][numKey] = 'B';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey + 1, numKey, pole);
                    MarkSurroundings(letterKey + 2, numKey, pole);
                    MarkSurroundings(letterKey + 3, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'D':
                if (numKey + 3 <= 10 && pole[letterKey][numKey] == '.'
                    && pole[letterKey][numKey + 1] == '.'
                    && pole[letterKey][numKey + 2] == '.'
                    && pole[letterKey][numKey + 3] == '.') {
                    pole[letterKey][numKey] = 'B';
                    pole[letterKey][numKey + 1] = 'B';
                    pole[letterKey][numKey + 2] = 'B';
                    pole[letterKey][numKey + 3] = 'B';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey, numKey + 1, pole);
                    MarkSurroundings(letterKey, numKey + 2, pole);
                    MarkSurroundings(letterKey, numKey + 3, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            case 'W':
                if (letterKey - 3 >= 1 && pole[letterKey][numKey] == '.'
                    && pole[letterKey - 1][numKey] == '.'
                    && pole[letterKey - 2][numKey] == '.'
                    && pole[letterKey - 3][numKey] == '.') {
                    pole[letterKey][numKey] = 'B';
                    pole[letterKey - 1][numKey] = 'B';
                    pole[letterKey - 2][numKey] = 'B';
                    pole[letterKey - 3][numKey] = 'B';
                    MarkSurroundings(letterKey, numKey, pole);
                    MarkSurroundings(letterKey - 1, numKey, pole);
                    MarkSurroundings(letterKey - 2, numKey, pole);
                    MarkSurroundings(letterKey - 3, numKey, pole);
                    validPlacement = true;
                }
                else {
                    cout << "Invalid placement! Try again.\n";
                }
                break;
            default:
                cout << "Invalid direction. Please use W, A, S, or D .\n";
            }
        }

        PrintPole(pole);
    }
}

void WriteRow(int& letterKey) {
    do {
        cout << "\nWrite a row (A - J or a - j): \n";
        letterKey = _getch();
        cout << (char)letterKey << "\n";
    } while ((letterKey < 65 || letterKey > 74) && (letterKey < 97 || letterKey > 106));

    switch (letterKey) {
    case 65:
    case 97:
        letterKey = 1;
        break;
    case 66:
    case 98:
        letterKey = 2;
        break;
    case 67:
    case 99:
        letterKey = 3;
        break;
    case 68:
    case 100:
        letterKey = 4;
        break;
    case 69:
    case 101:
        letterKey = 5;
        break;
    case 70:
    case 102:
        letterKey = 6;
        break;
    case 71:
    case 103:
        letterKey = 7;
        break;
    case 72:
    case 104:
        letterKey = 8;
        break;
    case 73:
    case 105:
        letterKey = 9;
        break;
    case 74:
    case 106:
        letterKey = 10;
        break;
    default:
        break;
    }
}

void WriteColumn(int& numKey) {
    do {
        cout << "\nWrite a column (1 - 10): ";
        numKey = _getch();
        cout << (char)numKey << "\n";
    } while (numKey < 48 || numKey > 57);

    switch (numKey) {
    case 48:
        numKey = 1;
        break;
    case 49:
        numKey = 2;
        break;
    case 50:
        numKey = 3;
        break;
    case 51:
        numKey = 4;
        break;
    case 52:
        numKey = 5;
        break;
    case 53:
        numKey = 6;
        break;
    case 54:
        numKey = 7;
        break;
    case 55:
        numKey = 8;
        break;
    case 56:
        numKey = 9;
        break;
    case 57:
        numKey = 10;
        break;
    default:
        break;
    }
}

void PlayerMove(char field[11][11], char rivalField[11][11], char shotsField[11][11], int& countOfMoves, int& switchSides, int& countOfShips, int letterKey, int numKey) {
    WriteRow(letterKey);
    WriteColumn(numKey);

    if (shotsField[letterKey][numKey] != '.') {
        cout << "You already attacked this position. Try again." << endl;
        return;
    }

    if (rivalField[letterKey][numKey] != '.' && rivalField[letterKey][numKey] != 'X') {
        cout << "Hit!" << endl;
        shotsField[letterKey][numKey] = 'X';
        rivalField[letterKey][numKey] = 'X';
        countOfShips--;
    }
    else {
        cout << "Miss!" << endl;
        shotsField[letterKey][numKey] = '0';
        switchSides++;
    }

    countOfMoves++;
    cout << "Your shots field:" << endl;
    PrintPole(shotsField);
}

bool GameMode(char mainField[11][11], char rivalField[11][11], char viewRivalField[11][11], char viewMainField[11][11], int& countOfMoves, int& swichSides, int countOfShipsPL1, int countOfShipsPL2, int letterKey, int numKey) {
    if (countOfShipsPL1 == 0) {
        cout << "Player2 wins the game!!!" << endl;
        return false;
    }
    if (countOfShipsPL2 == 0) {
        cout << "Player win the game!!!" << endl;
        return false;
    }
    if (swichSides % 2 == 0) {
        cout << "Player 1's move:" << endl;
        PlayerMove(mainField, rivalField, viewRivalField, countOfMoves, swichSides, countOfShipsPL2, letterKey, numKey);
    }
    else {
        cout << "Player 2's move:" << endl;
        PlayerMove(rivalField, mainField, viewMainField, countOfMoves, swichSides, countOfShipsPL1, letterKey, numKey);
    }

    return true;
}



int main() {
    int letterKey = 0;
    int numKey = 0;
    int wayKey = 0;
    int countOfDestroyShip = 4;
    int countOfCruiseShip = 3;
    int countOfSubmarines = 2;
    int countOfBattleShips = 1;
    int countOfAllShips = 10;
    char polePlayer[11][11];
    char polePlayer2[11][11];
    char player1Shots[11][11];
    char player2Shots[11][11];
    int countOfMoves = 0;
    int swichSides = 0;

    fillArray(polePlayer);
    fillArray(polePlayer2);
    fillArray(player1Shots);
    fillArray(player2Shots);
    cout << "Player num1 please place ur ship's : " << endl;
    PlaceDestroyers(letterKey, numKey, countOfDestroyShip, polePlayer);
    PlaceCruiser(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer);
    PlaceSubmarine(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer);
    PlaceBattleShip(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer);
    cout << "Player num2 please place ur ship's : " << endl;
    PlaceDestroyers(letterKey, numKey, countOfDestroyShip, polePlayer2);
    PlaceCruiser(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer2);
    PlaceSubmarine(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer2);
    PlaceBattleShip(letterKey, numKey, wayKey, countOfCruiseShip, polePlayer2);
    while (GameMode(polePlayer, polePlayer2, player1Shots, player2Shots, countOfMoves, swichSides, countOfAllShips, countOfAllShips, letterKey, numKey));
    return 0;
}

/* Letters for way
W - 87;
w - 119;
A - 65;
a - 97;
S - 83;
s - 115;
D - 68;
d - 100;
*/

/* Letters for fıll pole
A - 65;
a - 97;
B - 66;
b - 98;
C - 67;
c - 99;
D - 68;
d - 100;
E - 69;
e - 101;
F - 70;
f - 102;
G - 71;
g - 103;
H - 72;
h - 104;
I - 73;
i - 105;
J - 74;
j - 106;
*/

/* Nums for pole
0 - 48;
1 - 49;
2 - 50;
3 - 51;
4 - 52;
5 - 53;
6 - 54;
7 - 55;
8 - 56;
9 - 57;
*/