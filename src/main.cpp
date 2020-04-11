#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <string>
#include <stdlib.h>
#include <ctime>

#include "window.hpp"
#include "texture.hpp"
#include "action.hpp"
#include "entity.hpp"

bool check_collition(
        SDL_Rect A,
        SDL_Rect B
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
    if(
        (A_ABJ >= B_ARR) &&
        (A_ARR <= B_ABJ) &&
        (A_DER >= B_IZQ) &&
        (A_IZQ <= B_DER) 
    ){
        return true;
    }
    return false;
}

int main( int argc, char* args[] ){
    srand (time(0));
    int SCREEN_WIDTH  = 640;
    int SCREEN_HEIGHT = 480;
    int TEXT_SIZE =  SCREEN_HEIGHT/12;
    
    int VEL       = SCREEN_HEIGHT/100;
    int BALL_SIZE = SCREEN_HEIGHT/50;

    int PLAYER_WIDHT  = SCREEN_HEIGHT/50;
    int PLAYER_HEIGHT = SCREEN_HEIGHT/6;
    int PLAYER_PADING = SCREEN_HEIGHT/10;
    
    int WIN_CONDITION = 3;
    int score[2] = {0,0};



    Uint32 start_view_timer = 600;

 
    bool exit  = false;
    bool pause = false;

    Uint32 ref_timer = 0;
 
    enum entity{
        BALL,
        PLAYER1,
        PLAYER2
    };
    
    enum views{
        VIEW_START,
        VIEW_GAME,
        VIEW_GAME_OVER
    };
    
    enum game_over_options{
        YES,
        NO,
        TOTAL_OPTIONS
    };
    
    int view_index = VIEW_START;
    int game_over_selector = NO;
    
    std::string GAME_NAME = "PONG";
    std::string PATH(SDL_GetBasePath());

    std::string PATH_FONT = PATH + "asset/font/LiberationMono-Regular.ttf";
    std::string PATH_ICON = PATH + "asset/icon.bmp";

    SDL_Color COLOR_BLACK = {0x00, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_RED   = {0xFF, 0x00, 0x00, 0xFF};
    SDL_Color COLOR_GREEN = {0x00, 0xFF, 0x00, 0xFF};
    SDL_Color COLOR_BLUE  = {0x00, 0x00, 0xFF, 0xFF};
    SDL_Color COLOR_WHITE = {0xFF, 0xFF, 0xFF, 0xFF};

    Entity ball;
    Entity player1;
    Entity player2;
    
    ball.init(
        SCREEN_WIDTH/2, SCREEN_HEIGHT/2,
        BALL_SIZE, BALL_SIZE, {VEL, VEL/2},
        COLOR_WHITE
    );

    ball.reset_direction();


    player1.init(
        PLAYER_PADING, SCREEN_HEIGHT/2 - PLAYER_HEIGHT,
        PLAYER_HEIGHT, PLAYER_WIDHT, {VEL, VEL},
        COLOR_WHITE
    );
    
    player2.init(
        SCREEN_WIDTH - PLAYER_WIDHT - PLAYER_PADING, SCREEN_HEIGHT/2 - PLAYER_HEIGHT,
        PLAYER_HEIGHT, PLAYER_WIDHT, {VEL, VEL},
        COLOR_WHITE
    );
    
    Window window(
        GAME_NAME.c_str(),
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
    
    TextureText text_red(
        window.get_render(),
        PATH_FONT,
        COLOR_RED,
        TEXT_SIZE
    );
    
    Action* action = Action::get_instance();
    action->init(
        SDL_SCANCODE_Z,      // BUTTON_ACTION
        SDL_SCANCODE_X,      // BUTTON_CANCEL
        SDL_SCANCODE_RETURN, // BUTTON_START
        SDL_SCANCODE_UP,     // BUTTON_MOVE_UP
        SDL_SCANCODE_DOWN,   // BUTTON_MOVE_DOWN
        SDL_SCANCODE_LEFT,   // BUTTON_MOVE_LEFT
        SDL_SCANCODE_RIGHT   // BUTTON_MOVE_RIGHT
    );
    
    /** Record
    int img_index = 0;
    char buffer[256];
    SDL_Rect thing = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    **/
    ref_timer = SDL_GetTicks();
    while(exit == false){
        if(window.check_exit()){
            exit = true;
        }else{
            window.clear_screen();
                        
            // Logic
            switch(view_index){
                case VIEW_GAME:{
                    if(pause){
                        if(action->check_action(action->BUTTON_START)){
                            pause = false;
                        }
                    }else{
                        //PLAYER
                        if(action->get_state(action->BUTTON_MOVE_UP)){
                            player1.move_up();
                        }else if(action->get_state(action->BUTTON_MOVE_DOWN)){
                            player1.move_down();
                        }else{
                            player1.stop();
                        }

                        if(action->check_action(action->BUTTON_START)){
                            pause = true;
                        }

                        if((player1.y <= 0) && (player1.speed.y < 0)){
                            player1.stop_y();
                            player1.y = 0;
                        }else if(
                            (player1.y + player1.h >= SCREEN_HEIGHT) &&
                            (player1.speed.y > 0)   
                        ){
                            player1.stop_y();
                            player1.y = SCREEN_HEIGHT - player1.h;
                        }

                        // PC
                        if (ball.speed.x>0){
                            if(player2.y + (player2.h/2) + 20 < ball.y){
                                player2.move_down();
                            }else if(player2.y + (player2.h/2) - 20 > ball.y){
                                player2.move_up();
                            }else{
                                player2.stop();
                            }
                        }else{
                            player2.stop();
                        }

                        if(
                            (player2.y + player2.h >= SCREEN_HEIGHT) &&
                            (player2.speed.y > 0)
                        ){
                            player2.stop_y();
                            player2.y = SCREEN_HEIGHT - player2.h;
                        }else if((player2.y <= 0) && (player2.speed.y < 0)){
                            player2.stop_y();
                            player2.y = 0;
                        }
                        // ball movement
                        
                        if(ball.x + ball.w > SCREEN_WIDTH){
                            printf("HAI\n");
                            score[PLAYER1 - 1]++;
                            ball.x = SCREEN_WIDTH/2;
                            ball.y = rand() % SCREEN_HEIGHT;
                            ball.reset_direction();
                        }
                        if(ball.x < 0){
                            printf("IEE\n");
                            score[PLAYER2 - 1]++;
                            ball.x = SCREEN_WIDTH/2;
                            ball.y = rand() % SCREEN_HEIGHT;
                            ball.reset_direction();
                        }

                        // Bounce on screen
                        if(ball.y + ball.h > SCREEN_HEIGHT){
                            ball.move_up();
                        }
                        if(ball.y < 0){
                            ball.move_down();
                        }

                        // bounce on each elements

                        if(ball.speed.x < 0){
                            if(
                                check_collition(
                                    ball.get_rect(),
                                    player1.get_rect()
                                )
                            ){
                                ball.move_right();
                            }
                        }

                        if(ball.speed.x > 0){
                            if(
                                check_collition(
                                    ball.get_rect(),
                                    player2.get_rect()
                                )
                            ){
                                ball.move_left();
                            }
                        }

                        if(
                            (score[PLAYER1 - 1] >= WIN_CONDITION) ||
                            (score[PLAYER2 - 1] >= WIN_CONDITION)
                        ){
                            view_index = VIEW_GAME_OVER;
                            game_over_selector = NO;
                        }
                    }
                    break;
                }
                
                case VIEW_START:{
                    if(action->check_action(action->BUTTON_START)){
                        view_index = VIEW_GAME;
                    }
                    break;
                }
                
                case VIEW_GAME_OVER:{
                    if(action->check_action(action->BUTTON_START)){
                        if(game_over_selector==NO){
                            view_index = VIEW_START;
                            score[PLAYER1 - 1] = 0;
                            score[PLAYER2 - 1] = 0;
                            ball.x = SCREEN_WIDTH/2;
                            ball.y = rand() % SCREEN_HEIGHT;
                            ball.reset_direction();
                        }else{
                            exit = true;
                        }
                    }else if(action->check_action(action->BUTTON_MOVE_UP)){
                        game_over_selector++;
                        if(game_over_selector >= TOTAL_OPTIONS){
                            game_over_selector = 0;
                        }
                    }else if(action->check_action(action->BUTTON_MOVE_DOWN)){
                        game_over_selector--;
                        if(game_over_selector < 0){
                            game_over_selector = TOTAL_OPTIONS-1;
                        }
                    }
                    break;
                }
            }


            // Update world
            if( !pause && view_index==VIEW_GAME){
                ball.update();
                player1.update();
                player2.update();
            }

            // Render            
            switch(view_index){
                case VIEW_START:{
                   text_white.render(
                        SCREEN_WIDTH/2, TEXT_SIZE,
                        GAME_NAME,
                        text_white.CENTER
                    );


                    if(SDL_GetTicks() - ref_timer < start_view_timer){
                        text_white.render(
                            SCREEN_WIDTH/2, SCREEN_HEIGHT - 2*TEXT_SIZE,
                            "PRESS START",
                            text_white.CENTER
                        );
                    }else if(SDL_GetTicks() - ref_timer > 2*start_view_timer){
                        ref_timer = SDL_GetTicks();
                    }
                    break;

                }
                case VIEW_GAME:{
                    // Draw entitys
                    window.draw_rectangle(ball.get_rect(), COLOR_WHITE);
                    window.draw_rectangle(player1.get_rect(), COLOR_WHITE);
                    window.draw_rectangle(player2.get_rect(), COLOR_WHITE);

                    // Draw UI
                    text_white.render(
                        SCREEN_WIDTH/2-  10, 0,
                        std::to_string(score[PLAYER1 - 1]),
                        text_white.LEFT
                    );

                    text_white.render(
                        SCREEN_WIDTH/2 + 10, 0,
                        std::to_string(score[PLAYER2 - 1])
                    );
                    
                    window.draw_line(
                        {SCREEN_WIDTH/2, 0},
                        {SCREEN_WIDTH/2, SCREEN_HEIGHT},
                        COLOR_WHITE
                    );
                    
                    if(pause){
                        text_white.render(
                            SCREEN_WIDTH/2,
                            SCREEN_HEIGHT/2 - TEXT_SIZE/2,
                            "PAUSE",
                            text_white.CENTER
                        );
                    }
                    break;
                }
                case VIEW_GAME_OVER:{
                    text_white.render(
                        SCREEN_WIDTH/2, TEXT_SIZE,
                        "GAME OVER",
                        text_white.CENTER
                    );

                    text_white.render(
                        SCREEN_WIDTH/2, 3*TEXT_SIZE,
                        "Quit?",
                        text_white.CENTER
                    );

                    if(game_over_selector==YES){
                        text_red.render(
                            SCREEN_WIDTH/2, 5*TEXT_SIZE,
                            "Yes",
                            text_red.CENTER
                        );
                    }else{
                        text_white.render(
                            SCREEN_WIDTH/2, 5*TEXT_SIZE,
                            "Yes",
                            text_white.CENTER
                        );
                    }
                    
                    if(game_over_selector==NO){
                        text_red.render(
                            SCREEN_WIDTH/2, 6*TEXT_SIZE,
                            "No",
                            text_red.CENTER
                        );
                    }else{
                        text_white.render(
                            SCREEN_WIDTH/2, 6*TEXT_SIZE,
                            "No",
                            text_white.CENTER
                        );
                    }

                    break;
                }
            }

            window.update_screen();
            
            SDL_Surface *sshot = SDL_CreateRGBSurface(0,
                SCREEN_WIDTH, SCREEN_HEIGHT, 32,
                0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000
            );


            SDL_RenderReadPixels(
                window.get_render(),
                &thing,
                SDL_PIXELFORMAT_ARGB8888,
                sshot->pixels, sshot->pitch
            );
            

            /** Record
            sprintf(buffer, "%06d", img_index);
            std::string str(buffer);
            std::string str_thing = "cap/cap_"+ str + ".bmp";
            SDL_SaveBMP(sshot, str_thing.c_str());
            SDL_FreeSurface(sshot);
            img_index++;
            **/
        }

    }
    return 0;
}
