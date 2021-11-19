# LeetCode Medium 46. Permutations.
## Summary.

[Permutations - LeetCode](https://leetcode.com/problems/permutations/)

[[Python] 순열, 조합 구현하기 - itertools & recursion](https://cotak.tistory.com/70)

순열 알고리즘 문제이다.

---

## Code.

```python
from itertools import permutations

class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        arr = list(list(permutations(nums, len(nums))))
    
        return arr
```

itertools를 사용하면 쉽고 빠르게 순열을 구현할 수 있다.

---

## Another Code.

```python
def gen_permutations(arr, n):
	result = []

	if n == 0:
		return [[]]

	for i, elem in enumerate(arr):
		for P in gen_permutations(arr[:i] + arr[i+1:], n-1):
			result += [[elem]+P]

	return result

arr = [0, 1, 2, 3, 4, 5]
print(gen_permutations(arr, 3))
```

재귀를 사용하여 문제를 해결할 수도 있다.