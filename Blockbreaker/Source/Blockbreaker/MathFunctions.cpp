// Fill out your copyright notice in the Description page of Project Settings.

#include "MathFunctions.h"
#include <math.h>
#include "BlockbreakerBPFunctionLibrary.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMath.h"
#include <iostream>
#include <iomanip>
#include <sstream>

MathFunction* MathFunction::GetFunction(int32 num){
  switch(num){
    case 1: return new Cosine();
    case 2: return new Tangent();
    case 3: return new Secant();
    case 4: return new Cosecant();
    case 5: return new Cotangent();
    case 6: return new Arctangent();
    case 7: return new Arccotangent();
    case 8: return new SawtoothWave();
    case 9: return new SquareWave();
    case 10: return new Ellipse();
    case 11: return new Linear();
    case 12: return new Square();
    case 13: return new Cubic();
    case 14: return new Quadratic();
    case 15: return new Logarithmic();
    case 16: return new Exponential();
    case 17: return new Absolute();
    case 18: return new Reciprocal();
    case 19: return new Root();
    default: return new Sine();
  }
}
//  ax+b
void Linear::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = (isnan((*a * (*x)) + *b) ? 0.0f : ((*a * (*x)) + *c));
}
//  ax^2 + b
void Square::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = (isnan((*a *((*x)*(*x) + *b))) ? 0.0f : (*a*((*x)*(*x)) + *b));
}
//  ax^3 + b
void Cubic::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = (isnan((*a *((*x)*(*x)*(*x)) + *c)) ? 0.0f : (*a*((*x)*(*x)*(*x)) + *c));
}
//  ax ^ (b/c) + y
void Root::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan(UBlockbreakerBPFunctionLibrary::NRoot(*x,*b,*c)) ? 
         0.0f : *a *(UBlockbreakerBPFunctionLibrary::NRoot(*x,*b,*c) + *y);
}
//   a*|x + b| + c 
void Absolute::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan(*a * fabs(*x + *b) + *c) ? 0.0f : *a * fabs(*x + *b) + *c;
}
//  ax^2 + bx + c
void Quadratic::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan(*a*(*x * *x)+(*b * *x)+ *c) ? 0.0f :*a * (*x * *x)+(*b * *x) + *c;
}
//  e^(ax+b) + c
void Exponential::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan( exp((*a * *x)+ *b) + *c) ? 0.0f : exp((*a * *x) + *b) + *c;
}
//  a * Ln(bx + c) + y
void Logarithmic::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan(*a * FGenericPlatformMath::Loge((*b * *x) + *c) + *y ) ? 
          0.0f : (*a * FGenericPlatformMath::Loge((*b * *x) + *c) + *y );
}
//  a / (b * x + c) + y
void Reciprocal::Operation(float *x, float *y, float *a, float *b, float* c){
  if (*b * *x + *c == 0.0f)
    *y = *a / 0.1f + *y;
  else
    *y = (*a / (*b * *x + *c)) + *y;
  
}
//  a * sin(bx+c) + y
void Sine::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan((sin((*b * *x) + *c))) ? 0.01 : *a *(sin((*b * *x) + *c) + *y);
}
//  a * cos(bx+c) + y
void Cosine::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan((cos((*b * *x) + *c))) ? 0.01 : *a *(cos((*b * *x) + *c) + *y);
}
//  a * tan(bx+c) + y
void Tangent::Operation(float *x, float *y, float *a, float *b, float* c){
  *y = isnan((tan((*b * *x) + *c))) ? 0.01 : *a *(tan((*b * *x) + *c) + *y);
}
//  a * sec(bx+c) + y
void Secant::Operation(float *x, float *y, float *a, float *b, float* c){
  MathFunction* Sin = new Sine();
  Sin->Operation(x, y, a, b, c);
  *y = isnan(1.0 / *y) ? 0.01f : (1.0f / *y);
}
//  a * csc(bx+c) + y
void Cosecant::Operation(float *x, float *y, float *a, float *b, float* c){
  MathFunction* Cos = new Cosine();
  Cos->Operation(x, y, a, b, c);
  *y = isnan(1.0 / *y) ? 0.01f : (1.0f / *y);
}
//  a * cot(bx+c) + y
void Cotangent::Operation(float *x, float *y, float *a, float *b, float* c){
  MathFunction* Tan = new Tangent();
  Tan->Operation(x, y, a, b, c);
  *y = isnan(1.0 / *y) ? 0.01f : (1.0f / *y);
}
//  a * atan(bx+c) + y
void Arctangent::Operation(float *x, float *y, float *a, float *b, float* c) {
  *y = isnan(1.0 / (atan((*b * *x) + *c))) ? 0.01f : *a *(atan((*b * *x) + *c) + *y);
}
//  a * acot(bx+c) + y
void Arccotangent::Operation(float *x, float *y, float *a, float *b, float* c) {
  MathFunction* Arctan = new Arctangent();
  Arctan->Operation(x, y, a, b, c);
  *y = isnan(1.0 / *y) ? 0.01f : (1.0f / *y);
}
//  a*2 *( floor[ (b*x/c) + (1/2)]) + y
void SawtoothWave::Operation(float *x, float *y, float *a, float *b, float* c) {
  *y = isnan(*a * 2 * floor(((*b * *x) / *c) + (1.0/2.0) + *y)) ? 0.01f : (1.0f / *y);
}
//  sign(a*2 *( floor[ (b*x/c) + (1/2)]) + y)
void SquareWave::Operation(float *x, float *y, float *a, float *b, float* c){
  SawtoothWave Sawtooth;
  Sawtooth.Operation(x, y, a, b, c);
  *y = isnan(*y) ? 0.01f : UBlockbreakerBPFunctionLibrary::Sign(*y);
}
// c - ((x^2/a) + (y^2/b))
void Ellipse::Operation(float * x, float *y, float *a, float *b, float* c ){
  *a == 0.0 ? *a = 1.0 : *a;
  *b == 0.0 ? *b = 1.0 : *b;
  *y = *c - (((*x * *x) / (*a * *a)) + ((*y * *y) / *b * *b));
}
