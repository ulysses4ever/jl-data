
(defun evm-tile-windows-horizontally ()
  "Tile windows horizontally"
  (let ((wins (workspace-windows current-workspace))
		(calculated-width 0)
		(x 0)
		(border-width 0)
		(borders-width 0))
	;; Calculate width of the window border
	(setq border-width (- (car (window-frame-dimensions (car wins))) 
						  (car (window-dimensions (car wins)))))
	;; Calculate width of borders of all windows on current viewport
	(setq borders-width 
		  (* (length wins) border-width))
	(setq calculated-width 
		  (ceiling (/ (- (screen-width) borders-width) 
					  (length wins))))
	(while wins
	  (resize-window-to (car wins) calculated-width (- (screen-height) 54))
	  (move-window-to (car wins) x 0)
	  (setq x (+ x calculated-width border-width))
	  (setq wins (cdr wins))
	  )
	)
  )

(defun evm-tile-windows-vertically ()
  "Tile windows vertically"
  (let ((wins (workspace-windows current-workspace))
		(calculated-height 0)
		(y 0)
		(border-height 0)
		(borders-heights 0))
	;; Calculate height of the window border
	(setq border-height (- (cdr (window-frame-dimensions (car wins))) 
						   (cdr (window-dimensions (car wins)))))
	;; Calculate height of borders of all windows on current viewport
	(setq borders-height 
		  (* (length wins) border-height))
	(setq calculated-height 
		  (ceiling (/ (- (screen-height) borders-height 28) 
					  (length wins))))
	(while wins
	  (resize-window-to (car wins) (- (screen-width) 18) calculated-height)
	  (move-window-to (car wins) 0 y)
	  (setq y (+ y calculated-height border-height))
	  (setq wins (cdr wins))
	  )
	)
  )

