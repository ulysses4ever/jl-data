(defcustom scroll-viewport-steps 5
  "Number of steps in which to scroll between viewports (less steps = faster scrolling)."
  :group workspace
  :type number
  :range (1 . nil))

(defun scroll-viewport (x y)
  (let ((step-count scroll-viewport-steps)
	(xstep (quotient (- x viewport-x-offset) scroll-viewport-steps))
	(ystep (quotient (- y viewport-y-offset) scroll-viewport-steps)))
    (if (and (= xstep 0) (= ystep 0))
	(setq step-count 0))
    (while (> step-count 0)
      (orig-set-viewport (+ viewport-x-offset xstep) (+ viewport-y-offset ystep))
      (setq step-count (1- step-count)))
    (orig-set-viewport x y)))

(defvar orig-set-viewport set-viewport)
(setq set-viewport scroll-viewport)
