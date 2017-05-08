;;; title-offset.jl -- Interactively move tab-styled title bars.
;;  Jason Peters <jasonpeters@email.com>

;;  Version 0.2 - semantics have changed:
;;                uses relative percentage-style offset instead of 
;;                absolute positioning.  themes must be changed
;;
;;  Older Versions:
;;  Version 0.1 - initial release
;;
;;  This code has been mostly culled from Sawfish's move-resize.jl

;; title-offset.jl is free software distributed under the terms of the GNU
;; General Public Licence, version 2. For details see the file COPYING.

;;; Commentary:

;; The following code provides a mechanism for adjusting the position of 
;; tab-styled title bars.  This is accomplished by adding a `title-offset' 
;; property to the window's property list.  A theme can then check for this 
;; symbol when drawing its frame, and adjust its display accordingly.
;;
;; To use this module, stick it in your load-path and add the following
;; line in your ~/.sawfishrc file:
;;
;; (require 'title-offset)
;;
;; For this module to be of any use, you also need a theme that understands 
;; the 'title-offset property.  One such theme is DragDome, a modified  
;; version of the TigDome theme that I have put together.  Get it at 
;; <http://www.eng.uwaterloo.ca/students/jdpeters/DragDome.tar.gz>, and
;; check out theme.jl to see how to modify other themes. 
;;
;; Then bind change-title-offset-interactively to a title-bar mouse action.  
;; (I'm currently using Button2-Move.)  You should then be able to 
;; interactively adjust the position of your title bars.

;;; Code:

(require 'move-resize)  ;; for the move cursor
(provide 'title-offset)

(defvar change-title-offset-map (bind-keys (make-keymap)
	"Any-Off"  'change-title-offset-finished
	"Any-Move" 'change-title-offset-motion
	"Any-ESC"  'change-title-offset-cancel
	"Any-RET"  'change-title-offset-finished))

(defvar title-offset-old nil)
(defvar title-offset-old-position nil)
(defvar title-offset-old-ptr-x nil)
(defvar title-offset-ptr nil)
(defvar title-offset-window nil)
(defvar title-offset-window-position nil)
(defvar title-offset-window-width nil)

(defun change-title-offset-interactively (w)
  "Interactively adjust the position of tab-styled window title bars."
  (interactive "%W")
  (let*
      ((from-motion-event (and (current-event) (string-match "-Move$" (event-name (current-event)))))
	   (override-keymap change-title-offset-map)
	   (unbound-key-hook nil)
       (disable-auto-raise t)
       (title-offset-window w)
	   (title-offset-window-width (car (window-frame-dimensions w)))
	   (title-offset-window-position (+ (car (window-position w) 
	                                    (car (window-frame-offset w)))))
	   (title-offset-last-ptr (if from-motion-event (query-button-press-pointer) (query-pointer t)))
       (title-offset-old-ptr-x (car title-offset-last-ptr))
	   (title-offset-old (or (window-get w 'title-offset) 0.0))
	   (title-offset-old-position (* title-offset-old title-offset-window-width))
	   (title-offset-ptr (/ (- title-offset-old-ptr-x title-offset-window-position 
	                        title-offset-old-position) title-offset-window-width)))
    (raise-window title-offset-window)
    (unwind-protect
	(progn
	  (allow-events 'async-pointer)
	  (when (grab-pointer nil move-cursor-shape)
	    (unwind-protect
		(progn
		  (grab-keyboard title-offset-window)	;this may fail
		  (catch 'change-title-offset-done
		    (when from-motion-event (change-title-offset-motion))
		    (recursive-edit)))
	      (ungrab-keyboard)
	      (ungrab-pointer)))))))

;; called each pointer motion event
(defun change-title-offset-motion ()
  (interactive)
  (let*
    ((this-ptr (query-pointer))
	 (ptr-x (car this-ptr))
	 (frame-width title-offset-window-width)
	 (position-change (- ptr-x title-offset-old-ptr-x))
	 (change-direction (if (eq position-change 0) 1 (/ position-change (abs position-change))))
	 (position-change-adjusted (* position-change 
	                             (+ 1 (* change-direction title-offset-ptr)))))
	(setq offset 
	  (min 1.0
	  (max 0.0 (/ (+ title-offset-old-position position-change-adjusted) frame-width))))
	(window-put title-offset-window 'title-offset offset)
	(rebuild-frame title-offset-window)
   ; (setq offset-last-ptr this-ptr)
   ))

;; called when finished (i.e. button-release event)
(defun change-title-offset-finished ()
  (interactive)
  (throw 'change-title-offset-done t))

(defun change-title-offset-cancel ()
  (interactive)
  (window-put title-offset-window 'title-offset title-offset-old)
  (rebuild-frame title-offset-window)
  (throw 'change-title-offset-done nil))

;; vim:filetype=lisp
