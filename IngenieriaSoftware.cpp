// IngenieriaSoftware.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>


//void spawnEnemy(int* enemyList, int playerPosition, int size);
//void shoot(int playerPositon, bool direction);
int aliveEnemies(bool* enemies, int size);

int main()
{
	//init
	int playerPos = 25;
	bool playerDir = true;
	int mapSize = 90;
	char* map = new char[mapSize + 1];
	bool* enemies = new bool[mapSize];
	bool* enemiesBuffer = new bool[mapSize];
	int bulletPos = -1;
	bool bulletDir = true;

	int enemyCount = 0;
	bool running = true;

	//float lastTime = (float)clock() / CLOCKS_PER_SEC;
	//float deltaTime = 0.f;

	for (size_t i = 0; i < mapSize; i++)
	{
		map[i] = ' ';
		enemies[i] = false;
		enemiesBuffer[i] = false;
	}
	map[mapSize] = '\0';
	map[playerPos] = 'A';

	//update 
	while (running)
	{
		short uLeftKeyState = GetKeyState(VK_LEFT);
		short uRightKeyState = GetKeyState(VK_RIGHT);
		short uShootKeyState = GetKeyState(0x53);

		if ((uLeftKeyState & 0x8000) != 0)
		{
			playerDir = false;
			playerPos = (playerPos - 1 + mapSize) % mapSize;
		}
		if ((uRightKeyState & 0x8000) != 0)
		{
			playerDir = true;
			playerPos = (playerPos + 1) % mapSize;
		}
		if ((uShootKeyState & 0x8000) != 0)
		{
			if (bulletPos == -1)
			{
				bulletDir = playerDir;
				bulletPos = playerPos;
			}
		}

		if (aliveEnemies(enemies, mapSize) < 3)
		{
			enemies[(rand() % (mapSize - 40) + 20 + playerPos) % mapSize] = true;
		}

		if (bulletPos >= 0)
		{
			bulletDir ?
				bulletPos++ :
				bulletPos--;
			if (bulletPos < 0 || bulletPos >= mapSize)
			{
				bulletPos = -1;
			}

			if (enemies[bulletPos])
			{
				enemies[bulletPos] = false;
				bulletPos = -1;
				enemyCount++;
			}
		}

		for (size_t i = 0; i < mapSize; i++)
		{
			if (enemies[i])
			{
				if ((-1) >= (i - playerPos) && (i - playerPos) <= 1)
				{
					running = false;
					
				}
				else if (-1 >= (i - bulletPos) && (i - bulletPos) <= 1)
				{
					enemies[i] = false;
					bulletPos = -1;
					enemyCount++;
				}
				else if (i < playerPos)
				{
					enemiesBuffer[i + 1] = true;
				}
				else
				{
					enemiesBuffer[i - 1] = true;
				}
			}
		}
		for (size_t i = 0; i < mapSize; i++)
		{
			map[i] = ' ';
			enemies[i] = enemiesBuffer[i];
			if (enemies[i])
			{
				map[i] = 'E';
			}
			enemiesBuffer[i] = false;
		}
		if (bulletPos >= 0)	map[bulletPos] = 'o';
		running? map[playerPos] = 'A' :map[playerPos] = 'X';
		system("cls");
		printf("--|%s|--\n", map);
		printf("Puntos: %d", enemyCount);
		Sleep(17);
	}
}

int aliveEnemies(bool* enemies, int size)
{
	int count = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (enemies[i]) count++;
	}
	return count;
}
