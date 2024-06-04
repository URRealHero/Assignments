#include "LinkList.h"
#include <iostream>
using namespace std;

int main ()
{
	int op=1;
	int flag = 0;
	while(op){
	  system("clear");	printf("\n\n");
	  printf("      Menu for Link List Table\n");
	  printf("-------------------------------------------------\n");
	  printf("    	  1. InitList       7. LocateElem\n");
	  printf("    	  2. DestroyList8. PriorElem\n");
	  printf("    	  3. ClearList       9. NextElem \n");
	  printf("    	  4. ListEmpty     10. ListInsert\n");
	  printf("    	  5. ListLength     11. ListDelete\n");
	  printf("    	  6. GetElem       12. ListTrabverse\n");
	  printf("    	  0. Exit\n");
	  printf("-------------------------------------------------\n");
	  printf("    请选择你的操作[0~12]:");
	  scanf("%d",&op);
	   switch(op){
	   case 1:
		if(flag == 1) cout<< "Link List already exists." << endl;
		 //printf("\n----IntiList功能待实现！\n");
		cout << "Please Input the Number of elements you want to input, 0 means Initiating an empty Link List" << endl;
		int ElemNum;
		cin >> ElemNum;
		if(!ElemNum){
		  LList L;
		}
		else{
		  LList L(ElemNum);
		}
		flag = 1;
		getchar();getchar();
		break;
	   case 2:

		 getchar();getchar();
		 break;
	   case 3:
		 printf("\n----ClearList功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 4:
		 printf("\n----ListEmpty功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 5:
		 printf("\n----ListLength功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 6:
		 printf("\n----GetElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 7:
		 printf("\n----LocateElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 8:
		 printf("\n----PriorElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 9:
		 printf("\n----NextElem功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 10:
		 printf("\n----ListInsert功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 11:
		 printf("\n----ListDelete功能待实现！\n");     
		 getchar();getchar();
		 break;
	   case 12:
		 //printf("\n----ListTrabverse功能待实现！\n");     
		 if(!ListTrabverse(L)) printf("线性表是空表！\n");
		getchar();getchar();
		 break;
	case 0:
         break;
	}//end of switch
  }
  return 0;
}
