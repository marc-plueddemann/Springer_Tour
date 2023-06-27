#include <cstddef>
#include <cstdio>

struct Position {
  int x;
  int y;
};

struct Board {
  int data[7][6];
  Position pos;
  int current;
  int cols;
  int rows;
  int nums;
};

void getNums(Board &board) {
  for (int i = 0; i < board.rows; i++) {
    for (int j = 0; j < board.cols; j++) {
      if (board.data[i][j] != -1) {
        board.nums = board.nums & (1 << board.data[i][j]);
      }
    }
  }
}

void setNum(Board &board) {
  board.nums = board.nums & (1 << board.current);
}

bool containsNum(Board &board) {
  return board.nums & (1 << board.current);
}

bool isValidMove(Board &board, Position move, Position pos) {
  int dx = pos.x + move.x;
  if ((dx >= board.cols) || (dx < 0)) {
    return false;
  }

  int dy = pos.y + move.y;
  if ((dy >= board.rows) || (dy < 0)) {
    return false;
  }
  return true;
}

void print_board(Board &board) {
  for (int i = 0; i < board.rows; i++) {
    for (int j = 0; j < board.cols; j++) {
      if (board.data[i][j] == -1)
        printf("x\t");
      else
        printf("%d\t", board.data[i][j]);
    }
    printf("\n");
  }
  printf("iteration = %d\n", board.current);
}

void print_move(Position move) {
  printf("x = %d, y = %d\n", move.x, move.y);
}

Board fill_board(Board board) {
  board.current++;
  Position moves[] = {
    {1, 2},
    {1, -2},
    {-1, 2},
    {-1, -2},
    {-2, 1},
    {-2, -1},
    {2, 1},
    {2, -1},
  };

  if (board.current == (board.cols * board.rows)) {
    return board;
  }

  for (int i = 0; i < 8; i++) {
    Position move = moves[i];

    if (!isValidMove(board, move, board.pos)) {
      continue;
    }

    int x = board.pos.x;
    int y = board.pos.y;

    if(containsNum(board) && 
        (board.data[y+move.y][x+move.x] != board.current)
      ) {
      continue;
    }

    if((board.data[y+move.y][x+move.x] != -1) && 
        (board.data[y+move.y][x+move.x] != board.current)
      ) {
      continue;
    }

    Board new_board = board;
    new_board.data[y+move.y][x+move.x] = board.current;
    new_board.pos = Position {
      x+move.x, y+move.y
    };
    setNum(new_board);

    // print_board(new_board);
    // print_move(move);
    // print_move(board.pos);
    // if (board.current == 23)
    //   return new_board;
    Board result = fill_board(new_board);
    if (result.current != -1) {
      return result;
    }
  }
  board.current = -1;
  return board;
}

void fill_board_outer(Board &board) {
  getNums(board);
  board = fill_board(board);
}

int main(int argc, char** argv) {
  Board board1 = Board {
    .data = {
      {0,-1,4,-1,-1,-1},
      {3,-1,1,-1,5,-1},
      {-1,29,-1,7,-1,-1},
      {-1,2,-1,-1,-1,6},
      {-1,-1,-1,-1,-1,-1}
    },
    .pos = Position { 3, 2 },
    .current = 7,
    .cols = 6,
    .rows = 5
  };
  Board board3 = Board {
    .data = {
      {0,-1,-1,-1,-1,-1},
      {-1,-1,-1,-1,-1,-1},
      {-1,-1,-1,-1,-1,-1},
      {-1,-1,-1,-1,-1,-1},
      {-1,-1,-1,-1,-1,-1}
    },
    .pos = Position { 0, 0 },
    .current = 0,
    .cols = 6,
    .rows = 5
  };
  Board board2 = Board {
    .data = {{0,-1,-1,-1,-1,-1},
            {-1,-1,1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1},
            {-1,2,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1}},    
    .pos = Position { 1, 3 },
    .current = 2,
    .cols = 6,
    .rows = 5,
  };
  Board board4 = Board {
    .data = {{0,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1},{-1,-1,-1,-1}},
    .pos = Position { 0, 0 },
    .current = 0,
    .cols = 4,
    .rows = 4,
  };

  Board board = board2;
  
  print_board(board);
  board = fill_board(board);
  print_board(board);
  return 0;
}
