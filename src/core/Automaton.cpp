
// Avoid circular dependencies
#pragma once
#include "Automaton.h"
#include "./../include/raylib-cpp.hpp"

void Automaton::setup(int seed) {
  // Set the Target Frame rate to the defined value
  SetTargetFPS(10);

  // Generate a new grid with random values in the form of a 2D vector
  this->grid = std::vector<std::vector<int>>(this->HEIGHT + 1);
  this->grid_tmp = std::vector<std::vector<int>>(this->HEIGHT + 1);
  srand(seed);
  for (int i = 0; i < this->HEIGHT; i++) {
    this->grid[i].resize(this->WIDTH + 1);
    this->grid_tmp[i].resize(this->WIDTH + 1);
  }

  for (int i = 0; i < this->HEIGHT; i++)
    for (int j = 0; j < this->WIDTH; j++)
      this->grid[i][j] = (rand() % 3) + 1;
}

// Render method: renders the values in the grid
void Automaton::render() {
  BeginDrawing();

  ClearBackground(RAYWHITE);

  for (int i = 0; i < this->HEIGHT; i++)
    for (int j = 0; j < this->WIDTH; j++)
      if (grid[i][j] == Types::paper)
        DrawRectangle(i * this->pixel_size, j * this->pixel_size,
                      this->pixel_size, this->pixel_size,
                      CLITERAL(Color){184, 71, 80, 255});
      else if (grid[i][j] == Types::rock)
        DrawRectangle(i * this->pixel_size, j * this->pixel_size,
                      this->pixel_size, this->pixel_size,
                      CLITERAL(Color){163, 48, 207, 255});
      else if (grid[i][j] == Types::scissors)
        DrawRectangle(i * this->pixel_size, j * this->pixel_size,
                      this->pixel_size, this->pixel_size,
                      CLITERAL(Color){104, 166, 89, 255});
  EndDrawing();
}

void Automaton::processEvents() {
  // TODO
}

// Check neighbors around each cell and update accordingly
void Automaton::update() {
  // copy current grid into a temporary one
  for (int i = 0; i < this->HEIGHT; i++)
    for (int j = 0; j < this->WIDTH; j++)
      grid_tmp[i][j] = grid[i][j];

  for (int i = 0; i < this->HEIGHT; i++)
    for (int j = 0; j < this->WIDTH; j++)
      switch (this->grid[i][j]) {
      case Types::rock:
        if (countNeighbors(i, j)[Types::paper] > 2)
          this->grid_tmp[i][j] = Types::paper;
        continue;
      case Types::paper:
        if (countNeighbors(i, j)[Types::scissors] > 2)
          this->grid_tmp[i][j] = Types::scissors;
        continue;
      case Types::scissors:
        if (countNeighbors(i, j)[Types::rock] > 2)
          this->grid_tmp[i][j] = Types::rock;
        continue;
      }

  // Copy the new grid to the origial, the one to be rendered
  for (int i = 0; i < this->HEIGHT; i++)
    for (int j = 0; j < this->WIDTH; j++)
      grid[i][j] = grid_tmp[i][j];
}

// Main loop
void Automaton::run(int seed = time(0)) {
  this->setup(seed);
  countNeighbors(0, 0);
  while (!this->window->ShouldClose()) {
    this->processEvents();
    this->update();
    this->render();
  }
}

// Function to count the neighbors around a cell and return a vector with the
// array indexes corresponding to the type of cell and the value being the
// amount of said cell
std::vector<int> Automaton::countNeighbors(int x, int y) {
  std::vector<int> out(4);

  for (int dx = -1; dx <= 1; dx++)
    for (int dy = -1; dy <= 1; dy++)
      if (!(dx == 0 && dy == 0)) {
        unsigned int cell = this->grid[(x + dx + this->WIDTH) % this->WIDTH]
                                      [(y + dy + this->HEIGHT) % this->HEIGHT];
        if (cell > 3)
          continue;
        out[cell]++;
      }

  return out;
}
