;; theme file, written Mon Apr 23 17:48:19 2001
;; created by sawfish-themer -- DO NOT EDIT!

(require 'make-theme)

(let
    ((patterns-alist
      '(("menu"
         (inactive
          "button_inactive.png")
         (focused
          "menu.png")
         (highlighted
          "menu_active.png")
         (inactive-highlighted
          "menu_active.png")
         (clicked
          "menu_clicked.png")
         (inactive-clicked
          "button_inactive.png"))
        ("iconify"
         (inactive
          "button_inactive.png")
         (focused
          "iconify.png")
         (highlighted
          "iconify_active.png")
         (inactive-highlighted
          "button_inactive.png")
         (clicked
          "iconify_clicked.png")
         (inactive-clicked
          "button_inactive.png"))
        ("maximize"
         (inactive
          "button_inactive.png")
         (focused
          "maximize.png")
         (highlighted
          "maximize_active.png")
         (inactive-highlighted
          "button_inactive.png")
         (clicked
          "maximize_clicked.png")
         (inactive-clicked
          "button_inactive.png"))
        ("close"
         (inactive
          "button_inactive.png")
         (focused
          "close.png")
         (highlighted
          "close_active.png")
         (inactive-highlighted
          "button_inactive.png")
         (clicked
          "close_clicked.png")
         (inactive-clicked
          "button_inactive.png"))
        ("title"
         (inactive
          "title_inactive.png")
         (focused
          "title.png"))
        ("bottomleft"
         (inactive
          "bottom_left.png"))
        ("bottomright"
         (inactive
          "bottom_right.png"))
        ("bottom"
         (inactive
          "bottom.png"))
        ("left"
         (inactive
          "left.png"))
        ("right"
         (inactive
          "right.png"))
        ("topleft"
         (inactive
          "top_left.png"))
        ("topright"
         (inactive
          "top_right.png"))
        ("titleleft"
         (inactive
          "title_left_inactive.png")
         (focused
          "title_left.png"))
        ("titleright"
         (inactive
          "title_right_inactive.png")
         (focused
          "title_right.png"))
        ("titleback"
         (inactive
          "title_back.png"))
        ("topleftshaded"
         (inactive
          "top_left_shaded.png"))
        ("toprightshaded"
         (inactive
          "top_right_shaded.png"))))

     (frames-alist
      '(("shadebob"
         ((top-edge . -28)
          (right-edge . 0)
          (left-edge . 0)
          (background . "titleback")
          (class . title))
         ((top-edge . -23)
          (background . "menu")
          (class . menu-button))
         ((top-edge . -23)
          (right-edge . -1)
          (background . "close")
          (class . close-button))
         ((right-edge . 41)
          (top-edge . -23)
          (background . "iconify")
          (class . iconify-button))
         ((top-edge . -23)
          (right-edge . 20)
          (background . "maximize")
          (class . maximize-button))
         ((background . "topleftshaded")
          (top-edge . -28)
          (left-edge . -6)
          (class . top-left-corner))
         ((background . "toprightshaded")
          (top-edge . -28)
          (right-edge . -6)
          (class . top-right-corner))
         ((left-edge . 21)
          (top-edge . -28)
          (background . "titleleft")
          (class . title))
         ((right-edge . 62)
          (top-edge . -28)
          (background . "titleright")
          (class . title))
         ((y-justify . center)
          (x-justify . center)
          (font . "-b&h-lucida-medium-r-normal-*-*-100-*-*-p-*-iso8859-1")
          (right-edge . 67)
          (left-edge . 31)
          (top-edge . -28)
          (text . window-name)
          (background . "title")
          (class . title)))
        ("smooth"
         ((right-edge . 0)
          (left-edge . 0)
          (background . "titleback")
          (top-edge . -28)
          (class . title))
         ((top-edge . -23)
          (background . "menu")
          (class . menu-button))
         ((top-edge . -23)
          (right-edge . -1)
          (background . "close")
          (class . close-button))
         ((right-edge . 41)
          (top-edge . -23)
          (background . "iconify")
          (class . iconify-button))
         ((top-edge . -23)
          (right-edge . 20)
          (background . "maximize")
          (class . maximize-button))
         ((right-edge . 0)
          (left-edge . 0)
          (bottom-edge . -6)
          (background . "bottom")
          (class . bottom-border))
         ((background . "bottomleft")
          (bottom-edge . -6)
          (left-edge . -6)
          (class . bottom-left-corner))
         ((right-edge . -6)
          (bottom-edge . -6)
          (class . bottom-right-corner)
          (background . "bottomright"))
         ((class . left-border)
          (top-edge . 0)
          (background . "left")
          (left-edge . -6)
          (bottom-edge . 0))
         ((bottom-edge . 0)
          (top-edge . 0)
          (right-edge . -6)
          (background . "right")
          (class . right-border))
         ((top-edge . -28)
          (left-edge . -6)
          (background . "topleft")
          (class . top-left-corner))
         ((top-edge . -28)
          (right-edge . -6)
          (background . "topright")
          (class . top-right-corner))
         ((left-edge . 21)
          (top-edge . -28)
          (background . "titleleft")
          (class . title))
         ((right-edge . 62)
          (top-edge . -28)
          (background . "titleright")
          (class . title))
         ((left-edge . 31)
          (right-edge . 67)
          (font . "-b&h-lucida-medium-r-normal-*-*-100-*-*-p-*-iso8859-1")
          (top-edge . -28)
          (x-justify . center)
          (y-justify . center)
          (text . window-name)
          (background . "title")
          (class . title)))))

     (mapping-alist
      '((shaped . "shadebob")
        (default . "smooth")
        (transient . "smooth")
        (shaped-transient . "shadebob")))

     (theme-name 'smooth))

  (add-frame-style
   theme-name (make-theme patterns-alist frames-alist mapping-alist))
  (when (boundp 'mark-frame-style-editable)
    (mark-frame-style-editable theme-name)))
