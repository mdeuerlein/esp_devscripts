#include "wled.h"
#include "audio_reactive.h"
/*
 * This v1 usermod file allows you to add own functionality to WLED more easily
 * See: https://github.com/Aircoookie/WLED/wiki/Add-own-functionality
 * EEPROM bytes 2750+ are reserved for your custom use case. (if you extend #define EEPSIZE in const.h)
 * If you just need 8 bytes, use 2551-2559 (you do not need to increase EEPSIZE)
 *
 * Consider the v2 usermod API if you need a more advanced feature set!
 */

/*
 * Functions and variable delarations moved to audio_reactive.h
 * Not 100% sure this was done right. There is probably a better way to handle this...
 */


// This gets called once at boot. Do all initialization that doesn't depend on network here
void userSetup()
{

}

// This gets called every time WiFi is (re-)connected. Initialize own network interfaces here
void userConnected()
{
}

// userLoop. You can use "if (WLED_CONNECTED)" to check for successful connection
void userLoop() {

  if (millis()-lastTime > delayMs) {                       // I need to run this continuously because the animations are too slow
    if (!(audioSyncEnabled & (1 << 1))) {                  // Only run the sampling code IF we're not in Receive mode
      lastTime = millis();
      getSample();                                              // Sample the microphone
      agcAvg();                                                 // Calculated the PI adjusted value as sampleAvg
      myVals[millis()%32] = sampleAgc;
      logAudio();
    }
  }

  // Begin UDP Microphone Sync
  if (audioSyncEnabled & (1 << 1)) {
    // Only run the audio listener code if we're in Receive mode
    if (millis()-lastTime > delayMs) {
      if (udpSyncConnected) {
//        Serial.println("Checking for UDP Microphone Packet");
        int packetSize = fftUdp.parsePacket();
        if (packetSize) {
          // Serial.println("Received UDP Sync Packet");
          uint8_t fftBuff[packetSize];
          fftUdp.read(fftBuff, packetSize);
          audioSyncPacket receivedPacket;
          memcpy(&receivedPacket, fftBuff, packetSize);
          for (int i = 0; i < 32; i++ ){
            myVals[i] = receivedPacket.myVals[i];
          }
          sampleAgc = receivedPacket.sampleAgc;
          sample = receivedPacket.sample;
          sampleAvg = receivedPacket.sampleAvg;
          // VERIFY THAT THIS IS A COMPATIBLE PACKET
          char packetHeader[6];
          memcpy(&receivedPacket, packetHeader, 6);
          if (!(isValidUdpSyncVersion(packetHeader))) {
            memcpy(&receivedPacket, fftBuff, packetSize);
            for (int i = 0; i < 32; i++ ){
              myVals[i] = receivedPacket.myVals[i];
            }
            sampleAgc = receivedPacket.sampleAgc;
            sample = receivedPacket.sample;
            sampleAvg = receivedPacket.sampleAvg;

            // Only change samplePeak IF it's currently false.  If it's true already, then the animation still needs to respond
            if (!samplePeak) {
              samplePeak = receivedPacket.samplePeak;
            }
          }
        }
      }
    }
  }
} // userLoop()
