#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Plat{
    char nom[31];
    char desc[101];
    float prix;
    int jour,mois,annee;
    struct Plat *next;
    struct Plat *prev;
 }Plat;

 typedef struct Categorie{
    char nom[31];
    Plat *Plat;
    struct Categorie *next;
    struct Categorie *prev;
}Categorie;

typedef struct Restaurant{
    int note;
    float moyenne_prix;
    float distance;
    char adresse[51];
    Categorie *Cat;
    struct Restaurant *next;
    struct Restaurant *prev;
}Restaurant;

void afficherTousLesPlats(Categorie *debut);

void fclean(char *tab,int taille){//la fonction principale qui passe en mode lecture pour les caracteres entree par l'utilisateur en upprimons \n
    fgets(tab,taille,stdin);
    int c = 0 ;
    while(tab[c] != '\n'){
        c++;
    }
    tab[c] = '\0' ;
}
int checkNomCat(Categorie *debut,char tab[]){ //fonction qui verifie si le nom entre par l'utilisatzur existe deja ou non
    while(debut){
        if(strcasecmp(tab,debut->nom) == 0)
        return 1;
            
        debut = debut->next;
    }
return 0;
}
Restaurant *ajouterCategorie(Restaurant *debut){ //fonction qui ajoute une nouvelle categorie
    Categorie *New,*temp;
    char check[31];
    int c ;
    New = malloc(sizeof(Categorie));
    printf("Entrez le nom de categorie: \n");
    do{
        fflush(stdin);
        fclean(check,31);
        if(checkNomCat(debut->Cat,check))
        printf("Nom de categorie existe deja. Veuillez entre a nouveau : ");
    }while(checkNomCat(debut->Cat,check));
    strcpy(New->nom,check);

    New->Plat = NULL;
    New->next = NULL;
    New->prev = NULL;

    if(!debut->Cat)
    debut -> Cat = New;
    else{
        New -> next = debut->Cat;
        New ->next -> prev = New;
        debut->Cat = New ;
    }

    return debut;
}
void calculePrixMoyenne(Restaurant *debut){ 

Categorie *cat;
Plat *ptr;

float somme = 0;
float resultat = 0;
float c = 1;

for(cat = debut->Cat ; cat != NULL ; cat = cat -> next){
    for(ptr = cat->Plat ; ptr != NULL ; ptr = ptr -> next){
        somme += ptr->prix;
        c++;
    }
    if(c)
    somme /= c;
    resultat += somme;
    somme = 0 ;
    c = 0 ;
}
debut -> moyenne_prix = resultat ;
}
Plat *creerPlat(Restaurant *debut){//fonction qui retourne un nouveau pointeur de type plat
    int i;
    Plat *new,*ptr;
    Categorie *cat ;


    new = malloc(sizeof(Plat));
    new->next = NULL;
    new->prev = NULL;

    char tab[31];
    printf("Entrez le nom de plat:\n");
    do{

    i=0;
    fflush(stdin);
    fclean(tab,31);

        for(cat = debut->Cat ; cat != NULL && !i ; cat = cat->next){
            for(ptr = cat->Plat ; ptr != NULL && !i; ptr = ptr->next){
                if(strcasecmp(tab,ptr->nom) == 0)
                i++;
            }
        }
    
    if(i){
    printf("\nLe nom de plat fournit existe deja!\n");
    printf("\tENTREZ A NOUVEAU: \n");}

}while(i);

strcpy(new->nom,tab);

printf("Entrez la description de plat :\n");
fflush(stdin);
fclean(new->desc,101);

do{
printf("Entrez le prix de plat:\n");
scanf("%f",&new->prix);
}while(new->prix <= 0);
do{
printf("Entrez le jour :\n");
scanf("%d",&new->jour);
}while(new->jour <=0 || new->jour > 31);

do{
    printf("Entrez le mois :\n");
scanf("%d",&new->mois);
}while(new->mois <= 0 || new->mois > 12);

do{
    do{
    printf("Entrez l'annee :\n");
    scanf("%d",&new->annee);
    }while(new->annee <= 0 || new->annee > 2025);
}while(new->annee < 0 || new->annee > 2025);

return new;
}
Plat *checkNomPlat(Categorie *ptr,char tab[]){//fonction qui v

for(ptr ; ptr != NULL ; ptr = ptr -> next){

    for(Plat *temp = ptr->Plat; temp != NULL ; temp = temp->next){
        if(strcasecmp(temp->nom,tab) == 0)
        return temp;
    }
}
return NULL;
}
void ajouterPlat(Restaurant *debut){
    int choix;
    char tab[31];
    Plat *new,*temp;
    Categorie *ptr;
    E1 :
    do{
        printf("0-Retour\n");
        printf("1-Ajout apres un plat specifique\n");
        printf("2-Ajouter dans une nouvelle categorie\n");
        printf("3-Ajouter dans une categorie existante\n");
        printf("\t\nVeuillez choisir: ");
        
        scanf("%d",&choix);
    }while(choix < 0 || choix >3);

    switch(choix){
        case 0:
        return;
        case 1 :
        if(!debut->Cat){
        printf("\n\tAUCUN PLAT N'EST DISPONIBLE !\n\n");
        goto E1;
    }
        else{
           
        printf("Entrez le plat specifique a Ajouter apres: ");
        do{
        fflush(stdin);
        fclean(tab,31);
        
        temp = checkNomPlat(debut->Cat,tab) ;
        if(!temp){
         printf("Nom de plat inexistant. ENTREZ A NOUVEAU : ");
        }
        }while(!temp);
        new = creerPlat(debut);
        new -> next = temp->next;
        new->prev = temp ;
        
        if(new->next){
        new->next->prev = new;
    }
    temp -> next = new ;
    printf("\n\tPLAT AJOUTE EN SUCCES!\n");
    }
        return;   
        case 2 :
        debut = ajouterCategorie(debut);
        debut->Cat->Plat = creerPlat(debut);
        printf("\n\tPLAT AJOUTE EN SUCCES!\n");
        return ;

        case 3 :
        if(!debut->Cat){
        printf("\n\tLA LISTE DES CATEGORIES EST VIDE!\n\n");
        goto E1 ;
    }
        else{
        printf("Entrez le nom de la categorie: \n");
        do{
            fflush(stdin);
            fclean(tab,31);

            if(!checkNomCat(debut->Cat,tab))
            printf("\n\tCategorie n'existe pas. Entrez a nouveau: \n");
        }while(!checkNomCat(debut->Cat,tab));
    }
    }
    do{
        printf("0-Retour\n");
        printf("1-Ajout au debut\n");
        printf("2-Ajout a la fin\n");
        scanf("%d",&choix);
    }while(choix < 0 || choix > 2);

    switch(choix){
        case 0 :
        goto E1;

        case 1 :
        ptr = debut->Cat;
        new = creerPlat(debut);

        while(strcasecmp(ptr->nom,tab) != 0){
            ptr = ptr->next;
        }
        new -> next = ptr->Plat ;

        if(ptr->Plat)
        ptr->Plat->prev = new;

        ptr->Plat = new;
        break;
        case 2 :
        new = creerPlat(debut);
        Plat *temp;
        ptr = debut->Cat;

        while(strcasecmp(ptr->nom,tab) != 0){
            ptr = ptr->next;
        }
        temp = ptr->Plat;

        if(temp){
        while(temp->next){
            temp = temp -> next;
        }
        temp->next = new ;
    }else
    ptr->Plat = new;

    new -> prev = temp ;
        break;
    }
    printf("\n\tPLAT AJOUTE EN SUCCES");
}
Plat *triPlat(Plat *plat ,int choix){
    float min;
    int c = 0,i = 0 ;
    Plat *temp,*ptr,*var;
       ptr = plat ;
             while(ptr){
             c = 0 ;
              var = ptr ;
              temp = ptr->next ;
              switch(choix){
                case 1:
                min = ptr->prix;
               while(temp){
               if(min > temp -> prix){
                   min = temp -> prix ;
                   var = temp ;
               }
               temp = temp -> next ;
           }
                break;
              }
            switch(choix){
                case 1 :
                if(ptr->prix)
                c++;
                break;
            }
            i++;
            if(i == 1)
            plat = var ;
           if(c){
            if(ptr->next == var){
            ptr->next = var->next;
            if(ptr->next != NULL)
            ptr->next->prev = ptr;
            var->prev = ptr->prev;
            if(var->prev != NULL)
            var->prev->next = var;
            var->next = ptr;
            ptr->prev = var;
            }else{
                temp = ptr->next;
                ptr->next = var->next;
                if(ptr->next)
                ptr->next->prev = ptr;
                var->next = temp;
                if(var->next)
                var->next->prev = var;
                temp = ptr->prev;
                ptr->prev = var->prev;
                if(ptr->prev)
                ptr->prev->next = ptr;
                var->prev = temp;
                if(var->prev)
                var->prev->next = var;
            }
           }
           ptr = var->next;
        }
   return plat;
}
Restaurant *tri(Restaurant *debut,int choix){
    float min;
    int c = 0,i = 0 ;
    Restaurant *temp,*ptr,*var;
       ptr = debut ;
             while(ptr){
             c = 0 ;
              var = ptr ;
              temp = ptr -> next ;
              switch(choix){
                case 1:
                min = ptr -> moyenne_prix ;
               while(temp){
               if(min > temp -> moyenne_prix){
                   min = temp -> moyenne_prix ;
                   var = temp ;
               }
               temp = temp -> next ;
           }
                break;
                case 2:
                min = ptr -> distance ;
               while(temp){
               if(min > temp -> distance){
                   min = temp -> distance ;
                   var = temp ;
               }
               temp = temp -> next ;
           }
                break;
                case 3:
                min = ptr -> note ;
               while(temp){
               if(min > temp -> note){
                   min = temp -> note ;
                   var = temp ;
               }
               temp = temp -> next ;
           }
                break;
              }    
            switch(choix){
                case 1 :
                if(ptr->moyenne_prix)
                c++;

                break;
                case 2 :
                if(ptr->distance)
                c++;

                break;
                case 3 :
                if(ptr->note)
                c++;

                break;
            }
            i++;
            if(i == 1)
            debut = var ;

           if(c){
            if(ptr->next == var){
            ptr->next = var->next;
            if(ptr->next != NULL)
            ptr->next->prev = ptr;
            var->prev = ptr->prev;
            if(var->prev != NULL)
            var->prev->next = var;
            var->next = ptr;
            ptr->prev = var;
            }else{
                temp = ptr->next;
                ptr->next = var->next;
                if(ptr->next)
                ptr->next->prev = ptr;
                var->next = temp;
                if(var->next)
                var->next->prev = var;
                temp = ptr->prev;
                ptr->prev = var->prev;
                if(ptr->prev)
                ptr->prev->next = ptr;
                var->prev = temp;
                if(var->prev)
                var->prev->next = var;
            }
           }
          
           ptr = var->next;
        }
   return debut;

}
Restaurant *ajouterRestaurant(Restaurant *debut){
Restaurant *ptr;
char tab[51];
ptr = malloc(sizeof(Restaurant));
ptr -> next = debut;
if(debut)
debut->prev = ptr;
ptr->prev = NULL;
do{
printf("Entrez la note de restaurant de sur 5: ");
scanf("%d",&ptr->note);
}while(ptr->note < 1 || ptr->note >5);
printf("\n");
ptr->moyenne_prix = 0;
printf("Entrez l'adresse de restaurant : ");
fflush(stdin);
fclean(ptr->adresse,51);
fflush(stdin);
printf("\n");
do{
    printf("Entrez la surface de restaurant en m^2: ");
    scanf("%f",&ptr->distance);
}while(ptr->distance <=0);
ptr->Cat = NULL ;
return ptr;
}
Restaurant *supprimerRestaurant(Restaurant *debut,int position){
    Restaurant *ptr;
    Categorie*ptr2;
    Plat *ptr3;
    ptr = debut;
    for(int c = 1 ; c < position ; ptr = ptr ->next,c++);
    ptr2 = ptr->Cat;
    while(ptr2){
        ptr3 = ptr2->Plat;
        while(ptr3){
            if(ptr3 -> next){
                ptr3 = ptr3 -> next;
                free(ptr3->prev);
            }else{
                free(ptr3);
                ptr3 = NULL;
            }
        }
        if(ptr2->next){
        ptr2 = ptr2->next;
        free(ptr2->prev);
    }else{
        free(ptr2);
        ptr2 = NULL;
    }}
    if(!ptr->prev){
        if(ptr->next){
            debut = ptr->next;
            debut->prev = NULL;
        }else{
            debut = NULL;
        }
    }else{
        if(ptr->next)
        ptr->next->prev = ptr->prev;

        ptr->prev->next = ptr->next;
    }
free(ptr);
return debut;
}
void spaceCat(char tab[]){
    int c = strlen(tab);
     c+=2;
     for(int a = c ; a < 30 ; a++){
      printf(" ");
     }
}
        void afficherCategorie(Categorie *debut,int *taille){

            if(!debut)
            printf("\n\tListe des categories est vide\n\n");
            else{
                int c = 1;
                printf("\n");
                printf("\t----Liste des categories----\n\n");
            while(debut){
                printf("%d-%s",c,debut->nom);
                spaceCat(debut->nom);
                debut = debut->next;
                c++;
            }
            *taille = c-1;
            }
            printf("\n\n");
        }
        void modifierNomCat(Categorie *debut,int position){

            if(!debut)
            printf("Liste des categories est vide\n");
            else{
                char check[31];
                printf("Entrez le nouveau nom de la categorie\n");
                do{
                    fflush(stdin);
                    fclean(check,31);

                if(checkNomCat(debut,check))
                printf("\tNom existe deja, Veuillez entrez a nouveau: ");

                }while(checkNomCat(debut,check));
                
                for(int c = 1 ; c < position ; c++,debut = debut->next);

                strcpy(debut->nom,check);

                printf("\n\tLe nom a ete modifier en succes!\n\n");
            }
        }
        void afficherRestaurant(Restaurant *debut,int *taille){
                printf("\t----Restaurants disponibles----\n\n");
                printf("0-Retour\n\n");
                for(*taille = 0 ; debut != NULL ; (*taille)++ , debut = debut->next){
                printf("\t----Restaurant %d----\n",*taille+1);
                printf("_____________________________________\n");
                printf("Note: %d\n",debut->note);
                printf("Adresse : %s\n",debut->adresse);
                printf("Prix moyenne des plats: %.2f DHS\n",debut->moyenne_prix);
                printf("Distance de restaurant: %.2f m2\n",debut->distance);
                printf("_____________________________________\n\n");
                }
                printf("\n");
            }
        Restaurant *supprimerCat(Restaurant *debut,int position){
            if(!debut){
            printf("\n\tListe des categories est vide\n");
            return debut;}
            Categorie *ptr = debut -> Cat;
            for(int c = 1 ; c < position ; c++ ,ptr = ptr-> next );
            Plat *plat = ptr->Plat;
                while(plat){
                    if(plat->next){
                        plat = plat->next;
                        free(plat->prev);
                    }else{
                        free(plat);
                        plat = NULL;
                    }
                }
            if(!ptr->prev){
                if(ptr->next){
                    debut->Cat = ptr->next;
                    debut->Cat->prev = NULL;
                }else{
                    debut->Cat = NULL;
                }
            }else{
                if(ptr->next)
                ptr->next->prev = ptr->prev;
        
                ptr->prev->next = ptr->next;
            }
            free(ptr);
            printf("\n\tCategorie supprime en succes\n");
            return debut;
        }
        void spacePlat(char tab[]){
            int c = strlen(tab);
            c += 8;
            for(int a = c ; a < 30 ; a++){
                printf(" ");
            }
        }
        void afficherTousLesPlats(Categorie *debut){
            int c = 1 ;
            int max1 = 0,max2 = 0;
            Plat *temp2;

            for(temp2 = debut->Plat ; temp2 != NULL; temp2 = temp2 ->next){
                max1++;
            }
            for(Categorie *temp = debut->next ; temp != NULL ; temp = temp -> next){
                max2 = 0 ;
                for(Plat *temp2 = temp->Plat ; temp2 != NULL; temp2 = temp2 ->next){
                    max2++; }
                if(max2 > max1){
                    max1 = max2 ;}
            }
            int i = 0 ;
            for(max1 ; max1 > 0 ; max1--){
                i++;
                for(Categorie *temp = debut ; temp != NULL ; temp = temp -> next){
                    c = i ;
                    temp2 = temp -> Plat ;
                        while( c > 1){
                            if(temp2)
                            temp2 = temp2 -> next ;
                            else break;
                            c--;}
                    if(temp2){
                    printf("Plat %d: %s",i,temp2->nom);
                    spacePlat(temp2 -> nom) ;
                        }else{
                            printf("                              ");
                        }
                }
                printf("\n"); }}
                
    void detailsPlat(Plat *ptr){
                printf("1-Nom de plat: %s\n",ptr->nom);
                printf("2-Description: %s\n",ptr->desc);
                printf("3-Prix: %.3f DHS\n",ptr->prix);
                printf("4-Date d'Ajout: ");
                if(ptr->jour/10 == 0)
                printf("0%d/",ptr->jour);
                else printf("%d/",ptr->jour);
                if(ptr->mois/10 == 0)
                printf("0%d/",ptr->mois);
                else printf("%d/",ptr->mois);
                printf("%d\n",ptr->annee);
                printf("_____________________\n\n");
    }
    int afficherPlatparNom(Categorie *cat){
        Plat *ptr;
        char tab[31];
        printf("\nEntrez le nom de plat: ");
        fflush(stdin);
        fclean(tab,31);
        for(cat ; cat != NULL ; cat = cat -> next){
            ptr = cat->Plat;
            while(ptr){
                if(strcasecmp(ptr->nom,tab) == 0){
                    printf("Categorie:\t----%s----\n",cat->nom);
                    detailsPlat(cat->Plat);
                    return 1 ;
                }
                ptr = ptr->next;
            } }
            return 0 ;
    }
    int afficherPlatsparCategorie(Categorie *cat){
        Plat *ptr;
        char tab[31];
        Categorie *P;
        printf("\nEntrez le nom de la categorie : ");
        fflush(stdin);
        fclean(tab,31);
        for(P = cat ; P != NULL && strcasecmp(P->nom,tab)!=0;P = P->next);
        if(P == NULL)
        return 0 ;
        printf("\n\tCategorie:\t----%s----\n\n",P->nom);
        printf("_____________________\n");
            ptr = P->Plat ;

            for(ptr ; ptr != NULL ; ptr = ptr -> next){
            detailsPlat(ptr);
            
            }
        return 1 ;
    }
    int afficherPlatsparDatte(Categorie *cat){
        int jour,mois,annee;
        int i = 0 , c = 0 ;
        Plat *P;
        do{
        printf("Entrez le jour : ");
        scanf("%d",&jour);
    }while(jour <=0 || jour  > 31 );
     do{
        printf("\nEntrez le mois : ");
        scanf("%d",&mois);
     }while(mois <=0 || mois > 12);
     do{
        printf("\nEntrez l'annee: ");
        scanf("%d",&annee);
     }while(annee < 0);
     printf("\n");
     for(cat ; cat != NULL ; cat = cat -> next ){
        for(P = cat->Plat ; P != NULL ; P = P -> next){
            i = 0 ;
            if(P->jour == jour && P->mois == mois && P->annee == annee){
                i++;
                if( i == 1 ){
                printf("\n\t----%s----\n",cat->nom);
                }
                detailsPlat(P) ;
                c = 1 ;
            }
         }
     } return c ;
    }
    void modifierPlat(Categorie *cat){
        int choix;
        char tab[31];
        Plat *ptr;
do{
    fflush(stdin);
        printf("Entrez le nom de plat a modifier : ");
        fclean(tab,31);
        ptr = checkNomPlat(cat,tab);
        if(!ptr){
            do{
            printf("\n\t----NOM DE PLAT NON TROUVE----\n");
            printf("1-Entrez a nouveau\n");
            printf("2-Retour\n");
            printf("\tVeuillez choisir : ");
            scanf("%d",&choix);
            }while(choix < 1 || choix > 2);
            if(choix == 2)
            return;}
            }while(choix == 1);
do{
        do{
            printf("0-Retour\n");
            detailsPlat(ptr);
            printf("\tVeuillez choisir la donnee a modifier : ");
            scanf("%d",&choix);
        }while(choix < 0 || choix > 4);

        switch(choix){
            case 0 : 
            return ;
            case 1 :
            printf("\nEntrez le nouveau nom de plat : ");
            fflush(stdin);
            fclean(ptr->nom,31);
            printf("\n");
            break;
            case 2 :
            printf("\nEntrez la nouvelle description: ");
            fflush(stdin);
            fclean(ptr->desc,101);
            printf("\n");
            break;
            case 3 :
            printf("\nEntrez le nouveau prix :");
            scanf("%f",&ptr->prix);
            printf("\n");
            break;
            case 4 :
            do{
            printf("\nEntrez le jour : ");
            scanf("%d",&ptr->jour);
            }while(ptr->jour <= 0 || ptr->jour >31);
            do{
            printf("\nEntrez le mois : ");
            scanf("%d",&ptr->mois);
            }while(ptr->mois <= 0 || ptr -> mois > 12);
            do{
            printf("\nEntrez l'annee : ");
            scanf("%d",&ptr->annee);
            }while(ptr->annee < 0);
            break;
        }
    }while(1);
    }
    void *suppressionPlat(Restaurant *rest){
        char tab[31];
        int choix;
        Plat *ptr;
        E1 :
        printf("Entrez le nom de plat a supprimer :");
        fflush(stdin);
        fclean(tab,31);
        ptr = checkNomPlat(rest->Cat,tab);
        if(!ptr){
        printf("\n\tLE PLAT N'EXISTE PAS !\n");
        do{
            printf("0-Retour\n");
            printf("1-Entrez a nouveau\n");
            printf("\n\tVeuillez choisir: ");
            scanf("%d",&choix);
        }while(choix < 0 || choix > 1);
        switch(choix){
            case 0 :
            return rest->Cat;
            case 1 :
            goto E1 ; }
    }
    if(!ptr->prev){
        if(ptr->next){
            ptr->next->prev = NULL;
            rest->Cat->Plat = ptr->next;
        }else rest->Cat->Plat = NULL;
    }else{
        ptr->prev->next = ptr->next;
        if(ptr->next)
        ptr->next->prev = ptr->prev;
    }
    free(ptr);
    printf("\n\tLE PLAT A ETE SUPPRIME AVEC SUCCES!\n");
}
int *convertInt(long i , int **SIZE){
    int *tab,c = 1,min,max,temp,taille;

    tab = malloc(sizeof(int));
    tab[0] = i % 10 ;
    i /= 10;
    while(i){
        c++;
        tab = realloc(tab,c*sizeof(int));
        tab[c-1] = i % 10 ;
        i /= 10 ;
    }
    min = 0 ;
    max = c - 1 ;
    for(taille = c/2;taille > 0 ; taille-- , max-- , min--){
        temp = tab[min];
        tab[min] = tab[max];
        tab[max] = temp ;
    }
    *(*SIZE) = c;
    return tab ;
}
char* toChar(int **number,int taille){
    char *tab;
    char *chiffre;
    tab = malloc((15+taille) *sizeof(char));
    chiffre = malloc(taille * sizeof(char));
    for(int a = 0 ; a < taille ; a++){
        chiffre[a] = (*number)[a] + '0';}
    strcpy(tab,"Restaurant");
    chiffre[taille] = '\0';
    strcat(tab,chiffre);
    strcat(tab,".txt");
    return tab;}
char *nomFichier(int position){

    char *new;
    int *SIZE,*tab,taille;
    SIZE = malloc(sizeof(int));
    tab = convertInt(position,&SIZE);
    taille = *SIZE;
    new = toChar(&tab,taille);
    return new;
    }
void fclear(char *tab,FILE **fichier,int taille){
    fgets(tab,taille,*fichier);
    for(int a = 0 ; a < taille ; a++){
        if(tab[a] == '\n'){
        tab[a] = '\0';
        break;}
    }
}
void Sauvegarde(Restaurant **Start,FILE **fichier){
    char *nouveauFichier;
    int positionFichier = 1 ;
    for(Restaurant *ptr = *Start ; ptr != NULL ; ptr = ptr -> next , positionFichier++){
        remove(nomFichier(positionFichier));
    }
    positionFichier = 1 ;
    for(Restaurant *ptr = *Start ; ptr != NULL ; ptr = ptr -> next , positionFichier++){
    nouveauFichier = nomFichier(positionFichier);
    *fichier = fopen(nouveauFichier,"a+");
    fprintf(*fichier,"%d\n",ptr->note);
    fprintf(*fichier,"%f\n",ptr->moyenne_prix);
    fprintf(*fichier,"%f\n",ptr->distance);
    fprintf(*fichier,"%s\n",ptr->adresse);
    for(Categorie *cat = ptr->Cat ; cat != NULL ; cat = cat->next){
     fprintf(*fichier,"CAT\n");
     fprintf(*fichier,"%s\n",cat->nom);
     for(Plat *plat = cat->Plat ; plat !=NULL ; plat = plat->next){
        fprintf(*fichier,"PLAT\n");
        fprintf(*fichier,"%s\n",plat->nom);
        fprintf(*fichier,"%s\n",plat->desc);
        fprintf(*fichier,"%f\n",plat->prix);
        fprintf(*fichier,"%d\n",plat->annee);
        fprintf(*fichier,"%d\n",plat->mois);
        fprintf(*fichier,"%d\n",plat->jour);
     }}
    fclose(*fichier);
    }
}

int main(){
    Restaurant *Start,*ptr;
    Categorie *ptrCAT;
    Plat *ptrPLAT;
    Start = NULL;
    FILE *fichier;
    char *nouveauFichier;
    int choix,choix2,choix3,choix4,choix5,choix6,choix7,choix8,choix9,choix10,choix11,choix12,choix13;
    int taille,positionFichier,i;
    char tabCAT[5];
    char tabPLAT[6];
    positionFichier = 1 ;
    fichier = fopen(nomFichier(positionFichier),"r") ;
    while(fichier){

        if(positionFichier == 1){
        Start = malloc(sizeof(Restaurant));
        Start->next = NULL ;
        Start->prev = NULL;
        Start->Cat = NULL ;
        ptr = Start ;
    }else{
        ptr->next = malloc(sizeof(Restaurant));
        ptr->next->prev = ptr;
        ptr = ptr->next;
        ptr->next = NULL;
        ptr->Cat = NULL ;
    }
    fscanf(fichier,"%d",&ptr->note);
    fscanf(fichier,"%f",&ptr->moyenne_prix);
    fscanf(fichier,"%f",&ptr->distance);
    fgetc(fichier);
    fclear(ptr->adresse,&fichier,51);
   
    fclear(tabCAT,&fichier,5);

    i = 1 ;
    while(!feof(fichier) && strncasecmp(tabCAT,"CAT",3) == 0 ){
        if(i){
        ptr->Cat = malloc(sizeof(Categorie));
        ptrCAT = ptr->Cat ;
        ptrCAT->prev = NULL;
        ptrCAT->next = NULL;
        ptrCAT->Plat = NULL ;
        }else{
            ptrCAT->next = malloc(sizeof(Categorie));
            ptrCAT->next->prev = ptrCAT;
            ptrCAT = ptrCAT->next;
            ptrCAT->next = NULL;
            ptrCAT->Plat = NULL;
        }
        fclear(ptrCAT->nom,&fichier,31);
        fclear(tabPLAT,&fichier,6);
    
        i = 1 ;
        while(!feof(fichier) && strncasecmp(tabPLAT,"PLAT",4) == 0){
            if(i){
                ptrCAT->Plat = malloc(sizeof(Plat));
                ptrPLAT = ptrCAT->Plat;
                ptrPLAT -> prev = NULL;
                ptrPLAT -> next = NULL;
            }else{
                ptrPLAT -> next = malloc(sizeof(Plat));
                ptrPLAT->next->prev = ptrPLAT;
                ptrPLAT = ptrPLAT -> next ;
                ptrPLAT -> next = NULL;
            }
            fclear(ptrPLAT->nom,&fichier,31);
            fclear(ptrPLAT->desc,&fichier,101);
            fscanf(fichier,"%f",&ptrPLAT->prix);
            fgetc(fichier);
            fscanf(fichier,"%d",&ptrPLAT->annee);
            fgetc(fichier);
            fscanf(fichier,"%d",&ptrPLAT->mois);
            fgetc(fichier);
            fscanf(fichier,"%d",&ptrPLAT->jour);
            fgetc(fichier);
            i = 0 ;
            fclear(tabPLAT,&fichier,6);
        }
        strcpy(tabCAT,tabPLAT);
         i = 0 ;
    }
    
    fclose(fichier);
    positionFichier++;
    fichier = fopen(nomFichier(positionFichier),"r") ;
}
   
    do{
         
        do{
            printf("\t----Menu principale----\n\n");
            printf("1-Gestion des restaurants\n");
            printf("2-Sauvegarder\n");
            printf("3-Quitter\n");
            printf("\tVeuiller choisir: ");
            scanf("%d",&choix);
        }while(choix<1 || choix >3);
        switch(choix){
    /*choix1*/case 1 :
    do{
        do{
        printf("\n\t----Gestion des restaurants----\n\n");
        printf("1-Ajouter un restaurant\n");
        printf("2-Gerer les restaurants disponibles\n");
        printf("3-Tri des restaurants\n");
        printf("4-Supprimer un restaurant\n");
        printf("5-Menu principal\n");
        printf("\tVeuiller choisir: ");
                scanf("%d",&choix2);
        }while(choix2 <1 || choix2 >5);

            switch(choix2){

           /*choix2*/ case 1:
           Start = ajouterRestaurant(Start);
        
            break;

           /*choix2*/ case 2:
            if(!Start)
            printf("\n\tAUCUN RESTAURANT N'EST DISPONIBLE!\n\n");
            else{

                E1 :
              printf("\n");
                afficherRestaurant(Start,&taille);
                printf("\n");
                do{
                    printf("\tVeuillez choisir : ");
                scanf("%d",&choix3);
                }while(choix3 < 0 || choix3 > taille);

                if(!choix3)
                break;

                ptr = Start ;

                for(int a = 1 ; a < choix3 ; ptr = ptr -> next , a++);
            do{
                printf("\n");
                do{
                    printf("\n\t----Gestion de Restaurant %d----\n\n",choix3);
                    printf("1-Ajout plat\n");
                    printf("2-Modification des plats\n");
                    printf("3-Suppression des plats\n");
                    printf("4-Recherche des plats\n");
                    printf("5-Afficher tous les plats\n");
                    printf("6-Gerer les categories des plats\n");
                    printf("7-Option de tri personnalisees\n");
                    printf("8-Retour\n");
                    printf("\tVeuiller choisir: ");
                    scanf("%d",&choix4);
                    }while(choix4 < 1 || choix4 > 8);

            switch(choix4){

          /*choix4*/case 1 :
          ajouterPlat(ptr);
          calculePrixMoyenne(ptr);
            break;

           /*choix4*/case 2 :
           if(!ptr->Cat)
           printf("\n\tAUCUN PLAT N'EST DISPONIBLE!\n");
           else{
           modifierPlat(ptr->Cat);
           calculePrixMoyenne(ptr);}
            break;

           /*choix4*/case 3 :
           suppressionPlat(ptr);
           calculePrixMoyenne(ptr);
            break ;

           /*choix4*/case 4 :
           if(!ptr->Cat)
           printf("\n\tLISTE DES CATEGORIES EST VIDE !\n");
           else{
            do{
                do{
                    printf("\n\t----Recherche des plats----\n");
                    printf("1-Par nom du plat\n");
                    printf("2-Par categorie\n");
                    printf("3-Recherche avancee\n");
                    printf("4-Retour\n");
                    printf("Veuillez choisir: ");
                    scanf("%d",&choix13);
                }while(choix13 < 1 || choix13 > 4);
                switch(choix13){
                    case 1 :
                    printf("\n\n");
                    if(!afficherPlatparNom(ptr->Cat))
                    printf("\n\tPLAT NON TROUVE!\n");
                        
                    break;

                    case 2 :
                    if(!afficherPlatsparCategorie(ptr->Cat))
                    printf("\n\tCATEGORIE NON TROUVE!\n");
                    else
                    printf("\n\n");
                    break;

                    case 3 :
                    if(!afficherPlatsparDatte(ptr->Cat))
                    printf("AUCUN PLAT N'A ETE TROUVE AVEC CETTE DATTE!\n\n");
                    break;
                }

            }while(choix13 != 4);
           }
            break ;
            /*choix4*/case 5 :
            afficherCategorie(ptr->Cat,&taille);
            
            if(ptr->Cat)
            afficherTousLesPlats(ptr->Cat);
            break ;

           /*choix4*/case 6 :
           do{
           do{
            printf("\t----Gestion des categories de Restaurant %d----\n\n",choix3);
            printf("1-Afficher tous les categories\n");
            printf("2-Ajouter une categorie\n");
            printf("3-Modifier le nom d'une categorie\n");
            printf("4-Supprimer une categorie\n");
            printf("5-retour\n");
            printf("\tVeuiller choisir: ");
            scanf("%d",&choix6);
           }while(choix6 <1 || choix6 >5);

           switch(choix6){
            case 1:
            afficherCategorie(ptr->Cat,&taille);
            break;

            case 2:
            Start = ajouterCategorie(ptr);
            break;

            case 3:

            afficherCategorie(ptr->Cat,&taille);
            if(ptr->Cat){
            do{
                printf("\n\tVeuillez entrez la position de la categorie a modifier: \n");
                scanf("%d",&choix7);
            }while(choix7 <=0 || choix7 > taille);
            modifierNomCat(ptr->Cat,choix7);
        }
            break;

            case 4:
            afficherCategorie(ptr->Cat,&taille);
            if(!ptr->Cat)
            printf("\t\nLA LISTE DES CATEGORIES EST VIDE!\n\n");
            else{
            do{
                printf("\n\tVeuillez entrez le numero de la categorie a supprimer: ");
                scanf("%d",&choix8);
            }while(choix8 <= 0 || choix8 > taille);

            ptr = supprimerCat(ptr,choix8);
        }
            break;  
           }
        }while(choix6 != 5);
            break;
            /*choix4*/case 7 :
            do{
                do{
                    printf("\n\t----Tri personnalisees----\n\n");
                printf("1-Tri des Plats\n");
                printf("2-Retour\n");
                scanf("%d",&choix9);
            }while(choix9 < 1 || choix9 > 2 );
            printf("\n");
                switch (choix9){
                    case 1:
                    do{
                        do{
                            printf("\n\t----Tri des Plats----\n\n");
                            /*printf("1-Tri selon la date\n");*/
                            printf("1-Tri selon le prix\n");
                            printf("2-Retour\n");
                            printf("\tVeuillez choisir : ");
                            scanf("%d",&choix12);
                        }while(choix12 < 1 || choix12 > 2);
                            switch(choix12){
                                case 1 :
                                ptr->Cat->Plat = triPlat(ptr->Cat->Plat,1);
                                printf("\n\tLISTE TRIE AVEC SUCCES!\n\n");
                                break;
                                case 2 :
                                break;
                            }
                        }while(choix12 != 2);
                    break;
            }
            }while(choix9 != 2);
            break ;
           /*choix4*/case 8 :
           goto E1;
            break;
            }
           }while(1);
        }
                 break;
               /*choix2*/case 3 :
               if(!Start)
               printf("\t\nLISTE DES RESTAURANTS VIDE!\n");
               else if(!Start->next)
               printf("\nIL EXISTE 1 SEUL RESTAURANT\n\n");
               else{
               do{
                do{
                    printf("\n\t----Tri des Restaurants----\n\n");
                    printf("1-Tri selon le prix_moyenne des plats\n");
                    printf("2-Tri selon la surface\n");
                    printf("3-Tri selon la note\n");
                    printf("4-Retour\n");
                    printf("\n\tVeuillez choisir: ");
                    scanf("%d",&choix10);
                }while(choix10 < 1 || choix10 > 4);
                    switch(choix10){
                        case 1 :
                       Start =  tri(Start,1);
                        break;
                        case 2 :
                      Start = tri(Start,2);
                        break;
                        case 3 :
                       Start = tri(Start,3);
                       printf("%p\n",Start->prev);
                        break;
                    }
                    printf("\n\tLA LISTE DES RESTAURANTS A ETE TRIE EN SUCCES!\n");
                }while(choix10 != 4);
            }
                break;
                /*choix2*/case 4 :
                if(!Start)
                printf("\n\tAUCUN RESTAURANT N'EST DISPONIBLE\n\n");
                else{
                afficherRestaurant(Start,&taille);
                printf("\n");
                do{
                    printf("\tVeuiller choisir: ");
                scanf("%d",&choix3);
                }while(choix3 < 0 || choix3 > taille);
                if(!choix3)
                break;
                Start = supprimerRestaurant(Start,choix3);
                for(int a = 1 ; a <= taille ; a++){
                    remove(nomFichier(a));
                }
                Sauvegarde(&Start,&fichier);
                
                printf("\t\nRESTAURANT %d A ETE SUPPRIMER AVEC SUCCES!\n\n",choix3);
            }
            }
          }while(choix2 != 5); 
    break;
    case 2 :
    Sauvegarde(&Start,&fichier);
    break;
    /*choix 1*/case 3 :
    fclose(fichier);
    exit(0);
    }
    }while(1);
    return 0 ;
}