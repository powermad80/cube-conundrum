#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Reveal {
public:
  int red = 0;
  int blue = 0;
  int green = 0;
};

class Game {
public:
  int Id;
  std::vector<Reveal> reveals;
};

static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> substrings;
  std::string substring;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, substring, delimiter)) {
    substrings.push_back(substring);
  }
  return substrings;
}

int getGameId(std::string line) {
  std::vector<std::string> partedLine = split(line, ' ');
  std::string idString = partedLine[1];
  trim(idString);
  return stoi(idString);
}

Reveal parseRevealString(std::string line) {
  trim(line);
  std::vector<std::string> partedLine = split(line, ' ');
  int dice;
  char color;
  Reveal reveal;
  for (int i = 0; i < partedLine.size(); i = i + 2) {
    dice = stoi(partedLine[i]);
    color = partedLine[i + 1][0];
    if (color == 'r') {
      reveal.red = dice;
    } else if (color == 'g') {
      reveal.green = dice;
    } else if (color == 'b') {
      reveal.blue = dice;
    }
  }
  return reveal;
}

std::vector<Reveal> getGameReveals(std::string line) {
  std::vector<Reveal> reveals;
  Reveal reveal;
  std::string gameReveals = line;
  trim(gameReveals);
  std::vector<std::string> revealsString = split(gameReveals, ';');
  for (int i = 0; i < revealsString.size(); i++) {
    reveal = parseRevealString(revealsString[i]);
    reveals.push_back(reveal);
  }
  return reveals;
}

Game parseGame(std::string line) {
  std::vector<std::string> partedLine = split(line, ':');
  std::string gameIdString = partedLine[0];
  std::string revealsString = partedLine[1];
  Game game;
  game.Id = getGameId(gameIdString);
  game.reveals = getGameReveals(revealsString);
  return game;
}

std::vector<Game> getAllGames() {
  std::ifstream file("input.txt");
  std::string line;
  Game game;
  std::vector<Game> games;
  while (std::getline(file, line)) {
    game = parseGame(line);
    games.push_back(game);
  }
  return games;
}

bool isGamePossible(Game game) {
  // Set dice limits here
  int maxRed = 12;
  int maxGreen = 13;
  int maxBlue = 14;
  Reveal rev;
  for (int i = 0; i < game.reveals.size(); i++) {
    rev = game.reveals[i];
    if ((rev.red > maxRed) || (rev.blue > maxBlue) || (rev.green > maxGreen)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector games = getAllGames();
  Game game;
  int total = 0;
  for (int i = 0; i < games.size(); i++) {
    game = games[i];
    if (isGamePossible(game)) {
      total += game.Id;
    }
  }
  std::cout << total << "\n";
  return total;
}
