#include "raylib.h"
#include "piece.h"
#include "shape_node.h"
#include "Plateau.h"
#include<conio.h>

int main()
{

    const int screenWidth = 1200;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Dessiner des formes");
    SetTargetFPS(60);

    Color colors[] = { BLUE, YELLOW, RED, GREEN };
    static float rotation = 0.0f;
    float x = 600.0f, y = 80.0f;
    bool canDPressKey = true;
    bool canGPressKey = true;

    /*-----------
    ------------------------------*/
    //piece randowShape(4, 4, float(x), float(y));

    //shape_node *randomNode=new shape_node(randowShape);

    Plateau* myPlateau=new Plateau();
    
    
        
        /*-------------------------------------------*/
        


        myPlateau->afficher();
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        myPlateau->drawAll();


        piece *randowShape1=new piece(4, 4, float(x), float(y));
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            myPlateau->inserer_right(randowShape1);

        }else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            myPlateau->inserer_left(randowShape1);


        }




        myPlateau->drawAll();

       /* if (x < 0) x = 0;
        if (y < 0) y = 0;
        if (x > screenWidth - 40) x = screenWidth - 40;
        if (y > screenHeight - 40) y = screenHeight - 40;

        /*--------------------------------------------------------
        if (IsKeyPressed(KEY_RIGHT) && canDPressKey) {
            x += GetFrameTime() + 250.0f;
            y += GetFrameTime() + 250.0f;
            myPlateau->get_head()->get_piece().set_X(x);
            myPlateau->get_head()->get_piece().set_Y(y );
            canDPressKey = false;
            canGPressKey = false;



        }if (IsKeyPressed(KEY_LEFT) && canGPressKey) {
            x -= GetFrameTime() + 250.0f;
            y += GetFrameTime() + 250.0f;
            myPlateau->get_head()->get_piece().set_X(x);
            myPlateau->get_head()->get_piece().set_Y(y );
            canGPressKey = false;
            canDPressKey = false;


        }if (IsKeyPressed(KEY_UP)) {
            x = 600;
            y = 80;
            myPlateau->get_head()->get_piece().set_X(x);
            myPlateau->get_head()->get_piece().set_Y(y);
            canGPressKey = true;
            canDPressKey = true;


        }
        /*static float rotation = 45.0f;
        DrawRectanglePro(Rectangle{x ,y, 40,40 }, { 20,20 }, rotation, colors[0]);*/
        
       /*for (int i = 0; i <= 3; i++)
        {
            static float rotation = 45.0f;
            rotation += 0.5f;
            DrawCircle(20+i*60, 320, 20, colors[i]);
            DrawRectangleRec(Rectangle{float( 20 + i * 60),360, 40,40 }, colors[i]);
            DrawRectanglePro(Rectangle{float( 40 + i * 60),440, 40,40 },{20,20}, rotation, colors[i]);
            DrawTriangle({ float(20 + i * 60), 530 }, { float(60 + i * 60), 530 }, { float(40 + i * 60), 495 }, colors[i]);

            
        }*/
        EndDrawing();
    }
    
    CloseWindow();
            myPlateau->afficher();

    return 0;
}