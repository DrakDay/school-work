 
;CSE 240 Spring 2019 HW12
; Name: zhi li hu

; For testing a procedure, you may comment out other procedures.

;Q1: (8 points) creates a list with alternative values from the 3 given lists

(define (alternate lst1 lst2 lst3)
; Put your code here:
  (if (or (null? lst1)(null? lst2)(null? lst3));stop condition
      '()   ;return value
      (append (list(car lst1))(list(car lst2))(list(car lst3)) ; put the first letter into a new list
              (alternate (cdr lst1) (cdr lst2) (cdr lst3))))) ; call itslef the finish rest of the list


  
;Test case:
(alternate '(1 2 3 4) '(a b c d) '(m n o p))
; Test output:
;'(1 a m 2 b n 3 c o 4 d p).


;Q2: (8 points) shuffle lists one and two in pairs

(define (pairs lst1 lst2)
; Put your code here:
  (if (or (null? lst1)(null? lst2)) ;stop condtion
           '()  ;return value
          (append (list (cons (car lst1)(car lst2))) ; cons a pair form the head of two list
                        (pairs (cdr lst1)(cdr lst2))))) ; calling it slef to finsh rest of the list
  

;Test case:
(pairs '(1 2 3 4) '(a b c d))
;Test output
;'((1 . a) (2 . b) (3 . c) (4 . d))

  
;Q3: (9 points)
 (define key (read)); read keyboard inputs
;encryption
(define encrypt
  (lambda (str)
; Put your code here:
     (list->string(map character-encryption(string->list str))))) ; using map to encrypt string
    
(define character-encryption
  (lambda(ch)
    (if (or (char-alphabetic? ch)
        (and (>= (char->integer ch) 48)
             (<= (char->integer ch) 57))) ; only want encrypt char and numbers(48-57 are numbers)
         (integer->char (+ (char->integer ch) key)); if is a char or number then encrypt it
         ch ; else just return the char
        )))
   
;decryption
(define decrypt
  (lambda (str)
; Put your code here:
     (list->string(map character-decryption(string->list str))))) ; using map to encrypt string
    
(define character-decryption
  (lambda(ch)
    (if (or (char-alphabetic? ch)
        (and (>= (char->integer ch) 48)
             (<= (char->integer ch) (+ 57 key)))) ; only want decrypt char and numbers + some speical characters 
                                          ; beucase if u encypt 9 then it is not char and number anymore
         (integer->char (- (char->integer ch) key)); if is a char or number or some special characters then derypt it
         ch ; else just return the char
        )))
    

; Test cases:
(encrypt "Hello CSE240!")
(decrypt "Lipps GWI684!")
(encrypt "Hello CSE598?")
(decrypt "Lipps GWI9=<?")

; Test outputs:
;4
;"Lipps GWI684!"
;4
;"Hello CSE240!"
;4
;"Lipps GWI9=<?"
;4
;"Hello CSE598?"
> 