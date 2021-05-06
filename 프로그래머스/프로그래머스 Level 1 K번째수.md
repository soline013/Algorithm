# 프로그래머스 Level 1 K번째수.

[코딩테스트 연습 - K번째수](https://programmers.co.kr/learn/courses/30/lessons/42748)

## Code.

```python
def solution(array, commands):
    answer = []
    for i in commands:
        temp = sorted(array[i[0]-1 : i[1]])
        answer.append(temp[i[2] - 1])
    return answer
```

Python은 List를 기본으로 지원하고, 다른 언어의 Array로 생각하면 편하다.

## Another Code.

```python
def solution(array, commands):
return list(map(lambda x:sorted(array[x[0]-1:x[1]])[x[2]-1], commands))
```