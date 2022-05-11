#include "hd.h"
using namespace std;

void draw(SDL_Renderer* renderer,int x,int y, char *s, float tiLe){
    SDL_Texture* dogde= loadTexture(s,renderer);
    SDL_Rect dogdeRect;
    SDL_QueryTexture(dogde,NULL,NULL,&dogdeRect.w,&dogdeRect.h);
    dogdeRect.x=x;
    dogdeRect.y=y;
    dogdeRect.w=dogdeRect.w/tiLe;
    dogdeRect.h=dogdeRect.h/tiLe;
    SDL_RenderCopy(renderer,dogde,NULL,&dogdeRect);


    SDL_RenderPresent(renderer);
}
SDL_Texture* loadTexture( string path,SDL_Renderer* renderer ){
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == NULL )
        cout << "Unable to load image " << path << " SDL_image Error: "<< IMG_GetError() << endl;

    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
            cout << "Unable to create texture from " << path << " SDL Error:"<< SDL_GetError() << endl;

        SDL_FreeSurface( loadedSurface );
}
    return newTexture;
}
