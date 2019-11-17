//Enemy

class Enemy:public Character{
	private:
		int enemyX;
		int enemyY;
		int cropX;
		int ctrAI;
	public:
		Enemy();
		SDL_Surface *enemy = NULL;
		SDL_Rect enemyBox;
		SDL_Rect cropE;
		void setEnemyX(int a){enemyX = a;}
		void setEnemyY(int b){enemyY = b;}
		void setcropX(int c){cropX = c;}
		void setCtrAI(int d){ctrAI = d;}
		int getEnemyX(){return enemyX;}
		int getEnemyY(){return enemyY;}
		int getCropX(){return cropX;}
		int getCtrAI(){return ctrAI;}
		
		void moveLeft();
		void moveRight();
		void moveDown();
		void shoot();
		void cropSprites();
		void spawn(SDL_Surface *&screen);
		int randomAI();
		void printBullet(SDL_Surface *&bulletsEnemy, SDL_Surface *&screen, int w);
				
};

Enemy::Enemy()
{
	int t = rand()%400+100;
	int y = rand()%150+75 ; 
	//enemyX = t;
	//enemyY = y;
	enemyBox.x = t;
	enemyBox.y = y;
	enemyBox.w = 64;
	enemyBox.h = 32;
	cropX = 0;
	enemy = IMG_Load("./images/enemy.png");
}

void Enemy::cropSprites()
{
	cropE.x = cropX; 
	cropE.y = 0;
	cropE.w = 64;
	cropE.h = 32;
	
}

void Enemy::spawn(SDL_Surface *&screen)
{
	this->cropSprites();
	apply_cropped_surface(enemyBox.x, enemyBox.y, cropE.x, cropE.y, cropE.w, cropE.h, enemy, screen);
}

void Enemy::moveLeft()
{
	if(enemyBox.x > 40) enemyBox.x = enemyBox.x - 20;
	else moveRight();
}

void Enemy::moveRight()
{
	if(enemyBox.x < 560) enemyBox.x = enemyBox.x + 20;
	else moveLeft();
}

void Enemy::moveDown()
{
	enemyBox.y = enemyBox.y + 20;
}

void Enemy::shoot()
{
	bulletE[ctrEnemy] = new Bullets();
	bulletE[ctrEnemy]->bulletBoxE.x = enemyBox.x+32;
	bulletE[ctrEnemy]->bulletBoxE.y = enemyBox.y+30;
	ctrEnemy++;	
}

int Enemy::randomAI()
{
	if(ctrAI % 20 == 0)
	{
		int x = rand()%20+1;
		
		if(x == 1 || x == 2 || x == 3 || x == 4 || x == 5) moveLeft();
		if(x == 6 || x == 7 || x == 8 || x == 9 || x == 10) moveRight();
		if(x == 11 || x == 12 || x == 13 || x == 14 || x == 15) shoot(); 
		if(x == 16 || x == 17 || x == 18 || x == 19 || x == 20) moveDown();
		return x;
	}
	
}

void Enemy::printBullet(SDL_Surface *&bulletsEnemy, SDL_Surface *&screen, int w)
{
	//for(int w = 0; w < ctrEnemy; w++)
	//{
		//SDL_Rect bullE;
		//bullE.x = bulletE[w]->bulletBox.x;
		//bullE.y = bulletE[w]->bulletBox.y;
		bulletE[w]->bulletBoxE.y = bulletE[w]->bulletBoxE.y+5;
		apply_surface(bulletE[w]->bulletBoxE.x, bulletE[w]->bulletBoxE.y, bulletsEnemy, screen);
		//SDL_Delay(1000);
		if(bulletE[w]->bulletBoxE.y > 650)
		{
			for(int q = w; q < ctrEnemy; q++)
			{
			bulletE[q] = bulletE[q+1];
			}
			delete[] bulletE[ctrEnemy];
			ctrEnemy--; 
		}	
		
	//}	
}


