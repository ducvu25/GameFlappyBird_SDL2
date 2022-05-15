#include "game.h"

using namespace std;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer = NULL;
    SDL_Event g_event;
    initSDL(window, renderer);
    DauGame(renderer);

    int Kieu = 0;
    SDL_Texture *NhanVat;
    NhanVat = ChonNhanVat(renderer, Kieu);
    SDL_Texture *BackGround = loadTexture("bg.bmp", renderer);
    SDL_Rect NV;
    SDL_QueryTexture(NhanVat, NULL, NULL, &NV.w, &NV.h);
    NV.x = 165;
    NV.y = 75;
    NV.h /= 3;
    NV.w /= 3;
    SDL_RenderCopy(renderer, BackGround, NULL, NULL);
    Menu(renderer);
    SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
    SDL_RenderPresent(renderer);
    int d = 0;
    do{
        if(SDL_PollEvent(&g_event))
            if(g_event.type == SDL_KEYDOWN){
                cerr<<""<<SDL_GetKeyName(g_event.key.keysym.sym)<<""<<endl;
                switch(g_event.key.keysym.sym){
                    case SDLK_a: d--;  if(d == -1)  d = 3;  break;
                    case SDLK_d: d++;  if(d == 4)   d = 0;  break;
                    case SDLK_s:{
                        switch(d){
                            case 0:{
                                Play(window, renderer, NhanVat);
                                EndGame(renderer, Kieu);
                                break;
                            }
                            case 1:{
                                Kieu = MenuNV(NhanVat, renderer);
                                NhanVat = ChonNhanVat(renderer, Kieu);
                                break;
                            }
                            case 3:{
                                ThoatApp(window, renderer);
                                break;
                            }
                        }
                        break;
                    }
                }
            NV.x = 165 + 200*d;
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, BackGround, NULL, NULL);
            Menu(renderer);
            SDL_RenderCopy(renderer, NhanVat, NULL, &NV);
            SDL_RenderPresent(renderer);
            }
    }while(1);

  SDL_RenderPresent(renderer);
}
