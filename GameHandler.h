#include <vector>

double timeControl = 120;

struct GameState {
  char[64] boardLayout;
  double whiteTime;
  double blackTime;
  bool whiteCastleKingside;
  bool whiteCastleQueenside;
  bool blackCastleKingSide;
  bool blackCastleQueenside;
}


enum Pieces {
  white_pawn,
  white_knight,
  white_bishop,
  white_rook,
  white_queen,
  white_king,
  black_pawn
  black_knight,
  black_bishop,
  black_rook,
  black_queen,
  black_king,
  empty
}







class GameHandler {

 public:

  GameState GetGameState(){
    return GameState{
      board,
      whiteTime,
      blackTime,
      whiteCastleKingside,
      whiteCastleQueenside,
      blackCastleKingside,
      blackCastleQueenside
    }
  }

  void RecieveMove() {}

  bool ValidateMove() {}

  // lichess api

 private:
  char[64] board = {
  /* a    b    c    d    e    f    g    h*/
    'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r', /* 8 */
    'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p', /* 7 */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 6 */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 5 */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 4 */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', /* 3 */
    'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P', /* 2 */
    'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'  /* 1 */
  }
  board = {
    Pieces::black_rook, Pieces::black_knight, Pieces::black_bishop, Pieces::black_queen, Pieces::black_king, Pieces::black_bishop, Pieces::black_knight, Pieces::black_rook,
    Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, 
    Pieces::white_rook, Pieces::white_knight, Pieces::white_bishop, Pieces::white_queen, Pieces::white_king, Pieces::white_bishop, Pieces::white_knight, Pieces::white_rook
  }
  double whiteTime = timeControl;
  double blackTime = timeControl;
  bool whiteCastleKingside = true;
  bool whiteCastleQueenside = true;
  bool blackCastleKingside = true;
  bool blackCastleQueenside = true;
}
