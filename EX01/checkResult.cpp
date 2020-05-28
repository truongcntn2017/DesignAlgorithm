#include <bits/stdc++.h>
#define X_MAX 1000000
#define Y_MAX 1000000

using namespace std;

struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    } 
}; 

typedef pair<double, pair<int, int>> corner;

int nPoints;
vector<pair<int, int>> points;
unordered_map<pair<int, int>, int, hash_pair> indices;
pair<int, int> startPoint, endPoint;

int startIndex, endIndex;

void input(string inputFile){
    ifstream fin (inputFile, ios::in);

    fin >> nPoints;
    for (int i=0; i<nPoints;++i){
        pair<int, int> temp;
        fin >> temp.first >> temp.second;
        temp.first += X_MAX;
        temp.second += Y_MAX;
        points.push_back(temp);
        indices[temp] = i + 1;
    }

    fin.close();
}

double calArea(pair<int, int> a, pair<int, int> b, pair<int, int> c){
    double area = 0;
    area = 0.5*((a.first + b.first)*(a.second - b.second)
     + (b.first + c.first)*(b.second - c.second)
     + (c.first + a.first)*(c.second - a.second));  

    return area;
}

double distance(pair<int, int> a, pair<int, int> b){
    return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

bool isPosArea(pair<int, int> a, pair<int, int> b, pair<int, int> c){ 
     return (calArea(a, b, c) > 0);
}

bool isEqualNumArea(){
    pair<int, int> num;

    for (int i=0; i<points.size();++i){
        if (points[i] != startPoint && points[i] != endPoint){
            (isPosArea(startPoint, points[i], endPoint)) ? num.first++ : num.second++;
        }
    }

    // cout<<"startPoint = "<<startPoint.first<<", "<<startPoint.second<<endl;
    // cout<<"endPoint = "<<endPoint.first<<", "<<endPoint.second<<endl;
    // cout<<"num = "<<num.first<<" "<<num.second<<endl;

    return num.first == num.second;
}

bool check(){
    startPoint = points[startIndex-1];
    endPoint = points[endIndex-1];

    return isEqualNumArea();
}

void output(string outputFile){
    ifstream fin(outputFile, ios::out);

    fin>>startIndex>>endIndex;
    fin.close();
}


int main(int argc, char** argv){
    string inputFile = "apples.inp";
    string outputFile = "apples-0.out";

    for (int i=0; i<10; ++i){
        inputFile = "testcase/" + to_string(i) + ".inp";
        outputFile = argv[1] + to_string(i) + ".out";

        input(inputFile);
        output(outputFile);
        if (check()){
            cout<<"True"<<endl;
        }
        else{
            cout<<"False"<<endl;
        }

        points.clear();
        indices.clear();
    }
    
    return 0;
}