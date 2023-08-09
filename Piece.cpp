#include "Piece.h"
#include <iostream>
#include <algorithm>



std::vector<PiecePosition> GetMoveset(int fileNum, int rankNum, Pieces pieceType, bool isWhite=true) {
  // std::vector<PiecePosition> 
  // switch (pieceType) {
  //   case white_pawn:
  //     if (fileNum)
  // };
  // return {};

  std::vector<std::vector<int>> allMoves;
  switch (pieceType) {
    case Pieces::pawn:
      if (isWhite) {
      }
      break;
    case Pieces::knight:
      break;
    case Pieces::bishop:
      for (int i = 1; i < 8; i++) {
        allMoves.push_back({(fileNum - i) % 8, (rankNum - i) % 8});
        allMoves.push_back({(fileNum - (8-i)) % 8, (rankNum - i) % 8});
      }
      
  }
  
};

// id must be 1-32 inclusive
Piece::Piece(int id) : _id(id) {
  int pawnRank = 7;
  int pieceRank = 8;
  if (_id <= 16) {
    pawnRank = 2;
    pieceRank = 1;
  }
  int moduloedID = (_id - 1) % 16;
  _pos.SetFile(_pos.files[(_id - 1) % 8]);
  if (moduloedID >= 9) {
    _pieceType = Pieces::pawn;
    _pos.SetRank(pawnRank);
  } else {
    _pos.SetRank(pieceRank);

    if (moduloedID == 0 || moduloedID == 7) {
      _pieceType = Pieces::rook;
    } else if (moduloedID == 1 || moduloedID == 6) {
      _pieceType = Pieces::knight;
    } else if (moduloedID == 2 || moduloedID == 5) {
      _pieceType = Pieces::bishop;
    } else if (moduloedID == 3) {
      _pieceType = Pieces::queen;
    } else {
      _pieceType = Pieces::king;
    }
  }
}


// PiecePosition::PiecePosition() {}
PiecePosition::PiecePosition(char fileChar, int rankNum): _file(fileChar), _rank(rankNum) {}

void PiecePosition::SetFile(char file) {
  _file = file;
}
void PiecePosition::SetRank(int rank) {
  _rank = rank;
}

PiecePosition Piece::GetPosition() {
  return _pos;
}


int PiecePosition::FindFileIndex(char fileChar) {
  for (int i = 0; i < 8; i++) {
    if (fileChar == files[i]) {
      return i;
    }
  }
  return -1;
}



void PiecePosition::Translate(int filesTranslated, int ranksTranslated) {
  _file = files[(FindFileIndex(_file) + filesTranslated) % 8];
  _rank = (_rank + ranksTranslated) % 8;
}

void Piece::MovePiece(PiecePosition newPos) {
  PiecePosition prevPos = _pos;
  _pos = newPos;

  int fileTranslate = newPos.FindFileIndex(newPos._file) - prevPos.FindFileIndex(prevPos._file);
  int rankTranslate = newPos._rank - prevPos._rank;

  int targetableTilesSize = sizeof(moveset);
  for (int i = 0 ; i < targetableTilesSize; i++) {
    targetableTiles[i].Translate(fileTranslate, rankTranslate);
  }
}