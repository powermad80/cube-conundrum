#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

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

Reveal parseGame(std::string line) {
  std::istringstream iss(line);
  std::string word;
  Reveal rev;
  while (iss >> word) {
    if (word == "Red") {
      iss >> rev.red;
    }
  }
}

std::vector<Game> getAllGames() {
  std::ifstream file("input.txt");
  std::string line;
  Game game;
  std::vector<Game> games;
  std::vector<Reveal> reveals;
  while (std::getline(file, line)) {
    game = parseGame(line);
    games.push_back(game);
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
