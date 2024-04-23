#include "raylib.h"
#include "piece.h"
#include "shape_node.h"
#include "Plateau.h"
#include "Design.h"
//#include<conio.h>
//#include <iostream>

bool paused = false;
int main()
{
    
    Design design;

    //Game g;
    //_getch();
    /*----add this on party's class---------------------------------------*/
  
        design.render();
   
    return 0;
}
//myPlateau->afficher();

/*
    const int screenWidth = 1200;
    const int screenHeight = 600;
    int fps = 60;
    InitWindow(screenWidth, screenHeight, "Dessiner des formes");
    SetTargetFPS(fps);

    Color colors[] = { BLUE, YELLOW, RED, GREEN };
    static float rotation = 0.0f;
    float x = 600.0f, y = 50.0f;
    bool canDPressKey = true;
    bool canGPressKey = true;
    */
    /*-----------
    ------------------------------*/
    //piece randowShape(4, 4, float(x), float(y));

    //shape_node *randomNode=new shape_node(randowShape);
//randowShape1.draw();
//piece copy(randowShape1.get_shape(), randowShape1.get_color(), randowShape1.get_X(), randowShape1.get_Y());
//piece* ptr = new piece(copy);

/*shape_node* copyNode = new shape_node(copy, NULL, NULL, NULL, NULL, NULL);
myChoisePlateau->set_head(copyNode);
myChoisePlateau->set_tail(copyNode);

while (!WindowShouldClose() && myChoisePlateau->get_head() != nullptr)
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    myChoisePlateau->get_head()->get_piece().draw();
    myChoisePlateau->afficher();
    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        myPlateau->inserer_right(&randowShape1);
        myChoisePlateau->set_head(nullptr);
        myChoisePlateau->set_tail(nullptr);
    }else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        myPlateau->inserer_left(&randowShape1);
        myChoisePlateau->set_head(nullptr);
        myChoisePlateau->set_tail(nullptr);
    }
    myPlateau->drawAll();
    if (x < 0) x = 0;
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


     }
     EndDrawing();
 }*/
 //myPlateau->afficher();
