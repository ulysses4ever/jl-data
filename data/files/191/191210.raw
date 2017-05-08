;;; other-setting.jl begin here

(defun shove-window (dir &optional no-focus)
  "Move focused window 'left, 'right, 'up or 'down to screen edges."
  (interactive)
  (let* ((win (input-focus))
         (pos (window-position win))
         (dim (window-frame-dimensions win))
         (endx (car pos))
         (endy (cdr pos)))
    (cond ((eq dir 'left) (setq endx 0))
          ((eq dir 'right) (setq endx (- (screen-width) (car dim))))
          ((eq dir 'up) (setq endy 0))
          ((eq dir 'down) (setq endy (- (screen-height) (cdr dim)))))
    (move-window-to win endx endy)
    (unless no-focus
      (display-window win))))

(defun warp-to-center (x y)
  (interactive)
  (let* ((win (input-focus))
         (xpix (floor (inexact->exact (* x (car (window-dimensions win))))))
         (ypix (floor (inexact->exact (* y (cdr (window-dimensions win)))))))
    (warp-cursor-to-window win xpix ypix)))

;;capture screen
(defun capture-root-window ()  
  "capture root window"  
  (interactive)  
  (system "import -window root shot.png; display shot.png&"))  

(defun capture-this-window ()  
  "capture active window"  
  (interactive)  
  (let ((w (current-event-window)))  
    (when w  
      (display-message (concat "import -window "  
                        (prin1-to-string (window-id w)) " window.png"))  
      (system (concat "import -window "  
                      (prin1-to-string (window-id w)) " window.png"))  
      (system "display window.png&"))))  

(defun capture-region ()  
  "capture region"  
  (interactive)  
  (let ((process (make-process standard-output)  
    (start-process process "import" "capture.png")))))  

;; define functions
(defun backgroundize (string)
  "Append a character '&' to STRING if it is not end with a '&'."
  (let ((len (length string)))
    (if (string= "&" (substring string (- len 1)))
        string
        (concat string " &"))))

(defun show-desktop-toggle ()
  "Show or hide the desktop."
  (if (showing-desktop-p)
      (hide-desktop)
      (show-desktop)))

;; display-message-with-timeout
(defun display-message-with-timeout (message timeout)
  (display-message message)
  (make-timer (lambda () (display-message nil)) timeout))

;; iconify-all-windows
(defun iconify-all-windows ()
  (map-windows iconify-window))

;; close-all-windows
(defun close-all-windows ()
  (map-windows delete-window))

(provide 'other-setting)
;;; other-setting.jl end here
