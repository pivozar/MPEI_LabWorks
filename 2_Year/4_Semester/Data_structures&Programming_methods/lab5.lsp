(defun _get_pos (lst func cur_pos) (
    (cond ((null lst) ())
          ((funcall func (car lst))
              (cons cur_pos (_get_pos (cdr lst) func (incq cur_pos))))
          (T (_get_pos (cdr lst) func (incq cur_pos))))))

(defun get_pos (lst func) (
    (cond ((null lst) nil)
          (T (_get_pos lst func 0)))))

(defun sum (lst) (
    (setq res 0)
    (loop ((null (car lst)) res)
          (setq res (+ res (car lst)))
          (pop lst))))

(defun sublist_sum (lst) (
    (cond ((null lst) nil)
          (T (maplist 'sum lst)))))

(defun _remove (lst elem) (
    (mapcon '(lambda (lst2) (cond ((eq (car lst2) elem) nil) (T (list (car lst2))))) lst)))

(defun remove (lst elem)
  (cond ((or (null lst) (not (listp lst)) (not (atom elem))) nil)
        (T (_remove lst elem))))

(defun _get_set (lst)
    (mapcon '(lambda (L)
        (if (member (car L) (cdr L)) nil
            (list (car L)))) lst))

(defun get_set (lst)
    (cond ((listp lst) (_get_set lst))
    (T nil)))

(defun _merge (lst1 lst2) (
    (mapcan '(lambda (a b) ( if (eq a b) nil (list (cons a b)))  ) lst1 lst2)))

(defun merge (lst1 lst2) (
    (cond ((not (eq (length lst1) (length lst2))) nil)
          (T (_merge lst1 lst2)))))

(defun file_write (lst fname) (
    (wrs fname)
    (loop ((null (car lst)) (wrs))
          (print (pop lst)))
))

(DEFUN SORT (FileName File1 File2 File3 File4)
    (setq nums '())
    (setq lists '())
    (setq chars '())
    (setq pairs '())
    (rds FileName)
    (setq size (read))
    (loop ((eq 0 size) SORT_IS_FINISHED)
          (decq size)
          (setq X (read))
          (cond ((numberp X) (push X nums))
                ((listp X) (push X lists))
                ((symbolp X) (push X chars))
                (T (push X pairs))))
    (rds)
    (file_write nums File1)
    (file_write lists File2)
    (file_write chars File3)
    (file_write pairs File4)
)
