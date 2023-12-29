<<<<<<< HEAD
#ifndef machineabstraite_h_included
#define machineabstraite_h_included

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//structure du bloc d'un fichier LO_VC
typedef struct Bloc {
  char Tab[10];
  int svt;
}Bloc;

//buffer à utiliser pour manipuler la MC et la MS
Bloc Buffer;

//structure de l'entete du fichier LO_VC
typedef struct Entete{
int prem_Bloc;
int der_Bloc;
int pos_libre;
int nbcar_ins;
int nbcar_supp;
}Entete;

//structure d'un fichier LO_VC
typedef struct LO_VC{
FILE* f;
Entete entete_f;
}LO_VC;

//structure d'un enregistrement dans un bloc de fichier LO_VC
typedef struct enregistrement
{   int cle;
    int car_spe1;
    int efface;
    char car_spe2;
    char nom;
}enreg;

//machine abstraite LO_VC
LO_VC* ouvrir(char nomfichier[20],char mode);
void fermer (LO_VC *t);
void lireMS(LO_VC *t ,int i,Bloc *buf);
void ecrireMS(LO_VC *t ,int i,Bloc *buf);
int entete(LO_VC *t,int i);
void affecter_entete(LO_VC *t,int i,int n);
int AllocBloc(LO_VC *t);

//fonctions fichier LO_VC
void creationLO_VC(LO_VC *t,int nb_enrg);
void suppressionLO_VC(LO_VC *t, int cle);
void insertionLO_VC(LO_VC *t, char *cle);
void rechercheLO_VC(LO_VC *t, char *key, bool *trouve,int *i,int *pos);
void ecrire_char_Bloc(LO_VC *t,char *ch,int *i ,int *pos);
void recuperer_cle_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup);
void recuperer_efface_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup);
void afficherLO_VC(LO_VC *t);




#endif // machineabstraite_h_included



=======
#ifndef machineabstraite_h_included
#define machineabstraite_h_included

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//structure du bloc d'un fichier LO_VC
typedef struct Bloc {
  char Tab[10];
  int svt;
}Bloc;

//buffer ï¿½ utiliser pour manipuler la MC et la MS
Bloc Buffer;

//structure de l'entete du fichier LO_VC
typedef struct Entete{
int prem_Bloc;
int der_Bloc;
int pos_libre;
int nbcar_ins;
int nbcar_supp;
}Entete;

//structure d'un fichier LO_VC
typedef struct LO_VC{
FILE* f;
Entete entete_f;
}LO_VC;

//structure d'un enregistrement dans un bloc de fichier LO_VC
typedef struct enregistrement
{   int cle;
    int car_spe1;
    int efface;  // pour indiquer l'effacement logique
    char car_spe2;
}enreg;

//machine abstraite LO_VC
LO_VC* ouvrir(char nomfichier[20],char mode);
void fermer (LO_VC *t);
void lireMS(LO_VC *t ,int i,Bloc *buf);
void ecrireMS(LO_VC *t ,int i,Bloc *buf);
int entete(LO_VC *t,int i);
void affecter_entete(LO_VC *t,int i,int n);
int AllocBloc(LO_VC *t);

//fonctions fichier LO_VC
void creationLO_VC(LO_VC *t,int nb_enrg);
void suppressionLO_VC(LO_VC *t, int cle);
void insertionLO_VC(LO_VC *t, int cle);
void rechercheLO_VC(LO_VC *t, char *key, bool *trouve,int *i,int *pos);
void ecrire_char_Bloc(LO_VC *t,char *ch,int *i ,int *pos);
void recuperer_cle_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup);
void recuperer_efface_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup);
void afficherLO_VC(LO_VC *t);


#endif // machineabstraite_h_included



>>>>>>> 890cedd68643eef98c019bfaa224d42cd5870170
