(defun compute_series (x eps) (
    (setq sum (+ x 1))
    (setq i 2)
    (setq next_elem (/ (* x x) i))
    (loop ((< next_elem eps) sum)
          (setq sum (+ sum next_elem))
          (incq i)
          (setq next_elem (/ (* next_elem x) i)))))

(defun _back (lst) (
    (loop ((null (cdr lst)) (pop lst))
          (pop lst))))

(defun back (lst) (
    (cond ((null lst) nil)
          (T (_back lst)))))

(defun _reverse (lst res) (
    (loop ((null (car lst)) res)
          (cond ((atom (car lst)) (
                    (setq res (cons (pop lst) res))
                    )
                )
                (T (setq res (cons (_reverse (pop lst) '()) res))
                )
          )
    )
))

(defun reverse (lst) (
    (cond ((null lst) nil)
          (T (_reverse lst '())))))

(defun _filter (lst min max res) (
    (loop ((null (car lst)) res)
          (setq cur_elem (pop lst))
          (cond ((and (< cur_elem max) (> cur_elem min)) (push cur_elem res))
                (T nil))
    )
))

(defun filter (lst min max) (
    (cond ((null lst) nil)
          ((< max min) nil)
          (T (reverse (_filter lst min max '())))
    )
))

(defun _replace (lst char1 char2 count res) (
    (loop ((null (car lst)) res)
          (setq cur_char (pop lst))
          (cond ((and (eq cur_char char1) (> count 0)) (
                (push char2 res)
                (decq count)
                ))
                (T (push cur_char res))))
))

(defun replace (lst char1 char2 count) (
    (cond ((not (and (listp lst)
                     (symbolp char1)
                     (symbolp char2)
                     (numberp count)
                )) nil)
          (T (reverse (_replace lst char1 char2 count '()))))
))
