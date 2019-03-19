//******************************************************************************
// File:        bs_client.cc
// Author:      Wesley Ryder
// Description:
//******************************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;


void ship_clean(vector<vector<int> > &board, int x, int y)
{
	for (int i=0;i<4;i++) {
		for (int j=0;j<4;j++) {
			if( board[i][j] == 1){
				board[i][j] = 0;
			}
		}
	}
	board[y][x] = 1;
}

bool check_move(int x, int y,int rotation) {
	switch(rotation) {
		case 0:
			if((x + 2) >= 4 || (y -2) < 0){return false;}
			else{return true;}
		case 1:
			if((x + 2) >= 4){return false;}
			else{return true;}
			break;
		case 2:
			if((x + 2) >= 4 || (y + 2) >= 4){return false;}
			else{return true;}
			break;
		case 3:
			if((y + 2) >= 4){return false;}
			else{return true;}
			break;
		case 4:
			if((x -2) < 0 || (y + 2) >= 4){return false;}
			else{return true;}
			break;
		case 5:
			if((x - 2) < 0){return false;}
			else{return true;}
			break;
		case 6:
			if((x - 2) < 0 || (y - 2) < 0){return false;}
			else{return true;}
			break;
		case 7:
			if((y - 2) < 0){return false;}
			else{return true;}
			break;
		case 8:
			if((x+2) >= 4 || (y - 2) < 0){return false;}
			else{return true;}
			break;
	}
}

// Draw the maxtrix
void draw_matrix(vector<vector<int> > &board,
		     int cur_row,
		     int cur_col,
			 	 int y_start ) {

		for (int j=0;j<4;j++) {
    	move(y_start, 2*j);
     	printw("+-");
   }
   move(y_start, 2*4);
   printw("+");
 	for (int i=0;i<4;i++) {
   	for (int j=0;j<4;j++) {
    	move(2*i+1+y_start, 2*j);
     	printw("|");
     	move(2*i+1+y_start, 2*j+1);
     	if (board[i][j] == 0) {
				printw(" ");
     	} else {
				printw("X");
     }
   	}
   	move(2*i+1+y_start, 2*4);
   	printw("|");

   	for (int j=0;j<4;j++) {
     	move(2*i+2 + y_start, 2*j);
     	printw("+-");
   	}
   	move(2*i+2+y_start, 2*4);
   	printw("+");
 	}
 	move(2*cur_row+1+y_start, 2*cur_col+1);

}

main() {
  int rows;
  int cols;
  int cur_row=0;
  int cur_col=0;
  int ch;
	int ch2;
	int rotation = 0;
	bool turn = true;
	bool ship_placement = false;
	int x = 0;
	int y = 0;
	bool valid_placement = true;

  vector<vector<int> > board;
	vector<vector<int> > enemy_board;
  for (int i=0;i<4;i++) {
    vector<int> t;
    for (int j=0;j<4;j++) {
      t.push_back(0);
    }
    board.push_back(t);
		enemy_board.push_back(t);
  }

  // Screen initialization
  initscr();

  // Clear the screen
  clear();

  // Get the size of the window!
  getmaxyx(stdscr,rows,cols);


  cbreak();  // Pass all characters to this program!

  keypad(stdscr, TRUE); // Grab the special keys, arrow keys, etc.

  // Paint the row and column markers.
  // paint_markers(rows,cols,10,0,0);
  // Redraw the screen.
  refresh();

	// Drawing initial boards
	draw_matrix(enemy_board, 0, 0, 12);
  draw_matrix(board,0, 0, 0);

  // I/O Loop
  // Stop when the q Key is hit.

  while ((ch = getch())!='q') {
		draw_matrix(enemy_board, 0 ,0, 12);
    switch (ch) {
    case ' ':
			turn = true;
			board[cur_row][cur_col]= 1;
			x = cur_col;
			y = cur_row;
      draw_matrix(board,cur_row,cur_col, 0);
			refresh();
			while ((ch2 = getch()) != 'r' && turn == true && ship_placement == false) {
				switch(ch2) {
					case KEY_LEFT:
						//rotation--;
						if (rotation == 1) {
							valid_placement = check_move(x, y, rotation);
							if (valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col +1] = 1;
								board[cur_row-2][cur_col +2] = 1;
							}
							rotation = 8;
							//else{rotation--;}
						}
						if (rotation == 2) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col] = 1;
								board[cur_row-2][cur_col] = 1;
							}
							rotation = 1;
							//else{rotation--;}
						}
						if (rotation == 3) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col+1] = 1;
								board[cur_row+2][cur_col+2] = 1;
							}
							rotation = 2;
							//else{rotation--;}
						}
						if (rotation == 4) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col] = 1;
								board[cur_row+2][cur_col] = 1;
							}
							rotation = 3;
							//else{rotation--;}
						}
						if (rotation == 5) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col-1] = 1;
								board[cur_row+2][cur_col-2] = 1;
							}
							rotation = 4;
							//else{rotation--;}
						}
						if (rotation == 6) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row][cur_col-1] = 1;
								board[cur_row][cur_col-2] = 1;
							}
							rotation = 5;
							//else{rotation--;}
						}
						if (rotation == 7) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col-1] = 1;
								board[cur_row-2][cur_col-2] = 1;
							}
							rotation = 6;
							//else{rotation--;}
						}
						if (rotation == 8) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col] = 1;
								board[cur_row-2][cur_col] = 1;
							}
							rotation = 7;
							//else{rotation = 1;}
						}
						draw_matrix(board,cur_row,cur_col, 0);
						refresh();
						break;

					case KEY_RIGHT:
						rotation++;
						if (rotation == 1) {
							valid_placement = check_move(x, y, rotation);
							if (valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row][cur_col +1] = 1;
								board[cur_row][cur_col +2] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 2) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col+1] = 1;
								board[cur_row+2][cur_col+2] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 3) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col] = 1;
								board[cur_row+2][cur_col] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 4) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row+1][cur_col-1] = 1;
								board[cur_row+2][cur_col-2] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 5) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row][cur_col-1] = 1;
								board[cur_row][cur_col-2] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 6) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col-1] = 1;
								board[cur_row-2][cur_col-2] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 7) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col] = 1;
								board[cur_row-2][cur_col] = 1;
							}
							else{rotation++;}
						}
						if (rotation == 8) {
							valid_placement = check_move(x, y, rotation);
							if(valid_placement == true){
								ship_clean(board, x, y);
								board[cur_row-1][cur_col+1] = 1;
								board[cur_row-2][cur_col+2] = 1;
							}
							else{rotation = 0;}
						}
						draw_matrix(board,cur_row,cur_col, 0);
						refresh();
						break;
					case ' ':
						//turn = false;
						board[cur_row][cur_col]= 1;
						draw_matrix(board,cur_row,cur_col, 0);
						refresh();
						ship_placement = true;
						break;
					case 27:
						turn = false;
						ship_clean(board, x, y);
						refresh();
						board[y][x] = 0;
						draw_matrix(board,cur_row,cur_col, 0);
					}
				}
      // Redraw the screen.
      break;
    case KEY_RIGHT:
      cur_col++;
      cur_col%=4;
      draw_matrix(board,cur_row,cur_col, 0);
      // Redraw the screen.
      refresh();
      break;

    case KEY_LEFT:
      cur_col--;
      cur_col = (4+cur_col)%4;
      draw_matrix(board,cur_row,cur_col, 0);
      // Redraw the screen.
      refresh();
      break;

    case KEY_UP:
      cur_row--;
      cur_row=(4+cur_row) % 4;
      draw_matrix(board,cur_row,cur_col, 0);

      // Paint_markers(rows,cols,10,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    case KEY_DOWN:
      cur_row++;
      cur_row%=4;
      draw_matrix(board,cur_row,cur_col, 0);
      // Paint_markers(rows,cols,10,cur_row,cur_col);
      // Redraw the screen.
      refresh();
      break;
    }
  }
  endwin();
}
