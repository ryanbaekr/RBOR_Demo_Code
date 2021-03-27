#include "ESP8266.h"
#include <RBOR.h>

#define SSID        "DIRECT-63-HP Officejet 4724"
#define PASSWORD    "bypassrowan"
#define HOST_NAME   "192.168.1.3"
#define HOST_PORT   (44444)

ESP8266 wifi(Serial2, 115200);

char command[3]; // can't access buffer directly for some reason but I can store a copy in here

RBOR robot;

void setup(void)
{
  Serial.begin(9600);
  Serial.print("setup begin\r\n");

  Serial.print("FW Version:");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStationSoftAP()) {
    Serial.print("to station + softap ok\r\n");
  } else {
    Serial.print("to station + softap err\r\n");
  }

  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  if (wifi.registerUDP(HOST_NAME, HOST_PORT)) {
    Serial.print("register udp ok\r\n");
  } else {
    Serial.print("register udp err\r\n");
  }

  char *hello = "password";
  wifi.send((const uint8_t*)hello, strlen(hello));

  robot.Start();

  Serial.print("setup end\r\n");
}

void loop(void)
{
  uint8_t buffer[128] = {0};

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    for (uint32_t i = 0; i < len; i++) {
      command[i] = buffer[i];
    }
    if (analogRead(A1) < 300) {
      if (strcmp(command, "fo") == 0) {
        robot.CrawlForward();
      }
      if (strcmp(command, "ba") == 0) {
        robot.CrawlBackward();
      }
      if (strcmp(command, "le") == 0) {
        robot.CrawlLeft();
      }
      if (strcmp(command, "ri") == 0) {
        robot.CrawlRight();
      }
      if (strcmp(command, "tl") == 0) {
        robot.TurnLeft();
      }
      if (strcmp(command, "tr") == 0) {
        robot.TurnRight();
      }
    }
  }
}
