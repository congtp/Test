#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

void display(std::vector <std::string> &v){
  for (int i = 0; i < v.size(); i++){
    std::cout << v[i] << std::endl;
  }
}

int my_count_str(std::string const &s, char ch){
  int count{0};
  for(char c:s){
    if(c == ch){
      count++;
    }
  }
  return count;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n, q;
    std::cin >> n >> q;
    std::cin.ignore(); // flush the buffer
    std::vector<std::string> hrml;
    std::vector<std::string> queries;


    // receive the hrml
    for (int i{0}; i < n; i++){
      std::string temp;
      getline(std::cin, temp);
      hrml.push_back(temp);
    }

    // receive the queries
    for (int i{0}; i < q; i++){
      std::string temp;
      getline(std::cin, temp);
      queries.push_back(temp);
    }
    int sPos {0};
    int ePos {0};
    int k{0};
    bool isFindKey = true;
    bool isVectorPushed = false;
    std::string key;
    std::string value;
    std::vector<std::vector<std::pair<string, string>>> tags;
     // To maintain the hierarchy of tags
    std::vector<std::map<std::string, bool>> tag_hierarchy;
    std::map<std::string, bool> current_tag_map;
    for (int i = 0; i < n; i++)
    {
      sPos = 0;
      ePos = 0;
      if(isVectorPushed){
        k++;
        isVectorPushed = false;
      }
      if (hrml[i].substr(0, 2) == "</") {
          // Closing tag: pop the hierarchy level
          tag_hierarchy.pop_back();
          continue;
      }
      while (sPos != -1)
      {
        if(isFindKey){
          // find the first space
          sPos = hrml[i].find_first_of(" \t", sPos);

          // find the second space
          ePos = hrml[i].find_first_of(" \t", sPos + 1);

          if (sPos == std::string::npos || ePos == std::string::npos){
            break;
          }
          if(!isVectorPushed){
            tags.push_back(std::vector<std::pair<std::string, std::string>>());
            isVectorPushed = true;
            // Adding a new tag level to hierarchy
            tag_hierarchy.push_back(current_tag_map);
          }

          // substr need first argument is start position, and next is how much elements from start
          key = hrml[i].substr(sPos + 1, ePos - sPos - 1);
          //std::cout << key << endl;
          isFindKey = false;


          
        }
        else
        {
          // find the first space
          sPos = hrml[i].find_first_of("\"", sPos);

          // find the second space
          ePos = hrml[i].find_first_of("\"", sPos + 1);

          if (sPos == std::string::npos || ePos == std::string::npos){
            break;
          }

          value = hrml[i].substr(sPos + 1, ePos - sPos - 1);
          //std::cout << value << std::endl;
          isFindKey = true;

          // after we find the key, and value, we add its into the map
          tags[k].push_back(make_pair(key, value));
        }
        // new sPos
        sPos = ePos + 1;
      }
    }

    for (int i = 0; i < q; i++){
    int index = my_count_str(queries[i], '.');
    // if index is not present in vector
      // find the key
      // find the '~'
      int sPos = 0;
      bool found = false;
      std::string key;
      sPos = queries[i].find_first_of('~', sPos);
      key = queries[i].substr(sPos + 1, std::string::npos);
      // go through the size of pairs
      for (int j = 0; j < tags[index].size(); j++){
        if(key.compare(tags[index][j].first) == 0){
          std::cout << tags[index][j].second << std::endl;
        }else{
          std::cout << "Not found!" << std::endl;
        }
      }
    }
    

      return 0;
}
