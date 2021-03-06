#include "q1.h"
bool InRange(int value, int min_value, int max_value){
  return (value>=min_value && value<=max_value);
}

bool IsInGrid(int i, int j,const std::vector<std::vector<char> > &grid){
    return (InRange(i,0,grid.size()-1) && InRange(j,0,grid[i].size()-1));
}

void FindAllWordsRecursive(int x, int y, const Dictionary & d,
                            std::vector<std::vector<char> > &grid,
                            std::vector<std::vector<bool> > &visited,
                            std::string current_word,
                            std::set<std::string> &found_words) {
  current_word += grid[x][y];
  if (d.IsWord(current_word)){
    found_words.insert(current_word);
  }

  if (!d.IsPrefix(current_word)) return;

  visited[x][y] = true;
  for (int delta_x : {-1,0,+1}){
    for (int delta_y : {-1,0,+1}){
      const int next_x = x+delta_x;
      const int next_y = y+delta_y;
      if (IsInGrid(next_x,next_y,grid) && !visited[next_x][next_y]) {
        FindAllWordsRecursive(next_x,next_y,d,grid,visited,current_word,found_words);
      }
    }
  }

  visited[x][y] = false;

}



std::set<std::string> FindAllWords(const Dictionary &d, std::vector<std::vector<char> > &grid){
  int n = grid.size();
  std::set<std::string>all_words;
  for (int i = 0 ; i < n; ++i){
      int m = grid[i].size();
      for (int j = 0; j < m; ++j){
        std::vector<std::vector<bool> > visited_positions(n, std::vector<bool> (m,false));
        FindAllWordsRecursive (i,j,d,grid,visited_positions,"",all_words);
      }
    }
    return all_words;
}
