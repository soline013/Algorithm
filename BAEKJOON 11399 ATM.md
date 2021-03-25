# BAEKJOON 11399 ATM.
[11399번: ATM](https://www.acmicpc.net/problem/11399)

### Code.

```python
people = int(input())
time = sorted(list(map(int, input().split())))
sum1 = 0
sum2 = 0

for i in time:
    sum1 += i
    sum2 += sum1
    
print(sum2)
```

`map()`과 `split()`에서 약간 혼란이 있었다.

for문에 List를 사용할 수 있다는 걸 잊지 말자.

### Another Code.

```python
import sys
people = int(sys.stdin.readline())
time = sorted(list(map(int, sys.stdin.readline().split())))
sum1 = 0
sum2 = 0

for i in time:
    sum1 += i
    sum2 += sum1
    
print(sum2)
```

`input()` 대신 `sys.stdin.readline()`을 사용한다.

### Greedy Algorithm.

근사치 추정을 위한 알고리즘으로, 최적의 해에 가까운 값을 구한다.

여러 상황에서 하나를 결정할 때, 매번 최적이라고 생각되는 경우를 선택한다.