// Allow dynamic adjustments of timers
// this should be disabled when we find a "good set" of timer values

int adjust_timer_time = 0;

// the following function automaticaly adjust timer limits
// it is done by moving the joystick to a specific location and holding it there for 10 seconds
// the adjustment value is MIN_TIMER_VALUE as follows:
//
// ,------------------------------------.
// |location| timer       | adjustments |
// |--------+-------------+-------------|
// | UP     | gesture_time| increase    |
// |--------+-------------+-------------|
// | DOWN   | gesture_time| decrease    |
// |--------+-------------+-------------|
// | LEFT   | loop_delay  | increase    |
// |--------+-------------+-------------|
// | RIGHT  | loop_delay  | decrease    |
// |--------+-------------+-------------|
// | B.LEFT | reset_time  | increase    |
// |--------+-------------+-------------|
// | B.RIGHT| reset_time  | decrease    |
// `------------------------------------'
static int adjustment_pos = 0;
void timers_adjustment(int pos) {
  if ((adjustment_pos == 0) || (adjustment_pos != pos)) {
    adjustment_pos = pos;
    return;
  }
  adjust_timer_time += LOOP_DELAY;
  if (adjust_timer_time >= ADJUST_TIMER_TIME) {
    switch (pos) {
    case 2:
      if (gesture_time_limit <  MAX_TIMER_VALUE) {
         gesture_time_limit += MIN_TIMER_VALUE;
         Serial.print("Increased gesture time: ");
         Serial.println(gesture_time_limit);
      }
      break;
    case 8: 
      if (gesture_time_limit >  (loop_delay + MIN_TIMER_VALUE)) {
        gesture_time_limit -= MIN_TIMER_VALUE;
        Serial.print("Decreased gesture time: ");
        Serial.println(gesture_time_limit);
      }
      break;
    case 4:
      if (loop_delay <  (gesture_time_limit - MIN_TIMER_VALUE)) {
        loop_delay += MIN_TIMER_VALUE;
        Serial.print("Increased loop delay: ");
        Serial.println(loop_delay);
      }
      break;
    case 6: 
      if (loop_delay >  MIN_TIMER_VALUE) {
        loop_delay -= MIN_TIMER_VALUE;
        Serial.print("Decreased loop delay: ");
        Serial.println(loop_delay);
      }
      break;
    case 7:
      if (reset_time <  MAX_TIMER_VALUE) {
        reset_time += MIN_TIMER_VALUE;
        Serial.print("Increased reset time: ");
        Serial.println(reset_time);
      }
      break;
    case 9: 
      if (reset_time >  2*gesture_time_limit) {
        reset_time -= MIN_TIMER_VALUE;
        Serial.print("Decreased reset_time: ");
        Serial.println(reset_time);
      }
      break;
    }
    adjust_timer_time = 0;
  }
}
