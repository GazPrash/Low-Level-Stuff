#include<bits/stdc++.h>
using namespace std;

bool evaluate_zjcj(vector<float> &zj_cj, vector<vector<float>> &A, map<string, int> &basis){
  for (int i =0; i < A[0].size(); i++){
    float z_sum = 0;
    int current_row = 0;
    for (auto it = basis.begin(); it != basis.end(); it++){
      z_sum += it->second * A[current_row][i];
      current_row++;
    }
    zj_cj[i] = z_sum;
  }
}

vector<float> simplex(vector<float> C, vector<vector<float>> &A, vector<float> &b, map<string, int> &basis){
  if (C.size() != A.size()) throw runtime_error("Objective function and the constraints must have the same number of variables.");
  for (float bcap : b){
    if (bcap < 0) throw std::runtime_error("Invalid value for constant vector [b]. very element of b must be positive.");
  }
  
  auto zj_cj = vector<float> (C.size(), -1);
  evaluate_zjcj(zj_cj, A, basis);
  while (1){
    if (all_of(zj_cj.begin(), zj_cj.end(), [](float zc) { return zc >= 0;})){
      if (!all_of(basis.begin(), basis.end(), [](map<string, int> ::iterator itr){return (itr->first[0] == '*');})){
        return b;
      } else {
        cout << "Artificial Variables remain in the basis. No solution exists.\n";
        return {};
      }
    } else {
      float maxzjcj = 0;
      int key_col_ind = -1;
      for (int j = 0; j < zj_cj.size(); j++){
        auto val = zj_cj[j];
        if (maxzjcj < val){
          maxzjcj = val;
          key_col_ind = j;
        }
      }

      vector<float> KEYCOL;
      float Mratio = 0;
      int key_row_ind = -1;
      for (int row =0; row < A.size(); row++){
        KEYCOL.push_back(A[row][key_col_ind]);
        auto ratio = b[row]/A[row][key_col_ind];
        if (ratio < 0) continue;
        if (row == 0){
          Mratio = b[row]/A[row][key_col_ind];
          continue;
        } else{
          if (Mratio < ratio){
            Mratio = ratio
       

          } 
        }


      }






    }
  }

  return {};
}

int main(){
  simplex({}, {{}}, {2, -1});
  
  return 0;
}