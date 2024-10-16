#include "FileHandler.h"

#include <iostream>

void file::saveMap(TerrainData* info)
{
	//Test for directory to save maps
	struct stat meta;
	if (stat(MAP_PATH.c_str(), &meta) != 0)
	{
		printf(("Directory ./" + MAP_PATH + ", does not exist. Creating directory... ").c_str());
		std::filesystem::create_directories("./" + MAP_PATH);
	}

	std::string file_path = MAP_PATH + info->name;
	std::ofstream file(file_path);

	if (file.is_open())
	{
		file << "$ layers" << std::endl;
		file << info->map.size() << std::endl;
		for (auto&& t : info->map)
		{
			file << t->sheet_name << std::endl;
			file << "$ dimensions" << std::endl;
			file <<t->rows << ", " << t->cols << std::endl;
			
			for (std::vector<int> row : t->layers) {
				for (int tile : row) {
					file << tile << ", ";
				}
				file << std::endl;
			}
		}
		
		file.close();
	}
	else {
		file.close();
		throw "Could not open file " + file_path;
	}
}

void file::loadMap(std::string file_path, TerrainData* data)
{
	std::string line;
	std::string row;
	std::vector<std::string> input;
	std::ifstream file(file_path);

	if (file.is_open())
	{
		// Retrieve lines from text file
		while (std::getline(file, line))
		{
			// Skip lines starting with $
			if (line.substr(0,1) == "$")
				continue;
			input.emplace_back(line);
			//printf((line + "\n").c_str());
		}
		file.close();

		// Process strings input MapInfo data
		std::string delimeter = ",";
		size_t pos = 0;

		if(input.size() == 0)
			throw "Error: file " + file_path + " is empty";
		auto iter = input.begin();
	
		int num_layers = std::stoi(*iter++);

		pos = iter->find(delimeter);
		for (int i = 0; i < num_layers; i++)
		{

			
			if (iter == input.end()) break;
			data->map.emplace_back(std::make_unique<Terrain>());

			data->map.back()->sheet_name = *iter;
			iter++;
			data->map.back()->rows = std::stoi(iter->substr(0, pos));
			data->map.back()->cols = std::stoi(iter->substr(pos + delimeter.length(), std::string::npos));
			
			// Load tile map
			for (int j = 0; j < data->map.back()->rows; j++)
			{
				iter++;
				std::vector<int> vec;
				row = *iter;

				while ((pos = row.find(delimeter)) != std::string::npos)
				{
					vec.emplace_back(std::stoi(row.substr(0, pos)));
					row.erase(0, pos + delimeter.length());
				}

				data->map.back()->layers.emplace_back(vec);
			}
			iter++;
		}
		printf("Finished printing lines.\n");
	}
	else {
		file.close();
		throw "Could not open file " + file_path;
	}
}

void file::loadMap(std::string file_path, std::unique_ptr<TerrainData>* data)
{
	std::string line;
	std::string r;
	std::vector<std::string> input;
	std::ifstream file(file_path);
	size_t pos = 0;
	int rows = 0, cols = 0;

	if (file.is_open())
	{
		//Retrieve level name
		(*data)->name = file_path;

		// Retrieve lines from text file
		while (std::getline(file, line))
		{
			// Skip lines starting with $
			if (line.substr(0, 1) == "$") continue;
			input.emplace_back(line);
			//printf((line + "\n").c_str());
		}
		file.close();

		// Process strings input MapInfo data

		if (input.size() == 0)
			throw "Error: file " + file_path + " is empty";

		auto iter = input.begin();
		int num_layers = std::stoi(*iter++);
		std::string delimeter (",");

		for (int i = 0; i < num_layers; i++)
		{
			//printf("i is %d\n", i);
			if (iter == input.end()) break;

			(*data)->map.emplace_back(std::make_unique<Terrain>());
			(*data)->map.back()->sheet_name = *iter;
			iter++;
			//printf("Scanned sheet name\n");
			rows = std::stoi(*iter);
			(*data)->map.back()->rows = rows;
			iter++;
			//printf("Scanned rows\n");
			// Load each layer of the tile map
			for (int j = 0; j < rows; j++)
			{
				//printf("j is %d\n", j);
				std::vector<int> vec;
				r = *iter;

				while ((pos = r.find(delimeter)) != std::string::npos)
				{
					vec.emplace_back(std::stoi(r.substr(0, pos)));
					r.erase(0, pos + delimeter.length());
				}

				(*data)->map.back()->layers.emplace_back(vec);
				iter++;
			}
			cols = (*data)->map.back()->layers.back().size();
			(*data)->map.back()->cols = cols;
			(*data)->map_size = rows * cols;

			printf("rows: %d, ", rows);
			printf("cols: %d\n", cols);
			printf("map size: %d\n", (*data)->map_size);
		}

		if (iter == input.end())
			throw "Error: file " + file_path + " is missing wall logic grid";

		// Load the wall logic grid
		for (int j = 0; j < rows; j++)
		{
			std::vector<int> vec;
			r = *iter;

			while ((pos = r.find(delimeter)) != std::string::npos)
			{
				vec.emplace_back(std::stoi(r.substr(0, pos)));
				r.erase(0, pos + delimeter.length());
			}

			(*data)->wall_grid.emplace_back(vec);
			iter++;
		}
		(*data)->rows = rows;
		(*data)->cols = cols;
		printf("Finished printing lines.\n");
	}
	else {
		file.close();
		throw "Could not open file " + file_path;
	}
}