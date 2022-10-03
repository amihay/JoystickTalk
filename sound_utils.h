// ======================================
// A wrapper for sound functions
// Created by Amihay Hollinger 28/9/2022
// ======================================
#ifndef SOUND_UTILS
#define SOUND_UTILS

#include "TMRpcm.h" //Lib to play auido
#include "debug_utils.h"

TMRpcm sound;

void init_sound() {
  sound.speakerPin = 9; //Auido out on pin 9
  sound.setVolume(5);    //   0 to 7. Set volume level
  sound.quality(1);      //  Set 1 for 2x oversampling Set 0 for normal
  Serial.println("TMRpcm initialized OK");
}

void play_file(String filename) {
  print_sound_file(filename);
  
  // Compile warning here, for some reason play() expect char* and not const char*
  sound.play(filename.c_str());
  while(sound.isPlaying()){
    Serial.print(".");
    delay(200);  
  }
  
  Serial.println("played!");
}

#endif
