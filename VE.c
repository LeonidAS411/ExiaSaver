#include<stdio.h>
#include<stdlib.h>

int main()
{
  /*-------------CREATION DES VARIABLES D'ENVIRONNEMENT--------------*/
  putenv("EXIASAVER_HOME=/home/loic211198/Documents/EXIASAVER_HOME");
  putenv("EXIASAVER1_PBM=/home/loic211198/Documents/PBM");
  putenv("EXIASAVER2_PBM=/home/loic211198/Documents/PBM/chiffres");
  putenv("EXIASAVER2_TAILLE=5x3");
  putenv("EXIASAVER2_SLEEP=10");
  putenv("EXIASAVER3_PBM=/home/loic211198/Documents/PBM");

  return 0;
}
