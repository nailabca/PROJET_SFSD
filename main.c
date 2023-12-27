#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "machineabstraite.h"
#include <string.h>


int main()
{

    LO_VC *t = ouvrir("test_sfsd",'N');

    creationLO_VC(t,10);

    afficherLO_VC(t);



    printf("\n");

    char *ma_cle;
    bool cle_trouvee;
    int i,pos;
    ma_cle= (char*)malloc(sizeof(char)*(5));
    if (ma_cle == NULL) {
        fprintf(stderr, "Allocation de memoire impossible \n");
        return 1;
    }
    else{ printf("\nVeuillez entrer une cle <=4 : ");
           scanf("%s",ma_cle);
           printf("La cle choisie est : %s\n",ma_cle);
           rechercheLO_VC(t,ma_cle,&cle_trouvee,&i,&pos);
        }


  fermer(t);
    return 0;
}
