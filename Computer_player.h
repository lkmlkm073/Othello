// Computer_player.h

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

// This class is quite similar to the Human_player class
// Only the difference is it will make a random moves in only valid places
// and it will take corners prior to other valid places.
using namespace std;
// Human_player class that dervied from Player class
class Computer_player : public Player {
  int comp_score;             // contains user and comp score
  int user_score;
  Board board;
public:
  // constructor
  Computer_player(Board B)
  : comp_score(0),user_score(0), board(B)
  { }
  // getters that return board and comp_score
  Board get_board() const { return board; }
  int get_score() const { return comp_score;}
  // get board from the opponent and use it
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
  // Now check board[r][c] is legal or not
  // 0 means false, 1 means true;
  // totally identical to the Human_player's method
  // only the opponent colour is different
  int is_valid_move(int r, int c){
    int row_delta = 0;
    int col_delta = 0;
    int x = 0;
    int y = 0;
    int is_valid = 0;
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
            if(board.get(r + row_delta, c + col_delta) == Tile::Black){
              x = r + row_delta;
              y = c + col_delta;
              for(;;){
                x += row_delta;
                y += col_delta;
                if(x < 0 || x >= board.height() - 1 || y < 0 || y >= board.width() - 1)
                  break;
                if(board.get(x,y) == Tile::Space)
                  break;
                if(board.get(x,y) == Tile::White){
                  is_valid = 1;
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
  // Same as well
  bool flip(int r, int c){
    int row_delta = 0;
    int col_delta = 0;
    int x = 0;
    int y = 0;
    bool is_valid = true;

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
            if(board.get(r + row_delta, c + col_delta) == Tile::Black){
              x = r + row_delta;
              y = c + col_delta;
              for(;;){
                x += row_delta;
                y += col_delta;
                if(x < 0 || x >= board.height() - 1 || y < 0 || y >= board.width() - 1)
                  break;
                if(board.get(x,y) == Tile::Space)
                  break;
                if(board.get(x,y) == Tile::White){
                  is_valid = false;
                  for(;;){
                    x -= row_delta;
                    y -= col_delta;
                    board.set_loc(r,c,Tile::White);
                    if(x == r && y == c)
                      break;
                    board.set_loc(x,y,Tile::White);
                  }
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
  // This part is quite different
  // basically creating the array contains truth values of the valid moves are the Same
  // but this time it will make a move randomly and take important places first.
  void make_move(){
    int row = 1;
    int col = 1;
    int valid_moves[64];
    int index = 0;
    bool no_legal_move = true;
    // Here
    for(int i = 0; i < 64; i++){
      valid_moves[i] = 0;
    }
    for(int i = 1; i <= 8; i++){
      for(int j = 1; j <= 8; j++){
        valid_moves[index] = is_valid_move(i,j);
        index++;
      }
    }
    for(int i = 0; i <= index; i++){
      if(valid_moves[i] == 1){
        no_legal_move = false;
      }
    }
    // to Here are same
    while(true){
      if( no_legal_move ){      // if no more valid moves, automatically pass its turn
        cout << "Computer has no legal move. It is your turn again." << endl;
        break;
      }
      // Take corners is a prioritiy
      if(valid_moves[0] == 1){
        flip(1,1);
        board.println();
        break;
      } else if(valid_moves[7] == 1){     // valid_moves[7] = (1,8) ; row 1, col 8
        flip(1,8);
        board.println();
        break;
      } else if(valid_moves[56] == 1){    // valid_moves[56] = (8,1) ; row 8, col 1
        flip(8,1);
        board.println();
        break;
      } else if(valid_moves[63] == 1){    // and so on...
        flip(8,8);
        board.println();
        break;
      }
      row = rand() % 8 + 1;              // set random row and col 1 to 8
      col = rand() % 8 + 1;
      if( !flip(row,col) ){              // if those randomly generated values have valid position
        board.println();                 // then make a move and quit the loop
        break;
      }
    }
  }
  // print score method
  void print_score(){
    set_score();
    cout << "\t\tYour score : " << user_score << "\t\tComputer's score : " << comp_score << endl << endl;
  }
};
