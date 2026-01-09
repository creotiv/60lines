// Arkanoid-ish in ~60 lines using raylib
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

int main(void){
  const int W=900,H=600,cols=12,rows=6; InitWindow(W,H,"arkanoid"); SetTargetFPS(60);
  srand((unsigned)time(NULL));
  Rectangle pad={W/2-60,H-30,120,14};
  Vector2 ball={ (float)(60+rand()%(W-120)), (float)(H/2 + rand()%80) }, v={ (rand()%2?1:-1)*320.0f, -360.0f };
  bool br[rows][cols]; for(int r=0;r<rows;r++)for(int c=0;c<cols;c++) br[r][c]=true;
  for(;;){
    if(WindowShouldClose()) break;
    float dt=GetFrameTime(), ps=520.0f; // paddle speed
    if(IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) pad.x-=ps*dt;
    if(IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) pad.x+=ps*dt;
    if(pad.x<10) pad.x=10; if(pad.x+pad.width>W-10) pad.x=W-10-pad.width;

    ball.x+=v.x*dt; ball.y+=v.y*dt; // ball speed is v magnitude (separate from ps)
    if(ball.x<12||ball.x>W-12) v.x=-v.x;
    if(ball.y<12) v.y=-v.y;

    Rectangle brect={ball.x-6,ball.y-6,12,12};
    if(CheckCollisionRecs(brect,pad) && v.y>0){ v.y=-v.y; float t=(ball.x-(pad.x+pad.width/2))/(pad.width/2); v.x=420.0f*t; }

    int bw=(W-40)/cols, bh=22;
    for(int r=0;r<rows;r++)for(int c=0;c<cols;c++) if(br[r][c]){
      Rectangle rc={20+c*bw,40+r*bh,(float)bw-6,(float)bh-6};
      if(CheckCollisionRecs(brect,rc)){ br[r][c]=false; v.y=-v.y; }
    }

    if(ball.y>H+30 || IsKeyPressed(KEY_R)){ // restart (random)
      pad.x=W/2-pad.width/2;
      ball=(Vector2){ (float)(60+rand()%(W-120)), (float)(H/2 + rand()%80) };
      v=(Vector2){ (rand()%2?1:-1)*320.0f, -360.0f };
      for(int r=0;r<rows;r++)for(int c=0;c<cols;c++) br[r][c]=true;
    }

    BeginDrawing(); ClearBackground((Color){16,18,24,255});
    DrawRectangleRec(pad,(Color){220,220,255,255}); DrawCircleV(ball,6,(Color){255,220,140,255});
    for(int r=0;r<rows;r++)for(int c=0;c<cols;c++) if(br[r][c])
      DrawRectangle(20+c*bw,40+r*bh,bw-6,bh-6,(Color){120+10*r,140+6*c,220-12*r,255});
    EndDrawing();
  }
  CloseWindow(); return 0;
}
