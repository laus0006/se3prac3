#include <stdio.h>
#include "2048.h"

int tilt_line_left(int length,int *line)
{
  // make sure vector length is sensible
  if (length<1||length>255) return -1;
  
  // slide tiles to the left
  int src;
  int dest;
  for(dest=0;dest<length-1;dest++){
    for(src = 1;src<length;src++){
      if(line[src] != 0 && line[dest] == 0){
	line[dest] = line[src];
	line[src] = 0;
	break;
      }
    }
  }
  // combine tiles as required

  return 0;
}
