#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "machineabstraite.h"
#include <string.h>


int main()
{
   //Ouverture du fichier LO_VC :
    LO_VC *t = ouvrir("test_sfsd",'N');

   //Cr�ation du fichier LO_VC :
    creationLO_VC(t,10);

   //Affichage des blocs du fichier LO_VC :
    printf("\n********Affichage des blocs********* \n");
    afficherLO_VC(t);
    printf("\n");

   //Recherche d'une cl� :
    char *ma_cle;
    bool cle_trouvee;
    int i,pos;
    ma_cle= (char*)malloc(sizeof(char)*(5));
    if (ma_cle == NULL) {
        fprintf(stderr, "Allocation de memoire impossible \n");
        return 1;
    }
    else{  printf("\n********Recherche d'une cl%c********* \n",130);
           printf("\n* Veuillez entrer une cle entre (0-9999) : ");
           scanf("%s",ma_cle);
           printf("* La cle choisie est : %s\n",ma_cle);
           rechercheLO_VC(t,ma_cle,&cle_trouvee,&i,&pos);
        }
    printf("\n\n********Emplacement libre********* \n");
    printf("\n Le dernier bloc : %d , La derniere position libre : %d \n ",entete(t,2),entete(t,3));


   //Insertion d'une cl� :
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

   //Suppression d'une cl� :
    char *cle_supprime;
    cle_supprime = (char*)malloc(sizeof(char)*(5));
    if (nouv_cle == NULL) {
        fprintf(stderr, "Allocation de memoire impossible \n");
        return 1;
    }
    else{  printf("\n* Veuillez entrer la cle entre (0-9999) que vous souhaitez supprimer : ");
            scanf("%s",cle_supprime);
           printf("* La cle choisie est : %s\n",cle_supprime);
            suppressionLO_VC(t,cle_supprime);
           printf("\n");
            afficherLO_VC(t);
           printf("\n");
        }


 //Fermeture du fichier LO_VC :
  fermer(t);

    return 0;
}
