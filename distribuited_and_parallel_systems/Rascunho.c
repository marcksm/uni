#include <math.h>
int Rx, Ry, R[20][20], teta, Bx, By, B[20][20];
int C[20][20];

int main (){
    int i, j;
    Rx = sin (teta) * R[i][j];
    Ry = cos (teta) * R[i][j];

    Bx = -sin (teta) * B[i][j];
    By = -cos (teta) * B[i][j];

    
    return 0;
}
