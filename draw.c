#include "include/stdio.h"
#include "include/stdlib.h"
#include "include/windows.h"

void move_to(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void draw_border() {
  move_to(0, 0);
  printf("--------------------");

  move_to(0, 10);
  printf("--------------------");
}

void clear_screen() { system("cls"); }

void draw_game_over() {
  clear_screen();
  draw_border();

  move_to(2, 5);
  printf("GAME OVER");

  system("pause>nul");
  clear_screen();
  exit(0);
}