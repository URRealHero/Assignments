#include <iostream>
using namespace std;

class FoodTrainUnion
{
private:
    int *id;
public:
    int find(int x);
    void Union(int x, int y);
    bool connected(int x, int y);
    FoodTrainUnion(int x):id(new int[x]){
        for (int i = 0; i < x; i++)
        {
            id[i] = i;
        }
    };
    ~FoodTrainUnion(){
        delete id;
    }
};

int FoodTrainUnion::find(int x){
    return id[x] == x ? x : id[x] = find(id[x]);
}

void FoodTrainUnion::Union(int x, int y){
    x = find(x);
    y = find(y);
    if(x == y) return;
    id[y] = x;
}

bool FoodTrainUnion::connected(int x, int y){
    return find(x) == find(y);
}

int main(){
    int N,K;
    scanf("%d %d", &N, &K);
    int d,x,y;
    int index = 0;
    FoodTrainUnion Animals(N*3); // 0~N-1 A, N~2N-1 B, 2N~3N-1 C
    for (int i = 0; i < K; i++)
    {
        scanf("%d %d %d", &d, &x, &y);
        if(x > N || y > N){
            index++;
            continue;
        }
        if(d == 1){
            if(Animals.connected(x-1, y-1+N) || Animals.connected(x-1, y-1+2*N) || Animals.connected(x-1+N, y-1) || Animals.connected(x-1+N, y-1+2*N) || Animals.connected(x-1+2*N, y-1) || Animals.connected(x-1+2*N, y-1+N)) {
                index++;
            }// 不同类
            else{
                Animals.Union(x-1, y-1);
                Animals.Union(x-1+N, y-1+N);
                Animals.Union(x-1+2*N, y-1+2*N);
            }
        }
        else{
            if(Animals.connected(x-1, y-1) || Animals.connected(x-1+2*N, y-1+2*N) || Animals.connected(x-1+N, y-1+N) || Animals.connected(x-1+N, y-1) || Animals.connected(x-1+2*N, y-1+N) || Animals.connected(x-1, y-1+2*N)){
                index++;
            }// 同类或者x被y吃
            else{
                Animals.Union(x-1, y-1+N);
                Animals.Union(x-1+N, y-1+2*N);
                Animals.Union(x-1+2*N, y-1);
            }
        }
    }
    cout << index << endl;
    return 0;
}