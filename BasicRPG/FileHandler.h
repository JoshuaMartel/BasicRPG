#pragma once

#include <fstream>
#include <filesystem>

#include "TerrainData.h"

namespace file {
	const std::string MAP_PATH = "maps/";

	void saveMap(TerrainData* info);

	void loadMap(std::string file_path, TerrainData* data);

}