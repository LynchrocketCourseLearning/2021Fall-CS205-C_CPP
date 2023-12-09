#include <iostream>
#include <string>
using namespace std;


char c[] = {'2','3','6'};
string s[1010];

string func(int n) {
	int a[50], cnt = 0;
	string t;

	while(n--) {
		a[++cnt] = n%3;
		n/=3;
	}

	for(int i = cnt; i > 0; i--) {
		t += c[a[i]];
	}
	return t;
}
int main() {
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);

    int t, cnt = 0;
    cin >> t;
    while(t--) {
		int n;
		cin >> n;
		s[++cnt] = func(n);
    }
    for(int i = 1; i <= cnt; i++) cout<<s[i]<<endl;

    return 0;
}