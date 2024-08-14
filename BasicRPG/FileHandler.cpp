#include "FileHandler.h"

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
			printf((line + "\n").c_str());
		}
		file.close();

		// Process strings input MapInfo data
		std::string delimeter = ",";
		size_t pos = 0;

		if(input.size() == 0)
			throw "Error: file " + file_path + " is empty";
		auto iter = input.begin();
		//printf("Printing lines...\n");
		//printf(iter->c_str());
		//printf("\n");
		int num_layers = std::stoi(*iter++);

		pos = iter->find(delimeter);
		for (int i = 0; i < num_layers; i++)
		{
			//printf(iter->c_str());
			//printf("\n");
			
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
				//printf(r.c_str());
				//printf("\n");
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