#pragma once

#include <string>
#include <memory>
#include <vector>

#include "Texture.h"

class Character
{
public:
	Character();

	void render();

	void updatePosition(int x, int y);

public:
	int m_health;

	int m_x, m_y;

	std::string m_name;

private:

	std::vector<std::unique_ptr<Texture>> p_animations;
};

