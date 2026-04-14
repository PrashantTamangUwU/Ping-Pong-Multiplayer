#include"./raylib/src/raylib.h"

int highScore=0, scorep1=0, scorep2=0;

 typedef struct Player{
    float sizeX;
    float sizeY; 

    float posX;
    float posY;  

    float speedY;

  }player;

  typedef struct Ball{
    float posX;
    float posY;  

    float radius;
    float speedX;
    float speedY;

}ball;


void Update(player *p1, player *p2, ball *b1){

  //Ball Movement
  b1->posY += b1->speedY;
  b1->posX += b1->speedX;


  //Collision with window
  if ((b1->posY + b1->radius) >= GetScreenHeight() || (b1->posY - b1->radius) <= 0)  b1->speedY *=-1;
  //if ((b1->posX + b1->radius) >= GetScreenWidth() || (b1->posX - b1->radius) <= 0)  b1->speedX *=-1;
   

  //Player paddle
  if(p1->posY+p1->sizeY >= GetScreenHeight()) p1->posY=GetScreenHeight()-p1->sizeY; 
  if(p1->posY <= 0) p1->posY=0;

  if(p2->posY+p2->sizeY >= GetScreenHeight()) p2->posY=GetScreenHeight()-p2->sizeY; 
  if(p2->posY <= 0) p2->posY=0;

 
  //scores
  if ((b1->posX + b1->radius) >= GetScreenWidth() || (b1->posX - b1->radius <=0)) highScore++;

  if (b1->posX + b1->radius >=GetScreenWidth()){ 

    b1->posX = (float)GetScreenWidth()/2;
    b1->posY = (float)GetScreenHeight()/2;

    //speed increase when player score
    float ballSpeed[] = {-1.02000, 1.02000};

    b1->speedX *= ballSpeed[GetRandomValue(0, 1)];
    b1->speedY *= ballSpeed[GetRandomValue(0, 1)];

    p1->speedY += 1.0f;

    p1->sizeY -=4.3f;
    scorep1++;
  }

    if (b1->posX - b1->radius <=0){

    b1->posX = (float)GetScreenWidth()/2;
    b1->posY = (float)GetScreenHeight()/2;

    //speed increase when player score
    float ballSpeed[] = {-1.03000, 1.03000};

    b1->speedX *= ballSpeed[GetRandomValue(0, 1)];
    b1->speedY *= ballSpeed[GetRandomValue(0, 1)];
    
    p2->speedY += 1.0f;

    p2->sizeY -=4.3f;
    scorep2++;
  }

  //Collision with player
  if(CheckCollisionCircleRec(Vector2 {b1->posX, b1->posY}, b1->radius, {p1->posX, p1->posY, p1->sizeX, p1->sizeY})) b1->speedX *=-1;
  if(CheckCollisionCircleRec(Vector2 {b1->posX, b1->posY}, b1->radius, {p2->posX, p2->posY, p2->sizeX, p2->sizeY})) b1->speedX *=-1;


  if(IsKeyDown(KEY_S)) p1->posY+=p1->speedY;  
  if(IsKeyDown(KEY_W)) p1->posY-=p1->speedY;
   
  if(IsKeyDown(KEY_DOWN)) p2->posY+=p2->speedY;  
  if(IsKeyDown(KEY_UP)) p2->posY-=p2->speedY;


  
}

int main(void){

  const float screenHeight = 1080.0f;
  const float screenWidth = 1920.0f;

  Color Green = Color{131, 238, 0, 255};
  Color Pink = Color{238, 0, 178, 255};
  Color Yellow = Color{238, 210, 0, 255};
  Color Grey = Color{153, 153, 153, 25};
  Color darkGrey = Color{153, 153, 153, 60};
 
  player *p1 = new player();
  player *p2 = new player();

  ball *b1 = new ball();

  InitWindow(screenWidth, screenHeight, "Window");
  SetTargetFPS(60);

  p1->posX=55;
  p1->posY=(float)screenHeight/2-70;
  p1->sizeX=20;
  p1->sizeY=200;
  p1->speedY=12.0f;

  p2->posX=(float)screenWidth-85;
  p2->posY=(float)screenHeight/2-70;
  p2->sizeX=20;
  p2->sizeY=200;
  p2->speedY=12.0f;

  b1->posX = (float)screenWidth/2;
  b1->posY = (float)screenHeight/2;
  b1->radius = 15.0f;
  b1->speedX = 10.12f;
  b1->speedY = 7.60f;

  Rectangle rec1;
  Rectangle rec2;

  while(!WindowShouldClose()){
    
    BeginDrawing();
    ClearBackground(BLACK);

    DrawText("Developed by Prashant Tamang", GetScreenWidth()-200, 20, 10, GREEN);
    DrawText(TextFormat("FPS : %d", GetFPS()), 20, 20, 24, GREEN);

    if(highScore!=40){

      rec1 = {p1->posX,  p1->posY, p1->sizeX, p1->sizeY};
      rec2 = {p2->posX, p2->posY, p2->sizeX, p2->sizeY};

      //updating
      Update(p1, p2, b1);

      DrawText(TextFormat("Total Scores : %d", highScore), GetScreenWidth()/2.25, 20, 24, GREEN);
      DrawText(TextFormat("Player(1) : %d\n---------------", scorep1), GetScreenWidth()/5.5f, 20, 20, GREEN);
      DrawText(TextFormat("Speed buff : %.2lf ++\n-----------------", p1->speedY), GetScreenWidth()/5.5f, 70, 20, GREEN);
      DrawText(TextFormat("Player(2) : %d\n---------------", scorep2), GetScreenWidth()/1.5f, 20, 20, GREEN);
      DrawText(TextFormat("Speed buff : %.2lf ++\n-----------------", p2->speedY), GetScreenWidth()/1.5f, 70, 20, GREEN);

      DrawCircle(GetScreenWidth()/2, GetScreenHeight()/2, 250, Grey);
      //verticle line & horizontal line
      DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, darkGrey);
      //DrawLine(0, screenHeight/2, screenWidth, screenHeight/2, GRAY);


      //ball
      DrawCircle(b1->posX, b1->posY, b1->radius, Yellow);
      DrawRectangleRec(rec1, Green);
      DrawRectangleRec(rec2, Pink);
   
    }

    else{

      DrawText("! CONGRATULATION !\n----------------------", GetScreenWidth()/3.1f, GetScreenHeight()/2-250, 60, GREEN);
      if(scorep1 > scorep2){
        DrawText("Player(1) Wins !", GetScreenWidth()/2.6, GetScreenHeight()/2-140, 55, GREEN);
        DrawText(TextFormat("Total Scores : %d+", highScore), GetScreenWidth()/2.5f, GetScreenHeight()/2-60, 40, GREEN);
        DrawText(TextFormat("Player(1) : %d+", scorep1), GetScreenWidth()/2.3, GetScreenHeight()/2-10, 30, GREEN);
        DrawText(TextFormat("Player(2) : %d+", scorep2), GetScreenWidth()/2.3, GetScreenHeight()/2+30, 30, GREEN);
      }
      else if(scorep2 > scorep1){
        DrawText("Player(2) Wins !", GetScreenWidth()/2.5, GetScreenHeight()/2-150, 55, GREEN);
        DrawText(TextFormat("Total Scores : %d+", highScore), GetScreenWidth()/2.5f, GetScreenHeight()/2-60, 40, GREEN);
        DrawText(TextFormat("Player(2) : %d+", scorep2), GetScreenWidth()/2.3, GetScreenHeight()/2-10, 30, GREEN);
        DrawText(TextFormat("Player(1) : %d+", scorep1), GetScreenWidth()/2.3, GetScreenHeight()/2+30, 30, GREEN);
      }
      else{
        DrawText(TextFormat("Draw! : %d", highScore), GetScreenWidth()/2.3, GetScreenWidth()/2, 24, GREEN);
      }
    }
EndDrawing();
    
  } 

  CloseWindow();
  delete p1;
  p1 = nullptr;

  delete p2;
  p2 = nullptr;

  delete b1;
  b1 = nullptr;
  return 0;
}
