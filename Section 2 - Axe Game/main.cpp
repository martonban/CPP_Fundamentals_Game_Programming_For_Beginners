#include "raylib.h"

int main(){

    //Window dimention
    int width{800};
    int height{450};
    InitWindow(width, height, "MyFirst C++ Game");

    //Circle coordinates
    int circle_x{200};
    int circle_y{200};
    int circle_radius{25};
    //circle edges
    int l_circle_x{circle_x - circle_radius};
    int r_circle_x{circle_x + circle_radius};
    int u_circle_y{circle_y - circle_radius};
    int b_circle_y{circle_y + circle_radius};

    //Rectangle coordinates
    int rectangle_x{400};
    int rectangle_y{0};
    int axe_length{50};
    //Axe Edges
    int l_axe_x{rectangle_x};
    int r_axe_x{rectangle_x + axe_length};
    int u_axe_y{rectangle_y};
    int b_axe_y{rectangle_y + axe_length};

    int direction{10};

    bool collisionWithAxe = (b_axe_y >= u_circle_y) 
                            && (u_axe_y <= b_circle_y) 
                            && (r_axe_x >= l_circle_x)
                            && (l_axe_x <= r_circle_x);
    SetTargetFPS(60);
    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(WHITE);

        if(collisionWithAxe){
            DrawText("Game Over", 400, 200, 20, RED);
        }else{
            //Game Logic

            //Update collison
            l_circle_x = circle_x - circle_radius;
            r_circle_x = circle_x + circle_radius;
            u_circle_y = circle_y - circle_radius;
            b_circle_y = circle_y + circle_radius;

            l_axe_x = rectangle_x;
            r_axe_x = rectangle_x + axe_length;
            u_axe_y = rectangle_y;
            b_axe_y = rectangle_y + axe_length;


            collisionWithAxe = (b_axe_y >= u_circle_y) 
                            && (u_axe_y <= b_circle_y) 
                            && (r_axe_x >= l_circle_x)
                            && (l_axe_x <= r_circle_x);


            DrawCircle(circle_x, circle_y, circle_radius, BLUE); 
            DrawRectangle(rectangle_x, rectangle_y, axe_length, axe_length, RED);

            if(IsKeyDown(KEY_D) && circle_x < width){
                circle_x += 10;    
            }

            if(IsKeyDown(KEY_A) && circle_x > 0 ){
                circle_x -= 10;
            }

            rectangle_y += direction;
            if(rectangle_y > height || rectangle_y < 0){
                direction *= -1;
            }

        
            //Game Logic End
        }

        
        EndDrawing();
    }
    

}