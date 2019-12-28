#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <map>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) {
      pos = str.length();
    }
    std::string token = str.substr(prev, pos - prev);

    if (!token.empty()) {
      tokens.push_back(token);
    }
    prev = pos + delim.length();

  } while (pos < str.length() && prev < str.length());

  return tokens;
}

typedef std::vector<std::vector<int>> Board;

std::vector<std::vector<std::string>> get_input_data() {
  std::fstream file;
  std::vector<std::vector<std::string>> fdata;
  const std::string delim = ",";

  file.open("./input.txt");
  if (file.is_open()) {
    std::string data;
    while(std::getline(file, data)) {
      fdata.push_back(split(data, delim));
    }
  }

  return fdata;
}

void walk_direction(Board& board, const int& walks, int xDir, int yDir) {
  int x = xDir;
  int y = yDir;
  for (int i = 0; i < walks; i++) {
    std::cout << "Trying [" << x << "," << y << "]" << std::endl;
    /* board[x][y]++; */
    x += xDir;
    y += yDir;
  }
}

void process_instructions(std::vector<std::string> instructions, Board& board) {
  for (auto& ins : instructions) {
    const char& dir = ins[0];
    const int& walks = std::stoi(ins.substr(1, ins.length()));
    switch (dir) {
      case 'U':
        walk_direction(board, walks, 1, 0);
        break;
      case 'L':
        walk_direction(board, walks, -1, 0);
        break;
      case 'D':
        walk_direction(board, walks, 0, -1);
        break;
      case 'R':
        walk_direction(board, walks, 0, 1);
        break;
      default:
        std::cout << "Invalid direction! Exiting..." << std::endl;
        exit(1);
    }
    std::cout << "Instruction is: " << dir <<  " - Walks: " << walks << std::endl;
  }
}

int main() {
  const auto fdata = get_input_data();
  Board board(100000);

  for (auto& instructions : fdata) {
    process_instructions(instructions, board);
    std::cout << "Done!" << std::endl;
    exit(0);
  }

  return 0;
}
