#include "./../include/raylib-cpp.hpp"
#include <vector>
#include <string>

class Automaton
{
private:
	void update();
	void render();
	void processEvents();
	void setup();
	std::vector<int> countNeighbors(int x, int y); // return an array where the index corresponds to the type of the cell and the value is the amount of them. 0: rock 1: paper 2: scissors

public:
	Automaton(int height, int width, int pixel_size, std::string window_name);
	void run();

private:
	int HEIGHT;
	int WIDTH;
	int pixel_size;
	raylib::Window *window;
	std::string WINDOW_NAME;
	std::vector<std::vector<int>> grid;

	enum Types
	{
		rock = 1,
		paper = 2,
		scissors = 3
	};
};