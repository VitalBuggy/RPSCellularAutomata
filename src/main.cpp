#include "stdio.h"
#include "core/Automaton.h"

int main()
{
    Automaton automaton(800, 600, 8, "RPS");
    automaton.run();
}