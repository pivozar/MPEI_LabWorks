(defun _run_test (obj lst test res) (
    (cond ((null (car lst)) res)
          ((not (null (funcall test obj (car lst)))) (_run_test obj (cdr lst) test (cons (car lst) res)))
          (T (_run_test obj (cdr lst) test  res)))))

(defun @findlist (obj lst test) (
    (cond ((or (null lst) (not (listp lst))) nil)
          ((null test) (_run_test obj lst 'eq '()))
          (T (_run_test obj lst test '())))))

(defun _findlist-if (test lst res) (
    (cond ((null lst) res)
          ((funcall test (car lst)) (_findlist-if test (cdr lst) (cons (car lst) res)))
          (T (_findlist-if test (cdr lst) res)))))

(defun @findlist-if (test lst) (
    (cond ((or (null lst) (not (listp lst))) nil)
          (T (_findlist-if test lst '())))))

(defun @insend (atm lst func) (
    (cond ((null lst) nil)
          ((and (atom atm) (listp lst)) (funcall func atm lst '()))
          (T nil))))

(defun _ins1 (atm lst) (
    (cond ((null lst) (list atm))
          ((atom (car lst)) ((cons (car lst) (_ins1 atm (cdr lst)))))
          (T (append (list (_ins1 atm (car lst))) (_ins1 atm (cdr lst)))))))


(defun _ins2 (atm lst res) (
    (loop ((null (car lst)) (setq res (append res (list atm))))
          (setq cur_elem (pop lst))
          (cond ((atom cur_elem) (setq res (append res (list cur_elem))))
                (T (setq res (append res (list (_ins2 atm cur_elem '())))))))))

(defun _ins3 (atm lst) (
    (defun __ins0 (lst) (
        (cond ((null (cdr lst)) atm)
              ((listp (car lst)) (_ins3 atm (car lst)))
              (T (car lst)))))
    (maplist '__ins0 (append lst (list nil)))))
