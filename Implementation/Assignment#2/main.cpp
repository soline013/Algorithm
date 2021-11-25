#include<iostream>
#include<cstring>
#define MAX_N 300
using namespace std;

//전역 변수.
int cnt;		     //Count Path. 
int N;                       //[N]umber of vertex
int W[MAX_N + 1][MAX_N + 1]; //[W]eight array
int D[MAX_N + 1][MAX_N + 1]; //[D]istance array
int P[MAX_N + 1][MAX_N + 1]; //[P]ath array

void printPath(int a, int b);
void countPath(int a, int b);
int main(int argc, char *argv[]) {
	cin >> N;

	//Init W.
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			cin >> W[i][j];
			if ((W[i][j] == 0) && (i != j)) {W[i][j] = MAX_N;}
        	}
    	}

    	//TODO : Floyd's Alogirhtm	
	//Init P, D.
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++) {
			P[i][j] = 0;
			D[i][j] = W[i][j];
		}

	//Floyd's Algorithm.
	for (int k=0; k<N; k++)
		for (int i=0; i<N; i++)
			for (int j=0; j<N; j++)
				if (D[i][j] > D[i][k] + D[k][j]) { 
					D[i][j] = D[i][k] + D[k][j];	
					P[i][j] = k + 1;
				}
	
	//Option is array.
    	if (strcmp(argv[1], "array") == 0) {
        // option : "array"
        // output : "N\nD array \n P array"
        // ex) 아래 형식으로 N, D와 P를 출력해야함.
        //      +----------+
        //      | 3        |
        //      | 1 2 3    |
        //      | 4 5 6    |
        //      | 7 8 9    |
        //      | 11 12 13 |
        //      | 14 15 16 |
        //      | 17 18 19 |	
        //      +----------+
		//Print N.
		cout << N << endl;
        	
		//Print D.
		for (int i=0; i<N; i++) {
            		for (int j=0; j<N; j++) {
                		cout << D[i][j] << ' ';
            		}
            	cout << '\n';
        	}

		//Print P.
        	for (int i=0; i<N; i++) {
            		for (int j=0; j<N; j++) {
                		cout << P[i][j] << ' ';
            		}
            	cout << '\n';
        	}
    	}
	//Option is path.
	else if (strcmp(argv[1], "path") == 0) {
        // OUTPUT : "최소 이동 거리와 해당 경로"
        // ex) 아래 박스 있는 값처럼 출력하면 됨.
        //     아래 출력 예시는 첫째줄에 각 정점에서 정점으로 이동하는 경로와 둘째줄에 이동 거리를 의미
        //       +-----------+
        //       | 0         | -> 노드 1에서 노드 1로 가는 최소 이동 거리 (이동거리가 0)
        //       | 4 1 3 5 2 | -> 노드 1에서 노드 2로 가는 최소 이동 거리와 그 옆에는 최소 이동 경로
        //       | 2 1 3     | -> 노드 1에서 노드 3로 가는 최소 이동 거리와 그 옆에는 최소 이동 경로
        //       | ...       | -> 이하 생략
        //       +-----------+
    		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				//Case Zero.
				if ((D[i][j] == 0) && (W[i][j] == 0)) {
					cout << "0 " << endl;
				}
				//Case Direct.
				else if (W[i][j] == D[i][j]) {
					cout << "2 " << i+1 << " " << j+1 << endl;
				}
				//Case Path.
				else if (W[i][j] != D[i][j]) {
					cnt = 2;
					countPath(i, j);
					
					cout << cnt << " " << i+1 << " ";
					printPath(i, j);
					cout << j+1 << endl;
				}
			}
		}
	}
    	return 0;
}

void printPath(int a, int b) {
	if (P[a][b] != 0) {
		printPath(a, P[a][b]-1);
		cout << P[a][b] << " ";
		printPath(P[a][b]-1, b);
	}
}

void countPath(int a, int b) {
	if (P[a][b] != 0) {
		countPath(a, P[a][b]-1);
		cnt += 1;
		countPath(P[a][b]-1, b);
	}
}

