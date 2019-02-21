// ================================================================
// ===                        LIBRARIES                         ===
// ================================================================
#include <Wire.h>
#include "Adafruit_TMP007.h"

// ================================================================ 
// ===                       DEFINITIONS                        === 
// ================================================================


// ================================================================ 
// ===                        STRUCTURES                        === 
// ================================================================
struct config_tmp007_t {
	uint16_t delay;
};

struct state_tmp007_t {
	Adafruit_TMP007 inst_tmp007;
	uint16_t volt;
	uint16_t obj_temp;
	uint16_t die_temp;
	double sun_energy;
};


// ================================================================ 
// ===                   GLOBAL DECLARATIONS                    === 
// ================================================================
struct config_tmp007_t config_tmp007;
struct state_tmp007_t  state_tmp007;


// ================================================================ 
// ===                   FUNCTION PROTOTYPES                    === 
// ================================================================
bool setup_tmp007();
void package_tmp007(OSCBundle *, char[], uint8_t port);
void measure_tmp007();


// ================================================================ 
// ===                          SETUP                           === 
// ================================================================
//
// Runs any startup for tmp007 that should occur on device startup
// 
// @return  Whether or not sensor initialization was successful
//
bool setup_tmp007() 
{
	//Setup Here
  //Serial.print("SETTING UP THERMOPILE\n");
	bool is_setup;
	state_tmp007.inst_tmp007 = Adafruit_TMP007(0x40);
	if(state_tmp007.inst_tmp007.begin()){
		is_setup = true;
		config_tmp007.delay = 4000;
		LOOM_DEBUG_Println("Initialized tmp007");
	}
	else{
		is_setup = false;
		LOOM_DEBUG_Println("Failed to initialize tmp007");
	}

  //Serial.print("FINISHED SETTING UP THERMOPILE\n");
	return is_setup;
}


// ================================================================ 
// ===                        FUNCTIONS                         === 
// ================================================================


// --- PACKAGE tmp007 --- (Multiplexer Version)
//
// Adds OSC Message of most recent sensor readings to a provided OSC bundle
//
// @param bndl                  The OSC bundle to be added to
// @param packet_header_string  The device-identifying string to prepend to OSC messages
//   if I2C multiplexer sensor, then also
// [@param port                  Which port of the multiplexer the device is plugged into]
//
void package_tmp007(OSCBundle *bndl, char packet_header_string[], int port) 
{
  //Serial.print("PACKAGING BUNDLE\n");
	char address_string[255];
	sprintf(address_string, "%s%s%d%s", packet_header_string, "/port", port, "/tmp007/data");

	OSCMessage msg = OSCMessage(address_string);
  /*
	msg.add("voltage").add((int32_t)state_tmp007.volt);
	msg.add("object_temp").add((int32_t)state_tmp007.obj_temp);
	msg.add("die_temp").add((int32_t)state_tmp007.die_temp);
	msg.add("W/m^2").add((int32_t)state_tmp007.sun_energy);
	*/
	// Just W/m^2 data, no text
	msg.add((int32_t)state_tmp007.sun_energy);
	
	
	bndl->add(msg);
}

#if is_multiplexer != 1
void package_tmp007(OSCBundle *bndl, char packet_header_string[])
{
	char address_string[255];
/*
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", tmp007_0x40_name, "_voltage");
	bndl->add(address_string).add((int32_t)state_tmp007.volt);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", tmp007_0x40_name, "object_temp");
	bndl->add(address_string).add((int32_t)state_tmp007.obj_temp);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", tmp007_0x40_name, "_die_temp");
	bndl->add(address_string).add((int32_t)state_tmp007.die_temp);
  */
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", tmp007_0x40_name, "_sun_energy");
	bndl->add(address_string).add((int32_t)state_tmp007.sun_energy);
	
}
#endif


// --- MEASURE tmp007 ---
//
// Gets the current sensor readings of the <Module and stores into variables
// If debug prints are enabled, can also print any relevant information 
//
void measure_tmp007() 
{
	//helpful links for math: 
	//https://vtechworks.lib.vt.edu/bitstream/handle/10919/37014/chap2.pdf?sequence=3
	//https://www.makeitfrom.com/material-properties/Polylactic-Acid-PLA-Polylactide
	
	//the +273.15 is converting Celsius to Kelvin
	//readings before
	double v_before = state_tmp007.inst_tmp007.readRawVoltage() + 273.15;
	double obj_before = state_tmp007.inst_tmp007.readObjTempC() + 273.15;
	double die_before = state_tmp007.inst_tmp007.readDieTempC() + 273.15;
	
	//delay 4 seconds
	delay(config_tmp007.delay);
	
	//readings after
	double v_after = state_tmp007.inst_tmp007.readRawVoltage() + 273.15;
	double obj_after = state_tmp007.inst_tmp007.readObjTempC() + 273.15;
	double die_after = state_tmp007.inst_tmp007.readDieTempC() + 273.15;


	state_tmp007.volt = v_after;
	state_tmp007.obj_temp = obj_after;
	state_tmp007.die_temp = die_after;

	
	//use Stefan-Boltzmann's Law - total IR radiated from dome, only part of what we want
	double emissivity = 0.91;						//emissivity of PLA and ABS
	double stefan_const = 0.000000056703;					//stefan-boltzmann constant (W/m^2)
	double temp = obj_after * obj_after * obj_after * obj_after;		//T^4 (K)
	double energy_out = emissivity * stefan_const * temp;			//W/m^2

	//delta energy, the other part of what we want
	double mass = 0.002;							//mass of dome (kg)
	//specific heat of ABS = 1423.512 (J/kg-K)
	double cp = 1800.324;							//specific heat (J/kg-K) of dome (PLA)
	double delta_T = obj_after - obj_before;				//change in temperature of object (K)
	double delta_energy = (mass * cp * delta_T)/config_tmp007.delay;	//change in energy over time (W)
		
	//suns total energy - what we want
	state_tmp007.sun_energy = delta_energy + energy_out;			// W/m^2
	
	
	
	
  #if LOOM_DEBUG == 1
    Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
    Serial.print(F("Volts: ")); Serial.print(state_tmp007.volt); Serial.print(F("  "));
    Serial.print(F("Die Temp: ")); Serial.print(state_tmp007.die_temp); Serial.print(F("  "));
    Serial.print(F("Object Temp: ")); Serial.print(state_tmp007.obj_temp); Serial.print(F("  "));
    Serial.print(F("W/m^2: ")); Serial.print(state_tmp007.sun_energy); Serial.print(F("  "));
  #endif
}
