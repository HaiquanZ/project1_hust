#include <stdio.h>
#include <stdlib.h>

int visited[2000000] = {0};
int pushed[2000000] = {0};
int visitedVC[2000000] = {0};
int cnt = 0;

int option, chooseFile;

//Xay dung cau truc du lieu: Danh sach ke
typedef struct Node{
	int value;
	struct Node* next;
}Node;

Node* makeNode(int value){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value;
	newNode->next = NULL;
	return newNode;
}

typedef struct Graph{
	int vertices;
	Node** list;
}Graph;

Graph* makeGraph(int v){
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertices = v;
	g->list = (Node**)malloc(v*sizeof(Node*));
	for (int i=0;i<v;i++)
		g->list[i] = NULL;
	
	return g;
}

char rn[][20] = {"","roadNet-CA.txt","roadNet-PA.txt","roadNet-TX.txt"};
char vc[][20] = {"","roadNet-CA.vc","roadNet-PA.vc","roadNet-TX.vc"};

//Tai file do thi
Graph* g;
void input(int t){
	int edge1,edge2,sumVertex;
	sumVertex = -1;
	char tmp[1000];
	g = makeGraph(2000000);
		FILE *f;
		f = fopen(rn[t],"r");
		if (f == NULL){
			printf("Loi mo File!");
			exit(1);
		}
		for (int i=1;i<=4;i++)
			fgets(tmp, 1000, f);
		//Xu ly du lieu cac canh cua do thi
		do{
			fscanf(f, "%d\t%d", &edge1, &edge2);
			Node* newNode = makeNode(edge2);
			newNode->next = g->list[edge1];
			g->list[edge1] = newNode;
			if (edge1 > sumVertex) sumVertex = edge1;
			if (edge2 > sumVertex) sumVertex = edge2;
		}while(!(feof(f)));
		g->vertices = sumVertex;
		fclose(f);
	printf("Da nap xong du lieu\n");
}
//Duyet theo chieu sau
void DFS(int v){
	Node* st = makeNode(v);
	while(st != NULL){
		int tmpValue = st->value;
		visited[tmpValue] = 1;
		cnt++;
		printf("%d - %d\n",cnt,tmpValue);
		st=st->next;
		Node* tmp = g->list[tmpValue];
		while(tmp){	
			if(visited[tmp->value] == 0 && pushed[tmp->value] == 0){
				pushed[tmp->value] = 1;
				Node* newNode = makeNode(tmp->value);
				newNode->next = st;
				st = newNode;
			}
			tmp = tmp->next;
		}
	}
}

void checkDFS(){
	cnt = 0;
	int sumVertex;
	sumVertex = g->vertices;
	for (int i=0;i<=sumVertex;i++){
		if (g->list[i] == NULL) visited[i] = -1;
		else visited[i] = 0;
		pushed[i] = 0;
	}
	
	for (int i=0;i<=sumVertex;i++)
		if (visited[i] == 0) DFS(i);
	//Check
	for (int i=0;i<=sumVertex;i++)
		if(visited[i] == 0){
			printf("Duyet sai do thi!\n");
			break;
		}
	printf("Da duyet theo chieu sau\n");
}
//Day node vao hang doi
Node* pushNode(Node* h, int value){
	Node* newNode = makeNode(value);
	if (h == NULL) h = newNode;
	else{
		Node* tmp = h;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = newNode;
	}
	return h;
}
//Duyet theo chieu rong
void BFS(int v){
	Node* queue = makeNode(v);
	visited[v] = 1;
	cnt++;
	printf("%d - %d\n",cnt,v);
	while(queue != NULL){
		int u;
		u = queue->value;
		queue = queue->next;
		while (g->list[u] != NULL){
			int t;
			t = g->list[u]->value;
			if (visited[t] == 0){
				queue = pushNode(queue, t);
				visited[t] = 1;
				cnt++;
				printf("%d - %d\n",cnt,t);
			}
			g->list[u] = g->list[u]->next;
		}
	}
}

void checkBFS(){
	cnt = 0;
	int sumVertex;
	sumVertex = g->vertices;
	
	for (int i=0;i<=sumVertex;i++)
		if (g->list[i] == NULL) visited[i] = -1;
		else 
		visited[i] = 0;
	
	for (int i=0;i<=sumVertex;i++)
		if (visited[i] == 0) BFS(i);
	//check
	for (int i=0;i<=sumVertex;i++)
		if (visited[i] == 0){
			printf("Duyet sai do thi!\n");
			break;
		}
	printf("Da duyet theo chieu rong\n");
}
//Kiem tra tap phu dinh
int checkVertexcover(){
	int totalVertex;
	int v;
	totalVertex = g->vertices;
	for (int i=0;i<=totalVertex;i++)
		visitedVC[i] = 0;
	char c,str[1000];
	//doc du lieu
	FILE *f;
	f = fopen(vc[chooseFile],"r");
	if (f == NULL){
		printf("Loi mo file!\n");
		exit(1);
	}
	fgets(str,1000,f);
	fgets(str,1000,f);
	fgets(str,1000,f);
	do{
		//danh dau nhung dinh trong tap dinh Vertex Cover
		fscanf(f,"%c %d",&c,&v);
		visitedVC[v] = 1;
	}while (!(feof(f)));
	fclose(f);
	Node* tmp;
	for (int i=0;i<=totalVertex;i++){
		tmp = g->list[i];
		while(tmp != NULL){
			if (visitedVC[i] == 0 && visitedVC[tmp->value] == 0){
				printf("Canh %d - %d khong chua dinh nao trong tap phu dinh\n",i,tmp->value);
				return 0;
			}
			tmp = tmp->next;
		}
	}
	
	return 1;
}


int main(){
	chooseFile = 0;
	while(1){
		//Hien thi danh muc lua chon
		printf("Mon hoc: Project I\n");
		printf("----------------------------\n");
		printf("Danh muc cac lua chon:\n");
		printf("1. Tai file do thi\n");
		printf("2. Duyet do thi theo chieu rong - BFS\n");
		printf("3. Duyet do thi theo chieu sau - DFS\n");
		printf("4. Kiem tra tap dinh bao phu\n");
		printf("5. Thoat\n");
		printf("----------------------------\n");
		printf("Nhap lua chon: ");
		scanf("%d",&option);
		
		//Xu ly tung lua chon
		if (option == 1){
			system("cls");
			printf("Chon file do thi:\n");
			printf("1. California: roadNet-CA.txt\n");
			printf("2. Pennsylvania: roadNet-PA.txt\n");
			printf("3. Texas: roadNet-TX.txt\n");
			printf("Nhap lua chon: ");
			scanf("%d",&chooseFile);
			if (chooseFile >= 1 && chooseFile <= 3) input(chooseFile);
			else printf("Nhap sai lua chon!\n");
		}
		else if (option == 2){
			system("cls");
			if (chooseFile <1 || chooseFile >3) printf("Chua nap do thi!\n");
			else{
				checkBFS();
			}
		}
		else if (option == 3){
			system("cls");
			if (chooseFile < 1 || chooseFile >3) printf("Chua nap du lieu!\n");
			else checkDFS();
		}
		else if (option == 4){
			system("cls");
			if (chooseFile <1 || chooseFile > 3) printf("Chua nap do thi!\n");
			else{
				if (checkVertexcover()) 
					printf("%s la tap dinh bao phu cua do thi %s\n",vc[chooseFile],rn[chooseFile]);
				else{
					printf("%s khong phai la tap dinh bao phu cua do thi %s\n",vc[chooseFile],rn[chooseFile]);
				}
			}
		}
		else if (option == 5) break;
		else printf("Nhap sai lua chon! Nhap lai\n");
	}
	
	//Giai phong bo nho
	for(int j=0;j<=2000000;j++) free(g->list[j]);
	return 0;
}
