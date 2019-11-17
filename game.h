//Menu
class Game{
	private:
		int score;
		int highScore;
	public:
		SDL_Surface *menuBackground = NULL;
		
		
		void setScore(int a){score = a;}
		int getScore(){return score;}
		void mainMenu(SDL_Surface *&screen);
		void setCrop();
		bool checkCollision(SDL_Rect A, SDL_Rect B);
		void printLifeScreen();
		bool gameDone();
		bool bossSpawn;
		void readHighScore();
		void setHighScore(int b){highScore = b;}
		int getHighScore(){return highScore;}
		void writeHighScore();
		void reset();
};

void Game::mainMenu(SDL_Surface *&screen)
{
	menuBackground = IMG_Load("./images/menu.png");
	apply_surface(0, 0, menuBackground, screen);		
}

void Game::setCrop()
{
	if(character.getCropX() == 96) character.setCropX(0);
    else character.setCropX(character.getCropX()+32);
    for(int a = 0; a < ctrObjEnemy; a++)
    {
    	if(enemy[a]->getCropX() == 384) enemy[a]->setCropX(enemy[a]->getCropX()+32);
    	else enemy[a]->setCropX(0); 
	}
	/*if(boss[ctrObjBoss]->getCropX() == 610) boss[ctrObjBoss]->setCropX(0);
	else boss[ctrObjBoss]->setCropX(boss[ctrObjBoss]->getCropX()+122);*/
}

bool Game::checkCollision(SDL_Rect A, SDL_Rect B)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
        
    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    return true;
}

bool Game::gameDone()
{
	if(character.getLife() <= 0) return true;
	else return false;
}

void Game::readHighScore()
{
	int high;
	char highscore[1][1];
	ifstream filei;
	filei.open("highscore.dat");
	filei.get(highscore[1], 10);
	high = atoi(highscore[1]);
	setHighScore(high);
}

void Game::writeHighScore()
{
	ofstream fileo;
	fileo.open("highscore.dat");
	fileo << getHighScore();
}

void Game::reset()
{
	score = 0;
	character.setLife(5);
	for(int i = ctrChar; i > 0 ; i--)
	{
		delete bullet[i];
		ctrChar--;
	}
	for(int j = ctrEnemy; j > 0; j--)
	{
		delete bulletE[j];
		ctrEnemy--;
	}
	for(int k = ctrBoss; k > 0; k--)
	{
		delete bulletB[k];
		ctrBoss--;
	}
	for(int l = ctrObjEnemy; l > 0; l--)
	{
		delete enemy[l];
		ctrObjEnemy--;
	}
	for(int m = ctrObjBoss; m > 0; m++)
	{
		delete boss[m];
		ctrObjBoss--;
	}
	//gameDone();
}
/*class Button
{
	private:
		SDL_Rect boxStart, boxInstructions, boxCredits;	
		SDL_Rect *clipStart, *clipInstructions, *clipCredits;
		SDL_Surface *start = NULL, *instructions = NULL, *credits = NULL;
	public:
		Button(int x, int y, int w, int h);
		void setClipStart();
		void set_clips();
		void show();
		void handle_events();
};

void set_clips()
{
    
	    clips[ CLIP_MOUSEOVER ].x = 0;
	    clips[ CLIP_MOUSEOVER ].y = 0;
	    clips[ CLIP_MOUSEOVER ].w = 400;
	    clips[ CLIP_MOUSEOVER ].h = 80;
	
	    clips[ CLIP_MOUSEOUT ].x = 400;
	    clips[ CLIP_MOUSEOUT ].y = 0;
	    clips[ CLIP_MOUSEOUT ].w = 320;
	    clips[ CLIP_MOUSEOUT ].h = 240;
	
	    /*clips[ CLIP_MOUSEDOWN ].x = 0;
	    clips[ CLIP_MOUSEDOWN ].y = 240;
	    clips[ CLIP_MOUSEDOWN ].w = 320;
	    clips[ CLIP_MOUSEDOWN ].h = 240;
	    
	    clips[ CLIP_MOUSEUP ].x = 320;
	    clips[ CLIP_MOUSEUP ].y = 240;
	    clips[ CLIP_MOUSEUP ].w = 320;
	    clips[ CLIP_MOUSEUP ].h = 240;
}

void Button::setClipStart()
{
	start = IMG_Load("./images/startButton.png");
}

Button::Button(int x, int y, int w, int h)
{
	boxStart.x = x;
	boxStart.y = y;
	boxStart.w = w;
	boxStart.h = h;
	
	clip = &clips[CLIP_MOUSEOUT];
}

void Button::show()
{
	apply_surface(boxStart.x, boxStart.y, )
}

void Button:handle_events()
{
	int x = 0;
	int y = 0;
	 if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        //If the mouse is over the button
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOVER ];
        }
        //If not
        else
        {
            //Set the button sprite
            clip = &clips[ CLIP_MOUSEOUT ];
        }
    }
}
*/
