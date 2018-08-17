/*
   Config file : define your SSID and password; the port of your WebServer, the path for the
   assistant handler, and its access token.
   From here, you can also create user accounts that can be used on the Web management console. To keep everything simple, you can not create user acccounts from
   the web console.
*/

ESP8266WebServer server(8080); // <- Web server port
const char* ssid = "YourWifiName";
const char* wifiPassword = "YourWifiPassword";
const char* assistantToken = "YourAssistantToken";

const char* usernames[] = { "user1", "user2", "user3", "\0" };
const char* passwords[] = { "changeme", "changeme", "changeme" };

void initWifi () {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    ESP.restart();
  }
}
