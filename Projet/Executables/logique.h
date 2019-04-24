#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
extern int isGoodCode(SDL_Renderer* renderer,object* clickedObject,object* Button9);
extern int initAll();
extern int createWindow(SDL_Window** window,SDL_Renderer** renderer,int Width,int Height,char* Title);
extern int createWindow(SDL_Window** window,SDL_Renderer** renderer,int Width,int Height,char* Title);
extern Object* createObject(liObject *liste,SDL_Renderer* renderer,char* spritePath, int x, int y,int visibility,int drag,int cliquable,int z);
extern void makeObject(SDL_Renderer* renderer,object* Objet,char* spritePath, int x, int y,int visibility,int cliquable,int drag);
extern int isPointOnObject(int x,int y,object Objet);
extern object* getClickedObject(liObject* liste,int x,int y);
int isObjectOnObject(object* Objet1,object* Objet2);
extern liObject* initListObject(SDL_Renderer* renderer,char* spritePath, int x,int y,int visibility,int drag,int cliquable);
extern void deleteObject(liObject *liste,Object* deleted);
#endif // LOGIQUE_H_INCLUDED
