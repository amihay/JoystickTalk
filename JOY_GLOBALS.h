// updates:
// 15-OCT-2020 - Avi created.
//
int xValue = 0; // variable to store x value
int yValue = 0; // variable to store y value
int Pos;

int current_choice = 0;
int gesture_time = 0; // timer to decide that this is the gesture to display
int old_pos = 5;

int loop_delay = LOOP_DELAY;
int gesture_time_limit = GESTURE_TIME;
int reset_time = RESET_TIME; // how long it takes before reseting to start again
