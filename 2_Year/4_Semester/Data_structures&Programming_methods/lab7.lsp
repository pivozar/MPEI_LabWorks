(setq current_year 2021)

(deframeq card_001
          (title ($value (Airport)))
          (author ($value (Arthur_Hailey)))
          (genre ($value (thriller)))
          (rating ($value (8.5)))
          (year ($value (1968)))
          (age ($value (get_age (status: eval) (parm: current_year))))
)

(deframeq card_002
          (title ($value (_17_mgnoveniy_vesni)))
          (author ($value (Julian_Semenov)))
          (genre ($value (political_detective)))
          (rating ($value (9.2)))
          (year ($value (1969)))
          (age ($value (get_age (status: eval) (parm: current_year))))
)

(deframeq card_003
          (title ($value (Twenty_thousands_leagues_under_the_sea)))
          (author ($value (Jules_Verne)))
          (genre ($value (Adventures)))
          (rating ($value (8.5)))
          (year ($value (1870)))
          (age ($value (get_age (status: eval) (parm: current_year))))
)

(deframeq card_004
          (title ($value (The_Count_of_Monte_Cristo)))
          (author ($value (Alexandre_Dumas)))
          (genre ($value (Adventure)))
          (rating ($value (9.9)))
          (year ($value (1844)))
          (age ($value (get_age (status: eval) (parm: current_year))))
)

(passertq get_age (now) (- now (car (fget :frame year))))

(defun change_rating (frame new_rating) (
    (fdelete frame rating $value)
    (fput frame rating $value new_rating)
))

(defun _make_frview (frame_list) (
    (setq fr_no 1)
    (setq watched_frames '())
    (setq cmd 'n)
    (loop ((equal cmd 'x)(print "Output over."))
          (princ "This is frame no. ")(princ fr_no)
          (print ". Print?")
          (if (equal (read input) 'y) (fprint (list (car frame_list))))
          (print "Show (n)ext, (p)revious or e(x)it?")
          (setq cmd (read input))
          (cond ((and (equal cmd 'p) (not (null watched_frames)))
                    (push (pop watched_frames) frame_list)
                    (decq fr_no))
                ((and (equal cmd 'n) (not (null frame_list)))
                    (push (pop frame_list) watched_frames)
                    (incq fr_no))
                (T (print "This is the edge of the list!"))
                )))
)

(defun get_fview (frame_list)
    (cond ((null FL) nil)
        (T (_make_frview frame_list)))
)
