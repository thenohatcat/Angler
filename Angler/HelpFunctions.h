//Version: 0.1.1
//Author: Jakob Pipping
//Contributors:

#ifndef INC_HELPFUNCTIONS_H
#define INC_HELPFUNCTIONS_H

#ifdef ANGLER_0_1_1

#include <SFML\System\Vector2.hpp>
#include <glm\mat4x4.hpp>

namespace Angler
{
	namespace HelpFunctions
	{
		template <class T, class U>
		bool isDerivedFrom(U* p)
		{
			return (dynamic_cast<T*>(p) == p);
		}

		sf::Vector2f transform(double *matrix, sf::Vector2f vIn)
		{
			glm::mat2 m(
				matrix[0], matrix[1],
				matrix[4], matrix[5]);
	
			glm::vec2 v = glm::vec2(vIn.x, vIn.y) * m + glm::vec2(matrix[12], matrix[13]);
			return sf::Vector2f(v.x, v.y);
		}
	}
}

#else
#error HelpFunctions.h: Wrong Version 0.1.1
#endif

#endif