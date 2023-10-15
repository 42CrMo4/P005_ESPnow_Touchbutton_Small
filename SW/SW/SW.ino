// https://microcontrollerslab.com/esp-now-one-to-many-esp32-esp8266/
// https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/
// https://techtutorialsx.com/2019/10/20/esp32-getting-started-with-esp-now/
// https://dronebotworkshop.com/esp-now/
// https://randomnerdtutorials.com/get-change-esp32-esp8266-mac-address-arduino/#:~:text=Change%20ESP32%20MAC%20Address%20(Arduino%20IDE)&text=You%20can%20set%20a%20custom,old%20and%20new%20MAC%20Address.


// transmitter

#include <esp_now.h>
#include <WiFi.h>

// Define LED and pushbutton state booleans
//bool buttonDown_0 = false;
//bool buttonDown_1 = false;

// Define LED and pushbutton pins
// #define STATUS_BUTTON_0 0
// #define STATUS_BUTTON_1 1
// #define STATUS_BUTTON_2 1
// #define STATUS_BUTTON_3 4
// #define STATUS_BUTTON_4 5
#define STATUS_BUTTON_6 6

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t Receiver_Address1[] = {0x58, 0xCF, 0x79, 0x07, 0x4C, 0xF8};
uint8_t Receiver_Address2[] = {0x7C, 0x9E, 0xBD, 0x37, 0xCA, 0x84};
uint8_t Receiver_Address3[] = {0x84, 0xCC, 0xA8, 0x5E, 0x52, 0x44};

int x = 0;

typedef struct struct_message {
  int integer;
  char character[100];
} struct_message;

struct_message message;

void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char address[18];
  Serial.print("Sent to: ");
  snprintf(address, sizeof(address), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(address);
  Serial.print(" status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {

  // Pushbutton uses built-in pullup resistor
//  pinMode(STATUS_BUTTON_0, INPUT_PULLUP);
//  pinMode(STATUS_BUTTON_1, INPUT_PULLUP);
//  pinMode(STATUS_BUTTON_2, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(STATUS_BUTTON_6, OUTPUT);

  digitalWrite(STATUS_BUTTON_6, LOW);
  digitalWrite(7, HIGH);

//  if (digitalRead(STATUS_BUTTON_3) == HIGH)
//  {
//    x = 6;
//  }
//  if (digitalRead(STATUS_BUTTON_4) == HIGH)
//  {
//    x = 5;
//  }

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(data_sent);

  esp_now_peer_info_t peerInfo;
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  //  memcpy(peerInfo.peer_addr, Receiver_Address1, 6);
  //  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
  //    Serial.println("Failed to add peer");
  //    return;
  //  }

  memcpy(peerInfo.peer_addr, Receiver_Address2, 6);
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

  

  //  memcpy(peerInfo.peer_addr, Receiver_Address3, 6);
  //  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
  //    Serial.println("Failed to add peer");
  //    return;
  //  }
}

void send(int LED) {
  message.integer = LED;
  strcpy(message.character, "Welcome to Microcontrollerslab! This is test example.");

  esp_err_t outcome = esp_now_send(0, (uint8_t *) &message, sizeof(struct_message));

  if (outcome == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(200);
  digitalWrite(STATUS_BUTTON_6, LOW);
}

void loop() {
send(x);

}
