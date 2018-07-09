////////////////////////////////////////////////////////////////////////////////
// board.cc : Game of Tic Tac Toe
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// ALL YOUR WORK SHOULD BE DONE IN THIS FILE
//
// Student Name: Ahmad Rangeen
// Student ID: 916775826
// Student Email: arangeen@mail.sfsu.edu
////////////////////////////////////////////////////////////////////////////////


#include "board.h"

#include <cstdlib>   // std::exit and EXIT_FAILURE macro
#include <iostream>  // std::cout, std::cin, std::cerr, std::endl
#include <stdlib.h>
using namespace std;

// Constructor
//   size: the size of the grid (i.e. size x size)
// 1. Verify that size is >= 3 and <= 10. If not, print an error message to
//    cerr and call exit(EXIT_FAILURE) to terminate the program.
// 2. Dynamically allocate the 2D array named grid_. If there are any
//    allocation errors (e.g. bad_alloc exception), print an error
//    message to cerr and call exit(EXIT_FAILURE) to terminate the program.
// 3. Initialize all the values within the 2D array to be ' ' (a space).

Board::Board(int size) 
{
    // Your code goes here
    size_ = size; 
    if (size_ < 3 || size_ > 10)
    {
        cerr << "size must be >=3 or <= 10" << endl; 
        exit(EXIT_FAILURE); 
    }
    
    
    try{
        grid_ = new char*[size_];
        for (int i = 0; i < size_; ++i )
        {
            grid_[i] = new char[size_];
            for(int j = 0; j < size_; ++j)
            {
                grid_[i][j] = ' ';
            }
            
        }
        
        
    }
    catch(const bad_alloc&){
        cerr << "size must be >=3 or <=10" << endl;
        exit(EXIT_FAILURE);
    }
    
       
}
// end of Board(int size)


// Destructor
// 1. De-allocate the 2D array
Board::~Board()
{
    // Your code goes here
    for (int i = 0; i < size_; ++i)
        {
            delete grid_[i];    
        }
    delete [] grid_;
     
}

// Prints the current board to the screen
// The board should have numbers to indicate the rows and columns, and the
// current values at each position should be displayed (i.e. blank, X, or O).
// This should look something like this (for size=3):
//    0   1   2
//  +---+---+---+
// 0| X |   | O |
//  +---+---+---+
// 1| O |   | X |
//  +---+---+---+
// 2|   | X | O |
//  +---+---+---+
void Board::Display() 
{
    // Your code goes here
    for (int i = 0; i < size_; ++i)
    {
        cout << " " << i;
    }
    cout<< endl << " +";
    for(int i = 0; i < size_; ++i)
    {
        cout << "---+"; 
    }
    cout << endl; 
    
    for (int i = 0; i < size_; ++i)
    {
        cout << i <<"|";
        for (int j = 0; j < size_; ++j)
        {
            cout <<" "<< grid_[i][j] << "|"; 
        }
        cout << endl << " +";
        for (int j = 0; j < size_; ++j)
        {
            cout << "---+"; 
        }
        cout << endl;
        
    }
    
}

// Marks the player in the given row and column and returns true on success.
// If the position is invalid or already occupied, print an error to cerr and
// return false.
bool Board::Mark(Player player, int row, int column) {
    // Your code goes here
    if(row < 0 || row >= size_ || column < 0 || column >= size_)
    {
        cerr << "Invalid row or column. Try it again." << endl;
        return false;
    }
    
    if(grid_[row][column] != " ")
    {
        cerr << "The position is already occupied. Try it again." << endl;
        return false;
    }
    
    switch (player)
    {
        case Player::X: 
            grid_[row][column] = 'X';
            break;
        case Player::O:
            grid_[row][column] = 'O';
            break;
    }
    return true;
    
}

// Returns the winner if they have won, or indicates if the game is still in
// progress or ended in a stalemate (see enum class Winner for details).
Winner Board::CheckWinner() {
    // Your code goes here
    
    int num_spaces = 0; 
    
    /*
     Check for ROW wins 
     */
    
    for (int i = 0; i < size_; ++i)
    {
        int num_x = 0; 
        int num_o = 0;
        
        for (int j = 0; j < size_; ++j)
        {
            if(grid_[i][j] == 'X')
            {
                ++num_x;
            }
            else if (grid_[i][j] == 'O')
            {
                ++num_o;
            }
            else
            {
                ++num_spaces;
            }
        }
        
        if(num_x == size_)
        {
            return Winner::X;
        }else if(num_o == size_)
        {
            return Winner::O;
        }
        
    }
    
    
    /*
     Check for column wins 
     */
    for (int j = 0; j < size_; ++j)
    {
        int num_x = 0; 
        int num_o = 0; 
        
        for(int i = 0; i < size_; ++i)
        {
            if(grid_[i][j] == 'X')
            {
                ++num_x;
            }
            else if(grid_[i][j] == 'O')
            {
                ++num_o;
            }
           
        }
        
        if(num_x == size_)
        {
            return Winner::X;
        }
        else if(num_o == size_)
        {
            return Winner::O;
        }
    }
    
    /*
     * Check for diagonal wins 
     */
    int num_x_1 = 0, num_x_2 = 0, num_o_1 = 0, num_o_2 = 0;
    for (int i = 0; i < size_; ++i) {
        if (grid_[i][i] == 'X') {
            ++num_x_1;
        } else if (grid_[i][i] == 'O') {
            ++num_o_1;
        }
        if (grid_[i][(size_-1)-i] == 'X') {
            ++num_x_2;
        } else if (grid_[i][(size_-1)-i] == 'O') {
            ++num_o_2;
        }
        if (num_x_1 == size_ || num_x_2 == size_) {
            return Winner::X;
        } else if (num_o_1 == size_ || num_o_2 == size_) {
            return Winner::O;
        }
    }
    // Check for stalemate
    if (num_spaces == 0) {
        return Winner::STALEMATE;
    }
    return Winner::STILL_PLAYING;
    
    
    
}
