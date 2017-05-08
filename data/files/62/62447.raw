;; Lunatic theme 0.2
;; Implemented by Stefan Zeiger <szeiger@szeiger.de>

;; The make-title-image function is based on
;; make-text-image by Simon Budig <simon.budig@unix-ag.org>

(require 'x)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Theme configuration options

(defgroup Lunatic "Lunatic Theme" :group appearance)

(defcustom Lunatic:icon-mode 'if-available
  "Show window icon in title bar: \\w"
  :type (choice (always       "Always (use default icon where necessary)")
		(if-available "If available (don't use the default icon)")
		(never        "Never"))
  :group (appearance Lunatic)
  :after-set after-setting-frame-option)

(defcustom Lunatic:title-height 29
  "Title bar height: \\w"
  :type number
  :group (appearance Lunatic)
  :range (13 . 29)
  :after-set after-setting-frame-option)

(defcustom Lunatic:title-text-offset 16
  "Y offset for text on title bars: \\w"
  :type number
  :group (appearance Lunatic)
  :after-set after-setting-frame-option)

(defcustom Lunatic:shadow-style 'soft-shadows
  "Title bar text has \\w shadows"
  :type (choice (no-shadows            "no")
		(soft-shadows          "soft")
		(hard-and-soft-shadows "hard and soft"))
  :group (appearance Lunatic)
  :after-set after-setting-frame-option)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Auxiliary functions

(define black-color (get-color "#000000"))
(define white-color (get-color "#ffffff"))

(define (make-title-image w text-color shadow-color outline-color)
  (let* ( (width (max 0 (- (car (window-dimensions w))
                           -15
                           (text-left-edge w)
                           (* 3 Lunatic:title-height) )))
          (height 25)
          (font default-font)
          (string (window-name w))
          shapedrw image
          (ybase Lunatic:title-text-offset)
          (drawable (x-create-pixmap (cons width height))) )

    (let
      ( (text-gc    (x-create-gc drawable `((foreground . ,text-color))))
        (shadow-gc  (x-create-gc drawable `((foreground . ,shadow-color))))
        (outline-gc (x-create-gc drawable `((foreground . ,outline-color)))) )
      (x-fill-rectangle drawable outline-gc '(0 . 0) (cons width height))
      (if (eq Lunatic:shadow-style 'hard-and-soft-shadows)
        (x-draw-string drawable shadow-gc (cons 2 (+ ybase 1)) string font) )
      (x-draw-string drawable text-gc (cons 1 ybase ) string font)
      (x-destroy-gc text-gc)
      (x-destroy-gc shadow-gc)
      (x-destroy-gc outline-gc)
    )

    (setq shapedrw (x-create-pixmap (cons width height)))

    (let ((gc (x-create-gc shapedrw `((foreground . ,black-color)))))
      (x-fill-rectangle shapedrw gc '(0 . 0) (cons width height))
      (x-change-gc gc `((foreground . ,white-color)))

      (x-draw-string shapedrw gc (cons 1 ybase) string font)

      (if (eq Lunatic:shadow-style 'no-shadows)
        nil
        (x-draw-string shapedrw gc (cons 0 (- ybase 1)) string font)
        (x-draw-string shapedrw gc (cons 2 (- ybase 1)) string font)
        (x-draw-string shapedrw gc (cons 0 ybase) string font)
        (x-draw-string shapedrw gc (cons 3 ybase) string font)
        (x-draw-string shapedrw gc (cons 0 (+ ybase 1)) string font)
        (x-draw-string shapedrw gc (cons 2 (+ ybase 1)) string font)
        (x-draw-string shapedrw gc (cons 3 (+ ybase 1)) string font)
        (x-draw-string shapedrw gc (cons 1 (+ ybase 2)) string font)
        (x-draw-string shapedrw gc (cons 3 (+ ybase 2)) string font)
        (x-draw-string shapedrw gc (cons 3 (+ ybase 3)) string font) )

      (x-destroy-gc gc)
    )

    (setq image (x-grab-image-from-drawable drawable shapedrw))
    (x-destroy-drawable drawable)
    (x-destroy-drawable shapedrw)
    image
  ))

(define (make-title-images w)
  (list (make-title-image w
           inactive-text-color inactive-shadow-color inactive-outline-color)
        (make-title-image w
           focused-text-color focused-shadow-color focused-outline-color)))

(define (make-images name #!optional (lo 0) (ro 0) (to 0) (bo 0))
  (mapcar
    (lambda (e) (set-image-border (make-image (concat name e)) lo ro to bo))
    '("-i.png" "-f.png")))

(define (make-button-images name)
  (define (mk type)
    (set-image-border
      (make-image (concat "button-" name "-" type ".png"))
      3 3 3 3))
  (list
    (cons 'inactive             (mk "i"))
    (cons 'focused              (mk "f"))
    (cons 'inactive-highlighted (mk "ih"))
    (cons 'highlighted          (mk "h"))
    (cons 'inactive-clicked     (mk "ic"))
    (cons 'clicked              (mk "c"))
  ))

(define (hide-menu-image w)
  (case Lunatic:icon-mode
    ((always)       nil)
    ((if-available) (not (window-icon-image w)))
    ((never)        t) ))

(define (text-left-edge w)
  (if (hide-menu-image w) 10 (- Lunatic:title-height 2)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Colors

(define inactive-text-color    (get-color "#e8f5f5"))
(define inactive-shadow-color  (get-color "#26365d"))
(define inactive-outline-color (get-color "#3d6090"))
(define focused-text-color     (get-color "#dfffff"))
(define focused-shadow-color   (get-color "#002584"))
(define focused-outline-color  (get-color "#0356cc"))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Images

(define default-icon  (list (make-image "default-icon.png")))
(define menuback-imgs (make-images "menuback"))
(define ltitle-imgs   (make-images "ltitle" 10 0 3 6))
(define rtitle-imgs   (make-images "rtitle" 0 7 3 6))
(define lshaded-imgs  (make-images "lshaded" 13 0 6 6))
(define rshaded-imgs  (make-images "rshaded" 0 8 6 6))
(define close-imgs    (make-button-images "c"))
(define iconify-imgs  (make-button-images "i"))
(define max-imgs      (make-button-images "m"))
(define restore-imgs  (make-button-images "r"))
(define top-imgs      (make-images "tborder" 5))
(define bottom-imgs   (make-images "b"))
(define left-imgs     (make-images "l" 0 0 21))
(define right-imgs    (make-images "r" 0 0 21))
(define bl-imgs       (make-images "bl"))
(define br-imgs       (make-images "br"))
(define tl-imgs       (make-images "tl" 0 0 6))
(define tr-imgs       (make-images "tr" 0 0 6))

(define (menu-img w)
  (let ((icon (window-icon-image w)))
    (if icon (list icon) default-icon)) )

(define (max-restore-imgs w)
  (if (window-maximized-p w) restore-imgs max-imgs))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Define and install frames

(define frame-buttons `(
  ((width . ,(lambda (w) (- Lunatic:title-height 10)))
   (height . ,(lambda (w) (- Lunatic:title-height 10)))
   (top-edge . ,(lambda (w) (- 5 Lunatic:title-height)))
   (cursor . left_ptr)
   (class . menu-button)
   (left-edge . 2)
   (scale-foreground . t)
   (hidden . ,hide-menu-image)
   (foreground . ,menu-img)
   (background . ,menuback-imgs))

  ((right-edge . 0)
   (cursor . left_ptr)
   (top-edge . ,(lambda (w) (- 3 Lunatic:title-height)))
   (height . ,(lambda (w) (- Lunatic:title-height 6)))
   (width . ,(lambda (w) (- Lunatic:title-height 6)))
   (removable . t)
   (background . ,close-imgs)
   (class . close-button))

  ((cursor . left_ptr)
   (right-edge . ,(lambda (w) (- Lunatic:title-height 5)))
   (removable . t)
   (top-edge . ,(lambda (w) (- 3 Lunatic:title-height)))
   (height . ,(lambda (w) (- Lunatic:title-height 6)))
   (width . ,(lambda (w) (- Lunatic:title-height 6)))
   (class . maximize-button)
   (background . ,max-restore-imgs))

  ((cursor . left_ptr)
   (right-edge . ,(lambda (w) (- (* 2 Lunatic:title-height) 10)))
   (removable . t)
   (top-edge . ,(lambda (w) (- 3 Lunatic:title-height)))
   (height . ,(lambda (w) (- Lunatic:title-height 6)))
   (width . ,(lambda (w) (- Lunatic:title-height 6)))
   (class . iconify-button)
   (background . ,iconify-imgs))

  ((top-edge . -26)
   (height . 25)
   (cursor . left_ptr)
   (left-edge . ,text-left-edge)
   (class . title)
   (background . ,make-title-images)
   (x-justify . 8)) ))

(define frame (append `(
  ((class . top-border)
   (right-edge . 7)
   (left-edge . 7)
   (top-edge . ,(lambda (w) (- 0 Lunatic:title-height)))
   (height . 3)
   (background . ,top-imgs))

  ((class . top-left-corner)
   (left-edge . -3)
   (top-edge . ,(lambda (w) (- 0 Lunatic:title-height)))
   (background . ,tl-imgs))

  ((class . top-right-corner)
   (right-edge . -3)
   (top-edge . ,(lambda (w) (- 0 Lunatic:title-height)))
   (background . ,tr-imgs))

  ((class . left-border)
   (left-edge . -3)
   (top-edge . ,(lambda (w) (- 10 Lunatic:title-height)))
   (bottom-edge . 7)
   (background . ,left-imgs))

  ((class . right-border)
   (right-edge . -3)
   (top-edge . ,(lambda (w) (- 10 Lunatic:title-height)))
   (bottom-edge . 7)
   (background . ,right-imgs))

  ((class . bottom-border)
   (left-edge . 7)
   (right-edge . 7)
   (bottom-edge . -3)
   (background . ,bottom-imgs))

  ((class . bottom-left-corner)
   (left-edge . -3)
   (bottom-edge . -3)
   (background . ,bl-imgs))

  ((class . bottom-right-corner)
   (right-edge . -3)
   (bottom-edge . -3)
   (background . ,br-imgs))

  ((class . title)
   (right-edge . 0)
   (width . 72)
   (top-edge . ,(lambda (w) (- 3 Lunatic:title-height)))
   (height . ,(lambda (w) (- Lunatic:title-height 3)))
   (cursor . left_ptr)
   (background . ,rtitle-imgs))

  ((right-edge . 72)
   (top-edge . ,(lambda (w) (- 3 Lunatic:title-height)))
   (height . ,(lambda (w) (- Lunatic:title-height 3)))
   (cursor . left_ptr)
   (left-edge . 0)
   (class . title)
   (background . ,ltitle-imgs)
   (x-justify . 8))
 ) frame-buttons))

(define shaped-frame (append `(
  ((cursor . left_ptr)
   (right-edge . -3)
   (width . 75)
   (top-edge . ,(lambda (w) (- 0 Lunatic:title-height)))
   (height . ,(lambda (w) Lunatic:title-height))
   (class . title)
   (background . ,rshaded-imgs))

  ((cursor . left_ptr)
   (top-edge . ,(lambda (w) (- 0 Lunatic:title-height)))
   (right-edge . 72)
   (height . ,(lambda (w) Lunatic:title-height))
   (background . ,lshaded-imgs)
   (class . title)
   (left-edge . -3))
 ) frame-buttons))

(add-frame-style 'Lunatic (lambda (w type) (case type
  ((shaped)           shaped-frame)
  ((shaded)           shaped-frame)
  ((transient)        frame)
  ((shaped-transient) shaped-frame)
  ((shaded-transient) shaped-frame)
  ((unframed)         nil-frame)
  (t                  frame) )))

(call-after-property-changed 'WM_NAME
  (lambda () (rebuild-frames-with-style 'Lunatic)))
