;; theme file, written Fri Mar 30 15:23:09 2001
;; created by sawfish-themer -- DO NOT EDIT!

(require 'make-theme)

(let
    ((patterns-alist
      '(("title"
         (inactive
          "pb9.png")
         (focused
          "pb9.png"))
        ("drag"
         (inactive
          "pb3.png")
         (focused
          "pb3.png")
         (highlighted
          "pb3.png")
         (inactive-highlighted
          "pb3.png")
         (clicked
          "pb31.png")
         (inactive-clicked
          "pb31.png"))
        ("top"
         (inactive
          "pb2.png")
         (focused
          "pb2.png")
         (highlighted
          "pb2.png")
         (inactive-highlighted
          "pb2.png"))
        ("bottom"
         (inactive
          "pb5.png")
         (focused
          "pb5.png")
         (highlighted
          "pb5.png")
         (inactive-highlighted
          "pb5.png"))
        ("right"
         (inactive
          "pb8.png")
         (focused
          "pb8.png")
         (highlighted
          "pb8.png")
         (inactive-highlighted
          "pb8.png"))
        ("bottoml"
         (inactive
          "pb6.png")
         (focused
          "pb6.png")
         (highlighted
          "pb6.png")
         (inactive-highlighted
          "pb6.png"))
        ("topright"
         (inactive
          "pb1.png")
         (focused
          "pb1.png")
         (highlighted
          "pb1.png")
         (inactive-highlighted
          "pb1.png"))
        ("left"
         (inactive
          "p8.png"))))

     (frames-alist
      '(("normal"
         ((top-edge . -2)
          (left-edge . 0)
          (right-edge . 0)
          (x-justify . center)
          (y-justify . center)
          (background . "top")
          (class . top-border))
         ((left-edge . 0)
          (right-edge . 0)
          (y-justify . center)
          (x-justify . center)
          (bottom-edge . -3)
          (background . "bottom")
          (class . bottom-border))
         ((bottom-edge . -2)
          (left-edge . -11)
          (top-edge . 19)
          (y-justify . center)
          (x-justify . center)
          (background . "title")
          (class . shade-button))
         ((left-edge . -11)
          (cursor . cross)
          (top-edge . -2)
          (y-justify . center)
          (x-justify . center)
          (background . "drag")
          (class . title))
         ((bottom-edge . 0)
          (top-edge . 0)
          (right-edge . -3)
          (y-justify . center)
          (x-justify . center)
          (background . "right")
          (class . right-border))
         ((right-edge . -3)
          (bottom-edge . -3)
          (background . "bottoml")
          (class . bottom-right-corner))
         ((right-edge . -3)
          (top-edge . -2)
          (background . "topright")
          (class . top-right-corner)))
        ("noborder"
         ((cursor . cross)
          (top-edge . -2)
          (right-edge . 0)
          (y-justify . center)
          (x-justify . center)
          (background . "drag")
          (class . title))
         ((top-edge . 19)
          (bottom-edge . -2)
          (right-edge . 0)
          (background . "title")
          (class . shade-button))
         ((top-edge . -2)
          (right-edge . -3)
          (bottom-edge . -2)
          (background . "right")
          (class . right-border)))
        ("left"
         ((class . title))
         ((class . bottom-border))
         ((class . top-border))
         ((width . 8)
          (height . 16)
          (left-edge . -12)
          (top-edge . 19)
          (background . "drag")
          (class . menu-button)))))

     (mapping-alist
      '((default . "normal")
        (shaped . "noborder")))

     (theme-name 'brushedpager))

  (add-frame-style
   theme-name (make-theme patterns-alist frames-alist mapping-alist))
  (when (boundp 'mark-frame-style-editable)
    (mark-frame-style-editable theme-name)))
