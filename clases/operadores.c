#include <stdio.h>
int main(){
  int x;
  float v;

  x=4.5+3;
  v=4.5+3;
  printf(" %d, %.2f\n", x, v);


  x=4.5-3;
  v=4.5-3;
  printf(" %d, %.2f\n", x, v);


  x=4.5*3;
  v=4.5*3;
  printf(" %d, %.2f\n", x, v);


  x=4.5/3;
  printf(" %d\n", x);

  x=4/3;
  printf(" %d\n", x);

  x=4.0/3.0;
  printf(" %d\n", x);

  v=4/3;
  printf("%.2f\n", v);

  v=4.0/3.0;
  printf("%.2f\n", v);

  v=(float)4/3;
  printf("%.2f\n", v);

  v=((float)5+3)/6;
  printf("%.2f\n", v);


  x=15%2;
  v=(15%2)/2;
  printf(" %d, %.2f\n", x, v);

  v=((float)(15%2))/2;
  printf("%.2f\n", v);


  int a,b;

  a=6;
  b=4;
  a+=3;
  printf("a=%d\n", a);
  a+=b;
  printf("a=%d\n", a);

  a=6;
  b=2;
  a-=1;
  printf("a=%d\n", a);
  a-=b;
  printf("a=%d\n", a);

  a=5;
  b=3;
  a*=2;
  printf("a=%d\n", a);
  a*=b;
  printf("a=%d\n", a);

  a=30;
  b=2;
  a/=3;
  printf("a=%d\n", a);
  a/=b;
  printf("a=%d\n", a);

  a=20;
  b=3;
  a%=12;
  printf("a=%d\n", a);
  a%=b;
  printf("a=%d\n", a);

  a=7;
  printf("a=%d\n", a);
  b=a++;
  printf("a=%d,b=%d\n", a, b);

  a=7;
  printf("a=%d\n", a);
  b=++a;
  printf("a=%d,b=%d\n", a, b);
  
  a=7;
  printf("a=%d\n", a);
  b=a--;
  printf("a=%d,b=%d\n", a, b);

  a=7;
  printf("a=%d\n", a);
  b=--a;
  printf("a=%d,b=%d\n", a, b);



  int res;

  res='h'=='p';
  printf("res=%d\n", res);

  res='h'=='H';
  printf("res=%d\n", res);

  res='h'=='h';
  printf("res=%d\n", res);


  res='h'!='p';
  printf("res=%d\n", res);

  res=7<15;
  printf("res=%d\n", res);

  res=22>11;
  printf("res=%d\n", res);

  res=15<=2;
  printf("res=%d\n", res);

  res=30>=100;
  printf("res=%d\n", res);



  int  y ;

  x=(!(7>15));
  y=(!0);
  printf("x=%d,y=%d\n", x, y);

  x=(35>20)&&(20<=23);
  y=0&&1;
  printf("x=%d,y=%d\n", x, y);

  x=(35>20)||(20<=18);
  y=0||1;
  printf("x=%d,y=%d\n", x, y);

  return 0;
}