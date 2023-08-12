#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

enum Pieces {
  pawn,
  knight,
  bishop,
  rook,
  queen,
  king,
  empty
};


class PiecePosition {
 public:
  PiecePosition(char fileChar, int rankNum);

  void SetFile(char file);
  void SetRank(int rank);

  void Translate(int filesTranslated, int ranksTranslated);
  int FindFileIndex(char fileChar);

  static constexpr char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char _file;
  int _rank;

 private:
  
};

class Piece {
 public:
  Piece(int id);
  PiecePosition GetPosition();

  void MovePiece(PiecePosition newPos);
  // void UpdateMoveSet(); // is actually taken care of in MovePiece

 private:
  int _id;
  Pieces _pieceType;
  PiecePosition _pos{'a', 1};
  bool hasMoved = false;
  // assuming and empty board, the tiles the piece can attack
  std::vector<PiecePosition> moveSet;
  std::vector<PiecePosition> allowedMoves;

};