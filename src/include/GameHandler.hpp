#include <vector>

double timeControl = 120;

struct GameState {
  std::vector<char> boardLayout;
  double whiteTime;
  double blackTime;
  bool whiteCastleRights;
  bool blackCastleRights;
  bool whiteShortCastleRights;
  bool blackShortCastleRights;
  bool whiteLongCastleRights;
  bool blackLongCastleRights;
};

enum Pieces {
  white_pawn,
  white_knight,
  white_bishop,
  white_rook,
  white_queen,
  white_king,
  black_pawn,
  black_knight,
  black_bishop,
  black_rook,
  black_queen,
  black_king,
  empty
};

// surely each piece should be a class which derives from a "piece class which has things like state"

class GameHandler {
 public:

  GameState GetGameState(){
    return GameState{
      board,
      whiteTime,
      blackTime,
      whiteShortCastleRights,
      blackShortCastleRights,
      whiteLongCastleRights,
      blackLongCastleRights
    };
};

  void RecieveMove() {} // surely this should return a move to be validated and used to change the board

  bool ValidateMove() {} // surely this has to take in a move 

  // lichess api ??

 private:
  // std::vector<char> board = {
  // /* a    b    c    d    e    f    g    h*/
  //   'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', /* 8 */
  //   'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', /* 7 */
  //   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 6 */
  //   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 5 */
  //   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 4 */
  //   ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 3 */
  //   'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', /* 2 */
  //   'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'  /* 1 */
  // }; dunno what this was meant to be

  std::vector<Piece> board = {
    Pieces::black_rook, Pieces::black_knight, Pieces::black_bishop, Pieces::black_queen, Pieces::black_king, Pieces::black_bishop, Pieces::black_knight, Pieces::black_rook,
    Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, 
    Pieces::white_rook, Pieces::white_knight, Pieces::white_bishop, Pieces::white_queen, Pieces::white_king, Pieces::white_bishop, Pieces::white_knight, Pieces::white_rook
  }; // nice

  double whiteTime = timeControl;
  double blackTime = timeControl;
  bool whiteShortCastleRights = true;
  bool blackShortCastleRights = true;
  bool whiteLongCastleRights = true;
  bool blackLongCastleRights = true;
};
