;;; common-setting.jl begin here

;; Load Modules
(require 'sawfish-defaults)
(require 'sawfish.wm.viewport)
(require 'sawfish.wm.menus)
(require 'iswitch-window)
(require 'jump-or-exec)
(require 'run-application)
(require 'string2)
(require 'sawfish.wm.focus)
(require 'sawfish.wm.ext.match-window)

(setq capture-menu  
      '(("Current Window"  (capture-this-window))  
        ("Region"          (capture-region))  
        ("Full Screen"     (capture-root-window))))

;;font set
(setq default-font (get-font "-*-Microsoft YaHei Mono-medium-r-*-*-14-*-*-*-*-*-*-*"))

;;set frame default style
;(custom-set-typed-variable (quote Crux:normal-color) (quote "#ca0064003b00") (quote (optional color)))
;(custom-set-typed-variable (quote default-frame-style) (quote Crux) (quote frame-style))
(custom-set-typed-variable (quote default-frame-style) (quote pager) (quote frame-style))

;;wm modifier value
(custom-set-typed-variable (quote wm-modifier-value) (quote (super)) (quote modifier-list))

;;set start program
(define startup-programs
  '(
    ;("gnome-panel")
    ;("bluetooth-applet")
    ;("nm-applet")
    ("xscreensaver" "-no-splash")
    ("/usr/lib/vino/vino-server" "--sm-disable")             ;;for remote desktop
    ("gnome-settings-daemon")                                ;;for ubuntu 11.04 use gtk
    ("gnome-keyring-daemon" "--start" "--components=pkcs11") ;;/etc/xdg/autostart/gnome-keyring-pkcs11.desktop
    ("ibus-daemon" "--xim")                                  ;;input method
    ("numlockx" "on")
    ))

;;wallpaper setting
(setq list-wallpaper '("black.png" "ubuntu-12-04.png" "grass.jpg"))
(setq startup-programs
      (cons (list "feh" "--bg-fill" (concat zzsawfish-path "wallpaper/" (nth 2 list-wallpaper))) startup-programs))

(add-hook 'before-exit-hook  
          (lambda ()  
            (mapc stop-process (active-processes))))

(mapc (lambda (program)  
        (apply start-process (make-process standard-output) program))  
      startup-programs) 

(add-hook 'before-exit-hook  
          (lambda ()  
            (mapc stop-process (active-processes))))

(setq apps-menu-autogen   nil)
(setq workspace-names     '("work")) 
(setq decorate-transients t)
(setq place-window-mode   'first-fit)

(setq root-menu
      '(("Windows"    . window-menu)
        ("Workspaces" . workspace-menu)
        ("Programs"   . apps-menu)
        ("Customize"  . custom-menu)
        ("About..."   (customize 'about))
        ()
        ("Restart"    restart)
        ("Quit"       quit)))

(setq apps-menu  
      '(("Terminal"   (system "gnome-terminal &"))  
        ("Emacs"      (system "emacs &"))  
        ("Firefox"    (system "firefox &"))  
        ("Bcompare"   (system "bcompare &"))
        ("Nautilus"   (system "nautilus --no-desktop ~ &"))
        ("Evince"     (system "evince &"))
        ("Monitor"    (system "gnome-system-monitor &"))
        ("Gcolor2"    (system "gcolor2 &"))  
        ("Gcalctool"  (system "gcalctool &"))
        ("Capture"    (popup-menu capture-menu))  
        ()
        ("Run"        (system "gmrun &"))
        ("Lock"       (system "xscreensaver-command -lock &"))
        ))


(provide 'common-setting)
;;; common-setting.jl end here
