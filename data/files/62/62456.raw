;; theme file, written Tue Jan 23 23:18:45 2001
;; created by sawfish-themer -- DO NOT EDIT!

(require 'make-theme)

(let
    ((patterns-alist
      '(("top"
         (inactive
          "top.png")
         (focused
          "top-highlighted.png"))
        ("top-left"
         (inactive
          "top-left.png")
         (focused
          "top-left-highlighted.png"))
        ("top-right"
         (inactive
          "top-right.png")
         (focused
          "top-right-highlighted.png"))
        ("top-edge"
         (inactive
          "top-edge.png")
         (focused
          "top-edge-highlighted.png"))
        ("left-top"
         (inactive
          "left-top.png")
         (focused
          "left-top-highlighted.png"))
        ("left"
         (inactive
          "left.png")
         (focused
          "left-highlighted.png"))
        ("right"
         (inactive
          "right.png")
         (focused
          "right-highlighted.png"))
        ("right-top"
         (inactive
          "right-top.png")
         (focused
          "right-top-highlighted.png"))
        ("right-towards-top"
         (inactive
          "right-towards-top.png")
         (focused
          "right-towards-top-highlighted.png"))
        ("right-bottom"
         (inactive
          "right-bottom.png")
         (focused
          "right-bottom-highlighted.png"))
        ("left-bottom"
         (inactive
          "left-bottom.png")
         (focused
          "left-bottom-highlighted.png"))
        ("bottom-left"
         (inactive
          "bottom-left.png")
         (focused
          "bottom-left-highlighted.png"))
        ("bottom"
         (inactive
          "bottom.png")
         (focused
          "bottom-highlighted.png"))
        ("bottom-right"
         (inactive
          "bottom-right.png")
         (focused
          "bottom-right-highlighted.png"))
        ("close-button"
         (inactive
          "close-button.png")
         (focused
          "close-button-highlighted.png"))
        ("clear"
         (inactive
          "clear.png"))
        ("minimize-button"
         (inactive
          "minimize-button.png")
         (focused
          "minimize-button-highlighted.png"))
        ("maximize-button"
         (inactive
          "maximize-button.png")
         (focused
          "maximize-button-highlighted.png"))
        ("left-top-shaded"
         (inactive
          "left-top-shaded.png")
         (focused
          "left-top-shaded-highlighted.png"))
        ("right-top-shaded"
         (inactive
          "right-top-shaded.png")
         (focused
          "right-top-shaded-highlighted.png"))))

     (frames-alist
      '(("normal"
         ((top-edge . -16)
          (class . title)
          (left-edge . 0)
          (right-edge . 0)
          (x-justify . 18)
          (text . window-name)
          (background . "top"))
         ((top-edge . -18)
          (left-edge . -5)
          (background . "top-left")
          (class . top-left-corner))
         ((right-edge . -5)
          (top-edge . -18)
          (background . "top-right")
          (class . top-right-corner))
         ((top-edge . -18)
          (right-edge . 11)
          (left-edge . 11)
          (foreground . "top-edge")
          (background . "top-edge")
          (class . top-border))
         ((top-edge . -14)
          (left-edge . -5)
          (background . "left-top")
          (class . top-left-corner))
         ((bottom-edge . 11)
          (top-edge . 0)
          (left-edge . -5)
          (background . "left")
          (class . left-border))
         ((bottom-edge . 11)
          (top-edge . 32)
          (right-edge . -5)
          (background . "right")
          (class . right-border))
         ((top-edge . -14)
          (right-edge . -5)
          (background . "right-top")
          (class . top-right-corner))
         ((right-edge . -5)
          (background . "right-towards-top")
          (class . right-border))
         ((bottom-edge . -5)
          (right-edge . -5)
          (background . "right-bottom")
          (class . bottom-right-corner))
         ((bottom-edge . -5)
          (left-edge . -5)
          (background . "left-bottom")
          (class . bottom-left-corner))
         ((bottom-edge . -5)
          (left-edge . 0)
          (background . "bottom-left")
          (class . bottom-left-corner))
         ((left-edge . 11)
          (right-edge . 11)
          (background . "bottom")
          (bottom-edge . -5)
          (class . bottom-border))
         ((right-edge . 0)
          (bottom-edge . -5)
          (background . "bottom-right")
          (class . bottom-right-corner))
         ((cursor . diamond_cross)
          (left-edge . 2)
          (background . "close-button")
          (top-edge . -14)
          (class . close-button))
         ((cursor . based_arrow_down)
          (right-edge . 15)
          (top-edge . -14)
          (background . "minimize-button")
          (class . iconify-button))
         ((top-edge . -14)
          (cursor . based_arrow_up)
          (right-edge . 2)
          (background . "maximize-button")
          (class . maximize-button)))
        ("shaded"
         ((right-edge . 0)
          (top-edge . -16)
          (left-edge . 0)
          (class . title)
          (x-justify . 18)
          (text . window-name)
          (background . "top"))
         ((left-edge . -5)
          (top-edge . -18)
          (background . "top-left")
          (class . title))
         ((right-edge . -5)
          (top-edge . -18)
          (background . "top-right")
          (class . title))
         ((right-edge . 11)
          (left-edge . 11)
          (top-edge . -18)
          (foreground . "top-edge")
          (background . "top-edge")
          (class . title))
         ((top-edge . -14)
          (left-edge . -5)
          (class . title)
          (background . "left-top-shaded"))
         ((right-edge . -5)
          (class . title)
          (top-edge . -14)
          (background . "right-top-shaded"))
         ((left-edge . 2)
          (cursor . diamond_cross)
          (background . "close-button")
          (top-edge . -14)
          (class . close-button)))))

     (mapping-alist
      '((default . "normal")
        (transient . "normal")
        (shaped . "shaded")
        (shaped-transient . "shaded")))

     (theme-name 'Sleek))

  (add-frame-style
   theme-name (make-theme patterns-alist frames-alist mapping-alist))
  (when (boundp 'mark-frame-style-editable)
    (mark-frame-style-editable theme-name)))
