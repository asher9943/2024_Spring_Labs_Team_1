#include "heltec_wifi.hpp"


/******************************************************************
 *                          Variables
 ******************************************************************
 */

const char *ssid = "carpeted-kitchen";
const char *password = "czkm443@";

const char *serverName = "198.162.46.240";
const int serverPort = 80;

// Set web server port number to 80
WiFiServer server(serverPort);

// Client
WiFiClient client;



/******************************************************************
 *                          Functions
 ******************************************************************
 */


/*
 * Initialization
 */


/*
 * Wifi initialization, put in setup()
 */
void wifi_Init() {
  Serial.print("Connecting to ");
  Serial.print(ssid);

  // Connect to Wi-Fi network with SSID and password
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address
  Serial.println("\n\nWiFi connected");
  Serial.print  ("IP address:  ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}


/*
 * Tell server to start listening for clients, put in setup()
 */
void server_Init() {
  server.begin();

  Serial.print  ("Server created, listening to port ");
  Serial.println(serverPort);
  Serial.println("");
}


/*
 * Connect to server, put in setup()
 */
void client_Init() {
  Serial.print("Connecting to ");
  Serial.print(serverName);
  Serial.print(" at port ");
  Serial.print(serverPort);

  while(!client.connect(serverName, serverPort)) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("\nConnected");
}



/*
 * Communication functions
 */


/*
 * Check for clients and check their connection
 *
 * return
 *   0 - Client unavalible (No client/client disconneced)
 *   1 - Client connected
 */
int client_check() {
  // If there is currently no client, try to find one
  if(!client) {
    client = server.available();    // Listen for incoming clients
    if(!client) return 0;           // return 0 if no clients
    
    Serial.println("New client");
  }

  if(client.connected()) {    // The client is connected
    return 1;
  } else {                    // The client has disconnected
    client.stop();
    Serial.println("\nClient disconnected\n");
    return 0;
  }
}


/*
 * Read data from client
 *
 * return
 *   0 - No data from client
 *   1 - Data avalible
 */
int client_read(String *client_rx_buff) {
    if(client.available()) {    // if there is data to be read
      // clear buffer
      *client_rx_buff = "";

      // read data
      *client_rx_buff = client.readStringUntil('\n');
      client.flush();

      return 1;
    }
    return 0;
}


/*
 * Write data to client
 */
int client_write(String client_tx_buff) {
  client.println(client_tx_buff);
  client.flush();
}
