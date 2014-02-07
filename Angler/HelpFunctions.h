//Version: 0.1.4
//Author: Jakob Pipping
//Contributors:

#ifndef INC_HELPFUNCTIONS_H
#define INC_HELPFUNCTIONS_H

#ifdef ANGLER_0_1_4

#include <SFML\System\Vector2.hpp>
#include <glm\mat4x4.hpp>
#include <vector>

namespace Angler
{
	namespace HelpFunctions
	{
		//Determines if a certain class is derived from another
		template <class T, class U>
		static bool isDerivedFrom(U* p)
		{
			return (dynamic_cast<T*>(p) == p);
		}

		static std::vector<Node*> getAnscestors(Node *node)
		{
			std::vector<Node*> ntr;
			while (node != nullptr)
			{
				if (Angler::HelpFunctions::isDerivedFrom<Angler::Nodes::Transformation>(node))
					ntr.push_back((Angler::Nodes::Transformation*)node);

				node = node->getParent();
			}

			return ntr;
		}

		//Returns all nodes that descend from this, in a depth first manner
		static std::vector<Node*> getDescendants(Node *node)
		{
			std::vector<Angler::Node*> nds;

			std::vector<Angler::Node*> nxt;
			nxt.push_back(node);

			Angler::Node *n;
			while (nxt.size() > 0)
			{
				n = nxt.back();
				nxt.pop_back();

				nds.push_back(n);

				std::vector<Angler::Node*> v = n->getChildren();
				for (int i = 0; i < v.size(); i++)
				{
					nxt.push_back(v.at(v.size() - 1 - i));
				}
			}

			return nds;
		}

		namespace Geometry
		{
			//Transforms a vector with a matrix
			static sf::Vector2f transform(double *matrix, sf::Vector2f vIn)
			{
				glm::mat2 m(
					matrix[0], matrix[4],
					matrix[1], matrix[5]);
	
				glm::vec2 v = glm::vec2(vIn.x, vIn.y) * m + glm::vec2(matrix[12], matrix[13]);
				return sf::Vector2f(v.x, v.y);
			}

			//Much of this will probably be moved to a dedicated Polygon class at a later time

			//Gets the "bounding box" corners ("upper left" and "lower right") of a series of points
			static void getBoundingPoints(std::vector<sf::Vector2f> *p, sf::Vector2f *ul, sf::Vector2f *lr)
			{
				float leb(p->at(0).x), ub(p->at(0).y), rb(p->at(0).x), lob(p->at(0).y);

				for (int i = 0; i < p->size(); i++)
				{
					sf::Vector2f v = p->at(i);
					if (v.x < leb)
						leb = v.x;
					if (v.y < ub)
						ub = v.y;
					if (v.x > rb)
						rb = v.x;
					if (v.y > lob)
						lob = v.y;
				}

				ul->x = leb; ul->y = ub;
				lr->x = rb; lr->y = lob;
			}

			//Determines the "sideness" of a point in relation to a line a->b, uses a normal that is to the "left"
			static int side(sf::Vector2f a, sf::Vector2f b, sf::Vector2f c)
			{
				float adb = 
					((c.x-a.x)*(b.x-a.x) + (c.y-a.y)*(b.y-a.y)) /
					((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
				float v = 
					((c.x-a.x) - adb * (b.x-a.x)) * (b.y-a.y) + 
					((c.y-a.y) - adb * (b.y-a.y)) * (a.x-b.x);
				if (v == 0)
					return 0;
				else
					return (int)(v / abs(v));
			}

			//Determines if a point lies "between" the end points of a line. Betweenness is determined by the projection of the vector a1b on the vector a1a2
			static int pointBetween(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b)
			{
				float a1b_dot_a1a2 = 
					((b.x-a1.x) * (a2.x-a1.x) + (b.y-a1.y) * (a2.y-a1.y)) / 
					((a2.x-a1.x) * (a2.x-a1.x) + (a2.y-a1.y) * (a2.y-a1.y));
				if (a1b_dot_a1a2 < 0)			//B < A1
					return -2;
				else if (a1b_dot_a1a2 == 0)		//B = A1
					return -1;
				else if (a1b_dot_a1a2 == 1)		//B = A2
					return 1;
				else if (a1b_dot_a1a2 > 1)		//B > A2
					return 2;
				else							//A1<B<A2
					return 0;
			}

			//Determines if a point p is within the polygon
			static bool pointIsWithinPolygon(std::vector<sf::Vector2f> *polygon, sf::Vector2f p)
			{
				for (int i = 0; i < polygon->size(); i++)
				{
					if (side(polygon->at(i), polygon->at((i + 1) % polygon->size()), p) < 0)
					{
						return false;
					}
				}
				return true;
			}

			//Determines if two finite lines cross
			static int lineCrosses(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2)
			{
				int 
					side1 = side(a1, a2, b1),
					side2 = side(a1, a2, b2);
				int 
					between1 = pointBetween(a1, a2, b1),
					between2 = pointBetween(a1, a2, b2);

				if ((between1 == 2 && between2 == 2) ||
					(between1 == -2 && between2 == -2))
					return 0;
				else if (
					((between1 == -1 && between2 == -2) || (between1 == 1 && between2 == 2)) ||
					((between1 == -2 && between2 == -1) || (between1 == 2 && between2 == 1)))
					return 0;
				else if (side1 == side2 && side1 != 0)
					return 0;
				else if (side1 == side2 && side1 == 0)
				{
					if ((between1 == -1 || between1 == 1 || between1 == 0) &&
						(between2 == -1 || between2 == 1 || between2 == 0))
					{
						return 2;
					}
				}
				else if (side1 != side2)
				{
					if ((between1 == -1 || between1 == 1 || between1 == 0) &&
						(between2 == -1 || between2 == 1 || between2 == 0))
					{
						return 1;
					}
					else
					{
						int 
							side1 = side(b1, a1, b2),
							side2 = side(a2, b1, b2);

						if (side1 != -1 && side2 != -1)
							return 1;
						else
							return 0;
					}
				}

				return 3;
			}

			//Determines if two polygon intersects
			static bool polygonIntersects(std::vector<sf::Vector2f> *pA, std::vector<sf::Vector2f> *pB)
			{
				for (int i = 0; i < pB->size(); i++)
				{
					if (pointIsWithinPolygon(pA, pB->at(i)))
						return true;
				}
				for (int i = 0; i < pA->size(); i++)
				{
					if (pointIsWithinPolygon(pB, pA->at(i)))
						return true;
				}
				for (int i = 0; i < pA->size(); i++)
				{
					for (int k = 0; k < pB->size(); k++)
					{
						int cr = lineCrosses(pA->at(i), pA->at((i+1) % pA->size()), pB->at(k), pB->at((k+1) % pB->size())); 

						if (cr == 1)
							return true;
					}
				}
				return false;
			}
		}
	}
}

#else
#error HelpFunctions.h: Wrong Version 0.1.4
#endif

#endif