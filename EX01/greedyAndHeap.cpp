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
    // cout<<num.first<<" "<<num.second<<endl;

    return num.first == num.second;
}
double getCorner(pair<int, int> a, pair<int, int> b, pair<int, int> c){
    double res = 0;
    double edgeC = distance(a, b);
    double edgeA = distance(b, c);
    double edgeB = distance(a, c);
    res = acos((edgeA*edgeA + edgeC*edgeC - edgeB*edgeB )/(2*edgeA*edgeC));

    return res;
}

void processing(){
    priority_queue<corner, vector<corner>, greater<corner>> posHeap; //
    priority_queue<corner, vector<corner>, greater<corner>> negHeap; //

    sort(points.begin(), points.end()); // x , y
    endPoint = points.back(); // 
    startPoint = points.front(); //

    for (pair<int, int> point: points){ // (O(N))
        if (point != startPoint && point != endPoint){
            double corner = getCorner(startPoint, endPoint, point);
            // cout<<"corner"<<corner<<endl;

            if (isPosArea(startPoint, point, endPoint) > 0){ //O(log(n))
                posHeap.push(make_pair(corner, point));
            }
            else{
                negHeap.push(make_pair(corner, point));
            }
        }
    }

    while (posHeap.size() != negHeap.size()){
        // isEqualNumArea();
        // cout<<"size "<<posHeap.size()<<", "<<negHeap.size()<<endl;
        // cout<<"startPoint = "<<startPoint.first<<", "<<startPoint.second<<endl;
        // cout<<"endPoint = "<<endPoint.first<<", "<<endPoint.second<<endl;

        if (posHeap.size() > negHeap.size()){
            negHeap.push(make_pair(acos(-1), startPoint)); 
            startPoint = posHeap.top().second;
            // cout<<"corner = "<<posHeap.top().first<<endl;
            posHeap.pop();  
        }
        else{
            posHeap.push(make_pair(acos(-1), startPoint)); 
            startPoint = negHeap.top().second;
            negHeap.pop();
        }
    }
    
    // isEqualNumArea();
    // cout<<"startPoint = "<<startPoint.first<<", "<<startPoint.second<<endl;
    // cout<<"endPoint = "<<endPoint.first<<", "<<endPoint.second<<endl;
    startIndex = indices[startPoint];
    endIndex = indices[endPoint];
}

void output(string outputFile){
    ofstream fout(outputFile, ios::out);

    fout<<startIndex<<" "<<endIndex<<endl;
    fout.close();
}

int main(){
    string inputFile = "apples.inp";
    string outputFile = "apples-1.out";

    for (int i=0; i<9; ++i){
        inputFile = "testcase/" + to_string(i) + ".inp";
        outputFile = "greedyAndHeapOutput/" + to_string(i) + ".out";
    
        input(inputFile);
        processing();
        output(outputFile);
    }
    
  
    return 0;
}