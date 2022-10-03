// updates:
// 15-OCT-2020 - Avi created.
//
//
// calculate the position of the joystick in a 3x3 sqaure
//

int const square_length = 341; // legth of small square 
int const margin        = 50
;  // margin to define the postion

//
//  .-----------. 1023
//  | 1 | 2 | 3 |  ^
//  +-----------+  |
//  | 4 | 5 | 6 |  |
//  +-----------+  y
//  | 7 | 8 | 9 |  |
//  `-----------'  0
//  1023<--- x -0
//
//
int calc_position(int lx, int ly) {
  
  int p = 0;
  // bottom right
  if ((ly<(square_length - margin)) &&  (ly > margin)) {
    if ((lx<(square_length - margin)) && (lx > margin)) {
      p = 9;        
    } else
    // down
    if((lx<(2*square_length - margin)) && (lx > (square_length + margin))) {
      p = 8;
    } else
    // bottom left
    if((lx<(3*square_length - margin)) && (lx > (2*square_length + margin))) {
      p = 7;        
    }
  } else if ((ly<(2*square_length - margin)) &&  (ly >(square_length+ margin))) {
    // right
    if((lx<(square_length - margin)) && (lx >  margin)) {
      p = 6;       
    } else
    // center
    if((lx<(2*square_length - margin)) && (lx > (square_length + margin))) {
  p = 5;       
    } else
      // left
    if((lx<(3*square_length - margin)) && (lx > (2*square_length + margin))) {
  p = 4;       
    }
  } else if ((ly<(3*square_length - margin)) &&  (ly >(2*square_length+ margin))) {
    // top right
    if ((lx<(square_length - margin)) && (lx > margin)) {
      p = 3;       
    } else
    // up 
    if ((lx<(2*square_length - margin)) && (lx >(square_length + margin))) {
      p = 2;       
    } else 
    // top left 
    if ((lx<(3*square_length - margin)) && (lx >(2*square_length + margin))) {
      p = 1;       
    }
  }
  return p;
}
