//
// Created by ly on 2018/8/15.
//
#include <iostream>
#include <algorithm>

using namespace std;

class Dijkstra{

private:
    int m;
    int **array;
    int startPoint;
public:
    Dijkstra(){};
    void init(int **array, int m, int startPoint){
        this->array = array;
        this->m = m;
        this->startPoint = startPoint;
    }

    void run_algorithm(){
        int shortestPath = 10000;
        int pathDistance = -1;
        int path[m];
        int nextNodeToJoin = -1;
        //初始化路径
        for (int k = 1; k < m; k++) {
            path[k] = -1;
        }
        path[0] = startPoint;

        for (int i = 0; i < this->m-1; i++) {
            for (int j = 0; j < this->m; j++) {
                if(array[startPoint][j]!=-1 && array[startPoint][j]<shortestPath){
                    shortestPath = array[startPoint][j];
                    nextNodeToJoin = j;
                }
            }

            path[i+1] = nextNodeToJoin;
            array[startPoint][nextNodeToJoin] = -1;
            nextNodeToJoin = -1;
            pathDistance = shortestPath;
            shortestPath = 10000;

            //更新距离
            for (int k = 0; k < m; ++k) {
                if(std::find(path, path+m, k)==path+m && array[path[i+1]][k]!=-1){
                    if(array[startPoint][k]==-1 || pathDistance + array[path[i+1]][k] < array[startPoint][k])
                        array[startPoint][k] = pathDistance + array[path[i+1]][k];
                }
            }
        }

        for (int l = 0; l < m; ++l) {
            cout << path[l] << " ";
        }
    }

    void print(){
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                cout << array[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {

    int m = 5;
    int startPoint = 0;
    //先分配行
    int **array = new int *[m];
    //每行分配元素
    for(int i = 0;i < m;i++){
        array[i] = new int[m];
    }

    //元素自己到自己的距离不计算
    for(int i = 0;i < m;i++){
        for(int j = 0;j < m;j++) {
            array[i][j] = -1;
        }
    }

    //  data/dijkstraData/dijkstra1.jpg
    array[0][1] = 10;
    array[0][3] = 30;
    array[0][4] = 100;

    array[1][2] = 50;

    array[2][4] = 10;

    array[3][2] = 20;
    array[3][4] = 60;

    Dijkstra dijkstra;
    dijkstra.init(array, m, startPoint);
    dijkstra.run_algorithm();

    return 0;
}
