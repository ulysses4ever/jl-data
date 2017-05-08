;;;; -*- Mode: Lisp; Syntax: Common-Lisp; -*-

;;; String2 Sawfish Module.  Version 1.6.

;;; Copyright (c) 2003  Ewan Mellor <sawfish@ewanmellor.org.uk>.
;;; 

;;; This module was created by me, Ewan Mellor.  All the code in it, however,
;;; comes from the string2 string manipulation library.  I can find neither an
;;; attribution nor a licence for string2.  The only work I have done
;;; personally is wrap this code into a module.


(define-structure string2
  (export
   string2-max-common-substring
   string2-elipsis
   string2-replace
   string2-join
   string2-split
   string2-contains
   string2-index
   string2-trim
   )
   
  (open rep
        rep.regexp)

(define (string2-max-common-substring str ls0 case-insensitive)
  "given a string str and a list of strings, find me the longest common
substring of all the elements of the list beginning with str (but str is not
necessarily at the beginning of any element, or in the same position in any
element).  be case-insensitive about it"
  ;; XXX case-insensitive argument is ignored (it's always on)
  (if ls0
      (let* ((ls (filter 
		  (lambda (x) (string2-contains (string-downcase x) 
					       (string-downcase str))) ls0))
	     (len (length ls))
	     (caroff (string2-index (string-downcase (car ls)) 
				   (string-downcase str)))
	     (carlen (length (car ls)))
	     (i (length str))
	     (it str)
	     (keep-going t))
	(while keep-going
	  (setq i (+ i 1))
	  (if (= len (length (filter 
			      (lambda (x) (string2-contains 
					   (string-downcase x) 
					   (string-downcase str)))
			      ls)))
	      (progn
		(setq it str)
		(if (> (+ caroff i) carlen)
		    (setq keep-going nil)
		  (setq str (substring (car ls) caroff (+ caroff i)))))
	    (setq keep-going nil)))
	it)
    str))

(define (string2-elipsis str max-len)
  ""
  (if (> (length str) max-len)
      (concat (substring str 0 (if (> max-len 3) (- max-len 3) max-len)) "...")
    str))

(define (string2-replace big old-small new-small)
  ""
  (string2-join (string2-split big old-small) new-small))

(define (string2-join strings between)
  ;; can use mapconcat for this
  ""
  (let ((res nil))
    (while strings
      (if (cdr strings)
	  (setq res (concat res (car strings) between))
	(setq res (concat res (car strings))))
      (setq strings (cdr strings)))
    res))

(define (string2-split big small)
  ""
  (let ((res nil)
	(done nil)
	(idx 0))
    (while (and (not done) (>= (length big) (length small)))
      (setq idx (string2-index big small))
      (if (> idx -1)
	  (setq res (cons (substring big 0 idx) res)
		big (substring big (+ (length small) idx)))
	(setq done t
	      res (cons big res))))
    (if (not done) (setq res (cons big res)))
    (reverse res)))

(define (string2-contains big small)
  "Does the big string contain the small string?"
  ;; use instead of (> (string2-index foo bar) > -1)
  (string-match (concat ".*" (quote-regexp small) ".*") big))

(define (string2-index big small) 
  ;; XXX slow algorithm
  "Return the index of the small string in the big string, or -1"
  (let ((si-iter (lambda (b s)
		   (let ((off 0)
			 (match t))
		     (while (and match (> (length s) off))
		       (if (not (= (elt b off) (elt s off)))
			   (setq match nil)
			 (setq off (+ off 1))))
		     match)))
	(off 0)
	(found nil))
    (while (and (not found) (>= (length big) (+ off (length small))))
      (if (si-iter (substring big off) small)
	  (setq found t)
	(setq off (+ off 1))))
    (if found off -1)))

(define (string2-trim str)
  "Remove leading and trailing whitespace"
  (let* ((i 0)
	(len (length str))
	(beg 0)
	(end len)
	(stop nil)
	(is-whitespace (lambda (x) 
			 (or (eq x ?\n) (eq x ?\r) (eq x ?\t) (eq x ?\ )))))
    
    (while (and (not stop) (< i len))
      (if (is-whitespace (aref str i))
	  (setq i (+ i 1)
		beg i)
	(setq stop t)))
    (setq stop nil
	  i len)
    (while (and (not stop) (> i 0))
      (if (is-whitespace (aref str (- i 1)))
	  (setq i (- i 1)
		end i)
	(setq stop t)))
    (if (> end beg)
	(substring str beg end)
      "")))

)
