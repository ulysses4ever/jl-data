####################################################
## QuickSort
####################################################
# b = sort(a, alg=QuickSort)
# @test issorted(b)

(define filter (lambda (f lst)
   (if lst
      (if (f (head lst))
         (cons (head lst) (filter f (rest lst)))
         (filter f (rest lst)))
      nil)))

(define combine (lambda (as bs)
   (if as
      (cons (head as) (combine (rest as) bs))
      bs)))

(define qsort (lambda (lst)
   (if lst
      (begin
         (define pivot (head lst))
         (define less (filter (lambda (a) (< a pivot)) (rest lst)))
         (define greater (filter (lambda (a) (>= a pivot)) (rest lst)))
         (combine (qsort less) (cons pivot (qsort greater))))
      nil)))

# example
(print (qsort (list 7 3 2 6 9 1 8 4 5)) "\n")

a = [4,2,3,1]
qsort(a)