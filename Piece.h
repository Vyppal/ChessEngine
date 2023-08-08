#pragma once

#include <vector>

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
};


class PiecePosition {
 public:
  PiecePosition(char fileChar, int rankNum);

  void Translate(int filesTranslated, int ranksTranslated);
  int FindFileIndex(char fileChar);
  
  char file;
  int rank;

 private:
  char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

};


class Piece {
 public:
  Piece(int id);
  PiecePosition GetPosition();
  void Promote(Pieces promotionPiece);

  void MovePiece(PiecePosition newPos);

 private:
  int _id;
  PiecePosition _pos;
  Pieces pieceType;

  // assuming and empty board, the tiles the piece can attack
  std::vector<PiecePosition> targetableTiles;

};
