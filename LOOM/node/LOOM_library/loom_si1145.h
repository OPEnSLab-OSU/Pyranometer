// ================================================================
// ===                        LIBRARIES                         ===
// ================================================================
#include <Wire.h>
#include "Adafruit_SI1145.h"

// ================================================================ 
// ===                       DEFINITIONS                        === 
// ================================================================


// ================================================================ 
// ===                        STRUCTURES                        === 
// ================================================================
struct config_si1145_t {
	uint16_t delay;
};

struct state_si1145_t {
	Adafruit_SI1145 inst_si1145;
	uint16_t visible;
	uint16_t ir;
	uint16_t uvi;
	double uv_wm2;
};


// ================================================================ 
// ===                   GLOBAL DECLARATIONS                    === 
// ================================================================
struct config_si1145_t config_si1145;
struct state_si1145_t  state_si1145;


// ================================================================ 
// ===                   FUNCTION PROTOTYPES                    === 
// ================================================================
bool setup_si1145();
void package_si1145(OSCBundle *, char[], uint8_t port);
void measure_si1145();


// ================================================================ 
// ===                          SETUP                           === 
// ================================================================
//
// Runs any startup for si1145 that should occur on device startup
// 
// @return  Whether or not sensor initialization was successful
//
bool setup_si1145() 
{
	//Setup Here
	bool is_setup;
	if(state_si1145.inst_si1145.begin()){
		is_setup = true;
		config_si1145.delay = 1000;
		LOOM_DEBUG_Println("Initialized si1145");
	}
	else{
		is_setup = false;
		LOOM_DEBUG_Println("Failed to initialize si1145");
	}

  	//Serial.print("FINISHED SETTING UP THERMOPILE\n");
	return is_setup;
}


// ================================================================ 
// ===                        FUNCTIONS                         === 
// ================================================================


// --- PACKAGE si1145 --- (Multiplexer Version)
//
// Adds OSC Message of most recent sensor readings to a provided OSC bundle
//
// @param bndl                  The OSC bundle to be added to
// @param packet_header_string  The device-identifying string to prepend to OSC messages
//   if I2C multiplexer sensor, then also
// [@param port                  Which port of the multiplexer the device is plugged into]
//
void package_si1145(OSCBundle *bndl, char packet_header_string[], int port) 
{
  	//Serial.print("PACKAGING BUNDLE\n");
	char address_string[255];
	sprintf(address_string, "%s%s%d%s", packet_header_string, "/port", port, "/si1145/data");

	OSCMessage msg = OSCMessage(address_string);
  	/*
	msg.add("visible").add((int32_t)state_si1145.visible);
	msg.add("IR").add((int32_t)state_si1145.ir);
	msg.add("UV").add((int32_t)state_si1145.uvi);
    */
	msg.add("UV W/m^2").add((int32_t)state_si1145.uv_wm2);
	
	
	bndl->add(msg);
}

#if is_multiplexer != 1
void package_si1145(OSCBundle *bndl, char packet_header_string[])
{
	char address_string[255];
/*
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", si1145_0x60_name, "_visible");
	bndl->add(address_string).add((int32_t)state_si1145.visible);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", si1145_0x60_name, "_ir");
	bndl->add(address_string).add((int32_t)state_si1145.ir);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", si1145_0x60_name, "_uvi");
	bndl->add(address_string).add((int32_t)state_si1145.uvi);
  */

	//W/m^2
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", si1145_0x60_name, "_uv_wm2");
	bndl->add(address_string).add((int32_t)state_si1145.uv_wm2);
	
}
#endif


// --- MEASURE si1145 ---
//
// Gets the current sensor readings of the <Module and stores into variables
// If debug prints are enabled, can also print any relevant information 
//
void measure_si1145() 
{	
    state_si1145.visible = state_si1145.inst_si1145.readVisible();
    state_si1145.ir = state_si1145.inst_si1145.readIR();
    state_si1145.uvi = (state_si1145.inst_si1145.readUV())/100;
    state_si1145.uv_wm2 = state_si1145.uvi * 0.025;			//translates UVI into W/m^2
	
	
  #if LOOM_DEBUG == 1
    Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
    Serial.print(F("Visible: ")); Serial.print(state_si1145.visible); Serial.print(F("  "));
    Serial.print(F("IR: ")); Serial.print(state_si1145.ir); Serial.print(F("  "));
    Serial.print(F("UV: ")); Serial.print(state_si1145.uvi); Serial.print(F("  "));
    Serial.print(F("UV W/m^2: ")); Serial.print(state_si1145.uv_wm2); Serial.print(F("  "));
  #endif
}
