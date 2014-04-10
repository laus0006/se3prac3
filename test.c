#include <stdio.h>
#include "2048.h"
//tilt board left
/* int tbl(int size, int **boardStart, int **boardEnd){
  printf("Tilting\n");
  board_display(size, boardStart);
  printf("\ninto\n");
  board_display(size,boardEnd);
  
  tilt_board_left(size, boardStart);
  
  int x,y;
  for( x = 0;x < size;x++){
	for( y=0;y<size;y++){
	  if (boardStart[x][y] != boardEnd[x][y]){
	    printf("Failed at element (%d,%d)\n Was %d, should be %d."
		,x,y,boardStart[x][y],boardEnd[x][y]);
	    return -1;
	  }
	}
  }
  printf("Success");
  return 1;
} */
 
int line_vector_test(int i1,int i2,int i3,int i4,char *msg,
                int o1,int o2,int o3,int o4, int (*func)(int,int *))
{
  int list[4]={i1,i2,i3,i4};
  if (msg) printf("%s - ",msg); 
  else {
    printf("Tilting {%d,%d,%d,%d} left yields {%d,%d,%d,%d} - ",
             i1,i2,i3,i4,o1,o2,o3,o4);
  }
  fflush(stdout);
  func(4,list);
  if ((list[0]!=o1)||(list[1]!=o2)||(list[2]!=o3)||(list[3]!=o4))
    {
      printf("FAILED: {%d,%d,%d,%d} became {%d,%d,%d,%d} instead of"
             " {%d,%d,%d,%d}\n",
             i1,i2,i3,i4,list[0],list[1],list[2],list[3],
             o1,o2,o3,o4);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

int ttl_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_left);
}

int ttr_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_right);
}

int ttu_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_up);
}

int ttd_vector(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,tilt_line_down);
}

int ttl_vector_slide_left(int i1,int i2,int i3,int i4,char *msg,
               int o1,int o2,int o3,int o4)
{
  return line_vector_test(i1,i2,i3,i4,msg,o1,o2,o3,o4,slide_tiles_to_left);
}

int ttl_slide_single_left(int i1, int i2, char *msg, int o1, int o2,
  						int (*func)(int *,int *)){
  int list[2]={i1,i2};

  if (msg) printf("%s - ",msg); 
  else {
    printf("Tilting {%d,%d} left yields {%d,%d} - ",
             i1,i2,o1,o2);
  }
  fflush(stdout);
  func(&list[0],&list[1]);
  //tilt_line_left(4, list);
  if ((list[0]!=o1)||(list[1]!=o2))
    {
      printf("FAILED: {%d,%d} became {%d,%d} instead of"
             " {%d,%d}\n",
             i1,i2,list[0],list[1],
             o1,o2);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

int test_slide_single_left(){
  int e=0;
  e|=ttl_slide_single_left(0,1, "Value on right shifts to left",1,0,slide_single_to_left);
  e|=ttl_slide_single_left(1,0, "Value on left stays to left",1,0,slide_single_to_left);
  e|=ttl_slide_single_left(2,4, "Distinct Values don't combine",2,4,slide_single_to_left);
  e|=ttl_slide_single_left(2,1, "Combinations keep order",2,1,slide_single_to_left);
  return e;
}

int test_slide_left(){
  int e=0;
  e|=ttl_vector_slide_left(0,0,0,0,"Empty list is empty after shift",0,0,0,0);
  e|=ttl_vector_slide_left(1,0,0,0,"Value on left stays on left after shift",1,0,0,0);
  e|=ttl_vector_slide_left(0,0,0,1,"Value on right shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector_slide_left(0,0,1,0,"Value in (right) middle shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector_slide_left(0,1,0,0,"Value in (left) middle shifts to left edge after shift",1,0,0,0);
  e|=ttl_vector_slide_left(2,0,2,0,"non-1 value tiles shift left",2,2,0,0);
  e|=ttl_vector_slide_left(2,0,2,8,"Alternate value tiles stay in order",2,2,8,0);
  e|=ttl_vector_slide_left(2,0,2,0,"Value in (left) middle shifts to left edge after shift",2,2,0,0);
  return e;
}

int test_tilt_left()
{
  int e=0;
  
  e|=ttl_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttl_vector(1,1,1,1,"Combinations don't cascade",2,2,0,0);
  e|=ttl_vector(0,0,1,1,"Combines and shift left",2,0,0,0);
  e|=ttl_vector(4,0,1,1,"Keep Uncombinable value or combine others",4,2,0,0);
  e|=ttl_vector(2,0,1,1,"Limit to one move",2,2,0,0);
  return e;
}

int test_tilt_right(){
  int e=0;
  
  e|=ttr_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttr_vector(1,1,1,1,"Combinations don't cascade",0,0,2,2);
  e|=ttr_vector(0,0,1,1,"Combines and shift left",0,0,0,2);
  e|=ttr_vector(4,0,1,1,"Keep Uncombinable value or combine others",0,0,4,2);
  e|=ttr_vector(2,0,1,1,"Limit to one move",0,0,2,2);
  return e;
}

int test_tilt_up(){
  int e=0;
  e|=ttu_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttu_vector(1,1,1,1,"Combinations don't cascade",2,2,0,0);
  e|=ttu_vector(0,0,1,1,"Combines and shift left",2,0,0,0);
  e|=ttu_vector(4,0,1,1,"Keep Uncombinable value or combine others",4,2,0,0);
  e|=ttu_vector(2,0,1,1,"Limit to one move",2,2,0,0);
  return e;
}

int test_tilt_down(){
  int e=0;
  
  e|=ttd_vector(1,2,4,8,"Distinct values don't combine",1,2,4,8);
  e|=ttd_vector(1,1,1,1,"Combinations don't cascade",0,0,2,2);
  e|=ttd_vector(0,0,1,1,"Combines and shift left",0,0,0,2);
  e|=ttd_vector(4,0,1,1,"Keep Uncombinable value or combine others",0,0,4,2);
  e|=ttd_vector(2,0,1,1,"Limit to one move",0,0,2,2);
  return e;
}

int board3_vector_test(int i1,int i2,int i3,int i4,	
						int i5,int i6,int i7,int i8,
						int i9,int i10,int i11,int i12,
						int i13,int i14,int i15,int i16,
						char *msg,
                       int o1,int o2,int o3,int o4,
					   int o5,int o6,int o7,int o8,
					   int o9,int o10,int o11,int o12,
					   int o13,int o14,int o15,int o16,
                       int (*func)(int,int **))
{
  int **board=alloca(4*sizeof(int*));
  board[0]=alloca(sizeof(int)*4);
  board[1]=alloca(sizeof(int)*4);
  board[2]=alloca(sizeof(int)*4);
  board[3]=alloca(sizeof(int)*4);
  
  board[0][0]=i1; board[1][0]=i2; board[2][0]=i3, board[3][0]=i4;
  board[0][1]=i5; board[1][1]=i6; board[2][1]=i7, board[3][1]=i8;
  board[0][2]=i9; board[1][2]=i10; board[2][2]=i11, board[3][2]=i12;
  board[0][3]=i13; board[1][3]=i14; board[2][3]=i15, board[3][3]=i16;

  if (msg) printf("%s - ",msg); 
  else {
    printf("Board operation on \n");
    board_display(4, board);
    printf(	"yields\n");
	board_display(4,board);
  }
  fflush(stdout);
  func(4,board);
  if (
      (board[0][0]!=o1)||(board[1][0]!=o2)||(board[2][0]!=o3)|| (board[3][0]!=o4)||
	  (board[0][1]!=o5)||(board[1][1]!=o6)||(board[2][1]!=o7)||(board[3][1]!=o8)||
	  (board[0][2]!=o9)||(board[1][2]!=o10)||(board[2][2]!=o11)||(board[3][2]!=o12)||
	  (board[0][3]!=o13)||(board[1][2]!=o14)||(board[2][3]!=o15)||(board[3][3]!=o16)
      )
    {
     printf("FAILED: {{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d}} became {{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d}} instead of"
             " {{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d},{%d,%d,%d,%d}}\n",
             i1,i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,
             board[0][0],board[1][0],board[2][0],board[3][0],
             board[0][1],board[1][1],board[2][1],board[3][1],
             board[0][2],board[1][2],board[2][2],board[3][2],
             board[0][3],board[1][3],board[2][3],board[3][3],
             o1,o2,o3,o4,o5,o6,o7,o8,o9,o10,o11,o12,o13,o14,o15,o16);
      return -1;
    } 
  printf("PASSED.\n");
  return 0;
}

int test_board_left(){
  int e=0;
  

  e|=board3_vector_test(
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		"Tilt empty board left",
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		tilt_board_left);
  e|=board3_vector_test(
		0,0,0,1,
		0,0,0,1,
		0,0,0,1,
		0,0,0,1,
		"Tilt left column 1s board left",
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		tilt_board_left);
  e|=board3_vector_test(
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		"Tilt right column 1s board left",
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		1,0,0,0,
		tilt_board_left);
  e|=board3_vector_test(
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		1,1,1,1,
		"Tilt 1s board left and merge",
		2,2,0,0,
		2,2,0,0,
		2,2,0,0,
		2,2,0,0,
		tilt_board_left);
	e|=board3_vector_test(
		1,1,1,1,
		0,0,0,0,
		1,1,1,1,
		0,0,0,0,
		"Tilt 1s board left and merge, keep empty rows",
		2,2,0,0,
		0,0,0,0,
		2,2,0,0,
		0,0,0,0,
		tilt_board_left);

  return e;
}

int main(int argc,char **argv)
{
  int e=0;
  printf("\nTesting slide single left\n\n");
  e|=test_slide_single_left();
  printf("\nTesting slide left\n\n");
  e|=test_slide_left();
  printf("\nTesting tilt left\n\n");
  e|=test_tilt_left();
  printf("\nTesting tilt right\n\n");
  e|=test_tilt_right();
  printf("\nTesting tilt up\n\n");
  e|=test_tilt_up();
  printf("\nTesting tilt down\n\n");
  e|=test_tilt_down();
  printf("\nTesting tilt board left\n\n");
  e|=test_board_left();
  return e;
}
