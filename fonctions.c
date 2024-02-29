#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <windows.h>

void game_motion_esc()      //fonction pour afficher le titre du jeu avec effets et couleur
{
    printf("\033[31m");
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$$$$\\   $$$$$$\\    $$$$$$\\ \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$  _____| $$  _ $$\\  $$  __$$\\ \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$ |       $$ / \\__|  $$ / \\__| \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$\\      $$$$$$    $$ | \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$  __|       \\_ $$   $$ | \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$ |       $$   |$$\\  $$ |  $$\\ \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$$$$\\  \\$$$$$$ |  \\$$$$$$ | \n");
    Sleep(200);
    printf("\t\t\t\t\t\t\t\t\t\t \\_______|   \\_____/    \\______/ \n");
    printf("\033[0m");
    Sleep(200);
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t");
}


void game_motion_esc_stable()           //fonction pour afficher le titre du jeu
{
    printf("\033[31m");
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$$$$\\   $$$$$$\\    $$$$$$\\ \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$  _____| $$  _ $$\\  $$  __$$\\ \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$ |       $$ / \\__|  $$ / \\__| \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$\\      $$$$$$    $$ | \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$  __|       \\_ $$   $$ | \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$ |       $$   |$$\\  $$ |  $$\\ \n");
    printf("\t\t\t\t\t\t\t\t\t\t $$$$$$$$\\  \\$$$$$$ |  \\$$$$$$ | \n");
    printf("\t\t\t\t\t\t\t\t\t\t \\_______|   \\_____/    \\______/ \n");
    printf("\033[0m");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t");
    printf("\n\n\n\t\t\t\t\t\t\t\t\t\t");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
}

void menu_display()             //fonction pour afficher les choix du menu
{
    printf("Bienvenue sur ESC!!!");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("Veuiller selectionner un choix:");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("1.Jouer");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("2.Parametres");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("3.Scoreboard");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("4.Tutoriel");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("5.Quitter");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
}

void settings_display()             //fonction pour afficher le choix des parametres
{
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("Vous voulez modifier les parametres de jeu:");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("1.Nombre d'obstacles");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("2.Nombre d'ennemis");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("3.Frequence des points bonus");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
    printf("4.Retour menu");
    printf("\n");
    printf("\t\t\t\t\t\t\t------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t\t");
    printf("| Apres avoir modifier les parametre cliquer sur 4 pour revenir au menu principale |");
    printf("\n\t\t\t\t\t\t\t------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t\t\t\t\t\t\t");
}

void score_display()            //fonction pour afficher la partie visuelle des scores
{
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t       -----");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t\t      |SCORE|");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t------------------------------------");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t|Appuyez sur 0 pour revenir au menu|");
    printf("\n\t\t\t\t\t\t\t\t\t\t\t------------------------------------");
}


void signature_chris_william()      //fonction pour afficher notre signature a la fin du jeu sous forme d'un texte qui change de font et cree un effet
{

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(console, &info);

    int i = 0;
    while (i<21) {
        SetConsoleCursorPosition(console, info.dwCursorPosition);

        if (i % 2 == 0) {
            SetConsoleTextAttribute(console, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
            printf("\n\n");
            printf("\n\t\t\t\t\t\t\t\t   _____ _          _               __          ___ _ _ _                 \n");
            printf("\t\t\t\t\t\t\t\t  / ____| |        (_)       ___    \\ \\        / (_) | (_)                \n");
            printf("\t\t\t\t\t\t\t\t | |    | |__  _ __ _ ___   ( _ )    \\ \\  /\\  / / _| | |_  __ _ _ __ ___  \n");
            printf("\t\t\t\t\t\t\t\t | |    | '_ \\| '__| / __|  / _ \\/\\   \\ \\/  \\/ / | | | | |/ _` | '_ ` _ \\ \n");
            printf("\t\t\t\t\t\t\t\t | |____| | | | |  | \\__ \\ | (_>  <    \\  /\\  /  | | | | | (_| | | | | | |\n");
            printf("\t\t\t\t\t\t\t\t  \\_____|_| |_|_|  |_|___/  \\___/\\/     \\/  \\/   |_|_|_|_|\\__,_|_| |_| |_|\n");
            printf("\t\t\t\t\t\t\t\t                                                                          ");
        } else {
            SetConsoleTextAttribute(console, BACKGROUND_INTENSITY);
            printf("\n\n\n\t\t\t\t\t\t\t\t                                                                          ");
            printf("\n\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          \n");
            printf("\t\t\t\t\t\t\t\t                                                                          ");

        }

        i++;
        Sleep(1000);
    }



}



void game_over()
{
            printf("\n\t\t\t\t\t\t\t\t\t\t   _____                                ____                 \n");
            printf("\t\t\t\t\t\t\t\t\t\t  / ____|                              / __ \\                \n");
            printf("\t\t\t\t\t\t\t\t\t\t | |  __  __ _ _ __ ___   ___         | |  | |_   _____ _ __ \n");
            printf("\t\t\t\t\t\t\t\t\t\t | | |_ |/ _` | '_ ` _ \\ / _ \\        | |  | \\ \\ / / _ \\ '__|\n");
            printf("\t\t\t\t\t\t\t\t\t\t | |__| | (_| | | | | | |  __/        | |__| |\\ V /  __/ |   \n");
            printf("\t\t\t\t\t\t\t\t\t\t  \\_____|\\__,_|_| |_| |_|\\___|         \\____/  \\_/ \\___|_|   \n");
            printf("\t\t\t\t\t\t\t\t\t\t\n");
}

void fin_de_partie()
{
        printf("\n\t\t\t\t\t\t\t\t\t\t\n");
        printf("\t\t\t\t\t\t\t\t\t\t  ______ _             _____            _____           _   _      \n");
        printf("\t\t\t\t\t\t\t\t\t\t |  ____(_)           |  __ \\          |  __ \\         | | (_)     \n");
        printf("\t\t\t\t\t\t\t\t\t\t | |__   _ _ __       | |  | | ___     | |__) |_ _ _ __| |_ _  ___ \n");
        printf("\t\t\t\t\t\t\t\t\t\t |  __| | | '_ \\      | |  | |/ _ \\    |  ___/ _` | '__| __| |/ _ \\\n");
        printf("\t\t\t\t\t\t\t\t\t\t | |    | | | | |     | |__| |  __/    | |  | (_| | |  | |_| |  __/\n");
        printf("\t\t\t\t\t\t\t\t\t\t |_|    |_|_| |_|     |_____/ \\___|    |_|   \\__,_|_|   \\__|_|\\___|\n");
        printf("\t\t\t\t\t\t\t\t\t\t\n");
}
