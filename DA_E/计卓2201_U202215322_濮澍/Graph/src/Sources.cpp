#include "Graph.h"

// Path: Graph.h

status CreateGraph(ALGraph &G,VertexType V[],KeyType VR[][2])   
    /*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    G.kind = DN;
    int i,k;
    int index;
    int flag1 = 0,flag2 = 0;
    for(i = 0; V[i].key != -1 ; i++){
        for(int j = i+1 ; V[j].key != -1 ; j++){
            if(V[i].key == V[j].key) return ERROR;
            if(strcmp(V[i].others,V[j].others) == 0) return ERROR;
        }
    }
    if(i > MAX_VERTEX_NUM) return ERROR;
    else G.vexnum = i;
    for(i = 0 ; VR[i][0] != -1 && VR[i][1] != -1; i++){
        if(VR[i][0] == VR[i][1]) return ERROR;
        for(int j = 0; V[j].key != -1 ; j++){
            if(VR[i][0] == V[j].key) flag1 = 1;
            if(VR[i][1] == V[j].key) flag2 = 1;
        }
        if(flag1 == 0 || flag2 == 0) return ERROR;
        flag1 = flag2 = 0;
        for(int k = i+1 ; VR[k][0]!= -1 && VR[k][1] != -1 ; k++){
            if(VR[i][0] == VR[k][0] && VR[i][1] == VR[k][1] || VR[i][0] == VR[k][1] && VR[i][1] == VR[k][0]) return ERROR;
        }
    }//O(n^2)
    G.arcnum = i;
    if(G.vexnum == 0) return ERROR;
    for(i = 0 ; i < G.vexnum ; i++){
        G.vertices[i].data.key = V[i].key;
        //Map[V[i].key] = i; 
        G.vertices[i].firstarc = NULL;
        strcpy(G.vertices[i].data.others,V[i].others);
    }
    for(i = 0 ; i<G.vexnum ; i++){
        for(int j = 0; j < G.arcnum ; j++){
            if(V[i].key == VR[j][0]){
                //search(G,VR[j][1])
                for(k = 0; k < G.vexnum ; k++){
                    if(G.vertices[k].data.key == VR[j][1]){
                        index = k;
                        break;
                    }
                }
                if(k == G.vexnum) continue;
                struct ArcNode * A = (struct ArcNode *)malloc(sizeof(struct ArcNode));
                A->adjvex = index;
                A->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = A;
            }
            if(V[i].key == VR[j][1]){
                for(k = 0; k < G.vexnum ; k++){
                    if(G.vertices[k].data.key == VR[j][0]){
                        index = k;
                        break;
                    }
                }
                if(k == G.vexnum) continue;
                struct ArcNode * A = (struct ArcNode *)malloc(sizeof(struct ArcNode));
                A->adjvex = index;
                A->nextarc = G.vertices[i].firstarc;
                G.vertices[i].firstarc = A;
            }
        }
    }
    return OK;

    /********** End **********/
}


status DestroyGraph(ALGraph &G){
    int i;
    ArcNode *p,*q;
    for(i=0;i<G.vexnum;i++){
        p=G.vertices[i].firstarc;
        while(p){
            q=p->nextarc;
            delete p;
            p=q;
        }
    }
    G.vexnum=0;
    G.arcnum=0;
    return OK;
}

int LocateVex(ALGraph G,KeyType u){
    int i;
    for(i=0;i<G.vexnum;i++){
        if(G.vertices[i].data.key==u)
            return i;
    }
    return -1;
}

status PutVex(ALGraph &G,KeyType u,VertexType value)
{
    int location;
    if((location = LocateVex(G,u)) == -1) return ERROR;
    for (int i = 0 ; i < G.vexnum ; i++) 
        if(value.key == G.vertices[i].data.key) return ERROR;
    G.vertices[location].data = value;
    return OK;
}



int FirstAdjVex(ALGraph G,KeyType u){
    int location;
    ArcNode *p;
    if((location = LocateVex(G,u)) == -1) return -1;
    p = G.vertices[location].firstarc;
    if(p) return p->adjvex;
    else return -1;
}

int NextAdjVex(ALGraph G,KeyType v,KeyType w)
//v对应G的一个顶点,w对应v的邻接顶点；操作结果是返回v的（相对于w）下一个邻接顶点的位序；如果w是最后一个邻接顶点，或v、w对应顶点不存在，则返回-1。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location;
    if((location = LocateVex(G,v)) == -1) return -1;
    ArcNode * P = G.vertices[location].firstarc;
    while(P){
        if(G.vertices[P->adjvex].data.key == w) 
            if(P->nextarc) return P->nextarc->adjvex;
            else return -1;

        P = P->nextarc;
    }
    return -1;

    /********** End **********/
}

status InsertVex(ALGraph &G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    if(G.vexnum == MAX_VERTEX_NUM) return ERROR;
    if(LocateVex(G,v.key) != -1) return ERROR;
    G.vertices[G.vexnum].firstarc = nullptr;
    G.vertices[G.vexnum++].data = v;
    return OK;
//可以初始化连线
    /********** End **********/
}


status DeleteVex(ALGraph &G,KeyType v)
//在图G中删除关键字v对应的顶点以及相关的弧，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location = LocateVex(G, v);
    if(location == -1) return ERROR;
    ArcNode *p = nullptr,*q = nullptr;
    p = G.vertices[location].firstarc;
    while(p){
        q = p->nextarc;
        free(p);
        p = q;
        G.arcnum--;
    }//
    for(int j = location+1 ; j < G.vexnum ; j++){
        G.vertices[j-1] = G.vertices[j];
    }
    G.vexnum--;//
    if(G.vexnum == 0) return ERROR;
    for (int k = 0 ; k < G.vexnum ; k++){
        p = G.vertices[k].firstarc;
        if(p && p->adjvex == location) {
            q = p->nextarc;
            free(p);
            G.vertices[k].firstarc = q;
            p = q;
        }
        q = p;
        while(q){
            if(q->adjvex > location){
                q->adjvex--;
                p = q; 
                q = q->nextarc;
            }
            else if(q->adjvex < location){
                p = q;
                q = q->nextarc;
            }
            else{
                p->nextarc= q->nextarc;
                free(q);
                q = p->nextarc;
            }
        }
    }
    return OK;
    /********** End **********/
}

status InsertArc(ALGraph &G,KeyType v,KeyType w)
//在图G中增加弧<v,w>，成功返回OK,否则返回ERROR
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int location1 = LocateVex(G,v);
    if(location1 == -1) return ERROR;
    int location2 = LocateVex(G,w);
    if(location2 == -1) return ERROR;
    ArcNode *P = G.vertices[location1].firstarc;
    while(P){
        if(P->adjvex == location2) return ERROR;
        P = P->nextarc;
    }
    ArcNode * P1 = (ArcNode *)malloc(sizeof(ArcNode)), *P2 = (ArcNode *)malloc(sizeof(ArcNode));
    P1->adjvex = location2;
    P1->nextarc = G.vertices[location1].firstarc;
    P2->adjvex = location1;
    P2->nextarc = G.vertices[location2].firstarc;
    G.vertices[location1].firstarc = P1;
    G.vertices[location2].firstarc = P2;
    G.arcnum++;
    return OK;
    /********** End **********/
}

status DeleteArc(ALGraph &G,KeyType v,KeyType w)
//在图G中删除弧<v,w>，成功返回OK,否则返回ERROR
{
    int location1 = LocateVex(G,v);
    if(location1 == -1) return ERROR;
    int location2 = LocateVex(G,w);
    if(location2 == -1) return ERROR;
    ArcNode *P = G.vertices[location1].firstarc;
    int cnt = 0;
    ArcNode * Pre;
    if(P->adjvex == location2){
        cnt = 2;
    }
    else{
        while(P){
            if(P->nextarc && P->nextarc->adjvex == location2) {
                cnt = 1;
                Pre = P;
                P = P->nextarc;
                break;
            }
            P=P->nextarc;
        }
    }
    if(cnt == 0) return ERROR;
    if(cnt == 1){
        Pre->nextarc = Pre->nextarc->nextarc;
        free(P);
    }
    if(cnt == 2){
        G.vertices[location1].firstarc = G.vertices[location1].firstarc->nextarc;
        free(P);
    }
    
    P = G.vertices[location2].firstarc;
    cnt = 0;
    Pre = P;
    if(P->adjvex == location1){
        cnt = 2;
    }
    else{
        while(P){
            if(P->nextarc && P->nextarc->adjvex == location1) {
                cnt = 1;
                Pre = P;
                P = P->nextarc;
                break;
            }

            P=P->nextarc;
        }
    }
    if(cnt == 0) return ERROR;
    if(cnt == 1){
        Pre->nextarc = Pre->nextarc->nextarc;
        free(P);
    }
    if(cnt == 2){
        G.vertices[location2].firstarc = G.vertices[location2].firstarc->nextarc;
        free(P);
    }
    
    G.arcnum--;
    return OK;

    /********** End **********/
}



status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int i = 0;
    if(!G.vexnum) return ERROR;
    int visited[1000] = {0};
    for(; i < G.vexnum ; i++){
        if(visited[i] == 0){
            DFS(G,G.vertices[i],visited,i,visit);
        }
    }
    return OK;
    /********** End **********/
}

void DFS(ALGraph &G,VNode V, int (&visited)[1000], int i,void (*visit)(VertexType)){
    visited[i] = 1;
    visit(V.data);
    ArcNode * next = V.firstarc;
    while(next){
        if(!visited[next->adjvex])
            DFS(G,G.vertices[next->adjvex],visited,next->adjvex,visit);
            next = next->nextarc;
    }
    
}

status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    VNode VQueue[1000];
    int head = 0,rear = 0;
    bool isvisited[1000] = {false};
    VNode Vnow;
    for(int i = 0 ; i < G.vexnum ; i++){
        if(isvisited[i] == 0){
            isvisited[i] = 1;
            VQueue[rear++] = G.vertices[i];
        }
        while(head < rear){
            Vnow = VQueue[head++];
            visit(Vnow.data);
            ArcNode * next = Vnow.firstarc;
            while(next){
                if(!isvisited[next->adjvex]){
                    isvisited[next->adjvex] = true;
                    VQueue[rear++] = G.vertices[next->adjvex];
                }
                next = next->nextarc;
            }

        }
    }
    return OK;
    /********** End **********/
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE * fp = fopen(FileName,"w");
    fprintf(fp,"%d %d %d ",G.vexnum,G.arcnum,G.kind);
    for(int i = 0 ; i < G.vexnum ; i++){
        fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
        ArcNode * P = G.vertices[i].firstarc;
        while(P){
            fprintf(fp,"%d ",P->adjvex);
            P = P->nextarc;
        }
        fprintf(fp,"%d ",-1);
    }
    fclose(fp);
    return OK;
    /********** End 1 **********/
}

status LoadGraph(ALGraph &G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE * fp = fopen(FileName,"r");
    if(!fp) return ERROR;
    fscanf(fp,"%d %d %d ",&G.vexnum,&G.arcnum,&G.kind);
    int i = 0;
    while(i<G.vexnum){
        fscanf(fp,"%d %s ", &G.vertices[i].data.key,G.vertices[i].data.others);
        G.vertices[i].firstarc = nullptr;
        int adj;
        ArcNode * P, * Q;
        fscanf(fp,"%d ",&adj);
        if(adj!=-1){
            Q = (ArcNode *)malloc(sizeof(ArcNode));
            Q->adjvex = adj;
            Q->nextarc = nullptr;
            G.vertices[i].firstarc = Q;
            while(fscanf(fp,"%d ",&adj)&&adj != -1){
                P = Q;
                Q = (ArcNode *)malloc(sizeof(ArcNode));
                Q->adjvex = adj;
                Q->nextarc = nullptr;
                P->nextarc = Q;
            }
        }
        i++;
    }
    fclose(fp);
    return OK;
    /********** End 2 **********/
}

int * Path_Length_to_v(ALGraph G,KeyType v){
    int * path = (int *)malloc(sizeof(int)*G.vexnum);
    for(int i = 0 ; i<G.vexnum; i++){
        path[i] = -1;
    }
    int location = LocateVex(G,v);
    path[location] = 0;
    DFS_LEN(G,location,0,path);
    return path;
}

void DFS_LEN(ALGraph G,int location,int len,int * &path){//通过DFS计算每个点到v的距离
//如果未访问或原长度过大，则重新分配
    ArcNode * P = G.vertices[location].firstarc;
    while(P){
        if(path[P->adjvex] == -1 || path[P->adjvex] > len+1){
            path[P->adjvex] = len+1;
            DFS_LEN(G,P->adjvex,len+1,path);
        }
        P = P->nextarc;
    }
}

int * VerticesSetLessThanK(ALGraph &G,KeyType v,int k){
    int location = LocateVex(G,v);
    if(location == -1) return nullptr;
    int * path = Path_Length_to_v(G,v);
    int * ans = (int *)malloc(sizeof(int)*G.vexnum);
    for(int i = 0 ; i < G.vexnum ; i++){
        if(path[i] < k && path[i] != -1){
            ans[i] = 1;
        }
        else ans[i] = 0;
    }
    return ans;
}


int ShortestPathLength(ALGraph G, KeyType v,KeyType w){//求无权图G中从顶点v到顶点w的最短路径长度
    if(G.kind == DG){
        int *path1 = Path_Length_to_v(G,v);
        int *path2 = Path_Length_to_v(G,w);
        int location1 = LocateVex(G,v);
        int location2 = LocateVex(G,w);
        return path1[location2] > path2[location1] ? path2[location1] : path1[location2];
    }
    else{
        int * path = Path_Length_to_v(G,v);
        int location = LocateVex(G,w);
        return path[location];
    }
}

int DFSCountCCP(ALGraph G){
//对图G进行深度优先搜索遍历 返回联通分量个数
    // 请在这里补充代码，完成本关任务
    /********** Begin *********/
    int index = 0;
    int visited[1000] = {false};
    if(!G.vexnum) return ERROR;
    for(int i = 0 ; i<G.vexnum ; i++){
        if(visited[i] == false){
            DFSCount(G,G.vertices[i],visited,i);
            index++;
        }
    }
    return index;
    /********** End **********/
}

void DFSCount(ALGraph G,VNode V, int (&visited)[1000], int i){
    visited[i] = 1;
    ArcNode * next = V.firstarc;
    while(next){
        if(!visited[next->adjvex])
            DFSCount(G,G.vertices[next->adjvex],visited,next->adjvex);
            next = next->nextarc;
    }
    
}//返回树的数量

int ConnectedComponentsNums(ALGraph G){
    if(G.kind == DG) return Strongly_ConnectedComponentsNums(G);
    else{
        return DFSCountCCP(G);
    }
}

int Strongly_ConnectedComponentsNums(ALGraph G){
    //Use Two times DFS
    //DFS(G)
    //Reverse G
    //DFS(G^T) in decreasing order of finish time
    //Count the number of trees in DFS forest
    return 0;//undone
}

int * TopologicalSort(ALGraph G){
    if(G.kind == UDG) return nullptr;
    if(G.kind == DG) return nullptr;
    if(G.kind == UDN) return nullptr;
    if(G.kind == DN) {
        int * ans = (int *)malloc(sizeof(int)*G.vexnum);
        int * inDegree = (int *)malloc(sizeof(int)*G.vexnum);
        for(int i = 0 ; i < G.vexnum ; i++){
            inDegree[i] = 0;
        }
        for(int i = 0 ; i < G.vexnum ; i++){
            ArcNode * P = G.vertices[i].firstarc;
            while(P){
                inDegree[P->adjvex]++;
                P = P->nextarc;
            }
        }
        int index = 0;
        while(index < G.vexnum){
            for(int i = 0 ; i < G.vexnum ; i++){//Please Use Heap
                if(inDegree[i] == 0){
                    ans[index++] = i;
                    inDegree[i] = -1;
                    ArcNode * P = G.vertices[i].firstarc;
                    while(P){
                        inDegree[P->adjvex]--;
                        P = P->nextarc;
                    }
                }
            }
        }
        return ans;
    }
}

void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
}

status Add_GRAPHS(GRAPHS &P,char FileName[]){
    if(P.length == 20) return ERROR;
    strcpy(P.elem[P.length].name,FileName);
    VertexType V[1000];
    KeyType VR[1000][2];
    int i = 0;
    cout << "Please Input the Vertexs' Information of the Graphs" << endl;
    while(1){
        KeyType key;
        char others[20];
        cin >> key;
        cin >> others;
        V[i].key = key;
        strcpy(V[i].others,others);
        if(key == -1) break;
        i++;
    }
    i = 0;
    cout << "Please Input the Edges of the Graphs" << endl;
    while(1){
        KeyType key1,key2;
        cin >> key1;
        cin >> key2;
        VR[i][0] = key1;
        VR[i][1] = key2;
        if(key1 == -1 || key2 == -1) break;
        i++;
    }
    if(CreateGraph(P.elem[P.length].G,V,VR)==ERROR) return ERROR;
    P.length++;
    return OK;
}

status Remove_GRAPHS(GRAPHS &P,char FileName[]){
    if(P.length == 0) return ERROR;
    for(int i = 0 ; i < P.length ; i++){
        if(strcmp(P.elem[i].name,FileName) == 0){
            for(int j = i ; j < P.length-1 ; j++){
                P.elem[j] = P.elem[j+1];
            }
            P.length--;
            return OK;
        }
    }
    return ERROR;
}

status Locate_and_Modi_GRAPHS(GRAPHS &P,ALGraph &G,char FileName[]){
    for(int i = 0 ; i <P.length ; i++){
        if(strcmp(P.elem[i].name,FileName) == 0){
            G = P.elem[i].G;
            return OK;
        }
    }
    return ERROR;
}

status Traverse_GRAPHS(GRAPHS &P){
    for(int i = 0 ; i < P.length ; i++){
        cout << P.elem[i].name << endl;
    }
    return OK;
}