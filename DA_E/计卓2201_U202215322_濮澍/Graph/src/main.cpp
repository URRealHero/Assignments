#include "Graph.h"

int main(){
    ALGraph G;
    GRAPHS P;
    int op = 1;
    while(op){
	system("clear");	printf("\n\n");
	printf("      Menu for Graph\n");
	printf("-------------------------------------------------\n");
	printf("    	  1. CreateGraph    7. InsertVex\n");
	printf("    	  2. DestroyGraph   8. DeleteVex\n");
	printf("    	  3. LocateVex      9. InsertArc\n");
	printf("    	  4. AssignValue    10. DeleteArc\n");
	printf("    	  5. FirstAdjvex    11. DFSTraverse\n");
	printf("    	  6. NextAdjvex     12. BFSTraverse\n");
    cout << "         13. SaveGraph     14. LoadGraph" << endl;
    cout << "         15. VerticesSetLessThanK" << endl;
    cout << "         16. ShortestPathLength of the No-weight Graph(Graphs of other kinds havn't realised)" << endl;
    cout << "         17. ConnectedComponentsNums(Easiest version)" << endl;
	printf("-------------------------------------------------\n");
    cout << "Multi-Graphs Operation" << endl;
    cout << "         18. Add Graph to Graphs" << endl;
    cout << "         19. Remove Graph from Graphs" <<endl;
    cout << "         20. Locate and Modify the Graph in Graphs" << endl;
    cout << "         There are topo sort but have no meaning under UG" << endl;
    printf("    	  0. Exit\n");
	printf("-------------------------------------------------\n");
	printf("    请选择你的操作[0~20]:");
	scanf("%d",&op);
    switch(op){
        case 1:{
            VertexType V[20];
            KeyType VR[20][2];
            int i = 0;
            cout << "Please Input the Vertexs' Information of the Graphs" << endl;
            while(1){
                scanf("%d%s",&V[i].key,V[i].others);
                if(V[i].key == -1) break;
                i++;
            }
            i = 0;
            cout << "Please Input the Edges of the Graphs" << endl;
            while(1){
            scanf("%d%d",&VR[i][0],&VR[i][1]);
            if(VR[i][0] == -1 || VR[i][1] == -1) break;
            i++;
            }
            if(CreateGraph(G,V,VR) == OK) cout << "CreateGraph Success" << endl;
            else cout << "CreateGraph Failed" << endl;
            getchar();getchar();
        }
        break;
	   case 2:{
        DestroyGraph(G);
        cout << "Graph Destroyed Successfully" << endl;
		 getchar();getchar();
       }
		 break;

	   case 3:{
		 cout << "Please Input the key you wan't to search in the Graph" << endl; 
            KeyType key;
            cin >> key;
            int i = LocateVex(G,key);
            if(i == -1) cout << "LocateVex Failed" << endl;
            else cout << "LocateVex Success" << "The Vex is at the " << i << "th place!"<< endl;
    }
		 getchar();getchar();
		 break;
	   case 4:{
		 cout << "Please Input the key of a vertex you wan't to assign the value" << endl;
         KeyType key;
         cin >> key;
         cout << "Please Input the value you wan't to assign to the vertex" << endl;
         VertexType V;
         cin >> V.key;
         cout << "Please Input the Information you wan't to assign to the vertex" << endl;
        cin >> V.others;
         if(PutVex(G,key,V) == OK) cout << "AssignValue Success" << endl;
         else cout << "Assign Value Failed, There must be a conflict or there is no value of key" << key << endl;    
		 getchar();getchar();
       }
		 break;
	   case 5:{    
         cout << "Please Input the key of a vertex you wan't to get the first adjvex" << endl;
            KeyType key; 
            cin >> key;
            int i;
            if((i = FirstAdjVex(G,key)) == -1) cout << "FirstAdjvex Failed" << endl;
            else {cout << "FirstAdjvex Success" << endl;
        cout << "The First Adjvex is at" << i << "th place and the key is " << G.vertices[i].data.key << endl;}
		 getchar();getchar();
       }
         break;
	   case 6:{
		 cout << "Please Input the key of a vertex you wan't to get the next adjvex" << endl;
            KeyType key; 
            cin >> key;
            cout << "Please Input the key of the adjvex you wan't to get the next adjvex" << endl;
            KeyType key1;
            cin >> key1;
            int i;
            if((i = NextAdjVex(G,key,key1)) == -1) cout << "NextAdjvex Failed" << endl;
            else {cout << "NextAdjvex Success" << endl;
        cout << "The Next Adjvex is " << i << endl;}
		 getchar();getchar();}
		 break;
	   case 7:{
        VertexType V;
        cout << "Please Input the key of a vertex you wan't to insert" << endl;
        cin >> V.key;
        cout << "Please Input the Information of the vertex you wan't to insert" << endl;
        cin >> V.others;
        if(InsertVex(G,V) == OK) cout << "InsertVex Success" << endl;
        else cout << "InsertVex Failed" << endl;
		 getchar();getchar();
       }
         break;
	   case 8:
		 cout << "Please Input the key of a vertex you wan't to delete" << endl;
         KeyType key;
         cin >> key;
         if(DeleteVex(G,key) == OK) cout << "DeleteVex Success" << endl;
         else cout << "DeleteVex Failed! Wrong Input or sth" << endl;     
		 getchar();getchar();
		 break;
	   case 9:{
        cout << "Please Input a couple of key which represent the edge you wan't to insert" << endl;
        KeyType key1,key2;
        cin >> key1;
        cin >> key2;
        if(InsertArc(G,key1,key2) == OK) cout << "InsertArc Success" << endl;
        else cout << "InsertArc Failed! No such vertices or conflict emerges" << endl;
		 getchar();getchar();
       }
         break;
	   case 10:{
        cout << "Please Input a couple of key which represent the edge you wan't to delete" << endl;
        KeyType key1,key2;
        cin >> key1;
        cin >> key2;
        if(DeleteArc(G,key1,key2) == OK) cout << "DeleteArc Success" << endl;
        else cout << "DeleteArc Failed! No such vertices" << endl;    
		 getchar();getchar();
       }
		 break;
	   case 11:{
        cout << "Time To Traverse the Graph by DFS" << endl;
        DFSTraverse(G,visit);
		 getchar();getchar();
       }
		 break;
	   case 12:{
		 cout << "Time To Traverse the Graph by BFS" << endl;
         BFSTraverse(G,visit);
		getchar();getchar();
       }
         break;
         case 13:{
            cout << "Please Input the FileName you wan't to save the Graph" << endl;
            char FileName[100];
            cin >> FileName;
            if(SaveGraph(G,FileName) == OK) cout << "Save Success" << endl;
            else cout << "Save Failed" << endl;
            getchar();getchar();
         }
            break;
        case 14:{
            cout << "Please Input the FileName you wan't to load the Graph" << endl;
            char FileName[100];
            cin >> FileName;
            if(LoadGraph(G,FileName) == OK) cout << "Load Success" << endl;
            else cout << "Load Failed" << endl;
            getchar();getchar();
        }
        break;
        case 15:{
            KeyType key;
            int k;
            cout << "Please Input the key of the vertex you wan't to judge the length to it is less than k" << endl;
            cin >> key;
            cout << "Please Input the k" << endl;
            cin >> k;
            int * ans = VerticesSetLessThanK(G,key,k);
            if (ans == nullptr)
            {
                cout << "VerticesSetLessThanK Failed, Vertex not find" << endl;
            }
            
            for (int i = 0 ; i < G.vexnum ; i++){
                if(ans[i] == 1) cout << "The Vertex " << i << " of key " << G.vertices[i].data.key << " is less than " << k << " to " << key << endl;
                else cout << "The Vertex " << i << " of key " << G.vertices[i].data.key <<" is not less than " << k << " to " << key << endl;
            }
            getchar();getchar();
        }
        break;
        case 16:{
            cout << "Please input two keys to get the shortest path between'em." << endl;
            KeyType key1,key2;
            cin >> key1 >> key2;
            int ans = ShortestPathLength(G,key1,key2);
            cout << "The Length of the shortest path between the vertex of "<< key1<< " and "<< key2 <<"is " << ans << "." << endl;
            getchar();getchar();
        }
        break;
        case 17:{
            cout << "Here we are going to judge how many Connected Components are there in the UD Graph." << endl;
            int index;
            cout << "The Graph has "<< ConnectedComponentsNums(G) << " Connected Component(s)";
            cout << endl;
            getchar();getchar();
        }
        break;
        case 18:{
            Traverse_GRAPHS(P);
            cout << "Please enter the graph's name that you wan't to input in the Graphs" << endl;
            char FileName[100];
            cin >> FileName;
            if(Add_GRAPHS(P,FileName) == OK) cout << "Add Success" << endl;
            else cout << "Add Failed,Full GRAPHS" << endl;
            getchar();getchar();
        }
        break;
        case 19:{
            Traverse_GRAPHS(P);
            cout << "Please enter the graph's name that you wan't to delete in the Graphs" << endl;
            char FileName[100];
            cin >> FileName;
            if(Remove_GRAPHS(P,FileName) == OK){ cout << "Delete Success" << endl;
            Traverse_GRAPHS(P);}
            else cout << "Delete Failed,No such Graph" << endl;

            getchar();getchar();
        }
        break;
        case 20:{
            Traverse_GRAPHS(P);
            cout << "Please enter the graph's name that you wan't to get in the Graphs" << endl;
            char FileName[100];
            cin >> FileName;
            if(Locate_and_Modi_GRAPHS(P,G,FileName) == OK) cout << "Get Success" << endl;
            else cout << "Get Failed,No such Graph" << endl;
            getchar();getchar();
        }
        break;
	case 0:
         break;
	}//end of switch
  }//end of while
printf("欢迎下次再使用本系统！\n");
}//end of main()
