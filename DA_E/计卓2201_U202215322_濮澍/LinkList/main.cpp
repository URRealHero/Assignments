#include "LinkList.h"
#include <cstdio>

using namespace std;

int main(){
	int op=1;
	LinkList L = NULL;
	ArrList Lists;
	Lists.length = 0;
	while(op){
	  system("clear");	printf("\n\n"); printf("      Menu for Link List Table\n"); printf("-------------------------------------------------\n");
	  printf("    	  1. InitList      7. LocateElem\n");
	  printf("    	  2. DestroyList   8. PriorElem\n");
	  printf("    	  3. ClearList     9. NextElem \n");
	  printf("    	  4. ListEmpty     10. ListInsert\n");
	  printf("    	  5. ListLength    11. ListDelete\n");
	  printf("    	  6. GetElem       12. ListTraverse\n");
	  printf("        13. SaveList     14. LoadList\n");
	  printf("        15. ReverseList  16. RemoveNthFromEnd\n");
	  printf("        17. SortList     18.多链表中添加新空表并初始化\n");
	  printf("        19. 多链表中删除某名称表\n");
	  printf("        20. 多链表中查找某名称表并对其进行管理\n");
	  printf("        21. 将当前链表保存入多链表中\n");
	  printf("    	  0. Exit\n");
	  printf("-------------------------------------------------\n");
	  printf("    请选择你的操作[0~21]:");
	  scanf("%d",&op);
	  switch(op){
		case 1:{
		  if(L != NULL ) cout<< "Link List already exists." << endl;
		  else {
			cout << "Please Input the Number of elements you want to input, 0 means Initiating an empty Link List" << endl;
			int ElemNum;
			cin >> ElemNum;
			if(!ElemNum){
			  InitList(L);
			}
			else{
			  cout << "Now input the num you want to insert." << endl;
			  InitList(L,ElemNum);
			  ListTraverse(L);
			}
		  }
			getchar();getchar();
		  }
		  break;
		case 2:{
			if(DestroyList(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			cout << "The LinkList is already destroyed." << endl;
			getchar();getchar();
		  }
			break;
		case 3:{
			if(ClearList(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else cout << "LinkList Cleared! " << endl;
			getchar();getchar();
		  }
			break;
		case 4:{
			int flag = ListEmpty(L);
			if(flag==INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else if (flag == FALSE) cout << "The LinkList is not empty! " << endl;
			else cout << "The LinkList is empty! " << endl;
			getchar();getchar();
		  }
			break;
		case 5:{
			int Length = ListLength(L);
			if(Length == INFEASIBLE)cout << "The LinkList hasn't been initialized " << endl;   
			else cout << "The LinkList is of " << Length << "long!" << endl;
			getchar();getchar();
		  }
			break;
		case 6:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{
			  int index;
			  ElemType e;
			  cout << "Please input which index you wan't to get in the LinkList:"<< "(1~" << ListLength(L) << ")";
			  cin >> index;
			  cout << endl;
			  if(GetElem(L,index,e)==ERROR) cout << "Wrong index Input! "<< "Your input should be among 1~" << ListLength(L) <<endl;
			  else cout << "The Elem under index " << index << "is "<< e << endl;
			}
			getchar();getchar();
		  }
		  break;
		case 7:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{
			int e;
			int i;
			cout << "Please input the number you wan't to search:";
			cin >> e;
			cout << endl;
			if((i = LocateElem(L,e))==ERROR) cout << "The number is not in the LinkList" << endl;
			else cout << "The number is at the " << i<< "th place" << endl;
		  }
			getchar();getchar();
		  }
		  break;
		case 8:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{		  
			  int pre,e;
			  cout << "Please input the number which you care about its prior elem:";
			  cin >> e;
			  cout << endl;
			  if(PriorElem(L,e,pre)==ERROR) cout << "There is no elem e or e has no prior elem"<<endl;
			  else cout << "The elem before e " << e <<  "is " << pre << endl;  
		  }
			
			getchar();getchar();
		  }
		  break;
		case 9:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{		  
			  int next,e;
			  cout << "Please input the number which you care about its next elem:";
			  cin >> e;
			  cout << endl;
			  if(NextElem(L,e,next)==ERROR) cout << "There is no elem e or e has no next elem"<<endl;
			  else cout << "The elem after e " << e <<  "is " << next << endl;  
			}
		  getchar();getchar();
		  }
		  break;
		case 10:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{
			int i , e;
			cout << "Please input the index you wan't to input(1~" << ListLength(L)+1 << "):";
			cin >> i;
			cout << endl;
			cout << "Please input the number you wan't to input before index " << i << ':';
			cin >> e;
			cout << endl;
			if(ListInsert(L,i,e)==ERROR) cout << "Wrong Index Input!! Nothing inserted"<< endl;
			else cout << "Insert successfully!" << endl;
			ListTraverse(L);
		  }
			getchar();getchar();
		  }
		  break;
		case 11:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else{
			int i , e;
			cout << "Please input the index you wan't to delete(1~" << ListLength(L) << "):";
			cin >> i;
			cout << endl;
			if(ListDelete(L,i,e)==ERROR) cout << "Wrong Index Input!! Nothing deleted"<< endl;
			else cout << "Delete successfully!" << "Elem " << e << "under index " << i << "has been deleted." << endl;
			ListTraverse(L);

		  }
			getchar();getchar();
		  }
		  break;
		case 12:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized " << endl;
			else ListTraverse(L);
			getchar();getchar();
		  }
		  break;
		case 13:{
			if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized "<< endl;
			else{
			  getchar();
			  char FileName[30];
			  cout << "请输入保存的文件名:";
			  cin.get(FileName,30);
			  cout << endl;
			  SaveList(L,FileName);
			  cout << "存储成功!"<< endl;
			}
			getchar();
			getchar();
		}
		  break;
		case 14:{
		  getchar();
		  char FileName[30];
		  cout << "请输入加载的文件名:";
		  cin.get(FileName,30);
		  cout << endl;
		  if(LoadList(L,FileName) == INFEASIBLE) cout << "加载失败" << endl;
		  else {
			cout << "加载成功!"<< endl;
			ListTraverse(L);
		  }
		getchar();
		getchar();

		}
		  break;
		case 15:{
		  if(ReverseList(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized! " << endl; 
		  else cout << "The List has been reversed" << endl; 
		  getchar();
		  getchar();
		}
		  break;
		case 16:{
		  if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized! " << endl;
		  else {
			int n,e;
			cout << "Please input the index you wan't to remove counting from the end:" ;
			cin >> n;
			cout << endl;
			if(RemoveNthFromEnd(L,n,e)==FALSE) cout << "The List Length is less than the index you've just input! Nothing has been removed;" << endl;
			else cout << "The " <<n<< "th index counting from behind has been removed, which is elem " << e  << endl;
			ListTraverse(L);
		}
		  getchar();
		  getchar();

		}
		  break;
		case 17:{
		  if(SortList(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized! " << endl; 
		  else cout << "The LinkList has been sorted" << endl;
		  getchar();
		  getchar();

		}
		  break;
		//多线性表操作
		case 18://创建线性表集合
		{
		  if(Lists.length>=20) cout<< "链集合已满，插入失败" << endl;
		  else{
			char ListName[30];
			getchar();
			cout << "请输入插入链表的名字:";
			cin.get(ListName,30);
			cout << endl;
			AddList(Lists,ListName);
		}
		getchar();
		getchar();
	  }
		  break;
		case 19://删除线性表集合中的线性表
		{
		  char ListName[30];
		  getchar();
		  cout << "请输入要删除的链表的名字:";
		  cin.get(ListName,30);
		  cout << endl;
		  if(RemoveList(Lists,ListName,L) == ERROR) {
		    std::cout << "未找到该名称的链表！" << std::endl;
		  }
		  else 
		   std::cout << "删除成功！" << std::endl;
		  getchar();
		  getchar();
	  }
		  break;
		case 20://查找线性表
		{
		  char ListName[30];
		  int i;
		  getchar();
		  cout << "请输入要查找的链表的名字:";
		  cin.get(ListName,30);
		  cout << endl;
		  if((i = LocateList(Lists,ListName,L)) == 0) std::cout << "未找到该名称的链表！" << std::endl;
		  else std::cout << "成功！该链表在位置" << i << "处" << std::endl;
		  getchar();
		  getchar();
		}
		  break;
		case 21:{
		  if(ListEmpty(L) == INFEASIBLE) cout << "The LinkList hasn't been initialized! " << endl;
		  else if(Lists.length>=20) cout<< "链集合已满，插入失败" << endl;
		  else{
			char ListName[30];
			getchar();
			cout << "请输入要存入的链表名字:";
			cin.get(ListName,30);
			cout << endl;
			Save2List(Lists,ListName,L);
			cout << "The LinkList you are controlling has been saved into the Lists Set" << endl;
		}
			getchar();
			getchar();
	  }
		case 0:
		  break;

	}//end of switch
  }
  return 0;
}
