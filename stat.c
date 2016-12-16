#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define TAILLE_HISTORIQUE 20

void historique() //creation de la fonction historique
{
    FILE *historique = NULL; //on met on pointeur sur le fichier historique
    historique = fopen("historique.txt", "r"); //ouverture du fichier historique

    int tab[10][7]; // Variable contenant la chaine lu

    int j,k,l; //Variable pour l'algo de tri
    int tri=0;

    char nom[50]; // Variable contenant le nom de l'image

    int compteurMode[3] = {0}; // Variable contenant le compteur de chaque mode
    int compteurImage[5] = {0}; // Variable contenant le compteur de chaque image
    int choix = 0, i = 0; //Variable contenant le choix de la statistique lu par l'utilisateur


    /// SI ON ARRIVE A OUVRIR LE FICHIER
    if (historique != NULL)
    {


	system("clear"); //la console se vide

	printf("Bienvenue dans le menu statistique\n\nQuelle statistique voulez vous observer ? \n\n 1. Les types lances par ExiaSaver\n 2. Les images.pbm lancees par le type statique\n"); //Menu des statistiques
        scanf("%d", &choix); //L'utilisateur rentre un chiffre qui correspond à une statistique

        switch(choix)
        {
            case 1: //si l'utilisateur a rentré "1"
                for (i = 0; i < 10; i++) //parcours du fichier historique
                {
                    fscanf(historique, "%d/%d/%d %d:%d:%d;%d; %s", &tab[i][0], &tab[i][1], &tab[i][2], &tab[i][3], &tab[i][4], &tab[i][5], &tab[i][6], &nom); //scan des valeurs du fichier historique

                    if (tab[i][6] == 1) //Type statique
                        compteurMode[0]++;
                    else if (tab[i][6] == 2) //Type dynamique
                        compteurMode[1]++;
                    else if (tab[i][6] == 3) //Type intéractif
                        compteurMode[2]++;
                }
                printf("Type statique : %d\nType dynamique : %d\nType interactif : %d\n", compteurMode[0], compteurMode[1], compteurMode[2]); //Affichage du nombre de lancement de chaque types
            break;

            case 2: //si l'utilisateuur tape "2"
                for (i = 0; i < 10; i++)//parcours de l'historique
                {
                    fscanf(historique, "%d/%d/%d %d:%d:%d;%d; %s", &tab[i][0], &tab[i][1], &tab[i][2], &tab[i][3], &tab[i][4], &tab[i][5], &tab[i][6], &nom); //scan des valeurs du fichier historique

                    if (strcmp(nom, "fusee.pbm") == 0) //compare pour trouver le nom du fichier
                    {
                        compteurImage[0]++;
                    }

                    else if (strcmp(nom, "panda.pbm") == 0) //......
                    {
                        compteurImage[1]++;
                    }

                    else if (strcmp(nom, "temps.pbm") == 0)//......
                    {
                        compteurImage[2]++;
                    }

                    else if (strcmp(nom, "main.pbm") == 0)//......
                    {
                        compteurImage[3]++;
                    }

                    else if (strcmp(nom, "cadenas.pbm") == 0) //......
                    {
                        compteurImage[4]++;
                    }
                }
                printf("fusee : %d\npanda : %d\ntemps : %d\nmain : %d\ncadenas : %d\n", compteurImage[0], compteurImage[1], compteurImage[2], compteurImage[3], compteurImage[4]); //affichage final du menu 2
            break;

        }

    /*case3:

       // while (tri==0)
        {
            int i = 0;
            tri = 1;
  	    if(tab[i][6] l< tab[i+1][6])
            {
                int tampon=0;

                tampon = tab[i][6];

                tab[i][6]] = tab[i+1][6];

                tab[i+1][6] = tampon;

                tri = 0;
            }
        }
        for (k=0;k<10;k++){
		for (l=0;l<7;l++){
			printf("%d",tab[k][l]);
		}
		printf("/n");
	} */


    fclose(historique);

    }

 /// SINON
    else
    {
        printf("Impossible d'ouvrir le fichier");
    }

}


int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "-stats") == 0)
    {
        historique();
    }
    else
    {
	printf("Utilisez -stats pour lancer le mode statistique\n");
    }
    return 0;
}


