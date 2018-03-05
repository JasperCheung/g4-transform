#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

void parse_file ( char * filename, struct matrix * transform, struct matrix * edges, screen s) {

  FILE *f;
  char line[256];
  clear_screen(s);
  color c;
  c.red = 30;
  c.green = 45;
  c.blue = 230;

  if ( !strcmp(filename, "stdin") ) f = stdin;
  else f = fopen(filename, "r");

  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';

    double xcord[2];
    double ycord[2];
    double zcord[2];
    struct matrix *temp;
    double angle;
    char axis;

    if ( !strcmp(line, "line") ) {
      fgets(line, sizeof(line), f);
      sscanf(line, "%lf %lf %lf %lf %lf %lf", xcord, ycord, zcord, xcord+1, ycord+1, zcord+1);
      add_edge(edges, xcord[0], ycord[0], zcord[0], xcord[1], ycord[1], zcord[1]);
    }
    else if ( !strcmp(line, "ident") ) {
      ident(transform);
    }
    else if ( !strcmp(line, "scale") ) {
      fgets(line, sizeof(line), f);
      sscanf(line, "%lf %lf %lf", xcord, ycord, zcord);
      temp = make_scale( xcord[0], ycord[0], zcord[0]);
      matrix_mult(temp, transform);
    }
    else if ( !strcmp(line, "move") ) {
      fgets(line, sizeof(line), f);
      sscanf(line, "%lf %lf %lf", xcord, ycord, zcord);
      temp = make_translate( xcord[0], ycord[0], zcord[0]);
      matrix_mult(temp, transform);
    }
    else if ( !strcmp(line, "rotate") ) {
      fgets(line, sizeof(line), f);
      sscanf(line, "%c %lf", &axis, &angle);
      angle = angle * (M_PI / 180);
      if ( axis == 'x' ) {
	temp = make_rotX( angle );
      }
      else if ( axis == 'y' )
	{temp = make_rotY( angle );
	}
      else if ( axis == 'z' ) {
	temp = make_rotZ( angle );
      }
      matrix_mult(temp, transform);

    }
    else if ( !strcmp(line, "apply") ) {
      matrix_mult(transform, edges);
    }
    else if ( !strcmp(line, "display") ) {
      clear_screen(s);
      draw_lines(edges, s, c);
      display( s );
    }
    else if ( !strcmp(line, "save") ) {
      fgets(line, 255, f);
      clear_screen(s);
      draw_lines(edges, s, c);
      save_extension(s, line);
    }
  }
}
