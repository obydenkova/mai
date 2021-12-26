(defun knight-moves (x1 y1 x2 y2)
 (labels ((knight-moves-sup (x1 y1 x2 y2)
            (cond ((and (= x1 x2) (= y1 y2)) T)
                ((or (and  (= (+ x1 1) x2) (= (+ y1 2) y2))
                     (and  (= (+ x1 1) x2) (= (- y1 2) y2))
                     (and  (= (- x1 1) x2) (= (+ y1 2) y2))
                     (and  (= (- x1 1) x2) (= (- y1 2) y2))
                     (and  (= (+ x1 2) x2) (= (+ y1 1) y2))
                     (and  (= (+ x1 2) x2) (= (- y1 1) y2))
                     (and  (= (- x1 2) x2) (= (+ y1 1) y2))
                     (and  (= (- x1 2) x2) (= (- y1 1) y2))
                     ) (values x1 y1)))))
    (cond ((knight-moves-sup (+ x1 1) (+ y1 2) x2 y2) (knight-moves-sup (+ x1 1) (+ y1 2) x2 y2))
        ((knight-moves-sup (+ x1 1) (- y1 2) x2 y2) (knight-moves-sup (+ x1 1) (- y1 2) x2 y2))
        ((knight-moves-sup (- x1 1) (+ y1 2) x2 y2) (knight-moves-sup (- x1 1) (+ y1 2) x2 y2))
        ((knight-moves-sup (- x1 1) (- y1 2) x2 y2) (knight-moves-sup (- x1 1) (- y1 2) x2 y2))
        ((knight-moves-sup (+ x1 2) (+ y1 1) x2 y2) (knight-moves-sup (+ x1 2) (+ y1 1) x2 y2))
        ((knight-moves-sup (+ x1 2) (- y1 1) x2 y2) (knight-moves-sup (+ x1 2) (- y1 1) x2 y2))
        ((knight-moves-sup (- x1 2) (+ y1 1) x2 y2) (knight-moves-sup (- x1 2) (+ y1 1) x2 y2))
        ((knight-moves-sup (- x1 2) (- y1 1) x2 y2) (knight-moves-sup (- x1 2) (- y1 1) x2 y2))
            )))


(print (knight-moves 1 1 3 2))

(multiple-value-bind (q r) (knight-moves 1 1 5 3)
(print q) (princ ", ") (prin1 r))

(print (knight-moves 1 1 8 8))
