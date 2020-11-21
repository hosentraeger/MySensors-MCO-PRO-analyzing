#define BUILD_MQTT_GATEWAY // either build mqtt gateway or ethernet gateway
// #define USE_SIGNING
#define MY_RADIO_RF24
// #define MY_RADIO_RFM69
#define WEBFRONTEND // provide a webfrontend at port 80 that shows gateway config
#define MY_DEBUG

#define SN "MySensors W5100 Gateway"
#define SV "0.2"

#define MY_MQTT_PUBLISH_TOPIC_PREFIX "mysgw1-out"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "mysgw1-in"
#define MY_MQTT_CLIENT_ID "mysgw1"
#define MY_MQTT_CONTROLLER_IP_ADDRESS 192, 168, 99, 20
#define MY_MQTT_PORT 1883
#define MY_MYSGW_PORT 5003

#define MY_IP_ADDRESS 192,168,99,13
#define MY_MAC_ADDRESS 0xDE, 0xAD, 0xBA, 0xBE, 0x99, 0x13
#define MY_SIGNING_ATSHA204_PIN 17
#define MY_RFM69_NETWORKID (200)
#define MY_RFM69_TX_POWER_DBM 20
#define MY_SERIALDEVICE Serial

#if !defined(MY_W5100_SPI_EN) && !defined(ARDUINO_ARCH_SAMD)
  #define MY_SOFTSPI
  #define MY_SOFT_SPI_SCK_PIN (14)
  #define MY_SOFT_SPI_MISO_PIN (16)
  #define MY_SOFT_SPI_MOSI_PIN (15)
#endif

#ifdef MY_RADIO_RF24
  #define MY_RF24_CE_PIN (5)
  #define MY_RF24_CS_PIN (6)
#elif defined MY_RADIO_RFM69
  #define MY_IS_RFM69HW
  #define MY_RFM69_NEW_DRIVER
  #define MY_RF69_SPI_CS (14)
#else
  #error "only rfm24 or rf69 supported"
#endif

#ifdef BUILD_MQTT_GATEWAY
  #define MY_GATEWAY_MQTT_CLIENT
  #define MY_PORT MY_MQTT_PORT
  #define MY_CONTROLLER_IP_ADDRESS MY_MQTT_CONTROLLER_IP_ADDRESS
#else
  #define MY_GATEWAY_W5100
  #define MY_PORT MY_MYSGW_PORT
#endif

#ifdef USE_SIGNING
  #define MY_SIGNING_ATSHA204_PIN 17
  #define MY_SIGNING_ATSHA204 //!< Hardware signing using ATSHA204A
  #define MY_SIGNING_REQUEST_SIGNATURES
#endif

void printIpAddress ( Stream &s, uint8_t a, uint8_t b, uint8_t c, uint8_t d )
{
  s.print ( a );
  s.print ( "." );
  s.print ( b );
  s.print ( "." );
  s.print ( c );
  s.print ( "." );
  s.print ( d );
}

void printMacAddress ( Stream &s, uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f )
{
  s.print ( a, HEX );
  s.print ( ":" );
  s.print ( b, HEX );
  s.print ( ":" );
  s.print ( c, HEX );
  s.print ( ":" );
  s.print ( d, HEX );
  s.print ( ":" );
  s.print ( e, HEX );
  s.print ( ":" );
  s.print ( f, HEX );
}

void printConfig ( Stream &s, char * lineBreak )
{
  s.print ( F ( "***********************************************" ) );
  s.print ( lineBreak );
  s.print ( SN );
  s.print ( lineBreak );
  s.print ( "Version " );
  s.print ( SV );
  s.print ( lineBreak );
  s.print ( F("own mac address: ") );
  printMacAddress ( s, MY_MAC_ADDRESS );
  s.print ( lineBreak );
  s.print ( F("own network address: ") );
  printIpAddress ( s, MY_IP_ADDRESS );
  s.print ( lineBreak );
#ifdef BUILD_MQTT_GATEWAY
    s.print ( F("Gateway type: mqtt" ) );
    s.print ( lineBreak );
    s.print ( F ( "mqtt controller address: " ) );
    printIpAddress ( s, MY_CONTROLLER_IP_ADDRESS );
    s.print ( lineBreak );
    s.print ( F ( "mqtt controller port: " ) );
    s.print ( MY_MQTT_PORT );
    s.print ( lineBreak );
    s.print ( F ( "mqtt client id: " ) );
    s.print ( MY_MQTT_CLIENT_ID );
    s.print ( lineBreak );
    s.print ( F ( "mqtt publish prefix: " ) );
    s.print ( MY_MQTT_PUBLISH_TOPIC_PREFIX );
    s.print ( lineBreak );
    s.print ( F ( "mqtt subscribe prefix: " ) );
    s.print ( MY_MQTT_SUBSCRIBE_TOPIC_PREFIX );
    s.print ( lineBreak );
#else
    s.print ( F ( "Gateway type: MysGW" ) );
    s.print ( lineBreak );
    s.print ( F ( "network port: " ) );
    s.print ( MY_MYSGW_PORT );
    s.print ( lineBreak );
#endif
  s.print ( F ( "Radio type: " ) );
#ifdef MY_RADIO_RF24
    s.print ( F ( "NRF24" ) );
    s.print ( lineBreak );
#elif defined MY_RADIO_RFM69
    s.print ( F (  "RFM69" ) );
    s.print ( lineBreak );
    s.print ( F ( "network id: " ) );
    s.print ( MY_RFM69_NETWORKID );
    s.print ( lineBreak );
#else
    s.print ( F ( "bad radio defined" ) );
    s.print ( lineBreak );
#endif
  s.print ( F ( "signing: " ) );
#ifdef USE_SIGNING
    s.print ( "yes" );
#else
    s.print ( "no" );
#endif
  s.print ( lineBreak );
}

#include <Ethernet.h>
#include <MySensors.h>
#ifdef WEBFRONTEND
  byte mac[] = { MY_MAC_ADDRESS };
  IPAddress ip ( 192,168,99,13 );
  EthernetServer server ( 80 );
#endif

void setup() 
{
  uint32_t enter = hwMillis();
  while (hwMillis() - enter < (uint32_t)500);
  while(!MY_SERIALDEVICE); // For USB enabled devices, wait for USB enumeration before continuing
  printConfig( MY_SERIALDEVICE, "\n" );
#ifdef WEBFRONTEND
  Ethernet.begin(mac, ip);
#endif
}

void presentation() { }

void loop() 
{
#ifdef WEBFRONTEND
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          printConfig ( client, "<br />" );
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
  #endif
}
