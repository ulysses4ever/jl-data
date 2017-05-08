;; win98/theme.jl

;; Copyright (C) 1999 Lyonel Vincent <vincent@eea.ec-lyon.fr>
;; based on the gradient and brushed-metal themes by John Harper <john@dcs.warwick.ac.uk>

(require 'gradient)

(defgroup win98-frame "Windows 98 look & feel")

(defcustom win98:gradient-type 'horizontal
   "Direction of gradient."
     :type (set horizontal vertical diagonal)
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:normal-color1 (get-color "gray")
   "Right color of inactive title bar"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:normal-color2 (get-color "lightgray")
   "Left color of inactive title bar"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:active-color1 (get-color "navy")
   "Right color of active title bar"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:active-color2 (get-color "cornflower blue")
   "Left color of active title bar"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:active-title-color (get-color "white")
   "Color of active title"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:normal-title-color (get-color "black")
   "Color of inactive title"
     :type color
     :group win98-frame
     :after-set after-setting-frame-option)

(defcustom win98:font
   (get-font "-adobe-helvetica-bold-r-normal-*-*-120-*-*-p-*-iso8859-1")
   "Font for window titles"
   :type font
   :group win98-frame
   :after-set after-setting-frame-option)

(let*
    (
     (render-bg (lambda (img state)
                  (apply (cond ((eq win98:gradient-type 'diagonal)
                                draw-diagonal-gradient)
                               ((eq win98:gradient-type 'horizontal)
                                draw-horizontal-gradient)
                               ((eq win98:gradient-type 'vertical)
                                draw-vertical-gradient))
                         img (if state
                                 (list win98:active-color1
                                       win98:active-color2)
                               (list win98:normal-color1
                                     win98:normal-color2)))
                  (when (> (cdr (image-dimensions img)) 4)
                    (bevel-image img 1 (not (eq state 'clicked))))
                  (set-image-border img 1 1 1 1)))
     
     (bottom-images (list (make-image "b6-.png") (make-image "b6.png")))

     (top-images (list (make-image "b2-.png") (make-image "b2.png")))

     (right-images (list (flip-image-diagonally
			  (copy-image (nth 0 bottom-images)))
			 (flip-image-diagonally
			  (copy-image (nth 1 bottom-images)))))

     (left-images (list (flip-image-diagonally
			 (copy-image (nth 0 top-images)))
			(flip-image-diagonally
			 (copy-image (nth 1 top-images)))))

     (top-left-images (list (make-image "b1.png")))
     (bottom-left-images (list (make-image "b7.png")))
     (top-right-images (list (make-image "b3.png")))
     (bottom-right-images (list (make-image "b5.png")))

     (default-icon (list (make-image "t1.png")))
     (menu-images (lambda (w)
                          (let ((icon (window-icon-image w)))
                               (if (eq icon 'nil) default-icon (list icon)))
                          ))

     (corner-images (list (make-image "corner.png")))

     (iconify-images (list (make-image "minimize-.png") (make-image "minimize.png")
			   nil (make-image "minimize-b.png")))

     (maximize-images (list (make-image "maximize-.png") (make-image "maximize.png")
			    nil (make-image "maximize-b.png")))

     (unmaximize-images (list (make-image "unmaximize-.png") (make-image "unmaximize.png")
			    nil (make-image "unmaximize-b.png")))

     (max-unmax-images (lambda (w)
                          (if (window-maximized-p w) unmaximize-images maximize-images)))

     (close-images (list (make-image "close-.png") (make-image "close.png")
			 nil (make-image "close-b.png")))

     (frame-colors (lambda ()
		    (list win98:normal-color1 win98:active-color1)))

     (title-colors (lambda ()
		    (list win98:normal-title-color win98:active-title-color)))

     (frame `(
	      (
	       (foreground . ,title-colors)
	       (renderer . ,render-bg)
	       (text . ,window-name)
	       (font . ,(lambda () (list win98:font)))
	       (x-justify . 20)
	       (y-justify . center)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -22)
	       (height . 22)
	       (class . title))

	      ((background . ,menu-images)
	       (top-edge . -17)
	       (left-edge . 2)
               (width . 16)
               (height . 16)
	       (class . menu-button))

	      ((background . ,iconify-images)
	       (right-edge . 37)
	       (top-edge . -16)
	       (class . iconify-button))

	      ((background . ,max-unmax-images)
	       (right-edge . 21)
	       (top-edge . -16)
	       (class . maximize-button))

	      ((background . ,close-images)
	       (right-edge . 3)
	       (top-edge . -16)
	       (class . close-button))

	      ((background . ,left-images)
	       (left-edge . -4)
	       (top-edge . -19)
	       (bottom-edge . 0)
	       (class . left-border))

	      ((background . ,right-images)
	       (right-edge . -4)
	       (top-edge . -19)
	       (bottom-edge . 0)
	       (class . right-border))

	      ((background . ,top-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -23)
	       (class . top-border))

	      ((background . ,bottom-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (bottom-edge . -4)
	       (class . bottom-border))

	      ((background . ,top-left-images)
	       (left-edge . -4)
	       (top-edge . -23)
	       (class . top-left-corner))

	      ((background . ,top-right-images)
	       (right-edge . -4)
	       (top-edge . -23)
	       (class . top-right-corner))

	      ((background . ,bottom-left-images)
	       (left-edge . -4)
	       (bottom-edge . -4)
	       (class . bottom-left-corner))

	      ((background . ,bottom-right-images)
	       (right-edge . -4)
	       (bottom-edge . -4)
	       (class . bottom-right-corner))

	      ((background . ,corner-images)
	       (bottom-edge . 0)
	       (right-edge . 0)
	       (class . bottom-right-border))))

     (transient-frame `(
	      (
	       (foreground . ,title-colors)
	       (renderer . ,render-bg)
	       (text . ,window-name)
	       (font . ,(lambda () (list win98:font)))
	       (x-justify . 4)
	       (y-justify . center)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -22)
	       (height . 22)
	       (class . title))

	      ((background . ,close-images)
	       (right-edge . 3)
	       (top-edge . -16)
	       (class . close-button))

	      ((background . ,left-images)
	       (left-edge . -4)
	       (top-edge . -19)
	       (bottom-edge . 0)
	       (class . left-border))

	      ((background . ,right-images)
	       (right-edge . -4)
	       (top-edge . -19)
	       (bottom-edge . 0)
	       (class . right-border))

	      ((background . ,top-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -23)
	       (class . top-border))

	      ((background . ,bottom-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (bottom-edge . -4)
	       (class . bottom-border))

	      ((background . ,top-left-images)
	       (left-edge . -4)
	       (top-edge . -23)
	       (class . top-left-corner))

	      ((background . ,top-right-images)
	       (right-edge . -4)
	       (top-edge . -23)
	       (class . top-right-corner))

	      ((background . ,bottom-left-images)
	       (left-edge . -4)
	       (bottom-edge . -4)
	       (class . bottom-left-corner))

	      ((background . ,bottom-right-images)
	       (right-edge . -4)
	       (bottom-edge . -4)
	       (class . bottom-right-corner))))

     (shaped-frame `(
	      (
	       (foreground . ,title-colors)
	       (renderer . ,render-bg)
	       (text . ,window-name)
	       (font . ,(lambda () (list win98:font)))
	       (x-justify . 20)
	       (y-justify . center)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -22)
	       (class . title))

	      ((background . ,menu-images)
	       (top-edge . -17)
	       (left-edge . 2)
               (width . 16)
               (height . 16)
	       (class . menu-button))

	      ((background . ,iconify-images)
	       (right-edge . 37)
	       (top-edge . -16)
	       (class . iconify-button))

	      ((background . ,max-unmax-images)
	       (right-edge . 21)
	       (top-edge . -16)
	       (class . maximize-button))

	      ((background . ,close-images)
	       (right-edge . 3)
	       (top-edge . -16)
	       (class . close-button))

	      ((background . ,left-images)
	       (left-edge . -4)
	       (top-edge . -19)
	       (height . 20)
	       (class . left-border))

	      ((background . ,right-images)
	       (right-edge . -4)
	       (top-edge . -19)
	       (height . 20)
	       (class . right-border))

	      ((background . ,top-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . -23)
	       (class . top-border))

	      ((background . ,bottom-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (top-edge . 0)
	       (class . bottom-border))

	      ((background . ,top-left-images)
	       (left-edge . -4)
	       (top-edge . -23)
	       (class . top-left-corner))

	      ((background . ,top-right-images)
	       (right-edge . -4)
	       (top-edge . -23)
	       (class . top-right-corner))

	      ((background . ,bottom-left-images)
	       (left-edge . -4)
	       (top-edge . 1)
	       (class . bottom-left-corner))

	      ((background . ,bottom-right-images)
	       (right-edge . -4)
	       (top-edge . 1)
	       (class . bottom-right-corner))))
	)


  (add-frame-style 'win98
                   (lambda (w type)
                     (cond ((eq type 'shaped)
                            shaped-frame)
                           ((eq type 'shaded)
                            shaped-frame)
                           ((eq type 'transient)
                            transient-frame)
                           ((eq type 'shaped-transient)
                            shaped-frame)
                           ((eq type 'shaded-transient)
                            shaped-frame)
                           ((eq type 'unframed)
                            nil-frame)
                           (t
                            frame)))))
