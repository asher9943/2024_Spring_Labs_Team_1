#include "heltec_espnow.hpp"

// #define TERM

// #define ROBOT_GRN
#define ROBOT_BLU


/******************************************************************
 *                          Variables
 ******************************************************************
 */

// broadcast MAC address
const uint8_t broadcastAddr_D[] = {0x30,0xC6,0xF7,0x14,0x33,0xBC}; //Donald
const uint8_t broadcastAddr_A[] = {0x78,0x21,0x84,0x9E,0xFA,0xF4}; //Asher
const uint8_t broadcastAddr_S[] = {0x78,0x21,0x84,0x99,0x63,0x24}; //Stephen

// peer info
esp_now_peer_info_t peerInfo;

// message buffers
esp_message espMessageDataTx;
esp_message espMessageDataRx;



/******************************************************************
 *                          Functions
 ******************************************************************
 */

// initialize esp-now
void heltec_espnow_Init(void) {
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    #ifdef TERM
    Serial.println("Error initializing ESP-NOW");
    #endif
    return;
  }


  esp_now_register_send_cb(OnDataSent_Callback);
  esp_now_register_recv_cb(OnDataRecv_Callback);


  #ifndef ROBOT_RED
    memcpy(peerInfo.peer_addr, RED_ADDR, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      
      #ifdef TERM
        Serial.println("Failed to add peer");
      #endif
      return;
    }
  #endif
  #ifndef ROBOT_GRN
    memcpy(peerInfo.peer_addr, GRN_ADDR, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      #ifdef TERM
        Serial.println("Failed to add peer");
      #endif
      return;
    }
  #endif
  #ifndef ROBOT_BLU
    memcpy(peerInfo.peer_addr, BLU_ADDR, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK){
      #ifdef TERM
        Serial.println("Failed to add peer");
      #endif
      return;
    }
  #endif
}

// data sent callback
void OnDataSent_Callback(const uint8_t *mac_addr, esp_now_send_status_t status) {
  #ifdef TERM
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  #endif
}

// data recieve callback
void OnDataRecv_Callback(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&espMessageDataRx, incomingData, sizeof(espMessageDataRx));

  #ifdef TERM
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("Maze obsticle: ");
    Serial.println(espMessageDataRx.maze_obsticle);
    Serial.print("Dual Fates, ready: ");
    Serial.println(espMessageDataRx.dualFates_rdy);
    Serial.print("Dual Fates, value: ");
    Serial.println(espMessageDataRx.dualFates_val);
    Serial.print("Start robot: ");
    Serial.println(espMessageDataRx.start);
    Serial.print("Rescue: ");
    Serial.println(espMessageDataRx.rescue);
    Serial.println();
  #endif

  if(espMessageDataRx.maze_obsticle) {
    // avoid maze obsticle
  } else if(espMessageDataRx.dualFates_rdy) {
    if(espMessageDataRx.dualFates_val) {
      // turn right
    } else {
      // turn left
    }
  } else if(espMessageDataRx.start) {
    // start moving
  } else if(espMessageDataRx.rescue) {
    // rescue red robot
  }
}
