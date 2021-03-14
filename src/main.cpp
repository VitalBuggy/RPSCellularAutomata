#include "stdio.h"
#include "core/Automaton.h"
#include <cstring>

int main(int argc, char **args)
{
    Automaton automaton(600, 400, 8, "RPS");
    srand(time(0));

    (argc < 2 ? automaton.run(rand()) : automaton.run(atoi(args[1])));
}
