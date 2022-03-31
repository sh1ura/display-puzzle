#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define DEBUG 0
#define FIND_ALL_SOLUTIONS 0
#define SHOW_FIELD 1

#define PN 16 // number of pieces, 16 = 64 / 4

// definition of pieces
char *pieceDef[]= {
  "AaBbbKKK",
  "aABCCklL",
  "DeccfMLl",
  "DEeGfMmm",
  "DEGgfoNn",
  "dhIGFOOn",
  "HhIJjoPn",
  "HiIJjPpp"
};

// images to be shown
char *disp[][8] = {
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    "   *    ",
    "  **    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "  ***   ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    "     *  ",
    "    *   ",
    "   *    ",
    "  *     ",
    " *****  ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    "     *  ",
    "   **   ",
    "     *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    "    *   ",
    "   **   ",
    "  * *   ",
    " *  *   ",
    " *****  ",
    "    *   ",
    "    *   ",
  },
  {
    "        ",
    " *****  ",
    " *      ",
    " *      ",
    " ****   ",
    "     *  ",
    "     *  ",
    " ****   ",
  },
  {
    "        ",
    "  ***   ",
    " *      ",
    " *      ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    " *****  ",
    "     *  ",
    "     *  ",
    "    *   ",
    "   *    ",
    "  *     ",
    " *      ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    "  ****  ",
    "     *  ",
    "     *  ",
    "  ***   ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    " *****  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
  },
  {
    "        ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
  },
  {
    "        ",
    "  ***   ",
    " *      ",
    " *      ",
    " *      ",
    " *      ",
    " *      ",
    "  ***   ",
  },
  {
    "        ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " ****   ",
  },
  {
    "        ",
    " *****  ",
    " *      ",
    " *      ",
    " *****  ",
    " *      ",
    " *      ",
    " *****  ",
  },
  {
    "        ",
    " *****  ",
    " *      ",
    " *      ",
    " *****  ",
    " *      ",
    " *      ",
    " *      ",
  },
  {
    "        ",
    "  ***   ",
    " *      ",
    " *      ",
    " *  **  ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    " *   *  ", 
    " *   *  ",
    " *   *  ",
    " *****  ",
    " *   *  ", 
    " *   *  ",
    " *   *  ",
  },
  {
    "        ",
    "  ***   ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "  ***   ",
  },
  {
    "        ",
    "   ***  ",
    "    *   ",
    "    *   ",
    "    *   ",
    "    *   ",
    " *  *   ",
    "  **    ",
  },
  {
    "        ",
    " *   *  ", 
    " *  *   ",
    " * *    ",
    " **     ",
    " * *    ", 
    " *  *   ",
    " *   *  ",
  },
  {
    "        ",
    " *      ", 
    " *      ", 
    " *      ", 
    " *      ", 
    " *      ", 
    " *      ", 
    " *****  ",
  },
  {
    "        ",
    " *   *  ", 
    " ** **  ", 
    " * * *  ", 
    " *   *  ", 
    " *   *  ", 
    " *   *  ", 
    " *   *  ", 
  },
  {
    "        ",
    " *   *  ", 
    " *   *  ", 
    " **  *  ", 
    " * * *  ", 
    " *  **  ", 
    " *   *  ", 
    " *   *  ", 
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
    " *      ",
    " *      ",
    " *      ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *  *   ",
    "  ** *  ",
  },
  {
    "        ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
    " * *    ",
    " *  *   ",
    " *   *  ",
  },
  {
    "        ",
    "  ***   ",
    " *      ",
    " *      ",
    "  ***   ",
    "     *  ",
    "     *  ",
    "  ***   ",
  },
  {
    "        ",
    " *****  ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
  },
  {
    "        ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  * *   ",
    "   *    ",
  },
  {
    "        ",
    " *   *  ", 
    " *   *  ", 
    " *   *  ", 
    " *   *  ",  
    " * * *  ", 
    " ** **  ", 
    " *   *  ",  
  },
  {
    "        ",
    " *   *  ",
    " *   *  ",
    "  * *   ",
    "   *    ",
    "  * *   ",
    " *   *  ",
    " *   *  ",
  },
  {
    "        ",
    " *   *  ",
    " *   *  ",
    "  * *   ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
  },
  {
    "        ",
    " *****  ",
    "     *  ",
    "    *   ",
    "   *    ",
    "  *     ",
    " *      ",
    " *****  ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  ***   ",
    "     *  ",
    "  ****  ",
    " *   *  ",
    "  ****  ",
  },
  {
    "        ",
    "        ",
    " *      ",
    " *      ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  ***   ",
    " *      ",
    " *      ",
    " *      ",
    "  ***   ",
  },
  {
    "        ",
    "        ",
    "     *  ",
    "     *  ",
    "  ****  ",
    " *   *  ",
    " *   *  ",
    "  ****  ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  ***   ",
    " *   *  ",
    " *****  ",
    " *      ",
    "  ***   ",
  },
  {
    "        ",
    "    **  ",
    "   *    ",
    "   *    ",
    " *****  ",
    "   *    ",
    "   *    ",
    "   *    ",
  },
  {
    "        ",
    "        ",
    "  ****  ",
    " *   *  ",
    " *   *  ",
    "  ****  ",
    "     *  ",
    "  ***   ",
  },
  {
    "        ",
    " *      ",
    " *      ",
    " *      ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
  },
  {
    "        ",
    "        ",
    "   *    ",
    "        ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
  },
  {
    "        ",
    "        ",
    "   *    ",
    "        ",
    "   *    ",
    "   *    ",
    "   *    ",
    " **     ",
  },
  {
    "        ",
    "  *     ",
    "  *     ",
    "  *  *  ",
    "  * *   ",
    "  **    ",
    "  * *   ",
    "  *  *  ",
  },
  {
    "        ",
    "  **    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "  ***   ",
  },
  {
    "        ",
     "        ",
    "        ",
    " ** *   ",
    " * * *  ",
    " * * *  ",
    " * * *  ",
    " * * *  ",
  },
  {
    "        ",
    "        ",
    "        ",
    " * **   ",
    " **  *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  ***   ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  ***   ",
  },
  {
    "        ",
    "        ",
    " ****   ",
    " *   *  ",
    " *   *  ",
    " ****   ",
    " *      ",
    " *      ",
  },
  {
    "        ",
    "        ",
    "  ****  ",
    " *   *  ",
    " *   *  ",
    "  ****  ",
    "     *  ",
    "     *  ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  * *   ",
    "  **    ",
    "  *     ",
    "  *     ",
    "  *     ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  ***   ",
    " *      ",
    "  ***   ",
    "     *  ",
    "  ***   ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  *     ",
    " ****   ",
    "  *     ",
    "  *     ",
    "   **   ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  ****  ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *   *  ",
    " *   *  ",
    " *   *  ",
    "  * *   ",
    "   *    ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *   *  ",
    " *   *  ",
    " * * *  ",
    " * * *  ",
    "  * *   ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *   *  ",
    "  * *   ",
    "   *    ", 
    "  * *   ",
    " *   *  ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *   *  ",
    " *   *  ",
    "  ****  ", 
    "     *  ",
    "  ***   ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *****  ",
    "    *   ",
    "   *    ", 
    "  *     ",
    " *****  ",
  },
  {
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "        ",
    "   *    ",
  },
  {
    "        ",
    "  * *   ",
    "  * *   ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "  * *   ",
    "  * *   ",
    " *****  ",
    "  * *   ",
    " *****  ",
    "  * *   ",
    "  * *   ",
  },
  {
    "        ",
    "   *    ",
    "  ***   ",
    " * *    ",
    "  ***   ",
    "   * *  ",
    "  ***   ",
    "   *    ",
  },
  {
    "        ",
    " **     ",
    " **  *  ",
    "    *   ",
    "   *    ",
    "  *     ",
    " *  **  ",
    "    **  ",
  },
  {
    "        ",
    "        ",
    "  *     ",
    " * *    ",
    "  *     ",
    " * * *  ",
    " *  *   ",
    "  ** *  ",
  },
  {
    "        ",
    "   *    ",
    "   *    ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "    *   ",
    "   *    ",
    "  *     ",
    "  *     ",
    "  *     ",
    "   *    ",
    "    *   ",
  },
  {
    "        ",
    "  *     ",
    "   *    ",
    "    *   ",
    "    *   ",
    "    *   ",
    "   *    ",
    "  *     ",
  },
  {
    "        ",
    "        ",
    "   *    ",
    " * * *  ",
    "  ***   ",
    " * * *  ",
    "   *    ",
    "        ",
  },
  {
    "        ",
    "        ",
    "   *    ",
    "   *    ",
    " *****  ",
    "   *    ",
    "   *    ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "   *    ",
    "  *     ",
  },
  {
    "        ",
    "        ",
    "        ",
    "        ",
    " *****  ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "   *    ",
  },
  {
    "        ",
    "        ",
    "     *  ",
    "    *   ",
    "   *    ",
    "  *     ",
    " *      ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    "   *    ",
    "        ",
    "   *    ",
    "        ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    "   *    ",
    "        ",
    "   *    ",
    "  *     ",
    "        ",
  },
  {
    "        ",
    "        ",
    "    *   ",
    "   *    ",
    "  *     ",
    "   *    ",
    "    *   ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    " *****  ",
    "        ",
    " *****  ",
    "        ",
    "        ",
  },
  {
    "        ",
    "        ",
    "  *     ",
    "   *    ",
    "    *   ",
    "   *    ",
    "  *     ",
    "        ",
  },
  {
    "        ",
    "  ***   ",
    " *   *  ",
    "    *   ",
    "   *    ",
    "   *    ",
    "        ",
    "   *    ",
  },
  {
    "        ",
    "        ",
    "  ***   ",
    "     *  ",
    " *** *  ",
    " * * *  ",
    " * * *  ",
    "  ***   ",
  },
  {
    "        ",
    "  ***   ",
    "  *     ",
    "  *     ",
    "  *     ",
    "  *     ",
    "  *     ",
    "  ***   ",
  },
  {
    "        ",
    "        ",
    " *      ",
    "  *     ",
    "   *    ",
    "    *   ",
    "     *  ",
    "        ",
  },
  {
    "        ",
    "  ***   ",
    "    *   ",
    "    *   ",
    "    *   ",
    "    *   ",
    "    *   ",
    "  ***   ",
  },
  {
    "        ",
    "   *    ",
    "  * *   ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
    " *****  ",
  },
  {
    "        ",
    "   *    ",
    "    *   ",
    "        ",
    "        ",
    "        ",
    "        ",
    "        ",
  },
  {
    "        ",
    "    *   ",
    "   *    ",
    "   *    ",
    "  *     ",
    "   *    ",
    "   *    ",
    "    *   ",
  },
  {
    "        ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
    "   *    ",
  },
  {
    "        ",
    "  *     ",
    "   *    ",
    "   *    ",
    "    *   ",
    "   *    ",
    "   *    ",
    "  *     ",
  },
  {
    "        ",
    "        ",
    "        ",
    "  *     ",
    " * * *  ",
    "    *   ",
    "        ",
    "        ",
  },
};  

#include  "puzzlelib.c"

typedef struct { // data structure for recursive search
  Field f; // current pattern of the field
  int used[PN]; // table of used pieces
} Sdata;

Sdata sd = {
  {{{0}}},
  {0}
};

// recursive search of placing pieces
int placeCheck(Sdata *sd, int pn, char *pattern[]) {
  int x, y, i, pose, result = 0;

#if DEBUG // show process
  for(i = 0; i < PN; i++) {
    printf(" %d", sd->used[i]);
  }
  printf("\n");
  showField(sd->f);
#endif
  
  if(pn == PN) { // solution is found
#if SHOW_FIELD
    showFieldBin(sd->f);
    showField(sd->f);
#if FIND_ALL_SOLUTIONS
    printf("\n");
#endif
#endif
    return 1;
  }
  // find top-left empty cell
  for(y = 0; y < F_SIZE; y++) {
    for(x = 0; x < F_SIZE; x++) {
      if(sd->f.p[y][x] == 0) {
	goto OUT;
      }
    }
  }
 OUT:
  for(i = 0; i < PN; i++) {
    if(sd->used[i]) { // select unsed piece
      continue;
    }
    for(pose = 0; pose < poseNum[i]; pose++) {
      for(int py = 0; py < piece[i][pose].y; py++) {
	for(int px = 0; px < piece[i][pose].x; px++) {
	  int posx = x - px;
	  int posy = y - py;
	  if(posx < 0 || posy < 0 ||
	     posx + piece[i][pose].x > F_SIZE ||
	     posy + piece[i][pose].y > F_SIZE) {
	    continue; // piece is not in the field
	  }
	  if(piece[i][pose].p[py][px] <= 0) {
	    continue; // the piece must fill (y, x)
	  }
	  if(isPlaceable(&(sd->f), &piece[i][pose], posx, posy)) {
	    int okFlag = 1;
	    for(int y = 0; y < piece[i][pose].y; y++) {
	      for(int x = 0; x < piece[i][pose].x; x++) {
		if(piece[i][pose].p[y][x] == 0) {
		  continue;
		}
		if((piece[i][pose].p[y][x] > 26 && pattern[y+posy][x+posx] == '*') ||
		   (piece[i][pose].p[y][x] <= 26 && pattern[y+posy][x+posx] == ' ')) {
		  okFlag = 0;
		  break;
		}
	      }
	    }
	    if(!okFlag) {
	      continue;
	    }
	    
	    Sdata nsd = *sd;
	    nsd.used[i] = 1;
	    doPlace(&(nsd.f), &piece[i][pose], posx, posy);
	    result += placeCheck(&nsd, pn + 1, pattern);
#if !FIND_ALL_SOLUTIONS
	    if(result) {
	      return 1;
	    }
#endif
	  }
	}
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  int pn, i, nosolCount = 0;

  initPuzzle();
  genPose(pieceDef); // generate mirrored and rotated patterns of pieces
  
  for(int c = 0; c < sizeof(disp) / sizeof(char [8][8]); c++) {
    i = placeCheck(&sd, 0, disp[c]); // search
    if(i == 0) {
      printf("============= NO SOLUTION ============\n");
      nosolCount++;
    }
#if FIND_ALL_SOLUTIONS
    printf("Solution = %d\n", i);
#endif
  }
  printf("No Solution = %d\n", nosolCount);
  return 0;
}
