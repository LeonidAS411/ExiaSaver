#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ncurses.h>
#define TAILLE_MAX 1000

int main(int argc, char *argv[])
{

/*-------------------------LANCEUR ALEATOIRE-------------------------------*/

  int alea;

  int nLigne = 0;
  int x, y;
  char formatP[2];
  char lettre;

  int hauteur = (23-y)/2;   // calcul de la hauteur centree
  int largeur = (80-x)/2;    // calcul de la largeur centree
  int i;

  int ctrlc=0;

  int charcompteur=0;


    srand(time(NULL));	     //mettre a 0 srand
    alea = rand() %5+1;	     //alea = variable aleatoire entre 1 et 5

    FILE* fichier = NULL;    //pointer le fichier
    char chaine[TAILLE_MAX] = "";   //creation chaine de characteres

      /*OUVRE UN DES FICHIER*/
      int PBM = alea;

      fopen(getenv("EXIASAVER_PBM")); //ouvrir le fichier VE

      switch(PBM)     //ouvrir une image PBM selon alea
      {
        case 1:
          fichier = fopen("cadenas.pbm", "r");
          break;

        case 2:
          fichier = fopen("fusee.pbm", "r");
          break;

        case 3:
          fichier = fopen("main.pbm", "r");
          break;

        case 4:
          fichier = fopen("temps.pbm", "r");
          break;

        case 5:
          fichier = fopen("panda.pbm", "r");
          break;
      }

/*------------------------ECRIRE DANS L'HISTORIQUE------------------------*/

FILE* historique = NULL;
      historique = fopen("historique.txt", "r+");
if (historique != NULL)		//Si le fichier existe on fait :
       {

          fseek(historique, 0, SEEK_END);		//Placer pointeur a la fin du texte

          switch(alea)
          {
            case 1:
              fprintf (historique, "cadenas.pbm\n");	      //Archiver dans historique
              break;

            case 2:
              fprintf (historique, "fusee.pbm\n");	      //Archiver dans historique
              break;

            case 3:
              fprintf (historique, "main.pbm\n");	      //Archiver dans historique
              break;

            case 4:
              fprintf (historique, "temps.pbm\n");	      //Archiver dans historique
              break;

            case 5:
              fprintf (historique, "panda.pbm\n");	      //Archiver dans historique
              break;
          }

          fclose(historique);
       }
    else
      {
            // On affiche un message d'erreur, sinon risque de plantage
          printf("Impossible d'ouvrir le fichier historique.txt");
      }

/*-------------------------MODULE DE LECTURE PBM--------------------------*/

    if (fichier != NULL)  //si le fichier existe faire
    {
        system("clear");

        /*lire et afficher les dimensions du PBM*/
        fseek(fichier, 0, SEEK_SET);    //se placer au premier caractere
        fscanf(fichier, "%c%c",&formatP[0], &formatP[1]); //scanner le format

          if(formatP[0] != 'P' && formatP[1] != '1')              //si le format n'est pas P1, quitter
            {
              printf("Votre image n'est pas du bon format.\n");
              return 0;
            }

        /*lire et afficher les dimensions du PBM*/
        fseek(fichier, 3, SEEK_SET);    //se placer a la 2e ligne
        fscanf(fichier, "%d %d",&x,&y); //scanner les 2 nombres
        printf("%c", fgetc(fichier));


        do          //faire : tant que on a pas atteint la fin du fichier
          {

          int i=0;

          lettre = fgetc(fichier); // lettre accède à la x ème ligne

          switch(lettre)
            {
                case ' ':         //si le caractere = espace, ne rien afficher
                    lettre = '\0';
                    break;

                case '0':         //si le caractere = 0, afficher espace
                    lettre = ' ';
                    charcompteur++;
                    break;

                case '1':         //si le caractere = 1, afficher X
                    lettre = '0';
                    charcompteur++;
                    break;
             }
            printf("%c", lettre);

            } while ((lettre) != EOF); // EOF: caractère de fin du fichier

          fclose(fichier); // On ferme le fichier qui a été ouvert
    }

    else
    {
        printf("Impossible d'ouvrir le fichier.");
    }
    /*-------------------------------PROCESSUS----------------------------------------*/

    	pid_t numero_fils;				//processus ID
    	int compteur;

    	numero_fils = fork();			//creation du processus fils


    	/*--------------------EN CAS D'ERREUR EAGAIN--------------------*/

    	while ((numero_fils == -1) && (errno == EAGAIN))
    	  {
    			/*attendre qq instants, ressayer d'obtenir un processus fils*/
    			numero_fils = fork();
    	  }

    	/*--------------------EN CAS D'ERREUR ENOMEN--------------------*/

    	if (numero_fils == -1)
    	   {
    			/*stderr = Sortie standard des erreurs*/
    			fprintf (stderr, "fork a echoue, erreur(errno) numero %d\n", errno);

    			return 1;
    	   }

    	/*--------------------DANS LE PROCESSUS FILS--------------------*/

    	if (numero_fils == 0)
    	{

        /*---------QUITTER le PRGM----------*/

          char exit;
          initscr();        //activer mode Ncurses et clear terminale
          cbreak();         //desactiver "enter" pour entrer une touche
          noecho();         //masquer affichage touches entrees sur shell
          exit = getchar(); //exit enregistre la touche appuyee sur clavier

          while(exit == 'c')    //tant que l'utilisateur ne touche pas au clavier: DAFUQQ AVEC \0 il prend pas mais le if en dessous LE PREND !!!!
          {
            //printf("Boucle 'c'\n");

            if (exit != '\0')   // '/0' = vide
             {
                //printf("Boucle '/0'\n");
                sleep(1);
                system("clear");
                echo();       //activer affichage touches entrees sur shell
                nocbreak();   //activer "enter" pour entrer une touche
                endwin();     //quitter mode Ncurses & liberer les emplacements memoire
                return 0;
              }
          }


    	}

    	/*--------------------DANS LE PROCESSUS PERE--------------------*/

    	else
    	   {
    		wait(NULL);	//attendre la fin du processus fils
    		printf("Bon travail fils, \nDepuis ton pere.\n");
    		sleep(1);
    	   }

    return 0;

}
