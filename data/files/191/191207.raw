;;; key-setting.jl begin here

;; Rootwindow Keybindings
(bind-keys root-window-keymap
           "Button3-Click" 'mouse-popup-root-menu
           "Button2-Click" 'mouse-popup-root-menu)

(bind-keys global-keymap "W-c" '(warp-to-center 0.5 0.5))

(setq warp-to-window-enabled t)
(bind-keys global-keymap "C-W-Left"  '(shove-window 'left))
(bind-keys global-keymap "C-W-Right" '(shove-window 'right))
(bind-keys global-keymap "C-W-Up"    '(shove-window 'up))
(bind-keys global-keymap "C-W-Down"  '(shove-window 'down))

(bind-keys global-keymap
           "W-TAB"   'cycle-windows
           "W-`"     'iswitch-window

           ;;window 
           "W-F2"    '(system "gmrun &")
           "W-F3"    '(show-desktop-toggle)
           "W-F4"    '(delete-window (current-event-window))

           "W-F9"    '(system (program-term "sawfish-client"))
           "W-F10"   'open/close-gnome-panel
           "W-F11"   'lock/unlock-mouse-click
           "W-F12"   '(popup-menu system-menu)

           "W-Print" 'capture-root-window
           "M-Print" 'capture-this-window
           "C-Print" 'capture-region

           "W-Menu"  'popup-window-menu
           "C-Menu"  'popup-root-menu
           "M-Menu"  'popup-apps-menu
           
           "W-Home"  '(jump-or-exec "Nautilus" "nautilus --no-desktop ~" t)
           "W-l"     '(system "xscreensaver-command -lock &")
           "W-x"     '(system (program-term "xkill")))

;;for run special program
(define exec-keymap (make-keymap))
(bind-keys global-keymap "W-e" exec-keymap)
(bind-keys exec-keymap
           "e"       'jump-or-exec-emacs
           "t"       '(system "gnome-terminal &")
           "n"       '(system "nautilus --no-desktop ~ &")
           "f"       '(jump-or-exec "Firefox" "firefox" #:match-class t)
           "b"       '(jump-or-exec "Beyond Compare" "bcompare")
           "C-b"     '(system "bcompare &")
           "g"       '(jump-or-exec "Geany" "geany" t)
           "G"       '(jump-or-exec "GPRename" "gprename" nil)
           "r"       '(jump-or-exec "Remmina" "remmina")
           "m"       '(system "gnome-system-monitor &")
           "s"       '(system "gnome-control-center &")
           "C-e"     '(system "evince &")

           "F2"      '(system "gksu &")
           "C-F2"    'run-application
           "F9"      '(jump-or-exec "Synaptic" "gksu -u root synaptic" nil)
           "F10"     '(jump-or-exec "Gtkorphan" "gksu -u root gtkorphan" t)
           "F11"     '(system "gksu -u root /etc/init.d/network-manager restart &")
           "F12"     '(system "gksu -u root /etc/init.d/privoxy restart &"))

;;for menus control
(define menus-keymap (make-keymap))
(bind-keys global-keymap "W-m" menus-keymap)
(bind-keys menus-keymap
           "1"       'popup-root-menu
           "2"       'popup-window-menu
           "3"       'popup-apps-menu)

;; Workspace Keymacros
(define ws-keymap (make-keymap))
(bind-keys global-keymap "W-w" ws-keymap)
(bind-keys ws-keymap
           "Left"    'workspace-left
           "Up"      'workspace-up
           "Right"   'workspace-right
           "Down"    'workspace-down)

;; Viewport keymacros
(define vp-keymap (make-keymap))
(bind-keys global-keymap "W-v" vp-keymap)
(bind-keys vp-keymap
           "Left"    '(move-viewport -1  0)
           "Up"      '(move-viewport  0 -1)
           "Right"   '(move-viewport  1  0)
           "Down"    '(move-viewport  0  1))

(bind-keys window-keymap
           "W--"         'iconify-window
           "W-="         'maximize-window-toggle
           "W-BackSpace" 'toggle-window-shaded

           "W-_"         'move-window-interactively
           "W-+"         'resize-window-interactively

           "W-]"         'raise-window
           "W-["         'lower-window
           "W-}"         'raise-window-depth
           "W-{"         'lower-window-depth
           
           "W-|"         'maximize-window-vertically-toggle
           "W-\\"        'maximize-window-horizontally-toggle

           "W-Return"    'maximize-window-fullscreen-toggle

           "W-Left"      'focus-west
           "W-Right"     'focus-east
           "W-Up"        'focus-north
           "W-Down"      'focus-south
           )

(define help-keymap (make-keymap))
(bind-keys global-keymap "W-h" help-keymap)


(provide 'key-setting)
;;; key-setting.jl end here
