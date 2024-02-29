#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"//on utilise un fichier pour utiliser des fonctions d'affichage
#include <conio.h>          //pour la fonction getch()
#include <windows.h>
#include <unistd.h>     //pour la fonction sleep
#include <math.h>
#include <time.h>       //pour l'affichage du temps
#include <string.h>     //pour la fonction sauvegarde
#include <sys/stat.h>   //pour la fonction sauvegarde
#include <sys/types.h>  //pour la fonction sauvegarde

//on defini le nombre de score maximale qu'on peut sauvegarder
#define MAX_SCORES 100
//on definit la longeur maximale de chaine de charactere pour le nom des joueur
#define MAX_NAME_LENGTH 20

//Prototypes des fonctions
void deplacement_joueur(int,int,int);
void clrscr();
void Timer(int*,int*);
void full_screen();
void Menu();
int attente(int,int,int portequisouvre[][2],int,int bonus[][2],int,int,int ennemi[][2]);
void coul_Joueur(int,int);
void coul_Normale(void);
void coul_Objet(int,int);
void laby1(void);
void afficheCarte(int,int,int portequisouvre[][2],int,int bonus[][2],int,int,int ennemi[][2]);
void Ouvreporte(int,int,int,int);
int changeetat(int);
void nombreporte(char,int *,int coordporte[][2]);
int verifportediff(int,int,int portequisouvre[][2]);
int verifsiestuneporte(int portequisouvre[][2],int,int,int);
void nombredespace(int *,int coordespace[][2]);
int verifbonusdiff(int,int,int bonus[][2]);
int verifsiestunbonus(int bonus[][2],int,int,int);
void Sortie(int,int,int,int,int*,int*);
int Findeniveau(int,int,int,int,int, int,int,int,int);
float dist(int,int,int,int);
int score_saver(int,int,int);
int score_triage();
void echange();
int Choixdifficulte(void);
int Choixporte(int);
int Choixennemi(int);
int Choixbonus(int);
void Parametres(int*,int*,int*,int);
void compteurdeptsbonus(int, int,int bonus[][2],int);
int score_finale_joueur(int, int,int,int,int);
int verifsiestunennemi(int ennemi[][2],int,int, int);
int verifennemidiff(int, int, int ennemi[][2]);
void compteurdesennemies(int, int, int ennemi[][2],int);
int attentioncontact(int,int);
//fin prototype des fonctions

//variable globale
int nombre_bonus_pris=0;
int nombre_ennemies_pris=0;
int ligne=35,colonne=70;
char Carte[35][70];
int compteur=0;
int etatporte=1;
char names[MAX_SCORES][MAX_NAME_LENGTH];
int scores[MAX_SCORES];
char nom_joueur[MAX_NAME_LENGTH];
int difficultechoisie=0;
int paramfait=0;
//fin variable globale



int main()
{

    Menu();


    return 0;
}


void deplacement_joueur(int nombrechoisideporte,int nombre_bonus_param,int nombre_ennemies_param)
{
    // Initialisation pour faire fonctionner la partie

    char joueur='@';        //le charactere @ represente le joueur
    int posi1,posi2;//=2





    laby1(); // Initialise la carte


    int lignesortie,colsortie; //position de la sortie

    int portequisouvre[nombrechoisideporte][2]; // la position des portes
    int coordporte[(ligne-2)*(colonne-2)][2]; // la position de tous les murs pouvant etre des portes
    int nombredeporte; // le nombre de murs pouvant etre des portes

    int bonus[nombre_bonus_param][2]; // la position des bonus
    int coordespace[(ligne-2)*(colonne-2)][2]; // la position de tous les espaces pouvant etre des bonus
    int nombredeespace; // le nombre d'espace pouvant etre des bonus

    //ennemie

    int ennemi[nombre_ennemies_param][2];

    char mur='|';//on assigne le charactere | aux murs

    int randporte; //indice d'une porte aleatoire
    int randbonus; //indice d'un bonus aleatoire
    int randpos; //indice de la pos du joueur aleatoire
    int randennemi;

    int minutes,secondes; //variable pour le timer

    int pas=2; // le temps qu'une porte reste ouverte/fermee

    int limmin=10; //distance min et max ou se trouve la sortie
    int limmax=15;

    nombreporte(mur,&nombredeporte,coordporte); //donne le nombre de murs-portes max et donne leur position
    nombredespace(&nombredeespace,coordespace);//donne le nombre de espace-bonus max et donne leur position


    srand(time(NULL)); //rend la fonction rand aleatoire



    for (int i = 0; i < nombrechoisideporte; i++) // boucle pour prendre un mur et le rendre porte aleatoirement parmi les murs
    {
        do
        {
        randporte = rand() % nombredeporte;
        }while (verifportediff(randporte,i,coordporte)==1);
        portequisouvre[i][0] = coordporte[randporte][0];
        portequisouvre[i][1] = coordporte[randporte][1];
    }

    for (int i = 0; i < nombre_bonus_param; i++) // boucle pour prendre un espace et le rendre bonus aleatoirement
    {
        do
        {
            randbonus = rand() % nombredeespace;
        }while (verifbonusdiff(randbonus,i,coordespace)==1);
        bonus[i][0] = coordespace[randbonus][0];
        bonus[i][1] = coordespace[randbonus][1];
    }

    for (int i = 0; i < nombre_ennemies_param; i++) // boucle pour prendre un espace et le rendre bonus aleatoirement
    {
        do
        {
            randennemi = rand() % nombredeespace;
        }while (verifennemidiff(randennemi,i,coordespace)==1 || verifsiestunbonus(bonus, nombre_bonus_param,coordespace[randennemi][0],coordespace[randennemi][1])==1);
        ennemi[i][0] = coordespace[randennemi][0];
        ennemi[i][1] = coordespace[randennemi][1];
    }

    for(int j=0;j<nombre_bonus_param;j++) //ajoute les bonus a la carte
    {
        int x=bonus[j][0];
        int y=bonus[j][1];
        Carte[x][y]='B';
    }
    for(int j=0;j<nombre_ennemies_param;j++) //ajoute les ennemis a la carte
    {
        int x=ennemi[j][0];
        int y=ennemi[j][1];
        Carte[x][y]='X';
    }

    do //met le joueur dans une pos aleatoire (qui etait un espace)
    {
        randpos = rand() % nombredeespace;
    }while (verifsiestunbonus(bonus,nombre_bonus_param,coordespace[randpos][0],coordespace[randpos][1])==1);

    posi1 = coordespace[randpos][0];
    posi2 = coordespace[randpos][1];

    Carte[posi1][posi2]= joueur; //met le charctere du joueur à sa position

    Sortie(posi1,posi2,limmin,limmax,&lignesortie,&colsortie); //positionne la sortie aleatoirement




        do
        {
        Timer(&minutes,&secondes);

        if(Findeniveau(posi1,posi2,lignesortie,colsortie,minutes,secondes,nombre_bonus_pris,nombre_ennemies_pris,nombre_ennemies_param)==1) // joueur est a la sortie, petite pause avant de sortir de la map
        {
            score_saver(minutes,secondes,nombre_ennemies_param);
            //sleep(2);
            break;
        }
        else if (Findeniveau(posi1,posi2,lignesortie,colsortie,minutes,secondes,nombre_bonus_pris,nombre_ennemies_pris,nombre_ennemies_param)==0)
        {
            score_saver(minutes,secondes,nombre_ennemies_param);
            clrscr();
            game_motion_esc_stable();
            game_over();

            sleep(5);
            break;
        }

        int input; //prned le mouvement du joueur

        input=attente(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi); //attend le mouvement du joueur ou met a jour la carte avec les mouvements des entite lorsque le temps de raffraichissement est atteint

        etatporte=changeetat(pas); //ouvre ou ferme les portes en fonction du pas choisi


        for(int j=0;j<nombrechoisideporte;j++) //ouvre/ferme les portes
        {
            Ouvreporte(portequisouvre[j][0],portequisouvre[j][1],pas,etatporte);
        }
        int mvttrouve=0;
        int randmvt;

        for (int i=0;i<nombre_ennemies_param;i++)//mvt des ennemis
        {
            if(ennemi[i][0]!=-1)//l'ennemi existe
            {
                mvttrouve=0; //regarde si il a fait un mvt sinon continu
                do
                {
                    randmvt=rand()%4;
                    if(randmvt==0 && attentioncontact(ennemi[i][0]-1,ennemi[i][1])==0)//peut aller haut
                    {
                        Carte[ennemi[i][0]][ennemi[i][1]]=' ';
                        if (ennemi[i][0]-1==posi1 && ennemi[i][1]==posi2)//est sur la pos du joueur
                        {
                            ennemi[i][0]=-1;//le supprime
                            ennemi[i][1]=-1;
                            nombre_ennemies_pris+=1;//soustrait au score
                        }
                        else
                        {
                            int x=ennemi[i][0]-1;
                            ennemi[i][0]=ennemi[i][0]-1;
                            int y=ennemi[i][1];
                            Carte[x][y]='X';
                        }
                        mvttrouve=1;

                    }
                    else if(randmvt==1 && attentioncontact(ennemi[i][0]+1,ennemi[i][1])==0)//peut aller bas
                    {
                        Carte[ennemi[i][0]][ennemi[i][1]]=' ';
                        if (ennemi[i][0]+1==posi1 && ennemi[i][1]==posi2)//est sur la pos du joueur
                        {
                            ennemi[i][0]=-1;//le supprime
                            ennemi[i][1]=-1;
                            nombre_ennemies_pris+=1;//soustrait au score
                        }
                        else
                        {
                            int x=ennemi[i][0]+1;
                            ennemi[i][0]=ennemi[i][0]+1;
                            int y=ennemi[i][1];
                            Carte[x][y]='X';
                        }
                        mvttrouve=1;
                    }
                    else if(randmvt==2 && attentioncontact(ennemi[i][0],ennemi[i][1]-1)==0)//peut aller gauche
                    {
                        Carte[ennemi[i][0]][ennemi[i][1]]=' ';
                        if (ennemi[i][0]==posi1 && ennemi[i][1]-1==posi2)//est sur la pos du joueur
                        {
                            ennemi[i][0]=-1;//le supprime
                            ennemi[i][1]=-1;
                            nombre_ennemies_pris+=1;//soustrait au score
                        }
                        else
                        {
                            int x=ennemi[i][0];
                            int y=ennemi[i][1]-1;
                            ennemi[i][1]=ennemi[i][1]-1;
                            Carte[x][y]='X';
                        }
                        mvttrouve=1;
                    }
                    else if(randmvt==3 && attentioncontact(ennemi[i][0],ennemi[i][1]+1)==0)//peut aller droite
                    {
                        Carte[ennemi[i][0]][ennemi[i][1]]=' ';
                        if (ennemi[i][0]==posi1 && ennemi[i][1]+1==posi2)//est sur la pos du joueur
                        {
                            ennemi[i][0]=-1;//le supprime
                            ennemi[i][1]=-1;
                            nombre_ennemies_pris+=1;//soustrait au score
                        }
                        else
                        {
                            int x=ennemi[i][0];
                            int y=ennemi[i][1]+1;
                            ennemi[i][1]=ennemi[i][1]+1;
                            Carte[x][y]='X';
                        }
                        mvttrouve=1;
                    }
                }while(mvttrouve==0); //continu tant qu'il n'a pas fait un mvt
            }
        }

        compteur++; //compteur pour le nombre de tour

        //mouvement du joueur

        if (input==56)//haut
        {
            if (Carte[posi1-1][posi2]=='|'||Carte[posi1-1][posi2]=='-'||Carte[posi1-1][posi2]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();//efface tout
                Carte[posi1][posi2]=' ';//ancienne pos du joueur effacee
                posi1=posi1-1;//change la pos du joueur
                Carte[posi1][posi2]='@';//nouvelle pos
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)//verifie si c'est un ennemi et supprimme sa position de la matrice ennemie pour ne pas avoir un ennemi fantome
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)//verifie si c'est un point bonus et supprimme sa position de la matrice bonus pour ne pas avoir un bonus fantome
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==50)//deplacement joueur vers le bas
        {
            if (Carte[posi1+1][posi2]=='|'||Carte[posi1+1][posi2]=='-'||Carte[posi1+1][posi2]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi1=posi1+1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule
            }

        }
        if (input==54)//deplacement joueur vers la droite
        {
            if (Carte[posi1][posi2+1]=='|'||Carte[posi1][posi2+1]=='-'||Carte[posi1][posi2+1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi2=posi2+1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==52)//deplacement joueur vers la gauche
        {
            if (Carte[posi1][posi2-1]=='|'||Carte[posi1][posi2-1]=='-'||Carte[posi1][posi2-1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi2=posi2-1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==57)//deplacement joueur vers la diagonale haut-droite
        {
            if (Carte[posi1-1][posi2+1]=='|'||Carte[posi1-1][posi2+1]=='-'||Carte[posi1-1][posi2+1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi1=posi1-1;
                posi2=posi2+1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }
                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==55)//deplacement joueur vers la diagonale haut-gauche
        {
            if (Carte[posi1-1][posi2-1]=='|'||Carte[posi1-1][posi2-1]=='-'||Carte[posi1-1][posi2-1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi1=posi1-1;
                posi2=posi2-1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==49)//deplacement joueur vers la diagonale bas-gauche
        {
            if (Carte[posi1+1][posi2-1]=='|'||Carte[posi1+1][posi2-1]=='-'||Carte[posi1+1][posi2-1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi1=posi1+1;
                posi2=posi2-1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }

                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==51)//deplacement joueur vers la diagonale bas-droite
        {
            if (Carte[posi1+1][posi2+1]=='|'||Carte[posi1+1][posi2+1]=='-'||Carte[posi1+1][posi2+1]=='+')             //pour ne pas depasser la bordure
                {}
            else
            {
                clrscr();
                Carte[posi1][posi2]=' ';
                posi1=posi1+1;
                posi2=posi2+1;
                Carte[posi1][posi2]='@';
                compteurdeptsbonus(posi1,posi2,bonus,nombre_bonus_param);
                compteurdesennemies(posi1,posi2,ennemi,nombre_ennemies_param);
                if(verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_ennemies_param;i++)
                    {
                        if (ennemi[i][0]==posi1 && ennemi[i][1]==posi2)
                        {
                            ennemi[i][0]=-1;
                            ennemi[i][1]=-1;
                        }
                    }
                }

                if(verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
                {
                    for (int i =0;i<nombre_bonus_param;i++)
                    {
                        if (bonus[i][0]==posi1 && bonus[i][1]==posi2)
                        {
                            bonus[i][0]=-1;
                            bonus[i][1]=-1;
                        }
                    }
                }
                afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);//reaffiche la carte avec la nouvelle pos, les portes ouvertes/fermees, le temps ecoule

            }

        }
        if (input==27)//quitter de force
        {
            clrscr();
            game_motion_esc_stable();
            printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\tVotre score ne sera pas sauvegarder!!");
            sleep(5);
            break; //quitte
        }
        }while(1);
}

int verifsiestunennemi(int ennemi[][2],int nombre_ennemies_param,int x, int y)
{
    for (int i = 0; i < nombre_ennemies_param; i++)//boucle qui verfie si un espace est un ennemi
    {
        if (ennemi[i][0] == x && ennemi[i][1] == y)
        {
            return 1;
        }
    }
    return 0;
}

int verifennemidiff(int idx, int max_idx, int ennemi[][2])//verfifie si l'ennemi est different des autres (pas de doublons)
{
    for (int i = 0; i < max_idx; i++) {
        if (ennemi[i][0] == ennemi[idx][0] && ennemi[i][1] == ennemi[idx][1]) {
            return 1;
        }
    }
    return 0;
}


int verifsiestunbonus(int bonus[][2], int nombre_bonus_param, int x, int y) //regarde si un espace est un bonus
{
    for (int i = 0; i < nombre_bonus_param; i++)
    {
        if (bonus[i][0] == x && bonus[i][1] == y)
        {
            return 1;
        }
    }
    return 0;
}

int verifbonusdiff(int idx, int max_idx, int bonus[][2]) //verfifie si le bonus est differente des autres (pas de doublons)
{
    for (int i = 0; i < max_idx; i++) {
        if (bonus[i][0] == bonus[idx][0] && bonus[i][1] == bonus[idx][1]) {
            return 1;
        }
    }
    return 0;
}

void nombredespace(int *nombredespace, int coordespace[][2]) //donne la pos de tous les espaces pouvant etre un bonus
{
    int compte = 0;
    for (int i = 1; i < ligne-1; i++) {
        for (int j = 1; j < colonne-2; j++) {
            if ((Carte[i][j] == ' '))
            {
                coordespace[compte][0] = i;
                coordespace[compte][1] = j;
                compte++;
            }
        }
    }
    *nombredespace = compte;
}



void Parametres(int* nombrechoisideporte,int* nombre_ennemies_param,int* nombre_bonus_param,int difficulte)
{   //fonction avec pointeurs pour recupere les valeurs des fonctions Choixporte(), Choixennemi() et Choixbonus() et specifier les valeurs limites
    int setting_choice;
    do
    {

        clrscr();
        game_motion_esc_stable();
        settings_display();
        setting_choice = getch();
        if (setting_choice == 49)
        {
            nombrechoisideporte[0]=Choixporte(difficulte);
        }
        else if(setting_choice == 50)
        {
            nombre_ennemies_param[0]=Choixennemi(difficulte);
        }
        else if (setting_choice == 51)
        {
            nombre_bonus_param[0]=Choixbonus(difficulte);
        }
        else if (setting_choice == 52)
        {
            break;
        }
    }while (setting_choice!=49 || setting_choice != 50 || setting_choice != 51 || setting_choice != 52);
}

int Choixbonus(int difficulte)
{   //fonction des limite le nombre de bonus pour chaque choix de difficultees et affiche la page pour entre le nombre de bonus
    int nombre_bonus_param=-1;
    int limitemini,limitemaxi;

    if(difficulte==1)
    {
        limitemini=30;
        limitemaxi=50;
    }
    if(difficulte==2)
    {
        limitemini=15;
        limitemaxi=30;
    }
    if(difficulte==3)
    {
        limitemini=0;
        limitemaxi=15;
    }

    while(nombre_bonus_param>limitemaxi || nombre_bonus_param<limitemini)
    {
        clrscr();
        game_motion_esc_stable();
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("Inserez le nombre de point bonus :");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("(Entre %d et %d)",limitemini,limitemaxi);
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        scanf("%d",&nombre_bonus_param);
        fflush(stdin);
    }

    //point_bonus(&frequence_bonus_param);
    printf("\n\n\t\t\t\t\t\t\t\t\t\t");
    printf("Le nombre de bonus est maintenant %d!",nombre_bonus_param);
    sleep(1);
    return nombre_bonus_param;
}

int Choixennemi(int difficulte)
{   //fonction des limite le nombre d'ennemis pour chaque choix de difficultees et affiche la page pour entre le nombre d'ennelis
    int nombre_ennemies_param=-1;
    int limitemini,limitemaxi;

    if(difficulte==1)
    {
        limitemini=0;
        limitemaxi=5;
    }
    if(difficulte==2)
    {
        limitemini=5;
        limitemaxi=10;
    }
    if(difficulte==3)
    {
        limitemini=10;
        limitemaxi=20;
    }

    while(nombre_ennemies_param>limitemaxi || nombre_ennemies_param<limitemini)
    {
        clrscr();
        game_motion_esc_stable();
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("Inserez le nombre d'ennemies que vous souhaiter avoir: ");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("(Entre %d et %d)",limitemini,limitemaxi);
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        scanf("%d",&nombre_ennemies_param);
        fflush(stdin);
    }

    printf("\n\n\t\t\t\t\t\t\t\t\t\t");
    printf("Le nombre d'ennemies est maintenant %d!",nombre_ennemies_param);
    sleep(1);
    return nombre_ennemies_param;
}

int Choixporte(int difficulte)
{   //fonction des limite le nombre de portes pour chaque choix de difficultees et affiche la page pour entre le nombre de portes
    int nombrechoisideporte=-1;
    int limitemini,limitemaxi;

    if(difficulte==1)
    {
        limitemini=25;
        limitemaxi=85;
    }
    if(difficulte==2)
    {
        limitemini=10;
        limitemaxi=50;
    }
    if(difficulte==3)
    {
        limitemini=0;
        limitemaxi=30;
    }

    while(nombrechoisideporte>limitemaxi || nombrechoisideporte<limitemini)
    {
        clrscr();
        game_motion_esc_stable();
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("Inserez le nombre de portes que vous souhaiter avoir:");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("(Entre %d et %d)",limitemini,limitemaxi);
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        scanf("%d",&nombrechoisideporte);
        fflush(stdin);
    }
    printf("\n\n\t\t\t\t\t\t\t\t\t\t");
    printf("Le nombre de portes est maintenant %d!",nombrechoisideporte);
    sleep(1);
    return nombrechoisideporte;
}

int Choixdifficulte(void)
{   //fonction pour selectionner le choix de difficultees
    int difficulte=0;
    while(difficulte!=1 && difficulte!=2 && difficulte!=3)
    {
        clrscr();
        game_motion_esc_stable();
        printf("\n\t\t\t\t\t\t\t\t\t\t-----------------------------");
        printf("\n\t\t\t\t\t\t\t\t\t\t|Choisissez la difficultee: |");
        printf("\n\t\t\t\t\t\t\t\t\t\t-----------------------------");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("1.Facile");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("2.Moyen");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("3.Difficile");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("\n\t\t\t\t\t\t\t\t\t\t");
        printf("Choix: ");
        scanf("%d",&difficulte);
        fflush(stdin);
    }
    printf("\n\n\t\t\t\t\t\t\t\t\t\t");

    if(difficulte==1)
    {
        printf("Vous avez choisi Facile ! C'est un debut ...");
        difficultechoisie=1;
        return difficulte;
    }
    if(difficulte==2)
    {
        printf("Vous avez choisi Moyen ! Classique.");
        difficultechoisie=1;
        return difficulte;
    }
    if(difficulte==3)
    {
        printf("Vous avez choisi Difficile ! Vous etes fort vous !");
        difficultechoisie=1;
        return difficulte;
    }
    sleep(2);
    return 0;
}



int attentioncontact(int x,int y)       //fonction qui limite le deplacement de l'ennemi pour ne pas depasser les bordures, traverser les murs, prendre des bonus, et effacer la sortie
{
    if(Carte[x][y]=='|'||Carte[x][y]=='-'||Carte[x][y]=='+'||Carte[x][y]=='S'||Carte[x][y]=='X')
    {
        return 1;
    }
    else
    {
        return 0;
    }

}



float dist(int x1, int y1, int x2, int y2) //donne la distance (vol d'oiseau ou normale du vecteur entre les deux points)
{
    float  distance=sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return distance;
}


int Findeniveau(int posi1, int posi2,int lignesortie,int colsortie, int minutes, int secondes,int nombre_bonus_pris,int nombre_ennemies_pris,int nombre_ennemies_param) //regarde si le joueur est a la sortie
{
    if (posi1==lignesortie&&posi2==colsortie)
    {
        clrscr();
        game_motion_esc_stable();
        fin_de_partie();
        sleep(5);
        return 1;
    }
    else if (score_finale_joueur(minutes, secondes,nombre_bonus_pris,nombre_ennemies_pris,nombre_ennemies_param)<=0)
    {
        return 0;
    }
}

void Sortie(int posi1, int posi2, int limmin,int limmax,int*lignesortie,int*colsortie) // positionne la sortie
{
    int distance;
    srand(time(NULL));
    do
    {
        lignesortie[0] = rand()%ligne;
        colsortie[0] = rand()%colonne;
        distance=dist(posi1,posi2,lignesortie[0],colsortie[0]);
    } while (distance<limmin || distance>limmax || Carte[lignesortie[0]][colsortie[0]]!=' ');


    Carte[lignesortie[0]][colsortie[0]] = 'S';
}


void compteurdeptsbonus(int posi1, int posi2,int bonus[][2],int nombre_bonus_param)     //fonction qui compte le nombre de points bonus pris par le joueur
{
    if (verifsiestunbonus(bonus,nombre_bonus_param,posi1,posi2)==1)
    {
        nombre_bonus_pris+=1;
    }
}


void compteurdesennemies(int posi1, int posi2, int ennemi[][2],int nombre_ennemies_param)       //fonction qui compte le nombre d'ennemis que le joueur a rencontrer
{
    if (verifsiestunennemi(ennemi,nombre_ennemies_param,posi1,posi2)==1)
    {
        nombre_ennemies_pris+=1;
    }
}


int score_finale_joueur(int minutes, int secondes,int nombre_bonus_pris,int nombre_ennemies_pris,int nombre_ennemies_param)
{       //algorythme pour calculer le score finale en fonction du temps, nombre de bonus pris et nombre d'ennemis rencontrer
    int score_finale;
    int temps_finale_sec,temps_finale_min;
    int nombre_ennemies_param_init;
    if (compteur==1)
    {
        nombre_ennemies_param_init = nombre_ennemies_param;
    }
    nombre_ennemies_param=nombre_ennemies_param_init-nombre_ennemies_pris;
    temps_finale_min=minutes;
    temps_finale_sec=secondes;

    score_finale = 1001 +((nombre_bonus_pris*100)-((temps_finale_min*60)+temps_finale_sec)-(nombre_ennemies_pris*250));

    return score_finale;
}

void Timer(int *minutes, int *secondes) //temps depuis debut de partie
{
    static time_t debut = 0;
    time_t mtn;
    double tpspasse;

    if (debut == 0) {
        debut = time(NULL);
    }

    mtn = time(NULL);
    tpspasse = difftime(mtn, debut);

    *minutes = (int)(tpspasse / 60);
    *secondes = (int)(tpspasse - (*minutes * 60));
}




int verifsiestuneporte(int portequisouvre[][2], int nombrechoisideporte, int x, int y) //regarde si un mur peut etre une porte
{
    for (int i = 0; i < nombrechoisideporte; i++)
    {
        if (portequisouvre[i][0] == x && portequisouvre[i][1] == y)
        {
            return 1;
        }
    }
    return 0;
}

int verifportediff(int idx, int max_idx, int portequisouvre[][2]) //verfifie si la porte est differente des autres (pas de doublons)
{
    for (int i = 0; i < max_idx; i++) {
        if (portequisouvre[i][0] == portequisouvre[idx][0] && portequisouvre[i][1] == portequisouvre[idx][1]) {
            return 1;
        }
    }
    return 0;
}

void nombreporte(char mur, int *nombredeporte, int coordporte[][2]) //donne la pos de tous les murs pouvant etre une porte
{
    int compte = 0;
    for (int i = 1; i < ligne-1; i++) {
        for (int j = 1; j < colonne-2; j++) {
            if ((Carte[i][j] == mur))
            {
                coordporte[compte][0] = i;
                coordporte[compte][1] = j;
                compte++;
            }
        }
    }
    *nombredeporte = compte;
}

void Ouvreporte(int x,int y,int pas,int etatporte)  //ouvre/ferme les portes a chaque nombre de raffraichissement egal au pas
{
    if(etatporte==2)
    {
        if(Carte[x][y]!='@')
        {
            Carte[x][y]=' ';
        }

    }

    if(etatporte==1)
    {
        if(Carte[x][y]!='@')
        {
            Carte[x][y]='|';
        }

    }
}

int changeetat(int pas)//change d'etat (ouvert/ferme) a chaque nombre de raffraichissement egal au pas
{
    if ((compteur+1) % pas == 0)
    {
        if (etatporte == 1)
        {
            etatporte = 2;
        }
        else
        {
            etatporte = 1;
        }
    }

    return etatporte;

}





void laby1(void) // la carte
{
    char Laby1[35][70]= {
        {"+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-+"},
        {"|                 |     |        |                 |        |       |"},
        {"+  +--+--+--+--+  +  +  +--+--+  +--+--+--+  +--+  +  +--+  +  +    +"},
        {"|     |        |              |     |        |     |  |        |    |"},
        {"+--+  +  +--+  +--+--+--+  +  +--+  +  +  +--+--+  +  +--+--+--+    +"},
        {"|     |        |     |     |  |        |        |        |          |"},
        {"+  +--+  +--+  +  +  +--+  +  +--+--+--+--+  +  +  +--+  +--+--+-+  +"},
        {"|  |     |        |     |                    |  |     |     |       |"},
        {"+  +  +--+  +--+  +  +  +--+--+--+--+  +--+  +  +  +--+  +  +--+--+-+"},
        {"|     |        |  |     |        |        |     |        |          |"},
        {"+--+--+  +--+--+  +  +  +--+--+  +--+--+  +--+  +--+--+--+--+  +--+-+"},
        {"|                 |  |  |        |        |     |     |        |    |"},
        {"+  +--+--+--+  +  +  +--+  +--+  +  +--+  +  +--+  +  +--+--+  +  +-+"},
        {"|           |  |  |     |     |     |     |  |     |        |       |"},
        {"+--+--+  +  +--+  +--+  +  +  +  +--+  +--+--+--+  +--+--+  +--+--+-+"},
        {"|        |     |        |  |     |                 |  |             |"},
        {"+--+--+--+  +--+--+--+--+  +--+  +  +  +--+--+--+  +  +--+--+--+--+-+"},
        {"|        |                       |     |           |                |"},
        {"+--+  +--+--+--+--+  +--+--+--+--+--+--+--+--+--+  +  +--+--+--+--+-+"},
        {"|              |     |     |                    |  |  |        |    |"},
        {"+--+--+--+--+  +--+  +  +  +--+  +--+--+--+--+--+--+  +--+--+  +  +-+"},
        {"|           |           |        |              |                   |"},
        {"+--+  +  +--+  +--+--+--+--+--+--+--+--+--+--+  +  +--+--+--+--+--+-+"},
        {"|     |     |  |                             |  |  |           |    |"},
        {"+--+--+  +--+  +--+--+  +--+  +  +--+--+--+--+  +  +  +--+--+--+  +-+"},
        {"|     |                    |  |              |                      |"},
        {"+--+  +--+--+--+  +--+--+--+  +  +--+--+--+  +  +--+  +--+--+--+--+-+"},
        {"|                                         |                         |"},
        {"+--+--+--+--+  +--+--+--+--+--+--+--+--+--+--+--+  +--+--+--+--+--+-+"},
        {"|                          |                                        |"},
        {"+--+--+--+--+  +--+  +--+  +--+--+--+--+--+--+--+--+--+--+--+  +--+-+"},
        {"|     |              |              |           |     |             |"},
        {"+--+  +  +--+--+--+--+--+--+--+--+  +--+--+  +  +--+  +--+--+--+--+-+"},
        {"|                                            |                      |"},
        {"+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+-+"}
    };

    for (int x=0;x<ligne;x++)
    {
        for(int y=0;y<colonne;y++)
        {
            Carte[x][y]=Laby1[x][y];
        }
    }
}



void coul_Joueur(int x,int y) // change la couleur du joueur et de la sortie
{
    if(Carte[x][y]=='@')
    {
        printf("\033[32m");
    }
    if(Carte[x][y]=='S')
    {
        printf("\033[34m");
    }

}

void coul_Objet(int x,int y) //change couleur objet
{
    if(Carte[x][y]=='|')
    {
        printf("\033[31m");
    }
    if(Carte[x][y]=='@')
    {
        printf("\033[32m");
    }
    if(Carte[x][y]=='B')
    {
        printf("\033[35m");
    }
    if(Carte[x][y]=='X')
    {
        printf("\033[36m");
    }
}

void coul_Normale(void)//revient a la couleur de base
{
    printf("\033[0m");
}




int attente(int minutes,int secondes,int portequisouvre[][2],int nombrechoisideporte,int bonus[][2],int nombre_bonus_param,int nombre_ennemies_param,int ennemi[][2])
{ //attend un mouvement du joueur ou si temps depasse le temps de raffraichissement
        int temps_passe = 0;
        int attente = 600;
        int input;

        while (temps_passe<attente)
        {
            Sleep(10);
            temps_passe+=10;
            if (kbhit())
            {
                temps_passe=0;
                input = getch();
                fflush(stdin);
                return input;
            }
        }

        if (temps_passe>=600)
        {
            temps_passe=0;

            clrscr();

            afficheCarte(minutes,secondes,portequisouvre,nombrechoisideporte,bonus,nombre_bonus_param,nombre_ennemies_param,ennemi);
        }
        return 0;
}



void afficheCarte(int minutes,int secondes,int portequisouvre[][2],int nombrechoisideporte,int bonus[][2],int nombre_bonus_param,int nombre_ennemies_param,int ennemi[][2])
{

    for (int x=0;x<ligne;x++)               //affichage de la carte bordure
    {
        for(int y=0;y<colonne;y++)
        {
            if(verifsiestuneporte(portequisouvre,nombrechoisideporte,x,y)==1)
            {
                coul_Objet(x,y);
                printf("%c",Carte[x][y]);
                coul_Normale();
            }
            else if(verifsiestunbonus(bonus,nombre_bonus_param,x,y)==1)
            {
                coul_Objet(x,y);
                printf("%c",Carte[x][y]);
                coul_Normale();
            }
            else if(verifsiestunennemi(ennemi,nombre_ennemies_param,x,y)==1)
            {
                coul_Objet(x,y);
                printf("%c",Carte[x][y]);
                coul_Normale();
            }
            else
            {
                coul_Joueur(x,y);
                printf("%c",Carte[x][y]);
                coul_Normale();
            }

        }
        printf("\n");
    }

    printf("\n %d : %d\t---Score: %d", minutes,secondes,score_finale_joueur(minutes,secondes,nombre_bonus_pris,nombre_ennemies_pris,nombre_ennemies_param));

}




void clrscr() //efface tout
{
    system("@cls||clear");
}

void full_screen()  //nous permet de jouer le jeu en plein ecran pour plus de satisfaction
{
    HWND console = GetConsoleWindow();
    SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_OVERLAPPEDWINDOW);
    ShowWindow(console, SW_MAXIMIZE);
}




int score_saver(int minutes, int secondes,int nombre_ennemies_param) //enregistre le score du joueur et son nom dans un fichier txt
{
    int score_player = score_finale_joueur(minutes,secondes,nombre_bonus_pris,nombre_ennemies_pris,nombre_ennemies_param);
    //cree un fichier dans Documents pour sauvegarder les scores
    char *homedir = getenv("HOME"); // Pour avoir le chemin d'access du fichier HOME
    char *dirpath = malloc(strlen(homedir) + strlen("/Documents/new_folder") + 1); // Allocation d'espace pour le noveau fichier
    sprintf(dirpath, "%s/Documents/E_S_C", homedir); // Construit le chemin pour le nouveau fichier
    mkdir(dirpath, 0777); // Cree le nouveau fichier avec toute les permissons d'administrateur
    char *filename = malloc(strlen(dirpath) + strlen("/Score.txt") + 1); // Cree un espace pour le nouveau fichier
    sprintf(filename, "%s/Score.txt", dirpath); // Construit le chemin pour le fichier

    FILE *file;

    file = fopen(filename, "a");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return 1;
    }

    fprintf(file, "%s\t\t\t%d\n",nom_joueur,score_player);
    fclose(file);
    free(dirpath); // Free the memory we allocated for the directory path
    free(filename); // Free the memory we allocated for the file path
}

void echange(int *a, int *b)        //fonction pour faciliter le trie des scores
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int score_triage()      //fonction qui va trier tout les scores enregistrer au cours du temps
{
    int num_scores = 0;

    FILE *fp;

    fp = fopen("Score.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file\n");
        return 1;}

    while (fscanf(fp, "%s %d", names[num_scores], &scores[num_scores]) != EOF) {
        // read a name and score from the file
        num_scores++;
        if (num_scores >= MAX_SCORES) {
            break; // array is full
        }
    }

    fclose(fp);
    int reserve1=0;
    for (int j=0;j<num_scores;j++)
    {
        for (int k=0;k<num_scores;k++)
        {
            if (scores[k]<scores[k+1])
            {
                echange(&scores[k], &scores[k + 1]);
                char temp[MAX_NAME_LENGTH];
                strcpy(temp, names[k]);
                strcpy(names[k], names[k + 1]);
                strcpy(names[k + 1], temp);
            }
        }
    }
    // print the names and scores
    score_display();
    printf("\n\t\t\t\t\t\t\t\t\t\t-----------------------------------------------------");

    for (int i = 0; i < num_scores; i++) {

            if (strlen(names[i])<=6)
            {
                printf("\n\t\t\t\t\t\t\t\t\t\t\t%s:\t\t\t\t%d", names[i], scores[i]);
            }
            else if (strlen(names[i])>6 && strlen(names[i])<12)
            {
                printf("\n\t\t\t\t\t\t\t\t\t\t\t%s:\t\t\t%d", names[i], scores[i]);
            }
            else
            {
                printf("\n\t\t\t\t\t\t\t\t\t\t\t%s:\t\t%d", names[i], scores[i]);
            }

    }
    printf("\n\t\t\t\t\t\t\t\t\t\t-----------------------------------------------------");

}




void Menu()
{
    clrscr();
    full_screen();
    game_motion_esc();
    menu_display();
    int choix_menu;

    int difficulte;  //La difficulte choisie

    int nombrechoisideporte=-1;     // le nombre de mur qui "s'ouvre"
    int nombre_ennemies_param=-1;
    int nombre_bonus_param=-1;
    do
    {
        choix_menu = getch();

        if (choix_menu == 49)
            {
                while(difficultechoisie!=1)
                {
                    difficulte=Choixdifficulte();
                }
                while(nombrechoisideporte==-1||nombre_ennemies_param==-1||nombre_bonus_param==-1)
                {
                    Parametres(&nombrechoisideporte,&nombre_ennemies_param,&nombre_bonus_param,difficulte);
                }
                clrscr();
                game_motion_esc_stable();
                printf("\n\n\n\n\t\t\t\t\t\t\t\t\t\tInserez votre nom: ");
                scanf("%s",&nom_joueur);
                fflush(stdin);
                printf("\n\n\t\t\t\t\t\t\t\t\t\tVous avez choisi %s",nom_joueur);
                deplacement_joueur(nombrechoisideporte,nombre_bonus_param,nombre_ennemies_param);
                clrscr();
                game_motion_esc_stable();       //Settings
                menu_display();

            }
        else if (choix_menu == 53)
            {
                signature_chris_william();
                break;
            }
        else if (choix_menu == 50)
            {
                if(difficultechoisie!=1)
                {
                    difficulte=Choixdifficulte();
                }

                Parametres(&nombrechoisideporte,&nombre_ennemies_param,&nombre_bonus_param,difficulte);
                clrscr();
                game_motion_esc_stable();
                menu_display();
            }

        else if (choix_menu == 51)
            {
                int exit_scoreboard=1;
                do
                    {

                        clrscr();
                        game_motion_esc_stable();
                        score_triage();//ouvrire fichier score et afficher tout les scores sauvegarder
                        exit_scoreboard = getch();

                    }while(exit_scoreboard==1);
                    clrscr();
                    game_motion_esc_stable();
                    menu_display();


            }
        else if (choix_menu == 52)
            {
                //Tutorial non dispo
            }

    }while(choix_menu !=49 || choix_menu !=50 || choix_menu !=51 || choix_menu !=52 || choix_menu !=53);

}
