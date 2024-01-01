#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "machineabstraite.h"
#include <string.h>


int main()
{

    LO_VC *t = ouvrir("test_sfsd",'N');

    creationLO_VC(t,10);

    printf("\n********Affichage des blocs********* \n");
    afficherLO_VC(t);

    printf("\n");




    char *ma_cle;
    bool cle_trouvee;
    int i,pos;
    ma_cle= (char*)malloc(sizeof(char)*(5));


  printf("veullez entrer la cle vous souhaitez supprimer   ");
    scanf("%s",ma_cle);
    suppressionLO_VC(t,ma_cle);

        printf("\n");
    printf("\n********Affichage des blocs********* \n");
    afficherLO_VC(t);


   /* if (ma_cle == NULL) {
        fprintf(stderr, "Allocation de memoire impossible \n");
        return 1;
    }
    else{  printf("\n********Recherche d'une cl%c********* \n",130);
           printf("\n* Veuillez entrer une cle entre (0-9999) : ");
           scanf("%s",ma_cle);
           printf("* La cle choisie est : %s\n",ma_cle);
           rechercheLO_VC(t,ma_cle,&cle_trouvee,&i,&pos);
        }
    printf("\n********Emplacement libre********* \n");
    printf("\n Le dernier bloc : %d , La derniere position libre : %d \n ",entete(t,2),entete(t,3));

*/


 /*
    char *nouv_cle;
    nouv_cle = (char*)malloc(sizeof(char)*(5));
    if (nouv_cle == NULL) {
        fprintf(stderr, "Allocation de memoire impossible \n");
        return 1;
    }
    else{  printf("\n* Veuillez entrer la cle entre (0-9999) que vous souhaitez inserer : ");
            scanf("%s",nouv_cle);
           printf("* La cle choisie est : %s\n",nouv_cle);
            insertionLO_VC(t,nouv_cle);
           printf("\n");
            afficherLO_VC(t);
           printf("\n");
        }

 */

  fermer(t);
    return 0;
}
