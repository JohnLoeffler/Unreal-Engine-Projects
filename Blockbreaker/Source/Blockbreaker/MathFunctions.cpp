// Fill out your copyright notice in the Description page of Project Settings.

#include "MathFunctions.h"
#include <math.h>
#include <iostream>
#include <iomanip>
#include "Logger.h"
#include <sstream>

MathFunction* MathFunction::GetFunction(int32 num) {
  switch(num) {
    case 1: return new Cosinusoidal();
    case 2: return new Tangential();
    case 3: return new Secantial();
    case 4: return new Cosecantial();
    case 5: return new Cotangential();
    case 6: return new Arctangential();
    case 7: return new Arccotangential();
    case 8: return new SawtoothWave();
    case 9: return new SquareWave();
    case 10: return new Linear();
    case 11: return new Square();
    case 12: return new Cubic();
    case 13: return new Quadratic();
    case 14: return new Logarithmic();
    case 15: return new Exponential();
    case 16: return new Absolute();
    case 17: return new Reciprocal();
    case 18: return new Squareroot();
    default:  return new Sinusoidal();
  }
}

float Linear::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan(*x)) ?
    0.0 : isnan((*a * (*x)) + *c) ?
    0.0 : ((*a * (*x)) + *c));
}

float Square::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan(*x)) ?
    0.0 : isnan((*a *((*x)*(*x) + *c))) ?
    0.0 : (*a*((*x)*(*x)) + *c));
}

float Cubic::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan(*x)) ?
    0.0 : isnan((*a *((*x)*(*x)*(*x)) + *c)) ?
    0.0 : (*a*((*x)*(*x)*(*x)) + *c));
}

float Squareroot::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ? NAN : (*a*(*x)) < 0 ?
    0.0 : isnan((*b * (sqrt(*a*(*x))) + *c)) ?
    0.0 : (*b * (sqrt(*a*(*x))) + *c));
}

float Absolute::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan(*b * (fabs(*a * (*x))) + *c) ?
    0.0 : (*b *(fabs(*a *(*x))) + *c));
}

float Quadratic::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan(*a * ((*x)*(*x)) + (*b * (*x)) + *c) ?
    0.0 : (*a * ((*x)*(*x)) + (*b * (*x)) + *c));
}

float Exponential::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : (isnan(pow(*a, (*x)) + *c)) ?
    0.0 : (pow(*a, (*x)) + *c));
}

float Logarithmic::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : (isnan(*a * log((*b * (*x))) + *c)) ?
    0.0 : (*a * log(*b * (*x)) + *c));
}

float Reciprocal::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : (*a * (*x)) == 0 ?
    0.0 : (isnan((*b / (*a * (*x))) + *c)) ?
    0.0 : (*b / (*a * (*x))) + *c);
}

float Sinusoidal::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan((*a * sin(*b * (*x)) + *c)) ?
    0.0 : (*a * sin(*b * (*x)) + *c));
}

float Cosinusoidal::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan(*a * cos(*b * (*x)) + *c)) ?
    0.0 : (*a * cos(*b * (*x)) + *c);
}

float Tangential::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan(*a * tan(*b * (*x)) + *c) ?
    0.0 : (*a * tan(*b * (*x)) + *c));
}

float Secantial::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  MathFunction* Sin = new Sinusoidal();
  return (Sin->Operation(x, a, b, c) == 0 ? 0.0 : (1.0 / Sin->Operation(x, a, b, c)));
}

float Cosecantial::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  MathFunction* Cos = new Cosinusoidal();
  return (Cos->Operation(x, a, b, c) == 0 ? 0.0 : (1.0 / Cos->Operation(x, a, b, c)));
}

float Cotangential::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  MathFunction* Tan = new Tangential();
  return (Tan->Operation(x, a, b, c) == 0 ? 0.0 : (1.0 / Tan->Operation(x, a, b, c)));
}

float Arctangential::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  return ((isnan((*x))) ?
    0.0 : isnan((*a * atan(*b * (*x)) + *c)) ?
    0.0 : (*a * atan(*b * (*x)) + *c));
}

float Arccotangential::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  MathFunction* Arctan = new Arctangential();
  return (Arctan->Operation(x, a, b, c) == 0 ? 0.0 : (1.0 / Arctan->Operation(x, a, b, c)));
}

float SawtoothWave::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  *c = (*c == 0.0 ? 4.0 : *c);
  return ((isnan((*x))) ?
    0.0 : *c == 0 ?
    0.0 : isnan(2 * ((*a * (*x)) / (*c) - floor(((*a * (*x)) / (*c) + (1 / 2))))) ?
    0.0 : 2 * ((*a * (*x)) / (*c) - floor(((*a * (*x)) / (*c) + (1 / 2)))));
}

float SquareWave::Operation(float *x, float *a, float *b, float *c) {
  std::stringstream SS;
  SS << "X: " << std::setw(4) << *x << "| A: " << std::setw(4) << *a << "| B: " << std::setw(4) << *b << "| C: " << *c;
  LOG(_INF, SS.str().c_str());
  *c = (*c == 0.0 ? 4.0 : *c);
  return (isnan((*x)) ?
    0.0 : isnan(Sign(2 * ((*a * (*x)) / (*c) - floor(((*a * (*x)) / (*c) + (1 / 2)))))) ?
    0.0 : Sign(2 * ((*a * (*x)) / (*c) - floor(((*a * (*x)) / (*c) + (1 / 2))))));
}