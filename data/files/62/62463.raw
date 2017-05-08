;; basic/theme.jl
;; $Id: theme.jl,v 1.1 2001/03/15 06:40:24 sfarrell Exp $


(defgroup basic "Basic"
  :group appearance)

(defcustom basic:normal-color "#9eb79eb79eb7"
  "Color of inactive frames in `basic' frame style."
  :type color
  :group (appearance basic)
  :user-level novice
  :after-set after-setting-frame-option)

(defcustom basic:active-color "#d995d995eb84"
  "Color of active frames in `basic' frame style."
  :type color
  :group (appearance basic)
  :user-level novice
  :after-set after-setting-frame-option)

(let*
    ((minimize (list (make-image "as_min.png") nil
                     nil (make-image "as_min-b.png")))
     (maximize (list (make-image "as_max.png") nil
                     nil (make-image "as_max-b.png")))
     (close (list (make-image "as_close.png") nil
                  nil (make-image "as_close-b.png")))
     (default (list (make-image "default.png")))
     (menu (lambda (w) (let ((icon (window-icon-image w)))
			 (if icon (list icon) default))))

     (frame-colors (lambda (w)
		     (list (or (window-get w 'frame-inactive-color)
			       basic:normal-color)
			   (or (window-get w 'frame-active-color)
			       basic:active-color))))

     (frame `(
	      ;; fill in the whole back of the title-bar
	      ;; XXX this does a little extra drawing
	      ((background . ,frame-colors)
	       (top-edge . -21)
	       (height . 21)
	       (left-edge . 0)
	       (right-edge . 0))

	      ;; fill in the text of the title-bar
	      ((background . ,frame-colors)
	       (foreground . "black")
	       (text . ,window-name)
	       (x-justify . 20)
	       (y-justify . center)
	       (left-edge . 0)
	       (right-edge . 56)
	       (top-edge . -21)
	       (height . 21)
	       (class . title))


	      ;; top
	      ((background . "black")
	       (left-edge . -4)
	       (right-edge . -4)
	       (top-edge . -22)
	       (height . 1))
	       
	      ;; left
	      ((background . "black")
	       (left-edge . -5)
	       (width . 1)
	       (top-edge . -22)
	       (bottom-edge . -5))
	       
	      ;; right
	      ((background . "black")
	       (right-edge . -5)
	       (width . 1)
	       (top-edge . -22)
	       (bottom-edge . -5))

	      ;; ((background . "gray")
	       ;; (right-edge . -6)
	       ;; (width . 1)
	       ;; (top-edge . -22)
	       ;; (bottom-edge . -6))

	      ;; bottom
	      ((background . "black")
	       (left-edge . -4)
	       (right-edge . -4)
	       (bottom-edge . -5)
	       (height . 1))

	      ;; ((background . "gray")
	       ;; (left-edge . -4)
	       ;; (right-edge . -4)
	       ;; (bottom-edge . -6)
	       ;; (height . 1))

	      ((background . ,frame-colors)
	       (left-edge . 0)
	       (right-edge . 0)
	       (bottom-edge . -4)
	       (height . 4)
	       (class . bottom-border))

	      ((background . ,frame-colors)
	       (right-edge . -4)
	       (top-edge . -21)
	       (bottom-edge . 0)
	       (width . 4)
	       (class . right-border))

	      ((background . ,frame-colors)
	       (left-edge . -4)
	       (top-edge . -21)
	       (bottom-edge . 0)
	       (width . 4)
	       (class . left-border))

	      ((background . ,frame-colors)
		(left-edge . -4)
		(width . 4)
		(bottom-edge . -4)
		(height . 4)
	       (class . bottom-left-corner))

	      ((background . ,frame-colors)
		(right-edge . -4)
		(width . 4)
		(bottom-edge . -4)
		(height . 4)
	       (class . bottom-right-corner))
	       
              ((background . ,menu)
               (left-edge . 0)
               (top-edge . -18)
	       (height . 16)
	       (width . 16)
	       (scale-foreground . t)
               (class . menu-button)
               (removable . t))

              ((background . ,minimize)
               (right-edge . 36)
               (top-edge . -18)
               (class . iconify-button)
               (removable . t))

              ((background . ,maximize)
               (right-edge . 18)
               (top-edge . -18)
               (class . maximize-button)
               (removable . t))
               
              ((background . ,close)
               (right-edge . 0)
               (top-edge . -18)
               (class . close-button)
               (removable . t))))
	       

     (shaped-frame `(((background . ,frame-colors)
		      (foreground . "black")
		      (text . ,window-name)
		      (x-justify . 30)
		      (y-justify . center)
		      (left-edge . 0)
		      (right-edge . 0)
		      (top-edge . -22)
		      (height . 21)
		      (class . title))
		      
		     ((background . "black")
		      (left-edge . 0)
		      (right-edge . 0)
		      (top-edge . -23)
		      (height . 1))
		      
		     ((background . "black")
		      (left-edge . -1)
		      (width . 1)
		      (top-edge . -23)
		      (height . 23))
		      
		     ((background . "black")
		      (right-edge . -1)
		      (width . 1)
		      (top-edge . -23)
		      (height . 23))
		      
		     ((background . "black")
		      (left-edge . 0)
		      (right-edge . 0)
		      (top-edge . -1)
		      (height . 1))

		     ((background . ,minimize)
		      (left-edge . 4)
		      (top-edge . -19)
		      (class . iconify-button)
		      (removable . t))
		      
		     ((background . ,close)
		      (right-edge . 4)
		      (top-edge . -19)
		      (class . close-button)
		      (removable . t))))

     (transient-frame `(((background . ,frame-colors)
			 (left-edge . 0)
			 (right-edge . 0)
			 (top-edge . -4)
			 (height . 4)
			 (class . title))
			 
			((background . "black")
			 (left-edge . 0)
			 (right-edge . 0)
			 (top-edge . -5)
			 (height . 1))
			 
			((background . "black")
			 (left-edge . -1)
			 (width . 1)
			 (top-edge . -5)
			 (bottom-edge . -5))
			 
			((background . "black")
			 (right-edge . -1)
			 (width . 1)
			 (top-edge . -5)
			 (bottom-edge . -5))

			((background . ,frame-colors)
			 (left-edge . 0)
			 (right-edge . 0)
			 (bottom-edge . -4)
			 (height . 4)
			 (class . bottom-border))
			 
			((background . "black")
			 (left-edge . 0)
			 (right-edge . 0)
			 (bottom-edge . -5)
			 (height . 1))))

     (shaped-transient-frame `(((background . ,frame-colors)
				(left-edge . 0)
				(right-edge . 0)
				(top-edge . -5)
				(height . 4)
				(class . title))
				
			       ((background . "black")
				(left-edge . 0)
				(right-edge . 0)
				(top-edge . -6)
				(height . 1))
				
			       ((background . "black")
				(left-edge . -1)
				(width . 1)
				(top-edge . -6)
				(height . 6))
				
			       ((background . "black")
				(right-edge . -1)
				(width . 1)
				(top-edge . -6)
				(height . 6))
				
			       ((background . "black")
				(left-edge . 0)
				(right-edge . 0)
				(top-edge . -1)
				(height . 1)))))

  (add-frame-style 'basic
		   (lambda (w type)
		     (case type
		       ((default) frame)
		       ((transient) transient-frame)
		       ((shaped) shaped-frame)
		       ((shaped-transient) shaped-transient-frame)))))
