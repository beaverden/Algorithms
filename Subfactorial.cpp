# n! ( 1 - 1/1! + 1/2! - 1/3! + 1/4! - ... +(-1)^n/n!)

n=int(input())

def fact(n):
  s = 1
  for x in range(1,n+1):
    s *= x
  return s
def subfact(n) :
  s = fact(n)
  k = s
  curr = 1
  for x in range(1,n+1):
    curr *= x
    if x%2 == 0:
      s += k//curr
    else :
      s -= k//curr
 
  return s
print(subfact(n))
