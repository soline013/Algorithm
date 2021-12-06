#include <iostream>
#include <cstring>
#include <ctime>
using namespace std;

//전역변수
int N, K;
int W[20], V[20];
int maxprof = -1;

//node.
//For Breadth-first.
class node {
public:
        int level, profit, weight;
};

//node2.
//For Best-first.
class node2 {
public:
	node2(int temp = 0) {}
	int level, profit, weight;
	float bound;

	bool operator<(const node2 &o) const {
		return bound < o.bound;
	}

	bool operator>=(const node2 &o) const {
		return bound >= o.bound;
	}
};

//Queue.
//자료구조에서 구현한 큐를 사용.
template <typename T>
class Queue {
    private:
        T *queue; //Array.
        int capacity; //Array Size.
        int front; //Behind one of First Element(Counterclockwise).
        int rear; //Postion of Last Element.
    
    public:
        Queue(int stackCapacity = 10);
        bool IsEmpty();
        T& Front();
        T& Rear();
        void Push(const T& item);
        void Pop();
};

//Constructor.
template <typename T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity) {
    if (capacity < 1) throw "Stak capacity must me > 0";
    queue = new T[capacity];
    front = rear = 0; //Empty Stack.
}

//Method.
template <typename T>
inline bool Queue<T>::IsEmpty() {
    return front == rear;
}

template <typename T>
inline T& Queue<T>::Front() {
    if (IsEmpty()) throw "Queue is empty. No front element.";
    
    return queue[(front + 1)%capacity];
}

template <typename T>
inline T& Queue<T>::Rear() {
    if (IsEmpty()) throw "Queue is empty. No rear element.";
        
    return queue[rear];
}

template <typename T>
void Queue<T>::Push(const T& item) {
    if ((rear + 1) % capacity == front) {
        T* newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;
        
        if (start < 2) {
            copy(queue+start, queue+start+capacity-1, newQueue);
        } else {
            copy(queue+start, queue+capacity, newQueue);
            copy(queue, queue+rear+1, newQueue+capacity-start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete[]queue;
        queue = newQueue;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = item;
}

template <typename T>
void Queue<T>::Pop() {
    if (IsEmpty()) throw "Queue is empty. Can not delete.";
    front = (front + 1) % capacity;
    queue[front].~T();
}

//MaxHeap.
//자료구조에서 구현한 MaxHeap을 사용하고자 하였으나 문제가 발생하여 변경하였다.
class HeapEmpty {};
class HeapFull {};

template<typename T>
class MaxHeap {
public:
	MaxHeap(int maxSize = 100) : heapSize(0), capacity(maxSize), heap(new T(maxSize)) {}
	~MaxHeap() { delete heap; }
	void Push(const T& data);
	void Pop();
	T& Top() const;
	int Size() const;
	bool IsEmpty() const;

private:
	T* heap;
	int heapSize;
	int capacity;
};

template<typename T>
void MaxHeap<T>::Push(const T& data) {
	try {
		if (Size() == capacity) throw HeapFull();
		heap[heapSize] = data;
		int parent = (heapSize - 1) / 2;
		int child = heapSize;
		
		while ((parent >= 0) && (heap[parent] < heap[child])) {
			T tmp = heap[parent];
			heap[parent] = heap[child];
			heap[child] = tmp;
			child = parent;
			parent = (child - 1) / 2;
		}
		++heapSize;
	}
	catch (HeapFull e) {
		cout << "Heap is full\n";
		exit(2);
	}
}

template<typename T>
void MaxHeap<T>::Pop() {
	try {
		if (IsEmpty()) throw HeapEmpty();
		heap[0] = heap[--heapSize];
		int parent = 0;
		int child = parent * 2 + 1;
		bool placed = false;
		
		while ((!placed) && (child < heapSize)) {
			if ((child < heapSize - 1) && (heap[child] < heap[child + 1]))
				child += 1;
			
			if (heap[parent] >= heap[child]) {
				placed = true;
			} else {
				T tmp = heap[parent];
				heap[parent] = heap[child];
				heap[child] = tmp;
			}
			
			parent = child;
			child = parent * 2 + 1;
		}
	}
	catch (HeapEmpty e) {
		cout << "Heap is empty\n";
		exit(2);
	}
}

template<typename T>
T& MaxHeap<T>::Top() const {
	try {
		if (IsEmpty()) throw HeapEmpty();
		return heap[0];
	}
	catch (HeapEmpty e) {
		cout << "Heap is empty\n";
		exit(2);
	}
}

template<typename T>
int MaxHeap<T>::Size() const {
	return heapSize;
}

template<typename T>
bool MaxHeap<T>::IsEmpty() const {
	return (heapSize == 0);
}

//main.
void backtracking(int i, int profit, int weight);
bool promising(int i, int profit, int weight);
void breadth();
void best();
template<typename T>
float bound(T u);
int main(int argc, char *argv[]) {
	clock_t start, end;
	double duration;	

	//Input.
	cin >> N >> K;
	if ((N < 1) || (N > 20)) { cout << "N의 입력이 잘못되었습니다."; return 0; }
	if ((K < 1) || (K > 20000)) { cout << "K의 입력이 잘못되었습니다."; return 0;}	
	for (int i=0; i<N; i++) {
        	cin >> W[i] >> V[i];
		if ((W[i] < 1) || (W[i] > 1000)) { cout << "W[" << i << "]의 입력이 잘못되었습니다."; return 0; }
		if ((V[i] < 1) || (V[i] > 1000)) { V[i] = 0; cout << "V[" << i << "]의 입력이 잘못되었습니다."; return 0; }
	}

	//Option.
	if (strcmp(argv[1], "backtracking") == 0) {
		start = clock();
        	backtracking(0, 0, 0);
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
    		cout << fixed << "Duration: " << duration << " " << "MAX Value: " << maxprof;
	} else if (strcmp(argv[1], "breadth") == 0) {
		start = clock();
		breadth();
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
    		cout << fixed << "Duration: " << duration << " " << "MAX Value: " << maxprof;
	} else if (strcmp(argv[1], "best") == 0) {
		start = clock();
		best();
		end = clock();
		duration = (double)(end - start) / CLOCKS_PER_SEC;
    		cout << fixed << "Duration: " << duration << " " << "MAX Value: " << maxprof;
	}

	return 0;
}

//Backtracking.
void backtracking(int i, int profit, int weight) {
	if ((weight <= K) && (profit > maxprof))
		maxprof = profit;
	
	if (promising(i, profit, weight)) {
		backtracking(i+1, profit+V[i], weight+W[i]);
		backtracking(i+1, profit, weight);
	}
}

bool promising(int i, int profit, int weight) {
	int j, k;
	int totwei;
	float bound;
	
	if (weight >= K) {return false;}
	else {
		j = i + 1;
		bound = profit;
		totwei = weight;
		while ((j <= N) && (totwei + W[j] <= K)) {
			totwei += W[j];
			bound += V[j];
			j++;
		}
		k = j;
		if (k <= N)
			bound = bound + (K - totwei) * V[k] / W[k];
	}
	return bound > maxprof;
}

//Branch and Bound.
//Breadth-first.
void breadth() {
	Queue<node> que;
	node u, v;

	v.level = 0;
	v.profit = 0;
	v.weight = 0;
	que.Push(v);

	while(!que.IsEmpty()) {
		v = que.Front();
		que.Pop();
		u.level = v.level + 1;
		u.weight = v.weight + W[u.level];
		u.profit = v.profit + V[u.level];
		if (u.weight <= K && u.profit > maxprof)
			maxprof = u.profit;
		if (bound(u) > maxprof)
			que.Push(u);

		u.weight = v.weight; 
		u.profit = v.profit; 
		if (bound(u) > maxprof)
			que.Push(u);	
	}

}

//Best-first.
void best() {
        MaxHeap<node2> pri_que;
        node2 u, v;

        v.level = 0;
        v.profit = 0;
        v.weight = 0;
        v.bound = bound(v);
        pri_que.Push(v);

        while(!pri_que.IsEmpty()) {
                v = pri_que.Top();
                pri_que.Pop();
                u.level = v.level + 1;
                u.weight = v.weight + W[u.level];
                u.profit = v.profit + V[u.level];
                if ((u.weight <= K) && (u.profit > maxprof))
                        maxprof = u.profit;
                u.bound = bound(u);
                if (u.bound > maxprof)
                        pri_que.Push(u);

                u.weight = v.weight;
                u.profit = v.profit;
                u.bound = bound(u);
                if (u.bound > maxprof)
                        pri_que.Push(u);
        }
}

//bound.
template<typename T>
float bound(T u) {
        int j, k;
        int totwei;
        float result;
        if (u.weight >= K) {return 0;}
        else {
                result = u.profit;
                j = u.level + 1;
                while((j <= N) && (totwei + W[j] <= K)){
                        totwei = u.weight + W[j];
                        result += V[j];
                        j++;
                }
                k = j;
                if (k <= N) {
                        result += (K - totwei) * (V[k] / W[k]);
                }
                return result;
        }
}
