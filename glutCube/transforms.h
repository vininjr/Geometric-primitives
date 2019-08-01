#ifndef TRANSFORMS_H_INCLUDED
#define TRANSFORMS_H_INCLUDED

#include <vector>

float *translatePoint(vector<float> P, float alpha, vector<float> v);
float *rotateVector(vector<float> v, float tetha, vector<float> axis);

#endif // TRANSFORMS_H_INCLUDED
