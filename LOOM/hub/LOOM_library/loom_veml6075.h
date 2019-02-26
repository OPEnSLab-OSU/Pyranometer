// ================================================================
// ===                        LIBRARIES                         ===
// ================================================================
#include <Wire.h>
#include "Adafruit_VEML6075.h"

// ================================================================ 
// ===                       DEFINITIONS                        === 
// ================================================================


// ================================================================ 
// ===                        STRUCTURES                        === 
// ================================================================
struct config_veml6075_t {
	uint16_t delay;
  veml6075_integrationtime integrationTime;
  bool highDynamicMode;
  bool forcedMode;

  float uva_A_coefficent;
  float uva_B_coefficent;
  float uvb_C_coefficent;
  float uvb_D_coefficent;
  float uva_response;
  float uvb_response;
};

struct state_veml6075_t {
  Adafruit_VEML6075 inst_veml6075;
	uint16_t uva;
	uint16_t uvb;
	uint16_t uvi;
};


// ================================================================ 
// ===                   GLOBAL DECLARATIONS                    === 
// ================================================================
struct config_veml6075_t config_veml6075;
struct state_veml6075_t  state_veml6075;


// ================================================================ 
// ===                   FUNCTION PROTOTYPES                    === 
// ================================================================
bool setup_veml6075();
void package_veml6075(OSCBundle *, char[], uint8_t port);
void measure_veml6075();


// ================================================================ 
// ===                          SETUP                           === 
// ================================================================
//
// Runs any startup for veml6075 that should occur on device startup
// 
// @return  Whether or not sensor initialization was successful
//
bool setup_veml6075() 
{
	//Setup Here
  Serial.print("SETTING UP UV SENSOR\n");
	bool is_setup;
	state_veml6075.inst_veml6075 = Adafruit_VEML6075();
	if(state_veml6075.inst_veml6075.begin()){
		is_setup = true;
		config_veml6075.delay = 1000;

    state_veml6075.inst_veml6075.setIntegrationTime(VEML6075_100MS);
    state_veml6075.inst_veml6075.setHighDynamic(false);
    state_veml6075.inst_veml6075.setForcedMode(false);
    state_veml6075.inst_veml6075.setCoefficients(2.22, 1.33,  // UVA_A and UVA_B coefficients
                     2.95, 1.74,  // UVB_C and UVB_D coefficients
                     0.001461, 0.002591); // UVA and UVB responses

		LOOM_DEBUG_Println("Initialized veml6075");
	}
	else{
		is_setup = false;
		LOOM_DEBUG_Println("Failed to initialize veml6075");
	}

  Serial.print("FINISHED SETTING UP UV SENSOR\n");
	return is_setup;
}


// ================================================================ 
// ===                        FUNCTIONS                         === 
// ================================================================


// --- PACKAGE veml6075 --- (Multiplexer Version)
//
// Adds OSC Message of most recent sensor readings to a provided OSC bundle
//
// @param bndl                  The OSC bundle to be added to
// @param packet_header_string  The device-identifying string to prepend to OSC messages
//   if I2C multiplexer sensor, then also
// [@param port                  Which port of the multiplexer the device is plugged into]
//
void package_veml6075(OSCBundle *bndl, char packet_header_string[], int port) 
{
  Serial.print("PACKAGING BUNDLE\n");
	char address_string[255];
	sprintf(address_string, "%s%s%d%s", packet_header_string, "/port", port, "/veml6075/data");

	OSCMessage msg = OSCMessage(address_string);
	msg.add("uva").add((int32_t)state_veml6075.uva);
	msg.add("uvb").add((int32_t)state_veml6075.uvb);
	msg.add("uvi").add((int32_t)state_veml6075.uvi);
	bndl->add(msg);
}

#if is_multiplexer != 1
void package_veml6075(OSCBundle *bndl, char packet_header_string[])
{
	char address_string[255];

	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", veml6075_0x10_name, "_uva");
	bndl->add(address_string).add((int32_t)state_veml6075.uva);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", veml6075_0x10_name, "_uvb");
	bndl->add(address_string).add((int32_t)state_veml6075.uvb);
	sprintf(address_string, "%s%s%s%s", packet_header_string, "/", veml6075_0x10_name, "_uvi");
	bndl->add(address_string).add((int32_t)state_veml6075.uvi);
}
#endif


// --- MEASURE veml6075 ---
//
// Gets the current sensor readings of the <Module and stores into variables
// If debug prints are enabled, can also print any relevant information 
//
void measure_veml6075() 
{
  Serial.print("MEASURING\n");
	state_veml6075.uva = state_veml6075.inst_veml6075.readUVA();
	state_veml6075.uvb = state_veml6075.inst_veml6075.readUVB();
	state_veml6075.uvi = state_veml6075.inst_veml6075.readUVI();

  #if LOOM_DEBUG == 1
    Serial.print(F("[ ")); Serial.print(millis()); Serial.print(F(" ms ] "));
    Serial.print(F("UVA: ")); Serial.print(state_veml6075.uva); Serial.print(F("  "));
    Serial.print(F("UVB: ")); Serial.print(state_veml6075.uvb); Serial.print(F("  "));
    Serial.print(F("UVI: ")); Serial.print(state_veml6075.uvi); Serial.print(F("  "));
  #endif

  Serial.print("DELAYING\n");
  delay(config_veml6075.delay);
}
