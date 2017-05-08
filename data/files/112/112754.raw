;; workspace-windows-menu.jl -- a menu which lists windows
;;                              per-workspace
;;
;; version 0.1
;;
;; $Id: workspace-windows-menu.jl,v 1.3 2005/01/01 17:40:05 mario Exp $
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
;; workspace-windows-menu.jl provides a menu which lists windows
;; per-workspace.  When a window is selected from the menu, it is
;; raised and gets focus.

(require 'menus)
 
(define (workspace-windows-menu)
  (mapcar 
   (lambda (window)
     (let ((win-name (window-name window))
	   (win-id (window-id window)))
       (list win-name
	     `(progn
		(raise-window (get-window-by-id ,win-id))
		(set-input-focus (get-window-by-id ,win-id))))))
   (workspace-windows)))

(define (workspace-windows-popup-menu)
  (interactive)
  (popup-menu workspace-windows-menu))
    
(provide 'workspace-window-menu)