#include "stdio.h"
#include "core/Automaton.h"

int main()
{
    Automaton automaton(800, 600, 8, "Bruh");
    automaton.run();
}