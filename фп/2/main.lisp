(defun square (x) (* x x))

(defun rec-square (items)
  (if (null items)
      ()
      (cons (* (first items) (first items))
            (rec-square (rest items)))))

(defun map-square (items)
  (mapcar #'square items))


(print (rec-square (list 1 2 3 4 5)))
(print (map-square (list 1 2 3 4 5)))