//Version: 0.1.7
//Author: Marcus Persson
//Contributors: Jakob Pipping

#ifndef ANGLER_0_1_7
#error MechanicsEngine.cpp: Wrong version 0.1.7
#endif


#include <vector>
#include <glm\glm.hpp>

#include "Mechanics.h"

#include <Angler\Node.h>
#include <Angler\Transformation.h>
#include <Angler\CollisionNode.h>
#include <Angler\HelpFunctions.h>

using namespace Angler;
using namespace Angler::Mechanics;
using namespace Angler::Nodes;
using namespace Angler::HelpFunctions::Nodes;

MechanicsEngine::MechanicsEngine(Game *game)
	: mParent(game)
{

}

MechanicsEngine::~MechanicsEngine()
{

}

void MechanicsEngine::doCollide(Node *node)
{
	std::vector<Node*> nds = getDescendants(node);

	for(unsigned int i = 0; i < nds.size(); i++)
	{
		if (typeid(*nds[i]) == typeid(CollisionNode) && ((CollisionNode*)nds[i])->getType() == 0)
			for(unsigned int k = i+1; k < nds.size(); k++)
			{
				if (typeid(*nds[k]) == typeid(CollisionNode))
					if(((CollisionNode*)nds[i])->isColliding((CollisionNode*)nds[k]) == 1)
						mParent->throwEvent(Game::Events::Collide, nds[i], nds[k]);
			}
	}
}