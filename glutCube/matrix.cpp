#include "matrix.h"

float* multMatrix4Point(float M[4][4], float N[4])
{
    float R[4];
    for (int i=0; i<4; i++)
    {
        float sum = 0;
        for(int j=0; j<4, j++)
        {
            sum += M[i][j] * N[j];
        }
        R[i] = sum;
    }
    return R;
}
