(defun list_len_ (list) (
    (cond ((null list) 0)
          (T (+ 1 (list_len_ (cdr list)))))))

(defun even_cnt (list) (
    (cond ((= (mod (list_len_ list) 2) 0) T)
          (T nil))))

(defun list_size (list) (
    (cond ((null list) 0)
          ((atom (car list)) (+ 1 (list_size (cdr list))))
          (T (+ (list_size (car list)) (list_size (cdr list)))))))

(defun max_depth (list) (
    (cond ((null list) 0)
          ((atom (car list)) (max_depth (cdr list)))
          (T (max (+ 1 (max_depth (car list))) (max_depth (cdr list)))))))

(defun max_element (list) (
    (cond ((null list) 0)
          ((atom (car list)) (max (car list) (max_element (cdr list))))
          (T (max (max_element (car list)) (max_element (cdr list)))))))

(defun eval_exp (exp) (
    (cond ((null exp) 0)
          ((atom exp) exp)
          ((eq (cdr exp) nil) (eval_exp (car exp)))
          ((eq "+" (car (cdr exp))) (+ (eval_exp (car exp)) (eval_exp (cddr exp))))
          ((eq "-" (car (cdr exp))) (- (eval_exp (car exp)) (eval_exp (cddr exp))))
          ((eq "*" (car (cdr exp))) (eval_exp (cons (* (eval_exp (car exp)) (eval_exp (car (cddr exp)))) (cdddr exp))))
          ((eq "/" (car (cdr exp))) (eval_exp (cons (/ (eval_exp (car exp)) (eval_exp (car (cddr exp)))) (cdddr exp))))
          (T nil))))
