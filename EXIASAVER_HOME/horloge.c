#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#define gotoxy(x,y) printf("\033[%d;%dH", (x), (y))
#define TAILLE_MAX 80

/*-------------------FONCTION D'AFFICHAGE DE L'HORLOGE---------------------*/

int Horloge()
{
	/*variables logistique*/
	int PBM = 0;

	int y=12, x=6;			//variables des coordonnees
	int i = 0, j = 0;  		// variables pour les boucles
	char chaine[TAILLE_MAX];
	int Px, Py;
	char formatP[2];			//format PBM ex:P1

	/*variables pour le temps*/
	time_t secondes;
	time(&secondes);

	struct tm instant;
	instant=*localtime(&secondes);
	/*declaration de chaque unité de l'heure a partir de la lib time.h*/
	int sec1 = (instant.tm_sec)/10;
	int sec2 = (instant.tm_sec)-(sec1*10);
	int min1 = (instant.tm_min)/10;
	int min2 = (instant.tm_min)-(min1*10);
	int heu1 = (instant.tm_hour)/10;
	int heu2 = (instant.tm_hour)-(heu1*10);
	int Time[8] = {heu1, heu2, 15, min1, min2, 15, sec1, sec2};
	//15 = double point


	FILE* fichier = NULL; //initialisation du pointeur a NULL

	fopen(getenv("EXIASAVER2_PBM")) //ouvrir le fichier VE

	for (PBM=0; PBM<8; PBM++)			//ouvrir tout les chiffres PBM
	{
		switch(Time[PBM])						//ouverture chiffre selon l'heure actuelle
		{
			case 0:
				fichier = fopen("0.pbm", "r");
				break;

			case 1:

				fichier = fopen("1.pbm", "r");
				break;

			case 2:
				fichier = fopen("2.pbm", "r");
				break;

			case 3:
				fichier = fopen("3.pbm", "r");
				break;

			case 4:
				fichier = fopen("4.pbm", "r");
				break;

			case 5:
				fichier = fopen("5.pbm", "r");
				break;

			case 6:
				fichier = fopen("6.pbm", "r");
				break;

			case 7:
				fichier = fopen("7.pbm", "r");
				break;

			case 8:
				fichier = fopen("8.pbm", "r");
				break;

			case 9:
				fichier = fopen("9.pbm", "r");
				break;

			case 15:
				fichier = fopen("doublepoint.pbm", "r");
				break;
		}

		if (fichier != NULL)  //si le fichier existe faire
     {
         /*lire et afficher les dimensions du PBM*/
         fseek(fichier, 0, SEEK_SET);    //se placer au premier caractere
         fscanf(fichier, "%c%c",&formatP[0], &formatP[1]); //scanner le format

           if(formatP[0] != 'P' && formatP[1] != '1')   //quit si format non P1
             {
               printf("Votre image n'est pas du bon format.\n");
               return 0;
             }

         /*lire et afficher les dimensions du PBM*/
         fseek(fichier, 3, SEEK_SET);    //se placer a la 2e ligne
         fscanf(fichier, "%d %d",&Px,&Py); //scanner les 2 nombres
         Px = (Px*2)-1;
				 Py=Py+1;

				 for(i=0; i<Py; i++) // boucle qui va parcourir les lignes
					{
						gotoxy(x,y);
						fgets(chaine, TAILLE_MAX, fichier); //charger ligne dans tab chaine
						for(j=0;j<Px;j++) // boucle qui parcourt la ligne
				    		{
						      gotoxy(x,y);
				      		if (chaine[j] == '0')
										{
				          		chaine[j] = ' '; // changement des 0 en espace
										}
				      		else if (chaine[j] == '1')
										{
				          		chaine[j] = 'X'; // changement des 1 en X
										}
				   		  }

						x=x+1;
				    printf("%s", chaine); // affichage de la ligne modifié

					 }
			fclose(fichier); // fermeture du fichier
    	}
		x=x-6;
		y=y+7;
	}
}

/*------------------------BOUCLE DU REFRESH------------------------*/

int main()
{

	int RefreshT = getenv("EXIASAVER2_SLEEP");				//variable de tps de refresh en secondes
	int infini = 0;
	int i;
	int x1 = 20,y1 = 15, x2 = 3, y2 = 25;		//coordonnees pour gotoxy

	system("clear");

	/*PHRASE D'ACTUALISATION*/
	while (infini != 1)
	{
		int x = 20;
		int y = 62;
		gotoxy(x2,y2);				//coordonnees de l'horloge
		Horloge();						//afficher l'horloge
		gotoxy(x1,y1);				//coordonnees de la phrase :
		printf("Cet ecran sera actualise dans quelques secondes \n");

		/*Afficher les points chaque seconde*/
		for (i=0; i<RefreshT; i++)
		{
			sleep(1);				//delai de 1 seconde
			gotoxy(x,y);		//coodronnees du point
			printf(".\n");
			y++;						//decaler le point d'une case de charactere
		}

		/*cacher les points avec une barre de "char(s)" vide*/
		y=y-RefreshT;
		gotoxy(x,y);
		printf("                            ");

	}

	return 0;
}
