#include <stdio.h>
#include "2048.h"
 
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
  return e;
}
