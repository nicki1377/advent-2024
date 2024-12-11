; return # of instances of XMAS
(word-search "input" "XMAS" 140)

; stack size may need to be extended a bit to run this
; due to the map operation done to get list-of-positions.
; not sure how i feel about this fact.

(defun word-search (path target-word num-lines)
  (let* ((array (parse path num-lines))
        (list-of-positions (map 'list (lambda (n) (positions (char target-word 0) n))
                                array)))
    (do ((x-list list-of-positions (cdr x-list))
         (y 0 (1+ y))
         (result 0 (apply #'+ result
                          (mapcar (lambda (l) (search-letter l y array target-word)) (car x-list)))))
        ((null x-list)
         result))))

; returns vector of strings representation of the word search array
(defun parse (path init-size)
  (with-open-file (str path :direction :input)
    (do ((line (read-line str nil 'eof)
               (read-line str nil 'eof))
         (result (make-array init-size :adjustable t :fill-pointer 0)
                 result))
        ((eql line 'eof)
         result)
      (vector-push line result))))

; returns sum of instances of XMAS for this starting letter
; by searching in all directions
(defun search-letter (x-index y-index array word)
  (+ (search-direction x-index y-index #'1+ #'identity array word)
     (search-direction x-index y-index #'1- #'identity array word)
     (search-direction x-index y-index #'identity #'1+ array word)
     (search-direction x-index y-index #'identity #'1- array word)
     (search-direction x-index y-index #'1+ #'1+ array word)
     (search-direction x-index y-index #'1- #'1+ array word)
     (search-direction x-index y-index #'1+ #'1- array word)
     (search-direction x-index y-index #'1- #'1- array word)))

(defun search-direction (start-x start-y x-increment y-increment array word)
  (let ((width (length (aref array 0)))
        (height (length array)))
    (do ((char-list word (subseq char-list 1))
         (x start-x (funcall x-increment x))
         (y start-y (funcall y-increment y)))
        ((or (equal char-list "")
             (out-of-bounds-p x y width height)
             (not (eql (char char-list 0)
                       (char (aref array y) x))))
         (if (equal char-list "")
             1
           0)))))

(defun out-of-bounds-p (x y width height)
  (or (< x 0)
      (>= x width)
      (< y 0)
      (>= y height)))

; returns '(1 2 3) etc. position of all instances of starting letter.
(defun positions (char sequence)
  (get-positions char sequence 0))

(defun get-positions (char sequence prev-pos)
  (let ((pos (position char sequence)))
    (cond ((null pos)
           'nil)
          (t
           (cons (+ prev-pos pos) (get-positions char (subseq sequence (+ 1 pos)) (+ 1 prev-pos pos)))))))