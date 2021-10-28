#include "core/Automaton.h"
#include "stdio.h"
#include <cstring>

int main(int argc, char **args) {
  Automaton automaton(1920, 1080, 8, "RPS");
  srand(time(0));

  (argc < 2 ? automaton.run(rand()) : automaton.run(atoi(args[1])));
}
