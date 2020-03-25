#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include <string>
#include <stdlib.h>
#include <ctime>

#include "window.h"
#include "texture.h"
#include "action.h"

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

class Entity{
    public:
        int x;
        int y;
        int h;
        int w;

        SDL_Point speed_limit;
        SDL_Point speed;
        SDL_Color color;
        
        Entity(){
            x = 0;
            y = 0;
            h = 0;
            w = 0;
            speed.x = 0;
            speed.y = 0;
            speed_limit.x = 0;
            speed_limit.y = 0;
            color = {0, 0, 0, 0xFF};
        }
        
        void init(
            int x, int y, int h, int w,
            SDL_Point speed, SDL_Color color
        ){
            this->x = x;
            this->y = y;
            this->h = h;
            this->w = w;
            this->speed_limit = speed;
            this->color = color;
        }
        
        void move_up(){
            speed.y = -speed_limit.y;
        }
        
        void move_down(){
            speed.y = +speed_limit.y;
        }
        
        void move_left(){
            speed.x = -speed_limit.x;
        }
        
        void move_right(){
            speed.x = +speed_limit.x;
        }
        
        void stop(){
            speed.x = 0;
            speed.y = 0;
        }
        
        void stop_x(){
            speed.x = 0;
        }
        
        void stop_y(){
            speed.y = 0;
        }
        
        void update(){
            x += speed.x;
            y += speed.y;
        }
        
        SDL_Rect get_rect(){
            SDL_Rect rect;
            rect.x = x;
            rect.y = y;
            rect.h = h;
            rect.w = w;
            return rect;
        }
        
        SDL_Point get_position(){
            SDL_Point point;
            point.x = x;
            point.y = y;
            return point;
        }
};

int main( int argc, char* args[] ){
    srand (time(0));
    int SCREEN_WIDTH  = 800;
    int SCREEN_HEIGHT = 600;
    int TEXT_SIZE =  SCREEN_HEIGHT/12;
    
    int VEL       = SCREEN_HEIGHT/100;
    int BALL_SIZE = SCREEN_HEIGHT/50;

    int PLAYER_WIDHT  = SCREEN_HEIGHT/50;
    int PLAYER_HEIGHT = SCREEN_HEIGHT/6;
    int PLAYER_PADING = SCREEN_HEIGHT/10;

    int score[2] = {0,0};
    int rand_value = 0;

    bool exit  = false;
    bool pause = false;

    int view_index = 0;
    int width = 0;

    enum views{
        VIEW_START,
        VIEW_GAME,
        VIEW_GAME_OVER
    };

    enum entity{
        BALL,
        PLAYER1,
        PLAYER2
    };

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

    rand_value = rand() % 4;
    if (rand_value == 0){
        ball.move_up();
        ball.move_right();
    }else if (rand_value == 1){
        ball.move_down();
        ball.move_right();
    }else if (rand_value == 2){
        ball.move_up();
        ball.move_left();
    }else if (rand_value == 3){
        ball.move_down();
        ball.move_left();
    }

    player1.init(
        PLAYER_PADING, 0,
        PLAYER_HEIGHT, PLAYER_WIDHT, {VEL, VEL},
        COLOR_WHITE
    );
    
    player2.init(
        SCREEN_WIDTH - PLAYER_WIDHT - PLAYER_PADING, 0,
        PLAYER_HEIGHT, PLAYER_WIDHT, {VEL, VEL},
        COLOR_WHITE
    );
    
    SDL_Point collition;
    
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

    while(exit == false){
        if(window.check_exit()){
            exit = true;
        }else{
            window.clear_screen();
            if(view_index == VIEW_START){
                width = text_white.get_text_size(
                    GAME_NAME
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 - width/2, TEXT_SIZE,
                    GAME_NAME
                );

                width = text_white.get_text_size(
                    "PRESS START"
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 - width/2,
                    SCREEN_HEIGHT - 2*TEXT_SIZE,
                    "PRESS START"
                );

                if(action->check_action(action->BUTTON_START)){
                    view_index = VIEW_GAME;
                }
            }else if(view_index == VIEW_GAME){
                if(!pause){
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
                        score[PLAYER1 - 1]++;
                        ball.x = SCREEN_WIDTH/2;
                        ball.y = SCREEN_HEIGHT/2;

                        rand_value = rand() % 4;
                        printf("%i", rand_value);
                        if (rand_value == 0){
                            ball.move_up();
                            ball.move_right();
                        }else if (rand_value == 1){
                            ball.move_down();
                            ball.move_right();
                        }else if (rand_value == 2){
                            ball.move_up();
                            ball.move_left();
                        }else if (rand_value == 3){
                            ball.move_down();
                            ball.move_left();
                        }
                    }
                    if(ball.x < 0){
                        score[PLAYER2 - 1]++;
                        ball.x = SCREEN_WIDTH/2;
                        ball.y = SCREEN_HEIGHT/2;

                        rand_value = rand() % 4;
                        printf("%i", rand_value);
                        if (rand_value == 0){
                            ball.move_up();
                            ball.move_right();
                        }else if (rand_value == 1){
                            ball.move_down();
                            ball.move_right();
                        }else if (rand_value == 2){
                            ball.move_up();
                            ball.move_left();
                        }else if (rand_value == 3){
                            ball.move_down();
                            ball.move_left();
                        }
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

                    // Update world
                    ball.update();
                    player1.update();
                    player2.update();

                    if((score[PLAYER1 - 1]>=10) || (score[PLAYER2 - 1] >= 10)){
                        view_index = VIEW_GAME_OVER;
                    }
                }else{
                    width = text_white.get_text_size(
                        "PAUSE"
                    ).w;

                    text_white.render(
                        SCREEN_WIDTH/2 - width/2,
                        SCREEN_HEIGHT/2 - TEXT_SIZE/2,
                        "PAUSE"
                    );
                    if(action->check_action(action->BUTTON_START)){
                        pause = false;
                    }
                }

                // Draw entitys
                window.draw_rectangle(ball.get_rect(), COLOR_WHITE);
                window.draw_rectangle(player1.get_rect(), COLOR_WHITE);
                window.draw_rectangle(player2.get_rect(), COLOR_WHITE);

                // Draw UI
                width = text_white.get_text_size(
                    std::to_string(score[PLAYER1 - 1])
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 - width -  10, 0,
                    std::to_string(score[PLAYER1 - 1])
                );

                width = text_white.get_text_size(
                    std::to_string(score[PLAYER2 - 1])
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 + 10, 0,
                    std::to_string(score[PLAYER2 - 1])
                );
                
                window.draw_line(
                    {SCREEN_WIDTH/2, 0},
                    {SCREEN_WIDTH/2, SCREEN_HEIGHT},
                    COLOR_WHITE
                );
            }else if(view_index == VIEW_GAME_OVER){
                width = text_white.get_text_size(
                    "GAME OVER"
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 - width/2, TEXT_SIZE,
                    "GAME OVER"
                );

                width = text_white.get_text_size(
                    "PRESS START"
                ).w;

                text_white.render(
                    SCREEN_WIDTH/2 - width/2,
                    SCREEN_HEIGHT - 2*TEXT_SIZE,
                    "PRESS START"
                );

                if(action->check_action(action->BUTTON_START)){
                    view_index = VIEW_START;
                    score[PLAYER1 - 1] = 0;
                    score[PLAYER2 - 1] = 0;
                    rand_value = rand() % 4;
                    ball.x = SCREEN_WIDTH/2;
                    ball.y = SCREEN_HEIGHT/2;
                    if (rand_value == 0){
                        ball.move_up();
                        ball.move_right();
                    }else if (rand_value == 1){
                        ball.move_down();
                        ball.move_right();
                    }else if (rand_value == 2){
                        ball.move_up();
                        ball.move_left();
                    }else if (rand_value == 3){
                        ball.move_down();
                        ball.move_left();
                    }
                }
            }

            window.update_screen();
        }
    }
    return 0;
}
