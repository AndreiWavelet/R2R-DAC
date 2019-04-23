/*  -----------------------------------------------------------
 *  Andrei Alves Cardoso 23-04-2019
 *  -----------------------------------------------------------
 *  r2r_dac.h
 *  Cabeçalho contendo declaração da classe da biblioteca R2R DAC,
 *  bem como de todos seus métodos.
 *  -----------------------------------------------------------
 *  Você pode usar livremente esse programa para quaisquer fins,
 *  porém NÃO HÁ GARANTIA para qualquer propósito.
 *  -----------------------------------------------------------
 *  23-04-2019: primeira documentação
 */

#ifndef R2R_DAC_H
#define R2R_DAC_H

#include <stdint.h>
#include "arduino.h"

template <int numBits>
class R2R_DAC{
  public:
    R2R_DAC();
    ~R2R_DAC();

    bool SetBitPin(int bitNum, int pinNum);
    
    void Set(uint16_t value);
    void SetAligned(uint16_t value);
    uint16_t Get();
    uint16_t GetAligned();
  private:
    volatile uint8_t *ports[numBits];
    uint8_t masks[numBits];
    uint16_t currentValue;
};

template <int numBits>
R2R_DAC<numBits>::R2R_DAC(){
  static uint8_t dummy = 0;
  for(int i=0;i<numBits;i++){
    ports[i] = &dummy;
    masks[i] = 0;
  }
  currentValue = 0;
}

template <int numBits>
R2R_DAC<numBits>::~R2R_DAC(){
  return;
}

template <int numBits>
bool R2R_DAC<numBits>::SetBitPin(int bitNum, int pinNum){
  if(bitNum>=numBits){
    return false;
  }

  uint8_t mask = digitalPinToBitMask(pinNum);
  uint8_t portId = digitalPinToPort(pinNum);
  volatile uint8_t *ddr;
  volatile uint8_t *port;

  if(portId==NOT_A_PIN){
    return false;
  }

  ddr = portModeRegister(portId);
  port = portOutputRegister(portId);

  *ddr |= mask;
  *port = ((*port)&(~mask)) | (((1<<bitNum)&currentValue)?(mask):(0));

  ports[bitNum] = port;
  masks[bitNum] = mask;

  return true;
}

template <int numBits>
void R2R_DAC<numBits>::Set(uint16_t value){
  //Save SREG and disable interrupts.
  uint8_t SREGbk = SREG;
  cli();
  
  currentValue = value;
  for(int i=0;i<numBits;i++){
    *ports[i] = (*ports[i] & (~masks[i])) | ( (value&1)?(masks[i]):(0));
    value = value >> 1;
  }

  SREG = SREGbk;
}

template <int numBits>
void R2R_DAC<numBits>::SetAligned(uint16_t value){
  Set(value >> (sizeof(value)*8-numBits));
}

template <int numBits>
uint16_t R2R_DAC<numBits>::Get(){
  return currentValue;
}

template <int numBits>
uint16_t R2R_DAC<numBits>::GetAligned(){
  auto v = Get();
  return v<<(sizeof(v)*8-numBits);
}

#endif
