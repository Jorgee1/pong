#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <string>

#include "window.h"
#include "texture.h"
#include "action.h"



int AnchoP = 640,LargoP = 480,Cor_x = AnchoP/2,Cor_y = LargoP/2,Vel = 4,Vel_x = 5,Vel_y = Vel/2,MCor_x = 50,MCor_y;

int ContVel = 0,TCor_x = AnchoP-70,TCor_y = LargoP/2,IA_Level = 3,Temp_IMG;



/*
void SDL_Cuadrado(int x,int y,int h,int w){

    SDL_Rect Cuadrado;
    Cuadrado.x = x;
    Cuadrado.y = y;
    Cuadrado.h = h;
    Cuadrado.w = w;
    SDL_SetRenderDrawColor(RenderP,0xFF,0,0,0xFF);
    SDL_RenderFillRect(RenderP,&Cuadrado);
}

void cargador(){
    Font = TTF_OpenFont("FONTS/arial.ttf",20);
    SDL_ShowCursor(SDL_DISABLE);
    Puntaje1.Cargar_Texto(to_string(Puntaje[0]),Blanco);
    Puntaje2.Cargar_Texto(to_string(Puntaje[1]),Blanco);
    Temp_IMG = Puntaje1.GetAncho();
}

void Reset(){
    Cor_x = AnchoP/2,Cor_y = LargoP/2;
    Vel_y = Vel/2;
    ContVel = 0;
}

bool Verificar_collision(int A_x,int A_y,int B_x,int B_y,int Detect[]){
    int A_IZQ,A_DER,A_ARR,A_ABJ;
    int B_IZQ,B_DER,B_ARR,B_ABJ;

    /// PARA A
    A_IZQ = A_x;
    A_DER = A_x + rect[0].w;
    A_ARR = A_y;
    A_ABJ = A_y + rect[0].h;
    /// PARA B
    B_IZQ = B_x;
    B_DER = B_x + rect[1].w;
    B_ARR = B_y;
    B_ABJ = B_y + rect[1].h;
    /// Restriccones
    if(Vel_x>0){
        return false;
    }
    if((A_ABJ>=B_ARR)&&(A_ARR<=B_ABJ)&&(A_DER>=B_IZQ)&&(A_IZQ<=B_DER)){
            if( (A_ABJ>=B_ARR) && (A_ABJ<=(B_ARR+(rect[1].h/5))) ){
                if(Vel_y>0){
                    Detect[1] = 1;
                    Detect[0] = 1;
                }else{
                    Detect[0] = 1;
                }
                ContVel = 1;
                return true;
            }
            if( (A_ARR<=B_ABJ) && (A_ARR>=(B_ABJ-(rect[1].h/5))) ){
                if(Vel_y<0){
                    Detect[1] = 1;
                    Detect[0] = 1;
                }else{
                    Detect[0] = 1;
                }
                ContVel = 1;
                return true;
            }
            if( (A_IZQ<=B_DER) && (Vel_x<0) ){
                Detect[0] = 1;
                ContVel = 2;
                return true;
            }

    }
    return false;
}

bool Verificar_collision_IA(int A_x,int A_y,int B_x,int B_y,int Detect[]){
    int A_IZQ,A_DER,A_ARR,A_ABJ;
    int B_IZQ,B_DER,B_ARR,B_ABJ;

    /// PARA A
    A_IZQ = A_x;
    A_DER = A_x + rect[0].w;
    A_ARR = A_y;
    A_ABJ = A_y + rect[0].h;
    /// PARA B
    B_IZQ = B_x;
    B_DER = B_x + rect[2].w;
    B_ARR = B_y;
    B_ABJ = B_y + rect[2].h;
    /// Restriccones
    if(Vel_x<0){
        return false;
    }
    if((A_ABJ>=B_ARR)&&(A_ARR<=B_ABJ)&&(A_DER>=B_IZQ)&&(A_IZQ<=B_DER)){
            if( (A_ABJ>=B_ARR) && (A_ABJ<=(B_ARR+(rect[2].h/3)))  ){
                if(Vel_y>0){
                    Detect[1] = 1;
                    Detect[0] = 1;
                }else{
                    Detect[0] = 1;
                }
                ContVel = 1;
                return true;
            }
            if( (A_ARR<=B_ABJ) && (A_ARR>=(B_ABJ-(rect[2].h/3))) ){
                if(Vel_y<0){
                    Detect[1] = 1;
                    Detect[0] = 1;
                }else{
                    Detect[0] = 1;
                }
                ContVel = 1;
                return true;
            }
            if( (A_DER>=B_IZQ) && (Vel_x>0) ){
                Detect[0] = 1;
                ContVel = 2;
                return true;
            }

    }
    return false;
}

bool Colision(int Dim,int Detect[2]){
    Verificar_collision(rect[0].x,rect[0].y,rect[1].x,rect[1].y,Detect);
    Verificar_collision_IA(rect[0].x,rect[0].y,rect[2].x,rect[2].y,Detect);
    if(Cor_x>(AnchoP-Dim)){
        //Detect[0] = 1;
        Puntaje[0]++;
        Reset();
    }
    if(Cor_x<0){
        //Detect[0] = 1;
        Puntaje[1]++;
        Reset();
    }
    if(Cor_y>(LargoP-Dim)){
        Detect[1] = 1;
    }
    if(Cor_y<0){
        Detect[1] = 1;
    }


    if(Detect[0] == 1){
        return true;
    }
    if(Detect[1] == 1){
        return true;
    }
    return false;
}

void Mover(){
    SDL_GetMouseState(NULL,&MCor_y);
    rect[1].h = 100;
    rect[1].w = 20;
    if(MCor_y+(rect[1].h/2)+4+rect[0].h>LargoP){
        MCor_y = LargoP-(rect[1].h/2)-4-rect[0].h;
    }
    if(MCor_y-(rect[1].h/2)-4-rect[0].h<0){
        MCor_y = rect[1].h/2+4+rect[0].h;
    }
    rect[1].x = MCor_x;
    rect[1].y = MCor_y-(rect[1].h/2);
    SDL_RenderFillRect(RenderP,&rect[1]);
}

void IA(){
    rect[2].h = 100;
    rect[2].w = 20;
    rect[2].x = AnchoP-70;
    rect[2].y = rect[0].y-(rect[2].h/2);
    if((TCor_y+(rect[2].h/2))<rect[0].y){
        TCor_y = TCor_y + IA_Level;
    }
    if((TCor_y+(rect[2].h/2))>rect[0].y){
        TCor_y = TCor_y - IA_Level;
    }
    if(TCor_y+((rect[2].h+rect[0].h+4))>LargoP){
        TCor_y = LargoP-(rect[2].h)-rect[0].h-4;
    }
    if(TCor_y<rect[0].h+4){
        TCor_y = rect[0].h+4;
    }
    rect[2].x = TCor_x;
    rect[2].y = TCor_y;
    SDL_RenderFillRect(RenderP,&rect[2]);
}

void Impresor_P(){
    int Col_XoY[2] = {0,0};
    SDL_SetRenderDrawColor(RenderP,0xFF,0xFF,0xFF,0xFF);
    Puntaje1.Cargar_Texto(std::to_string(Puntaje[0]),Blanco);
    Puntaje2.Cargar_Texto(std::to_string(Puntaje[1]),Blanco);
    rect[0].h = 10;
    rect[0].w = 10;
    rect[0].x = Cor_x;
    rect[0].y = Cor_y;

    Cor_x = Cor_x + Vel_x;
    Cor_y = Cor_y + Vel_y;

    Mover();
    IA();
    switch(ContVel){
        case 1: if((Vel_y == (Vel/2))||(Vel_y == -(Vel/2))){Vel_y = Vel_y*2;}break;
        case 2: if((Vel_y == (Vel))  || (Vel_y == -(Vel))){Vel_y = Vel_y/2;}break;
    }
    if(Colision(rect[0].h,Col_XoY) == true){
        if(Col_XoY[0] == 1){
            Vel_x = -1*Vel_x;
            Col_XoY[0] = 0;
        }
        if(Col_XoY[1] == 1){
            Vel_y = -1*Vel_y;
            Col_XoY[1] = 0;
        }
    }
    SDL_SetRenderDrawColor(RenderP,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderFillRect(RenderP,&rect[0]);
}
*/

int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int TEXT_SIZE     =  40;

    int SCORE[2] = {0,0};
    
    enum entity{
        BALL,
        PLAYER1,
        PLAYER2
    };

    bool exit = false;

    std::string PATH_FONT = "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = "asset/icon.bmp";

    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};

    SDL_Rect rect[3];

    rect[BALL].x = Cor_x;
    rect[BALL].y = Cor_y;
    rect[BALL].h = 10;
    rect[BALL].w = 10;

    rect[PLAYER1].x = MCor_x;
    rect[PLAYER1].y = MCor_y;
    rect[PLAYER1].h = 100;
    rect[PLAYER1].w = 20;

    rect[PLAYER2].x = TCor_x;
    rect[PLAYER2].y = TCor_y;
    rect[PLAYER2].h = 100;
    rect[PLAYER2].w = 20;

    Window window(
        "Window",
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        COLOR_BLACK
    );
    window.set_icon(PATH_ICON);

    TextureText text_white(
        window.get_render(),
        PATH_FONT,
        COLOR_WHITE,
        TEXT_SIZE
    );

    Action* action = Action::get_instance();
    action->init(
        SDL_SCANCODE_Z,
        SDL_SCANCODE_X,
        SDL_SCANCODE_RETURN,
        SDL_SCANCODE_UP,
        SDL_SCANCODE_DOWN,
        SDL_SCANCODE_LEFT,
        SDL_SCANCODE_RIGHT
    );

    //cargador();

    while(exit == false){
        if(window.check_exit()){
            exit = true;
        }else{
            window.clear_screen();





            //Impresor_P();

            // Print Characters
            window.set_render_draw_color(COLOR_WHITE);

            for(int i=0;i<3;i++){
                SDL_RenderFillRect(window.get_render(), &rect[i]);
            }


            // Print UI
            int width = 0;
            width = text_white.get_text_size(
                std::to_string(SCORE[0])
            ).w;

            text_white.render(
                SCREEN_WIDTH/2 - width, 0,
                std::to_string(SCORE[0])
            );

            width = text_white.get_text_size(
                std::to_string(SCORE[1])
            ).w;

            text_white.render(
                SCREEN_WIDTH/2, 0,
                std::to_string(SCORE[1])
            );
            



            SDL_RenderDrawLine(
                window.get_render(),
                SCREEN_WIDTH/2, 0,
                SCREEN_WIDTH/2, SCREEN_HEIGHT
            );
            window.update_screen();
        }
    }
    return 0;
}








