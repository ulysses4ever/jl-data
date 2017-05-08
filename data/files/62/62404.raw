;; smart-tile.jl --- Tile Sawfish windows in an intelligent (hah!) fashion
;;
;; Description: Handles tiling of all windows on the current workspace.
;; Windows are automatically sized and arranged to make best use of the
;; workspace without overlapping.
;;
;; Author: Mark Triggs <mst@dishevelled.net>
;;
;; Usage:
;;   (require 'smart-tile)
;;   (bind-keys global-keymap "M-t" 'tile-windows)
;;


;; For windows at least, wideness is preferable to tallness. So, the minimum
;; height specifies how short you are willing to tolerate your windows before
;; an extra column should be used.
(defvar min-height (/ (screen-height) 4))

(defun window-workspace (w)
  (car (window-get w 'workspaces)))

(defun find-if (fn l)
  (cond ((null l) nil)
        ((fn (car l)) (car l))
        (t (find-if fn (cdr l)))))

(defun window-on-current-workspace-p (w)
  (= (window-workspace w) current-workspace))

(defun window-touching-p (w)
  "Is W touching another window?"
  (find-if (lambda (other) (overlap-p w other))
           (remove w (remove-if window-ignored-p
                                (filter-windows
                                 window-on-current-workspace-p)))))

(defun window-x (w) (car (window-position w)))
(defun window-y (w) (cdr (window-position w)))
(defun window-width (w) (car (window-frame-dimensions w)))
(defun window-height (w) (cdr (window-frame-dimensions w)))

(defun overlap-p (w1 w2)
  "Do W1 and W2 overlap?"
  (and (< (abs (- (window-x w1) (window-x w2)))
          (window-width (if (< (window-x w1) (window-x w2))
                            w1 w2)))
       (< (abs (- (window-y w1) (window-y w2)))
          (window-height (if (< (window-y w1) (window-y w2))
                             w1 w2)))))

(defun resize-frame-to (w width height)
  (let ((width-offset (- (car (window-frame-dimensions w))
                         (car (window-dimensions w))))
        (height-offset (- (cdr (window-frame-dimensions w))
                          (cdr (window-dimensions w)))))
    (resize-window-to w (- width width-offset) (- height height-offset))))

(defmacro pop (l) `(setq ,l (cdr ,l)))

(defun tile-windows ()
  (interactive)
  (let ((windows (remove-if window-ignored-p
                            (filter-windows window-on-current-workspace-p))))
    (when (> (length windows) 1)
      (let* ((columns (do ((c 1 (1+ c)))
                          ((> (/ (screen-height) (/ (length windows) c))
                              min-height)
                           c)))
             (rows (ceiling (/ (length windows) columns)))
             (width (floor (/ (screen-width) columns)))
             (height (floor (/ (screen-height) rows))))
        (let ((w windows))
          (do ((x 0 (1+ x)))
              ((or (>= x columns) (null w)) nil)
            (do ((y 0 (1+ y)))
                ((or (>= y rows) (null w) nil))
              (resize-frame-to (car w) width height)
              (move-window-to (car w) (+ (* x width) 2) (* y height))
              (pop w))))
        ;; Resize the windows horizontally to use any remaining space.
        (mapc (lambda (w)
                (let ((old-width (window-width w))
                      (old-height (window-height w))
                      (new-width (- (screen-width) (window-x w))))
                  (resize-frame-to w new-width old-height)
                  (when (window-touching-p w)
                    ;; oops. Roll back to the original size
                    (resize-frame-to w old-width old-height))))
              windows)))))

(provide 'smart-tile)
