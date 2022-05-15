#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>

using namespace std;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Window";

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture* loadTexture( string path,SDL_Renderer* renderer );
SDL_Texture* ChonNhanVat(SDL_Renderer* renderer, int d);
void DauGame(SDL_Renderer* &renderer);
void Menu(SDL_Renderer *renderer);
int MenuNV(SDL_Texture *NhanVat, SDL_Renderer* &renderer);
void Play(SDL_Window* &window, SDL_Renderer* &renderer, SDL_Texture *NhanVat);
void EndGame(SDL_Renderer *renderer, int NhanVat);
void ThoatApp(SDL_Window* &window, SDL_Renderer* &renderer);
SDL_Texture * Diem(int So, SDL_Renderer* &renderer);
