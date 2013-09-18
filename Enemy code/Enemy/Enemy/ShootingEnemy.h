#ifndef SHOOTINGENEMY_H
#define SHOOTINGENEMY_H

#include "Enemy.h"
#include <stdlib.h>

using namespace std;

class ShootingEnemy: public Enemy
{
public:
	ShootingEnemy(void);
	~ShootingEnemy(void);
	void Update(int p_posX, int p_posY);
	void Render();
private:
};

#endif

