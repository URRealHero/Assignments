#include "def.h"
using namespace std;

int main(void){
int op=1;
BiTree T = nullptr;
BiForest F;
F.length = 0;
while(op){
	system("clear");	printf("\n\n");
	printf("      Menu for Linear Table On Sequence Structure \n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateTree     7. Insertion\n");
	printf("    	  2. ClearTree      8. Deletion\n");
	printf("    	  3. GetDepth       9.  Traverse\n");
	printf("    	  4. LocateNode     10. Save\n");
	printf("    	  5. Assign value   11. Load\n");
	printf("    	  6. Get Siblings\n");
    printf("-------------------------------------------------\n");
    printf("    	  Additional implementation\n");
    printf("    	  12. LowestCommonAncestor\n");
    printf("    	  13. MaxPathFromRootToLeaf\n");
    printf("    	  14. MaxPathSum\n");
    printf("          15. InverseTree\n");
    printf("-------------------------------------------------\n");
    printf("    	  Forest Manipulation\n");
    printf("    	  16. Add BiTree to Forest\n");
    printf("    	  17. Delete BiTree from Forest\n");
    printf("    	  18. Locate and modify the Tree from Forest\n");
    printf("    	  19. Traverse the Forest\n");
    printf("    	  20. Index of a Tree in the Forest\n");
	printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~20]:");
	scanf("%d",&op);
    switch(op){
    case 1:
        if(T) printf("树已经存在，如需重建，请先清空树！\n");
        else{
            TElemType *definition;
            definition = new TElemType[20];
            printf("请输入树的结点信息，格式为：结点值 结点信息\n");
            printf("输入-1 null表示结束！\n");
            int i = 0;
            while(1){
                scanf("%d %s",&definition[i].key,definition[i].others);
                if(definition[i].key == -1)
                    break;
                i++;
            }
            if(CreateBiTree(T,definition)==ERROR) printf("树创建失败！输入信息有误\n");
            else printf("树创建成功！\n");
            delete []definition;
        }
        getchar();getchar();
        break;
    case 2:
        if(!T) printf("树不存在，请先创建树！\n");
        else{
            ClearBiTree(T);
            printf("树已清空！\n");
        }
        getchar();getchar();
        break;
    case 3:
        if(!T) cout << "树不存在，请先创建树！" << endl;
        else{
            cout << "树的深度为：" << BiTreeDepth(T) << endl;
        }     
        getchar();getchar();
        break;
    case 4:
        if(!T) cout << "树不存在，请先创建树！" << endl;
        else{
            KeyType e;
            cout << "请输入要查找的结点的值：" << endl;
            cin >> e;
            BiTree p = LocateNode(T,e);
            if(p){
                cout << "结点的值为：" << p->data.key << endl;
                cout << "结点的信息为：" << p->data.others << endl;
            }
            else
                cout << "未找到该结点！" << endl;
        }     
        getchar();getchar();
        break;
    case 5:{
        if (!T)
        {
            cout << "树不存在，请先创建树！" << endl;
            getchar();getchar();
            break;
        }
        cout << "请输入要改变值的结点的值：" << endl;
        KeyType e;
        cin >> e;
        BiTree pointer = LocateNode(T,e);
        if(!pointer){
            cout << "未找到该结点！" << endl;
        }
        else{
            TElemType eNodedata;
            cout << "请输入要赋值的结点的值：" << endl;
            cin >> eNodedata.key;
            cout << "请输入要赋值的结点的信息：" << endl;
            cin >> eNodedata.others;
            if(Assign(T,e,eNodedata)==ERROR) cout << "赋值失败！赋值后树出现问题" << endl;
            else cout << "赋值成功！" << endl;
        }
        getchar();getchar();
    }
        break;
    case 6:{
        if(!T) cout << "树不存在，请先创建树" << endl;
        else{
            KeyType e;
            cout << "请输入要查找兄弟结点的结点的值：" << endl;
            cin >> e;
            if(LocateNode(T,e)==nullptr) cout << "未找到该结点！" << endl;
            else {
                BiTree Sib = GetSibling(T,e);
                if(!Sib) cout << "未找到该结点的兄弟结点！" << endl;
                else{
                    cout << "兄弟结点的值为：" << Sib->data.key << endl;
                    cout << "兄弟结点的信息为：" << Sib->data.others << endl;
                }
            }
        }     
        getchar();getchar();
    }
        break;
    case 7:{
        if(!T) cout << "树不存在，请先创建树！" << endl;
        else{
            KeyType e;
            cout << "请输入要插入的结点的父结点的值：" << endl;
            cin >> e;
            BiTree eNode = LocateNode(T,e);
            int LR;
            cout << "请输入要插入的结点是左孩子还是右孩子（0为左孩子，1为右孩子,-1为根节点插入）：" << endl;
            cin >> LR;
            if(LR!=-1 && LR!=0 && LR!=1){
                cout << "输入错误！" << endl;
            }
            if(LR!=-1 && !eNode) cout << "未找到该结点！" << endl;
            else{
                cout << "请输入要插入的结点的值：" << endl;
                TElemType eNodedata;
                cin >> eNodedata.key;
                cout << "请输入要插入的结点的信息：" << endl;
                cin >> eNodedata.others;
                if(InsertNode(T,e,LR,eNodedata)==ERROR) cout << "插入失败！树中出现错误！" << endl;
                else cout << "插入成功！" << endl;
            }
        }
        getchar();getchar();
    }
        break;
    case 8:{
        if(!T) cout <<"树不存在，请先创建树"<<endl;
        else{
            KeyType e;
            cout << "请输入要删除的结点的值：" << endl;
            cin >> e;
            if(LocateNode(T,e) == nullptr) cout << "未找到该结点！无法删除" << endl;
            else{
                DeleteNode(T,e);
                cout << "删除成功！" << endl;
            }
        }    
        getchar();getchar();
    }
        break;
    case 9:{
        if(!T) cout << "树不存在，请先创建树！" << endl;
        else{
            int choice;
            cout << "请选择遍历方式" << endl;
            cout << "1.先序遍历" << endl;
            cout << "2.中序遍历" << endl;
            cout << "3.后序遍历" << endl;
            cout << "4.层序遍历" << endl;
            cin >> choice;
            switch(choice){
                case 1:
                    PreOrderTraverse(T,visit);
                    break;
                case 2:
                    InOrderTraverse(T,visit);
                    break;
                case 3:
                    PostOrderTraverse(T,visit);
                    break;
                case 4:
                    LevelOrderTraverse(T,visit);
                    break;
                default:
                    cout << "输入错误！" << endl;
            }
        }
        getchar();getchar();
    }
        break;
    case 10:{
        cout << "请输入你要存储的文件名：" << endl;
        char filename[20];
        cin >> filename;
        SaveBiTree(T,filename);
        cout << "存储成功！" << endl;     
        getchar();getchar();
    }
        break;
    case 11:{
        if(T) {
            Auto_Add_a_BiTree(F,T);
            ClearBiTree(T);
        }
        cout << "请输入你要读取的文件名：" << endl;
        char filename1[20];
        cin >> filename1;
        if(LoadBiTree(T,filename1)==OK) cout << "读取成功！" << endl;
        else cout << "读取失败！" << endl;
        getchar();getchar();
        }
        break;
    case 12:{
        if(!T) cout << "树不存在，请先创建树！" <<endl;
        else{
            cout << "请输入想要查找的两棵子树的结点值" << endl;
            KeyType k1,k2;
            cin >> k1;
            cin >> k2;
            BiTree e1 = LocateNode(T,k1);
            BiTree e2 = LocateNode(T,k2);
            if (!e1 || !e2) cout <<"输入了至少一个错误结点值，无法完成最低公共祖先查找"<< endl;
            else{
                BiTree Ancestor = LowestCommonAncestor(T,e1,e2);
                cout << "最低公共祖先的值为：" << Ancestor->data.key << endl;
                cout << "最低公共祖先的信息为：" << Ancestor->data.others << endl;
            }
        }
		getchar();getchar();
        }
        break;
    case 13:{
        if(!T) cout << "树不存在，请先创建树！"<<endl;
        else{
            cout << "从根到叶子结点的加权最大路径和为："<< MaxPathLength(T) << endl;
        }
        getchar();getchar();
        }
        break;
    case 14:{
        if(!T) cout << "树不存在，请先创建树！"<<endl;
        else{
            cout << "树中的最大路径和为"<< MaxPathSum(T) << endl;
        }
        getchar();getchar();
        }
        break;
    case 15:{
        if(!T) cout << "树不存在，请先创建树！"<<endl;
        else{
            //翻转二叉树
            InverseBiTree(T);
            cout << "翻转成功！" << endl;
        }
        getchar();getchar();
        }
        break;
    case 16:{
        //在森林里创建一个树并初始化
        TElemType * definitions;
        definitions = new TElemType[20];
        printf("请输入树的结点信息，格式为：结点值 结点信息\n");
        printf("输入-1 null表示结束！\n");
        int i = 0;
        while(1){
            scanf("%d %s",&definitions[i].key,definitions[i].others);
            if(definitions[i].key == -1)
                break;
            i++;
        }
        char filename2[20];
        cout << "请输入森林中新树的名字：" << endl;
        cin >> filename2;
        if(Add_BiTree_to_Forest(F,filename2,definitions)==ERROR) cout << "添加失败！输入信息有误" << endl;
        else{
            cout << "添加成功！" << endl;
        }
        delete []definitions;
        getchar();getchar();
    }
        break;
    case 17:{
        Traverse_Forest_Names(F);
        char filename3[20];
        cout << "请输入你要删除的树的名字：" << endl;
        cin >> filename3;
        if(Remove_BiTree_from_Forest(F,filename3)==ERROR) cout << "未找到树或森林为空" << endl;
        else cout << "删除成功！" << endl;
        getchar();getchar();
        }
        break;
    case 18:{
        if(T) Auto_Add_a_BiTree(F,T);
        Traverse_Forest_Names(F);
        cout << "请输入你要读取的树名：" << endl;
        char filename4[20];
        cin >> filename4;
        if(Locate_And_Modify_a_Tree_in_Forest(F,filename4,T)==OK) cout << "读取成功！" << endl;
        else cout << "读取失败！" << endl;
        getchar();getchar();
        }
        break;
    case 19:{
        Traverse_Forest_Names(F);
        getchar();getchar();
        }
        break;
    case 20:{
        //返回树在森林中的位置
        cout << "请输入你要查找的树名：" << endl;
        char filename5[20];
        cin >> filename5;
        int pos = Index_of_Tree(F,filename5);
        if(pos == -1) cout << "未找到该树！" << endl;
        else cout << "该树在森林中的位置为：" << pos << endl;
        getchar();getchar();
    }
        break;
	case 0:
        break;
	}//end of switch
  }//end of while
    printf("欢迎下次再使用本系统！\n");
}//end of main()
/*--------page 23 on textbook --------------------*/
