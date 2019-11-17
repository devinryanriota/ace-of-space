class Bullets{
	private :
		int bulletX;
		int bulletY;
	public :
		//SDL_Surface *bulletsimg = NULL;
		SDL_Rect bulletBox, bulletBoxE, bulletBoxB;
		//Bullets();
		void setX(int a){ bulletX = a;}
		void setY(int b){ bulletY = b;}
		int getX() { return bulletX; }
		int getY() { return bulletY; }
		void checkExitScreen();
};



