// Put real into array
// Fake++


# include <iostream>
# include <map>
using namespace std;


map<int,int>Animal;
bool CheckReal(int d,int x,int y,int N);


int main(){
  int N,K;
  int d,x,y;
  int index = 0;
  scanf("%d %d", &N, &K);
  for (int i = 0 ; i < K ; i++){
	scanf("%d %d %d", &d, &x, &y);
	if(!CheckReal(d,x,y,N)){
	  index++;
	}
  }
  cout << index << endl;
  return 0;
}

bool CheckReal(int d, int x, int y,int N){
  if (x > N || y > N) return false;
  if(x == y && d == 2) return false;
  int Cat_x,Cat_y;
  if(Animal.find(x)!= Animal.end()) Cat_x = Animal[x];
  else Cat_x = 0;
//   cout << "Cat_x = " << Cat_x << endl;
  if(Animal.find(y) != Animal.end()) Cat_y = Animal[y];                                                                                                                                                   
  else Cat_y = 0;
//   cout << "Cat_y = " << Cat_y << endl;
  if(Cat_x != 0 && Cat_y != 0){
	if (d == 1){
	  if (Cat_x != Cat_y) return false;
	  else return true;
	}
	if (d == 2){
	  if(Cat_x - Cat_y == -1 || Cat_x - Cat_y == 2){
		return true;
	  }
	  else return false;
	}
  }
  else if(Cat_x != 0){
	if (d==1) Animal[y] = Cat_x;
	else{
	  if(Cat_x == 3) Animal[y] = 1;
	  else Animal[y] = Cat_x+1;
	}
	return true;
  }
  else if(Cat_y != 0){
	if(d == 1) Animal[x] = Cat_y;
	else {
	  if (Cat_y == 1) Animal[x] = 3;
	  else Animal[x] = Cat_y-1;
	}
	return true;
  }
  else{
	if(d==1) Animal[x] = Animal[y] = 1;
	else {
	  Animal[x] = 1;
	  Animal[y] = 2;
	}
	return true;
  }
  return true;
}
