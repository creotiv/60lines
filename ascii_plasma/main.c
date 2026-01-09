// 256-color ANSI plasma (Linux/macOS terminals)
#include <stdio.h>
#include <math.h>
#include <unistd.h>

static int clampi(int v,int lo,int hi){ return v<lo?lo:(v>hi?hi:v); }

int main(void){
    const int W=60, H=60;
    printf("\x1b[2J\x1b[?25l");                       // clear + hide cursor

    for(double t=0;; t+=0.07){
        printf("\x1b[H");                             // cursor home
        for(int y=0;y<H;y++){
            for(int x=0;x<W;x++){
                double nx=(x-W*0.5)/(W*0.5), ny=(y-H*0.5)/(H*0.5);
                double v = sin(3*nx+t)+sin(4*ny+t*1.3)+sin(3*(nx+ny)+t*0.7)+sin(6*hypot(nx,ny)-t*1.8);
                int c = clampi((int)((v+4.0)/8.0*23.0 + 0.5), 0, 55); 
                int ansi = 200 + c;                                  
                printf("\x1b[48;5;%dm  ", ansi);                      // background color
            }
            printf("\x1b[0m\n");                                      // reset at line end
        }
        fflush(stdout);
        usleep(16000);
    }
}
