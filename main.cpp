#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Reveal {
  public:
    int red;
    int blue;
    int green;
};

class Game {
  public:
    int Id;
    std::vector<Reveal> reveals;
};

Reveal parseGame(std::string game) {
  std::istringstream iss(line);
  std::string word;
  Reveal rev;
  while (iss >> word) {
    if (word == "Red")
    {
      iss >> rev.Red;
    }
  }
}

Game getAllGames() {
  std::ifstream file("input.txt");
  std::string line;
  Reveal rev;
  while (std::getline(file, line)) {
    rev = parseGame(line);
  }
}

int main() {
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    return 0;
}
