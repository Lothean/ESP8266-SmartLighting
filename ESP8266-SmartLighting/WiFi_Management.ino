void initWifi () {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(1000);
    ESP.restart();
  }
}

