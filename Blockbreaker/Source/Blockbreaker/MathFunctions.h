#pragma once
#ifndef MATHFUNCTION_H
#define	MATHFUNCTION_H

#include "CoreMinimal.h"

class Logger;

/**
 *  A Class Interface for implementing a Strategy Pattern based on the output of various mathematical functions
 */
class BLOCKBREAKER_API MathFunction
{
protected:
  Logger * _Logger;
  float Sign(float x) { return (x < 0 ? -1 : x > 0 ? 1 : 0); }
public:
  virtual float Operation(float *x, float *a, float *b, float *c)=0;

  /** 
  * Parent class for the various functions
  */
  MathFunction() {}
  virtual ~MathFunction() {}
  static MathFunction* GetFunction(int32 num);
  static float Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow) {
    return((OldHigh - OldLow) == 0.0 ? NewLow : (((Value - OldLow)*(NewHigh - NewLow) / (OldHigh - OldLow)) + (NewLow)));
  }
};

/* N-DEGREE MONO/POLYNOMIAL FUNCTIONS */
class Linear : public MathFunction {
public:
  Linear() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Square : public MathFunction {
public:
  Square() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Cubic : public MathFunction {
public:
  Cubic() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Quadratic : public MathFunction {
public:
  Quadratic() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Exponential : public MathFunction {
public:
  Exponential() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Logarithmic : public MathFunction {
public:
  Logarithmic() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Absolute : public MathFunction {
public:
  Absolute() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Squareroot : public MathFunction {
public:
  Squareroot() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Reciprocal : public MathFunction {
public:
  Reciprocal() {}
  float Operation(float *x, float *a, float *b, float *c);

};

/*    PERIODIC FUNCTIONS */

class Sinusoidal : public MathFunction {
public:
  Sinusoidal() {}
  float Operation(float *x, float *a, float *b, float *c);

};

/*
* I'm pretty sure this is not the proper name for the Cosine function, but I wanted to keep it consistent with Sinusoidal so it can be properly identified
*/
class Cosinusoidal : public MathFunction {
public:
  Cosinusoidal() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class Tangential : public MathFunction {
public:
  Tangential() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class Secantial : public MathFunction {
public:
  Secantial() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class Cosecantial : public MathFunction {
public:
  Cosecantial() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class Cotangential : public MathFunction {
public:
  Cotangential() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class Arctangential : public MathFunction {
public:
  Arctangential() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class Arccotangential : public MathFunction {
public:
  Arccotangential() {}
  float Operation(float *x, float *a, float *b, float *c);
};

class SawtoothWave : public MathFunction {
public:
  SawtoothWave() {}
  float Operation(float *x, float *a, float *b, float *c);

};

class SquareWave : public MathFunction {
public:
  SquareWave() {}
  float Operation(float *x, float *a, float *b, float *c);

};
#endif //	MATHFUNCTION_H
