#include<bits/stdc++.h>
using namespace std;

vector<string> split(string str, const char c) {
    replace(str.begin(), str.end(), c, ' ');
    istringstream iss(str);

    vector<string> ret;
    while (true) {
        string buf;
        iss >> buf;
        if (buf == "") break;
        ret.push_back(buf);
    }
    return ret;
}