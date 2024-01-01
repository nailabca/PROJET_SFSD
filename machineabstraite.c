#include "machineabstraite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

//machine abstraite fichier LO_VC
LO_VC* ouvrir(char nomfichier[20],char mode)
{
    LO_VC *t= malloc(sizeof(LO_VC));
    if(mode=='A')
    {
        t->f=fopen(nomfichier,"rb+"); //ouverture mode lecture +
        if(t->f==NULL)
            printf("error");
        else
            fread(&(t->entete_f),sizeof(Entete),1,t->f); //recuperation de l'entete en MC
    }
    else
    {
        t->f=fopen(nomfichier,"wb+"); //ouverture en mode ecriture +
        if(t->f==NULL)
            printf("error");
        else
        {
             //initialiser l'entete
            t->entete_f.prem_Bloc=0;
            t->entete_f.der_Bloc=0;
            t->entete_f.pos_libre=0;
            t->entete_f.nbcar_ins=0;
            t->entete_f.nbcar_supp=0;
            fwrite(&(t->entete_f),sizeof(Entete),1,t->f);  //ecrire l'entete dans le fichier
        }

    }
   return t;
}


void fermer (LO_VC *t)
{
    fseek(t->f,0,SEEK_SET);//se placer au debut du fichier
    fwrite(&(t->entete_f),sizeof(Entete),1,t->f); //ecrire l'entete probablement modifi� au cours des traitements
    fclose(t->f); //fermer le fichier
}

void lireMS(LO_VC *t ,int i,Bloc *buf)
{
    fseek(t->f,sizeof(Entete)+i*sizeof(Bloc),SEEK_SET);//se placer au debut du bloc
    fread(buf,sizeof(Bloc),1,t->f);//lire le bloc en MC
}

void ecrireMS(LO_VC *t ,int i,Bloc *buf)
{
    fseek(t->f,sizeof(Entete)+sizeof(Bloc)*i,SEEK_SET);//se placer au debut du bloc
    fwrite(buf,sizeof(Bloc),1,t->f); //ecrire le bloc dans le fichier
}

int entete(LO_VC *t,int i)
{
    if(i==1)
        return (t->entete_f).prem_Bloc; //premier bloc du fichier
    if(i==2)
        return (t->entete_f).der_Bloc; //nombre de blocs total
    if(i==3)
        return (t->entete_f).pos_libre; //position bloc libre
    if(i==4)
        return (t->entete_f).nbcar_ins; //nombre de caracteres inseres
    if(i==5)
        return (t->entete_f).nbcar_supp; //nombre de caracteres supprimes
    else
        return -1;
}

void affecter_entete(LO_VC *t,int i,int n)
{
    //modifier l'entete (son ecriture se fait uniquement lors de la fermeture du fichier)
    if(i== 1)
        (t->entete_f).prem_Bloc = n;
    if(i== 2)
        (t->entete_f).der_Bloc = n;
    if(i== 3)
        (t->entete_f).pos_libre = n;
    if(i== 4)
        (t->entete_f).nbcar_ins = n;
    if(i== 5)
        (t->entete_f).nbcar_supp = n;
}


//fonctions du fichier LO_VC

//fonction pour allouer un bloc
int AllocBloc(LO_VC *t){
 //on ne peut pas utiliser malloc lors de la manipulation de la MS
 int B = entete(t,2)+1; //+1 car on rajoute un nouveau bloc

  Bloc nouveauBloc;
    nouveauBloc.svt = -1;

 return B;
 }


//fonction pour ecrire dans le bloc � travers le buffer (�ventuellement la cl� /car sp�1 /effac� /car_sp�2 )
void ecrire_char_Bloc(LO_VC *t,char *ch,int *i, int *pos){

   for (int k = 0; k < strlen(ch) ; k++)
    {
        if(*pos<10)
        {    //pas de chevauchement
           Buffer.Tab[*pos] = ch[k];
           *pos = *pos + 1;
        }
        else{ //avec chevauchement
           int nouv_bloc = AllocBloc(t);
           affecter_entete(t,2,entete(t,2)+1);
           Buffer.svt = nouv_bloc;
           ecrireMS(t,*i,&Buffer); //ecrire le buffer rempli dans la MS
           *i= nouv_bloc;
           Buffer.Tab[0] = ch[k]; // transmission de la chaine au buffer et pos=0
           *pos = 1; //pour incrementer la pos dans le nouveau bloc
        }
       affecter_entete(t,4,entete(t,4)+1);
     }
  }

 //creation du fichier LO_VC
void creationLO_VC(LO_VC *t,int nb_enrg){
    char *ch = malloc(6);
    char ch_nom[15];
    FILE *fNom = fopen("Nom.txt","r");
    int pos = 0;
    int B = entete(t,2); //numero du bloc (B = Bloc)
  for(int i =0 ;i<nb_enrg; i++){
    int cle = rand()%10000; // (0-9999)
    snprintf(ch,sizeof(ch),"%d",cle); //conversion d'un entier en chaine
    ecrire_char_Bloc(t,ch,&B,&pos); //ecrire la cl�
    ecrire_char_Bloc(t,"$0#",&B,&pos); //ecrire (car sp�1 /effac� /car sp�2)
    if( fgets(ch_nom,sizeof(ch_nom),fNom)!= NULL )
    {    int k = 0;
         printf("%s",ch_nom);
        while(ch_nom[k] != '\0')
        {
            k++;
        }
       ch_nom[k-1] = '/';
    }
    ecrire_char_Bloc(t,ch_nom,&B,&pos);
    printf("Bloc = %d , position = %d\n",B,pos);
  }
   affecter_entete(t,3,pos); //positionner � la position libre du bloc libre
   ecrireMS(t,B,&Buffer); //ecrire le dernier bloc
  free(ch);
}

//fonction pour afficher le fichier LO_VC
void afficherLO_VC(LO_VC *t){

    int i = entete(t,1);
    int pos;
    while(i!=entete(t,2))
    {
         lireMS(t,i,&Buffer);
         printf("\n");
         printf("Bloc %d = ",i);
        for(pos=0;pos<10;pos++)
            {
                printf("%c",Buffer.Tab[pos]);
            }
        i = Buffer.svt;
    }

    //cas particulier : (dernier bloc, car il n'est peut �tre pas totalement rempli)
    lireMS(t,i,&Buffer);
    printf("\n");
    printf("Bloc %d = ",i);
    for(pos=0; pos< entete(t,3);pos++)
        {
            printf("%c",Buffer.Tab[pos]);
        }
}

//fonction pour rechercher une cl�
void rechercheLO_VC(LO_VC *t, char *key, bool *trouve,int *i,int *pos)
{
     *i= entete(t,1);
     *pos = 0;
     *trouve = false;
     lireMS(t,*i,&Buffer);
     char *cle = malloc(5);
     char *efface = malloc(5);
     while((*trouve==false)   && ((*i != entete(t,2)) || (*i == entete(t,2) && *pos < entete(t,3))) )
        {
          recuperer_cle_Bloc(t,i,pos,cle);
          printf(" %s ~",cle);
          recuperer_efface_Bloc(t,i,pos,efface);
          int cmp_cle = strcmp(key,cle);
          int cmp_efface = strcmp(efface,"$0");
         if ( (cmp_cle == 0 )&& (cmp_efface == 0))
           {*trouve = true;}
          //on avance pour se positionner sur le '/' pour recuperer les cles suivantes

            while((Buffer.Tab[*pos] != '/')&&((*i!=entete(t,2))||(*pos != entete(t,3))))
             {      if(*i!=entete(t,2))
                       {
                          if(*pos<10)
                            { //pas de chevauchement
                                *pos = *pos +1;
                            }
                              else{ //avec chevauchement
                                    *i = Buffer.svt;
                                    lireMS(t,*i,&Buffer);
                                        if(Buffer.Tab[0] != '/')
                                          {
                                            *pos = 1;
                                          }
                                       else{*pos=0;}
                                  }
                         }
                    else //pour le dernier bloc
                     {
                         if(*pos < entete(t,3))
                            { //pas de chevauchement
                                 *pos = *pos +1;
                            }
                     }
              }
        *pos = *pos +1;
        }
        if(*trouve==true){printf("\n------CLE TROUVEE !------");}
        else{printf("\n------CLE INTROUVABLE !------");}

}


void recuperer_cle_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup)
{   int k=0;
     if(Buffer.Tab[*pos] == '/')
        *pos=*pos+1;
    while((Buffer.Tab[*pos] != '$')&&((*i!=entete(t,2))||(*pos != entete(t,3))))
      {  if(*i!=entete(t,2))
           {
              if(*pos<10)
                { //pas de chevauchement
                    ch_recup[k] = Buffer.Tab[*pos];
                    *pos = *pos +1;
                    k++;
                }
                  else{ //avec chevauchement
                        *i = Buffer.svt;
                        lireMS(t,*i,&Buffer);
                            if(Buffer.Tab[0] != '$')
                              {
                                ch_recup[k] = Buffer.Tab[0];
                                k++;
                                *pos = 1;
                              }
                           else{*pos=0;}
                      }
             }
        else
         {
             if(*pos < entete(t,3))
                { //pas de chevauchement
                      ch_recup[k] = Buffer.Tab[*pos];
                     *pos = *pos +1;
                      k++;
                }
         }
      }
        ch_recup[k]='\0';

}

void recuperer_efface_Bloc(LO_VC *t, int *i, int *pos, char *ch_recup)
{ int k=0;
    while((Buffer.Tab[*pos] != '#')&&((*i!=entete(t,2))||(*pos != entete(t,3))))
     {
       if(*i!=entete(t,2))
         {
           if(*pos<10)
            { //pas de chevauchement
              ch_recup[k] = Buffer.Tab[*pos];
              *pos = *pos +1;
              k++;
            }
             else
                { //avec chevauchement
                 *i = Buffer.svt;
                 lireMS(t,*i,&Buffer);
                 if(Buffer.Tab[0] != '#')
                   {
                     ch_recup[k] = Buffer.Tab[0];
                     k++;
                     *pos = 1;
                   }
                 else
                    {*pos=0;}
              }
          }
        else
         {
             if(*pos < entete(t,3))
                { //pas de chevauchement
                      ch_recup[k] = Buffer.Tab[*pos];
                     *pos = *pos +1;
                      k++;
                }
         }
     }
     ch_recup[k]='\0';
}
void suppressionLO_VC(LO_VC *f, char *cle)
{
    int i,pos;
    bool trouv=false;
    Bloc buffer;
    rechercheLO_VC(f,cle,&trouv,&i,&pos); // recherche de la cle dans le fichier
    printf("\n");


  if (trouv)
    {

        int blockCurrent = i;





                while(blockCurrent>=0){

                lireMS(f, blockCurrent, &buffer);

            // chercher '#' dans le block current pour modifier l'indice d'effacement se trouvant juste avant ce dernier
            while(pos>0&&buffer.Tab[pos] != '#'){pos--;}

                if (pos>0)
                {
                    buffer.Tab[pos - 1] = '1'; // mise a 1 l'indice d'effacement
                    ecrireMS(f, blockCurrent, &buffer); // Reecriture  du bloc
                    affecter_entete(f, 5, entete(f, 5) + 1); // Mise a jour du nombre de caractère supprimes
                    printf("\n Suppression logique reussie\n");
                    break;
                }
                else
                {
                    pos=10;
                    blockCurrent--;
                }

                }

    }
    else
    {
        printf("\n Suppression impossible ! Cle inexistante\n");
    }
}






