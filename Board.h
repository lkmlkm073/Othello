// Board.h

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

using namespace std;
// using enum class called Tile instead of chars
enum class Tile : char {
    Black ='B', White='W', Edge_Top ='_', Edge_Bottom = ' ', Edge_Side = '|', Corner = '+', Space = ' '
};
// number of rows = height
// number of cols = width
class Board{
  // vector inside vector called board;
  vector<vector<Tile>> board;
  struct Location{
    int row;
    int col;
  };
public:
  // constructor
  Board(int w, int h)
  :board(h)
  {
    assert(w > 1 && h > 1);
    // initialliy filled columns with spaces
    for(int i = 0; i < board.size(); i++){
      board[i] = vector<Tile>(w, Tile::Space);
    }
    // Corners are '+'
    board[0][0] = Tile::Corner;
    board[9][0] = Tile::Corner;
    board[0][9] = Tile::Corner;
    board[9][9] = Tile::Corner;
    for(int i = 1; i < w-1; i++) board[0][i] = Tile::Edge_Top;        // Top border
    for(int i = 1; i < w-1; i++) board[w-1][i] = Tile::Edge_Bottom;   // Bottom border
    for(int i = 1; i < h-1; i++) board[i][0] = Tile::Edge_Side;       // Left border
    for(int i = 1; i < h-1; i++) board[i][h-1] = Tile::Edge_Side;     // Right border
  }
  // getters get width and height. in this case = 10;   10 X 10 board
  int width() const { return board[0].size(); }
  int height() const { return board.size(); }
  // check the board size;  Must be 10 x 10
  bool check_board(int row, int col) const {
    return (row >= 0 && row < height()) && (col >= 0 && col < width());
  }
  // set_loc will allow to fill the given location on the board with given tile
  void set_loc(int row, int col, const Tile& tile){
    assert(check_board(row, col));
    board[row][col] = tile;
  }
  // get Tile in the given location
  Tile get(int row, int col) const {
    assert(check_board(row, col));
    return board[row][col];
  }
  // print Board formally
  void print() const {
    for(int i = 0; i < height(); i++){
      if( 0 < i && i < 9){
        cout << "\t\t\t" << char('a'-1 + i) << char(board[i][0]);  // a to h (1~8) indicator
      }
      if( i == 0 || i == 9){ cout << "\t\t\t"; }
      for(int j = 0; j < width(); j++){
        if( (i == 0 && j == 0) || (i == 0 && j == 9) ){
          if(j == 9){
            cout << " " << char(board[i][j]);                      // cout Tiles in board
            continue;
          }
          cout << char(board[i][j]);                               // cout Tiles in board
          continue;
        }
        if( (i == 0 && j > 0) || (i == 0 && j < 9) ){
          cout << " " << char(board[i][j]) << j;                   // 1 to 8 indicator
          continue;
        }
        if ( i == 9 ){
          if(j == 8){
            cout << char(board[i][j]) << " ";                     // cout Tiles in board
            continue;
          }
          cout << char(board[i][j]) << "  ";                      // cout Tiles in board
          continue;
        }
        if( (i != 0 || i != 9) && (j >=1 && j <= 8) ){
          cout << "_" << char(board[i][j]) << "|";                // cout Tiles in board
          continue;                                               // and also layout _|
        }
      }
      cout << endl;
    }
  }
  // print with extra space line
  void println() const {
    print();
    cout << endl;
  }
};
