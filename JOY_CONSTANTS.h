// updates:
// 15-OCT-2020 - Avi created.
//
const int inX = A0; // analog input for x-axis
const int inY = A2; // analog input for y-axis


// Adjust the values as needed

int const timer_adjustment_value = 100;

// the amount of time spent in the center 
// that result in reset of the current_choice
int const RESET_TIME = 3000;// 8 seconds after which to reset
int const GESTURE_TIME = 300;// .5 seconds waiting to choose a gesture
int const MAX_TIMER_VALUE = 20000;
int const MIN_TIMER_VALUE = 100;

int const ADJUST_TIMER_TIME = 10000;
int const LOOP_DELAY = 200; // 0.5 Second
