
#ifndef STANDARDBOX_H
#define STANDARDBOX_H

// I2C Port Expander
#include <PCF8574.h>

#include "STB-conf.h"

enum OUTPUT_ACT_LOW{
				 ON,
				 OFF,
				 SET,
				 TOGGLE
};

class InputPin
{
public:
	InputPin();
	void init(uint8_t pin, uint8_t expander);
 	bool read(void);
private:
	uint8_t _pinNumber;
	uint8_t _usedExpander;
};

class OutputPin
{
public:
 	OutputPin();
	void init(uint8_t pin, uint8_t expander);
	void init(uint8_t pin, uint8_t expander, uint8_t init);
 	void on();
 	void off();
 	void set(uint8_t value);
 	void toggle();
private:
	uint8_t _PinNumber;
	uint8_t _UsedExpander;
	uint8_t _state;
};

class STB_Board
{
public:
	STB_Board();
	uint8_t	Expander_init(uint8_t I2C_Address);
	uint8_t Expander_getI2CAdd();
	uint8_t Expander_getNumber();
	bool		Inputs_initAll(uint8_t amount, uint8_t expanderNum);
	bool		Inputs_initAll(uint8_t amount, uint8_t expanderNum, uint8_t *state);
	//bool 		KeypadInit(void);
	//bool 		KeypadInit(uint8_t address);
	bool 		Inputs_readAll(uint8_t *state);
	bool 		Inputs_readPin(uint8_t pin);
	void 		Output_initAll(uint8_t amount, uint8_t expander);
	void 		Output_initAll(uint8_t amount, uint8_t expander, uint8_t *init);
private:
	InputPin 	_inputs[8];
	uint8_t		_iAmount;
	uint8_t		_iExpander;
	OutputPin _output[8];
	uint8_t		_oAmount;
	uint8_t		_oExpander;
	uint8_t 	_I2C_Address;
	uint8_t 	_ExpanderNum;
};

#endif
