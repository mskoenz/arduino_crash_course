#ifndef mux_READ_HEADER
#define mux_READ_HEADER

#include <Arduino.h>

/*
This Header allows to read from mux_read_class in a nice way.
Up to now 8 (3) and 16 (4) mux are usable (controlable with n = control pins).
The bool digital asks if one want to read digital or analog.
*/

inline int pow2(int expo)
{
  int res = 1;
  res = res << expo;
  return res;
}

template <int nt, bool defaultReadDigital>
class mux_read_class
{
  public:
    void mux_read_setup()
    {
      for(int i = 0; i < n; ++i)
        pinMode(conPin[i], OUTPUT);
      for(int i = 0; i < nSP; ++i)
      {
        digital[i] = defaultReadDigital;
      }
      pinMode(outPin, INPUT);
    }
    mux_read_class(int op, int cp0, int cp1, int cp2): outPin(op), n(nt), nSP(pow2(nt))
    {
      conPin[0] = cp0;
      conPin[1] = cp1;
      conPin[2] = cp2;
    }
    mux_read_class(int op, int cp0, int cp1, int cp2, int cp3): outPin(op), n(nt), nSP(pow2(nt))
    {
      conPin[0] = cp0;
      conPin[1] = cp1;
      conPin[2] = cp2;
      conPin[3] = cp3;
    }
    
    inline void selectPin(int subPin)
    {
      for(int i = 0; i < n; ++i)
      {
        digitalWrite(conPin[i], subPin & pow2(i));
      }
    }

    inline int readIn(int subPin)
    {
      selectPin(subPin);
      if(digital[subPin])
        return digitalRead(outPin);
      else
        return analogRead(outPin);
    }
    inline int operator[](int subPin)
    {
		return readIn(subPin);
	}
    
    inline void readAll(int array[nt])
    {
      for(int i = 0; i < nSP; ++i)
      {
        array[i] = readIn(i);
      }
    }
    
    inline void read_all_fast_4(byte array[nt]) //Factor 17.3 faster than readAll!
    {
		 digitalWrite(conPin[0], LOW);
		 digitalWrite(conPin[1], LOW);
		 digitalWrite(conPin[2], LOW);
		 digitalWrite(conPin[3], LOW);
		 array[0] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], HIGH);
		 array[1] = digitalRead(outPin);
		 
		 digitalWrite(conPin[1], HIGH);
		 array[3] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], LOW);
		 array[2] = digitalRead(outPin);
		 
		 digitalWrite(conPin[2], HIGH);
		 array[6] = digitalRead(outPin);
		 
		 digitalWrite(conPin[1], LOW);
		 array[4] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], HIGH);
		 array[5] = digitalRead(outPin);
		 
		 digitalWrite(conPin[1], HIGH);
		 array[7] = digitalRead(outPin);
		 
		 digitalWrite(conPin[3], HIGH);
		 array[15] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], LOW);
		 array[14] = digitalRead(outPin);
		 
		 digitalWrite(conPin[1], LOW);
		 array[12] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], HIGH);
		 array[13] = digitalRead(outPin);
		 
		 digitalWrite(conPin[2], LOW);
		 array[9] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], LOW);
		 array[8] = digitalRead(outPin);
		 
		 digitalWrite(conPin[1], HIGH);
		 array[10] = digitalRead(outPin);
		 
		 digitalWrite(conPin[0], HIGH);
		 array[11] = digitalRead(outPin);
    }
    
    
    inline int getSize()
    {
      return nSP;
    }
    
    inline void read_digital(int subPin)
    {
      digital[subPin] = true;
    }
    inline void read_analog(int subPin)
    {
      digital[subPin] = false;
    }
  private:
    int outPin;
    int conPin[nt];
    bool digital[(1<<nt)];
    int n;
    int nSP;
};

#endif
