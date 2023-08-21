#include "Piece.hpp"


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

std::vector<PiecePosition> Pieces::GetMoveset() {
  std::vector<std::vector<int>> allMoves;
  bool isWhite = (id >= 16);
  switch (_pieceType) {
    case Pieces::pawn:
      {
        int directionalMultiplier = -1;
        if (isWhite) {
          directionalMultiplier = 1;
        }
        advanceRank = rankNum + 1 * directionalMultiplier;
        if (!hasMoved) {   allMoves.push_back({fileNum, rankNum + 2 * directionalMultiplier});   }
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
Piece::Piece() {
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
  // moveSet = GetMoveset((_id - 1) % 8, rankNumber, _pieceType, b == 1);
  moveSet = GetMoveset();
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

PiecePosition Piece::GetPosition() {
  return _pos;
}

/*
	if not king
		check if in same file/rank/diagonal with king
		check if any piece between king and piece
		check if being attacked from any enemy piece along that shared line
	if not knight nor pawn nor king
		get moveset
		if not rook
			file num bigger, rank num bigger
			file num smaller, rank num bigger
			file num bigger, rank num smaller
			file num smaller, rank num smaller
		else if rook or queen or king
			file num bigger
			file num smaller
			rank num bigger
			rank num smaller
		if king
			check both rooks
				if not moved
				if no pieces in the way
				if no enemy attackers
				add castling
	else
		check if can move there based on the piece
*/

Colour Piece::GetColour() {
  return _colour;
}

void Piece::UpdateMoves() {
  if (_pieceType != Pieces::king) {
		// check if in same file/rank/diagonal with king
		// check if any piece between king and piece
		// check if being attacked from any enemy piece along that shared line
  }

  if (_pieceType != Pieces::knight && _pieceType != Pieces::pawn && _pieceType != Pieces::king) {
    std::vector<PiecePosition> currentMoves = GetMoveset();
    std::vector<std::vector<PiecePosition>> directionalMoves;
    directionalMoves.push_back({});
    directionalMoves.push_back({});
    directionalMoves.push_back({});
    directionalMoves.push_back({});
    if (_pieceType == Pieces::rook) {
      for (PiecePosition pos : currentMoves) {
        if (pos.FindFileIndex() > _pos.FindFileIndex()) { directionalMoves[0].push_back(pos); }
        else if (pos.FindFileIndex() < _pos.FindFileIndex()) { directionalMoves[1].push_back(pos); }
        else if (pos._rank > _pos._rank) { directionalMoves[2].push_back(pos); }
        else if (pos._rank < _pos._rank) { directionalMoves[3].push_back(pos); }
      }
    } else if (_pieceType == Pieces::bishop) {
      for (PiecePosition pos : currentMoves) {
        if (pos.FindFileIndex() > _pos.FindFileIndex()) {
          if (pos._rank > _pos._rank) { directionalMoves[0].push_back(pos); }
          else if (pos._rank < _pos._rank) { directionalMoves[1].push_back(pos); }
        }
        else if (pos.FindFileIndex() < _pos.FindFileIndex()) {
          if (pos._rank > _pos._rank) { directionalMoves[2].push_back(pos); }
          else if (pos._rank < _pos._rank) { directionalMoves[3].push_back(pos); }
        }
      }
    } else if (_pieceType == Pieces::queen) {
      directionalMoves.push_back({});
      directionalMoves.push_back({});
      directionalMoves.push_back({});
      directionalMoves.push_back({});
      for (PiecePosition pos : currentMoves) {
        if (pos.FindFileIndex() > _pos.FindFileIndex()) {
          if (pos._rank > _pos._rank) { directionalMoves[0].push_back(pos); }
          else if (pos._rank < _pos._rank) { directionalMoves[1].push_back(pos); }
          directionalMoves[2].push_back(pos);
        }
        else if (pos.FindFileIndex() < _pos.FindFileIndex()) {
          if (pos._rank > _pos._rank) { directionalMoves[3].push_back(pos); }
          else if (pos._rank < _pos._rank) { directionalMoves[4].push_back(pos); }
          directionalMoves[5].push_back(pos);
        }
        else if (pos._rank > _pos._rank) { directionalMoves[6].push_back(pos); }
        else if (pos._rank < _pos._rank) { directionalMoves[7].push_back(pos); }
      }
    }
  }
}



PiecePosition::PiecePosition() {}

void PiecePosition::SetFile(char file) {
  _file = file;
}
void PiecePosition::SetRank(int rank) {
  _rank = rank;
}

int PiecePosition::FindFileIndex(char fileChar) {
  for (int i = 0; i < 8; i++) {
    if (fileChar == files[i]) {
      return i;
    }
  }
  return -1;
}

int PiecePosition::FindFileIndex() {
  for (int i = 0; i < 8; i++) {
    if (files[i] == _file) {
      return i;
    }
  }
  return -1;
}

void PiecePosition::Translate(int filesTranslated, int ranksTranslated) {
  _file = files[(FindFileIndex(_file) + filesTranslated) % 8];
  _rank = (_rank + ranksTranslated) % 8;
}

PiecePosition PiecePosition::GetTranslatedPos(int filesTranslated, int ranksTranslated) {
  char file = files[(FindFileIndex(_file) + filesTranslated) % 8];
  int rank = (_rank + ranksTranslated) % 8;
  PiecePosition translatedPos;
  translatedPos.SetFile(file);
  translatedPos.SetRank(rank);
  return translatedPos;
}

int PiecePosition::GetBoardIndex() {
  return 63 - (FindFileIndex() + (_rank - 1) * 8);
}

Pawn::Pawn(Colour colour, PiecePosition startingPos) : _colour(colour), _pos(startingPos) {
  _pos = startingPos;

}

void Pawn::UpdateMoves(std::vector<Piece> board, bool isKingPinned=false) {
  if (isKingPinned) {   return;   }

  int forwardDirection = _colour == Colour::white ? 1 : -1;
  std::vector<PiecePosition> allMoves;
  if (_pos._file != 'a') {
    PiecePosition leftCapture = GetTranslatedPos(-1, forwardDirection);
    int leftPieceColour = board[leftCapture.GetBoardIndex()].GetColour()
    if (abs(1 - leftPieceColour) == 1) {
      allMoves.push_back(leftCapture);
    }
  }
  if (_pos._file != 'h') {
    PiecePosition rightCapture = GetTranslatedPos(1, forwardDirection);
    int rightPieceColour = board[rightCapture.GetBoardIndex()].GetColour()
    if (abs(1 - rightPieceColour) == 1) {
      allMoves.push_back(rightCapture);
    }
  }
  PiecePosition forward1 = GetTranslatedPos(0, forwardDirection);
  if (board[foward1.GetBoardIndex()].GetColour() == Piece::empty) {
    allMoves.push_back(forward1);
    if (!hasMoved) {
      PiecePosition forward2 = GetTranslatedPos(0, forwardDirection * 2);
      if (board[foward1.GetBoardIndex()].GetColour() == Piece::empty) {
        allMoves.push_back(forward2);
      }
    }
  }
}