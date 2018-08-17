const byte pins[] = {7, 8}; // I put the pin index upfront :) First one is cold white, second one is warm white!
/*************************************************************************************************************************
      ___________ ____  ____ ___   _____ _____      _____                      __  __    _       __    __  _
     / ____/ ___// __ \( __ )__ \ / ___// ___/     / ___/____ ___  ____ ______/ /_/ /   (_)___ _/ /_  / /_(_)___  ____ _
    / __/  \__ \/ /_/ / __  |_/ // __ \/ __ \______\__ \/ __ `__ \/ __ `/ ___/ __/ /   / / __ `/ __ \/ __/ / __ \/ __ `/
   / /___ ___/ / ____/ /_/ / __// /_/ / /_/ /_____/__/ / / / / / / /_/ / /  / /_/ /___/ / /_/ / / / / /_/ / / / / /_/ /
  /_____//____/_/    \____/____/\____/\____/     /____/_/ /_/ /_/\__,_/_/   \__/_____/_/\__, /_/ /_/\__/_/_/ /_/\__, /
                                                                                       /____/                  /____/
                                                                                                                        
*************************************************************************************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <Ticker.h>
#define TIMER_RESOLUTION 5 // Resolution for scheduling time check, in seconds
//Ticker scheduling;
void setup() {
  //scheduling.attach(TIMER_RESOLUTION, scheduling);
  initWifi();
}

void loop() {
}

