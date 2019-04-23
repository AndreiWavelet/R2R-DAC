# R2R_DAC

R2R DAC library for Arduino. It allows up to 16 bits R2R DAC with any pin.

This software is released into the public domain. See LICENSE for more info.

## Em português

Biblioteca DAC R2R para Arduino. Permite um DAC R2R de até 16 bits com quaisquer pinos.

Esse software está liberado em domínio público. Você pode usar livremente para qualquer propósito, mas SEM QUALQUER GARANTIA. Consulte o documento de licença (LICENSE) para mais informação.

## How to use

### 1. Instance a R2R_DAC object with the number of DAC bits at the template parameter:

R2R_DAC<n> object_name;

Example for a 6 bit DAC:
R2R_DAC<6> my_dac;

### 2. Register pins:

R2R_DAC::SetBitPin(bit, pin);

You must register every pin you use. Bit 0 is the LSb.

Example for a 6 bit DAC at Arduino pins 3 (LSb), 4, 6, 9, 10, 13 (MSb):

my_dac.SetBitPin(0, 3);

my_dac.SetBitPin(1, 4);

my_dac.SetBitPin(2, 6);

my_dac.SetBitPin(3, 9);

my_dac.SetBitPin(4, 10);

my_dac.SetBitPin(5, 13);


### 3. Set output value:

R2R_DAC::Set(value);
R2R_DAC::SetAligned(value);

### 4. Get last output value:

R2R_DAC::Get(value);
R2R_DAC::GetAligned(value);
