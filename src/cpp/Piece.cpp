#include "Piece.hpp"

/*
UNFINISHED!

gets every square the piece can move to assuming board is empty
*/
std::vector<PiecePosition> ConvertAndTrimMoves(std::vector<std::vector<int>> moves) {
  std::vector<PiecePosition> outputMoves;
  for (auto move : moves) {
    if (move[0] < 1) continue;
    if (move[1] < 1) continue;
    if (move[0] > 8) continue;
    if (move[1] > 8) continue;
    outputMoves.push_back(PiecePosition{PiecePosition::files[move[0] - 1], move[1]});
  }
  return outputMoves;
}

std::vector<PiecePosition> GetMoveset(int fileNum, int rankNum, Pieces pieceType, bool isWhite=true) {
  std::vector<std::vector<int>> allMoves;
  switch (pieceType) {
    case Pieces::pawn:
      {
        int advanceRank;
        if (isWhite) {
          advanceRank = rankNum + 1;
          if (rankNum == 2) {   allMoves.push_back({fileNum, rankNum + 2});   }
        } else {
          advanceRank = rankNum - 1;
          if (rankNum == 7) {   allMoves.push_back({fileNum, rankNum - 2});   }
        }
        allMoves.push_back({fileNum, advanceRank});
        allMoves.push_back({fileNum - 1, advanceRank});
        allMoves.push_back({fileNum + 1, advanceRank});
      } break;
    case Pieces::knight:
      allMoves.push_back({fileNum - 2, rankNum - 1});
      allMoves.push_back({fileNum - 2, rankNum + 1});
      allMoves.push_back({fileNum - 1, rankNum - 2});
      allMoves.push_back({fileNum - 1, rankNum + 2});
      allMoves.push_back({fileNum + 1, rankNum - 2});
      allMoves.push_back({fileNum + 1, rankNum + 2});
      allMoves.push_back({fileNum + 2, rankNum - 1});
      allMoves.push_back({fileNum + 2, rankNum + 1});
      break;
    case Pieces::queen:
      [[fallthrough]]
    case Pieces::bishop:
      for (int i = 1; i < 8; i++) {
        allMoves.push_back({(fileNum - i) % 8, (rankNum - i) % 8});
        allMoves.push_back({(fileNum - (8-i)) % 8, (rankNum - i) % 8});
      }
      if (pieceType != Pieces::queen) break;
      [[fallthrough]]
    case Pieces::rook:
      for (int i = 1; i < 8; i++) {
        allMoves.push_back({(fileNum - i) % 8, rankNum});
        allMoves.push_back({fileNum, (rankNum - i) % 8});
      }
      break;
    case Pieces::king:
      allMoves.push_back({fileNum - 1, rankNum - 1});
      allMoves.push_back({fileNum - 1, rankNum});
      allMoves.push_back({fileNum - 1, rankNum + 1});
      allMoves.push_back({fileNum, rankNum - 1});
      allMoves.push_back({fileNum, rankNum + 1});
      allMoves.push_back({fileNum + 1, rankNum - 1});
      allMoves.push_back({fileNum + 1, rankNum});
      allMoves.push_back({fileNum + 1, rankNum + 1});
      break;
  }
  return ConvertAndTrimMoves(allMoves);
};

// id must be 1-32 inclusive
Piece::Piece(int id) : _id(id) {
  int a = (id-1) / 8;
  int b = (id - 1) / 16;
  int rankNumber = 8 + (2*a - 7 - 2*b) * b - a;
  int moduloedID = (_id - 1) % 16;
  _pos.SetFile(_pos.files[(_id - 1) % 8]);
  _pos.SetRank(rankNumber);
  if (moduloedID >= 9) {
    _pieceType = Pieces::pawn;
  } else {
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
  moveSet = GetMoveset((_id - 1) % 8, rankNumber, _pieceType, b == 1);
}

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

  int targetableTilesSize = sizeof(moveSet);
  for (int i = 0 ; i < targetableTilesSize; i++) {
    moveSet[i].Translate(fileTranslate, rankTranslate);
  }
}