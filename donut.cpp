             #include <cmath>
          #include <cstdio>/*.*/
        #include <cstring>/*~~~~*/
     int main(){float A=0,B=0,z[1760];
  char b[1760];printf("\x1b[2J");for(;;){
memset(b,32,1760);      memset(z,0,7040);;
for(float j=0;j<          6.28;j+=.07)for(
float i=0;6.28>            i;i+=.02){float
c=sin(i),d=cos(j          ),e=sin(A),f=sin
(j),g=cos(A),h=d+        2,D=1/(c*h*e+f*g+
5),l=cos(i),m=cos(B    ),n=sin(B),t=c*h*g-
f*e;int x=40+30*D*(l*h*m-t*n),y=12+15*D*(l
 *h*n+t*m),o=x+80*y,N=8*((f*e-c*d*g)*m-c*
   d*e-f*g-l*d*n);if(y>0&&y<22&&x>0&&x<
     80&&D>z[o]){z[o]=D;b[o]=".,-~:;"
       "=!*#$@"[N>0?N:0];}} printf(
         "\x1b[H");for(int k=0;k<
           1761;k++) putchar(k%
             80?b[k]:10);A+=
              .04;B+=.02;}}