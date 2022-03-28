#include<iostream>
#include "sources/Notebook.hpp"
#include "sources/Direction.hpp"
using namespace std;
using namespace ariel;



int main(){
    Notebook notebook;
    notebook.write(100, 100, 50, ariel::Direction::Horizontal, "abcd");
    cout << notebook.read(100, 99, 51, ariel::Direction::Vertical, 3) << endl;  
    // prints "_b_" (starts at row 99 which is empty; then at row 100 there is "b"; then row 101 is empty again).
    notebook.write(100, 99, 52, ariel::Direction::Vertical, "xyz");
    // throws error because writing the letter y will intersect with the letter c
    notebook.erase(100, 99, 51, ariel::Direction::Vertical, 3);
    // writes ~ instead of _ in line 99, b in line 100 and _ again in line 99
    
    notebook.show(100); // shows the notebook's page in a reasonable way. For example:
    //    98:  _________
    //    99:  ___~_____
    //    100: __a~cd___
    //    101: ___~_____
    //    102: _________
}