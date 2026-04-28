#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string replaceSpace(string s){
        int count = 0;
        int sOldSize = s.size();
        for (char c : s) {
            if (c == ' '){
                count++;
            }
        }
        s.resize(sOldSize + count * 2);
        int sNewSize = s.size();
        for (int i = sOldSize - 1, j = sNewSize - 1; i < j; i--, j--){
            if(s[i] == ' '){
                s[j--] = '0';
                s[j--] = '2';
                s[j] = '%';
            }
            else{
                s[j] = s[i];
            }
        }
        return s;
    }
};

int main() {
    Solution solution;
    string s = "We are happy.";
    cout << solution.replaceSpace(s) << endl; // "We%20are%20happy."
    return 0;
}