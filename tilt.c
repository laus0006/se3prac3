#include <stdio.h>
#include "2048.h"

int tilt_board_left(int size, int **board){
  int i =0;
  for (i =0;i<size;i++){
  //extract a line 
  int list[4]={board[0][i],board[1][i],board[2][i],board[3][i]};
  
  //tilt the line
    tilt_line_left(size, &list);
	
	//save back
	board[0][i] = list[0];
	board[1][i] = list[1];
	board[2][i] = list[2];
	board[3][i] = list[3];
	
  }
  return 0;
}
int tilt_board_right(int size, int **board){
  int i =0;
  for (i =0;i<size;i++){
  //extract a line 
  int list[4]={board[0][i],board[1][i],board[2][i],board[3][i]};
  
  //tilt the line
    tilt_line_right(size, &list);
	
	//save back
	board[0][i] = list[0];
	board[1][i] = list[1];
	board[2][i] = list[2];
	board[3][i] = list[3];
	
  }
  
  return 0;
}

int tilt_board_up(int size, int **board){
  int i =0;
  for (i =0;i<size;i++){
  //tilt the line
    tilt_line_left(size, board[i]);
  }
}

int tilt_board_down(int size, int **board){
  int i =0;
  for (i =0;i<size;i++){
  //tilt the line
    tilt_line_right(size, board[i]);
  }
  return 0;
}

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

  for(src = 1; src < length; src++){
	if(line[src] != 0){
	  for(dest = 0;dest < length && dest < src;dest++){
		if (line[dest] == 0){
		  slide_single_to_left(&line[dest],&line[src]);
		  break;
		}
	  }
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

int tilt_line_right(int length,int *line)
{
  //invert
  if (length == 4){
    int lineL[4] = {line[3],line[2],line[1],line[0]};
	tilt_line_left(length,lineL);
	line[0]=lineL[3];
	line[1]=lineL[2];
	line[2]=lineL[1];
	line[3]=lineL[0];
  }
  
  return 0;
}

int tilt_line_up(int length, int *line){
  tilt_line_left(length, line);  
  return 0;
}

int tilt_line_down(int length, int *line){
  tilt_line_right(length, line);  
  return 0;
}
