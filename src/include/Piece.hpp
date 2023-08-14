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
  int FindFileIndex();

  static constexpr char files[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
  char _file;
  int _rank;

 private:
  
};

class Piece {
 public:
  Piece(int id);
  PiecePosition GetPosition();


  std::vector<PiecePosition> GetMoveset();

  void UpdateBoard(std::vector<Piece> board);
  void MovePiece(PiecePosition newPos);
  void UpdateMoves();
  // void UpdateMoveSet(); // is actually taken care of in MovePiece

 private:
  int _id;
  Pieces _pieceType;
  PiecePosition _pos{'a', 1};
  bool hasMoved = false;
  // assuming and empty board, the tiles the piece can attack
  std::vector<PiecePosition> moveSet;
  std::vector<PiecePosition> allowedMoves;

  std::vector<Piece> _board = {
    Pieces::black_rook, Pieces::black_knight, Pieces::black_bishop, Pieces::black_queen, Pieces::black_king, Pieces::black_bishop, Pieces::black_knight, Pieces::black_rook,
    Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn, Pieces::black_pawn,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty, Pieces::empty,
    Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, Pieces::white_pawn, 
    Pieces::white_rook, Pieces::white_knight, Pieces::white_bishop, Pieces::white_queen, Pieces::white_king, Pieces::white_bishop, Pieces::white_knight, Pieces::white_rook
  };
};