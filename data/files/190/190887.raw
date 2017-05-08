; auto-hide pager for sawfish by Jonas Berlin (xkr47 át outerspace.dyndns.org)
; License: GPLv2

; here you an adjust the auto-hide period - values 0 and 800 give 0.8 seconds
(setq pager-hide-seconds 0)
(setq pager-hide-milliseconds 800)

; variable used to store the pager window reference. leave this as is.
(setq pager-window '())

; timer object used to schedule the timeout when needed
(setq pager-hide-timer
      (make-timer
       (lambda (timer)
	 (when pager-window
	   (hide-window pager-window)) pager-hide-seconds pager-hide-milliseconds)))

; show the pager window and hide it after specified amount of milliseconds
(defun show-pager ()
  (when pager-window
    (show-window pager-window)
    (set-window-depth pager-window 10) ; make sure it's on top
    (set-timer pager-hide-timer pager-hide-seconds pager-hide-milliseconds)))

; force the pager window to hide. normally not called explicitly
(defun hide-pager ()
  (when pager-window
    (hide-window pager-window)))

; little helper function
(defun my-window-resourceclass (w)
  "Return the class that window W belongs to, as a string. Returns `nil' if W has no associated class."
  (let
      ((prop (get-x-text-property w 'WM_CLASS)))
    (if (arrayp prop) (aref prop 0))))

; This function gets called when new windows are shown, including when the pager window is first shown
(defun find-pager-window (win)
  (when (equal (my-window-resourceclass win) "pager")
    (window-put win 'ignored t) ; hide the pager window from the pager (this is <code>sawfish-pager</code>-specific I think)
    (setq pager-window win)))

; call the above function when new windows are shown
(add-hook ' add-window-hook (lambda (win) (find-pager-window win)) t)