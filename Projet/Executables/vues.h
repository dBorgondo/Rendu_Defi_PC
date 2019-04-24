#ifndef VUES_H_INCLUDED
#define VUES_H_INCLUDED
extern int drawImage(SDL_Renderer* renderer,SDL_Texture* img, int x, int y);
extern int drawObjects(SDL_Renderer* renderer,liObject *liste);
extern void changeSprite(SDL_Renderer* renderer,object* Objet,char* spritePath);
extern void resetButtons (SDL_Renderer* renderer,object* Button9);
#endif // VUES_H_INCLUDED
