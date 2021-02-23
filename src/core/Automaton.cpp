
// Avoid circular dependencies
#pragma once
#include "Automaton.h"
#include "./../include/raylib-cpp.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

void Automaton::setup()
{
	SetTargetFPS(11);

	this->grid = std::vector<std::vector<int>>(this->HEIGHT + 1);
	srand(time(0));
	for (int i = 0; i < this->HEIGHT; i++)
	{
		this->grid[i].resize(this->WIDTH + 1);
	}

	for (int i = 0; i < this->HEIGHT; i++)
	{
		for (int j = 0; j < this->WIDTH; j++)
		{
			grid[i][j] = (rand() % 3) + 1;
		}
	}
}

void Automaton::render()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	for (int i = 0; i < this->HEIGHT; i++)
	{
		for (int j = 0; j < this->WIDTH; j++)
		{
			if (grid[i][j] == Types::paper)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, CLITERAL(Color){255, 16, 88, 255});
			else if (grid[i][j] == Types::rock)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, CLITERAL(Color){130, 255, 111, 255});
			else if (grid[i][j] == Types::scissors)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, CLITERAL(Color){19, 141, 255, 255});
		}
	}
	EndDrawing();
}

void Automaton::processEvents()
{
	// There are no events to handle for now
}

void Automaton::update()
{
	for (int i = 0; i < this->HEIGHT; i++)
	{
		for (int j = 0; j < this->WIDTH; j++)
		{
			switch (this->grid[i][j])
			{
			case Types::rock:
				if (countNeighbors(i, j)[Types::paper] > 2)
					this->grid[i][j] = Types::paper;
				continue;
			case Types::paper:
				if (countNeighbors(i, j)[Types::scissors] > 2)
					this->grid[i][j] = Types::scissors;
				continue;
			case Types::scissors:
				if (countNeighbors(i, j)[Types::rock] > 2)
					this->grid[i][j] = Types::rock;
				continue;
			}
		}
	}
}

void Automaton::run()
{
	this->setup();
	countNeighbors(0, 0);
	while (!this->window->ShouldClose())
	{
		this->processEvents();
		this->update();
		this->render();
	}
}

std::vector<int> Automaton::countNeighbors(int x, int y)
{
	std::vector<int> out(4);

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (!(dx == 0 && dy == 0))
			{
				int cell = this->grid[(x + dx + this->WIDTH) % this->WIDTH][(y + dy + this->HEIGHT) % this->HEIGHT];
				if (cell > 3)
					continue;
				out[cell]++;
			}
		}
	}

	return out;
}