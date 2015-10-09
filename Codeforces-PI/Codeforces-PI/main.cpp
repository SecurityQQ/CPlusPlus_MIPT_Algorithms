//
//  main.cpp
//  Codeforces-PI
//
//  Created by Alexander Malyshev on 05.08.15.
//  Copyright (c) 2015 Alexander Malyshev. All rights reserved.
//

#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>

using namespace std;



class Range {
public:
  int lhs, rhs;
  Range(int a, int b) {
    lhs = a;
    rhs = b;
  }
  int size() {
    return rhs - lhs + 1;
  }
};

int main(int argc, const char * argv[]) {
  int n, k, a, m;
  
  std::cin>> n, k, a;
  std::cin>>m;;
  std::vector<int> x(m);
  
  
  for (int i = 0; i < m; ++i) {
    int foo;
    std::cin>>foo;
    x.push_back(foo);
  }
  
  std::sort(x.begin(), x.end());
  
  int marked = 0;
  for (int i = 0; i < m - 1; ++i) {
    int v = x[i];
    ++i;
    while((x[i]))
  }
  
  
    return 0;
}
