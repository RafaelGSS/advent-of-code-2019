#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <list>
#include <algorithm>
#include <stdlib.h>


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

struct Point {
  int m_x;
  int m_y;

  Point() {}
  Point(int x, int y): m_x(x), m_y(y) {}
  Point(Point& p): m_x(p.m_x), m_y(p.m_y) {}
  Point(Point* p): m_x(p->m_x), m_y(p->m_y) {}
};

typedef std::list<Point*> Board;

class Day3 {
  public:
    Day3() {
      this->nearest_intersection = -1;
      this->current_point = new Point(0, 0);
    }

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

    void walk_direction(const int& walks, int x_distance, int y_distance) {
      for (int i = 0; i < walks; i++) {
        this->current_point->m_x += x_distance;
        this->current_point->m_y += y_distance;
        // slow!
        auto found = std::find_if(this->board.begin(), this->board.end(), [&](Point* p) {
            return p->m_x == this->current_point->m_x && p->m_y == this->current_point->m_y;
            });

        if (found != this->board.end()) {
          int manhattan_distance = abs(this->current_point->m_x) + abs(this->current_point->m_y);
          if (manhattan_distance < this->nearest_intersection) {
            this->nearest_intersection = manhattan_distance;
          }
        } else {
          this->board.push_back(new Point(this->current_point));
        }

      }
    }

    void process_instructions(std::vector<std::string> instructions) {
      for (auto& ins : instructions) {
        const char& dir = ins[0];
        const int& walks = std::stoi(ins.substr(1, ins.length()));
        switch (dir) {
          case 'U':
            walk_direction(walks, 1, 0);
            break;
          case 'L':
            walk_direction(walks, -1, 0);
            break;
          case 'D':
            walk_direction(walks, 0, -1);
            break;
          case 'R':
            walk_direction(walks, 0, 1);
            break;
          default:
            std::cout << "Invalid direction! Exiting..." << std::endl;
            exit(1);
        }
      }
    }

    int get_nearest_intersection() {
      return this->nearest_intersection;
    }
  private:
    Board board;
    Point* current_point;
    int nearest_intersection;
};


int main() {
  Day3* day = new Day3();
  const auto fdata = day->get_input_data();

  for (auto& instructions : fdata) {
    day->process_instructions(instructions);
    std::cout << "Done = " <<  day->get_nearest_intersection() << std::endl;
    exit(0);
  }

  return 0;
}
