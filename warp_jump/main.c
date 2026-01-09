// Sci-fi warp speed (raylib)
#include "raylib.h"
#include <stdlib.h>

typedef struct { float x,y,z; } Star;

static float frand(float a, float b){ return a + (b-a)*(float)rand()/(float)RAND_MAX; }

int main(void){
    const int W=1200,H=700,N=4000;
    InitWindow(W,H,"warp jump"); SetTargetFPS(60);
    srand(12345);

    Camera3D cam = {0};
    cam.position=(Vector3){0,0,0};
    cam.target  =(Vector3){0,0,1};
    cam.up      =(Vector3){0,1,0};
    cam.fovy    = 70;
    cam.projection = CAMERA_PERSPECTIVE;

    Star *s = (Star*)MemAlloc(sizeof(Star)*N);
    for(int i=0;i<N;i++) s[i]=(Star){ frand(-30,30), frand(-18,18), frand(1,220) };

    float speed=90.0f;
    for(;!WindowShouldClose();){
        float dt=GetFrameTime();
        if(IsKeyDown(KEY_UP)) speed+=120*dt;
        if(IsKeyDown(KEY_DOWN)) speed-=120*dt;
        if(speed<10) speed=10;

        BeginDrawing();
        ClearBackground((Color){3,5,10,255});
        BeginMode3D(cam);

        for(int i=0;i<N;i++){
            float z0 = s[i].z;
            s[i].z -= speed*dt;

            // respawn star that passed camera
            if(s[i].z <= 0.2f){
                s[i].x = frand(-30,30);
                s[i].y = frand(-18,18);
                s[i].z = frand(120,220);
                z0 = s[i].z + speed*dt;
            }

            // streak: previous pos -> current pos
            Vector3 a = (Vector3){ s[i].x, s[i].y, z0 };
            Vector3 b = (Vector3){ s[i].x, s[i].y, s[i].z };

            float near = 1.0f - (s[i].z/220.0f);           // 0..1 (brighter when closer)
            unsigned char A = (unsigned char)(40 + 215*near);
            Color c = (Color){200,220,255,A};

            DrawLine3D(a,b,c);
        }

        EndMode3D();
        DrawText("WARP  |  Up/Down change speed  |  Esc quit", 12, 12, 20, RAYWHITE);
        DrawText(TextFormat("speed: %.0f", speed), 12, 38, 20, RAYWHITE);
        EndDrawing();
    }

    MemFree(s);
    CloseWindow();
    return 0;
}
