#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <sys/time.h>
#include <windows.h>
#define TABLE_LINES 520
#define TABLE_COLUMNS 1560
using namespace std;

char deadCell = '.';
string aliveCell = "@";
ofstream file;
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

void write()
{
    file.open("life.txt");
    for(unsigned int line = 0; line < TABLE_LINES; line++)
    {
        for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
        {
            if(table[line][column] == 0)
                file << deadCell;
            else
                file << aliveCell;
        }
        if(line != TABLE_LINES - 1)
            file << '\n';
    }
    file.close();
}

void initRandom()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long long mslong = (long long) tp.tv_sec * 1000 + tp.tv_usec / 1000;
    srand(mslong);
}

void generateWithFrequency(unsigned short frequency)
{
    for(unsigned int line = 0; line < TABLE_LINES; line++)
    {
        for(unsigned int column = 0; column < TABLE_COLUMNS; column++)
        {
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

int main()
{
    unsigned int screen = 0;
    bool newPlate = true;
    if(newPlate)
    {
        initRandom();
        //generateManual();
        generateWithFrequency(2);
    }
    else
    {
        // read file
    }
    string input = "";
    while(true)
    {
        live();
        write();
        cout << screen << endl;
        screen++;
        Sleep(2000);
    }
    return 0;
}
