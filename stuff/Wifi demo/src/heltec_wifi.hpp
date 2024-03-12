#ifndef HELTEC_WIFI_H_
#define HELTEC_WIFI_H_

#include <WiFi.h>


/******************************************************************
 *                          Variables
 ******************************************************************
 */

// Server at specified port 
extern WiFiServer server;

// Client
extern WiFiClient client;

// Stores data from client
extern String client_line;



/******************************************************************
 *                          Protoypes
 ******************************************************************
 */

// Wifi initialization, put in setup()
void heltec_Wifi_Init();

/*
 * Connect to client and read data
 */
void process_client();

#endif
