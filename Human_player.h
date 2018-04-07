// Human_player.h

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

#include "Player.h"
using namespace std;
// Human_player class that dervied from Player class
class Human_player : public Player {
  int user_score;             // contains user and comp score
  int comp_score;
  Board board;
public:
  Human_player()                                      // constructor
  : user_score(0), comp_score(0), board(10,10)        // initialization list
  {
    board.set_loc(4,4, Tile::Black);                  // initial board game set-up
    board.set_loc(4,5, Tile::White);                  // two black and two white
    board.set_loc(5,4, Tile::White);                  // in the middle of the board
    board.set_loc(5,5, Tile::Black);
    board.println();                                  // print
  }
  // getters that return board and user_score
  Board get_board() const { return board; }
  int get_score() const { return user_score; }
  // accept new board that is created from the opponent's move and copied it to the board
  void set_board( Board B ){
    board = B;
  }
  // it counts how many blacks and whites are in the current board
  void set_score(){
    user_score = 0;
    comp_score = 0;
    for(int i = 1; i < board.height()-1; i++){
      for(int j = 1; j < board.width()-1; j++){
        if(board.get(i, j) == Tile::Black){
          user_score += 1;
        }
        if(board.get(i, j) == Tile::White){
          comp_score += 1;
        }
      }
    }
  }
  // user's typing format should be letter a to h in the first letter
  // and 1 to 8 in the second letter otherwise return true;
  // !false == true
  bool invalid_move(const string& s){
    if(s.length() == 2 && (('a' <= s[0]) && (s[0] <= 'h')) && (('1' <= s[1]) && (s[1] <= '8'))){
      return false;
    }
    else if ( s[0] < 'a' || s[0] > 'h') return true;
    else if ( s[1] < '1' || s[1] > '8') return true;
    else return true;
  }
  // Now check board[r][c] is legal or not
  // 0 means false, 1 means true;
  int is_valid_move(int r, int c){
    int row_delta = 0;                  // delta will help to find the direction of
    int col_delta = 0;                  // valid place
    int x = 0;                          // will count how many opponent's pieces are in
    int y = 0;                          // between user's valid space and user's piece
    int is_valid = 0;                   // if valid return 0;
    for(int i = 0; i < board.height(); i++){
      for(int j = 0; j < board.width(); j++){
        if(board.get(r,c) != Tile::Space)         // if there is Tile Space its ok but if not skip it
          continue;
        // if it is space then search all 8 directions (Norht,North-east, east, ...)
        for(row_delta = -1; row_delta <= 1; row_delta++){
          for(col_delta = -1; col_delta <= 1; col_delta++){
            if(r + row_delta < 0 || r + row_delta >= board.height() - 1
            || c + col_delta < 0 || c + col_delta >= board.width() - 1
            || (row_delta == 0 && col_delta == 0))
              continue;
            // if there is a opponent's piece in that direction
            if(board.get(r + row_delta, c + col_delta) == Tile::White){
              x = r + row_delta;        // save that direction in the x and y
              y = c + col_delta;
              for(;;){                  // keep searching in that direction
                x += row_delta;
                y += col_delta;
                if(x < 0 || x >= board.height() - 1 || y < 0 || y >= board.width() - 1)
                  break;                // if it find another space, failed .quit the loop
                if(board.get(x,y) == Tile::Space)
                  break;
                if(board.get(x,y) == Tile::Black){    // Find the opponent's piece
                  is_valid = 1;                       // valid place so return true;
                  break;
                }
              }
            }
          }
        }
      }
    }
    return is_valid;
  }
  // this method is basically the same as is_invalid_move(int r, int c)
  // just the return type is different and at the end of this method
  // it will make a move and flip the opponent's pieces
  bool flip(int r, int c){
    int row_delta = 0;
    int col_delta = 0;
    int x = 0;
    int y = 0;
    bool valid = true;
    for(int i = 0; i < board.height(); i++){
      for(int j = 0; j < board.width(); j++){
        if(board.get(r,c) != Tile::Space)
          continue;
        for(row_delta = -1; row_delta <= 1; row_delta++){
          for(col_delta = -1; col_delta <= 1; col_delta++){
            if(r + row_delta < 0 || r + row_delta >= board.height() - 1
            || c + col_delta < 0 || c + col_delta >= board.width() - 1
            || (row_delta == 0 && col_delta == 0))
              continue;
            if(board.get(r + row_delta, c + col_delta) == Tile::White){
              x = r + row_delta;
              y = c + col_delta;
              for(;;){
                x += row_delta;
                y += col_delta;
                if(x < 0 || x >= board.height() - 1 || y < 0 || y >= board.width() - 1)
                  break;
                if(board.get(x,y) == Tile::Space)
                  break;
                if(board.get(x,y) == Tile::Black){
                  valid = false;
                  for(;;){
                    x -= row_delta;
                    y -= col_delta;
                    board.set_loc(r,c,Tile::Black);
                    if(x == r && y == c)
                      break;
                    board.set_loc(x,y,Tile::Black);
                  }
                  break;
                }
              }
            }
          }
        }
      }
    }
    return valid;
  }
  // translates user's typing into correct int row format
  int row_setting(const string& s){
    if(s[0] == 'a') return 1;
    else if (s[0] == 'b') return 2;
    else if (s[0] == 'c') return 3;
    else if (s[0] == 'd') return 4;
    else if (s[0] == 'e') return 5;
    else if (s[0] == 'f') return 6;
    else if (s[0] == 'g') return 7;
    else return 8;
  }
  // translates user's typing into correct int col format
  int col_setting(const string& s){
    if(s[1] == '1') return 1;
    else if (s[1] == '2') return 2;
    else if (s[1] == '3') return 3;
    else if (s[1] == '4') return 4;
    else if (s[1] == '5') return 5;
    else if (s[1] == '6') return 6;
    else if (s[1] == '7') return 7;
    else return 8;
  }
  // control user's typing and make an actual move
  void make_move(){                  // size 64 represents each place in 8 X 8 board
    int moves[64];                   // create an array that contains truth value of valid moves
    int index = 0;                   // array index
    bool no_legal_move = true;       // will be used for break the infinite loop
    for(int i = 0; i < 64; i++){     // set all initial array values to 0
      moves[i] = 0;
    }
    for(int i = 1; i <= 8; i++){
      for(int j = 1; j <= 8; j++){         // Now arr[0] = first place, which is row 1, col 1
        moves[index] = is_valid_move(i,j); // 0 and 1 truth values for valid moves are now assigned
        index++;                           // to the array moves[0] to the end moves[63]
      }                                    // now we know where the valid moves are
    }
    for(int i = 0; i <= index; i++){       // loop that finds the valid moves in the array
      if(moves[i] == 1){
        no_legal_move = false;
      }
    }
    if(no_legal_move == true){             // if array contains all 0's and no 1 then there
      while(true){                         // is no legal move
        char pass;
        cout << "You have no legal move." << endl;      // make user to pass his/her turn
        cout << "Enter 0 to pass: ";
        cin >> pass;
        if(pass == '0'){
          break;
        }
      }
    } else{                                     // if there is legal moves
      string move;
      cout << endl << "Enter your move : ";     // let user types his moves
      cin >> move;                              // check the correct format
      while( flip( row_setting(move), col_setting(move) ) ){
        if(invalid_move(move)){
          cout << "Invalid move. row: a~h , col: 1~8 (e.g. a1, b4, g7,,)" << endl
          << "Re-enter : ";
          cin >> move;
        } else{
          cout << "Invalid move. Check again." << endl << "Re-enter : ";
          cin >> move;
        }
      }
      board.println();
    }
  }
  // print both scores every end of turn.
  void print_score(){
    set_score();
    cout << "\t\tYour score : " << user_score << "\t\tComputer's score : " << comp_score << endl << endl;
  }
};
