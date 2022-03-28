#include <string>

#include "Direction.hpp"
#include <vector>
#include <climits>
using namespace std;



namespace ariel{
    
    class Notebook{
        private:
            // i decided to use vector of vector of string because it is easier to add new rows
            // and to resize the vector of vector of string
            
            vector<vector<string>> pages;
            

          public:
                void write(int page,int row, int col, ariel::Direction direction , const string &input);
                void erase(int page,int row, int col, ariel::Direction direction , int length); 
                string read(int page, int row,int col, ariel::Direction direction , int length);
                void show(int page);

                // when we first create new notebook we initialize it with 100 pages, each page has 100 rows 
                // and each row has 100 colums where each char in the string is a '_'
                Notebook(){
                    for(int i = 0; i < 100; i++){
                        vector<string> page;
                        for(int j = 0; j < 100; j++){
                            string row(100 , '_');
                            
                            page.push_back(row);
                        }
                        pages.push_back(page);
                    }
                }
                    
                
               // disconstructor
                ~Notebook(){
                    pages.clear();
                }

                // the new page function adds a new page to the notebook
                // and fill it with '_'
                void new_row(int page){
                    string row;
                    for(int k = 0; k <100; k++){
                        row.push_back('_');
                    }
                    pages[(uint)page].push_back(row);
                    }

                          
           
      };

}