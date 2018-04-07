// Player.h

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
// Base class Player
class Player{
public:
  Player(){}
  // virtual destructor
  virtual ~Player(){ }
  // virtual methods
  virtual void make_move() = 0;
  virtual int get_score() const = 0;
  virtual Board get_board() const = 0;
  virtual void print_score() = 0;
  virtual void set_board( Board B ) = 0;
};
