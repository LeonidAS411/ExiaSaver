#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define TAILLE_HISTORIQUE 20

int main(int argc, char * argv[])
{
    FILE *historique = NULL;

    char caractere = 0;

    historique = fopen("htc.txt", "r");

    int tab[7][10];

    char nom[50];

    int i;
    int compteurMode[3] = {0};
    int compteurImage[5] = {0};
    int choix = 0;




    /**
        OUVERTURE ET LECTURE DU FICHIER
    */

    /// SI ON ARRIVE A OUVRIR LE FICHIER
    if (historique != NULL)
    {
        for (i = 0; i < 10; i++)
        {
            fscanf(historique, "%d/%d/%d %d:%d:%d;%d; %s", &tab[0][i], &tab[1][i], &tab[2][i], &tab[3][i], &tab[4][i], &tab[5][i], &tab[6][i], &nom);
            //printf("%d\n", tab[6][i]);
            printf("%s\n", nom);


            printf("Bienvenue dans le menu statistique\n\nQuelle statistique voulez vous observer ? \n\n 1. Les types lances par ExiaSaver\n 2. Les images.pbm lancees par le type statique\n");
            scanf("%d", &choix);

            switch (choix)
            {
                /**
                    STATISTIQUES 1
                    INDIQUE LE NOMBRE D'AFFICHAGE POUR CHAQUE MODE
                */
                case 1:
                    for(i=0;i<5; i++)
                    {
                        if (tab[6][i] == 1)
                            compteurMode[0]++;
                        else if (tab[6][i] == 2)
                            compteurMode[1]++;
                        else if (tab[6][i] == 3)
                            compteurMode[2]++;
                    }
                    printf("Type statique : %d\nType dynamique : %d\nType intéractif : %d\n", compteurMode[0], compteurMode[1], compteurMode[2]);
                break;



                /**
                    STATISTIQUES 2
                    INDIQUE LE NOMBRE D'AFFICHAGE POUR CHAQUE IMAGE
                */

                case 2:
                    if (strcmp(nom, "fusee.pbm") == 0)
                    {
                        compteurImage[0]++;
                    }

                    else if (strcmp(nom, "panda.pbm") == 0)
                    {
                        compteurImage[1]++;
                    }

                    else if (strcmp(nom, "temps.pbm") == 0)
                    {
                        compteurImage[2]++;
                    }

                    else if (strcmp(nom, "main.pbm") == 0)
                    {
                        compteurImage[3]++;
                    }

                    else if (strcmp(nom, "cadenas.pbm") == 0)
                    {
                        compteurImage[4]++;
                    }

                    printf("Image de la fusee : %d\nImage du panda : %d\nImage du sablier : %d\nImage de la main : %d\nImage du cadenas : %d\n", compteurImage[0], compteurImage[1], compteurImage[2], compteurImage[3], compteurImage[4]);

                break;

            }
        }
    }

    /// SINON
    else
    {
        printf("Impossible d'ouvrir le fichier");
    }




//system("clear");


    fclose(historique);
    return 0;
}
