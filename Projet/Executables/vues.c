#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "values.h"
#include "logique.h"
//Entree :renderer,Image à dessiner,coordonnée en x et en y
//Sortie : Image dessiné
//Commentaire : Dessine une image à l'ecran
int drawImage(SDL_Renderer* renderer,SDL_Texture* img, int x, int y){
    int Width=0;
    int Height=0;
    SDL_Rect canva;
    SDL_QueryTexture(img, NULL, NULL, &Width, &Height);
    canva.x = x;
    canva.y = y;
    canva.w = Width;
    canva.h = Height;
    SDL_RenderCopy(renderer, img, NULL, &canva);
    return 1;
}
//Entree : renderer, liste d'objet
//Sortie : Objets dessinée
//Commentaire : Dessines tout les objets de la liste chainée d'objets
void drawObjects(SDL_Renderer* renderer,liObject *liste){
    Object *objet = liste->premier;
    while((objet!= NULL)){
        if(objet->visible){
            (drawImage(renderer,objet->sprite,objet->cBox.x,objet->cBox.y));
        }
        objet = objet->suivant;
    }
}
//Entree : renderer,objet et chemin vers une image
//Sortie : Objet dont l'hitbox et l'image sont modifié
//Commentaire : Modifie l'image d'un objet et modifie la hitbox en fonction de l'image donnee
void changeSprite(SDL_Renderer* renderer,object* Objet,char* spritePath){
    if(!(Objet->sprite = IMG_LoadTexture(renderer,spritePath))){
        printf("Erreur de chargement de l'image: %s \n", SDL_GetError());
    }
    SDL_QueryTexture(Objet->sprite, NULL, NULL, &Objet->cBox.w, &Objet->cBox.h);
}
//Entree : renderer, premier bouton des boutons
//Sortie : Tous les boutons avec leurs sprite non brillant
//Commentaire : Remet tout les boutons à leurs sprites de bases
void resetButtons (SDL_Renderer* renderer,object* Button9){
            char buffer[2];
            char path[40]="Assets/Images/button";
            object* actual=Button9;
            int counter=0;
            for(counter=0;counter<=9;counter++){
                strcpy(path,"Assets/Images/button");
                changeSprite(renderer,actual,(strcat((strcat(path,itoa(9-counter,buffer,10))),".png")));
                actual=actual->suivant;
            }
}
