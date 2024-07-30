#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

struct Movie {
    int id;
    string director;
    string actor;
    string genre;
};

int main() {
    
    ifstream infile("input.txt");
    if(!infile) 
    {
        cerr << "Unable to open file";
        exit(1);
    }
    
    int N;
    infile >> N;
    vector<Movie> movies(N);

    // 读取电影信息
    for (int i = 0; i < N; ++i) {
        infile >> movies[i].id >> movies[i].director >> movies[i].actor >> movies[i].genre;
    }

    char M;
    string K;
    infile >> M >> K;

    vector<int> result;

    // 根据查询条件筛选电影
    for (const auto& movie : movies) {
        if ((M == 'D' && movie.director == K) ||
            (M == 'A' && movie.actor == K) ||
            (M == 'T' && movie.genre == K)) {
            result.push_back(movie.id);
        }
    }

    // 输出结果
    if (result.empty()) {
        cout << "-1" << endl;
    } else {
        sort(result.begin(), result.end());
        for (size_t i = 0; i < result.size(); ++i) {
            if (i > 0) cout << " ";
            cout << result[i];
        }
        cout << endl;
    }

    return 0;
}