// On the following arrays, the first number is for cold white, the second is for warm white
int currentColor[] = {0, 0}; // The current color, stored to make the fade effect (set to zero at first to make the fade effect at first launch)
int newColor[] = {1023, 1023}; // The target color, stored to make the fade effect
int backupColor[] = {1023, 1023}; // Backup of the old current color, used to make the ON/OFF fade effect
/*
   SmartLighting Command handler : receives the messages from all interfaces and then interprets them
   There's two types of SLMessages :
   - Instant messages, designed to be applied now (new color...), consisting of a 1 byte command type (instant_byte) + 1 byte command and then a 1+ byte payload.
   - Scheduling messages, designed to create a task that will later call an instant message which consists of :
    1 byte command type (scheduling_byte) + 1 byte command, 1 byte for the hour, 1 byte for the minutes, 1+ byte command payload
    The first byte of both messages is to determine the type of message     1 = Instant message   0 = Scheduling message
    The seconde byte is the command, which is global. Look at the declaration below for details

*/
// GLOBAL BYTES DECLARATION
#define instant_byte 0x01
#define scheduling_byte 0x00

// INSTANT MESSAGES COMMANDS
#define power_off 0x01 // No payload needed
#define power_on 0x02 // No payload needed
#define set_cold_white 0x03 // a 1 byte payload (expecting 0% to 100%)
#define set_warm_white 0x04 // a 1 byte payload (expecting 0% to 100%)
#define set_both 0x05 // a 2 bytes payload (expecting 0% to 100%, two times, the first time for cold)


// UTILITY VARIABLES
#define default_fade_delay 1

void instantMessageHandler (byte command_type, byte command, byte payload[]) {
  if (command_type == instant_byte) { // We're not supposed to receive unwanted messages, but it's still worth checking.
    switch (command) {
      case power_off:
        backupColor[0] = currentColor[0];
        backupColor[1] = currentColor[1];
        newColor[0] = 0;
        newColor[1] = 0;
        regularFadeUpdate(default_fade_delay);
        break;
      case power_on:
        newColor[0] = backupColor[0];
        newColor[1] = backupColor[1];
        regularFadeUpdate(default_fade_delay);
        break;
      case set_cold_white:
        if (payload[0] > 100) { //checking that we do not get more than 100%
          break;
        }
        else {
          currentColor[0] = map(payload[0], 0, 100, 0, 1023);
          regularFadeUpdate(default_fade_delay);
          break;
        }
      case set_warm_white:
        if (payload[0] > 100) { //checking that we do not get more than 100%
          break;
        }
        else {
          currentColor[1] = map(payload[0], 0, 100, 0, 1023);
          regularFadeUpdate(default_fade_delay);
          break;
        }
      case set_both:
        if (payload[0] > 100 || payload[1] > 100 ) { //checking that we do not get more than 100%
          break;
        }
        else {
          currentColor[0] = map(payload[0], 0, 100, 0, 1023);
          currentColor[1] = map(payload[1], 0, 100, 0, 1023);
          regularFadeUpdate(default_fade_delay);
          break;
        }
    }
  }
}


void regularFadeUpdate (byte fadingDelay) { // Fade function that uses delay... dirty but enough for the small amount of time
  while (currentColor[0] != newColor[0] || currentColor[1] != newColor[1]) {
    for (int i = 0; i <= 1; i++) {        // We check through the colors with a for loop, compare them, increase or decrease them and apply the color to make the fade effect
      if (currentColor[i] < newColor[i]) {
        currentColor[i]++;
      }
      if (currentColor[i] > newColor[i]) {
        currentColor[i]--;
      }
      analogWrite(pins[i], currentColor[i]);
    }
    delay(fadingDelay); // Adjust this delay to set your fade speed
  }
}

