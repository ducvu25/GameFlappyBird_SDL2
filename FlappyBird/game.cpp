
#include "game.h"

using namespace std;

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
renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

SDL_Texture* ChonNhanVat(SDL_Renderer* renderer, int d){
    SDL_Texture *NhanVat;
    switch(d){
        case 0:{
            NhanVat = loadTexture("NhanVat1.bmp", renderer);
            break;
        }
        case 1:{
            NhanVat = loadTexture("NhanVat2.bmp", renderer);
            break;
        }
        case 2:{
            NhanVat = loadTexture("NhanVat3.bmp", renderer);
            break;
        }
        case 3:{
            NhanVat = loadTexture("NhanVat4.bmp", renderer);
            break;
        }
    }
    return NhanVat;
}
void DauGame(SDL_Renderer* &renderer){
    SDL_Texture *BackGround = loadTexture("gb.bmp", renderer);
    SDL_Texture *load;
    SDL_Rect Load;
    SDL_QueryTexture(BackGround, NULL, NULL, &Load.w, &Load.h);
    Load.x = 450;
    Load.y = 300;
    Load.h /= 1;
    Load.w /= 0.5;
    SDL_RenderCopy(renderer, BackGround, NULL, NULL);
    SDL_RenderPresent(renderer);
    for(int i=0; i<15; i++){
        SDL_RenderClear(renderer);
        if(i % 3 == 0)  load = loadTexture("load1.bmp", renderer);
        if(i % 3 == 1)  load = loadTexture("load2.bmp", renderer);
        if(i % 3 == 2)  load = loadTexture("load3.bmp", renderer);
        SDL_RenderCopy(renderer, load, NULL, &Load);
        SDL_RenderPresent(renderer);
        SDL_Delay(500);
    }
}
void Menu(SDL_Renderer *renderer){
    SDL_Texture *BatDau = loadTexture("BatDau.bmp", renderer);
    SDL_Texture *CaiDat = loadTexture("CaiDat.bmp", renderer);
    SDL_Texture *AmThanh = loadTexture("AmThanh.bmp", renderer);
    SDL_Texture *Thoat = loadTexture("Thoat.bmp", renderer);
    SDL_Rect Nut;
    Nut.y = 250;
    Nut.h = 100;
    Nut.w = 100;
    Nut.x = 200;
    SDL_RenderCopy(renderer, BatDau, NULL, &Nut);
    Nut.x = 200 + 200*1;
    SDL_RenderCopy(renderer, CaiDat, NULL, &Nut);
    Nut.x = 200 + 200*2;
    Nut.w = 90;
    SDL_RenderCopy(renderer, AmThanh, NULL, &Nut);
    Nut.x = 200 + 200*3;
    Nut.w = 110;
    SDL_RenderCopy(renderer, Thoat, NULL, &Nut);
}
void Play(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture *NhanVat){
    SDL_Event g_event;
    SDL_Texture *Background = loadTexture("bg.bmp", renderer);
    SDL_RenderCopy(renderer, Background, NULL, NULL);
    int diem = 0;
    SDL_Texture *VatCanTren = loadTexture("CotTren.bmp", renderer);
    SDL_Texture *VatCanDuoi = loadTexture("CotDuoi.bmp", renderer);
    SDL_Rect CotTren[4];
    SDL_Rect CotDuoi[4];

    SDL_Rect NV;
    SDL_QueryTexture(NhanVat, NULL, NULL, &NV.w, &NV.h);
    NV.x = 100;
    NV.y = 100;
    NV.h /= 5;
    NV.w /= 5;
     float tiLe[4] = {1.5, 1.2, 2.5, 1.8};
                                for(int i=0; i<4; i++){
                                    SDL_QueryTexture(VatCanTren, NULL, NULL, &CotTren[i].w, &CotTren[i].h);
                                    CotTren[i].y = 0;
                                    CotTren[i].x = 350 + i*325;
                                    CotTren[i].w /= tiLe[i];
                                    CotTren[i].h /= tiLe[i];

                                    SDL_QueryTexture(VatCanDuoi, NULL, NULL, &CotDuoi[i].w, &CotDuoi[i].h);
                                    CotDuoi[i].y = CotTren[i].h + 150;
                                    CotDuoi[i].x = CotTren[i].x;
                                    CotDuoi[i].w = CotTren[i].w;
                                    CotDuoi[i].h = 600 - CotTren[i].h - 150;
                                }
    do{
         if(SDL_PollEvent(&g_event))
            if(g_event.type == SDL_KEYDOWN){
                cerr<<""<<SDL_GetKeyName(g_event.key.keysym.sym)<<""<<endl;
                switch(g_event.key.keysym.sym){
                    case SDLK_w: NV.y-=25; break;
                    case SDLK_x: NV.y+=25; break;
                }
            }
         SDL_RenderCopy(renderer, Background, NULL, NULL);
         SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
            for(int i=0; i<4; i++){
                CotTren[i].x--;
                CotDuoi[i].x = CotTren[i].x;
                if(CotDuoi[i].x == 100) diem++;
                if(CotTren[i].x <= 0){
                    CotTren[i].x = 1200;
                    srand(time(0));
                    tiLe[i] = rand() %7 + 3;
                    tiLe[i] *= 4.0/10;
                    SDL_QueryTexture(VatCanTren, NULL, NULL, &CotTren[i].w, &CotTren[i].h);
                    CotTren[i].w /= tiLe[i];
                    CotTren[i].h /= tiLe[i];
                    CotDuoi[i].y = CotTren[i].h + 150;
                    CotDuoi[i].x = CotTren[i].x;
                    CotDuoi[i].w = CotTren[i].w;
                    CotDuoi[i].h = 600 - CotTren[i].h - 150;
                }
                 if(NV.x + NV.w - 65 >= CotTren[i].x &&( NV.y + 30 <= CotTren[i].h || NV.y + NV.h - 20 >= CotDuoi[i].y) && NV.x + 10 < CotTren[i].x + CotTren[i].w)
                        return;
                 SDL_RenderCopy(renderer, VatCanTren, NULL, &CotTren[i]);
                 SDL_RenderCopy(renderer, VatCanDuoi, NULL, &CotDuoi[i]);
            }
        NV.y++;
        if(NV.y <=20)
            NV.y = 20;
        if(NV.y >= 550)
            return;
        int i = 0;
        int n = diem;
        do{
        int d = diem % 10;
        diem /= 10;
        SDL_Texture* HienThiDiem = Diem(d, renderer);
        SDL_Rect DIEM;
        SDL_QueryTexture(HienThiDiem, NULL, NULL, &DIEM.w, &DIEM.h);
        DIEM.x = 600 - 75*i;
        DIEM.y = 20;
        DIEM.h /= 2.5;
        DIEM.w /= 2.5;
        SDL_RenderCopy(renderer, HienThiDiem, NULL, &DIEM);
        i++;
        }while(diem > 0);
        diem = n;
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }while(1);
}
int MenuNV( SDL_Texture *NhanVat, SDL_Renderer* &renderer){
    int Kieu = 0;
    SDL_Event g1_event;
    SDL_Texture *BackGround = loadTexture("bg.bmp", renderer);
    SDL_Texture *NhanVat1 = loadTexture("NhanVat1.bmp", renderer);
    SDL_Texture *NhanVat2 = loadTexture("NhanVat2.bmp", renderer);
    SDL_Texture *NhanVat3 = loadTexture("NhanVat3.bmp", renderer);
    SDL_Texture *NhanVat4 = loadTexture("NhanVat4.bmp", renderer);
    SDL_Texture *Click = loadTexture("Click.bmp", renderer);
    SDL_Rect Nut;
    Nut.y = 250;
    Nut.h = 100;
    Nut.w = 100;
    SDL_Rect NV;
    SDL_QueryTexture(NhanVat, NULL, NULL, &NV.w, &NV.h);
    NV.x = 500;
    NV.y = 50;
    NV.h /= 3;
    NV.w /= 3;
    SDL_RenderCopy(renderer, BackGround, NULL, NULL);
    NhanVat = ChonNhanVat(renderer, Kieu);
                Nut.x = 200;
                SDL_RenderCopy(renderer, NhanVat1, NULL, &Nut);
                Nut.x = 200 + 200*1;
                SDL_RenderCopy(renderer, NhanVat2, NULL, &Nut);
                Nut.x = 200 + 200*2;
                SDL_RenderCopy(renderer, NhanVat3, NULL, &Nut);
                Nut.x = 200 + 200*3;
                SDL_RenderCopy(renderer, NhanVat4, NULL, &Nut);
                Nut.y = 300;
                Nut.x = 210 + 200*Kieu;
                SDL_RenderCopy(renderer, Click, NULL, &Nut);
                SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
                SDL_RenderPresent(renderer);
    do{
        if(SDL_PollEvent(&g1_event))
            if(g1_event.type == SDL_KEYDOWN){
                cerr<<""<<SDL_GetKeyName(g1_event.key.keysym.sym)<<""<<endl;
                switch(g1_event.key.keysym.sym){
                    case SDLK_a: Kieu--; if(Kieu == -1)  Kieu = 3; break;
                    case SDLK_d: Kieu++; if(Kieu == 4)   Kieu = 0; break;
                    case SDLK_s:    return Kieu;
                }
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, BackGround, NULL, NULL);

                NhanVat = ChonNhanVat(renderer, Kieu);
                Nut.x = 200;
                SDL_RenderCopy(renderer, NhanVat1, NULL, &Nut);
                Nut.x = 200 + 200*1;
                SDL_RenderCopy(renderer, NhanVat2, NULL, &Nut);
                Nut.x = 200 + 200*2;
                SDL_RenderCopy(renderer, NhanVat3, NULL, &Nut);
                Nut.x = 200 + 200*3;
                SDL_RenderCopy(renderer, NhanVat4, NULL, &Nut);
                Nut.y = 300;
                Nut.x = 210 + 200*Kieu;
                SDL_RenderCopy(renderer, Click, NULL, &Nut);
                SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
                SDL_RenderPresent(renderer);
            }
    }while(1);
}
void EndGame(SDL_Renderer *renderer, int d){
    SDL_Texture *NhanVat;
    switch(d){
        case 0:{
            NhanVat = loadTexture("end1.bmp", renderer);
            break;
        }
        case 1:{
            NhanVat = loadTexture("end2.bmp", renderer);
            break;
        }
        case 2:{
            NhanVat = loadTexture("end3.bmp", renderer);
            break;
        }
        case 3:{
            NhanVat = loadTexture("end4.bmp", renderer);
            break;
        }
    }
    SDL_Rect NV;
    SDL_QueryTexture(NhanVat, NULL, NULL, &NV.w, &NV.h);
    NV.x = 300;
    NV.y = 100;
    NV.h /= 1;
    NV.w /= 1;
    SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
}
void ThoatApp(SDL_Window* &window, SDL_Renderer* &renderer){
    SDL_Texture *BackGround = loadTexture("gb.bmp", renderer);
    SDL_RenderCopy(renderer, BackGround, NULL, NULL);
    SDL_RenderPresent(renderer);
    SDL_Delay(2000);
    quitSDL(window, renderer);   //quit khá»i window
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
SDL_Texture * Diem(int So, SDL_Renderer* &renderer){
    SDL_Texture *NhanVat;
    switch(So){
        case 0:{
            NhanVat = loadTexture("0.bmp", renderer);
            break;
        }
        case 1:{
            NhanVat = loadTexture("1.bmp", renderer);
            break;
        }
        case 2:{
            NhanVat = loadTexture("2.bmp", renderer);
            break;
        }
        case 3:{
            NhanVat = loadTexture("3.bmp", renderer);
            break;
        }
        case 4:{
            NhanVat = loadTexture("4.bmp", renderer);
            break;
        }
        case 5:{
            NhanVat = loadTexture("5.bmp", renderer);
            break;
        }
        case 6:{
            NhanVat = loadTexture("6.bmp", renderer);
            break;
        }
        case 7:{
            NhanVat = loadTexture("7.bmp", renderer);
            break;
        }
        case 8:{
            NhanVat = loadTexture("8.bmp", renderer);
            break;
        }
        case 9:{
            NhanVat = loadTexture("9.bmp", renderer);
            break;
        }
    }
    return NhanVat;
}

