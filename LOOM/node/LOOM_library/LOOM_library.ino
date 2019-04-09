// ================================================================
// ===              INCLUDE CONFIGURATION FILE                  ===
// ===    INCLUDE DECLARATIONS, STRUCTS, AND FUNCTIONS FROM     ===
// ===            OTHER FILES AS SET IN CONFIG.H                ===
// ================================================================

// Config has to be first has it hold all user specified options
#include "config.h"

// Preamble includes any relevant subroutine files based 
// on options specified in the above config
#include "loom_preamble.h"

// ================================================================ 
// ===                           SETUP                          ===
// ================================================================ 
void setup() 
{
  //delay 1 minute before beginning to give time to put the lid on and get the pyrometer setup
  //delay(1000 * 60);

  //delete the existing data file
  sd_delete_file("pyro.csv");

  // LOOM_begin calls any relevant (based on config) LOOM device setup functions
  Loom_begin(); 

  // Any custom setup code
}


// ================================================================ 
// ===                        MAIN LOOP                         ===
// ================================================================ 
void loop() 
{

  OSCBundle bndl, send_bndl;      // Declare bundles to hold incoming and outgoing data

  measure_sensors();          // Read sensors, store data in sensor state struct
  package_data(&send_bndl);     // Copy sensor data from state to provided bundle
  send_bundle(&send_bndl, LORA);    // Send bundle of packaged data

  log_bundle(&send_bndl,SDCARD, "pyro.csv"); //filename for SD files
  additional_loop_checks();     // Miscellaneous checks

}


// ================================================================ 
// ===                 High-Level API Functions                 === 
// ================================================================ 

//
// void receive_bundle(OSCBundle *bndl, CommPlatform platform);
// void process_bundle(OSCBundle *bndl);
// void measure_sensors();
// void package_data(OSCBundle *send_bndl);
// void send_bundle(OSCBundle *send_bndl, CommPlatform platform, int port);
// void send_bundle(OSCBundle *send_bndl, CommPlatform platform);
// void log_bundle(OSCBundle *send_bndl, LogPlatform platform, char* file); //filename for SD files
// void log_bundle(OSCBundle *send_bndl, LogPlatform platform);
// bool bundle_empty(OSCBundle *bndl);
// void additional_loop_checks();
