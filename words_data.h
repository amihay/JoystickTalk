// updates:
// 15-OCT-2020 - Avi created.
//
// define the list of gestures their associated words and audio files


typedef struct
{
  int id;
  const char* word;
  const char* audio_file;
} WordsData;

// The word entries id are based on the joystick movment
// Based of the Pos value of the joystick the current_choice is adjusted 
// in the following way current_choice = current_choice*10 + Pos;
// Exception to this is the center position Pos == 5 which is not added
// The center position is used for reset the current_choice by calculating reset_choice
// in similar way reset_choice is incremented each time the Pos == 5

WordsData words_array[] =
{ 
  {2, "yes", "STARWARS.WAV"},
  {6, "no", "6.wav"},    
  {3, "drink", "3.wav"},    
  {4, "want", "4.wav"},    
  {8, "i", "8.wav"},   
  {7, "trip", "7.wav"},   
  {9, "batroom", "9.wav"},   
  {1, "eat", "1.wav"},   
  {236, "come", "1.come"}, 
    {87, "go", "1.go"}, 
  
  // use this as last entry for round robin
  // this is used to prevent overflow when looking the the table entries
  {0,"",""} 
  
};
WordsData *find_word_entry(int id) {
  int i = 0;
  while (words_array[i].id != 0) {
    if (id == words_array[i].id) {
      return (&words_array[i]);
    }
     i++;  
  }
  return 0;
}
