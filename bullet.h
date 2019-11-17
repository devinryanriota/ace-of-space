//Bullet
void spawnBullet(int x, int y, SDL_Surface *&screen);



class Bullet{  
	private:
		int bulletX;
		int bulletY;
		bool bulletCheck;
	public:
		
		SDL_Surface *bullet;
		void setBulletX(int a){bulletX = a;}
		int getBulletX(){return bulletX;}
		void setBulletY(int b){bulletY = b;}
		int getBulletY(){return bulletY;}
		void setBulletCheck(bool x){bulletCheck = x;}
		int getBulletCheck(){return bulletCheck;}
		void spawnBullet(int x, int y, SDL_Surface *&screen);
		void printBullet(SDL_Surface *&screen);
		void moveCharBullet(SDL_Surface *&screen);
};


void Bullet::spawnBullet(int x, int y, SDL_Surface *& screen)
{
	bulletX = x + 13;
	bulletY = y - 14;
	bullet = IMG_Load("./images/laserGreen2.png");
	//bulletCheck = true;
	//apply_surface(bulletX, bulletY, bullet, screen);
}

void Bullet::printBullet(SDL_Surface *&screen)
{
	apply_surface(bulletX, bulletY, bullet, screen);
	//cout<<bulletX<<" "<<bulletY<<endl;
}

void Bullet::moveCharBullet(SDL_Surface *&screen)
{
	if(bulletY <= -20) ;
	else bulletY -=15;
	apply_surface(bulletX, bulletY, bullet, screen);	
}



