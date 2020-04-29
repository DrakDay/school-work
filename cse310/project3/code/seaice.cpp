#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;
struct vertex {
	float num;
	int name;
	struct vertex* next;
};
struct adjlists{
	struct vertex* head;
};

void dfs(adjlists * list);
void DFSUtil(adjlists * list, bool visisted[], int v);


int main(){
	vertex ** graph = new vertex*[3969];
	adjlists * adjlist = new adjlists[3969];
	adjlists * adjlist2 = new adjlists[3969];
	adjlists * adjlist3 = new adjlists[3969];
	for(int i =0; i < 3969 ; i++){
		graph[i] = new vertex[832];
		graph[i]->next = NULL;
		graph[i]->name = i;
		adjlist[i].head = NULL;
		adjlist2[i].head = NULL;
		adjlist3[i].head = NULL;	
	}

	for(int i = 0; i <  16; i++) {
		for (int j = 1; j <  53; j++) {
			string week = "";
			if (j < 10) { 
				 week = "0" + to_string(j); 
			}
			else { 
				 week = to_string(j); 
			}
			string year = to_string(1990 + i);	
			//cout << year << endl;
			string filename = "CS310_project_subregion/" + year + "/Beaufort_Sea_diffw" + week + "y" + year + "+landmask";
			
			ifstream inputfile(filename, ios::in | ios::binary);
			float datain = 0;
			for (int k = 0; k <3969 ; k++) {
				inputfile.read((char*)&datain, 4);
				graph[k][i*52+j-1].num = datain;
			}			
			inputfile.close();
		}
	}
	
	for(int i =0; i< 3969 ; i ++){
		// compute mean for x (i)
		float xsum = 0;  int xmissingcount = 0;
		for (int k = 0; k < 832; k++) {
			if (graph[i][k].num == 157) { xmissingcount++; }
			else { xsum = xsum + graph[i][k].num; }
		}
		float xmean = xsum / float(832 - xmissingcount);

		//compute sxx
		float sxx = 0;
		for (int k = 0; k < 832; k++) {
			if (graph[i][k].num == 157) { continue; }
			else { sxx = sxx + pow(graph[i][k].num - xmean, 2.0); }
		}

		for(int j = i+1; j < 3969;j ++){
			// if it is a land we skip it
			if(graph[i][0].num == 168 ) {continue;}
			if(graph[j][0].num == 168 ) {continue;}

			// compute mean of y (j)
			float ysum = 0; int ymissingcount = 0;
			for(int k = 0 ;k <832; k ++){
				if(graph[j][k].num == 157) {ymissingcount++; }
				else {ysum = ysum+graph[j][k].num;}
			}
			float ymean = ysum / float(832 - ymissingcount);

			//compute syy
			float syy = 0;
			for(int k = 0; k < 832 ; k ++){
				if(graph[j][k].num == 157) {continue;}
				else{ syy = syy + pow(graph[j][k].num - ymean , 2.0);}
			}

			//compute sxy
			float sxy = 0; 	
			for(int k = 0; k < 832 ; k ++){
				if(graph[i][k].num == 157) { continue;}
				else if(graph[j][k].num == 157) { continue;}
				else { sxy = sxy + (graph[i][k].num - xmean)*(graph[j][k].num - ymean);}
			}
					
			//compute r
			float r = sxy / sqrt(sxx*syy);
			r = fabs(r);
			if(r > 0.90){
				vertex* newnode = new vertex;
				newnode->name = graph[j]->name;
				newnode->next = adjlist[i].head;
				adjlist[i].head = newnode;

				vertex * newnode2 = new vertex;
				newnode2-> name = graph[i]->name;
				newnode2-> next = adjlist[j].head;
				adjlist[j].head = newnode2;

			if (r > 0.925) {
				vertex* newnode = new vertex;
				newnode->name = graph[j]->name;
				newnode->next = adjlist2[i].head;
				adjlist2[i].head = newnode;

				vertex * newnode2 = new vertex;
				newnode2->name = graph[i]->name;
				newnode2->next = adjlist2[j].head;
				adjlist2[j].head = newnode2;
			}

			if (r > 0.95) {
				vertex* newnode = new vertex;
				newnode->name = graph[j]->name;
				newnode->next = adjlist3[i].head;
				adjlist3[i].head = newnode;

				vertex * newnode2 = new vertex;
				newnode2->name = graph[i]->name;
				newnode2->next = adjlist3[j].head;
				adjlist3[j].head = newnode2;
			}
			}			
		}	
	}

//print stat of number of degree foor rth 0.95
	cout << "--------stat for thereshold 0.9--------"<< endl;
	int max = 0;
	for( int i = 0 ; i < 3969;i++){
		vertex * node = adjlist[i].head;
		int length = 0;
		while(node){
			length++;
			node = node->next;
		}
		if(length > max)
			max = length;
	}
	int * arr = new int[max+1];
	for(int i =0; i < max+1 ; i++){ arr[i] = 0; }
	
	for(int i = 0; i < 3969; i++) {
		int length = 0;
		vertex* node = adjlist[i].head;
		while(node){
			length++;
			node = node->next;
		}
		arr[length] = arr[length] + 1;
	}
	for(int i = 0; i < max+1; i ++){
		cout<< "degree " <<  i << " : " << arr[i] <<endl;		
	}
	delete[] arr;

	//print stat of number of degree foor rth 0.925
	cout << endl;
	cout << "--------stat for thereshold 0.925--------" << endl;
	max = 0;
	for (int i = 0; i < 3969; i++) {
		vertex * node = adjlist2[i].head;
		int length = 0;
		while (node) {
			length++;
			node = node->next;
		}
		if (length > max)
			max = length;
	}
	int * arr1 = new int[max + 1];
	for (int i = 0; i < max + 1; i++) { arr1[i] = 0; }

	for (int i = 0; i < 3969; i++) {
		int length = 0;
		vertex* node = adjlist2[i].head;
		while (node) {
			length++;
			node = node->next;
		}
		arr1[length] = arr1[length] + 1;
	}
	for (int i = 0; i < max + 1; i++) {
		cout << "degree " << i << " : " << arr1[i] << endl;
	}
	delete[] arr1;

	//print stat of number of degree foor rth 0.9
	cout << endl;
	cout << "--------stat for thereshold 0.95--------" << endl;
	max = 0;
	for (int i = 0; i < 3969; i++) {
		vertex * node = adjlist3[i].head;
		int length = 0;
		while (node) {
			length++;
			node = node->next;
		}
		if (length > max)
			max = length;
	}
	int * arr2 = new int[max + 1];
	for (int i = 0; i < max + 1; i++) { arr2[i] = 0; }

	for (int i = 0; i < 3969; i++) {
		int length = 0;
		vertex* node = adjlist3[i].head;
		while (node) {
			length++;
			node = node->next;
		}
		arr2[length] = arr2[length] + 1;
	}
	for (int i = 0; i < max + 1; i++) {
		cout << "degree " << i << " : " << arr2[i] << endl;
	}
	delete[] arr2;

	//dfs
	cout << endl;
	cout << "---------THRESHOLD 0.9 COMPONENT ANALYSIS-----------" << endl;
	dfs(adjlist);
	cout << endl;
	cout << "---------THRESHOLD 0.925 COMPONENT ANALYSIS-----------" <<endl;
	dfs(adjlist2);
	cout << endl;
	cout << "---------THRESHOLD 0.95 COMPONENT ANALYSIS-----------"<<endl;
	dfs(adjlist3);
}

int size = 0;

void dfs(adjlists * list){
	int count = 0;
	bool * visited = new bool[3969];
	for(int i = 0; i < 3969; i ++){
		visited[i] = false;
	}
	int arr[3969];
	for (int i = 0; i < 3969; i++) {
		arr[i] = 0;
	}
	for(int i = 0; i < 3969; i++){
		if(visited[i] == false){
			DFSUtil(list,visited,i);
			count++;
			arr[size] = arr[size] + 1;
			size = 0;
		}
		
	}
	cout << "number of components :" << count << endl;
	for (int i = 0; i < 3969; i++) {
		if (arr[i] != 0) {
			cout << "Component " << i << " #: " << arr[i] << endl;
		}
	}
}

void DFSUtil(adjlists * list, bool visited[], int v){
	size++;
	visited[v] = true;
	vertex * node = list[v].head;

	while(node != NULL){
		int vertex = node->name;
		if(visited[vertex] == false){ DFSUtil(list,visited,vertex);}
		node = node->next;
	}
}
	
