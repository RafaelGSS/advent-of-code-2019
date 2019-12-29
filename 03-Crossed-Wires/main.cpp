#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <map>
#include <list>
#include <algorithm>
#include <stdlib.h>
#include <limits>

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

  bool operator==(Point& p) const {
    return p.m_x == m_x && p.m_y == m_y;
  }
  Point() {}
  Point(int x, int y): m_x(x), m_y(y) {}
  Point(Point& p): m_x(p.m_x), m_y(p.m_y) {}
  Point(Point* p): m_x(p->m_x), m_y(p->m_y) {}
};

typedef std::vector<Point*> Board;

class Day3 {
  public:
    Day3() {
      this->nearest_intersection = std::numeric_limits<int>::max();
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

    void find_intersec(Board& find_at_wire) {
      auto found = std::find_if(find_at_wire.begin(), find_at_wire.end(), [&](Point* p) {
          return p->m_x == this->current_point->m_x && p->m_y == this->current_point->m_y;
          }) != find_at_wire.end(); 

      if (found) {
        this->intersections.push_back(new Point(this->current_point));
        int manhattan_distance = abs(this->current_point->m_x) + abs(this->current_point->m_y);
        if (manhattan_distance < this->nearest_intersection) {
          this->nearest_intersection = manhattan_distance;
        }
      }
    }

    void walk_direction(const int& walks, int x_distance, int y_distance) {
      for (int i = 0; i < walks; i++) {
        this->current_point->m_x += x_distance;
        this->current_point->m_y += y_distance;

        if (this->wire_idx == 1) {
          this->find_intersec(this->wires[0]);
        }
        this->wires[this->wire_idx].push_back(new Point(this->current_point));
      }
    }

    void reset_current_point() {
      this->current_point = new Point(0, 0);
    }

    void process_instructions(std::vector<std::string> instructions) {
      for (auto& ins : instructions) {
        const char& dir = ins[0];
        const int& walks = std::stoi(ins.substr(1, ins.length()));
        switch (dir) {
          case 'U':
            walk_direction(walks, 0, 1);
            break;
          case 'L':
            walk_direction(walks, -1, 0);
            break;
          case 'D':
            walk_direction(walks, 0, -1);
            break;
          case 'R':
            walk_direction(walks, 1, 0);
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

    void set_wire_idx(unsigned short int idx) {
      this->wire_idx = idx;
    }

    Board get_wire(int idx) {
      return this->wires[idx];
    }

    Board intersections;
  private:
    std::vector<Board> wires {Board(), Board()};

    Point* current_point;
    int nearest_intersection;
    unsigned short int wire_idx;
};


int main() {
  Day3* day = new Day3();
  const auto fdata = day->get_input_data();
  unsigned short int wire_idx = 0;

  for (auto& instructions : fdata) {
    day->set_wire_idx(wire_idx);
    day->process_instructions(instructions);
    day->reset_current_point();
    wire_idx++;
  }

  auto wire1 = day->get_wire(0);
  auto wire2 = day->get_wire(1);

  int steps = std::numeric_limits<int>::max();
  for (Point* i : day->intersections) {
    int sequence = 0;
    for (Point* p : wire1) {
      sequence++;
      if (*p == *i) break;
    }

    for (Point* p : wire2) {
      sequence++;
      if (*p == *i) break;
    }

    if (sequence < steps) {
      steps = sequence;
    }
  }

  std::cout << "Done = " <<  day->get_nearest_intersection() << " Steps = " << steps << std::endl;
  return 0;
}
