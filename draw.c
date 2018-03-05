#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

void add_point( struct matrix * points, double x, double y, double z) {
  if ( points->lastcol == points->cols ) grow_matrix( points, points->lastcol + 100 );
  points->m[0][ points->lastcol ] = x;
  points->m[1][ points->lastcol ] = y;
  points->m[2][ points->lastcol ] = z;
  points->m[3][ points->lastcol ] = 1;
  points->lastcol++;
}

void add_edge( struct matrix * points, double x0, double y0, double z0, double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

void draw_lines( struct matrix * points, screen s, color c) {
  if ( points->lastcol < 2 ) return; //not enough points
  int point;
  for (point=0; point < points->lastcol-1; point+=2) draw_line( points->m[0][point], points->m[1][point], points->m[0][point+1], points->m[1][point+1], s, c);
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
  if ( x0 > x1 ) return draw_line(x1, y1, x0, y0, s, c); // swap coordinates if necessary
  int x = x0, y = y0, dx = x1 - x, dy = y1 - y, d;
  int A = dy * 2;  // 2A
  int B = -2 * dx; // 2B
  if ( dy > 0 ) { // octants 1 and 2
    if ( dx > dy ) { // octant 1
      d = A + B/2; // 2A + B
      while ( x <= x1 ) {
        plot( s, c, x, y );
        if ( d > 0 ) {
          y++;
          d+=B;
        }
        x++;
        d+=A;
      }
    }// end octant 1
    else { // octant 2
      d = A/2 + B; // A + 2B
      while ( y <= y1 ) {
        plot( s, c, x, y );
        if ( d < 0 ) {
          x++;
          d+=A;
        }
        y++;
        d+=B;
      }
    }// end octant 2
  }// end octants 1 and 2
  else { // octants 7 and 8
    if ( dx + dy < 0 ) { // octant 7
      d = A/2 - B; // A - 2B
      while( y >= y1 ) {
        plot(s, c, x, y);
        if ( d > 0 ) {
          x++;
          d+=A;
        }
        y--;
        d-=B;
      }
    }// end octant 7
    else { // octant 8
      d = A - B/2; // 2A - B
      while ( x <= x1 ) {
        plot(s, c, x, y);
        if ( d < 0 ) {
          y--;
          d-=B;
        }
        x++;
        d+=A;
      }
    }// end octant 8
  }// end octants 7 and 8
} //end draw_line
