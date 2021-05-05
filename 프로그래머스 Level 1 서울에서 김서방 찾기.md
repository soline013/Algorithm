# 프로그래머스 Level 1 서울에서 김서방 찾기.

## Code.

```python
def solution(seoul):
    for i in range(0,len(seoul)):
        if seoul[i] == "Kim":
            answer = "김서방은 "+str(i)+"에 있다"
    return answer
```

```python
def solution(seoul):
    answer = "김서방은 " + str(seoul.index("Kim")) + "에 있다"
    return answer
```

`index()`를 활용하자.

Python은 List를 기본 지원하고, 관련 Method도 많다. 

## Another Code.

```python
def solution(seoul):
    return "김서방은 {}에 있다".format(seoul.index('Kim'))
```

`format()`도 있다.