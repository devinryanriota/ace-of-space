//boss

class Boss:public Character{
	private:
		int bossX;
		int bossY;
		int cropX;
		int life;
		int ctrRandom;
	public:
		Boss();
		SDL_Surface *boss = NULL;
		SDL_Rect bossBox;
		SDL_Rect cropB;
		
		void setBossX(int a){bossX = a;}
		void setBossY(int b){bossY = b;}
		void setCropX(int c){cropX = c;}
		void setLife(int d){life = d;}
		void setCtrRandom(int e){ctrRandom = e;}
		
		int getBossX(){return bossX;}
		int getBossY(){return bossY;}
		int getCropX(){return cropX;}
		int getLife(){return life;}
		int getCtrRandom(){return ctrRandom;}
		
		void cropSprites();
		void spawn(SDL_Surface *&screen);
		void moveLeft();
		void moveRight();
		void shoot();
		void printBullet(SDL_Surface *&bulletsBoss, SDL_Surface *&screen);
		int randomAI();
		bool bossDead();
				
};

Boss::Boss()
{
	int a = rand() % 400 + 100;
	bossX = a;
	bossY = 0;
	cropX = 0;
	life = 6;
	bossBox.x = a;
	bossBox.y = 0;
	bossBox.w = 122;
	bossBox.h = 128;
	boss = IMG_Load("./images/boss.png");
}

void Boss::cropSprites()
{
	cropB.x = cropX;
	cropB.y = 0;
	cropB.w = 122;
	cropB.h = 128;
}

void Boss::spawn(SDL_Surface *&screen)
{
	this->cropSprites();
	apply_cropped_surface(bossBox.x, bossBox.y, cropB.x, cropB.y, cropB.w, cropB.h, boss, screen);
}

void Boss::moveLeft()
{
	if(bossBox.x >=250) bossBox.x = bossBox.x - 30;
	else moveRight();
}

void Boss::moveRight()
{
	if(bossBox.x <=500) bossBox.x = bossBox.x + 30;
	else moveLeft();
}

void Boss::shoot()
{
	bulletB[ctrBoss] = new Bullets();
	bulletB[ctrBoss]->bulletBoxB.x = bossBox.x+32;
	bulletB[ctrBoss]->bulletBoxB.y = bossBox.y+128;
	ctrBoss++;	
}

void Boss::printBullet(SDL_Surface *&bulletsEnemy, SDL_Surface *&screen)
{
	for(int i = 0; i < ctrBoss; i++)
    {
		bulletB[i]->bulletBoxB.y = bulletB[i]->bulletBoxB.y + 20;
		apply_surface(bulletB[i]->bulletBoxB.x, bulletB[i]->bulletBoxB.y, bulletsEnemy, screen);
		//cek Bullet keluar layar
		if(bulletB[i]->bulletBoxB.y > 650)
		{
			for(int x = i; x < ctrBoss; x++)
			{
				bulletB[x] = bulletB[x+1];
			}
			delete[] bulletB[ctrBoss];
			ctrBoss--; 
		}	
	}
}

int Boss::randomAI()
{
	if(ctrRandom % 20 == 0)
	{
		int x = rand()%20+1;
		
		if(x == 1 || x == 2 || x == 3 || x == 4 || x == 5 || x == 6 || x == 7 || x == 8) moveLeft();
		if(x == 9 || x == 10 || x == 11 || x == 12 || x == 13 || x == 14 || x == 15 || x == 16) moveRight();
		if(x == 17 || x == 18 || x == 19 || x == 20) shoot(); 
		return x;
	}
}

bool Boss::bossDead()
{
	if(life <=0) return true;
	else return false;
}

