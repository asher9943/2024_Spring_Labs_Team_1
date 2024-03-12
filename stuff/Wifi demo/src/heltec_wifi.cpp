#include "heltec_wifi.hpp"
// #include "movement.hpp"


/******************************************************************
 *                          Variables
 ******************************************************************
 */

const char *ssid = "carpeted-kitchen";
const char *password = "czkm443@";
const int serverPort = 80;

// Set web server port number to 80
WiFiServer server(serverPort);

// Client
WiFiClient client;

// Stores data from client
String client_buff = "";



/******************************************************************
 *                          Functions
 ******************************************************************
 */


/*
 * Wifi server initialization, put in setup()
 */
void heltec_Wifi_Init() {
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.print(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  delay(100);

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print  ("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print  ("Port:       ");
  Serial.println(serverPort);
  Serial.println("");

  server.begin();

  client = server.available(); 
}


/*
 * Connect to client and read data
 */
void process_client() {
  if(!client) {                   // If there is no client
    client = server.available();    // Listen for incoming clients
    if(!client) return;             // No clients
    
    Serial.println("New client");
  }

  if(client.connected()) {        // if the client is connected
    if(client.available()) {        // if there is data to be read
      // read data
      while(client.available()) {
        char c = client.read();
        if((c == '\r') || (c == '\n')) break;
        client_buff += c;
      }
      Serial.println(client_buff);

      // process command
    
      // disconnect client
      if(client_buff == "disconnect") {
        client.stop();
        Serial.println("\nClient disconnected\n");
      }
    
      client_buff = "";
    }
  } else {
    // client is disconnected
    client.stop();
    Serial.println("\nClient disconnected\n");
  }
}

