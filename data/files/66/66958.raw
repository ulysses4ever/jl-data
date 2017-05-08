;; cycle-placement -- toggle a window's placement between multiple candidate 
;; positions.
;;
;; Copyright 2014 Cory Echols <cory@sixtimesnine.org>

(define-structure cycle-placement
	(export cycle-window-placement-on-current-head
			move-resize-frame-by-percent-on-current-head)

	(open rep
		rep.system
		sawfish.wm.state.maximize
		sawfish.wm.windows
		sawfish.wm.misc
	)

	;; Move and resize the frame to the supplied position and size
	(defun move-resize-frame-to (window x y width height)
		(move-window-to window x y)
		(resize-frame-to window width height)
	)

	;; Resize the window's frame to the provided width and height.
	(defun resize-frame-to (window width height)
		(let* ((dim-difference (window-frame-difference window))
			   (w-diff (car dim-difference))
			   (h-diff (cdr dim-difference))
			   (new-width (- width w-diff))
			   (new-height (- height h-diff)))
			(unmaximize-window window)
			(resize-window-to window new-width new-height))
	)

	;; Calculate how much frame decorations add to a window's size.
	(defun window-frame-difference (window)
		(let* ((win-dim (window-dimensions window))
			  (win-w (car win-dim))
			  (win-h (cdr win-dim))
			  (frame-dim (window-frame-dimensions window))
			  (frame-w (car frame-dim))
			  (frame-h (cdr frame-dim)))
			(cons (- frame-w win-w) (- frame-h win-h)))
	)

	;; Move and resize a frame, where supplied coordinates and size are
	;; a percentage of the current screen dimensions.
	(defun move-resize-frame-by-percent (window x y width height)
		(let* ((screen-x (car (screen-dimensions)))
			   (screen-y (cdr (screen-dimensions)))
			   (new-x (exact-percent x screen-x))
			   (new-y (exact-percent y screen-y))
			   (new-width (exact-percent width screen-x))
			   (new-height (exact-percent height screen-y)))
			(move-resize-frame-to window new-x new-y new-width new-height))
	)

	;; Move and resize a frame, where suppplied coordinates and size are a
	;; percentage of the current monitor dimensions
	(defun move-resize-frame-by-percent-on-current-head (window x y width height)
		(let* ((head-x (car (current-head-dimensions window)))
			   (head-y (cdr (current-head-dimensions window)))
			   (head-offset-x (car (current-head-offset window)))
			   (head-offset-y (cdr (current-head-offset window)))
			   (new-x (+ head-offset-x (exact-percent x head-x)))
			   (new-y (+ head-offset-y (exact-percent y head-y)))
			   (new-width (exact-percent width head-x))
			   (new-height (exact-percent height head-y)))
			(move-resize-frame-to window new-x new-y new-width new-height))
	)

	;; Return 'percent' of 'quantity' as an exact integer.
	;; librep has muliple numeric types, but it looks like sawfish wants 
	;; integers for everything.  There's probably a better way to do this.
	(defun exact-percent (percent quantity)
		(inexact->exact (exact->inexact (* ( / percent 100) quantity) ))
	)

	;; Cycle window through the list of candidate positions
	;; _window_ is a window, as would be returned by sawfish functions such as 
	;; `(input-focus)`.
    ;;
	;; _list-of-candidates_ is a list-of-lists.  Each of the contained lists is 
	;; a candidate position.  The candidate position describes where the window 
	;; should be placed as `(x-percent y-percent width-percent height-percent)`.  
	;; The first invocation of the function will place the window according to 
	;; the first entry in `list-of-candidates`.  Successive invocations will 
	;; select from the following entries in the list.
	(defun cycle-window-placement-on-current-head (window candidate-positions)
		(let* ((last-cycled-position (window-get window 'cte-last-cycled-pos 'none))
			   (last-cycled-member (member last-cycled-position candidate-positions))
			   (next-cycled-position (cond
										((< 1 (length last-cycled-member))
											(nth 1 last-cycled-member))
										(t
											(nth 0 candidate-positions)))))
			(window-put window 'cte-last-cycled-pos next-cycled-position)
			(move-resize-frame-by-percent-on-current-head
				window
				(nth 0 next-cycled-position)
				(nth 1 next-cycled-position)
				(nth 2 next-cycled-position)
				(nth 3 next-cycled-position)
			)
		)
	)
)
