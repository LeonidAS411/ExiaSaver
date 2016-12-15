#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{

		int alea = 0;

	/*-------------------CREATION VARIABLE RANDOM-----------------------*/

		srand(time(NULL));	//mettre à 0 srand
		alea = rand() %3+1;	//donner a la variable alea une valeur aléatoire entre 0 et 2
		printf("Varriable aléatoire : %d\n", alea);


	/*-------------------CREATION VARIABLE DATE / HEURE-----------------------*/

		/* lire l'heure courante */
	  	time_t now = time (NULL);

	   	/* la convertir en heure locale */
	   	struct tm tm_now = *localtime (&now);

	   	/* Creer une chaine JJ/MM/AAAA HH:MM:SS */
	   	char s_now[sizeof "AAAA/MM/JJ HH:MM:SS"];
	   	strftime (s_now, sizeof s_now, "%Y/%m/%d %H:%M:%S", &tm_now);


	/*-------------------CREATION POINTEUR VERS HISTORIQUE-----------------------*/

		FILE* historique = NULL;
	        historique = fopen("historique.txt", "r+");

	/*--------------------------------------------------------STATIQUE---------------------------------------------------*/

		if(alea == 1)
		 {
			printf("Lancement du termSaver Statique\n\n");


	   		if (historique != NULL)		//Si le fichier existe on fait :
	    		 {

			        fseek(historique, 0, SEEK_END);		//Placer pointeur a la fin du texte
	   					fprintf (historique, "%s;1; ", s_now);	//Archiver dans historique
							fclose(historique);
	    		 }
	   		else
	    	  {
	      		  	// On affiche un message d'erreur, sinon risque de plantage
	       		 	printf("Impossible d'ouvrir le fichier historique.txt");
	   		  }
		  }

	/*--------------------------------------------------------DYNAMIQUE---------------------------------------------------*/

		else if(alea == 2)
		  {
			printf("Lancement du termSaver Dynamique\n\n");

			if (historique != NULL)		//Si le fichier existe on fait :
	    		 {

			        fseek(historique, 0, SEEK_END);		//Placer pointeur a la fin du texte
	   					fprintf (historique, "%s;2; 5x3\n", s_now);	//Archiver dans historique
							fclose(historique);
	    		 }
	   		else
	    	  {
	      		  	// On affiche un message d'erreur, sinon risque de plantage
	       		 	printf("Impossible d'ouvrir le fichier historique.txt");
	   		  }
		  }

	/*--------------------------------------------------------INTERACTIF---------------------------------------------------*/

		else if(alea == 3)
		  {
			printf("Lancement du termSaver Interactif\n\n"
							"En cours de réalisation ...\n");

			if (historique != NULL)		//Si le fichier existe on fait :
	    		 {

			        fseek(historique, 0, SEEK_END);		//Placer pointeur a la fin du texte
	   					fprintf (historique, "%s;3; X,Y\n", s_now);	//Archiver dans historique
							fclose(historique);
	    		 }
	   		else
	    		{
	      		  	// On affiche un message d'erreur, sinon risque de plantage
	       		 	printf("Impossible d'ouvrir le fichier historique.txt");
	   		  }
		  }
/*----------------------------LANCEMENT-----------------------------*/

	//LANCER LE TERMSAVER SELECTIONNE
	if(alea == 1)
		{
			sleep(3);			//temps pour que l'utilisateur lise le terminale

			char * argv[] = {"PBM/lecteurPBM.c", "fichier.c", NULL};
			/* dernier élément NULL, obligatoire */
			execl("lecteurPBM","lecteurPBM", NULL);
		}
	else if(alea == 2)
		{
			sleep(3);			//temps pour que l'utilisateur lise le terminale

			char * argv[] = {"horloge.c", "fichier.c", NULL};
			/* dernier élément NULL, obligatoire */
			execl("horloge","horloge", NULL);
		}
		else if(alea == 3)
			{
			}
}
