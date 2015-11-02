#include "ObjectMap.h"

USING_NS_CC;

int ObjectMap::gameState = 0;

bool ObjectMap::hasElephant = false;

bool ObjectMap::ateElephant = false;

ObjectBase* ObjectMap::map[7][10];

ObjectMap::ObjectMap()
{

}
ObjectMap::~ObjectMap()
{

}

void ObjectMap::init()
{
	gameState = 0;
	hasElephant = false;
	ateElephant = false;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = nullptr;
		}
	}
}

void ObjectMap::doMove(int posX, int posY, int direction)
{
	if (map[posX][posY] == nullptr)return;
	else if (map[posX][posY]->getType() == objectTypeSnakeAttack)
	{
		switch (direction)
		{
		case 0:
			if (map[posX - 1][posY] == nullptr)
			{
				map[posX][posY]->setXY(posX - 1, posY);
				map[posX - 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (dealContact(map[posX][posY], map[posX - 1][posY]))
			{
				removeObject(posX - 1, posY, true);
				map[posX][posY]->setXY(posX - 1, posY);
				map[posX - 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			break;
		case 1:
			if (map[posX][posY + 1] == nullptr)
			{
				map[posX][posY]->setXY(map[posX][posY]->getX(), map[posX][posY]->getY() + 1);
				map[posX][posY + 1] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (dealContact(map[posX][posY], map[posX][posY + 1]))
			{
				removeObject(posX, posY + 1, true);
				map[posX][posY]->setXY(posX, posY + 1);
				map[posX][posY + 1] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			break;
		case 2:
			if (map[posX + 1][posY] == nullptr)
			{
				map[posX][posY]->setXY(map[posX][posY]->getX() + 1, map[posX][posY]->getY());
				map[posX + 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (dealContact(map[posX][posY], map[posX + 1][posY]))
			{
				removeObject(posX + 1, posY, true);
				map[posX][posY]->setXY(posX + 1, posY);
				map[posX + 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			break;
		case 3:
			if (map[posX][posY - 1] == nullptr)
			{
				map[posX][posY]->setXY(map[posX][posY]->getX(), map[posX][posY]->getY() - 1);
				map[posX][posY - 1] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (dealContact(map[posX][posY], map[posX][posY - 1]))
			{
				removeObject(posX, posY - 1, true);
				map[posX][posY]->setXY(posX, posY - 1);
				map[posX][posY - 1] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		if (direction&&posX >= 6)
		{
			removeObject(posX, posY);
			return;
		}
		else if (!direction&&posX <= 0)
		{
			removeObject(posX, posY);
			return;
		}

		switch (direction)
		{
		case 0:
			if (map[posX - 1][posY] == nullptr)
			{
				map[posX][posY]->setXY(posX - 1, posY);
				map[posX - 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (map[posX - 1][posY]->getType() == objectTypeSnakeAttack)
			{
				if (dealContact(map[posX - 1][posY], map[posX][posY]))
				{
					removeObject(posX, posY, true);
				}
			}
			break;
		case 2:
			if (map[posX + 1][posY] == nullptr)
			{
				map[posX][posY]->setXY(map[posX][posY]->getX() + 1, map[posX][posY]->getY());
				map[posX + 1][posY] = map[posX][posY];
				map[posX][posY] = nullptr;
			}
			else if (map[posX + 1][posY]->getType() == objectTypeSnakeAttack)
			{
				if (dealContact(map[posX + 1][posY], map[posX][posY]))
				{
					removeObject(posX, posY, true);
				}
			}
			break;
		default:
			break;
		}
	}
}

bool ObjectMap::dealContact(ObjectBase* snake, ObjectBase* obj)
{
	if (snake->getDefending() && (obj->getType() == objectTypeAnimalDefense || obj->getType() == objectTypeAnimalAttack))
	{
		if (obj->getAttack() > snake->getAttack() && obj->getType() != objectTypeAnimalDefense)
		{
			gameState = 105;
			return false;
		}
		else return true;
	}


	if (snake->getAttack() < obj->getAttack() || snake->getDefense() < obj->getDefense())
	{
		gameState = 105;
		return false;
	}
	else
	{
		if (obj->getType() == objectTypeElephant)
		{
			ateElephant = true;
		}
		else if (obj->getType() == objectTypeXiang1)
		{
			snake->setAttack(1);
		}
		else if (obj->getType() == objectTypeXiang2)
		{
			snake->setDefense(1);
		}
		else if (obj->getType() == objectTypeXiang3)
		{
			snake->setDefense(-1);
		}
		else if (obj->getType() == objectTypeXiang4)
		{
			if (ateElephant)
			{
				gameState = 55;
				return false;
			}
		}

		if (snake->getAttack() == obj->getAttack())
		{
			snake->setAttack(snake->getAttack() + 1);
		}
		if (snake->getDefense() == obj->getDefense())
		{
			snake->setDefense(snake->getDefense() + 1);
		}
	}

	return true;
}

bool ObjectMap::addObject(ObjectBase* obj)
{
	if (map[obj->getX()][obj->getY()] != nullptr)return false;
	else
	{
		map[obj->getX()][obj->getY()] = obj;
		if (obj->getType() < 5)gameState++;
		else if (obj->getType() == 8)hasElephant = true;
		return true;
	}
}

void ObjectMap::removeObject(int posX, int posY, bool eat)
{
	if (map[posX][posY]->getType() < 5)
	{
		if (eat)gameState ++;
		else gameState--;
	}
	else if (map[posX][posY]->getType() == 8)
	{
		hasElephant = false;
	}
	map[posX][posY]->removeFromParentAndCleanup(true);
	map[posX][posY] = nullptr;
}

void ObjectMap::step()
{
	if (gameState >= 50)return;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == nullptr)continue;
			map[i][j]->timer++;
			if (map[i][j]->timer >= 60)
			{
				map[i][j]->timer = 0;
				switch (map[i][j]->getType())
				{
				case objectTypeSnakeAttack:
					break;
				default:
					doMove(i, j, map[i][j]->getDirection() ? 2 : 0);
					break;
				}
			}
		}
	}
}