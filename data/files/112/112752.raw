;; file-browser-menu.jl -- a sawfish popup menu to allow users
;;                         manipulate files and directories.
;;
;; version 0.1  
;;
;; $Id: file-browser-menu.jl,v 1.2 2005/01/01 17:42:43 mario Exp $
;;
;; Copyright (C) 2004, 2005 Mario Domenech Goulart
;;
;; Author: Mario Domenech Goulart <mario@inf.ufrgs.br>
;;
;; This code is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published
;; by the Free Software Foundation; either version 1, or (at your
;; option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, write to the Free Software
;; Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
;;
;; Commentary:
;;
;; file-broser-menu.jl provides a menu to allow users manipulate files
;; and directories.  Actions for files can be configured through the
;; `fbm-file-actions' variable.  Actions for directories can be
;; configured through the `fbm-dir-actions' variable.  The menu which
;; lists files and directories uses the `ls' program to get file
;; names.  The options for `ls' can be configured through the
;; `fbm-ls-switches' variable.

(require 'menus)
(require 'rep.io.files)

(defvar fbm-ls-switches "-c1")

(defvar fbm-dir-actions
  '(("Go in"    fbm-popup-files-menu)
    ("Terminal here"   "(cd "  " ; xterm)")
    ("Mozilla"  "mozilla -remote \'openURL(" ",new-tab)\'")
))

(defvar fbm-file-actions
  '(("Emacsclient"  "emacsclient --no-wait")
    ("Ghostview"   "gv")
    ("Mozilla"  "mozilla -remote \'openURL(" ",new-tab)\'")
    ("Xpdf"  "xpdf ")
    ("Xdvi"  "xdvi ")
    ("Display"  "display -size 800x600")
    ("Mplayer"  "mplayer ")
    ("Mpg321"  "mpg321 ")
    ("Ogg123"  "ogg123 ")
))

(define (fbm-ls dir)
  (let* ((out (make-string-output-stream))
         (ls (make-process out)))
    (call-process ls nil "/bin/ls" fbm-ls-switches dir)
    (let ((files (get-output-stream-string out)))
      (string-split "\n" files))))

(define (fbm-fix-path path)
  "Fix PATH to be displayed correctly in the menu."
  (string-replace "_" "__" path))

(define (fbm-describe-files dir)
  (append 
   (list 
    (cons (concat "Listing from " dir) dir)
    (cons () ())
    (cons "Up"  (directory-file-name (file-name-directory dir))))
   (mapcar 
    (lambda (f)
      (let ((file (file-name-nondirectory (concat dir "/" f)))
	    (full-filename (concat dir "/" f)))
	(cond ((file-directory-p full-filename)
	       (cons (concat "[d] " (fbm-fix-path file)) full-filename))
	      ((file-symlink-p file)
	       (cons (concat "[l] " (fbm-fix-path file)) full-filename))
	      (t (cons (concat "[f] " (fbm-fix-path file)) full-filename)))))
    (let ((files (fbm-ls dir)))
      (delete (last files) files)))))

(define (fbm-popup-files-menu &optional dir)
  (interactive)
  (popup-menu
   (mapcar
    (lambda (entry)
      (let ((entry-text (car entry))
	    (full-path (cdr entry)))
	(if entry-text
	    (list entry-text 
		  `(fbm-popup-action-menu ,full-path))
	  '())))
    (if dir
	(fbm-describe-files dir) 
      (fbm-describe-files (getenv "HOME"))))))

(define (fbm-popup-action-menu path)
  (popup-menu
   (append 
    (list 
     (cons (concat "Action for " (fbm-fix-path path)) path)
     ())
    (mapcar 
     (lambda (item)
       (let ((title (nth 0 item))
	     (command (nth 1 item))
	     (postargs (nth 2 item)))
	 (list 
	  title
	  (if (stringp command)
	      `(system ,(concat command " "  path " " postargs " &"))
	    `(,(symbol-value command) ,path)))))
     (if (file-directory-p path)
	 fbm-dir-actions
       fbm-file-actions)))))

(provide 'file-browser-menu)