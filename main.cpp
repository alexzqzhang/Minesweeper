#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include "TextureManager.h"
#include "Random.h"
using namespace std;
class Tile
{
public:
    int _x;
    int _y;
    int _row;
    int _col;
    bool _isMine;
    bool _isClicked;
    bool _isFlagged;
    int _surroundingMines;
    vector<Tile*> adjacentTiles;
    Tile(int x, int y, bool isMine)
    {
        _x = x;
        _row = y/32;
        _col = x/32;
        _y = y;
        _isMine = isMine;
        _isClicked = false;
        _isFlagged = false;
        _surroundingMines = 0;
    }
    void setAdjacentTiles(vector<vector<Tile>>& board)
    {
        if (this->_x == 0 && this->_y == 0)
        {
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col) + 1]);
            this->adjacentTiles.push_back(&board[(this->_row) + 1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row) + 1][(this->_col) + 1]);
        }
        else if (this->_x == 0 && this->_y == board.size()*32-32)
        {
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col) +1]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)+1]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
        }
        else if (this->_x == board[0].size()*32-32 && this->_y == board.size()*32-32)
        {
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)-1]);
        }
        else if (this->_x == board[0].size()*32-32 && this->_y == 0)
        {
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)+1]);
        }
        else if (this->_x == 0 && this->_y != 0 && this->_y!=board.size()*32-32) {
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row) -1][(this->_col) +1]);
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)+1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)+1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)]);
        }
        else if (this->_y == 0 && this->_x != 0&& this->_x!=board[0].size()*32-32)
        {
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col) + 1]);
            this->adjacentTiles.push_back(&board[(this->_row) ][(this->_col)+1]);
        }
        else if (this->_y == board.size()*32-32 && this->_x != 0 && this->_x!=board[0].size()*32-32)
        {
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col) + 1]);
            this->adjacentTiles.push_back(&board[(this->_row) ][(this->_col)+1]);
        }
        else if (this->_x== board[0].size()*32-32 && this->_y != 0 && this->_y!=board.size()*32-32)
        {
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col) - 1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)]);
        }
        else
        {
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)-1][(this->_col)+1]);
            this->adjacentTiles.push_back(&board[(this->_row)][(this->_col) - 1]);
            this->adjacentTiles.push_back(&board[(this->_row) ][(this->_col)+1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)-1]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)]);
            this->adjacentTiles.push_back(&board[(this->_row)+1][(this->_col)+1]);
        }
    }
};
int SurroundingMines(Tile t, vector<vector<Tile>> board) {
    int count = 0;
    if (t._x == 0 && t._y == 0)
    {
        if (board[(t._row)][(t._col) + 1]._isMine)
            count++;
        if (board[(t._row) + 1][(t._col)]._isMine)
            count++;
        if (board[(t._row) + 1][(t._col) + 1]._isMine)
            count++;
        return count;
    }
    else if (t._x == 0 && t._y == board.size()*32-32)
    {
        if (board[(t._row)][(t._col) +1]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)+1]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)]._isMine)
            count++;
        return count;
    }
    else if (t._x == board[0].size()*32-32 && t._y == board.size()*32-32)
    {
        if (board[(t._row)-1][(t._col)]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        return count;
    }
    else if (t._x == board[0].size()*32-32 && t._y == 0)
    {
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)+1]._isMine)
            count++;
        return count;
    }
    else if (t._x == 0 && t._y != 0 && t._y!=board.size()*32-32) {
        if (board[(t._row)-1][(t._col)]._isMine)
            count++;
        if (board[(t._row) -1][(t._col) +1]._isMine)
            count++;
        if (board[(t._row)][(t._col)+1]._isMine)
            count++;
        if (board[(t._row) + 1][(t._col) + 1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)]._isMine)
            count++;
        return count;
    }
    else if (t._y == 0 && t._x != 0&& t._x!=board[0].size()*32-32)
    {
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)]._isMine)
            count++;
        if (board[(t._row)+1][(t._col) + 1]._isMine)
            count++;
        if (board[(t._row) ][(t._col)+1]._isMine)
            count++;
        return count;
    }
    else if (t._y == board.size()*32-32 && t._x != 0 && t._x!=board[0].size()*32-32)
    {
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)+1]._isMine)
            count++;
        if (board[(t._row)][(t._col) +1 ]._isMine)
            count++;
        return count;
    }
    else if (t._x== board[0].size()*32-32 && t._y != 0 && t._y!=board.size()*32-32)
    {
        if (board[(t._row)-1][(t._col)]._isMine)
            count++;
        if (board[(t._row) -1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)]._isMine)
            count++;
        return count;
    }
    else
    {
        if (board[(t._row)-1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row) -1][(t._col)]._isMine)
            count++;
        if (board[(t._row)-1][(t._col)+1]._isMine)
            count++;
        if (board[(t._row)][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)][(t._col)+1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)-1]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)]._isMine)
            count++;
        if (board[(t._row)+1][(t._col)+1]._isMine)
            count++;
        return count;
    }

}
vector<vector<Tile>> loadBoard(int cols, int rows, int mines)
{
    map <int, bool> mineList;
    int count = 0;
    while (count<mines)
    {
        int x = Random::Int(0,rows*cols-1);
        if(mineList.find(x)==mineList.end())
        {
            mineList.emplace(x,true);
            count++;
        }
    }
    int num = 0;
    vector<vector<Tile>> board;
    for(int i = 0; i < rows; i++)
    {
        vector<Tile> row;
        for(int j = 0; j < cols; j++)
        {
            bool b = false;
            if(mineList.find(num)!=mineList.end())
            {
                b = true;
            }
            row.push_back(Tile(32*j,32*i,b));
            num++;
        }
        board.push_back(row);
    }
    return board;
}
vector<vector<Tile>> loadBoard(string filename, int rows, int cols)
{
    vector<vector<Tile>> board;
    ifstream someFile("boards/"+filename);
    if (someFile.is_open())
    {
        for(int j = 0; j < rows; j++)
        {
            string line;
            getline(someFile, line);
            vector<Tile> tiles;
            for (unsigned int i = 0; i < line.size(); i++)
            {
                if (line[i] == '1')
                    tiles.push_back(Tile(i*32, j*32, true));
                else
                    tiles.push_back(Tile(i*32, j*32, false));
            }
            board.push_back(tiles);
        }
    }
    return board;
}

void RevealTile(vector<vector<Tile>>& board, int row, int col)
{
    if(row < 0 || row > board.size() || col < 0 || col > board[0].size())
        return;
    if(board[row][col]._isClicked||board[row][col]._isFlagged||board[row][col]._isMine)
        return;
    board[row][col]._isClicked = true;
    if (board[row][col]._surroundingMines==0)
    {
        for(unsigned int i = 0; i<board[row][col].adjacentTiles.size(); i++)
        {
            RevealTile(board,(*board[row][col].adjacentTiles[i])._row , (*board[row][col].adjacentTiles[i])._col);
        }
        /*RevealTile(board, row-1, col -1);
        RevealTile(board, row-1, col );
        RevealTile(board, row-1, col +1);
        RevealTile(board, row, col -1);
        RevealTile(board, row, col +1);
        RevealTile(board, row+1, col -1);
        RevealTile(board, row+1, col);
        RevealTile(board, row+1, col +1);
        for(int i = -1; i<=1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                if(i == 0 && j == 0)
                    continue;
                RevealTile(board, row+i, col+j);
            }
        }
         */
    }
}
bool checkWin(vector<vector<Tile>>& board)
{
    bool win = true;
    for(unsigned int i = 0; i<board.size(); i++)
    {
        for(unsigned int k = 0; k< board[0].size(); k++)
        {
            if(board[i][k]._isMine)
                continue;
            if(board[i][k]._isClicked==false)
            {
                win = false;
                break;
            }
        }
        if(win == false)
            break;
    }
    return win;
}
int main() {
    bool gameOver = false;
    bool debug = false;
    bool win = false;
    int cols;
    int rows;
    int mines;
    ifstream someFile("boards/config.cfg");
    if (someFile.is_open()) {
        someFile>>cols;
        someFile>>rows;
        someFile>>mines;
    }
    int mineCount = mines;
    vector<vector<Tile>> board = loadBoard(cols,rows,mines);
    for(int i = 0; i < rows; i++)
    {
        for(int k = 0; k < cols; k++)
        {
            board[i][k]._surroundingMines = SurroundingMines(board[i][k],board);
            board[i][k].setAdjacentTiles(board);
        }
    }
    int width = cols*32;
    int height = rows*32+100;

    sf::RenderWindow window(sf::VideoMode(width, height), "Minesweeper");
    sf::Sprite debugButton(TextureManager::GetTexture("debug"));
    sf::Sprite test1btn(TextureManager::GetTexture("test_1"));
    sf::Sprite test2btn(TextureManager::GetTexture("test_2"));
    sf::Sprite test3btn(TextureManager::GetTexture("test_3"));
    sf::Sprite face_happy(TextureManager::GetTexture("face_happy"));
    sf::Sprite face_lose(TextureManager::GetTexture("face_lose"));
    sf::Sprite face_win(TextureManager::GetTexture("face_win"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite digitNeg(TextureManager::GetTexture("digits"));
    digitNeg.setTextureRect(sf::IntRect (210,0,21,32));
    digitNeg.setPosition(0, rows*32);

    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    vector<sf::Sprite> numbers;
    sf::Sprite number_1(TextureManager::GetTexture("number_1"));
    numbers.push_back(number_1);
    sf::Sprite number_2(TextureManager::GetTexture("number_2"));
    numbers.push_back(number_2);
    sf::Sprite number_3(TextureManager::GetTexture("number_3"));
    numbers.push_back(number_3);
    sf::Sprite number_4(TextureManager::GetTexture("number_4"));
    numbers.push_back(number_4);
    sf::Sprite number_5(TextureManager::GetTexture("number_5"));
    numbers.push_back(number_5);
    sf::Sprite number_6(TextureManager::GetTexture("number_6"));
    numbers.push_back(number_6);
    sf::Sprite number_7(TextureManager::GetTexture("number_7"));
    numbers.push_back(number_7);
    sf::Sprite number_8(TextureManager::GetTexture("number_8"));
    numbers.push_back(number_8);
    sf::Sprite tile_hidden(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite tile_revealed(TextureManager::GetTexture("tile_revealed"));

    debugButton.setPosition((cols*32/2)+96, rows*32);
    test1btn.setPosition((cols*32/2)+160, rows*32);
    test2btn.setPosition((cols*32/2)+224, rows*32);
    test3btn.setPosition((cols*32/2)+288, rows*32);
    face_happy.setPosition((cols*32/2)-32,rows*32);
    face_win.setPosition((cols*32/2)-32,rows*32);
    face_lose.setPosition((cols*32/2)-32,rows*32);

    while(window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    int leftcol = localPosition.x/32;
                    int leftrow = localPosition.y/32;
                    if (leftcol >= 0 && leftcol < cols && leftrow >= 0 && leftrow < rows&&!gameOver)
                    {
                        if(!board[leftrow][leftcol]._isFlagged) {
                            RevealTile(board, leftrow, leftcol);
                            if (board[leftrow][leftcol]._isMine) {
                                gameOver = true;
                            }
                        }
                    }
                    if(localPosition.x >=(cols*32/2)-32 && localPosition.x <=(cols*32/2)+96 && localPosition.y >= rows*32 && localPosition.y <= height-36)
                    {
                        //restart button
                        gameOver = false;
                        board = loadBoard(cols, rows, mines);
                        for(int i = 0; i < rows; i++)
                        {
                            for(int k = 0; k < cols; k++)
                            {
                                board[i][k]._surroundingMines = SurroundingMines(board[i][k],board);
                                board[i][k].setAdjacentTiles(board);
                            }
                        }
                        mineCount = mines;
                        win = false;
                        debug = false;
                        //clear variables
                    }
                    if(localPosition.x >=(cols*32/2)+96 && localPosition.x <=(cols*32/2)+160 && localPosition.y >= rows*32 && localPosition.y <= height-36)
                    {
                        //debug button
                        if(debug == false)
                            debug = true;
                        else
                            debug = false;
                    }

                    if(localPosition.x >=(cols*32/2)+160 && localPosition.x <=(cols*32/2)+224 && localPosition.y >= rows*32 && localPosition.y <= height-36)
                    {
                        //test1 button
                        board = loadBoard("testboard1.brd", rows, cols);
                        mineCount = 0;
                        for(int i = 0; i < rows; i++)
                        {
                            for(int k = 0; k < cols; k++)
                            {
                                if(board[i][k]._isMine)
                                    mineCount++;
                                board[i][k]._surroundingMines = SurroundingMines(board[i][k],board);
                                board[i][k].setAdjacentTiles(board);
                            }
                        }
                        gameOver = false;
                        win = false;
                        debug = false;
                    }
                    if(localPosition.x >=(cols*32/2)+224 && localPosition.x <=(cols*32/2)+288 && localPosition.y >= rows*32 && localPosition.y <= height-36)
                    {
                        //test2 button
                        mineCount = 0;
                        board = loadBoard("testboard2.brd", rows, cols);
                        for(int i = 0; i < rows; i++)
                        {
                            for(int k = 0; k < cols; k++)
                            {
                                if(board[i][k]._isMine)
                                    mineCount++;
                                board[i][k]._surroundingMines = SurroundingMines(board[i][k],board);
                                board[i][k].setAdjacentTiles(board);
                            }
                        }
                        gameOver = false;
                        win = false;
                        debug = false;
                    }
                    if(localPosition.x >=(cols*32/2)+288 && localPosition.x <=(cols*32/2)+352 && localPosition.y >= rows*32 && localPosition.y <= height-36)
                    {
                        //test3 button
                        mineCount = 0;
                        board = loadBoard("testboard3.brd", rows, cols);
                        for(int i = 0; i < rows; i++)
                        {
                            for(int k = 0; k < cols; k++)
                            {
                                if(board[i][k]._isMine)
                                    mineCount++;
                                board[i][k]._surroundingMines = SurroundingMines(board[i][k],board);
                                board[i][k].setAdjacentTiles(board);
                            }
                        }
                        gameOver = false;
                        win = false;
                        debug = false;
                    }
                }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    int rightcol = localPosition.x/32;
                    int rightrow = localPosition.y/32;
                    if (gameOver)
                        continue;
                    if (rightcol >= 0 && rightcol < cols && rightrow >= 0 && rightrow < rows)
                    {
                        if (!board[rightrow][rightcol]._isClicked)
                        {
                            board[rightrow][rightcol]._isFlagged = !board[rightrow][rightcol]._isFlagged;
                            if (board[rightrow][rightcol]._isFlagged)
                            {
                                flag.setPosition(rightcol * 32, rightrow * 32);
                                window.draw(flag);
                                mineCount--;
                            }
                            else
                            {
                                mineCount++;
                            }

                        }
                    }
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(debugButton);
        window.draw(test1btn);
        window.draw(test2btn);
        window.draw(test3btn);
        window.draw(face_happy);
        if (gameOver)
            window.draw(face_lose);
        else if(win)
            window.draw(face_win);

        for(int i = 0; i < rows; i++)
        {
            for(int k = 0; k < cols; k++)
            {
                tile_hidden.setPosition(k*32,i*32);
                window.draw(tile_hidden);
                if(debug&&!gameOver)
                {
                    if(board[i][k]._isMine)
                    {
                        //tile_hidden.setPosition(k*32,i*32);
                        //window.draw(tile_hidden);
                        mine.setPosition(board[i][k]._x, board[i][k]._y);
                        window.draw(mine);
                        continue;
                    }
                }
                if (board[i][k]._isFlagged&&!gameOver)
                {
                    flag.setPosition(k*32,i*32);
                    window.draw(flag);
                    continue;
                }
                if(gameOver)
                {
                    if (board[i][k]._isMine)
                    {
                        tile_revealed.setPosition(k * 32, i * 32);
                        window.draw(tile_revealed);
                        mine.setPosition(k * 32, i * 32);
                        window.draw(mine);
                        continue;
                    }
                }
                if(checkWin(board))
                {
                    win = true;
                    mineCount = 0;
                    for(int i = 0; i< rows; i++)
                    {
                        for(int j = 0; j<cols; j++)
                        {
                            if(board[i][j]._isMine)
                            {
                                board[i][j]._isFlagged = true;
                                board[i][j]._isMine = false;
                            }
                        }
                    }
                    continue;
                }
                if(board[i][k]._isClicked)
                {
                    tile_revealed.setPosition(k * 32, i * 32);
                    window.draw(tile_revealed);
                    if(board[i][k]._surroundingMines!=0)
                    {
                        numbers[board[i][k]._surroundingMines-1].setPosition(k*32, i*32);
                        window.draw( numbers[board[i][k]._surroundingMines-1]);
                    }
                    continue;
                }
                tile_hidden.setPosition(k*32,i*32);
                window.draw(tile_hidden);
            }
        }

        if (mineCount < 0)
        {
            window.draw(digitNeg);
        }
        int temp = mineCount;
        for(int i = 0; i<=2; i++)
        {
            int dig = abs(temp) % 10;
            digits.setTextureRect(sf::IntRect (21*dig, 0, 21, 32));
            digits.setPosition(63-21*i,32*rows);
            window.draw(digits);
            temp /= 10;
        }

        window.display();
    }
    TextureManager::Clear();
}