ADC_MODE(ADC_VCC);
#include "arduino-collectd.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
const char *ssid =      "";
const char *password =  "";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  while (time(NULL) < 10000) {
    printf(".");
    delay(500);
  }

  delay(500);
}

void loop() {
  Serial.println("Sending data");
  Collectd c("testhost");
  c.SetType("temperature");
  c.SetTypeInstance("sensor-1");
  c.AddGauge(1.234);
  c.SetTypeInstance("sensor-2");
  c.AddGauge(2.345);
  c.SetType("memory");
  c.SetTypeInstance("freeheap");
  c.AddGauge(ESP.getFreeHeap());
  c.SetType("percent");
  c.SetTypeInstance("heapfrag");
  c.AddGauge(ESP.getHeapFragmentation());
  c.SetType("voltage");
  c.SetTypeInstance("vcc");
  c.AddGauge(ESP.getVcc());
  
  int ret = c.Send("10.255.255.1", 25826);  
  Serial.println(ret);
  delay(30000);
}
