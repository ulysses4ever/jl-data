;; Blue theme 0.6
;; Implemented by Stefan Zeiger <szeiger@szeiger.de>

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Theme configuration options

(defgroup Blue "Blue Theme" :group appearance)

(defcustom Blue:inactive-font-color "#c0c0c0"
  "Text color on title bars of inactive windows."
  :type color
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:focused-font-color "#ffffff"
  "Text color on title bars of focused windows."
  :type color
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:transients-can-iconify t
  "Transient windows can have iconify buttons."
  :type boolean
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:transients-can-max t
  "Transient windows can have maximize/restore buttons."
  :type boolean
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:show-resize-triangle nil
  "Show a resize triangle in the lower right corner of a window."
  :type boolean
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:icon-mode 'if-available
  "Show window icon in title bar: \\w"
  :type (choice (always       "Always (use default icon where necessary)")
		(if-available "If available (don't use the default icon)")
		(never        "Never"))
  :group (appearance Blue)
  :after-set after-setting-frame-option)

(defcustom Blue:title-text-offset 2
  "Y offset for text on title bars: \\w"
  :type number
  :group (appearance Blue)
  :after-set after-setting-frame-option)


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Auxiliary functions

(define (make-images name #!optional (lo 0) (ro 0) (to 0) (bo 0))
  (mapcar
    (lambda (e) (set-image-border (make-image (concat name e)) lo ro to bo))
    '("-i.png" "-f.png")))

(define (crop-images imgs x y w h #!optional (lo 0) (ro 0) (to 0) (bo 0))
  (mapcar
    (lambda (i) (set-image-border (crop-image i x y w h) lo ro to bo))
    imgs))

(define (hide-menu-image w)
  (case Blue:icon-mode
    ((always)       nil)
    ((if-available) (not (window-icon-image w)))
    ((never)        t) ))

(define (text-left-edge w) (if (hide-menu-image w) 0 14))

(define (make-button-images name) (let*
  ( (i-img (make-image (concat name "-i.png")))
    (f-img (make-image (concat name "-f.png")))
    (h-img (make-image (concat name "-h.png")))
    (d (image-dimensions i-img))
    (fr (lambda (fg frame off)
          (composite-images
            (composite-images (make-sized-image (car d) (cdr d)) fg off off)
            (nth frame bframe-imgs) 0 0))) )
  (list
    (cons 'inactive             (fr i-img 0 0))
    (cons 'focused              (fr f-img 1 0))
    (cons 'inactive-highlighted (fr h-img 0 0))
    (cons 'highlighted          (fr h-img 1 0))
    (cons 'inactive-clicked     (fr h-img 0 1))
    (cons 'clicked              (fr h-img 1 1)) )))

(define (hflip-copy i) (mapcar flip-image-horizontally (mapcar copy-image i)))

(define (dflip-copy i) (mapcar flip-image-diagonally (mapcar copy-image i)))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Colors

(define ltitle-colors `("#d4e0bc" "#5297f9"))

(define (font-colors w)
  (list Blue:inactive-font-color Blue:focused-font-color))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Images

(define default-icon  (list (make-image "default-icon.png")))
(define resize-img    (make-image "resize-triangle.png"))
(define title-imgs    (make-images "title" 0 79))
(define ltitle-imgs   (crop-images title-imgs 0 0 1 19))
(define rtitle-imgs   (crop-images title-imgs 79 0 1 19))
(define shaded-imgs   (make-images "shaded" 0 79))
(define lshaded-imgs  (make-images "lshaded" 2))
(define rshaded-imgs  (make-images "rshaded" 0 1))
(define bframe-imgs   (make-images "buttonframe"))
(define close-imgs    (make-button-images "close"))
(define iconify-imgs  (make-button-images "iconify"))
(define max-imgs      (make-button-images "maximize"))
(define restore-imgs  (make-button-images "restore"))
(define top-imgs      (make-images "tborder" 0 135))
(define top-imgs-left (crop-images top-imgs 0 0 1 3))
(define bl-imgs       (make-images "bl"))
(define br-imgs       (hflip-copy bl-imgs))
(define tl-imgs       (make-images "tl"))
(define tr-imgs       (list
                        (flip-image-horizontally (copy-image (car tl-imgs)))
                        (make-image "tr-f.png")))
(define left-imgs     (crop-images bl-imgs 0 0 4 4))
(define right-imgs    (hflip-copy left-imgs))
(define bottom-imgs   (dflip-copy right-imgs))
(define gradient-imgs (list (scale-image (car left-imgs) 4 20)
                            (make-image "lborder-gradient-f.png")))

(define (menu-img w)
  (let ((icon (window-icon-image w)))
    (if icon (list icon) default-icon)) )

(define (max-restore-imgs w)
  (if (window-maximized-p w) restore-imgs max-imgs))


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; Define and install frames

(define normal-base `(
  ((class . top-border)
   (right-edge . 0)
   (left-edge . ,text-left-edge)
   (top-edge . -22)
   (height . 3)
   (background . ,top-imgs))

  ((class . top-border)
   (left-edge . 0)
   (width . 14)
   (top-edge . -22)
   (hidden . ,hide-menu-image)
   (background . ,top-imgs-left))

  ((class . top-left-corner)
   (left-edge . -4)
   (top-edge . -22)
   (background . ,tl-imgs))

  ((class . top-right-corner)
   (right-edge . -4)
   (top-edge . -22)
   (background . ,tr-imgs))

  ((class . left-border)
   (left-edge . -4)
   (top-edge . 20)
   (bottom-edge . 6)
   (background . ,left-imgs))

  ((class . right-border)
   (right-edge . -4)
   (top-edge . 0)
   (bottom-edge . 6)
   (background . ,right-imgs))

  ((class . bottom-border)
   (left-edge . 6)
   (right-edge . 6)
   (bottom-edge . -4)
   (background . ,bottom-imgs))

  ((class . bottom-left-corner)
   (left-edge . -4)
   (bottom-edge . -4)
   (background . ,bl-imgs))

  ((class . bottom-right-corner)
   (right-edge . -4)
   (bottom-edge . -4)
   (background . ,br-imgs))

  ((class . left-border)
   (left-edge . -4)
   (top-edge . 0)
   (height . 20)
   (background . ,gradient-imgs))

  ((class . title)
   (right-edge . 0)
   (width . 56)
   (top-edge . -20)
   (height . 20)
   (cursor . left_ptr)
   (background . ,rtitle-imgs))))

(define shaped-base `(
  ((cursor . left_ptr)
   (right-edge . -4)
   (width . 60)
   (top-edge . -22)
   (height . 22)
   (class . title)
   (background . ,rshaded-imgs))))

(define ntframe-buttons `(
  ((width . 16)
   (height . 16)
   (top-edge . -19)
   (cursor . left_ptr)
   (class . menu-button)
   (left-edge . 0)
   (scale-foreground . t)
   (hidden . ,hide-menu-image)
   (foreground . ,menu-img)
   (background . ,ltitle-colors))

  ((right-edge . 0)
   (cursor . left_ptr)
   (top-edge . -19)
   (removable . t)
   (background . ,close-imgs)
   (class . close-button))

  ((cursor . left_ptr)
   (right-edge . 20)
   (removable . t)
   (top-edge . -19)
   (class . maximize-button)
   (background . ,max-restore-imgs))

  ((cursor . left_ptr)
   (right-edge . 36)
   (width . 17)
   (removable . t)
   (top-edge . -19)
   (class . iconify-button)
   (background . ,iconify-imgs))))

(define tframe-buttons `(
  ((right-edge . 0)
   (cursor . left_ptr)
   (top-edge . -19)
   (removable . t)
   (background . ,close-imgs)
   (class . close-button))

  ((cursor . left_ptr)
   (right-edge . 20)
   (removable . t)
   (top-edge . -19)
   (hidden . ,(lambda (w) (not Blue:transients-can-max)))
   (class . maximize-button)
   (background . ,max-restore-imgs))

  ((cursor . left_ptr)
   (right-edge . 36)
   (width . 17)
   (removable . t)
   (top-edge . -19)
   (hidden . ,(lambda (w) (not Blue:transients-can-iconify)))
   (class . iconify-button)
   (background . ,iconify-imgs))))

(define frame (append normal-base `(
  ((right-edge . 56)
   (top-edge . -20)
   (height . 20)
   (cursor . left_ptr)
   (foreground . ,font-colors)
   (left-edge . ,text-left-edge)
   (y-justify . ,(lambda (w) Blue:title-text-offset))
   (class . title)
   (text . ,window-name)
   (background . ,title-imgs)
   (x-justify . 8))

  ((left-edge . 0)
   (width . 14)
   (top-edge . -20)
   (height . 20)
   (cursor . left_ptr)
   (class . title)
   (hidden . ,hide-menu-image)
   (background . ,ltitle-imgs))

  ((class . bottom-right-corner)
   (right-edge . 0)
   (bottom-edge . 0)
   (hidden . ,(lambda (w) (not Blue:show-resize-triangle)))
   (background . ,resize-img))
 ) ntframe-buttons))

(define transient-frame (append normal-base `(
  ((right-edge . 56)
   (top-edge . -20)
   (height . 20)
   (cursor . left_ptr)
   (foreground . ,font-colors)
   (left-edge . 0)
   (y-justify . ,(lambda (w) Blue:title-text-offset))
   (class . title)
   (text . ,window-name)
   (background . ,title-imgs)
   (x-justify . 8))
 ) tframe-buttons))

(define shaped-frame (append shaped-base `(
  ((height . 22)
   (cursor . left_ptr)
   (top-edge . -22)
   (right-edge . 56)
   (background . ,shaded-imgs)
   (class . title)
   (text . ,window-name)
   (x-justify . 8)
   (y-justify . ,(lambda (w) (+ 2 Blue:title-text-offset)))
   (left-edge . ,text-left-edge)
   (foreground . ,font-colors))

  ((cursor . left_ptr)
   (left-edge . -4)
   (top-edge . -22)
   (class . title)
   (width . ,(lambda (w) (if (hide-menu-image w) 4 18)))
   (background . ,lshaded-imgs))
 ) ntframe-buttons))

(define shaped-transient-frame (append shaped-base `(
  ((height . 22)
   (cursor . left_ptr)
   (top-edge . -22)
   (right-edge . 56)
   (background . ,shaded-imgs)
   (class . title)
   (text . ,window-name)
   (x-justify . 8)
   (y-justify . ,(lambda (w) (+ 2 Blue:title-text-offset)))
   (left-edge . 0)
   (foreground . ,font-colors))

  ((cursor . left_ptr)
   (left-edge . -4)
   (top-edge . -22)
   (class . title)
   (width . 4)
   (background . ,lshaded-imgs))
 ) tframe-buttons))

(add-frame-style 'Blue (lambda (w type) (case type
  ((shaped)           shaped-frame)
  ((shaded)           shaped-frame)
  ((transient)        transient-frame)
  ((shaped-transient) shaped-transient-frame)
  ((shaded-transient) shaped-transient-frame)
  ((unframed)         nil-frame)
  (t                  frame) )))
