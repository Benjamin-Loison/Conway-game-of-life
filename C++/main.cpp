#include <iostream>
#include <random>
#include <ctime>
#include <sys/time.h>
//#include <windows.h>
#include <SDL.h>
#define TABLE_LINES WINDOW_HEIGHT // or cst
#define TABLE_COLUMNS WINDOW_WIDTH
#define WINDOW_WIDTH 1900
#define WINDOW_HEIGHT 1000
using namespace std;

char deadCell = '.';
string aliveCell = "@";
bool table[TABLE_LINES][TABLE_COLUMNS], newTable[TABLE_LINES][TABLE_COLUMNS];

void live()
{
    // SWITCH AND CLEAR
    for(unsigned int line = 0; line < TABLE_LINES; line++)
    {
        for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
        {
            table[line][column] = newTable[line][column];
            newTable[line][column] = 0;
        }
    }
    for(unsigned int line = 0; line < TABLE_LINES; line++)
    {
        for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
        {
            unsigned short aliveNeighboors = 0;
            for(unsigned int detectLine = line - 1; 0 <= detectLine && detectLine <= line + 1; detectLine++)
            {
                for(unsigned int detectColumn = column - 1; 0 <= detectColumn && detectColumn <= column + 1; detectColumn++)
                {
                    if(detectLine != line || detectColumn != column)
                        if(table[detectLine][detectColumn])
                        {
                            //cout << line << " " << detectLine << " " << column << " " << detectColumn << endl;
                            aliveNeighboors++;
                        }
                }
            }
            if(aliveNeighboors == 2 || aliveNeighboors == 3)
            {
                if(table[line][column]) // manage spawn of new cells ?
                    newTable[line][column] = 1;
                else if(aliveNeighboors == 3)
                    if(!table[line][column])
                        newTable[line][column] = 1;
            }
        }
    }
}

void initRandom()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << mslong << endl;
    srand(mslong);
}

void generateWithFrequency(unsigned short frequency)
{
    for(unsigned int line = 0; line < TABLE_LINES; line++)
    {
        for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
        {
            initRandom();
            unsigned short randomInt = rand() % frequency; // best way
            if(randomInt == frequency - 1)
            {
                newTable[line][column] = 1;
            }
        }
    }
}

void generateSpecifiedNumberOfPoints()
{

}

void generateManual()
{
    //newTable[5][5] = 1;
}

int main(int argc, char** argv)
{
    bool newPlate = true;
    if(newPlate)
    {
        initRandom();
        //generateManual();
        generateWithFrequency(50);
    }
    else
    {
        // read file
    }

    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP); // or SDL_WINDOW_FULLSCREEN_DESKTOP

    while(true)
    {
        live();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        for(unsigned int line = 0; line < TABLE_LINES; line++)
        {
            for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
            {
                if(table[line][column])
                    SDL_RenderDrawPoint(renderer, column, line);
            }
        }

        SDL_RenderPresent(renderer);
        if(SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
