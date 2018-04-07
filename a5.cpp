// a5.cpp

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Kevin Kyungmin Lee>
// St.# : <301271170>
// Email: <kla141@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "cmpt_error.h"
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
// include header files
#include "Board.h"
#include "Human_player.h"
#include "Computer_player.h"
using namespace std;


// Title
void title(){
  cout << "\t\t    ----------------------------------" << endl
       << "\t\t    |             REVERSI            |" << endl
       << "\t\t    ----------------------------------" << endl << endl << endl;
}
// each round
void Turn(Player* P){
  P->make_move();
  P->print_score();
}
// end_game trigger
bool end_game(Board B){
  bool is_end = true;
  for(int row = 1; row < B.height()-1; row++){
    for(int col = 1; col < B.width()-1; col++){
      if(B.get(row, col) == Tile::Space){
        is_end = false;
      }
    }
  }
  return is_end;
}
// Game function
void game(){
  title();
  // Human player
  Player* Human = new Human_player();
  // display initial board
  Human->print_score();
  Turn(Human);
  Board board = Human->get_board();
  // Computer
  Player* Computer = new Computer_player(board);
  // if end_game return true it will quit the loop
  // two conditions : 1. if there is no more space and User's score is higher than
  //                  computer's then user win
  //                : 2. if Computer's score reachs at 0 then user win (vice-versa)
  // Check those conditions every turn and make it break the infinite loop at some point.
  while(true){
    if( end_game(board) ){
      if( (Human->get_score() > Computer->get_score()) || Computer->get_score() == 0 ){
        cout << endl << "Congratulation! You won!" << endl;
      }
      if( (Computer->get_score() > Human->get_score()) || Human->get_score() == 0 ){
        cout << endl << "Sorry! Computer won!" << endl;
      }
      if(Computer->get_score() == Human->get_score()){
        cout << endl << "Tied!" << endl;
      }
      break;
    }
    cout << "Computer's turn : " << endl;
    Turn(Computer);
    board = Computer->get_board();
    Human->set_board(board);
    if( end_game(board) ){
      if( (Human->get_score() > Computer->get_score()) || Computer->get_score() == 0 ){
        cout << endl << "Congratulation! You won!" << endl;
      }
      if( (Computer->get_score() > Human->get_score()) || Human->get_score() == 0 ){
        cout << endl << "Sorry! Computer won!" << endl;
      }
      if(Computer->get_score() == Human->get_score()){
        cout << endl << "Tied!" << endl;
      }
      break;
    }
    cout << "Your turn : ";
    Turn(Human);
    board = Human->get_board();
    Computer->set_board(board);
  }
  // deallocate memory
  delete Human;
  delete Computer;
}
// ask Play again  at the end
// 1 == true : Play again
// 0 == false : quit
bool is_play_again(){
  bool play_again;
  string replay;
  cout << endl << "Would you like to play again?" << endl;
  cout << "Enter 1 to play again or 0 to quit : ";
  cin >> replay;
  if(replay == "1"){
    play_again = true;
  } else if(replay == "0"){
    play_again = false;
  }
  return play_again;
}
// Main function
int main(){
  srand(time(NULL));
  game();
  while( is_play_again() == true ){           // end game loop
    game();
  }
}
