(defun print-matrix (matrix &optional (chars 3) stream)
  (let ((*print-right-margin* (+ 6 (* (+ 1 chars) (array-dimension matrix 1))))) 
    (pprint matrix stream)
    (values)
  )
)

(defun find-min (arr)
  (let ((m (array-dimension arr 0))
        (n (array-dimension arr 1))
        (min-el (aref arr 0 0))
       )
    (loop for i upfrom 0 to (- m 1)
      do
      (loop for j upfrom 0 to (- n 1)
        do (when (< (aref arr i j) min-el)
             (setf min-el (aref arr i j))
           )
      )
    )
    min-el
  )
)

(defun change-arr (arr r)
  (let* ((m (array-dimension arr 0))
         (n (array-dimension arr 1))
         (new-arr (make-array (list m n) :initial-element 0.0))
         (min-el (find-min arr))
        )
    (loop for i upfrom 0 to (- m 1)
      do
      (loop for j upfrom 0 to (- n 1)
        do (when (= (aref arr i j) min-el)
             (setf (aref new-arr i j) r)
           )
           (when (/= (aref arr i j) min-el)
             (setf (aref new-arr i j) (aref arr i j))
           )
      )
    )
    new-arr
  )
)
