(defun count_nums (list) (
    (cond ((null list) nil)
          ((listp list) (_count list))
          (T nil))))

(defun _count (list) (
    (cond ((null list) T)
          ((numberp (car list)) (_count (cdr list)))
          ((atom (car list)) nil)
          (T (and (_count (car list)) (_count (cdr list)))))))
