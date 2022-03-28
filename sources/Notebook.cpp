#include "Notebook.hpp"
#include "Direction.hpp"
#include <iostream>
#include <stdexcept>
using namespace std;

using namespace ariel;
const int max_row = 99;
const int max_col = 99;
const int low_ascci = 32;
const int high_ascci = 125;
/*
the write function writes the input string to the page, row and column.
the page, row and colum must be bigger that 0, there are only
100 colums, the number of rows and pages are not limited.
the input string can be any length, but the colum + lenght of the string
is must be under 100. string can be empty, but every char must be
in the range of ascii.


*/
void Notebook::write(int page, int row, int col, Direction direction, const string &input)
{
    if (input == "\n" || input.empty())
    {
        throw invalid_argument("input can't be empty");
    }
    if (page < 0 || row < 0 || col < 0 || col > max_col)
    {
        throw out_of_range("the page, row and colum must be bigger that 0");
    }
    if (((unsigned int)(col) + input.length() > max_row) && (direction == Direction::Horizontal))
    {
        throw out_of_range("the colum + lenght of the string is must be under 100");
    }

    // if the page is bigger than the orignal page we update it
    if (((uint)page > pages.size()))
    {
        pages.resize((uint)page + 1);
        for (int i = 0; i < (uint)1 + input.size(); i++)
        {
            new_row(page);
        }
    }

    // if number of row is bigger than max row , resize row to row + input.size() +1
    if ((uint)row + input.size() > pages[(uint)page].size() && direction == Direction::Vertical)
    {
        for (int i = 0; i < (uint)1 + input.size(); i++)
        {
            new_row(page);
        }
    }

    // if number of row is bigger than the number of rows in the page
    // the page is added with a new row
    if (pages[(unsigned int)page].size() <= (unsigned int)row)
    {
        pages[(unsigned int)page].resize((unsigned int)(row + 1));
    }
    if (direction == Direction::Horizontal)
    {
        if (pages.size() <= (unsigned int)page)
        {
            pages.resize((unsigned int)(page + 1));
        }

        for (int i = 0; i < input.length(); i++)
        {

            if (input[(uint)i] < low_ascci || input[(uint)i] > high_ascci)
            {
                throw out_of_range("only ascii chars are allowed");
            }
            // if there is already char in the position we try to write in throw an exception
            if (pages[(unsigned int)page][(unsigned int)row][(unsigned int)(col + i)] == '_')
            {
                pages[(unsigned int)page][(unsigned int)row][(unsigned int)(col + i)] = input[(unsigned int)i];
            }
            else
            {
                throw out_of_range("there is already char in the position we try to write in");
            }

      
        }
    }
    if (direction == Direction::Vertical)
    {
        if (pages.size() <= (unsigned int)page)
        {
            pages.resize((unsigned int)(page + 1));
        }
        if ((uint)row + input.length() > max_row)
        {
            pages[(uint)page].resize((uint)row + input.length() + 1);
        }
        if (pages[(unsigned int)page].size() <= (unsigned int)row + input.length())
        {
            pages[(unsigned int)page].resize((unsigned int)((unsigned int)row + input.length()));
        }
        for (int i = 0; i < input.length(); i++)
        {
            if (input[(uint)i] < low_ascci || input[(uint)i] > high_ascci)
            {
                throw invalid_argument("only ascii chars are allowed");
            }
            // if there is already char in the position we try to write in throw an exception
            if ('_' == pages[(unsigned int)page][(unsigned int)(row + i)][(unsigned int)(col)])
            {
                pages[(unsigned int)page][(unsigned int)(row + i)][(unsigned int)col] = input[(unsigned int)i];
            }
            else
            {
                throw invalid_argument("there is already char in the position we try to write in");
            }
        }
    }
}

/*
the read function is returning a string, the page, row and colum must be bigger that 0, there are only
100 colums, the number of rows and pages are not limited.
the input string can be any length, but the colum + lenght of the string
is must be under 100. string can be empty, but every char must be
in the range of ascii.



*/
string Notebook::read(int page, int row, int col, Direction direction, int length)
{
    string str;
    if (page < 0 || row < 0 || col < 0 || col > max_col || length < 0)

    {
        throw out_of_range("(read function)the page, row and colum must be bigger that 0");
    }
    if (length == 0)
    {
        return "";
    }
    if ((col + length > max_col + 1) && (direction == Direction::Horizontal))
    {
        throw out_of_range("(read function)the colum + lenght of the string is must be under 100");
    }

    if ((uint)(row + length) > pages[(uint)page].size() && direction == Direction::Vertical)
    {
        for (int i = 0; i < (uint)(1 + length); i++)
        {
            new_row(page);
        }
    }

    if (direction == Direction::Horizontal)
    {

        for (int i = 0; i < length; i++)
        {
            str += pages[(unsigned int)page][(unsigned int)row][(unsigned int)(col + i)];
        }
    }

    else
    {

        for (int i = 0; i < length; i++)
        {
            str += pages[(unsigned int)page][(unsigned int)(row + i)][(unsigned int)col];
        }
    }
    return str;
}

/*
the erase function is erasing the input string from the page, row and column.
the page, row and colum must be bigger than 0, there are only
100 colums, the number of rows and pages are not limited.
the inputstring length must be bigger than 0,
when ever we erase somthing from the notebook we put ~ in the notebook.



*/
void Notebook::erase(int page, int row, int col, Direction direction, int length)
{
    if (page < 0 || row < 0 || col < 0 || col > max_col || length < 0)
    {
        throw out_of_range("(erase function)the page, row and colum must be bigger that 0");
    }

    if (length == 0)
    {
        cout << "the notebook stay the same!" << endl;
    }
    if (col + length > max_row && direction == Direction::Horizontal)
    {
        throw out_of_range("(erase function)the colum + lenght of the string is must be under 100");
    }

    if (direction == Direction::Horizontal)
    {
        for (int i = 0; i < length; i++)
        {
            pages[(unsigned int)page][(unsigned int)row][(unsigned int)(col + i)] = '~';
        }
    }
    else if (direction == Direction::Vertical)
    {
        for (int i = 0; i < length; i++)
        {
            pages[(unsigned int)page][(unsigned int)(row + i)][(unsigned int)col] = '~';
        }
    }
}

/*
the show function need to display our notebook.
the given page must be bigger than 0,
in aim to dispaly all the pages we will use the read function
where the colum and the row is 0 and the length is the size of the page.
*/
void Notebook::show(int page)
{
    if (page < 0)
    {
        throw out_of_range("the page must be bigger than 0");
    }
    if (pages.size() <= page)
    {
        throw out_of_range("the page is not exist");
    }
    for (int i = 0; i < pages[(unsigned int)page].size(); i++)
    {
        for (int j = 0; j < pages[(unsigned int)page][(unsigned int)i].size(); j++)
        {
            cout << pages[(unsigned int)page][(unsigned int)i][(unsigned int)j];
        }
        cout << endl;
    }
}
