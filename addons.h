//addons

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{

    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void apply_cropped_surface( int posX, int posY, int cropX, int cropY, int cropW, int cropH, SDL_Surface* source, SDL_Surface* destination ){
     
	 SDL_Rect crop;
	 SDL_Rect pos;
     
     pos.x = posX; 
	 pos.y = posY;
     crop.x = cropX; 
	 crop.y = cropY;
     crop.w = cropW;
     crop.h = cropH;
     
     SDL_BlitSurface( source, &crop, destination, &pos );  
}

void apply_surface_text( int x, int y, SDL_Surface* text, SDL_Surface* screen )
{
    SDL_Rect offset;
    
    offset.x = x;
    offset.y = y;
   
    SDL_BlitSurface( text, NULL, screen, &offset );
}
