#include <stdio.h>
#include "2048.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char **argv)
{
  // Randomise random unmber generator initial state.
  srandom(time(0));
  
  int board_size=4;
  int **board=board_create(board_size);
  if (!board) {
    printf("failed to create board.\n");
    exit(0);
  }

  while(1) {
    board_display(board_size,board);
    printf("Next move? "); fflush(stdout);
    int action=read_input();
    switch(action) {
    case GO_LEFT:
	  tilt_board_left(board_size, board);
      break;
    case GO_RIGHT:
	tilt_board_right(board_size, board);
      break;
    case GO_UP:
	tilt_board_up(board_size, board);
      break;
    case GO_DOWN:
	tilt_board_down(board_size, board);
      break;
    case GO_NOWHERE:
      break;
    case INVALID_INPUT:
    default:
      printf("Invalid input. Type l, r, u or d to tilt board.\n");
      break;
    }
	board_spawn_tile(board_size, board);
  }
}
