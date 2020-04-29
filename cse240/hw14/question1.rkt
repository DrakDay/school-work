(define (foo x y)  ;size n problem
  (cond
    ((<= y 0)        ;stoping condition 1
          x)         ;its return value
    ((<= x 0)        ;stoping condition 2
          y)         ;its return value
    ((>= x y)        ;condtion check
          (+ x (foo(- x 1)(- y 2))))  ;size m problen and its soulution
    (else(< x y)     
          (+ y (foo(- x 2)(- y 3)))))) ; size m problem and tis soultuion

(foo 1 2)
