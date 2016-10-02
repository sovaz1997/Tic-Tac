#include "game.hpp"

Game::Game() {
  startGame();
}
Game::~Game() {}

double Game::minimax(Board b, int depth) {
  if(b.evalute() != 0 || depth >= 9) {
    return b.evalute() / depth;
  }

  double max = -INFINITY;
  std::vector<Move>moves = b.generator();

  Board saved = b;
  Move local_move;

  for(unsigned int i = 0; i < moves.size(); ++i) {
    b.go(moves[i]);
    double tmp = -minimax(b, depth + 1);

    if(tmp > max) {
      max = tmp;
      local_move = moves[i];
    }
    b = saved;
  }

  if(depth == 0) {
    if(moves.size() > 0) {
      board.go(local_move);
    }
  }

  return max;
}

int Game::startGame() {
  board.print();

  int pos;
  int num_moves = 0;

  std::cout << "Вы кто (крестик - 1, нолик - 0): ";
  int you;
  std::cin >> you;
  if(you == 0) {
    you = -1;
  }
  while(num_moves <= 9) {
    if(you == 1) {
      std::cout << "Введите номер клетки (1-9): ";
      std::cin >> pos;
      --pos;
      Move move = Move(board.crossMove, pos / SIZE, pos % SIZE);
      while(!board.testOfLegalMove(move)) {
        std::cout << "Введите номер клетки (1-9): ";
        std::cin >> pos;
      }
      board.go(move);
      ++num_moves;
      you = -you;
    } else {
      minimax(board, 0);
      ++num_moves;
      board.print();
      you = -you;
    }
    if(board.evalute() * you > 0) {
      std::cout << "Вы выиграли!\n";
      return 0;
    } else if(board.evalute() * you < 0) {
      std::cout << "Вы проиграли!\n";
      return 0;
    }
  }

  std::cout << "Ничья!\n";
  return 0;
}
