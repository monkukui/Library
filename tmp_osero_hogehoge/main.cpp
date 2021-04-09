#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// オセロサイズ
const int n = 8;
using grid = vector<vector<char>>;

grid pre_grid;

void print(grid grid) {

  // cout << "\x1b[2j\x1b[h";
  cout << "  ";
  for (int i = 0; i < n; i++) {
    cout << i + 1 << " ";
  }
  cout << endl;
  cout << "  ---------------" << endl;
  for (int i = 0; i < n; i++) {
    cout << i + 1 << "|";
    for (int j = 0; j < n; j++) {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
}

char next_turn(char turn) {
  if (turn == 'o') return 'x';
  else return 'o';
}

// -1, -1 だったら、行ってもどす
pair<int, int> read_input() {
  cout << ">> ";
  int i, j;
  cin >> i >> j;
  i--;
  j--;
  return {i, j};
}

bool out_of_grid(int i, int j) {
  if (i < 0) return true;
  if (j < 0) return true;
  if (i >= n) return true;
  if (j >= n) return true;
  return false;
}

// grid[i][j] に turn をおく
// 返り値：{おいた後の grid, 実際におけたかどうか}
pair<grid, bool> put(grid grid, int i, int j, char turn) {
  const char player = (turn == 'o') ? 'o' : 'x';
  const char opponent = (turn == 'x') ? 'o' : 'x';

  // グリッドの外なら、ダメ
  if (out_of_grid(i, j)) {
    return {{}, false};
  }
  // すでに置かれてるところダメ
  if (grid[i][j] != '.') {
    return {{}, false};
  }

  // ちゃんとひっくり返ったかどうか
  bool ok = false;

  // 8 方向見る
  int di[] = {1, 1, 0, -1, -1, -1, 0, 1};
  int dj[] = {0, -1, -1, -1, 0, 1, 1, 1};
  for (int dir = 0; dir < 8; dir++) {
    int ni = i + di[dir];
    int nj = j + dj[dir];
    if (out_of_grid(ni, nj)) {
      continue;
    }

    // 隣が、相手の駒である必要がある
    if (grid[ni][nj] != opponent) {
      continue;
    }

    // (i, j) が自分の駒
    // (ni, nj) が相手の駒
    int pi = -1;
    int pj = -1;
    while (true) {
      if (out_of_grid(ni, nj)) {
        break;
      }
      if (grid[ni][nj] == player) {
        pi = ni;
        pj = nj;
        break;
      }
      if (grid[ni][nj] == '.') {
        break;
      }
      ni += di[dir];
      nj += dj[dir];
    }
    // 自分の駒が見つかってなかったら、ダメ
    if (pi == -1) {
      continue;
    }

    // 区間 (i, j) -> (pi, pj) が oxxxxxo
    ok = true;
    ni = i;
    nj = j;
    while (true) {
      if (ni == pi and nj == pj) {
        break;
      }
      grid[ni][nj] = turn;
      ni += di[dir];
      nj += dj[dir];
    }
  }

  if (!ok) {
    return {{}, false};
  }

  grid[i][j] = turn;
  return {grid, true};
}

bool skip(grid grid, char turn) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto [_, ok] = put(grid, i, j, turn);
      if (ok) return false;
    }
  }
  return true;
}

pair<int, int> othello_ai(grid grid, char turn) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      auto [_, ok] = put(grid, i, j, turn);
      if (ok) {
        return {i, j};
      }
    }
  }
  return {-1, -1};
}

int main() {

  vector<vector<char>> grid(n, vector<char>(n, '.'));
  grid[4][4] = 'o';
  grid[3][3] = 'o';
  grid[3][4] = 'x';
  grid[4][3] = 'x';
  char turn = 'o';
  while (true) {
    if (skip(grid, 'o') and skip(grid, 'x')) {
      break;
    }
    if (skip(grid, turn)) {
      turn = next_turn(turn);
      continue;
    }
    print(grid);
    cout << "next turn is " << turn << endl;
    int i, j;
    if (turn == 'o') {
      tie(i, j) = read_input();
      if (i == -2 and j == -2) {
        turn = next_turn(turn);
        grid = pre_grid;
        continue;
      }
      // tie(i, j) = othello_ai(grid, turn);
    } else {
      tie(i, j) = read_input();
      if (i == -2 and j == -2) {
        turn = next_turn(turn);
        grid = pre_grid;
        continue;
      }
      // tie(i, j) = othello_ai(grid, turn);
      // if (i == -1) {
      //   exit(1);
      // }
    }
    auto [next_grid, ok] = put(grid, i, j, turn);
    if (!ok) {
      cout << "ダメな置き方です" << endl;
      continue;
    }
    // 行って前の情報を持っておく
    pre_grid = grid;
    grid = next_grid;
    turn = next_turn(turn);
  }
  print(grid);
  cout << "ゲーム終了" << endl;
  return 0;
}
