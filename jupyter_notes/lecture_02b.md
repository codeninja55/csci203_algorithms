# Lecture 02b - Complexity

## More on Complexity 

* Last week we looked at the idea of *Complexity Classes*.
* These included:
  * **Constant:** 
  * ...



## Big $O$ Notation

* ...
* Note that $O(f(n))$ is the set of all functions that behave in the same general way:
  * They all grow at a rate that is *no faster than $f(n)$*.
* We say that ...



## Asymptotic Notation

* It is legitimate to talk about the order of $f(n)$ even if $f(n)$ is badly behaved below $n_0$
* Some texts use the notation $f(n) = O(f(n))$ which, given that $O(f(n))$ is a set, is strictly incorrect.
* **The maximum rule:** $O(f(n) + g(n)) = O(max(f(n), g(n)))$



## Comparing Functions

* 
* If $\lim_{n\to\infty} \frac{f(n)}{g(n)} \in \Bbb{R}^+$ then $f(n) \in O(g(n))$ and $g(n) \in O(f(n))$
* If $\lim_{n\to\infty} \frac{f(n)}{g(n)} = 0$ then $f(n) \in O(g(n))$ but $g(n) \notin O(f(n))$
* If $\lim_{n\to\infty} \frac{f(n)}{g(n)} = +\infty$ then $f(n) \notin O(g(n))$ and $g(n) \in O(f(n))$



## Other Asymptotic Notation: Omega

* ...



## Relating $O$ and $\Omega$

* ...



## Theta ($\Theta$), a tight bound

* ...

## Bounds and Algorithms

* ...



