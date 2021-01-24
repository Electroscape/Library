
#include "StandardBox.h"


Expander_PCF8574 		Global_STB_Expander[8] 	= {};
uint8_t 						Global_UsedExpanders		= 0;

STB_Board::STB_Board(){}

uint8_t STB_Board::Expander_init(uint8_t I2C_Address){
	if (Global_UsedExpanders>=8)
		Global_UsedExpanders = 0;
	Global_STB_Expander[Global_UsedExpanders].begin(I2C_Address);
//Serial.println("Expander Created");
//	_I2C_Address = I2C_Address;
//	_ExpanderNum = Global_UsedExpanders++;
	return Global_UsedExpanders++;
}

uint8_t STB_Board::Expander_getI2CAdd(){
	uint8_t value = _I2C_Address;
	return	 value;
}

uint8_t STB_Board::Expander_getNumber(){
	uint8_t value = _ExpanderNum;
	return value;
}

bool	STB_Board::Inputs_initAll(uint8_t amount, uint8_t expanderNum){
	_iExpander = expanderNum;
	_iAmount 	 = amount;
			for( int i=0; i<amount; i++ ) {
				_inputs[i].init(i, expanderNum);
			}
	return true;
	}

bool	STB_Board::Inputs_initAll(uint8_t amount, uint8_t expanderNum, uint8_t *state){
	_iExpander = expanderNum;
	_iAmount 	 = amount;
	for( int i=0; i<amount; i++ ) {
		_inputs[i].init(i, expanderNum);
		state[i] = _inputs[i].read();
	}
	return true;
	}

bool	STB_Board::Inputs_readAll(uint8_t *state){
		for( int i=0; i<_iAmount; i++ ) {
			state[i] = _inputs[i].read();
		}
		return true;
	}


bool	STB_Board::Inputs_readPin(uint8_t pin){
			bool value = _inputs[pin].read();
			return value;
		}

void	STB_Board::Output_initAll(uint8_t amount, uint8_t expanderNum){
			_oExpander = expanderNum;
			for( int i=0; i<amount; i++ ) {
				_output[i].init(i,expanderNum);
			}
	}

void	STB_Board::Output_initAll(uint8_t amount, uint8_t expanderNum, uint8_t *init){
			_oExpander = expanderNum;
			for( int i=0; i<amount; i++ ) {
				_output[i].init(i, expanderNum, init[i]);
			}
	}

InputPin::InputPin(){}

void InputPin::init(uint8_t pin, uint8_t expander){
	_pinNumber 		= pin;
	_usedExpander 	= expander;
	Global_STB_Expander[expander].pinMode(pin, INPUT);
	//delay(100);
	//Serial.print("Input "); Serial.print(_PinNumber); Serial.println(" OK");
}

bool InputPin::read(void){
 bool value = Global_STB_Expander[_usedExpander].digitalRead(_pinNumber);
 return value;
}

OutputPin::OutputPin(){}

void OutputPin::init(uint8_t pin, uint8_t expander){
	_state 					= OFF;
	_PinNumber 			= pin;
	_UsedExpander 	= expander;
	Global_STB_Expander[expander].pinMode(pin, OUTPUT);
	//delay(100);
  Global_STB_Expander[expander].digitalWrite(pin, _state);
  //delay(100);
	//Serial.print("     ");
	//Serial.print("Relay ["); Serial.print(_PinNumber); Serial.print("] set to "); Serial.println(_state);
  //delay(20);
  //Serial.println();
}

void OutputPin::init(uint8_t pin, uint8_t expander, uint8_t init){
	_state 					= init;
	_PinNumber 			= pin;
	_UsedExpander 	= expander;
	Global_STB_Expander[expander].pinMode(pin, OUTPUT);
	//delay(100);
  Global_STB_Expander[expander].digitalWrite(pin, init);
  //delay(100);
	//Serial.print("     ");
	//Serial.print("Relay ["); Serial.print(_PinNumber); Serial.print("] set to "); Serial.println(init);
  //delay(20);
  //Serial.println();
}

void OutputPin::on(void){
	_state 				= ON;
  Global_STB_Expander[_UsedExpander].digitalWrite(_PinNumber, _state);
  //delay(100);
}

void OutputPin::off(void){
	_state 				= OFF;
  Global_STB_Expander[_UsedExpander].digitalWrite(_PinNumber, _state);
  //delay(100);
}

void OutputPin::set(uint8_t value){
	_state 				= value;
  Global_STB_Expander[_UsedExpander].digitalWrite(_PinNumber, _state);
  //delay(100);
}

void OutputPin::toggle(void){
	_state 				= _state == HIGH? LOW : HIGH;
  Global_STB_Expander[_UsedExpander].digitalWrite(_PinNumber, _state);
  //delay(100);
}
