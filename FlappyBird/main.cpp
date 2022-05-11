#include "giaoDIen.h"

SDL_Event g_event, g2_event, g3_event;
SDL_Surface *g_object = NULL;

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(window, renderer);
    int d = 1, NhanVat = 1;
    draw(renderer, 50, 20, "NhanVat1.bmp", 2, NULL, NULL);
    char s[100];
    strcpy(s, "MuiTen.bmp");
    GiaoDien(renderer, 350, 450, s);
    draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
    Menu(200, 20, renderer, NhanVat, d);
    SDL_RenderPresent(renderer);
    Thoat3:
    do{
        if(SDL_PollEvent(&g_event))
            if(g_event.type == SDL_KEYDOWN){
                cerr<<""<<SDL_GetKeyName(g_event.key.keysym.sym)<<""<<endl;
                switch(g_event.key.keysym.sym){
                    case SDLK_a: d--; break;
                    case SDLK_d: d++; break;
                    case SDLK_s:{
                        switch(d){
                            case 1:{
                                ChoiLai:
                                 ToaDo Chim;
                                Chim.x = 150;
                                Chim.y = 200;
                                ToaDo VatTren[5];
                                ToaDo VatDuoi[5];
                                VatTren[1].x = 500; VatTren[1].tiLe = 2.4;
                                VatTren[1].y = 0;

                                VatTren[2] = VatTren[1];    VatTren[2].x += 300;    VatTren[2].tiLe = 1.9;
                                VatTren[3] = VatTren[2];    VatTren[3].x += 300;    VatTren[3].tiLe = 1.3;
                                VatTren[4] = VatTren[3];    VatTren[4].x += 300;    VatTren[4].tiLe = 2.5;

                                VatDuoi[1].x = 640; VatDuoi[1].tiLe = 3.8 - VatTren[1].tiLe;
                                VatDuoi[1].y = 600;

                                VatDuoi[2] = VatDuoi[1];    VatDuoi[2].x += 300;    VatDuoi[2].tiLe = 3.8 - VatTren[2].tiLe;
                                VatDuoi[3] = VatDuoi[2];    VatDuoi[3].x += 300;    VatDuoi[3].tiLe = 3.8 - VatTren[3].tiLe;
                                VatDuoi[4] = VatDuoi[3];    VatDuoi[4].x += 300;    VatDuoi[4].tiLe = 3.8 - VatTren[4].tiLe;
                                draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
                                switch(NhanVat){
                                    case 1: strcpy(s, "NhanVat1.bmp"); break;
                                    case 2: strcpy(s, "NhanVat2.bmp"); break;
                                    case 3: strcpy(s, "NhanVat3.bmp"); break;
                                    case 4: strcpy(s, "NhanVat4.bmp"); break;
                                }
                                draw(renderer, Chim.x, Chim.y, s, 4, &Chim.h, &Chim.w);
                                int timeGame = 0;

                                do{
                                    if(SDL_PollEvent(&g2_event))
                                        if(g2_event.type == SDL_KEYDOWN){
                                            cerr<<""<<SDL_GetKeyName(g2_event.key.keysym.sym)<<""<<endl;
                                            switch(g2_event.key.keysym.sym){
                                                case SDLK_w: Chim.y -= 40; break;
                                                case SDLK_x: Chim.y += 40; break;
                                            }
                                        }
                                    Chim.y++;
                                    if(Chim.y >= 550){
                                            EndGame:
                                            int k = 1;
                                            GiaoDienEnd(renderer, 300, 400, k, NhanVat);
                                            do{
                                                if(SDL_PollEvent(&g3_event))
                                                    if(g3_event.type == SDL_KEYDOWN){
                                                        cerr<<""<<SDL_GetKeyName(g3_event.key.keysym.sym)<<""<<endl;
                                                        switch(g3_event.key.keysym.sym){
                                                            case SDLK_a: k--; break;
                                                            case SDLK_d: k++; break;
                                                            case SDLK_s: if(k >= 2) goto Thoat3;
                                                                        else        goto ChoiLai;
                                                        }
                                                    if(k == 3)
                                                        k = 1;
                                                    if(k == 0)
                                                        k = 2;
                                                    SDL_RenderClear(renderer);
                                                    draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
                                                    GiaoDienEnd(renderer, 300, 400, k, NhanVat);
                                                    SDL_RenderPresent(renderer);
                                                    }
                                            }while(1);

                                    }
                                    draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
                                    draw(renderer, Chim.x, Chim.y, s, 4, &Chim.h, &Chim.w);
                                        for(int giam=1; giam <= 4; giam++){
                                            VatDuoi[giam].x-=1;
                                            VatTren[giam].x-=1;
                                            if(VatTren[giam].x < 0){
                                                 VatTren[giam].x = 1250;
                                                 VatTren[giam].tiLe = rand() %3 + 5;
                                                 VatTren[giam].tiLe *= 3;
                                                 VatTren[giam].tiLe /= 10;
                                            }
                                            if(VatDuoi[giam].x < 0){
                                                 VatDuoi[giam].x = 1250;
                                                 VatDuoi[giam].tiLe = 3.8 - VatTren[giam].tiLe;
                                            }
                                            draw(renderer, VatTren[giam].x, VatTren[giam].y, "CotTren.bmp", VatTren[giam].tiLe, &VatTren[giam].h, &VatTren[giam].w);
                                            drawChan(renderer, VatDuoi[giam].x, VatDuoi[giam].y, "CotDuoi.bmp", VatDuoi[giam].tiLe, &VatDuoi[giam].h, &VatDuoi[giam].w);
                                            if(Chim.y <= VatTren[giam].h && Chim.x + Chim.w >= VatTren[giam].x && Chim.x + Chim.w <= VatTren[giam].x + VatTren[giam].w )
                                                    goto EndGame;
                                            if(Chim.y + Chim.h >= 600 - VatDuoi[giam].h + 10 && Chim.x + Chim.w >= VatDuoi[giam].x && Chim.x + Chim.w <= VatDuoi[giam].x + VatDuoi[giam].w )
                                                    goto EndGame;

                                        }
                                SDL_RenderPresent(renderer);
                                SDL_RenderClear(renderer);
                                }while(1);
                                break;
                            }
                            case 2:{
                                MenuNV(200, 20, renderer, NhanVat);
                                do{
                                    if(SDL_PollEvent(&g2_event))
                                        if(g2_event.type == SDL_KEYDOWN){
                                            cerr<<""<<SDL_GetKeyName(g2_event.key.keysym.sym)<<""<<endl;
                                            switch(g2_event.key.keysym.sym){
                                                case SDLK_a: NhanVat--; break;
                                                case SDLK_d: NhanVat++; break;
                                                case SDLK_s: goto TienDen;
                                            }
                                        if(NhanVat == 0)
                                            NhanVat = 4;
                                        if(NhanVat == 5)
                                            NhanVat = 1;
                                        SDL_RenderClear(renderer);
                                      //  draw(renderer, 0, 0, "bg2.bmp", 1, NULL, NULL);
                                        MenuNV(200, 20, renderer, NhanVat);
                                        SDL_RenderPresent(renderer);
                                        }
                                }while(1);
                                break;
                            }
                            case 4:{
                                goto Out;
                            }
                        }
                        break;
                    }
                }
                TienDen:
                if(d == 0)
                    d = 4;
                if(d == 5)
                    d = 1;
                Menu(200, 20, renderer, NhanVat, d);
                }
    }while(1);
    Out:
    waitUntilKeyPressed();   //bấm phím bất kì để quit
    quitSDL(window, renderer);   //quit khỏi window
    return 0;
}
