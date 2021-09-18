# Algorithm

## Algorithm

- A general step-by-step procedure for producing the solution to each instance.
- 문제에 대한 답을 찾기 위한 계산하는 절차
- 단계별로 주의 깊게 설계된 계산 과정
- 컴퓨터가 어떤 일을 수행하기 위한 단계적 방법
- 유한한 단계를 통해 문제를 해결하기 위한 절차나 방법
    - 각 단계는 하나 또는 그 이상의 연산을 필요
- 연산은
    - 명확성: 각 연산들은 명확한 의미가 있어야 함
    - 효율성: 각 연산은 사람이 일정 시간 내에 수행할 수 있어야 함
    - 종결성: 유한 번의 연산 후에 끝나야 함
    - 입력, 출력: 외부로부터 입력 가능, 하나 이상의 결과가 나와야 함

## 표기

1. 자연어: 한글 또는 영어
2. 프로그래밍 언어: C, C++, JAVA, Python
3. 의사코드(Pseudo-code)
    - 직접 실행할 수 있는 프로그래밍 언어는 아니나, 실제 프로그램에 가깝게 계산 과정을 표현할 수 있는 언어
    - 알고리즘은 보통 의사코드로 표현한다.
    - 강의에서는 C/C++에 가까운 의사코드를 사용한다.

## C++과 의사코드의 차이점

1. 배열 인덱스의 범위에 제한 없음: S[5..20]
    1. C++은 반드시 0부터 시작
    2. 의사코드는 임의의 값 사용 가능
    3. Input, Output 명세에서 범위에 대한 서술 필요(e.g. Algorithm 1.1)

2. 프로시저의 파라미터 크기의 가변성 허용
    - e.g. `void pname(A[][]) { ... }`

3. 지역 배열에 변수 인덱스 허용
    - e.g. `keytype S([low..high]);`

4. 수학적 표현식 허용(e.g. Page 7)
    - `low <= x && x <= high` → low ≤ x ≤ high
    - `temp = x; x = y; y = temp;` → exchange x and y

5. C++에 없는 타입 사용 가능
    - index: 첨자로 사용되는 정수 변수
    - number: 정수(int) 또는 실수(float) 모두 사용 가능
    - bool: "true"나 "false" 값을 가질 수 있는 변수
    - keytype: the data type of key

6. key: Each item uniquely identifies a record

7. 수식적 표현과 C++에서의 표현 병행
    - Logical Operator: and(&&), or(||), not(!)
    - Relational Operator: x=y(x==y), (x!=y), x≤y(x<=y), (x>=y)

8. 제어 구조
    - repeat (n times) { ... }
    - 그래도 index 정의가 필요하기 때문에 for이 편리하다.

9. 프로시저와 함수
    - 프로시저: void pname(...) {...}
    - 함수: returntype fname (...) {... return x;}

10. 참조 파라미터(Reference Parameter)를 사용하여 프로시저의 결과값 전달
    - 배열: 참조 파라미터로 전달
    - 기타: 데이터 타입 이름 뒤에 &를 붙임
    - const 배열: 전달되는 배열의 값이 불변

## Basic Structure

- Definition Part
    - Problem, Input, Output에 관한 설명 기술

- Procedure Part
    - ReturnType procedureName(parameters) {

        Body;

        }

- e.g. Algorithm 1.1, 1.2, 1.3, 1.4

## Efficient Algorithm

### 순차검색 알고리즘(Sequential Search)

- 문제: 크기가 n인 배열 S에 x가 있는가?
- 입력: (1)양수, n (2)배열 S[1..n], (3)키x
- 출력: S에서 x가 있는 위치, 만약 없으면 0.
- 알고리즘(자연어):
    - x와 같은 아이템을 찾을 때까지 S에 있는 모든 아이템을 차례로 검사한다.
    - 만일 x와 같은 아이템을 찾으면 S안의 위치 값을 전달하고 S를 모두 검사하고도 찾지 못하면 0을 전달한다.

- 알고리즘(의사코드)

    ```cpp
    void seqsearch(int n,				//입력(1)
                   const keytype S[],	//입력(2)
    	           keytype x,		    //입력(3)
    			   index& location)	{	//출력
    	location = 1;
    	while(location <= n && [location] != x)
    		location++;
    	if (location > n)
    		location = 0;
    }
    ```

    - while-루프: 아직 검사할 항목이 있고, x를 찾지 못했나?
    - if-문: 모두 검사하였으나, x를 찾지 못했나?

- 분석
    1. 순차검색 알고리즘으로 키를 찾기 위해서 S에 있는 항목을 몇 개나 검색해야 하는가?
        - 키와 같은 항목의 위치에 따라 다르다.
        - 최악의 경우: n

    1. 좀 더 빨리 찾을 수는 없는가?
        - S에 있는 항목에 대한 정보가 없으면, 더 빨리 찾을 수 없다.

### 이분탐색 알고리즘(Binary Search)

- 문제: 크기가 n인 정렬된 배열 S에 x가 있는가?
- 입력: (1)양수, n (2)배열[1..n] (3)키
- 출력: S에서 x가 있는 위치, 만약 없으면 0.
- 알고리즘(의사코드)

    ```cpp
    void binsearch(int n,				//입력(1)
    			   const keytype S[],	//입력(2)
    			   keytype x,			//입력(3)
    			   index& location) {	//출력
    	index low, high, mid;
    	low = 1; high = n;
    	location = 0;
    	while (low <= high && location == 0) {
    		mid = (low + high) / 2; //정수 나눗셈
    		if (x == S[mid]) location = mid;
    		else if (x < S[mid]) high = mid - 1;
    		else low = mid + 1;
    	}
    }
    ```

    - while-루프: 아직 검사할 항목이 있고, x를 찾지 못했나?

- 분석
    - 이분검색 알고리즘으로 키를 찾기 위해서 S에 있는 항목을 몇 개나 검색해야 하는가?
    - while 문을 수행할 때마다 검색 대상의 총 크기가 반씩 감소하기 때문에, 최악의 경우도 lg n+1개만 검사하면 된다. 시간복잡도 O(log N)

        [이진 탐색과 시간 복잡도 분석 (Binary Search and its Time Complexity Analysis)](https://jwoop.tistory.com/9)

### 피보나치 수열(Fibonacci)

- 정의: $f_0 = 0, \, f_1 = 1, \, f_n = f_{n-1} + f_{n-2} \ (for \ n >= 2)$
- 문제: n번째 피보나치 수를 구하라.
- 입력: 양수 n
- 출력: n번째 피보나치 수
- 알고리즘(의사코드)

    ```cpp
    int fib(int n) {
    	if (n <= 1)
    		return n;
    	else
    		return fib(n-1) + fib(n-2);
    }
    ```

- 분석
    - 피보나치 수 구하기 재귀 알고리즘은 수행속도가 매우 느리다.
    - 이유: 같은 피보나치 수를 중복 계산한다.
    - e.g. fib(5) 계산에 fib(2) 3번 중복 계산

    ![스크린샷 2021-09-17 23.54.45.png](Algorithm%20cde76e3c9c6f45be862bd122fc287f18/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA_2021-09-17_23.54.45.png)

    ![스크린샷 2021-09-17 23.55.00.png](Algorithm%20cde76e3c9c6f45be862bd122fc287f18/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA_2021-09-17_23.55.00.png)

    ![스크린샷 2021-09-17 23.56.40.png](Algorithm%20cde76e3c9c6f45be862bd122fc287f18/%E1%84%89%E1%85%B3%E1%84%8F%E1%85%B3%E1%84%85%E1%85%B5%E1%86%AB%E1%84%89%E1%85%A3%E1%86%BA_2021-09-17_23.56.40.png)