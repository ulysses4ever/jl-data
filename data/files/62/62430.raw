;;; DragDome/theme.jl

;; Temporary fix for sawfish 0.31

(define close-image nil)
(define iconify-image nil)
(define maximize-image nil)
(define menu-image nil)
(define shade-image nil)
(define sticky-image nil)
(define unsticky-image nil)
(define close-image-small nil)
(define iconify-image-small nil)
(define maximize-image-small nil)
(define menu-image-small nil)
(define shade-image-small nil)
(define sticky-image-small nil)
(define unsticky-image-small nil)
(define button-images nil)
(define button-images-small nil)
(define border-frame nil)
(define frame nil)
(define shaped-frame nil)
(define title-shadow nil)
(define title-shadow-small nil)
(define frame-small nil)
(define shaped-frame-small nil)
(define bar nil)
(define bar-small nil)

;; Customization:
;; --------------

(defgroup dragdome "DragDome Theme"
  :group appearance)

(defcustom dragdome:focused-title-colour (get-color-rgb #xd900 #x9400 #x2f00)
  "Active frame title bar colour"
  :type color
  :group (appearance dragdome))

(defcustom dragdome:focused-text-colour (get-color "black")
  "Active frame title text colour"
  :type color
  :group (appearance dragdome))

(defcustom dragdome:unfocused-title-colour (get-color-rgb #x8000 #x8b00 #x8000)
  "Inactive frame title bar colour"
  :type color
  :group (appearance dragdome))

(defcustom dragdome:unfocused-text-colour (get-color "black")
  "Inactive frame title text colour"
  :type color
  :group (appearance dragdome))

(defcustom dragdome:bar-placement '((close . 1) (title . 2) (iconify . 3) (maximize . 4)) 
  "Normal frame title bar objects"
  :type* `(alist ((symbol close iconify maximize menu shade sticky title) "Item")
                 (number "Order"))
  :group (appearance dragdome))

(defcustom dragdome:font (get-font "-b&h-lucida-medium-r-normal-*-*-110-*-*-p-*-iso8859-1")
  "Normal frame title font"
  :type  font
  :group (appearance dragdome))

(defcustom dragdome:bar-placement-small '((close . 1) (title . 2)) 
  "Small frame title bar objects"
  :type* `(alist ((symbol close iconify maximize menu shade sticky title) "Item")
                 (number "Order"))
  :group (appearance dragdome))

(defcustom dragdome:font-small (get-font "-b&h-lucida-medium-r-normal-*-*-110-*-*-p-*-iso8859-1")
  "Small frame title font"
  :type  font
  :group (appearance dragdome))

(defcustom dragdome:show-unfocused-buttons t
  "Display buttons on inactive window frames?"
  :type boolean
  :group (appearance dragdome))

(defcustom dragdome:full-title-width nil
  "Use full window width for title bar?"
  :type boolean
  :group (appearance dragdome))


;; Colours:
;; --------

(define colours-active
  `((#x4e #x4e #x4e #xff)
    (#x53 #x53 #x53 #xff)
	(#x9d #x9d #x9d #xff)
	(#xa8 #xa8 #xa8 #xff)
	(#xce #xce #xce #xff)
	(#xd3 #xd3 #xd3 #xff)))

(define colours-inactive (copy-sequence colours-active))
(define colours-active-old nil)
(define colours-inactive-old nil)

(define (scale-colour colour factor)
  (mapcar (lambda (c) (inexact->exact (min #xff (* c factor)))) colour))

(define (desaturate-colour colour percent)
  (let*
    ((max-value (last (sort (copy-sequence colour)))))
	(mapcar (lambda (c) (inexact->exact (+ c (* (- max-value c) percent)))) colour)))

(define (create-colours base-colour)
  (let*
	((main-colour1 (color-rgb-8 base-colour))
	 (main-colour2 (scale-colour main-colour1 1.1))
	 
	 (low-colour1  (scale-colour main-colour1 0.4))
	 (low-colour2  (scale-colour main-colour2 0.4))
	 
	 (high-colour1 (desaturate-colour (scale-colour main-colour1 1.3) 0.7))
	 (high-colour2 (desaturate-colour (scale-colour main-colour2 1.3) 0.7)))
  
	  `((,@low-colour1  #xff)
	    (,@low-colour2  #xff)
		(,@main-colour1 #xff)
		(,@main-colour2 #xff)
		(,@high-colour1 #xff)
		(,@high-colour2 #xff))))

(define (set-colours)
  (setq colours-active-old (copy-sequence colours-active))
  (setq colours-active (create-colours dragdome:focused-title-colour))
  (setq colours-inactive-old (copy-sequence colours-inactive))
  (setq colours-inactive (create-colours dragdome:unfocused-title-colour)))

(define (find-colour colour from-colours to-colours)
  (nth (- (length from-colours) (length (member colour from-colours))) to-colours))

(define (find-active-colour   colour) (find-colour colour colours-active-old   colours-active))
(define (find-inactive-colour colour) (find-colour colour colours-inactive-old colours-inactive))

(define (map-colours images)
  (mapc (lambda (i) (if i (image-map find-active-colour i))) (cdr images))
  (image-map find-inactive-colour (car images)))

(define (map-active-colours images)
  (mapc (lambda (i) (if i (image-map find-active-colour i))) images))

(define (map-inactive-colours images) 
  (mapc (lambda (i) (image-map find-inactive-colour i)) images))


;; Images:
;; -------

(define bottom-image					  (make-image "bottom-bar.png"))
(define top-image						  (make-image "top-bar.png"))
(define top-left-image					  (make-image "top-left.png"))
(define top-right-image					  (make-image "top-right.png"))
(define bottom-left-image				  (make-image "bottom-left.png"))
(define bottom-right-image				  (make-image "bottom-right.png"))
(define left-image						  (make-image "left-bar.png"))
(define right-image						  (make-image "right-bar.png"))

(define shadow-left-image			(list (make-image "left-title-shadow.png")
										  (make-image "left-title-shadow.png")))
(define shadow-mid-image			(list (make-image "mid-title-shadow.png") 
										  (make-image "mid-title-shadow.png")))
(define shadow-right-image          (list (make-image "right-title-shadow.png")
                                   	      (make-image "right-title-shadow.png")))

(define title-image					(list (make-image "mid-title.png")
										  (make-image "mid-title.png")))
(define bar-left-image				(list (make-image "left-title.png")
										  (make-image "left-title.png")))
(define bar-right-image				(list (make-image "right-title.png")
										  (make-image "right-title.png")))
					  
(define title-image-small			(list (make-image "mid-title-small.png")
										  (make-image "mid-title-small.png")))
(define bar-left-image-small		(list (make-image "left-title-small.png")
										  (make-image "left-title-small.png")))
(define bar-right-image-small		(list (make-image "right-title-small.png")
										  (make-image "right-title-small.png")))
    
(define close-image-active			(list (make-image "close.png") nil
										  (make-image "close-clicked.png")))
(define iconify-image-active		(list (make-image "iconify.png") nil 	
										  (make-image "iconify-clicked.png")))
(define maximize-image-active		(list (make-image "maximize.png") nil
										  (make-image "maximize-clicked.png")))
(define menu-image-active			(list (make-image "menu.png") nil
										  (make-image "menu-clicked.png")))
(define shade-image-active			(list (make-image "shade.png") nil
										  (make-image "shade-clicked.png")))
(define sticky-image-active			(list (make-image "sticky.png") nil
										  (make-image "sticky-clicked.png")))
(define unsticky-image-active		(list (make-image "unsticky.png") nil
										  (make-image "unsticky-clicked.png")))

(define close-image-active-small	(list (make-image "close-small.png") nil
										  (make-image "close-clicked-small.png")))
(define iconify-image-active-small	(list (make-image "iconify-small.png") nil 	
                                    	  (make-image "iconify-clicked-small.png")))
(define maximize-image-active-small	(list (make-image "maximize-small.png") nil
								          (make-image "maximize-clicked-small.png")))
(define menu-image-active-small		(list (make-image "menu-small.png") nil
										  (make-image "menu-clicked-small.png")))
(define shade-image-active-small	(list (make-image "shade-small.png") nil
										  (make-image "shade-clicked-small.png")))
(define sticky-image-active-small	(list (make-image "sticky-small.png") nil
										  (make-image "sticky-clicked-small.png")))
(define unsticky-image-active-small	(list (make-image "unsticky-small.png") nil
										  (make-image "unsticky-clicked-small.png")))

(define blank-image						  (make-image "blank.png"))
(define blank-image-small				  (make-image "blank-small.png"))

(define close-image-inactive			  (make-image "close.png"))
(define iconify-image-inactive			  (make-image "iconify.png"))
(define maximize-image-inactive			  (make-image "maximize.png"))
(define menu-image-inactive				  (make-image "menu.png"))
(define shade-image-inactive			  (make-image "shade.png"))
(define sticky-image-inactive			  (make-image "sticky.png"))
(define unsticky-image-inactive			  (make-image "unsticky.png"))

(define close-image-inactive-small		  (make-image "close-small.png"))
(define iconify-image-inactive-small	  (make-image "iconify-small.png"))
(define maximize-image-inactive-small	  (make-image "maximize-small.png"))
(define menu-image-inactive-small		  (make-image "menu-small.png"))
(define shade-image-inactive-small		  (make-image "shade-small.png"))
(define sticky-image-inactive-small		  (make-image "sticky-small.png"))
(define unsticky-image-inactive-small	  (make-image "unsticky-small.png"))


(define (recolour-images)

  (set-colours)

  (mapc map-colours
	(list title-image bar-left-image bar-right-image 
		  title-image-small bar-left-image-small bar-right-image-small 
		  shadow-mid-image shadow-left-image shadow-right-image))
  (mapc map-active-colours
	(list close-image-active iconify-image-active maximize-image-active 
		  menu-image-active sticky-image-active unsticky-image-active 
		  shade-image-active
		  close-image-active-small iconify-image-active-small 
		  maximize-image-active-small menu-image-active-small 
		  sticky-image-active-small unsticky-image-active-small 
		  shade-image-active-small))
  (map-inactive-colours
	(list blank-image blank-image-small
		  close-image-inactive iconify-image-inactive maximize-image-inactive 
		  menu-image-inactive sticky-image-inactive unsticky-image-inactive 
		  shade-image-inactive
		  close-image-inactive-small iconify-image-inactive-small 
		  maximize-image-inactive-small menu-image-inactive-small 
		  sticky-image-inactive-small unsticky-image-inactive-small 
		  shade-image-inactive-small)))


(define (build-images)
  
  (mapc (lambda (i) (image-put i 'tiled t))
	`(,@title-image ,@title-image-small ,@shadow-mid-image
	  ,bottom-image ,top-image ,left-image ,right-image))

  (setq close-image    
    `(,(if dragdome:show-unfocused-buttons 
		  close-image-inactive blank-image)
	      ,@close-image-active))
  (setq iconify-image  
    `(,(if dragdome:show-unfocused-buttons 
	      iconify-image-inactive blank-image) 
		  ,@iconify-image-active))
  (setq maximize-image 
	`(,(if dragdome:show-unfocused-buttons 
	      maximize-image-inactive blank-image)
		  ,@maximize-image-active))
  (setq menu-image     
	`(,(if dragdome:show-unfocused-buttons 
	      menu-image-inactive blank-image)
		  ,@menu-image-active))
  (setq shade-image    
	`(,(if dragdome:show-unfocused-buttons 
	      shade-image-inactive blank-image)
		  ,@shade-image-active))
  (setq sticky-image   
	`(,(if dragdome:show-unfocused-buttons 
	      sticky-image-inactive blank-image)
		  ,@sticky-image-active))
  (setq unsticky-image 
	`(,(if dragdome:show-unfocused-buttons 
	      unsticky-image-inactive blank-image)
		  ,@unsticky-image-active))
		  
  (setq close-image-small
    `(,(if dragdome:show-unfocused-buttons
		  close-image-inactive-small blank-image-small)
	      ,@close-image-active-small))
  (setq iconify-image-small
    `(,(if dragdome:show-unfocused-buttons
	      iconify-image-inactive-small blank-image-small)
		  ,@iconify-image-active-small))
  (setq maximize-image-small
	`(,(if dragdome:show-unfocused-buttons
	      maximize-image-inactive-small blank-image-small)
		  ,@maximize-image-active-small))
  (setq menu-image-small
	`(,(if dragdome:show-unfocused-buttons
	      menu-image-inactive-small blank-image-small)
		  ,@menu-image-active-small))
  (setq shade-image-small
	`(,(if dragdome:show-unfocused-buttons
	      shade-image-inactive-small blank-image-small)
		  ,@shade-image-active-small))
  (setq sticky-image-small
	`(,(if dragdome:show-unfocused-buttons
	      sticky-image-inactive-small blank-image-small)
		  ,@sticky-image-active-small))
  (setq unsticky-image-small
	`(,(if dragdome:show-unfocused-buttons
	      unsticky-image-inactive-small blank-image-small)
		  ,@unsticky-image-active-small))
		  
  (setq button-images 
	`((close    . ,close-image)
	  (iconify  . ,iconify-image)
	  (maximize . ,maximize-image)
	  (menu     . ,menu-image)
	  (shade    . ,shade-image)
	  (sticky   . ,(lambda (w) (if (window-get w 'sticky) sticky-image unsticky-image)))))
	  
  (setq button-images-small
	`((close    . ,close-image-small)
	  (iconify  . ,iconify-image-small)
	  (maximize . ,maximize-image-small)
	  (menu     . ,menu-image-small)
	  (shade    . ,shade-image-small)
	  (sticky   . ,(lambda (w) (if (window-get w 'sticky) sticky-image-small 
					unsticky-image-small))))))


;; Buttons:
;; --------

(define button-classes
  `((close    . close-button)
	(iconify  . iconify-button)
	(maximize . maximize-button)
	(menu     . menu-button)
	(shade    . shade-button)
	(sticky   . sticky-button)))

(def-frame-class sticky-button '((cursor . tcross))
  (bind-keys sticky-button-keymap "Button1-Off" 'toggle-window-sticky))

(def-frame-class shade-button '((cursor . based_arrow_down))
  (bind-keys shade-button-keymap "Button1-Off" 'toggle-window-shaded))

(define build-buttons
  (lambda ()
    (setq dragdome:bar-placement 
	  (sort (copy-sequence dragdome:bar-placement) 
	        (lambda (a b) (< (cdr a) (cdr b)))))
    (setq dragdome:bar-placement-small 
	  (sort (copy-sequence dragdome:bar-placement-small) 
	        (lambda (a b) (< (cdr a) (cdr b)))))))


;; Frames:
;; -------

(define build-frames 
  (lambda ()
	(let* 
	 ((button-placement 
		(delete (assoc 'title dragdome:bar-placement) 
		  (copy-sequence dragdome:bar-placement)))
	  (button-placement-small 
		(delete (assoc 'title dragdome:bar-placement-small) 
		  (copy-sequence dragdome:bar-placement-small)))
	  
	  (frame-size 5)
	  (bar-bevel 2)
	  (bar-padding (+ 2 (* (if (assoc 'title dragdome:bar-placement) 4 2) bar-bevel)))
	  (bar-padding-small (+ 2 (* (if (assoc 'title dragdome:bar-placement-small) 4 2) bar-bevel)))
	  (bar-height 24)
	  (bar-height-small 24)
	  (bar-top-edge (- (+ bar-height (* 2 bar-bevel))))
	  (bar-top-edge-small (- (+ bar-height-small (* 2 bar-bevel))))
	  (button-size 16)
	  (button-size-small 16)
	  (button-position (- (+ 1 bar-bevel button-size (/ (- bar-height button-size) 2))))
	  (button-position-small (- (+ 1 bar-bevel button-size-small 
		(/ (- bar-height-small button-size-small) 2))))
	  
	  (font-colours (list dragdome:unfocused-text-colour dragdome:focused-text-colour))

	  (window-width
		(lambda (w)
		  (car (window-dimensions w))))

	  (frame-width
		(lambda (w)
		  (+ frame-size frame-size (window-width w))))
	  
	  (title-width
		(lambda (w)
		  (if (assoc 'title dragdome:bar-placement)
		  (if dragdome:full-title-width 
		    (- (frame-width w) bar-padding (* (length button-placement) button-size))
		    (max 0 (min 
			  (- (frame-width w) 
			     bar-padding (* (length button-placement) button-size))
			  (+ button-size (text-width (window-name w) dragdome:font)))))
		  0)))
	  
	  (title-width-small
		(lambda (w)
		  (if (assoc 'title dragdome:bar-placement-small)
		  (if dragdome:full-title-width 
		    (- (frame-width w) bar-padding (* (length button-placement-small) button-size-small))
			(max 0 (min 
			  (- (frame-width w) 
				 (+ bar-padding-small 
				  (* (length button-placement-small) button-size-small)))
			  (+ button-size-small (text-width (window-name w) dragdome:font-small)))))
		  0)))
	  
	  (bar-width
		(lambda (w)
		  (+ bar-padding 
			 (* (length button-placement) button-size) 
			 (title-width w))))
	  
	  (bar-width-small
		(lambda (w)
		  (+ bar-padding-small
			 (* (length button-placement-small) button-size-small) 
			 (title-width-small w))))
	  
	  ;; This function determines the appropriate offset for the title bar.
	  ;; It's result is added to all frame parts that should be shifted.

	  (bar-offset 
		(lambda (w) 
		  (- (inexact->exact  
			  (* (or (window-get w 'title-offset) 0)
				 (- (frame-width w) (bar-width w))))
			 frame-size)))
	  
	  (bar-offset-small
		(lambda (w) 
		  (- (inexact->exact  
			  (* (or (window-get w 'title-offset) 0)
				 (- (frame-width w) (bar-width-small w))))
			 frame-size)))
	  
	  (button-offset
		(lambda (w button)
		  (let*
			((offset (+ (bar-offset w) 1 bar-bevel)))
			(catch 'return
			  (mapc (lambda (x)
					  (if (equal (car x) button)
						  (throw 'return offset)
						  (setq offset 
							(+ offset 
							  (if (equal (car x) 'title) 
								(+ (title-width w) bar-bevel bar-bevel)
								button-size)))))
					dragdome:bar-placement)))))

	  (button-offset-small
		(lambda (w button)
		  (let*
			((offset (+ (bar-offset-small w) 1 bar-bevel)))
			(catch 'return
			  (mapc (lambda (x)
					  (if (equal (car x) button)
						  (throw 'return offset)
						  (setq offset 
							(+ offset 
							  (if (equal (car x) 'title) 
								(+ (title-width-small w) bar-bevel bar-bevel)
							    button-size-small)))))
					dragdome:bar-placement-small)))))

	  (title-offset
		(lambda (w)
		  (+ bar-bevel 1 
			 (/ button-size 2)
			 (* button-size 
			   (- (length dragdome:bar-placement) 
				  (length 
					(member 
					  (assoc 'title dragdome:bar-placement) 
					  dragdome:bar-placement)))))))
	  
	  (title-offset-small
		(lambda (w)
		  (+ bar-bevel 1
			 (/ button-size-small 2)
			 (* button-size-small 
			   (- (length dragdome:bar-placement-small) 
				  (length 
					(member 
					  (assoc 'title dragdome:bar-placement-small) 
					  dragdome:bar-placement-small))))))))
	  
	  (setq border-frame `(
		((background  . ,top-image)
		 (top-edge    . -5)
		 (left-edge   . 0)
		 (right-edge  . 0)
		 (class       . title))
		((background  . ,top-left-image)
		 (left-edge   . -5)
		 (top-edge    . -5)
		 (class       . title))
		((background  . ,top-right-image)
		 (right-edge  . -5)
		 (top-edge    . -5)
		 (class       . title))
		((background  . ,left-image)
		 (left-edge   . -5)
		 (top-edge    . 0)
		 (bottom-edge . 0)
		 (class       . left-border))
		((background  . ,right-image)
		 (right-edge  . -5)
		 (top-edge    . 0)
		 (bottom-edge . 0)
		 (class       . right-border))
		((background  . ,bottom-image)
		 (left-edge   . 0)
		 (right-edge  . 0)
		 (bottom-edge . -5)
		 (class       . bottom-border))
		((background  . ,bottom-left-image)
		 (left-edge   . -5)
		 (bottom-edge . -5)
		 (class       . bottom-left-corner))
		((background  . ,bottom-right-image)
		 (right-edge  . -5)
		 (bottom-edge . -5)
		 (class       . bottom-right-corner))
	  ))
	  
	  (setq title-shadow `(
		
		((background . ,shadow-left-image)
		 (left-edge  . ,bar-offset)
		 (top-edge   . -4)
		 (class      . title))
		 
		((background . ,shadow-mid-image)
		 (left-edge  . ,(lambda (w) (+ bar-bevel (bar-offset w))))
		 (right-edge . ,(lambda (w) (- (+ (window-width w) bar-bevel) 
		                               (bar-offset w) (bar-width w)))) 
		 (top-edge   . -4)
		 (class      . title))

		((background . ,shadow-right-image)
		 (right-edge . ,(lambda (w) (- (window-width w) (bar-offset w) (bar-width w))))
		 (top-edge   . -4)
		 (class      . title))
	  ))

	  (setq bar `(
		
		((background . ,title-image)
		 (foreground . ,font-colours)
		 (font       . ,dragdome:font)
		 (text       . ,window-name)
		 (top-edge   . ,bar-top-edge)
		 (left-edge  . ,(lambda (w) (+ bar-bevel (bar-offset w))))
		 (right-edge . ,(lambda (w) 
						  (- (+ (window-width w) bar-bevel) 
							 (bar-offset w) (bar-width w))))
		 (x-justify  . ,(lambda (w) (if dragdome:full-title-width 'center (title-offset w))))
		 (y-justify  . 2)
		 (class      . title))
		
		((background . ,bar-right-image)
		 (right-edge . ,(lambda (w) (- (window-width w) 
						  (bar-offset w) (bar-width w)))) 
		 (top-edge   . ,bar-top-edge)
		 (class      . title))
		
		((background . ,bar-left-image)
		 (left-edge  . ,bar-offset)
		 (top-edge   . ,bar-top-edge)
		 (class      . title))
		
		,@(mapcar (lambda (x) 
		   `((background . ,(cdr (assoc (car x) button-images)))
			 (class      . ,(cdr (assoc (car x) button-classes)))
			 (left-edge  . ,(lambda (w) (button-offset w (car x))))
			 (right-edge . ,(lambda (w) (- (window-width w) button-size
							  (button-offset w (car x)))))
			 (top-edge   . ,button-position)
			 (height     . ,button-size)
			 (removable  . t)))
		   button-placement)
	  ))

	  (setq frame        `( ,@title-shadow ,@border-frame ,@bar ))
	  (setq shaped-frame `( ,@title-shadow ,@bar ))

	  (setq title-shadow-small `(
		
		((background . ,shadow-left-image)
		 (left-edge  . ,bar-offset-small)
		 (top-edge   . -4)
		 (class      . title))
		 
		((background . ,shadow-mid-image)
		 (left-edge  . ,(lambda (w) (+ bar-bevel (bar-offset-small w))))
		 (right-edge . ,(lambda (w) (- (+ (window-width w) bar-bevel) 
						  (bar-offset-small w) (bar-width-small w)))) 
		 (top-edge   . -4)
		 (class      . title))

		((background . ,shadow-right-image)
		 (right-edge . ,(lambda (w) (- (window-width w) (bar-offset-small w) 
						  (bar-width-small w))))
		 (top-edge   . -4)
		 (class      . title))
	  ))

	  (setq bar-small `(
		  
		((background . ,bar-left-image-small)
		 (left-edge  . ,bar-offset-small)
		 (top-edge   . ,bar-top-edge-small)
		 (class      . title))
		
		((background . ,bar-right-image-small)
		 (right-edge . ,(lambda (w) (- (window-width w) (bar-offset-small w) 
						  (bar-width-small w)))) 
		 (top-edge   . ,bar-top-edge-small)
		 (class      . title))
		
		((background . ,title-image-small)
		 (foreground . ,font-colours)
		 (font       . ,dragdome:font-small)
		 (text       . ,window-name)
		 (top-edge   . ,bar-top-edge-small)
		 (left-edge  . ,(lambda (w) (+ bar-bevel (bar-offset-small w)))) 
		 (right-edge . ,(lambda (w) (- (+ (window-width w) bar-bevel) 
						  (bar-offset-small w) (bar-width-small w))))
		 (x-justify  . ,(lambda (w) (if dragdome:full-title-width 'center (title-offset-small w))))
		 (y-justify  . 2)
		 (class      . title))
		
		,@(mapcar (lambda (x) 
		   `((background . ,(cdr (assoc (car x) button-images-small)))
			 (class      . ,(cdr (assoc (car x) button-classes)))
			 (left-edge  . ,(lambda (w) (button-offset-small w (car x))))
			 (right-edge . ,(lambda (w) (- (window-width w) button-size-small
							  (button-offset-small w (car x)))))
			 (top-edge   . ,button-position-small)
			 (removable  . t)))
		   button-placement-small)
	  ))
	  
	  (setq frame-small        `(,@title-shadow-small ,@border-frame ,@bar-small))
	  (setq shaped-frame-small `(,@title-shadow-small ,@bar-small))
			
	)))
	
(define redraw-one-frame 
  (lambda (w)
    (if (eq (window-get w 'current-frame-style) 'DragDome)
      (rebuild-frame w))))

(define (redraw-frames-colours-changed)
  (recolour-images)
  (build-images)
  (build-frames)
  (reframe-windows-with-style 'DragDome))

(define (redraw-frames-images-changed)
  (build-images)
  (build-frames)
  (reframe-windows-with-style 'DragDome))

(define (redraw-frames-buttons-changed)
  (build-buttons)
  (build-frames)
  (reframe-windows-with-style 'DragDome))

(define (redraw-frames-frames-changed)
  (build-frames)
  (reframe-windows-with-style 'DragDome))

(recolour-images)
(build-images)
(build-buttons)
(build-frames)
	
(add-frame-style 'DragDome
  (lambda (w type)
    (case type
      ((default)          frame)
  	  ((shaped)           shaped-frame)
      ((transient)        frame-small)
      ((shaped-transient) shaped-frame-small)
  	  ((unframed)		  nil-frame))))
          
(call-after-property-changed 'WM_NAME redraw-one-frame)
(call-after-state-changed   '(sticky) redraw-one-frame)

(custom-set-property 'dragdome:font					  ':after-set redraw-frames-frames-changed)
(custom-set-property 'dragdome:font-small			  ':after-set redraw-frames-frames-changed)
(custom-set-property 'dragdome:full-title-width		  ':after-set redraw-frames-frames-changed)
(custom-set-property 'dragdome:focused-text-colour	  ':after-set redraw-frames-frames-changed)
(custom-set-property 'dragdome:unfocused-text-colour  ':after-set redraw-frames-frames-changed)
(custom-set-property 'dragdome:bar-placement		  ':after-set redraw-frames-buttons-changed)
(custom-set-property 'dragdome:bar-placement-small	  ':after-set redraw-frames-buttons-changed)
(custom-set-property 'dragdome:show-unfocused-buttons ':after-set redraw-frames-images-changed)
(custom-set-property 'dragdome:focused-title-colour	  ':after-set redraw-frames-colours-changed)
(custom-set-property 'dragdome:unfocused-title-colour ':after-set redraw-frames-colours-changed)

