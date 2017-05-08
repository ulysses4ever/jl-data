;;; key-setting.jl begin here

;; Rootwindow Keybindings
(bind-keys root-window-keymap
           "Button3-Click" 'popup-root-menu)

(bind-keys global-keymap "W-c" '(warp-to-center 0.5 0.5))

(setq warp-to-window-enabled t)
(bind-keys global-keymap "C-W-Left"  '(shove-window 'left))
(bind-keys global-keymap "C-W-Right" '(shove-window 'right))
(bind-keys global-keymap "C-W-Up"    '(shove-window 'up))
(bind-keys global-keymap "C-W-Down"  '(shove-window 'down))

(bind-keys global-keymap
           "W-TAB"   'cycle-windows
           "W-Right" 'next-workspace
           "W-Left"  'previous-workspace
           "W-Down"  'lower-window
           "W-Up"    'raise-window

           ;;window 
           "W-F1"    'popup-root-menu
           "W-F2"    '(system "gmrun &")
           "W-F3"    '(show-desktop-toggle)
           "W-F4"    '(delete-window (current-event-window))

           "W-F10"   '(maximize-window-toggle (current-event-window))

           "W-0"     'iswitch-window

           "W-Menu"  'popup-window-menu
           "C-Menu"  'popup-root-menu
           "S-Menu"  'popup-apps-menu
           
           "W-Home"  '(jump-or-exec "Nautilus" "nautilus --no-desktop ~" t)
           "W-l"     '(system "xscreensaver-command -lock &")
           "W-x"     '(system "xkill &"))

;;for run special program
(define exec-keymap (make-keymap))
(bind-keys global-keymap "W-e" exec-keymap)
(bind-keys exec-keymap
           "e"  'jump-or-exec-emacs
           "t"    '(system "gnome-terminal &")
           "n"    '(system "nautilus --no-desktop ~ &")
           "f"    '(jump-or-exec "Firefox" "firefox" #:match-class t)
           "b"    '(jump-or-exec "Beyond Compare" "bcompare")           
           "g"    '(jump-or-exec "Geany" "geany" t)
           "G"    '(jump-or-exec "GPRename" "gprename" nil)
           "r"    '(jump-or-exec "Remmina" "remmina")
           
           "F2"   '(system "gksu &")
           "C-F2" 'run-application
           "F9"   '(jump-or-exec "Synaptic" "gksu -u root synaptic" nil)
           "F10"  '(jump-or-exec "Gtkorphan" "gksu -u root gtkorphan" t)
           "F11"  '(system "gksu -u root /etc/init.d/network-manager restart &")
           "F12"  '(system "gksu -u root /etc/init.d/privoxy restart &"))

;;for menus control
(define menus-keymap (make-keymap))
(bind-keys global-keymap "W-m" menus-keymap)
(bind-keys menus-keymap
           "1"    'popup-root-menu
           "2"    'popup-window-menu
           "3"    'popup-apps-menu)

;; Workspace Keymacros
(define ws-keymap (make-keymap))
(bind-keys global-keymap "W-w" ws-keymap)
(bind-keys ws-keymap
           "Left"  'workspace-left
           "Up"    'workspace-up
           "Right" 'workspace-right
           "Down"  'workspace-down)

;; Viewport keymacros
(define vp-keymap (make-keymap))
(bind-keys global-keymap "W-v" vp-keymap)
(bind-keys vp-keymap
           "Left"  '(move-viewport -1  0)
           "Up"    '(move-viewport  0 -1)
           "Right" '(move-viewport  1  0)
           "Down"  '(move-viewport  0  1))

(bind-keys window-keymap
           "M-F10" 'maximize-window-fullscreen-toggle
           "W-F4"  'delete-window-safely
           "W-F5"  'destroy-window
           "C-W-m" 'maximize-window
           "C-W-w" 'unmaximize-window
           "C-W-s" 'shade-window
           "C-W-u" 'unshade-window
           "C-W-i" 'iconify-window
           "C-W-r" 'raise-window
           "C-W-l" 'lower-window
           "C-W-R" 'raise-window-depth
           "C-W-L" 'lower-window-depth
           "C-W-f" 'maximize-window-fullscreen
           "C-W-v" 'maximize-window-vertically
           "C-W-h" 'maximize-window-horizontally
           "C-W-y" 'move-window-interactively
           "C-W-x" 'resize-window-interactively
           )

(define help-keymap (make-keymap))
(bind-keys global-keymap "W-h" help-keymap)



(provide 'key-setting)
;;; key-setting.jl end here
