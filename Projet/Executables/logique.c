#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "values.h"
#include "vues.h"
//Entree : renderer,objet clické, premier bouton
//Sortie : Renvoie 1 si le bon code est entrée et 0 sinon
//Commentaire : Fonction s'occupant de gérer la tapé du code sur le clavier de chiffres
int isGoodCode(SDL_Renderer* renderer,object* clickedObject,object* Button9){
    static int pressedButton=0;
    static int goodButton=0;
    int counter=0;
    char buffer[2];
    char path[50]="Assets/Images/button";
    object* actual=Button9;
    while((counter!=10)&&(actual!=clickedObject)){
        actual=actual->suivant;
        counter++;
    }
    if(actual==clickedObject){
        if(pressedButton>=2){
            if((9-counter==9)&&(goodButton==2)){
                    changeSprite(renderer,actual,(strcat((strcat(path,itoa(9-counter,buffer,10))),"_p.png")));
                    return 1;
                }
            (pressedButton)=0;
            goodButton=0;
            resetButtons(renderer,Button9);
        }
        else{
            (pressedButton)+=1;
                if((9-counter==0)&&((pressedButton)==1)){
                        (goodButton)+=1;
                    }
                if((9-counter==6)&&((pressedButton)==2)){
                        (goodButton)+=1;
                    }

            changeSprite(renderer,actual,(strcat((strcat(path,itoa(9-counter,buffer,10))),"_p.png")));
        }
    }
    return 0;
}



//Entree :
//Sortie :
//Commentaire : Initilaise toute la sdl
int initAll(){
        if (SDL_Init(SDL_INIT_EVERYTHING)!= 0) {
            printf("Erreur d'initialisation de la SDL: %s\n", SDL_GetError());
            return 0;
        }
        printf("Toutes les initialisations ont ete effectue avec succes.\n");
        return 1;
}

//Entree : fenetre à créé, renderer de la fenetre, largeur de la fenetre, hauteur de la fenetre, titre de la fenetre
//Sortie : Fenetre créé et 1 si créé avec succés, 0 sinon
//Commentaire : Créé une fenetre SDL
int createWindow(SDL_Window** window,SDL_Renderer** renderer,int Width,int Height,char* Title){
    if(!(window = SDL_CreateWindow(Title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,Width,Height,SDL_WINDOW_SHOWN))){
        printf("Erreur de creation de la fenetre : %s \n", SDL_GetError());
        return 0;
    }
    if(!(*renderer = SDL_CreateRenderer(window,-1,0))){
        printf("Erreur de creation du creation : %s \n", SDL_GetError());
        return 0;
    }
    return 1;
}
//Entree : Liste d'objet, Objet à supprimer
//Sortie : Liste avec objet supprimer
//Commentaire : Supprime l'objet donné de la liste donné
void deleteObject(liObject *liste,Object* deleted){
    Object *actuel = liste->premier;
    while((actuel->suivant!= NULL)&&(actuel->suivant!=deleted)){
        actuel = actuel->suivant;
    }
    if((actuel->suivant=NULL)){
        printf("Object not found !");
    }
    else{
        actuel->suivant=deleted->suivant;
        SDL_DestroyTexture(deleted->sprite);
        free(deleted);
    }
}

//Entree : enderer, chemin de l'image de l'objet,cordonnée en x, coordonée en y,visibilité de l'objet(0/1),est-il drag and dropable?(0/1),cliquable(0/1)
//Sortie : Objet créé
//Commentaire : Créé un objet
void makeObject(SDL_Renderer* renderer,object* Objet,char* spritePath, int x, int y,int visibility,int cliquable,int drag){
    Objet->cBox.x=x;
    Objet->cBox.y=y;
    Objet->visible=visibility;
    Objet->cliquable=cliquable;
    Objet->drag=drag;
    if(!(Objet->sprite = IMG_LoadTexture(renderer,spritePath))){
        printf("Erreur de chargement de l'image: %s \n", SDL_GetError());
    }
    SDL_QueryTexture(Objet->sprite, NULL, NULL, &Objet->cBox.w, &Objet->cBox.h);
}
//Entree : Coordonnée en x,Coordonnée en y,Objet
//Sortie : 1 si la coordonée est sur l'objet et 0 sinon
//Commentaire : Vérifie si une cordonnée se situe dans un objet

int isPointOnObject(int x,int y,object Objet){
    if((((x)<(Objet.cBox.x))||((x)>((Objet.cBox.x)+(Objet.cBox.w))))||(((y)<(Objet.cBox.y))||((y)>((Objet.cBox.y)+(Objet.cBox.h))))){
        return 0;
    }
    return 1;
}

//Entree : Liste d'objet,Coordonnée en x,Coordonnée en y
//Sortie : Objet trouvée comme étant cliqué ou NULL sinon
//Commentaire : Cherche dans la liste si un objet se situe sur les coordonnée indiqué
object* getClickedObject(liObject* liste,int x,int y){
    Object* objet = liste->premier;
    Object* upObjet = NULL;
    while(objet!= NULL){
        if(isPointOnObject(x,y,*(objet))&&(objet->cliquable)){
            upObjet=objet;
        }
        objet = objet->suivant;
    }
    return upObjet;
}
//Entree : objet1,objet2
//Sortie : 1 si les objets se chevauchent et 0 sinon
//Commentaire : Vérifie si des objets se chevauchent
int isObjectOnObject(object* Objet1,object* Objet2){
   if((Objet2->cBox.x >= Objet1->cBox.x + Objet1->cBox.w)
	|| (Objet2->cBox.x + Objet2->cBox.w <= Objet1->cBox.x)
	|| (Objet2->cBox.y >= Objet1->cBox.y + Objet1->cBox.h)
	|| (Objet2->cBox.y + Objet2->cBox.h <= Objet1->cBox.y)){
        return 0;
	}
   else{
        return 1;
   }
}
//Entree : liste d'objets, renderer, chemin de l'image de l'objet,cordonnée en x, coordonée en y,visibilité de l'objet(0/1),est-il drag and dropable?(0/1),cliquable(0/1)
//Sortie : Objet crée
//Commentaire : Crée un objet et l'ajoute à la liste
Object* createObject(liObject *liste,SDL_Renderer* renderer,char* spritePath, int x, int y,int visibility,int drag,int cliquable,int z){
    Object *nouveau=malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Object *precedent = liste->premier;
    nouveau->z=z;
    while((precedent->suivant!= NULL)&&((nouveau->z))>(precedent->suivant->z)){
            precedent = precedent->suivant;
        }
    if(precedent->suivant==NULL){
        nouveau->suivant=NULL;
    }
    else{
        nouveau->suivant=precedent->suivant;
    }
    precedent->suivant=nouveau;
    makeObject(renderer,nouveau,spritePath,x,y,visibility,cliquable,drag);
    return nouveau;
}
//Entree : renderer, chemin de l'image du premier objet, cordonnée en x, coordonée en y,visibilité de l'objet(0/1),est-il drag and dropable?(0/1),cliquable(0/1)
//Sortie : Liste initilisé et premier objet
//Commentaire : Intialise la liste avec le premier objet
liObject* initListObject(SDL_Renderer* renderer,char* spritePath, int x,int y,int visibility,int drag,int cliquable){
    liObject *liste = malloc(sizeof(*liste));
    Object *object = malloc(sizeof(*object));
    if (liste == NULL || object == NULL)
    {
        exit(EXIT_FAILURE);
    }
    makeObject(renderer,object,spritePath,x,y,visibility,cliquable,drag);
    object->suivant=NULL;
    liste->premier=object;
    return liste;
}
