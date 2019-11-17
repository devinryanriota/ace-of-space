//Character
void cropSprites();
//void spawnBullet(int x, int y);

class Character{
	private:
		int charX;
		int charY;
		int cropX;
		int life;
	public:
		SDL_Surface *character = NULL;
		SDL_Rect crop;
		//crop.x = 0;
		SDL_Rect charBox;
		Character();
		void setCharX(int a){charX = a;}
		void setCharY(int b){charY = b;}
		void setCropX(int c){cropX = c;}
		void setLife(int d){life = d;}
		int getCharX(){return charX;}
		int getCharY(){return charY;}
		int getCropX(){return cropX;}
		int getLife(){return life;}
		
		void printChar(SDL_Surface *&screen);
		void cropSprites();
		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();
		void shoot();
		void printBullet(SDL_Surface *&bulletsImg, SDL_Surface *&screen);
		//int getX() { return charX; }
		//int getY() { return charY; }
};

Character::Character()
{
	charBox.x = 300;
	charBox.y = 550;
	charBox.w = 32;
	charBox.h = 64;
	cropX = 0;
	life = 10;
//	SDL_Surface *character = NULL;
	character = IMG_Load("./images/ship.png");
	
}

void Character::cropSprites()
{
	crop.x = this->cropX; 
	crop.y = 0;
	crop.w = 32;
	crop.h = 64;
}


void Character::printChar(SDL_Surface *&screen)
{
	this->cropSprites();
	apply_cropped_surface(charBox.x, charBox.y, crop.x, crop.y, crop.w, crop.h, character, screen);
//	SDL_Delay(25);
}

void Character::moveLeft()
{
	if(charBox.x >= 0) charBox.x = charBox.x - 10;
}

void Character::moveRight()
{
	if(charBox.x <= 600) charBox.x = charBox.x + 10;
}

void Character::moveUp()
{
	if(charBox.y <= 425) ;
	else charBox.y = charBox.y - 10;
}

void Character::moveDown()
{
	if(charBox.y <= 620) charBox.y = charBox.y + 10;
}


void Character::shoot()
{
	bullet[ctrChar] = new Bullets();	
	bullet[ctrChar]->bulletBox.x = charBox.x +13;
	bullet[ctrChar]->bulletBox.y = charBox.y -25;
	ctrChar++;	
}

void Character::printBullet(SDL_Surface *&bulletsImg, SDL_Surface *&screen)
{
	for(int i = 0; i < ctrChar; i++)
    {
    	//SDL_Rect bull;
    	//bull.x=bullet[i]->getX();
    	//bull.y=bullet[i]->getY();
		bullet[i]->bulletBox.y = bullet[i]->bulletBox.y - 10;
		apply_surface(bullet[i]->bulletBox.x, bullet[i]->bulletBox.y, bulletsImg, screen);
		//cek Bullet keluar layar
		if(bullet[i]->bulletBox.y < -10)
		{
			for(int x = i; x < ctrChar; x++)
			{
			bullet[x] = bullet[x+1];
			}
			delete[] bullet[ctrChar];
			ctrChar--; 
		}	
	}
}




