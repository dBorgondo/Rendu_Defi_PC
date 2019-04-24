#ifndef VALUES_H_INCLUDED
#define VALUES_H_INCLUDED
#define wWidth 1200
#define wHeight 800
typedef struct object Object;
typedef struct object{
    SDL_Texture* sprite;
    SDL_Rect cBox;
    int visible;
    int cliquable;
    int drag;
    int z;
    Object* suivant;
}object;

typedef struct liObject liObject;
struct liObject{
    Object* premier;
};

typedef struct coord{
    int x;
    int y;
}coord;


#endif // VALUES_H_INCLUDED
