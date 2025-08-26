#include <stdio.h>
#include <unistd.h>

#define GRID_COLS 20 // dove sarà scritto GRID_COLS sostituirà con 25
#define GRID_ROWS 20
#define GRID_CELLS (GRID_COLS*GRID_ROWS)
#define ALIVE '*' // stessa cosa
#define DEAD '.'

// traduce il putno della griglia alle x, y specificate nell'indice dell'array lineare. 
// Questa funzione implementa il wrapping, quindi sia le coordinate negative e positive fuori dalla griglia 
// will wrap around (effetto pacman)
int cell_to_index(int x, int y) {
   if (x < 0) {
      x = (-x) % GRID_COLS; //gestione del numero negativo
      x = GRID_COLS - x; // 
   }
   if (y < 0) {
      y = (-y) % GRID_ROWS;
      y = GRID_ROWS - y;
   }   
   if (x >= GRID_COLS) x = x % GRID_COLS; // ti pigli il resto ed effetto pacman
   if (y >= GRID_ROWS) y = y % GRID_ROWS;
   return y*GRID_COLS+x;
}

// la funzione imposta la cella impostata a x e y allo stato specificato
void set_cell(char *grid, int x, int y, int state) {
   grid[y*GRID_COLS+x] = state;
}

// la funzione restituisce lo stato della grilla a x e y
char get_cell(char *grid, int x, int y) {
   return grid[cell_to_index(x,y)];
}

// mostra la griglia sullo schermo
void print_grid(char *grid) {
   printf("\x1b[3J\x1b[H\x1b[2J"); // clear
   for (int y = 0; y < GRID_ROWS; y++) {
      for (int x = 0; x < GRID_COLS; x++) {
         printf("%c", get_cell(grid, x, y));
      }
      printf("\n");
   }
}

// imposta tutte le celle nello stato specificato
void set_grid(char *grid, char state) {
   for (int y = 0; y < GRID_ROWS; y++) {
      for (int x = 0; x < GRID_COLS; x++) {
         set_cell(grid, x, y, state);
      }
   }
}

// restituisce il numero di celle vive vicine a x, y
int count_living_neighbors(char *grid, int x, int y) {
   int alive = 0;
   for (int yo = -1; yo <= 1; yo++) { // y offset
      for (int xo = -1; xo <= 1; xo++) { // x offset
         if (xo == 0 && yo == 0) continue;
         if (get_cell(grid,x+xo ,y+yo) == ALIVE) alive++;
      }
   }
   return alive; 
}

// calcola il nuovo stato del Game of Life secondo le sue regole
void compute_new_state(char *old, char *new) {
    for (int y = 0; y < GRID_ROWS; y++) {
      for (int x = 0; x < GRID_COLS; x++) {
         int n_alive = count_living_neighbors(old, x, y);
         int new_state = DEAD;
         if (get_cell(old,x,y) == ALIVE) {
            if (n_alive == 2 || n_alive == 3) {
               new_state = ALIVE;
            }
         } else {
            if (n_alive == 3) {
               new_state = ALIVE;
            }
         }
         set_cell(new, x, y, new_state);
      }
   }

}


int main(void) {
   char old_grid[GRID_CELLS];
   char new_grid[GRID_CELLS];
   set_grid(old_grid, DEAD);
   set_cell(old_grid, 10, 10, ALIVE);
   set_cell(old_grid, 9, 10, ALIVE);
   set_cell(old_grid, 11, 10, ALIVE);
   set_cell(old_grid, 11, 9, ALIVE);
   set_cell(old_grid, 10, 8, ALIVE);

   /* versione vecchia (ripete la computazione dello stato)
   while(1) {
      compute_new_state(old_grid, new_grid);
      print_grid(new_grid);
      usleep(100000);
      compute_new_state(new_grid, old_grid);
      print_grid(old_grid);
      usleep(100000);
   } */
   char *new = new_grid;
   char *old = old_grid;
   while(1) {
      compute_new_state(old, new);
      print_grid(new);
      usleep(100000);
      char *tmp = old;
      old = new;
      new = tmp;
   }
   return 0;

}
