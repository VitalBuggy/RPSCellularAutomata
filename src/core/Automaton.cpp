
// Avoid circular dependencies
#ifndef GAME_H
#define GAME_H
#include "Automaton.h"
#include "./../include/raylib-cpp.hpp"
#include <string>
#include <iostream>
#include <cstdlib>

Automaton::Automaton(int height, int width, int pixel_size, std::string window_name = "Cellular Automaton")
{
	this->HEIGHT = height / pixel_size;
	this->WIDTH = width / pixel_size;
	this->pixel_size = pixel_size;
	this->WINDOW_NAME = window_name;
	this->window = new raylib::Window(height, width, this->WINDOW_NAME);
}

void Automaton::setup()
{
	SetTargetFPS(15);

	this->grid = std::vector<std::vector<int>>(this->HEIGHT);
	srand(time(0));
	for (int i = 0; i < this->HEIGHT; i++)
	{
		this->grid[i].resize(this->WIDTH);
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

	for (int i = 0; i < this->HEIGHT - 1; i++)
	{
		for (int j = 0; j < this->WIDTH - 1; j++)
		{
			if (grid[i][j] == Types::paper)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, RED);
			else if (grid[i][j] == Types::rock)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, GREEN);
			else if (grid[i][j] == Types::scissors)
				DrawRectangle(i * this->pixel_size, j * this->pixel_size, this->pixel_size, this->pixel_size, BLUE);
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
	for (int i = 0; i < this->HEIGHT - 1; i++)
	{
		for (int j = 0; j < this->WIDTH - 1; j++)
		{
			switch (this->grid[i][j])
			{
			case Types::rock:
				if (countNeighbors(i, j)[2] > 2)
					this->grid[i][j] = Types::paper;
				continue;
			case Types::paper:
				if (countNeighbors(i, j)[3] > 2)
					this->grid[i][j] = Types::scissors;
				continue;
			case Types::scissors:
				if (countNeighbors(i, j)[1] > 2)
					this->grid[i][j] = Types::rock;
				continue;
			default:
			{
			}
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
				out[cell]++;
			}
		}
	}

	return out;
}

#endif
