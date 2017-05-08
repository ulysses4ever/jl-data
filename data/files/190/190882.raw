; pager/theme.jl
;; stuff below is very poor

(defgroup pager-frame "Pager theme" :group appearance)

(defcustom pager:inactive-menu "rightarr6.png"
  "inactive shade-button."
  :group (appearance pager-frame)
  :type file-name)

(defcustom pager:active-menu "rightarr6.png"
  "active shade-button."
  :group (appearance pager-frame)
  :type file-name)
 ; :after-set (lambda () (color-changed)))

;(defcustom pager:active-menu-hov "righthov.png"
;  "active shade-button-hover."
;  :group (appearance pager-frame)
;  :type file-name)

;(defcustom pager:active-menu-click "rightclick.png"
;  "active shade-button-click."
;  :group (appearance pager-frame)
;  :type file-name)


(defcustom pager:shaded-button "rightarr6s-.png"
  "shaded-button."
  :group (appearance pager-frame)
  :type file-name)

;(defcustom Pager:button-type menu-button
;  "Type of button: \\w"
;  :type (choice (Menu menu-button)
;		(shade shade-button))
;  :group (appearance pager-frame)


;;
(let*
  (
 
    (menu-image (list (make-image pager:inactive-menu)
	              (make-image pager:active-menu)
                      ;(make-image "righthov.png")
                      ;(make-image pager:active-menu-hov)
                      ;(make-image pager:active-menu-click)
                      ;(make-image "rightclick.png")

))  
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; (make-image
;      (lambda (i)
;	(or (condition-case nil
;		(make-image i)
;	      (error))
;	    (make-image (concat install-dir i)))))
;     
;     (rebuild (lambda ()
;		(rebuild-frames-with-style 'pager)))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;  
;;;;;;;;;;;;;;;;;;;;;;    
    (shade-image (make-image pager:shaded-button))
    (title-image (make-image "top.png"))
    (top-left-image (make-image "cor.png"))
    (right-image (make-image "bit.png"))
    (top-right-image (make-image "tpcor.png"))
    (bottom-image (list (make-image "b1.png")
	                (make-image "b1.png")))
    (top-image (make-image "line.png")) 
    (right-bit (make-image "horbline.png")) 

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;       

(frame `(
        
((background . ,top-left-image)
         (top-edge . -2)
         (left-edge . -20)
         (class . title))
        
((background . ,title-image)
         
         (x-justify . left)
         (y-justify . center)
         (left-edge . -19)
         (right-edge . -3)
         (top-edge . -2)
         ;(height . 20)
         (class . title))
        
((background . ,top-right-image)
         (right-edge . -3)
         (top-edge . -2)
         (class . title))
                
((background . ,right-image)
         (right-edge . -3)
         (top-edge . 0)
         (bottom-edge . -2)
         (class . right-border))
     
((background . ,bottom-image)
         (left-edge . 0)
         (right-edge . 0)
         (bottom-edge . -2)
         (class . bottom-border))
        
((background . ,menu-image)
         (left-edge . -20)
         (top-edge . 0)
         (bottom-edge . -2)
(cursor . left_ptr)	 
(class . title))

((background . ,top-image)
         (left-edge . 0)
         (top-edge . 0)
         (right-edge . 0)
	 (class . title))      

((background . ,right-bit)
         (left-edge . 0)
         (top-edge . 0)
         (bottom-edge . 0)
	 (class . left-border))      
))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;dubious stuff;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

  
    (shaped-frame `(
        
((background . ,top-left-image)
         (top-edge . -2)
         (right-edge . 16)
         (class . top-left-corner))
        
((background . ,title-image)
         
         (right-edge . -5)
         (top-edge . -2)
         (width . 21)
         (class . title))
        
((background . ,top-right-image)
         (right-edge . -6)
         (top-edge . -2)
         (class . title))
                
((background . ,right-image)
         (right-edge . -6)
         (top-edge . 0)
         (bottom-edge . -2)
         (class . right-border))
        
        
((background . ,bottom-image)
         ;(left-edge . 0)
         (right-edge . -3)
         (bottom-edge . -2)
         (width . 20)
          (class . bottom-border))
        
((background . ,shade-image)
         (right-edge . -3)
         (top-edge . 0)
         (bottom-edge . -2)
	 (cursor . left_ptr)
         (class . shade-button))

)))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;      
(add-frame-style 'pager
		   (lambda (w type)
		     (case type
		       ((default) frame)
		       ((shaped) shaped-frame)
		       )))
 
(call-after-property-changed
   'WM_NAME (lambda ()
              (rebuild-frames-with-style 'pager))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;(unless batch-mode
;    (load-images));
;
;  (mapc (lambda (sym)
;	  (custom-set-property sym ':after-set rebuild))
;	'(pager:inactive-menu pager:active-menu pager:shaded-button
;	  )))