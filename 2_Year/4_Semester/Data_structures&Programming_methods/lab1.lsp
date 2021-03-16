( defun SumSquares (x y) (
    (cond ((> x y) nil)
          ((= x y) (* x x))
          ( T (+ (* x x) (SumSquares (+ x 1) y))))))

( defun gcd (x y) (
    (cond ((or (= x 0) (= y 0)) (+ x y))
          ((or (= x 1) (= y 1)) 1)
          ((> x y) (gcd (- x y) y))
          ((>= y x) (gcd (- y x) x)))))

(defun lcm (x y) (/ (* x y) (gcd x y)))

(defun sqrt (a n) (
    (cond ((= n 0) (* 0.5 (+ a 1)))
          (T (* 0.5 (+ (setq res (sqrt a (- n 1))) (/ a res)))))))

(defun fib (n) (
    (cond ((= n 1) 1)
          ((= n 2) 2)
          (T (+ (fib (- n 1)) (fib (- n 2)))))))
