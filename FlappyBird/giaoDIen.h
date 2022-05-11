#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


using namespace std;
typedef struct {
    int x;
    int y;
    int h;
    int w;
    float tiLe;
    ToaDo(){
    x = 0;
    y = 0;
    h = 0;
    w  =0;
    }
}ToaDo;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Window";
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
void draw(SDL_Renderer* renderer,int x,int y, char *s, float tiLe, int *cao, int *rong);
void drawChan(SDL_Renderer* renderer,int x,int y, char *s, float tiLe, int *cao, int *rong);
SDL_Texture* loadTexture( string path,SDL_Renderer* renderer );
void GiaoDien(SDL_Renderer* renderer, int x, int y, char *s);
void Menu(int x, int y, SDL_Renderer* renderer, int NhanVat, int d);
void MenuNV(int x, int y, SDL_Renderer* renderer, int k);
void GiaoDienEnd(SDL_Renderer* renderer, int x, int y, int d, int NhanVat);
void Nen(SDL_Renderer* renderer,int x,int y, int cao, int rong);
