// #define BUILD_MQTT_GATEWAY // either build mqtt gateway or ethernet gateway
// #define USE_SIGNING
#define MY_DEBUG
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER
#define MY_RF69_SPI_CS (14)
//#define MY_RFM69_NETWORKID (200)
// #define MY_RFM69_TX_POWER_DBM 20
#ifdef BUILD_MQTT_GATEWAY
  #define MY_GATEWAY_MQTT_CLIENT
  #define MY_MQTT_PUBLISH_TOPIC_PREFIX "mysgw1-out"
  #define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "mysgw1-in"
  #define MY_MQTT_CLIENT_ID "mysgw1"
  #define MY_CONTROLLER_IP_ADDRESS 192, 168, 99, 20
  #define MY_PORT 1883
#else
  #define MY_GATEWAY_W5100
  #define MY_PORT 5003
#endif

#define MY_IP_ADDRESS 192,168,2,73
#define MY_MAC_ADDRESS 0xDE, 0xAD, 0xBA, 0xBE, 0x42, 0x73
#ifdef USE_SIGNING
  #define MY_SIGNING_ATSHA204 //!< Hardware signing using ATSHA204A
  #define MY_SIGNING_ATSHA204_PIN 17
  #define MY_SIGNING_REQUEST_SIGNATURES
#endif
#include <Ethernet.h>
#include <MySensors.h>
void setup() { }
void presentation() { }
void loop() { }
