#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int table[7][7];
int x,y,targetX,targetY;

// Clear screen and display board
void Display(int table[7][7]) {
  system("clear"); // Efface le contenu du terminal
  printf("\n  0   2   4   6\n");
  for (int i=0; i < 7; i++) {
    !(i%2) ? printf("%d ",i) : printf("  "); // display column indicators
    for (int j=0; j < 7; j++) {
      switch (table[i][j]) {
      case (0): printf("◯ ");break;
      case (1): printf("⬤ ");break;
      default: printf("  ");break;
      }
    }
    printf("\n");
  }
  printf("\n");
}

// Start game and initialize data
void StartGame() {
  printf("Welcome to my Peg Solitaire!\n");
  
  for (int i=0; i < 7; i++) {
    for (int j=0; j < 7; j++) {
      if ((i == 0 || i == 6) && (j < 2 || j > 4) || (i == 1 || i == 5) && (j == 0 || j == 6)) {
	      table[i][j] = -1;
      } else {
	      table[i][j] = 1;
      }
    }
  }
  
  Display(table);
  printf("Choose the first marble to remove: \n");
  scanf("%d%d",&x, &y);
  while (table[x][y] != 1) {
    printf("Invalild position");
    scanf("%d%d",&x, &y);
  }
  table[x][y] = 0;
  Display(table);
  
  GameLoop();
  GameEnd();
}

// Main game loop
void GameLoop() {
  while (x != -1 && y != -1 && MovePossible()) {
    printf("Please enter move :\n");
    scanf("%d %d", &x, &y);
    if (table[x][y] != 1){
      printf("Invalid position\n");
    }
    else {
      scanf("%d %d", &targetX, &targetY);
      if (x==-1 && y == -1) {
        break;
      }
      if ((table[targetX][targetY] == 0 && table [x][y] == 1) &&                  
	  ( x == targetX && abs(y-targetY) == 2 && table[x][(targetY+y)/2] == 1 ||  
	    y == targetY && abs(x-targetX) == 2 && table[(targetX+x)/2][y] == 1)) { 
        table[x][y] = 0;
        table[targetX][targetY] = 1;
        table[(x + targetX)/2][(y+targetY)/2] = 0;
	
        Display(table);
	
      } else {
        printf("Invalid move\n");
      }
    }
  }
}

// Score display
void GameEnd() {
  printf("Game Over, Score : %d out of 37\n",37-Count());
}

// Marble count
int Count() {
  int res = 0;
  for (int i = 0; i<7; i++) {
    for (int j = 0; j < 7; j++) {
      if (table[i][j] == 1) {
	res += 1;
      }
    }
  }
  return res;
}

//   Check move validity
int MovePossible() {
  for (int i = 2; i < 5; i++) {
    for (int j = 2; j < 5; j++) {
      if (table[i][j]) {
	if (!table[i-2][j] && table[i-1][j] ||
	    !table[i][j-2] && table[i][j-1] ||
	    !table[i][j+2] && table[i][j+1] ||
	    !table[i+2][j] && table[i+1][j]) {
	  return 1;
	}
      }
    }
  }

  for (int i = 0; i<2; i++) {
    for (int j = 2; j < 5; j++) {
      if (table[i][j]) {
	if (!table[i][j-2] && table[i][j-1] ||
	    !table[i][j+2] && table[i][j+1] ||
	    !table[i+2][j] && table[i+1][j]) {
	  return 1;
	}
      }
      if (table[6-i][j]) {
	if (!table[6-i-2][j] && table[6-i-1][j] ||
	    !table[6-i][j-2] && table[6-i][j-1] ||
	    !table[6-i][j+2] && table[6-i][j+1]) {
	  return 1;
	}
      }
    }
  }
  
  for (int j = 0; j<2; j++) {
    for (int i = 2; i < 5; i++) {
      if (table[i][j]) {
	if (!table[i-2][j] && table[i-1][j] ||
	    !table[i+2][j] && table[i+1][j] ||
	    !table[i][j+2] && table[i][j+1]) {
	  return 1;
	}
      }
      if (table[i][6-j]) {
	if (!table[i][6-j-2] && table[i][6-j-1] ||
	    !table[i-2][6-j] && table[i-1][6-j] ||
	    !table[i+2][6-j] && table[i+1][6-j]) {
	  return 1;
	}
      }
    }
  }

  if (table[1][1]) {
    if(table[1][2] && !table[1][3] ||
       table[2][1] && !table[3][1]) {
      return 1;
    }
  }

  if (table[1][5]) {
    if(table[1][4] && !table[1][3] ||
       table[2][5] && !table[3][5]) {
      return 1;
    }
  }

  if (table[5][1]) {
    if(table[5][2] && !table[5][3] ||
       table[4][1] && !table[3][1]) {
      return 1;
    }
  }
  
  if (table[5][5]) {
    if(table[5][4] && !table[5][3] ||
       table[4][5] && !table[3][5]) {
      return 1;
    }
  }
  printf("\n");
  return 0;
}

int main() {
  StartGame();
  
  return 0;
}
