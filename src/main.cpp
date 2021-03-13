#include "stdio.h"
#include "core/Automaton.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

int main(int argc, char **args)
{
    Automaton automaton(600, 400, 8, "RPS");
    srand(time(0));

    automaton.run(rand());
}