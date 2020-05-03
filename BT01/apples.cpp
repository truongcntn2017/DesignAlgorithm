#include <bits/stdc++.h>

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
pair<int, int> firstPoint, lastPoint;
int firstIndex;
int lastIndex;

void input(){
    ifstream fin ("apples.inp", ios::in);

    fin >> nPoints;
    for (int i=0; i<nPoints;++i){
        pair<int, int> temp;
        fin >> temp.first >> temp.second;
        points.push_back(temp);
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
        if (points[i] != firstPoint && points[i] != lastPoint){
            (isPosArea(firstPoint, points[i], lastPoint)) ? num.first++ : num.second++;
        }
    }

    return num.first == num.second;
}

void processing(){
    sort(points.begin(), points.end());
    lastPoint = points.back();

    for (int i=0; i<nPoints; ++i){
        firstPoint = points[i];
        if (isEqualNumArea()){
            firstIndex = indices[firstPoint];
            lastIndex = indices[lastPoint];
            break;
        }
    }
}

void output(){
    ofstream fout("apples.out", ios::out);

    fout<<firstIndex<<" "<<lastIndex<<endl;
    fout.close();
}

int main(){
    input();
    processing();
    output();
  
    return 0;
}