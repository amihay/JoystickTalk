// ======================================
// Debug utils functions
// Created by Amihay Hollinger 28/9/2022
// ======================================
#ifndef DEBUG_UTILS
#define DEBUG_UTILS

void muki() {
  Serial.println("Muki");
}

void print_word(const char* word) {
  Serial.print("word is: ");
  Serial.print(word);
  Serial.print(" ====> ");
}

void print_sound_file(String sound_file) {
  Serial.print("playing: ");
  Serial.println(sound_file);
}

// 15-OCT-2020 - print_pos(int pos) created by Avi.
// print the position of the joystick: "center", "right", "up"...
void print_pos(int pos) {
      switch(pos) {
        case 1:
             Serial.print("Top Left, ");
           break;
        case 2:
             Serial.print("Up, ");
           break;
        case 3:
             Serial.print("Top Right, ");
           break;
        case 4:
             Serial.print("Left, ");
           break;
        case 5:
             Serial.print("Center, ");
           break;
        case 6:
             Serial.print("Right, ");
           break;
        case 7:
             Serial.print("Bottom Left, ");
           break;
        case 8:
             Serial.print("Down, ");
           break;
        case 9:
             Serial.print("Bottom Right ");
           break;
      }
}
#endif
