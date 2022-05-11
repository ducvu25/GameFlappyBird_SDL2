#include "giaoDIen.h"

using namespace std;


void GiaoDienEnd(SDL_Renderer* renderer, int x, int y, int d, int NhanVat){
    draw(renderer, 320, 350, "ChoiLai.bmp", 1.5, NULL, NULL);
    draw(renderer, 520, 350, "Thoat.bmp", 1.7, NULL, NULL);
    char s[100];
    switch(NhanVat){
    case 1: strcpy(s, "NhanVat1.bmp"); break;
    case 2: strcpy(s, "NhanVat2.bmp"); break;
    case 3: strcpy(s, "NhanVat3.bmp"); break;
    case 4: strcpy(s, "NhanVat4.bmp"); break;
    }
    switch(d){
        case 1: draw(renderer, 300, 250, s, 2.5, NULL, NULL); break;
        case 2: draw(renderer, 500, 250, s, 2.5, NULL, NULL); break;
    }
}
void MenuNV(int x, int y, SDL_Renderer* renderer, int NhanVat){
    draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
    draw(renderer, x, y + 200, "NhanVat1.bmp", 2.5, NULL, NULL);
    draw(renderer, x + 200, y + 200, "NhanVat2.bmp", 2.5, NULL, NULL);
    draw(renderer, x + 400, y + 200, "NhanVat3.bmp", 2.5, NULL, NULL);
    draw(renderer, x + 600, y + 200, "NhanVat4.bmp", 2.5, NULL, NULL);
    switch(NhanVat){
        case 1: draw(renderer, 500, y, "NhanVat1.bmp", 2, NULL, NULL);  draw(renderer, x + 33, y + 300, "ChonNV.bmp", 2, NULL, NULL);    break;
        case 2: draw(renderer, 500, y, "NhanVat2.bmp", 2, NULL, NULL);  draw(renderer, x+200 + 23, y + 300, "ChonNV.bmp", 2, NULL, NULL);    break;
        case 3: draw(renderer, 500, y, "NhanVat3.bmp", 2, NULL, NULL);  draw(renderer, x+400 + 35, y + 300, "ChonNV.bmp", 2,  NULL, NULL);    break;
        case 4: draw(renderer, 500, y, "NhanVat4.bmp", 2, NULL, NULL);  draw(renderer, x+600 + 30, y + 300, "ChonNV.bmp", 2, NULL, NULL);    break;
    }
    SDL_RenderPresent(renderer);
}
void Menu(int x, int y, SDL_Renderer* renderer, int NhanVat, int d){
    draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
    draw(renderer, x, y + 150, "BatDau.bmp", 1.5, NULL, NULL);
    draw(renderer, x + 200, y + 150, "CaiDat.bmp", 1.5, NULL, NULL);
    draw(renderer, x + 400, y + 150, "AmThanh.bmp", 1.5, NULL, NULL);
    draw(renderer, x + 600, y + 150, "Thoat.bmp", 1.5, NULL, NULL);
    int a = 20;
    switch(NhanVat){
        case 1:{
            draw(renderer, 200*d - a, y, "NhanVat1.bmp", 2, NULL, NULL);
            break;
        }
        case 2:{
            draw(renderer, 200*d - a, y, "NhanVat2.bmp", 2, NULL, NULL);
            break;
        }
        case 3:{
            draw(renderer, 200*d - a, y, "NhanVat3.bmp", 2, NULL, NULL);
            break;
        }
        case 4:{
            draw(renderer, 200*d - a, y, "NhanVat4.bmp", 2, NULL, NULL);
            break;
        }
    }
    SDL_RenderPresent(renderer);
}
void GiaoDien(SDL_Renderer* renderer, int x, int y, char *s){
    int d = 1;
    draw(renderer, 50, 0, "Flappy Birth.bmp", 1.8, NULL, NULL);
    SDL_RenderPresent(renderer);
    for(int i=0; i<400; i+=20){
        draw(renderer, 50, 0, "Flappy Birth.bmp", 1.8, NULL, NULL);
        switch(d){
            case 1: draw(renderer, 400, 400, "load1.bmp", 4, NULL, NULL); break;
            case 2: draw(renderer, 400, 400, "load2.bmp", 4, NULL, NULL); break;
            case 3: draw(renderer, 400, 400, "load3.bmp", 4, NULL, NULL); break;
        }
        d++;
        if(d == 4)
            d = 1;
        draw(renderer, x + i, y, s, 3, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_Delay(300);
    }
}
void logSDLError(std::ostream& os, const std::string &msg, bool fatal){
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
logSDLError(std::cout, "SDL_Init", true);
window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
//SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
if (window == NULL) logSDLError(std::cout, "CreateWindow", true);
//Khi chạy trong môi trường bình thường (không chạy trong máy ảo)
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
SDL_RENDERER_PRESENTVSYNC);
//Khi chạy ở máy ảo (ví dụ tại máy tính trong phòng thực hành ở trường)
//renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
if (renderer == NULL) logSDLError(std::cout, "CreateRenderer", true);
SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

//.............................................................


void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

//.............................................................

void waitUntilKeyPressed()
{
SDL_Event e;
while (true) {
if ( SDL_WaitEvent(&e) != 0 &&
(e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
return;
SDL_Delay(100);
}
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
void draw(SDL_Renderer* renderer,int x,int y, char *s, float tiLe, int *cao, int *rong){
    SDL_Texture* dogde= loadTexture(s,renderer);
    SDL_Rect dogdeRect;
    SDL_QueryTexture(dogde,NULL,NULL,&dogdeRect.w,&dogdeRect.h);
    dogdeRect.x=x;
    dogdeRect.y=y;
    dogdeRect.w=dogdeRect.w/tiLe;
    dogdeRect.h=dogdeRect.h/tiLe;
    if(cao != NULL) *rong = dogdeRect.w/2;
    if(rong != NULL) *cao = dogdeRect.h - 10;
    SDL_RenderCopy(renderer,dogde,NULL,&dogdeRect);
}

void drawChan(SDL_Renderer* renderer,int x,int y, char *s, float tiLe, int *cao, int *rong){
    SDL_Texture* dogde= loadTexture(s,renderer);
    SDL_Rect dogdeRect;
    SDL_QueryTexture(dogde,NULL,NULL,&dogdeRect.w,&dogdeRect.h);
    dogdeRect.w=dogdeRect.w/tiLe;
    dogdeRect.h=dogdeRect.h/tiLe;
    if(cao != NULL) *rong = dogdeRect.w/2;
    if(rong != NULL) *cao = dogdeRect.h;
    dogdeRect.x=x;
    dogdeRect.y=600-dogdeRect.h;
    SDL_RenderCopy(renderer,dogde,NULL,&dogdeRect);
}

