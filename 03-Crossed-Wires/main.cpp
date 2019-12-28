#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
  std::vector<std::string> tokens;
  size_t prev = 0, pos = 0;
  do {
    pos = str.find(delim, prev);
    if (pos == std::string::npos) {
      pos = str.length();
    }
    std::string token = str.substr(prev, pos-prev);

    if (!token.empty()) {
      tokens.push_back(token);
    }
    prev = pos + delim.length();

  } while (pos < str.length() && prev < str.length());

  return tokens;
}

struct Board {
  int central_port_position;
  std::vector<std::vector<int>> board;
};

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

void process_instructions(std::vector<std::string> instructions, std::shared_ptr<Board> board) {
  for (auto& ins : instructions) {
    /* const */ 
  }
}

int main() {
  const auto fdata = get_input_data();
  std::shared_ptr<Board> board(new Board);

  for (auto& instructions : fdata) {
    process_instructions(instructions);
  }

  return 0;
}
