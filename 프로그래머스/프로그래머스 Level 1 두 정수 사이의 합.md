# 프로그래머스 Level 1 두 정수 사이의 합.

[코딩테스트 연습 - 두 정수 사이의 합](https://programmers.co.kr/learn/courses/30/lessons/12912)

연습문제

## Code.

```python
def solution(a, b):
    answer = 0
    if a > b:
		temp = b
		b = a
		a = temp
    for i in range(a, b+1):
        answer += i
    return answer
```

```python
def solution(a, b):
    answer = 0
    if a > b: a, b = b, a
    for i in range(a, b+1):
        answer += i
    return answer
```

Python은 꼭 temp 등의 변수를 사용하지 않아도,

`a, b = b, a` 처럼 대입이 가능하다.

## Another Code.

```python
def solution(a, b):
    if a > b: a, b = b, a
    return sum(range(a, b+1))
```

그리곤 `sum()` 같은 함수를 사용하자.