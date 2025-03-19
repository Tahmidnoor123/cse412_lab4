#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

void start();

void loadingAnimation() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 14);
    printf("\n\n\t\t\t\tLoading, please wait...\n\n");
    printf("\t\t\t");

    for (int i = 0; i < 20; i++) {
        SetConsoleTextAttribute(h, i % 2 == 0 ? 10 : 11);
        printf("*");
        fflush(stdout);
        Sleep(100);
    }

    SetConsoleTextAttribute(h, 14);
    printf("\n\n");
    Sleep(500);
    SetConsoleTextAttribute(h, 7);
}

void showDevelopers() {
    system("cls");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(h, 10);
    printf("\n\n");
    printf("\t\t\t###########################################\n");
    printf("\t\t\t#                                         #\n");
    printf("\t\t\t#   Journey Through the Snare.....        #\n");
    printf("\t\t\t#                                         #\n");
    printf("\t\t\t###########################################\n");

    Sleep(1000);

    SetConsoleTextAttribute(h, 14);
    printf("\n\n\t\t\t\tDeveloped by:\n\n");
    SetConsoleTextAttribute(h, 11);
    printf("\t\t\t\t1. Mohammad Tahmid Noor\n");
    printf("\t\t\t\t2. Tasmiah Rahman Orpa\n");
    printf("\t\t\t\t3. Mahjabin Tasnim Samiha\n\n");

    SetConsoleTextAttribute(h, 7);
    Sleep(3000);
    system("cls");
}

bool isValid(int** arr, int row, int col, int n) {
    return (row >= 0 && col >= 0 && row < n && col < n && arr[row][col] == 1);
}

bool solveMaze(int** ar, int row, int col, int n, int** solAr) {
    if (row == n - 1 && col == n - 1) {
        solAr[row][col] = 1;
        return true;
    }
    if (isValid(ar, row, col, n)) {
        solAr[row][col] = 1;
        if (solveMaze(ar, row + 1, col, n, solAr)) {
            return true;
        }
        if (solveMaze(ar, row, col + 1, n, solAr)) {
            return true;
        }
        solAr[row][col] = 0;
        return false;
    }
    return false;
}

void menu() {
    system("COLOR 0E");
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    int choice;
    SetConsoleTextAttribute(h, 13);
    printf("\n\n\n");
    printf("\t\t\t*************************************\n");
    printf("\t\t\t*                                   *\n");
    printf("\t\t\t*     WELCOME TO RAT IN A MAZE      *\n");
    printf("\t\t\t*                                   *\n");
    printf("\t\t\t*************************************\n");

    SetConsoleTextAttribute(h, 11);
    printf("\n\n\t\t\t1. Start the Game\n");
    printf("\t\t\t2. Exit\n\n");

    SetConsoleTextAttribute(h, 14);
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            loadingAnimation();
            system("cls");
            start();
            break;
        case 2:
            system("cls");
            system("COLOR 0E");
            SetConsoleTextAttribute(h, 12);
            printf("\n\n\n\n\t\t\t\tEXITING..........\n");
            exit(0);
        default:
            system("cls");
            SetConsoleTextAttribute(h, 12);
            printf("\n\n\t\t\tERROR! Please enter 1 or 2 only.\n");
            menu();
    }
}

void start() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int stack[100][2];
    int top = -1;

    printf("Enter the Maze size: ");
    int n;
    scanf("%d", &n);

    int** maze = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        maze[i] = (int*)malloc(n * sizeof(int));
    }

    printf("Enter the Maze Structure (0 for blocked, 1 for path):\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    int** solMaze = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        solMaze[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            solMaze[i][j] = 0;
        }
    }

    if (solveMaze(maze, 0, 0, n, solMaze)) {
        system("cls");
        printf("Rat path is....\n\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (solMaze[i][j] == 0) {
                    SetConsoleTextAttribute(h, 4);
                    printf("0 ");
                } else if (solMaze[i][j] == 1) {
                    stack[++top][0] = i;
                    stack[top][1] = j;
                    SetConsoleTextAttribute(h, 2);
                    printf("1 ");
                }
            }
            printf("\n");
        }

        SetConsoleTextAttribute(h, 14);
        printf("\nRat path using stack...\n");
        for (int i = 0; i <= top; i++) {
            printf("(%d, %d)  ", stack[i][0], stack[i][1]);
        }
    } else {
        SetConsoleTextAttribute(h, 12);
        printf("\n\nSORRY! NO Path.\n\n");
    }

    SetConsoleTextAttribute(h, 14);
    printf("\n\n\n\n\t\t\t\tWant to play again??\n");
    printf("\t\t\t\tPRESS 1 for YES\n");
    printf("\t\t\t\tPRESS 2 for NO\n");

    int t;
    scanf("%d", &t);
    switch (t) {
        case 1:
            loadingAnimation();
            system("cls");
            menu();
            break;
        case 2:
            system("cls");
            system("COLOR 0E");
            printf("\n\n\n\n\t\t\t\tEXITING..........\n");
            exit(0);
        default:
            system("cls");
            system("COLOR 0E");
            printf("ERROR!!! PRESS 1 or 2 only......\n");
            start();
    }

    for (int i = 0; i < n; i++) {
        free(maze[i]);
        free(solMaze[i]);
    }
    free(maze);
    free(solMaze);
}

int main() {
    showDevelopers();
    menu();
}
