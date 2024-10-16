#pragma once
#include <vector>
#include <algorithm>

class Walls
{
public:
	Walls();

	Walls(int window_w, int window_h, int tile_w, int tile_h, std::vector<std::vector<int>> locations);

	bool intersect(float x, float y);

public:
	int m_tile_w, m_tile_h;

	int m_window_w, m_window_h;

	// 0 means no wall. 1 means wall
	std::vector<std::vector<int>> m_locations;
};

