#include "Walls.h"

Walls::Walls()
{
	m_window_w = 0;
	m_window_h = 0;
	m_tile_w = 0;
	m_tile_h = 0;
}

Walls::Walls(int window_w, int window_h, int tile_w, int tile_h, std::vector<std::vector<int>> locations)
{
	m_window_w = window_w;
	m_window_h = window_h;
	m_tile_w = tile_w;
	m_tile_h = tile_h;
	m_locations = locations;
	for (auto row : m_locations)
	{

	}
	
}

bool Walls::intersect(float x, float y)
{
	return true;
}