#include <stdio.h>
#include <stdlib.h>
#include "ml6.h"
#include "display.h"

void plot( screen s, color c, int x, int y) {
  y = YRES - 1 - y;
  if ( x >= 0 && x < XRES && y >=0 && y < YRES ) s[x][y] = c;
}

void clear_screen( screen s ) {
  int x, y;
  color c;
  c.red = 0;
  c.green = 0;
  c.blue = 0;
  for ( y=0; y < YRES; y++ ) for ( x=0; x < XRES; x++) s[x][y] = c;
}

void save_ppm( screen s, char *file) {
  int x, y;
  FILE *f;
  f = fopen(file, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  fclose(f);
}

void save_extension( screen s, char *file) {
  int x, y;
  FILE *f;
  char line[256];
  sprintf(line, "convert - %s", file);
  f = popen(line, "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
}

void display( screen s) {
  int x, y;
  FILE *f;
  f = popen("display", "w");
  fprintf(f, "P3\n%d %d\n%d\n", XRES, YRES, MAX_COLOR);
  for ( y=0; y < YRES; y++ ) {
    for ( x=0; x < XRES; x++)
      fprintf(f, "%d %d %d ", s[x][y].red, s[x][y].green, s[x][y].blue);
    fprintf(f, "\n");
  }
  pclose(f);
}
