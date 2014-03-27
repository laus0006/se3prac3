#include <stdio.h>
#include "2048.h"

int slide_single_to_left(int *int1, int *int2){
  if(*int1 == 0 && *int2 != 0){
    *int1 = *int2;
    *int2 = 0;
  }
  return 0;
}

int slide_tiles_to_left(int length, int *line){
  int src;
  int dest;
  for(dest=0;dest<length-1;dest++){
    for(src = 1;src<length;src++){
      slide_single_to_left(&line[dest],&line[src]);
    }
  }
  return 0;
}

int tilt_line_left(int length,int *line)
{
  // make sure vector length is sensible
  if (length<1||length>255) return -1;
  
  // slide tiles to the left
  slide_tiles_to_left(length, line);
  int src;
  // combine tiles as required
  for(src=0;src<length-1;src++){
    if (line[src] == line[src+1]){
      line[src] *= 2;
      line[src+1] = 0;
      //move current element along
      src += 1;
    }
  }
  
  // slide tiles to the left
  slide_tiles_to_left(length, line);


  return 0;
}


