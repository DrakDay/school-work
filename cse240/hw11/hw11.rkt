; CSE240 HW11 Spring 2019
; NOTE : make sure to select R5RS in the bottom left corner before running code

; Q1 (5 points)
;1.1
(+ 5(- 9 2))
;1.2
(- (* 5 (+ 6 12 +5)) 25)
;1.3
(* 7 (+ (- 5 (* 1 3)) (* 2 4)))
; 1.4
(* 3 (+ 4 (/ (+ (* 6 6) (* 6 6)) (+ 10 2))))
; 1.5
(+ (/ (- (/ (/ ( * (+ 4 6) (+ 6 4)) 2) 2) 5) 2) (+ (/ (+ (* 4 5) (* 5 4)) 2) (* 4 5)))

; Q2 (5 points)
;; define add
(define add (lambda (x y)
              (+ x y) ) )
; display and call prodecure add
(display (add 120 50)) (newline)

; Q3 (10 points)
; define the absolute function
(define absn (lambda (x)
              (if (negative? x)
                  (- x)
                    x)))
 ;define the suqre fuction
(define square (lambda (x) ; size n problem
                 (if (= x 0) ; stop condition
                     0      ; stop condition's return value
                     (add (square (- (absn x) 1)) (- (* 2 (absn x )) 1 )) ;size m problen and it's soultion
                     )))
(display (square -8)) (newline)

; Q4 (5 points)
;define readforsquare function
(define readforsquare (lambda ()
                      (square(read))))
;ask user to input number then call the readforsqure fuction
(display "please enter a number: ")
(display (readforsquare)) (newline)

; Q5 (10 points)
;define the difference between square fuction
(define diffsquare (lambda ()
                     (absn (- (readforsquare)(readforsquare)))))
(display "please enter 2 number: ")
(display (diffsquare)) (newline)

; Q6 (5 point)
;define add let fuction
(define addlet (lambda (x y z )
        (let  ( (x1 x) ;define let's value
                (y1 y)
                (z1 z))
             (+ x y z)))) ; lets procedure 
(display (addlet 1 2 3)) (newline)
                
; Q7 (5 points)
;define unnamed fuction
((lambda (x y z) (+ x y z )) 40 60 5)(newline)
;Q8: (10 points)

; named prodecure
(define (sumodd lst)
  ; if list is null return 0
    (cond ((null? lst) 0)
          ; if the car of list is odd then add
          ((odd? (car lst)) (+ (car lst) (sumodd (cdr lst))))
          ; if the car of list is not odd then skip
          (else (sumodd (cdr lst)))))
(display (sumodd '(1 3 4 5 6 -7))) (newline)

;unmaned fuction
((lambda (lst)
                (cond  ((null? lst ) 0)
                       ((odd? (car lst)) (+ (car lst) (sumodd (cdr lst))))
                       (else (sumodd (cdr lst)))))
                  '(1 3 4 5 6 -7))