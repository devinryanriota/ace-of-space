#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#undef main

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"

using namespace std;

int ctrChar = 0;     //bullet aktif character
int ctrEnemy = 0;    // bullet aktif musuh
int ctrBoss = 0;    // bullet aktif boss
int ctrObjEnemy = 0; // jumlah enemy yang aktif
int ctrObjBoss = 0;

#include "addons.h"
#include "bullets.h"
Bullets *bullet[100]; //bullet character
Bullets *bulletE[100]; //bullet enemy
Bullets *bulletB[10]; //bullet boss
#include "character.h"
Character character;

#include "enemy.h"
Enemy *enemy[50];

#include "boss.h"
Boss *boss[50];

#include "game.h"
Game game;

int menu();
int instructionsM();
int creditsM();
int gameOver();

int mainGame()
{
	int i = 0;
	//class Button button;
	TTF_Init();
	//SDL_Surface *printLife = NULL;
	
	srand(time(NULL));
	SDL_Surface *screen = NULL;
	SDL_Surface *bulletsImg = NULL;
	SDL_Surface *bulletsEnemy = NULL;
	SDL_Surface *bulletsBoss = NULL;
	SDL_Surface *printLife = NULL;
	SDL_Surface *printLifeB = NULL;
	SDL_Surface *printScore = NULL;
	SDL_Surface *printScoreB = NULL;
	SDL_Surface *printScoreC = NULL;
	SDL_Surface *printScoreD = NULL;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Event event;
	SDL_WM_SetCaption( "Ace of Space", NULL );
	 
	screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);
	

	TTF_Font *font = NULL;
	SDL_Color yellow = {244, 212, 15};
	font = TTF_OpenFont("./fonts/SF Distant Galaxy Alternate Italic.ttf", 34);
	
	//print text "LIFE"
	printLife = TTF_RenderText_Solid(font, "LIFE", yellow);
	SDL_Rect lifeFont;
	lifeFont.x = 10;
	lifeFont.y = 10;
	//apply_surface(lifeFont.x, lifeFont.y, printLife, screen);
	
	//print int LIFE
	char lifeB[5];
	itoa(character.getLife(), lifeB, 10);
	printLifeB = TTF_RenderText_Solid(font, lifeB, yellow);
	SDL_Rect lifeChar;
	lifeChar.x = 10;
	lifeChar.y = 25;
	//apply_surface(lifeChar.x, lifeChar.y, printLifeB, screen);
	
	//print text "HIGHSCORE"
	printScore = TTF_RenderText_Solid(font, "HIGHSCORE", yellow);
	SDL_Rect scoreFont;
	scoreFont.x = 415;
	scoreFont.y = 10;
	//apply_surface(scoreFont.x, scoreFont.y, printScore, screen);
	
	//print int HIGHSCORE
	game.readHighScore();
	char scoreB[20];
	itoa(game.getHighScore(), scoreB, 10);
	printScoreB = TTF_RenderText_Solid(font, scoreB, yellow);
	SDL_Rect highScoreGame;
	highScoreGame.x = 500;
	highScoreGame.y = 35;
	//apply_surface(highScoreGame.x, highScoreGame.y, printScoreB, screen);
	
	//print text "SCORE"
	printScoreC = TTF_RenderText_Solid(font, "SCORE", yellow);
	SDL_Rect scoreCFont;
	scoreCFont.x = 500;
	scoreCFont.y = 70;
	//apply_surface(scoreCFont.x, scoreCFont.y, printScoreC, screen);
	
	//print int "SCORE"
	char scoreC[20];
	itoa(game.getScore(), scoreC, 10);
	printScoreD = TTF_RenderText_Solid(font, scoreC, yellow);
	SDL_Rect scoreGame;
	scoreGame.x = 500;
	scoreGame.y = 100;
	//apply_surface(scoreGame.x, scoreGame.y, printScoreD, screen);
	
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	//BGM
	//bgm in game
	Mix_Music *bgm = NULL;
	bgm = Mix_LoadMUS("./musics/inGame3.wav");
	Mix_VolumeMusic(100);
	//if(bgm!=NULL) 
	Mix_PlayMusic(bgm, -1);

	
	//SFX
	//laser character
	Mix_Chunk *sfx = NULL;
	sfx = Mix_LoadWAV("./musics/laser.wav");
	Mix_VolumeChunk(sfx, 30);
	//laser enemy
	Mix_Chunk *sfx2 = NULL;
	sfx2 = Mix_LoadWAV("./musics/laser2.wav");
	Mix_VolumeChunk(sfx2 , 15);
	//laser boss
	Mix_Chunk *sfx3 = NULL;
	sfx3 = Mix_LoadWAV("./musics/laser4.wav");
	Mix_VolumeChunk(sfx3, 30);
	//spawn boss
	Mix_Chunk *sfx4 = NULL;
	sfx4 = Mix_LoadWAV("./musics/bossSpawn.wav");
	Mix_VolumeChunk(sfx4, 30);
	//
	
	/*Mix_Music *bgm2 = NULL;
	//bgm2
	Mix_VolumeMusic(50);
	Mix_PlayMusic(bgm2, -1);*/
	
	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
 
	SDL_Surface *bg = NULL;
	bg = IMG_Load("./images/farback2.png");
	bulletsImg = IMG_Load("./images/laserGreen2.png");
	bulletsEnemy = IMG_Load("./images/laserRed2.png");
	bulletsBoss = IMG_Load("./images/bulletBoss.png");
	
	
	SDL_EnableKeyRepeat(100,100);

	character.printChar(screen);
	
	while(!game.gameDone())
	{
		
		apply_surface(offset.x, offset.y, bg, screen);
		character.printChar(screen);
		
		//Spawn Boss
		if(game.getScore() != 0 && game.getScore() % 200 == 0 && game.bossSpawn == false )
		{	
			ctrObjBoss++;
			boss[ctrObjBoss] = new Boss();
			Mix_PlayChannel(-1, sfx4, 0);
			boss[ctrObjBoss]->spawn(screen);
			game.bossSpawn = true;
				
		}
		
		//print LIFE
		apply_surface(lifeFont.x, lifeFont.y, printLife, screen);
		
		char lifeB[5];
		itoa(character.getLife(), lifeB, 10);
		printLifeB = TTF_RenderText_Solid(font, lifeB, yellow);
		SDL_Rect lifeChar;
		lifeChar.x = 10;
		lifeChar.y = 35;
		apply_surface(lifeChar.x, lifeChar.y, printLifeB, screen);
		
		//print HIGHSCORE
		apply_surface(scoreFont.x, scoreFont.y, printScore, screen);
		
		game.readHighScore();
		char scoreB[20];
		itoa(game.getHighScore(), scoreB, 10);
		printScoreB = TTF_RenderText_Solid(font, scoreB, yellow);
		SDL_Rect highScoreGame;
		highScoreGame.x = 500;
		highScoreGame.y = 35;
		apply_surface(highScoreGame.x, highScoreGame.y, printScoreB, screen);
		
		//check Highscore
		if(game.getScore() > game.getHighScore())
		{
			game.setHighScore(game.getScore());
			game.writeHighScore();
		}
		
		//print text "SCORE"
		apply_surface(scoreCFont.x, scoreCFont.y, printScoreC, screen);
		
		char scoreC[20];
		itoa(game.getScore(), scoreC, 10);
		printScoreD = TTF_RenderText_Solid(font, scoreC, yellow);
		SDL_Rect scoreGame;
		scoreGame.x = 500;
		scoreGame.y = 100;
		apply_surface(scoreGame.x, scoreGame.y, printScoreD, screen);
		
		
		if(offset.y >=4 -640) offset.y --;
		else offset.y = 0;
	
		int randEnemy = rand()%30+1;
		int randEnemy2 = rand()%500+1;
		if(ctrObjEnemy <= 5)
		{
				if(randEnemy2 % randEnemy == 0)
				{
					enemy[ctrObjEnemy] = new Enemy();
					enemy[ctrObjEnemy]->spawn(screen);
					ctrObjEnemy++;
				}
		}
		     
		for(i=0; i < ctrObjEnemy; i++)
		{
			enemy[i]->spawn(screen);
		}
		
		
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
				{
					
					switch(event.key.keysym.sym)
					{
						case SDLK_UP : character.moveUp(); break;  
						case SDLK_DOWN : character.moveDown(); break;
						case SDLK_LEFT : character.moveLeft(); break;
						case SDLK_RIGHT : character.moveRight(); break;
						case SDLK_SPACE : character.shoot(); Mix_PlayChannel(-1, sfx, 0); break;
						default:;
					}
				}
		}
		
		else if( event.type == SDL_QUIT )
	    	{
	    		return 0;
	    	}
	    
		character.printBullet(bulletsImg, screen);
		
		for(int w = 0; w < ctrEnemy; w++)
		{
			//if(enemy[w] == NULL) ;
			enemy[w]->printBullet(bulletsEnemy, screen, w);
		}
	   	//Random AI Enemy
		for(int r = 0; r < ctrObjEnemy; r++)
		{
			enemy[r]->randomAI();
			int ac = enemy[r]->randomAI();
			if(ac == 11 || ac == 12 || ac == 13 || ac == 14 || ac == 15) Mix_PlayChannel(-1, sfx2, 0);
			enemy[r]->setCtrAI((enemy[r]->getCtrAI())+1);
		}
		//Random AI Boss
		if(game.bossSpawn == true)
		{	
			boss[ctrObjBoss]->spawn(screen);
			boss[ctrObjBoss]->randomAI();
			int ax = boss[ctrObjBoss]->randomAI();
			if(ax == 1 || ax == 2 || ax == 3 || ax == 4 || ax == 5 || ax == 6 || ax == 7 || ax == 8) Mix_PlayChannel(-1, sfx4, 0);
			if(ax == 9 || ax == 10 || ax == 11 || ax == 12 || ax == 13 || ax == 14 || ax == 15 || ax == 16) Mix_PlayChannel(-1, sfx4, 0);
			if(ax == 17 || ax == 18 || ax == 19 || ax == 20) Mix_PlayChannel(-1, sfx3, 0);
			boss[ctrObjBoss]->setCtrRandom(boss[ctrObjBoss]->getCtrRandom()+1);
			
			boss[ctrObjBoss]->printBullet(bulletsBoss, screen);
		}
		//Cek bos hidup atau mati
		if(game.bossSpawn == true)
		{
			if(boss[ctrObjBoss]->bossDead())
			{
				delete boss[ctrObjBoss];
				character.setLife(character.getLife()+3);
				game.bossSpawn = false;
			}
		}
		
		//Delete enemy ketika diluar layar
		for(int s = 0; s < ctrObjEnemy; s++)
		{
			if(enemy[s]->enemyBox.y > 640)
			{
				//cek apakah s terakhir
				if(enemy[s] != enemy[ctrObjEnemy])
				{
					for(int t = s; t < ctrObjEnemy; t++)
					{
						enemy[s] = enemy[s+1];
					}
					delete enemy[ctrObjEnemy];
					ctrObjEnemy--;
				}
				//untuk hapus terakhir
				else if(enemy[s] == enemy[ctrObjEnemy])
				{
					delete enemy[ctrObjEnemy];
					ctrObjEnemy--;
				}
			}
		}
		
		// Collision peluru character dengan musuh
		for(int o = 0; o < ctrObjEnemy; o++)
		{
			for(int p = 0; p < ctrChar; p++)
			{
				if(game.checkCollision(bullet[p]->bulletBox, enemy[o]->enemyBox))
				{
					if(enemy[o+1] != NULL)
					{
						for(int z = o; z < ctrObjEnemy; z++)
						{
							enemy[z] = enemy[z+1];
							delete enemy[ctrObjEnemy];
						}
						ctrObjEnemy--;
						game.setScore(game.getScore()+10);
					}
					else 
					{
						delete enemy[ctrObjEnemy];
						ctrObjEnemy--;
						game.setScore(game.getScore()+10);
					}
					if(bullet[p+1] != NULL)
					{
						for(int aq = p; aq < ctrChar; aq++)
						{
							bullet[aq] = bullet[aq+1];
						}
						delete bullet[ctrChar];
						ctrChar--;
					}
					else 
					{
						delete bullet[ctrChar];
						ctrChar--;
					} 
				}
			}
		}
		
		//Collision peluru character dengan boss
		if(game.bossSpawn == true)
		{
			for(int h = 0; h < ctrChar; h++)
			{
				if(game.checkCollision(bullet[h]->bulletBox, boss[ctrObjBoss]->bossBox))
				{
					if(bullet[h+1] != NULL)
					{
						for(int at = h; at < ctrChar; at++)
						{
							bullet[at] = bullet[at+1];
						}
						delete bullet[ctrChar];
						ctrChar--;
						game.setScore(game.getScore()+50);
						boss[ctrObjBoss]->setLife(boss[ctrObjBoss]->getLife()-1);
					}
					else
					{
						delete bullet[ctrChar];
						ctrChar--;
						game.setScore(game.getScore()+50);
						boss[ctrObjBoss]->setLife(boss[ctrObjBoss]->getLife()-1);
					}
				}
			}
		}
		
		//Collision peluru boss dengan character
		for(int t = 0; t < ctrBoss; t++)
		{
			if(game.checkCollision(bulletB[t]->bulletBoxB, character.charBox))
			{
				if(bulletB[t+1] != NULL)
				{
					for(int az = t; az < ctrBoss; az++)
					{
						bulletB[az] = bulletB[az+1];
					}
					delete bulletB[ctrBoss];
					ctrBoss--;
					character.setLife(character.getLife()-2);
				}
				else
				{
					delete bulletB[ctrBoss];
					ctrBoss--;
					character.setLife(character.getLife()-2);
				}
			}
		}
		
		
		// Collision peluru musuh dengan character
			for(int r = 0; r < ctrEnemy; r++)
			{
				if(game.checkCollision(bulletE[r]->bulletBoxE, character.charBox))
				{
					if(bulletE[r+1] != NULL)
					{
						for(int ay = r; ay < ctrEnemy; ay++)
						{
							bulletE[ay] = bulletE[ay+1];
						}
						delete bulletE[ctrEnemy];
						ctrEnemy--;
						character.setLife(character.getLife()-1);
					}
					else
					{
						delete bulletE[ctrEnemy];
						ctrEnemy--;
						character.setLife(character.getLife()-1);
					}
				}	
			}
		
		// Collision musuh dengan character
		for(int s = 0; s < ctrObjEnemy; s++)
		{
			if(game.checkCollision(enemy[s]->enemyBox, character.charBox))
			{
				if(enemy[s+1] != NULL)
				{
				for(int z = s; z < ctrObjEnemy; z++)
					{
						enemy[z] = enemy[z+1];
						delete enemy[ctrObjEnemy];
					}
					
					ctrObjEnemy--;
					character.setLife(character.getLife()-1);
				}
				else
				{
					delete enemy[ctrObjEnemy];
					ctrObjEnemy--;
					character.setLife(character.getLife()-1);
				}
			}
		}
			
	   	SDL_Flip(screen);
		
	   	game.setCrop();
	}
	
	gameOver();
	game.reset();
	menu();
	Mix_FreeMusic(bgm);
	Mix_FreeChunk(sfx);
	Mix_FreeChunk(sfx2);
	Mix_FreeChunk(sfx3);
	Mix_FreeChunk(sfx4);
			
	
}

int main(int argc, char** argv) {
		menu();
}

int menu()
{
	SDL_Surface *screen = NULL, *bgr = NULL, *arrow = NULL, *start = NULL, *instructions = NULL, *credits = NULL;
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption( "Ace of Space", NULL );
	SDL_Event event;
	Uint8 *key;
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	//BGM
	//bgm in game
	Mix_Music *bgm2 = NULL;
	bgm2 = Mix_LoadMUS("./musics/bgm.wav");
	Mix_VolumeMusic(70);
	//if(bgm!=NULL) 
	Mix_PlayMusic(bgm2, -1);
	 
	screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);	
	TTF_Init();
	TTF_Font *menu;
	SDL_Color yellow = {244, 212, 15};
	menu = TTF_OpenFont("./fonts/SF Distant Galaxy Alternate.ttf", 34);
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	bgr = IMG_Load("./images/menu.png");
	SDL_Rect arrowr;
	arrowr.x = 200;
	arrowr.y = 275;
	arrow = IMG_Load("./images/arrow5.png");
	start = TTF_RenderText_Solid( menu, "START", yellow );
	instructions = TTF_RenderText_Solid( menu, "INSTRUCTIONS", yellow );
	credits = TTF_RenderText_Solid( menu, "CREDITS", yellow );
	apply_surface(arrowr.x, arrowr.y, arrow, screen);			
	while(1)
	{
		apply_surface(offset.x, offset.y, bgr, screen);
		apply_surface(arrowr.x, arrowr.y, arrow, screen);
		apply_surface_text(250, 300, start, screen);
		apply_surface_text(250, 400, instructions, screen);
		apply_surface_text(250, 500, credits, screen);
		
		if(SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) SDL_Quit();
			key = SDL_GetKeyState( NULL );
			if(arrowr.y == 275 && key[SDLK_RETURN]) mainGame();
			if(arrowr.y == 375 && key[SDLK_RETURN]) 
			{
				instructionsM(); 
				break;
			}
			if(arrowr.y == 475 && key[SDLK_RETURN]) 
			{
				creditsM();
				break;
			} 
			if( key[SDLK_DOWN] )
			{
				if(arrowr.y < 475) arrowr.y += 100;
				else arrowr.y = 275;
			}
			if( key[SDLK_UP] )
			{
				if(arrowr.y > 275) arrowr.y -= 100;
				else arrowr.y = 475;
			}
		}
		SDL_Flip(screen);
	}
	Mix_FreeMusic(bgm2);
	//SDL_Delay(5000);
	
}

int instructionsM()
{
	SDL_Surface *screen = NULL, *bgri = NULL;
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption( "Ace of Space", NULL );
	SDL_Event event;
	screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);	
	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	bgri = IMG_Load("./images/instructions.png");
	while(1)
	{
		apply_surface(offset.x, offset.y, bgri, screen);
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
				{
					
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE : menu(); break;
						default:;
					}
				}
		}
		
	else if( event.type == SDL_QUIT )
    	{
	   		return 0;
	   	}
	   	SDL_Flip(screen);
	}
	
	
}

int creditsM()
{
	SDL_Surface *screen = NULL, *bgri = NULL;
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption( "Ace of Space", NULL );
	SDL_Event event;
	screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);	
	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	bgri = IMG_Load("./images/credits.png");
	while(1)
	{
		apply_surface(offset.x, offset.y, bgri, screen);
		if(SDL_PollEvent(&event))
		{
			if(event.type == SDL_KEYDOWN)
				{
					
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE : menu(); break;
						default:;
					}
				}
		}
		
	else if( event.type == SDL_QUIT )
   	{
	  	return 0;
	}
	   	SDL_Flip(screen);
	}
	
}

int gameOver()
{
	SDL_Surface *screen = NULL, *bgri = NULL, *gameOver = NULL, *finalScore = NULL;
	SDL_Init (SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption( "Ace of Space", NULL );
	SDL_Event event;
	screen = SDL_SetVideoMode(640, 640, 32, SDL_SWSURFACE);	
	
	SDL_Rect offset;
	offset.x = 0;
	offset.y = 0;
	bgri = IMG_Load("./images/gameOver.png");
	apply_surface(offset.x, offset.y, bgri, screen);
	
	TTF_Font *font = NULL;
	SDL_Color yellow = {244, 212, 15};
	font = TTF_OpenFont("./fonts/SF Distant Galaxy Alternate Italic.ttf", 40);
	
	gameOver = TTF_RenderText_Solid(font, "YOUR SCORE IS", yellow);
	SDL_Rect gameOverA;
	gameOverA.x = 150;
	gameOverA.y = 350;
	apply_surface(gameOverA.x, gameOverA.y, gameOver, screen);
	
	char finalScoreX[20];
	itoa(game.getScore(), finalScoreX, 10);
	finalScore = TTF_RenderText_Solid(font, finalScoreX, yellow);
	SDL_Rect finalScoreA;
	finalScoreA.x = 250;
	finalScoreA.y = 400;
	apply_surface(finalScoreA.x, finalScoreA.y, finalScore, screen);
	SDL_Flip(screen);
	SDL_Delay(5000);
}




