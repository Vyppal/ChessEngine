#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

enum Pieces {
  pawn,
  knight,
  bishop,
  rook,
  queen,
  king,
  empty
};

enum Colour {   empty = -5, black = 0, white = 1   };

class PiecePosition {
 public:
  PiecePosition();

  void SetFile(char file);
  void SetRank(int rank);

  void Translate(int filesTranslated, int ranksTranslated);
  PiecePosition GetTranslatedPos(int filesTranslated, int ranksTranslated);
  int FindFileIndex(char fileChar);
  int FindFileIndex();

  int GetBoardIndex();

  static constexpr char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char _file;
  int _rank;

 private:
  
};

class Piece {
 public:
  Piece();
  PiecePosition GetPosition();

  std::vector<PiecePosition> GetMoveset();

  void UpdateBoard(std::vector<Piece> board);
  void MovePiece(PiecePosition newPos);
  virtual void UpdateMoves(std::vector<Piece> board) override;
  // void UpdateMoveSet(); // is actually taken care of in MovePiece

  Colour GetColour();

 private:
  Colour _colour;
  PiecePosition _pos;
  Pieces _pieceType;
  bool hasMoved = false;
  // assuming and empty board, the tiles the piece can attack
  std::vector<PiecePosition> moveSet;
  std::vector<PiecePosition> allowedMoves;
};


class Empty : public Piece {
 public:
  Empty(Colour colour, PiecePosition startingPos);

 private:

}

class Pawn : public Piece {
 public:
  Pawn(Colour colour, PiecePosition startingPos);

  void UpdateMoves(std::vector<Piece> board);

 private:
  _pieceType = Pieces::pawn;
};

class Knight : public Piece {
 public:
  Knight(Colour colour, PiecePosition startingPos);

 private:
  _pieceType = Pieces::knight;
};

class Bishop : public Piece {
 public:
  Bishop(Colour colour, PiecePosition startingPos);

 private:
  _pieceType = Pieces::bishop;
};

class Queen : public Piece {
 public:
  Queen(Colour colour, PiecePosition startingPos);

 private:
  _pieceType = Pieces::queen;
};

class King : public Piece {
 public:
  King(Colour colour, PiecePosition startingPos);

 private:
  _pieceType = Pieces::king;
};

