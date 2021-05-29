(deframeq vocabulary
    (nouns ($value (avtomobil) (stol) (victor) (on)))
    (adjectives ($value (bystriy) (kholodniy) (priyatniy) (zeleniy)))
    (verbs ($value (bejit) (gorit) (molchit) (smotrit)))
)

(defun is_noun (word)
    (cond ((member word (fget vocabulary nouns $value)) T)
          (T nil)))

(defun is_adjective (word)
    (cond ((member word (fget vocabulary adjectives $value)) T)
          (T nil)))

(defun is_verb (word)
    (cond ((member word (fget vocabulary verbs $value)) T)
          (T nil)))

(defun is_word (word)
    (cond ((or (is_noun word) (is_adjective word) (is_verb word)) T)
          (T nil)))

(defun analysis (sent prev_word) (
    (cond ((null sent) (is_verb prev_word))
          ((not (is_word (car sent))) nil)
          (T (cond ((or (and (is_adjective prev_word) (is_verb (car sent)))
                      (and (is_noun prev_word) (not (is_verb (car sent)))))
                        nil)
                   (T (analysis (cdr sent) (car sent))))))
))
