//
// 25-OCT-2020: Avi - reset the gesture time when position changed.
  //                  - Reset all gesture values when gesture time reached even when wor_entry not found.
// 20-OCT-2020: Avi - Increase gesture time only when joystick is in center. When this is done we
//                    always end gesture with 5 so remove it.
// 19-OCT-2020: Avi - when reset the time set old_pos to  5 so gestures will not start with 5
//                  - Don't do auto timer adjustment ie  commented call to timer adjustment.
//                  - made xValue,yVallue locals.
//                  - add call to load_words_array() - it tries to load gestures.txt from the CD
//
// 14-OCT-2020: Avi - updates
// Added second try to find gesture if the original gesture failed and it ends back at the center (pos == 5)
// Modified the calc_position() to have margins between internal squares.
// Also make sure that only if calculated position is not 0 we will set the Pos variable.
// added timer adjustment function so the user can automaticaly adjust time limits.
// moved the print position code to a function and commented the call to it.
// This decreases the noise in the displayed output.
// Added the ARDUINO_R define to be able to build the same code in simulation mode on the PC 
// Changed the initial values of timer constants to work better with the simulator as well.
// comment some output with #if 0 to limit the output.
// Added output of the gesture. It makes the log more readable.
// moved the postion calculation to calc_position()
//
// set to 1 for Real Arduino compile
// for simulator set to 0
//
// 28-OCT-2022: Amihay - some refactoring and cleaning the code
//////////////////////////////////
#define ARDUINO_R 1 // set to 1 for Real Arduino compile, for simulator set to 0


#if (ARDUINO_R == 1)
#include "SD.h" //Lib to read SD card
#include "SPI.h" //SPI lib for SD card
#include "sound_utils.h"

#define SD_ChipSelectPin 10 //Chip select is pin number 10
 
#endif

#include "JOY_CONSTANTS.h"
#include "JOY_GLOBALS.h"

#include "words_data.h"

// has to be after words_data.h


#include "timers_adjustment.h"

#include "calc_position.h"

#include "debug_utils.h"

void setup() {
   
  Serial.begin(9600); // Setup serial connection for print out to console
  Serial.begin(9600); //Serial Com for debugging 

#if (ARDUINO_R == 1)
  init_SD();

  pinMode(inX, INPUT); // setup x input
  pinMode(inY, INPUT); // setup y input
  init_sound();
#else // 
//==
//  pinMode(inX, INPUT_ar); // setup x input
//  pinMode(inY, INPUT_ar); // setup y input
  
  // try to load list of gesture entries from CD

  //load_words_array("gestures.txt");
//==
#endif

 Serial.println("setup completed");
 Serial.println("--------------------------------");

}

void loop() {
  int xValue = analogRead(inX); // reading x value [range 0 -> 1023]
  int yValue = analogRead(inY); // reading y value [range 0 -> 1023]
  int p = calc_position(xValue, yValue);
  //Serial.println( p);
  
  // only if not 0 update the real position
  if (p != 0)
    Pos = p;
  // Enable only if want auto adjustment
  //  timers_adjustment(Pos);

 
#if 0
     if (current_choice == 0) {
        Serial.print("Start sequence: ");
     }
#endif
     if (old_pos != Pos) {
       // uncomment if need to debug 
     print_pos(Pos);
     
      current_choice = current_choice*10 + Pos;

      // Serial.print("current_choice: ");
      // Serial.println(current_choice);
      old_pos = Pos;

      gesture_time = 0; // start gesture time again
     } else {
       // measure the time in the center
       if (Pos == 5)
        gesture_time += loop_delay;
     }
     
  // after some time start from the begining
  // 
  if (gesture_time >= reset_time) {
     if (current_choice != 0) {
        Serial.print("Reset!");
     }
     current_choice = 0;
     gesture_time   = 0;
     old_pos        = 5; // prevent starting with gesture that is 5
  }
  // when notice that the joystick stopped moving for a while 
  // then display/sound the gesture
  if (gesture_time >= gesture_time_limit) {
    if (current_choice == 0)
      gesture_time = 0;
    else {
      // print out values
      Serial.print(" ===> Gesture: ");
      Serial.println(current_choice);
      

      // Every gesture is terminated in the center so just remove the 5
      // but check anyway
      int r = current_choice % 10;
      if (r == 5) 
	current_choice = current_choice / 10;
 
      WordsData* word_entry = 0;
      word_entry = find_word_entry (current_choice);

      // reset the time and gesture even if gesture is not found
      current_choice = 0;
      gesture_time = 0;
      old_pos = 5;

      // if a word was found display it and make the  sound
      if (word_entry != 0) {
        print_word(word_entry->word);
        String sound_file = word_entry->audio_file;

        #if (ARDUINO_R == 1)        
          play_file(sound_file);
        #else
          print_sound_file(sound_file);
        #endif
       } else {
        Serial.println("word not found");
        
       }
    }
  }
  
  // The following delay of 1000ms is only for debugging reasons (it's easier to follow the values on the serial monitor)
  delay(loop_delay); // Probably not needed for most applications
}

void init_SD() {
  if (!SD.begin(SD_ChipSelectPin)) {
     Serial.println("SD fail");
     while(true);  // block running
  }
  
  Serial.println("SD OK!");  
}
