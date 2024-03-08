// 여러개의 알파벳을 입력받으면 같은 알파벳이 몇개인지 출력하는 c++언어 코드를 만들어줘
// 참고로 사용자의 임력을 받는 부분도 만들어줘야해
// 예를 들어서 "hello"를 입력하면 h:1, e:1, l:2, o:1 이렇게 출력되어야해

#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    int count[26] = {0, };
    cin >> input;
    for (int i = 0; i < input.size(); i++) {
        count[input[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            cout << (char)('a' + i) << ": " << count[i] << endl;
        }
    }
    return 0;
}















