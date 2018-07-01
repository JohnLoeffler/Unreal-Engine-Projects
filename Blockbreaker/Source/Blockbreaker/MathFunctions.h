#pragma once
#ifndef MATHFUNCTIONS_H
#define	MATHFUNCTIONS_H

#include "CoreMinimal.h"
#include "Blockbreaker.h"
  /**
   * Interface Class for implementing interchangable Math functions
   */
    class BLOCKBREAKER_API MathFunction
    {
    protected:
      
    public:
      virtual void Operation(float *x, float *y, float *a, float *b, float *c) = 0;

      MathFunction() {}
      virtual ~MathFunction() {}
      static MathFunction* GetFunction(int32 num);
      static float Normalize(float Value, float NewHigh, float NewLow, float OldHigh, float OldLow) {
        return((OldHigh - OldLow) == 0.0 ? NewLow : (((Value - OldLow)*(NewHigh - NewLow) / (OldHigh - OldLow)) + (NewLow)));
      }
    };

    /* N-DEGREE FUNCTIONS */
    /**
    * Linear (a(x + b) + c) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result of the evaluation
    * @param a A pointer to a float that holds the slope of the line
    * @param b A pointer to a float that holds the constant value applied to 'x' value
    * @param c A pointer to a float that holds the constant value applied to the function
    */
    class Linear : public MathFunction {
    public:
      Linear() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Square (a(x + b)^2 + c) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result of the evaluation
    * @param a A pointer to a float that holds the coefficient of the 'x' value
    * @param b A pointer to a float that holds the constant value applied to the function
    * @param c Not used
    */
    class Square : public MathFunction {
    public:
      Square() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Cubic (a(x+b)^3 + c) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result of the evaluation
    * @param a A pointer to a float that holds the coefficient of the 'x' value
    * @param b A pointer to a float that holds the constant value applied to 'x' value
    * @param c A pointer to a float that holds the constant value applied to the function
    */
    class Cubic : public MathFunction {
    public:
      Cubic() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Quadratic (ax^2 + bx + c) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result of the evaluation
    * @param a A pointer to a float that holds the coefficient of the higher order 'x' value
    * @param b A pointer to a float that holds the coefficient of the lower order 'x' value
    * @param c A pointer to a float that holds the constant value applied to the function
    */
    class Quadratic : public MathFunction {
    public:
      Quadratic() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };

    /*  DECORATIVE PATTERN FUNCTIONS  */
    /**
    * Variable Root (ax^(b/c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the 'x' value
    * @param b A pointer to a float that holds the exponent factor applied to the 'x' value
    * @param c A pointer to a float that holds the root factor applied to the 'x' value
    */
    class Root : public MathFunction {
    public:
      Root() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Absolute Value ( a*|x + b| + c ) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result of the evaluation
    * @param a A pointer to a float that holds the coefficient of the 'x' value
    * @param b A pointer to a float that holds the constant value applied to 'x' value
    * @param c A pointer to a float that holds the onstant value applied to the function
    */
    class Absolute : public MathFunction {
    public:
      Absolute() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Exponential ( e^(ax+b) + c ) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the 'x' value
    * @param b A pointer to a float that holds the constant applied to the 'x' value
    * @param c A pointer to a float that holds the constant applied to the function
    */
    class Exponential : public MathFunction {
    public:
      Exponential() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Logarithmic (a * ln(bx + c) + y)
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Logarithmic : public MathFunction {
    public:
      Logarithmic() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Reciprocal ( a / (b * x + c) + y ) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Reciprocal : public MathFunction {
    public:
      Reciprocal() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };

    /*    PERIODIC FUNCTIONS */
    /**
    * Sine (a * sin(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Sine : public MathFunction {
    public:
      Sine() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Cosine (a * cos(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Cosine : public MathFunction {
    public:
      Cosine() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);

    };
    /**
    * Tangent (a * tan(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Tangent : public MathFunction {
    public:
      Tangent() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Secant (a * sec(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Secant : public MathFunction {
    public:
      Secant() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Cosecant (a * csc(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Cosecant : public MathFunction {
    public:
      Cosecant() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Cotangent (a * cot(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Cotangent : public MathFunction {
    public:
      Cotangent() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Arctangent (a * atan(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Arctangent : public MathFunction {
    public:
      Arctangent() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Arccotangent (a * acot(bx+c) + y) Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class Arccotangent : public MathFunction {
    public:
      Arccotangent() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Sawtooth Wave {a*2 *( floor[ (b*x/c) + (1/2)]) + y} Function
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the constant applied to the function on input, holds the result after function call
    * @param a A pointer to a float that holds the coefficient of the function
    * @param b A pointer to a float that holds the coefficient of the 'x' value
    * @param c A pointer to a float that holds the constant applied to the 'x' value
    */
    class SawtoothWave : public MathFunction {
    public:
      SawtoothWave() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Squarewave ( Sgn(SawtoothWave()) )
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the Coefficient of the function on input, holds function result after function call
    * @param a A pointer to a float that holds the Coefficient of the 'x' value
    * @param b A pointer to a float that holds the period of the sawtooth
    * @param c A pointer to a float that holds the constant value applied to the function
    */
    class SquareWave : public MathFunction {
    public:
      SquareWave() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
    /**
    * Ellipse ( c - ((x^2/a) + (y^2/b)) )
    * @param x A pointer to a float that holds the 'x' value being evaluated
    * @param y A pointer to a float that holds the 'y' value being evaluated on input, holds function result after function call
    * @param a A pointer to a float that holds the divisor of the 'x' value
    * @param b A pointer to a float that holds the divisor of the 'y' value
    * @param c A pointer to a float that holds the distance
    */
    class Ellipse : public MathFunction {
    public:
      Ellipse() {}
      void Operation(float *x, float *y, float *a, float *b, float *c);
    };
#endif //	MATHFUNCTIONS_H