#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//  no whitespace allowed
//  acc is an 8-bit unsigned char
//  ( - decrement acc
//  ) - increment acc
//  < - jump to start of line
//  > - jump to end of line
//  v - go down one line
//  ^ - go up one line
//  # - execute next command if acc is even
//  ~ - execute next command if acc greater than depth
//  ? - read single char input into acc
//  : - print acc
//  ; - clear acc
//  . - do nothing
//  x - halt execution

uint16_t clip(uint16_t val, size_t cap, bool skipFlag = false) {
  uint16_t res;
  res = val >= cap ? 0 : val < 0 ? cap - 1 : val;
  if (skipFlag) {
    ++res;
  }
  res = res >= cap ? 0 : res;
}

int main(int argc, char *argv[]) {
  // open file
  std::ifstream plungeFile;
  if (argc == 2) {
    plungeFile.open(argv[1]);
  } else {
    std::cerr << "No filename specified, exiting.";
    return 1;
  }
  if (!plungeFile.is_open()) {
    std::cerr << "Cannot open '" << argv[1] << "', exiting.";
    return 2;
  }

  // read file
  std::string line;
  std::vector<std::string> program;
  while (plungeFile >> line) {
    program.push_back(line);
  }

  unsigned char acc = 0b00000000;
  uint16_t depth = 0;
  uint16_t x = 0;
  bool skipFlag = false;

  // execute
  while (true) {
    depth = clip(depth, program.size());
    x = clip(x, program[depth].size(), skipFlag);
    skipFlag = false;

    unsigned char instr = program[depth][x];
    // std::cout << "Instr '" << instr << "' at [" << depth << "][" << x << "]\n";
    switch (instr) {
    case '(': {
      --acc;
      ++x;
      break;
    }
    case ')': {
      ++acc;
      ++x;
      break;
    }
    case '<': {
      x = 0;
      break;
    }
    case '>': {
      x = program[depth].size() - 1;
      break;
    }
    case 'v': {
      ++depth;
      break;
    }
    case '^': {
      --depth;
      break;
    }
    case '#': {
      skipFlag = acc % 2;
      ++x;
      break;
    }
    case '~': {
      skipFlag = acc <= depth;
      ++x;
      break;
    }
    case '?': {
      std::cout << "\n?: ... ";
      acc == std::getchar();
      ++x;
      break;
    }
    case ':': {
      std::cout << acc;
      ++x;
      break;
    }
    case ';': {
      acc = 0b00000000;
      ++x;
      break;
    }
    case '.': {
      ++x;
      break;
    }
    case 'x': {
      std::cout << "\nHalting execution.";
      plungeFile.close();
      return 0;
    }
    default: {
      std::cerr << "\nInvalid char encountered: '" << instr << "', exiting.";
      plungeFile.close();
      return 1;
    }
    }
  }
}
