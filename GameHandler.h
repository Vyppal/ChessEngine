#include <vector>

double timeControl = 120;

struct GameState {
  std::vector<char> boardLayout;
  double whiteTime;
  double blackTime;
  bool whiteCastleRights;
  bool blackCastleRights;
}








class GameHandler {

 public:

  GameState GetGameState(){
    return GameState{
      board,
      whiteTime,
      blackTime,
      whiteCastleRights,
      blackCastleRights
    }
  }

  void RecieveMove() {}

  bool ValidateMove() {}

  // lichess api

 private:
  std::vector<char> board = {
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
  bool whiteCastleRights = true;
  bool blackCastleRights = true;
}



/*

recieve move in tile from, tile to, additional flag format
once recieved move
  determine if move is legal
    if not legal:
      lose game
    update game board


updating game board
  set new tile and old tile type
  set tiles to "white targetted" or "black targetted" or both

    

determining if move is legal
  if king on target square



*/


/*
each piece has a piece id

*/