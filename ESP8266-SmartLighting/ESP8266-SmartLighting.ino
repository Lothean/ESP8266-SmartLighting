/*************************************************************************************************************************
      ___________ ____  ____ ___   _____ _____      _____                      __  __    _       __    __  _
     / ____/ ___// __ \( __ )__ \ / ___// ___/     / ___/____ ___  ____ ______/ /_/ /   (_)___ _/ /_  / /_(_)___  ____ _
    / __/  \__ \/ /_/ / __  |_/ // __ \/ __ \______\__ \/ __ `__ \/ __ `/ ___/ __/ /   / / __ `/ __ \/ __/ / __ \/ __ `/
   / /___ ___/ / ____/ /_/ / __// /_/ / /_/ /_____/__/ / / / / / / /_/ / /  / /_/ /___/ / /_/ / / / / /_/ / / / / /_/ /
  /_____//____/_/    \____/____/\____/\____/     /____/_/ /_/ /_/\__,_/_/   \__/_____/_/\__, /_/ /_/\__/_/_/ /_/\__, /
                                                                                       /____/                  /____/

*************************************************************************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#define user_count 3
#define TIMER_RESOLUTION 3 // Resolution for scheduling time check, in seconds
#define session_expire 25 // Number of seconds of inactivity before the web session expires
Ticker scheduling;
/*
   Config part : define your SSID and password; the port of your WebServer, the path for the
   assistant handler, and its access token.
   From here, you can also create user accounts that can be used on the Web management console. To keep everything simple, you can not create user acccounts from
   the web console.
*/
const int pins[2] = {16, 0}; // First one is cold white, second one is warm white!
ESP8266WebServer server(8080); // <- Web server port
const char* ssid = "FreeWifiTH";
const char* wifiPassword = "0231962944";
const char* assistantToken = "YourAssistantToken";

const char* usernames[user_count] = { "user1", "user2", "user3" };
const char* passwords[user_count] = { "changeme", "changeme", "changeme" };
long int loginCookie[user_count] = { 0, 0, 0 };
long int loginCookieTicks[user_count] = { 0, 0, 0 };
const int qtyOfTicksBeforeExpiring = session_expire / TIMER_RESOLUTION;


void initWifi () {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    ESP.restart();
  }
}
void setup() {
  scheduling.attach(TIMER_RESOLUTION, schedulingThing);
  Serial.begin(115200);
  initWifi();
  initWeb();
  analogWrite(pins[0], 0);
  analogWrite(pins[1], 0);
}

void loop() {
  server.handleClient();

}

void schedulingThing () {
  for (int i = 0; i < user_count; i++) {
    loginCookieTicks[i]++;
    if (loginCookieTicks[i] >= qtyOfTicksBeforeExpiring) {
      createCookie(i);
    }
  }
}

