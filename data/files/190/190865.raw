;; jumper.jl -- Tag and jump between windows.
;;
;; Copyright (C) 2008  Frederic Jolliton <frederic@jolliton.com>
;;
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2 of the License, or
;; (at your option) any later version.
;;
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; History
;; -------
;;
;; Version 0.3 [2008-09-22]
;;
;;   * define the commands as interactive to make them available in
;;     the bindings menu.
;;
;;   * conditionnaly configure default key bindings (previously they
;;     were always defined)
;;
;;   * beep if trying to jump to an unknown mark
;;
;; Version 0.2 [2008-09-21]
;;
;;   * ensure that multiple windows are not sharing the same ID
;;
;; Version 0.1 [2008-09-21]
;;
;;   * initial release
;;
;; Installation
;; ------------
;;
;; The latest version can be found at http://sawfish.wikia.com/wiki/Jumper
;;
;; Copy this file to ~/.sawfish/lisp/ as jumper.jl, then add the
;; following line to your ~/.sawfishrc:
;;
;;  (load "jumper")
;;
;; You can choose to configure Jumper entirely from the bindings menu,
;; in which case you might prefer to disable default key bindings by
;; setting jumper-bind-keys to nil.
;;
;; If your keyboard contains unused extra keys, you could also list
;; them in the jumper-keys variable (like '("F15" "F16" "F17") for
;; example) and set jumper-jump-modifier to nil (this way you can use
;; these keys without modifiers) and set jumper-mark-modifier to "S"
;; to use shift and the corresponding key to mark a window. My
;; Microsoft keyboard contains "Favorites" keys numbered from 1 to 5
;; which are perfect for this task.
;;
;; The default keybindings defines H-n to jump to the mark 'n' and
;; H-A-n to define the corresponding mark (where A = alt, H = hyper),
;; assuming you've a Hyper key configured. If not, you MUST update the
;; default configuration variables.
;;

(defvar jumper-version "0.3")

(defvar jumper-bind-keys t
  "If true, then the script will configure a default set of key
   bindings when loaded")

(defvar jumper-jump-modifier "W"
  "The modifier(s) to jump to a marked window")

(defvar jumper-mark-modifier "C-W"
  "The modifier(s) to mark a window")

(defvar jumper-keys '(?0 ?1 ?2 ?3 ?4 ?5 ?6 ?7 ?8 ?9)
  "The list of keys to bind (accordingly to modifiers specified with
   jumper-jump-modifier and jumper-mark-modifier)")

(defun jumper-find-window (id)
  (car (filter (lambda (window) 
                 (= id (window-get window 'jumper-id)))
               (managed-windows))))

(defun jumper-jump (id)
  "Set a mark to the currently focused window."
  (let ((target-window (jumper-find-window id)))
    (if target-window
        (display-window target-window)
        (beep))))

(defun jumper-clear-mark (id)
  (let ((window (jumper-find-window id)))
    (when window
      (window-put window 'jumper-id nil))))

(defun jumper-mark (id)
  "Jump to a previously marked window."
  (jumper-clear-mark id)
  (let ((current-window (input-focus)))
    (if current-window
        (window-put current-window 'jumper-id id)
        (beep))))

(define-command 'jump-to jumper-jump
  #:spec "NID:"
  #:type `(and (labelled ,(_ "ID:") (number 0))))

(define-command 'jump-set jumper-mark
  #:spec "NID:"
  #:type `(and (labelled ,(_ "ID:") (number 0))))

(when jumper-bind-keys
  ;; Defines all bindings
  (let ((jumper-concat-key (lambda (modifier id)
                             (if modifier
                                 (concat modifier "-" id)
                                 (concat id))))
        (id 0))
    (mapc (lambda (c)
            (bind-keys global-keymap (jumper-concat-key jumper-jump-modifier c) (list 'jumper-jump id))
            (bind-keys global-keymap (jumper-concat-key jumper-mark-modifier c) (list 'jumper-mark id))
            (setq id (1+ id)))
          jumper-keys)))

(provide 'jumper)
