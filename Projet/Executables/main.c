#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <string.h>
#include "values.h"
#include "logique.h"
#include "vues.h"

int main( int argc, char* args[] )
{
    int Gamestate= 100;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Renderer* renderer = NULL;
    SDL_Window* window = NULL;
    SDL_Event event;
    if(!(initAll())){
        return 0;
    }
    if(!(createWindow(&window,&renderer,wWidth,wHeight,"Briefcase"))){
        return 0;
    }
    //Mallette 1
    object* pickedObject=NULL;
    object* Mallette=NULL;
    liObject* lObjets=NULL;
    object* IntroDoc=NULL;
    object* InfoDel=NULL;
    object* M1BPlaque=NULL;
    object* M1RPlaque=NULL;
    object* M1LPlaque=NULL;
    object* Pierre1=NULL;
    object* Pierre3=NULL;
    object* Pierre4=NULL;
    object* Pierre5=NULL;
    object* Pierre6=NULL;
    object* Pierre8=NULL;
    object* Message1=NULL;
    object* Emplacement1=NULL;
    object* Emplacement3=NULL;
    object* Emplacement4=NULL;
    object* Emplacement5=NULL;
    object* Emplacement6=NULL;
    object* Emplacement8=NULL;
    object* Button0=NULL;
    object* Button1=NULL;
    object* Button2=NULL;
    object* Button3=NULL;
    object* Button4=NULL;
    object* Button5=NULL;
    object* Button6=NULL;
    object* Button7=NULL;
    object* Button8=NULL;
    object* Button9=NULL;
    object* Fir=NULL;
    object* West=NULL;
    object* Map_Icon=NULL;
    object* Map;
    object* Quit;
    object* Kill1;
    object* Fin;
    //
    int PierreFound=0;
    int FoundCode=0;
    lObjets=initListObject(renderer,"Assets/Images/table.png",0,0,1,1,0);
    Mallette=createObject(lObjets,renderer,"Assets/Images/mallette_1.png",100,100,1,0,1,1);
    IntroDoc=createObject(lObjets,renderer,"Assets/Images/intro_doc.png",wWidth/4,wHeight/4,1,1,1,2);
    Quit=createObject(lObjets,renderer,"Assets/Images/quit.png",1120,0,0,0,0,12);
    Kill1=createObject(lObjets,renderer,"Assets/Images/Kill1.png",333,91,0,0,0,14);
    Map=createObject(lObjets,renderer,"Assets/Images/map.png",0,0,0,0,0,10);
    Fin=createObject(lObjets,renderer,"Assets/Images/Fin.png",0,0,0,0,0,15);
    coord Shift;
    while(!(keys[SDL_SCANCODE_ESCAPE]))
    {
        SDL_WaitEvent(&event);

        switch(event.type){
            case SDL_MOUSEBUTTONDOWN :
                    //if(isPointOnObject(event.motion.x,event.motion.y,*(TestObjet))){
                    pickedObject=getClickedObject(lObjets,event.motion.x,event.motion.y);
                    if(pickedObject!=NULL){
                        if(event.type==SDL_MOUSEBUTTONDOWN ){
                            Shift.x=event.motion.x-pickedObject->cBox.x;
                            Shift.y=event.motion.y-pickedObject->cBox.y;
                            }
                }
            break;
            case SDL_MOUSEBUTTONUP :
                    pickedObject=NULL;
            break;
        }
        if((pickedObject!=NULL)&&((((event.motion.x)>0)&&((event.motion.x)<wWidth))&&(((event.motion.y)>0)&&((event.motion.y)<wWidth)))&&(pickedObject->drag==1)){
            pickedObject->cBox.x = (event.motion.x)-(Shift.x);
            pickedObject->cBox.y = (event.motion.y)-(Shift.y);
        }
        switch(Gamestate){
            case 10: //Phase de carte
                Map->visible=1;
                Map->cliquable=1;
                Quit->visible=1;
                Quit->cliquable=1;
                Kill1->drag=1;
                Kill1->cliquable=1;
                if(pickedObject==Fin){
                    return 1;
                }
                if(pickedObject==Kill1){
                    Fin->visible=1;
                    Fin->drag=1;
                    Fin->cliquable=1;
                }
                if(pickedObject==Quit){
                Map->visible=0;
                Map->cliquable=0;
                Quit->visible=0;
                Quit->cliquable=0;
                Kill1->drag=0;
                Kill1->cliquable=0;
                Kill1->visible=0;
                    Gamestate=113;
                }
            case 100 :
                if(pickedObject==IntroDoc){ //Ouverture doc d'intro
                    changeSprite(renderer,IntroDoc,"Assets/Images/intro_doc_open.png");
                    InfoDel=createObject(lObjets,renderer,"Assets/Images/info_delet.png",10,wHeight/4,1,0,0,2);
                    Gamestate=111;
                }
            break;
            case 111 :
                 if(pickedObject==IntroDoc){ //Lecture Doc
                        if(IntroDoc->cBox.x<0){
                            pickedObject=NULL;
                            deleteObject(lObjets,IntroDoc);
                            deleteObject(lObjets,InfoDel);
                            Gamestate=112;
                        }
                    }
            break;
            case 112 : //Ouverture Mallette
                if(pickedObject==Mallette){
                    Mallette->cliquable=0;
                    changeSprite(renderer,Mallette,"Assets/Images/mallette_1_empty.png");
                    Mallette->cBox.y=-500;
                    M1BPlaque=createObject(lObjets,renderer,"Assets/Images/M1_Bplaque.png",734,151,1,1,1,5);
                    M1RPlaque=createObject(lObjets,renderer,"Assets/Images/M1_Lplaque.png",M1BPlaque->cBox.x+M1BPlaque->cBox.w/2,318,1,1,1,5);
                    M1LPlaque=createObject(lObjets,renderer,"Assets/Images/M1_Lplaque.png",M1BPlaque->cBox.x+M1BPlaque->cBox.w/2-M1RPlaque->cBox.w,318,1,1,1,5);
                    Pierre1=createObject(lObjets,renderer,"Assets/Images/Pierre1.png",790,200,1,1,1,3);
                    Pierre3=createObject(lObjets,renderer,"Assets/Images/Pierre3.png",800,151,1,1,1,3);
                    Pierre4=createObject(lObjets,renderer,"Assets/Images/Pierre4.png",775,250,1,1,1,3);
                    Pierre5=createObject(lObjets,renderer,"Assets/Images/Pierre5.png",750,250,1,1,1,3);
                    Pierre6=createObject(lObjets,renderer,"Assets/Images/Pierre6.png",765,222,1,1,1,3);
                    Pierre8=createObject(lObjets,renderer,"Assets/Images/Pierre8.png",740,178,1,1,1,3);
                    Message1=createObject(lObjets,renderer,"Assets/Images/Message1.png",870,171,1,1,1,4);
                    Emplacement1=createObject(lObjets,renderer,"Assets/Images/Emplacement1.png",287,570,1,0,1,2);
                    Emplacement3=createObject(lObjets,renderer,"Assets/Images/Emplacement3.png",407,570,1,0,1,2);
                    Emplacement4=createObject(lObjets,renderer,"Assets/Images/Emplacement4.png",525,570,1,0,1,2);
                    Emplacement5=createObject(lObjets,renderer,"Assets/Images/Emplacement5.png",645,570,1,0,1,2);
                    Emplacement6=createObject(lObjets,renderer,"Assets/Images/Emplacement6.png",765,570,1,0,1,2);
                    Emplacement8=createObject(lObjets,renderer,"Assets/Images/Emplacement8.png",885,570,1,0,1,2);
                    Button0=createObject(lObjets,renderer,"Assets/Images/button0.png",394,347,1,0,1,2);
                    Button1=createObject(lObjets,renderer,"Assets/Images/button1.png",194,267,1,0,1,2);
                    Button2=createObject(lObjets,renderer,"Assets/Images/button2.png",264,267,1,0,1,2);
                    Button3=createObject(lObjets,renderer,"Assets/Images/button3.png",334,267,1,0,1,2);
                    Button4=createObject(lObjets,renderer,"Assets/Images/button4.png",194,347,1,0,1,2);
                    Button5=createObject(lObjets,renderer,"Assets/Images/button5.png",264,347,1,0,1,2);
                    Button6=createObject(lObjets,renderer,"Assets/Images/button6.png",334,347,1,0,1,2);
                    Button7=createObject(lObjets,renderer,"Assets/Images/button7.png",194,427,1,0,1,2);
                    Button8=createObject(lObjets,renderer,"Assets/Images/button8.png",264,427,1,0,1,2);
                    Button9=createObject(lObjets,renderer,"Assets/Images/button9.png",334,427,1,0,1,2);
                    Map_Icon=createObject(lObjets,renderer,"Assets/Images/Icon_map.png",5,5,1,0,1,3);
                    Gamestate=113;
                }
            break;
            case 113 ://Gameplay Mallette 1
                if(pickedObject==Map_Icon){
                    Gamestate=10;
                }
                if(pickedObject==M1BPlaque){
                    M1BPlaque->cBox.x=734;
                    if((M1BPlaque->cBox.y<151)||(((isObjectOnObject(M1BPlaque,M1RPlaque))||(isObjectOnObject(M1BPlaque,M1LPlaque))))){
                        M1BPlaque->cBox.y=151;
                    }
                    else if(M1BPlaque->cBox.y>317){
                        M1BPlaque->cBox.y=318;
                    }
                }
                else if(pickedObject==M1RPlaque){
                    M1RPlaque->cBox.y=318;
                    if((M1RPlaque->cBox.x)>1018){
                        M1RPlaque->cBox.x=1018;
                    }
                    else if(isObjectOnObject(M1RPlaque,M1BPlaque)){
                        M1RPlaque->cBox.x=M1BPlaque->cBox.x+M1BPlaque->cBox.w;
                    }
                    else if((M1LPlaque->cBox.x+M1LPlaque->cBox.w)>(M1RPlaque->cBox.x)){
                        M1RPlaque->cBox.x=(M1LPlaque->cBox.x+M1LPlaque->cBox.w);
                    }
                }
                else if(pickedObject==M1LPlaque){
                    M1LPlaque->cBox.y=318;
                    if(M1LPlaque->cBox.x<693){
                        M1LPlaque->cBox.x=693;
                    }
                    else if(isObjectOnObject(M1LPlaque,M1BPlaque)){
                        M1LPlaque->cBox.x=M1BPlaque->cBox.x-M1LPlaque->cBox.w;
                    }
                    else if((M1LPlaque->cBox.x+M1LPlaque->cBox.w)>(M1RPlaque->cBox.x)){
                        M1LPlaque->cBox.x=(M1RPlaque->cBox.x)-(M1LPlaque->cBox.w);
                    }
                }
                else if(pickedObject==Message1){
                    changeSprite(renderer,Message1,"Assets/Images/Message_open1.png");
                    if(Message1->cBox.x<0){
                            pickedObject=NULL;
                            deleteObject(lObjets,Message1);
                    }
                }
                else if((FoundCode==0)&&(pickedObject!=NULL)&&(isGoodCode(renderer,pickedObject,Button9))){
                    West=createObject(lObjets,renderer,"Assets/Images/West.png",600,151,1,1,1,2);
                    FoundCode=1;
                }
                if((isObjectOnObject(Emplacement1,Pierre1)&&(PierreFound==0))//Teste pour voir si les pierres sont dans le bonne ordre
                    && (isObjectOnObject(Emplacement1,Pierre1))
                    && (isObjectOnObject(Emplacement3,Pierre3))
                    && (isObjectOnObject(Emplacement4,Pierre4))
                    && (isObjectOnObject(Emplacement5,Pierre5))
                    && (isObjectOnObject(Emplacement6,Pierre6))
                    && (isObjectOnObject(Emplacement8,Pierre8))){
                        changeSprite(renderer,Emplacement1,"Assets/Images/Emplacement1_g.png");
                        changeSprite(renderer,Emplacement3,"Assets/Images/Emplacement3_g.png");
                        changeSprite(renderer,Emplacement4,"Assets/Images/Emplacement4_g.png");
                        changeSprite(renderer,Emplacement5,"Assets/Images/Emplacement5_g.png");
                        changeSprite(renderer,Emplacement6,"Assets/Images/Emplacement6_g.png");
                        changeSprite(renderer,Emplacement8,"Assets/Images/Emplacement8_g.png");
                        Fir =createObject(lObjets,renderer,"Assets/Images/Fir.png",885,510,1,0,0,2);
                        PierreFound=1;
                    }
            break;

        }
        SDL_SetRenderDrawColor(renderer,255,255,0,255);
        SDL_RenderClear(renderer);
        drawObjects(renderer,lObjets);
        SDL_RenderPresent(renderer);
    }
    return 1;
}



