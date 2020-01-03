#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <string>

#include "window.h"
#include "texture.h"
#include "action.h"

bool Verificar_collision(
        SDL_Rect A,
        SDL_Rect B,
        SDL_Point A_VEL,
        SDL_Point* collition
    ){
    /// PARA A
    int A_IZQ = A.x;
    int A_DER = A.x + A.w;
    int A_ARR = A.y;
    int A_ABJ = A.y + A.h;
    /// PARA B
    int B_IZQ = B.x;
    int B_DER = B.x + B.w;
    int B_ARR = B.y;
    int B_ABJ = B.y + B.h;
    /// Restriccones
    if(A_VEL.x>0){
        return false;
    }

    if(
        (A_ABJ >= B_ARR) &&
        (A_ARR <= B_ABJ) &&
        (A_DER >= B_IZQ) &&
        (A_IZQ <= B_DER)
    ){
        if(
            (A_ABJ >= B_ARR) &&
            (A_ABJ <= B_ARR+(B.h/5)) 
        ){
            if(A_VEL.y > 0){
                collition->y = 1;
                collition->x = 1;
            }else{
                collition->x = 1;
            }
            return true;
        }
        if(
            (A_ARR <= B_ABJ) &&
            (A_ARR >= B_ABJ-(B.h/5)) 
        ){
            if(A_VEL.y < 0){
                collition->y = 1;
                collition->x = 1;
            }else{
                collition->x = 1;
            }
            return true;
        }
        if(
            (A_IZQ <= B_DER) &&
            (A_VEL.x < 0) 
        ){
            collition->x = 1;
            return true;
        }

    }
    return false;
}

bool Verificar_collision_IA(
        SDL_Rect A,
        SDL_Rect B,
        SDL_Point A_VEL,
        SDL_Point* collition
    ){
    /// PARA A
    int A_IZQ = A.x;
    int A_DER = A.x + A.w;
    int A_ARR = A.y;
    int A_ABJ = A.y + A.h;
    /// PARA B
    int B_IZQ = B.x;
    int B_DER = B.x + B.w;
    int B_ARR = B.y;
    int B_ABJ = B.y + B.h;
    /// Restriccones
    if(A_VEL.x<0){
        return false;
    }

    if(
        (A_ABJ >= B_ARR) &&
        (A_ARR <= B_ABJ) &&
        (A_DER >= B_IZQ) &&
        (A_IZQ <= B_DER)
    ){
        if(
            (A_ABJ >= B_ARR) &&
            (A_ABJ <= B_ARR+(B.h/5))
        ){
            if(A_VEL.y > 0){
                collition->y = 1;
                collition->x = 1;
            }else{
                collition->x = 1;
            }
            return true;
        }
        if(
            (A_ARR <= B_ABJ) &&
            (A_ARR >= B_ABJ-(B.h/5)) 
        ){
            if(A_VEL.y<0){
                collition->y = 1;
                collition->x = 1;
            }else{
                collition->x = 1;
            }
            return true;
        }
        if(
            (A_DER >= B_IZQ) &&
            (A_VEL.x > 0)
        ){
            collition->x = 1;
            return true;
        }

    }
    return false;
}

int main( int argc, char* args[] ){
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int TEXT_SIZE     =  40;
    
    int IA_Level  = 3;
    int VEL       = 4;
    
    int BALL_SIZE = 10;

    int PLAYER_WIDHT  =  20;
    int PLAYER_HEIGHT = 100;

    int score[2] = {0,0};

    enum entity{
        BALL,
        PLAYER1,
        PLAYER2
    };

    bool exit = false;

    std::string PATH_FONT = "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = "asset/icon.bmp";

    SDL_Rect    rect[3];
    SDL_Point  ball_vel;
    SDL_Point collition;

    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};

    rect[BALL].x =  SCREEN_WIDTH/2;
    rect[BALL].y = SCREEN_HEIGHT/2;
    rect[BALL].h = BALL_SIZE;
    rect[BALL].w = BALL_SIZE;
    ball_vel.x   =   VEL;
    ball_vel.y   = VEL/2;

    rect[PLAYER1].x = 0;
    rect[PLAYER1].y = 0;
    rect[PLAYER1].h = PLAYER_HEIGHT;
    rect[PLAYER1].w =  PLAYER_WIDHT;

    rect[PLAYER2].x = SCREEN_WIDTH - PLAYER_WIDHT;
    rect[PLAYER2].y = 0;
    rect[PLAYER2].h = PLAYER_HEIGHT;
    rect[PLAYER2].w =  PLAYER_WIDHT;

    Window window(
        "PONG",
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

            //Movement Player
            if(action->get_state(action->BUTTON_MOVE_UP)){
                rect[PLAYER1].y-=5;
            }else if(action->get_state(action->BUTTON_MOVE_DOWN)){
                rect[PLAYER1].y+=5;
            }

            if(rect[PLAYER1].y<0){
                rect[PLAYER1].y = 0;
            }else if(rect[PLAYER1].y + rect[PLAYER1].h>SCREEN_HEIGHT){
                rect[PLAYER1].y = SCREEN_HEIGHT - rect[PLAYER1].h;
            }

            // Movement computer
            rect[PLAYER2].y = rect[BALL].y-(rect[PLAYER2].h/2);

            if((rect[PLAYER2].y+(rect[PLAYER2].h/2))<rect[BALL].y){
                rect[PLAYER2].y = rect[PLAYER2].y + IA_Level;
            }
            if((rect[PLAYER2].y+(rect[PLAYER2].h/2))>rect[BALL].y){
                rect[PLAYER2].y = rect[PLAYER2].y - IA_Level;
            }
            if(rect[PLAYER2].y+((rect[PLAYER2].h+rect[BALL].h+4))>SCREEN_HEIGHT){
                rect[PLAYER2].y = SCREEN_HEIGHT-(rect[PLAYER2].h)-rect[BALL].h-4;
            }
            if(rect[PLAYER2].y<rect[BALL].h+4){
                rect[PLAYER2].y = rect[BALL].h+4;
            }

            // Movement ball
            rect[BALL].x += ball_vel.x;
            rect[BALL].y += ball_vel.y;
            
            if(rect[BALL].x + rect[BALL].w > SCREEN_WIDTH){
                score[PLAYER1 - 1]++;
                rect[BALL].x = SCREEN_WIDTH/2;
                rect[BALL].y = SCREEN_HEIGHT/2;

                ball_vel.y = VEL/2;
            }
            if(rect[BALL].x < 0){
                score[PLAYER2 - 1]++;
                rect[BALL].x = SCREEN_WIDTH/2;
                rect[BALL].y = SCREEN_HEIGHT/2;

                ball_vel.y = VEL/2;
            }

            collition.x = 0;
            collition.y = 0;

            // Bounce on screen
            if(rect[BALL].y + rect[BALL].h > SCREEN_HEIGHT){
                collition.y = 1;
            }
            if(rect[BALL].y<0){
                collition.y = 1;
            }

            // bounce on each elements
            Verificar_collision(rect[BALL], rect[PLAYER1], ball_vel, &collition);
            Verificar_collision_IA(rect[BALL], rect[PLAYER2], ball_vel, &collition);

            if( (collition.x == 1) || (collition.y == 1)){
                if(collition.x == 1){
                    ball_vel.x = -1*ball_vel.x;
                    collition.x = 0;
                }
                if(collition.y == 1){
                    ball_vel.y = -1*ball_vel.y;
                    collition.y = 0;
                }
            }

            // Print entitys
            window.set_render_draw_color(COLOR_WHITE);

            for(int i=0;i<3;i++){
                SDL_RenderFillRect(window.get_render(), &rect[i]);
            }


            // Print UI
            int width = 0;
            width = text_white.get_text_size(
                std::to_string(score[PLAYER1 - 1])
            ).w;

            text_white.render(
                SCREEN_WIDTH/2 - width, 0,
                std::to_string(score[PLAYER1 - 1])
            );

            width = text_white.get_text_size(
                std::to_string(score[PLAYER2 - 1])
            ).w;

            text_white.render(
                SCREEN_WIDTH/2, 0,
                std::to_string(score[PLAYER2 - 1])
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
