(defun get_primes (num k) (
    (cond ((null num) ())
          ((equal num 1) (1))
          ((> (* 2 k) num) (list num))
          ((= (mod num k) 0) (cons k (get_primes (/ num k) 2)))
          (T (get_primes num (+ k 1))))))

(defun reverse (lst) (
    (cond ((null lst) ())
          ((atom lst) (list lst))
          ((and (atom (car lst)) (null (cdr lst))) (list (car lst)))
          ((null (cdr lst)) (list (reverse (car lst))))
          ((atom (car lst)) (append (reverse (cdr lst)) (list (car lst))))
          (T (append (reverse (cdr lst)) (list (reverse (car lst))))))))

(defun linearise (lst) (
    (cond ((null lst) nil)
          ((listp (car lst)) (append (linearise (car lst)) (linearise (cdr lst))))
          (T (cons (car lst) (linearise (cdr lst)))))))

(defun intersect (lhs rhs res) (
    (cond ((null lhs) nil)
          ((null rhs) res)
          ((and (member (car rhs) lhs) (not (member (car rhs) res))) (intersect lhs (cdr rhs) (cons (car rhs) res)))
          (T (intersect lhs (cdr rhs) res)))))

(defun fib_seq (n) (
    (cond ((eq n 0) ())
          ((eq n 1) (list 1))
          ((eq n 2) (list 1 1))
          (T (reverse (fib_seq_ 1 1 (- n 2) (list 1 1)))))))

(defun fib_seq_ (one two n res) (
    (cond ((eq n 0) res)
          (T (fib_seq_ two (+ two one) (- n 1) (cons (+ two one) res))))))
