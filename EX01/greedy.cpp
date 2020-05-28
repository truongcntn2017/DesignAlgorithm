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

int nPoints;
vector<pair<int, int>> points;
unordered_map<pair<int, int>, int, hash_pair> indices;
pair<int, int> startPoint, endPoint;
int startIndex, endIndex;

void input(string inputFile){
    ifstream fin (inputFile, ios::in);

    fin >> nPoints;
    points.assign(nPoints,pair<int, int>(0,0));
    indices.clear();

    for (int i=0; i<nPoints;++i){
        pair<int, int> temp;
        fin >> temp.first >> temp.second;
        temp.first += X_MAX;
        temp.second += Y_MAX;
        points[i] = temp;
        indices[temp] = i + 1;
    }

    fin.close();
}

bool isPosArea(pair<int, int> a, pair<int, int> b, pair<int, int> c){
    double area = 0;
    area = 0.5*((a.first + b.first)*(a.second - b.second)
     + (b.first + c.first)*(b.second - c.second)
     + (c.first + a.first)*(c.second - a.second));  

     return (area > 0);
}

bool isEqualNumArea(){
    pair<int, int> num;

    for (int i=0; i<points.size();++i){
        if (points[i] != startPoint && points[i] != endPoint){
            (isPosArea(startPoint, points[i], endPoint)) ? num.first++ : num.second++;
        }
    }

    cout<<num.first<<" "<<num.second<<endl;

    return num.first == num.second;
}

void processing(){
    sort(points.begin(), points.end());
    endPoint = points.back();

    for (int i=0; i<nPoints; ++i){ // O(n)
        startPoint = points[i];
        if (isEqualNumArea()){ // O(n)
            startIndex = indices[startPoint];
            endIndex = indices[endPoint];
            break;
        }
    }
}

void output(string outputFile){
    ofstream fout(outputFile, ios::out);
    cout<<"startPoint = "<<startPoint.first<<", "<<startPoint.second<<endl;
    cout<<"endPoint = "<<endPoint.first<<", "<<endPoint.second<<endl;
    cout<<startIndex<<" "<<endIndex<<endl;

    fout<<startIndex<<" "<<endIndex<<endl;
    fout.close();
}

int main(){
    string inputFile = "apples.inp";
    string outputFile = "apples-0.out";

    for (int i=0; i<9; ++i){
        inputFile = "testcase/" + to_string(i) + ".inp";
        outputFile = "output/" + to_string(i) + ".out";
    
        input(inputFile);
        processing();
        output(outputFile);
    }
  
    return 0;
}