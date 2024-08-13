#pragma once

#include <vector>
#include <string>

struct Terrain
{
	int rows = 0, cols = 0;

	std::vector<std::vector<int>> layers;

	void print() {
		printf("rows, cols : %d, %d\n", rows, cols);
		printf("vector cols size : %d\n", (int)layers.size());
		printf("vector rows size : %d\n", (int)layers.front().size());
		for (std::vector<int> row : layers)
		{
			for (int tile : row) {
				printf("%d, ", tile);
			}
			printf("\n");
		}
	}
};

struct TerrainData {
	std::string name;
	
	std::vector<std::unique_ptr<Terrain>> map;
	
	void print()
	{
		printf("name : %s\n", name.c_str());
		for (int i = 0; i < map.size(); i++) {
			map[i]->print();
		}
	}
};