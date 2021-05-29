(deframeq frame_0
    (slot_0 ($value (ex0))
        ($if-geted (update_requests))
        ($if-removed (update_requests))
        ($if-added (update_requests)))
    (slot_1 ($default (ex1.1) (ex1.2))
        ($if-geted (update_requests))
        ($if-added (update_requests))
        ($if-removed (update_requests)))
    (requests ($value 0))
)

(passertq update_requests (lambda () (
    (setq new_req (+ (car (fget :frame requests)) 1))
    (cond ((equal (mod new_req 3) 0)
       (princ new_req)(print "th request!")))
    (fremove :frame requests)
    (fput :frame requests $value new_req)))
)
