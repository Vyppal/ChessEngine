#pragma once

#include <vector>
#include "Piece.hpp"

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

/* PieceColour, b=black, w=white, empty */
enum PC {
  b,
  w,
  e
};

// surely each piece should be a class which derives from a "piece class which has things like state"

class GameHandler {
 public:

  GameHandler();

  GameState GetGameState();

  /**
   * @brief Use this to send the gamehandler your choice of move
   * @param tileFrom An integer array of size 2 (fileNumber, rankNumber) representing the tile from which your moved piece is
   * @param tileTo An integer array of size 2 (fileNumber, rankNumber) representing the tile which you want your piece to move to
   * @param promotionPiece The capitalised algebraic notation of a piece a pawn should promote to. By default it's none.
  */
  void GiveMove(int tileFrom[2], int tileTo[2], char promotionPiece=' ');

  bool ValidateMove(); // surely this has to take in a move 

  // lichess api ??

 private:
  bool isWhitesTurn = true;
  std::vector<Piece> _pieces;

  double whiteTime = timeControl;
  double blackTime = timeControl;
  bool whiteShortCastleRights = true;
  bool blackShortCastleRights = true;
  bool whiteLongCastleRights = true;
  bool blackLongCastleRights = true;
};
