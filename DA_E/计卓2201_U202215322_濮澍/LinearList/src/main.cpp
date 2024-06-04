#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <string>
#include "SQList.h"
using namespace std;
int main(){
SQList L;  
int op=1;
LISTS Lists;
Lists.length = 0;
while(op){
	system("clear");	
	cout << endl << endl;
	cout << "      Menu for Linear Table On Sequence Structure \n";
	cout <<"-------------------------------------------------\n";
	cout <<"    	  1. InitList       7. LocateElem\n";
	cout <<"    	  2. DestroyList    8. PriorElem\n";
	cout <<"    	  3. ClearList      9. NextElem \n";
	cout <<"    	  4. ListEmpty      10. ListInsert\n";
	cout <<"    	  5. ListLength     11. ListDelete\n";
	cout <<"    	  6. GetElem        12. ListTraverse\n";
	cout <<"	  13. SaveList      14. LoadList\n";
	cout <<"	  15. AddList       16. RemoveList\n";
	cout <<"	  17. LocateList    18. MaxSubArray\n";
	cout <<"	  19. SubArrayNum   20. SortList\n";
	cout <<"	  21. TraverseLISTS\n";
	cout <<"	  0. Exit\n";
	cout <<"-------------------------------------------------\n";
	cout <<"    请选择你的操作[0~22]:";
	cin >> op;
    switch(op){
	  case 1:
		 //printf("\n----IntiList功能待实现！\n");
		  if(InitList(L)==OK) printf("线性表创建成功！\n");
		  else printf("线性表创建失败！\n");
		  getchar();
		  getchar();
		  break;
	  case 2:
		  if(DestroyList(L) == OK) printf("线性表销毁成功！\n");
		  else printf("无线性表，销毁失败\n");     
		  getchar();
		  getchar();
		  break;
	  case 3:
		  if(ClearList(L) == OK)printf("线性表清空成功\n");     
		  else printf("无线性表，清空失败\n");
		  getchar();
		  getchar();
		  break;
	  case 4:
		if(isEmpty(L) == INFEASIBLE)printf("线性表未初始化！\n");
		else if(isEmpty(L) == TRUE) printf("线性表为空\n");
		else printf("线性表非空！\n");
		getchar();
		getchar();
		break;
	  case 5:
		int l;
		if(( l = ListLength(L) )== INFEASIBLE)printf("List未初始化！\n");
		else printf("List长为%d\n",l); 
		getchar();
		getchar();
		break;
	  case 6:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化" << endl;
		else{
		  int e,i;
		  cout << "请输入要取的是第几位数字\n";
		  cin >> i;
		  while(GetElem(L,i,e)==ERROR){
			cout << "输入的下标超界"<< "0~" << L.length <<"或为负值，请确保正确的输入"<<endl;
			cin >> i;
		  }
		  cout << "取出的元素值为"<< GetElem(L,i,e)<<endl;
		} 
		getchar();
		getchar();
		break;
	  case 7:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int e;
		  cout << "请输入想查找的元素:";
		  cin >> e;
		  cout << endl;
		  if (!LocateElem(L,e))
			cout << e << "没有找到哦！" << endl;     
		  else{
			cout << e <<"找到了！" <<endl;
		  }
		}
		getchar();
		getchar();
		break;
	  case 8:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int e,pre;
		  std::cout << "将查找输入元素的前驱:" << std::endl;
		  std::cin >> e;
		  if(PriorElem(L,e,pre) == ERROR) std::cout << "没找到元素前驱，可能是输入下标有误" << std::endl;
		  else cout << e << "的前驱为" << pre <<endl; 
		}
		getchar();
		getchar();
		break;
	  case 9:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int e,next;
		  std::cout << "将查找输入元素的后继:" << std::endl;
		  std::cin >> e;
		  if(NextElem(L,e,next) == ERROR) std::cout << "没找到元素后继，可能是输入下标有误，已退出" << std::endl;
		  else cout << e << "的后继为" << next <<endl; 

		}     
		getchar();
		getchar();
		break;
	  case 10:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int i ;
		  ElemType e;
		  cout << "请输入插入到第几个元素前" << endl;
		  cin >> i;
		  cout << "请输入插入元素" << endl;
		  cin >> e;
		  if(ListInsert(L,i,e)==ERROR) cout << "输入了错误的下标！已退出" <<endl;
		  else std::cout << "插入成功" << std::endl;
		}
		getchar();
		getchar();
		break;
	  case 11:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int i ;
		  ElemType e;
		  cout << "请输入删除第几个元素" << endl;
		  cin >> i;
		  if(ListDelete(L,i,e)==ERROR) cout << "输入了错误的下标！" <<endl;
		  else std::cout << "删除成功" << "元素" << e << "被删除" <<std::endl;
		}
		getchar();
		getchar();
		break;
	  case 12:
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		//printf("\n----ListTrabverse功能待实现！\n");     
		else{
		  ListTraverse(L);
		  cout << endl;
		  cout << "Traverse done!" << endl;
		}
		getchar();
		getchar();
		break;
	  case 13://保存链表
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  getchar();
		  char FileName[MAXLEN];
		  cout << "请输入保存的文件名:";
		  cin.get(FileName,MAXLEN);
		  cout << endl;
		  SaveList(L,FileName);
		  cout << "存储成功!"<< endl;
		}
		getchar();
		getchar();
		break;

	  case 14://加载链表
		  getchar();
		  char FileName[MAXLEN];
		  cout << "请输入加载的文件名:";
		  cin.get(FileName,MAXLEN);
		  cout << endl;
		  if(LoadList(L,FileName) == INFEASIBLE ||  LoadList(L,FileName) == ERROR) cout << "加载失败" << endl;
		  else cout << "加载成功!"<< endl;
		getchar();
		getchar();
		break;
	  case 15://创建线性表集合
		if(Lists.length>=10) cout<< "线性表集合已满，插入失败" << endl;
		else{
		  getchar();
		  char ListName[MAXLEN];
		  cout << "请输入插入空线性表的名字:";
		  cin.get(ListName,MAXLEN);
		  cout << endl;
		  AddList(Lists,ListName);
		}
		getchar();
		getchar();
		break;
	  case 16://删除线性表集合中的线性表
		char ListName[MAXLEN];
		getchar();
		cout << "请输入要删除的空线性表的名字:";
		cin.get(ListName,MAXLEN);
		cout << endl;
		if(RemoveList(Lists,ListName) == ERROR) {
		  std::cout << "未找到该名称的线性表！" << std::endl;
		}
		else 
		  std::cout << "删除成功！" << std::endl;
		getchar();
		getchar();
		break;
	  case 17://查找线性表
		{
		char ListName[MAXLEN];
		int i;
		getchar();
		cout << "请输入要查找的空线性表的名字:";
		cin.get(ListName,MAXLEN);
		cout << endl;
		if((i = LocateList(Lists,ListName,L)) == 0) std::cout << "未找到该名称的线性表！" << std::endl;
		else std::cout << "成功！该线性表在位置" << i << "处" << std::endl;
		getchar();
		getchar();
		break;
	  }
	  case 18://最大子列和
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  cout << "该线性表的最大子列和为" << MaxSubArray(L) << endl;
		}
		getchar();
		getchar();
		break;
	
	  case 19://子列和为k的个数
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  int K;
		  cout << "请输入想知道的和:" << endl;
		  cin >> K;
		  cout << endl;
		  cout << "有"<< SubArrayNum(L,K) <<"个子列的和为K="<< K <<"！" << endl;
		}
		getchar();
		getchar();
		break;
	  case 20://排序链表
		if(isEmpty(L) == INFEASIBLE) cout << "线性表未初始化！" << endl;
		else{
		  SortList(L);
		  cout << "线性表已经升序排序完毕" << endl;
		}
		getchar();
		getchar();
		break;
	  case 21:		
        if(TraverseLISTS(Lists)==INFEASIBLE) cout << "无子表"<< endl;
		getchar();
		getchar();
        break;
	  case 0:
		break;

	}//end of switch
  }//end of while
}
