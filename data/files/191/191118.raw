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
(require 'shutdown)
(require 'focus-by-direction)
(require 'jumper)

(setq capture-menu  
      '(("Current Window"  (capture-this-window))  
        ("Region"          (capture-region))  
        ("Full Screen"     (capture-root-window))))

;;font set
(setq default-font (get-font "-*-Microsoft YaHei Mono-medium-r-*-*-14-*-*-*-*-*-*-*"))

;;set frame default style
(custom-set-typed-variable (quote Crux:normal-color) (quote "#ca0064003b00") (quote (optional color)))
(custom-set-typed-variable (quote default-frame-style) (quote Crux) (quote frame-style))

;;wm modifier value
(custom-set-typed-variable (quote wm-modifier-value) (quote (super)) (quote modifier-list))

;;wallpaper setting
(setq list-wallpaper '("black.png" "sand.jpg"   "grass.jpg"  "grid.jpg"
                       "red.jpg"   "summer.jpg" "yellow.jpg" "moon.jpg"))

;;set start program
(define startup-programs
  (list
   ;'("gnome-panel")
   ;'("bluetooth-applet")
   ;'("nm-applet")
   ;'("xeyes")
   ;'("xclock")
   '("xscreensaver" "-no-splash")
   '("/usr/lib/vino/vino-server" "--sm-disable")             ;;for remote desktop
   
   '("gnome-settings-daemon")                                ;;for ubuntu 11.04 use gtk
   '("gnome-power-manager")
   
   '("gnome-keyring-daemon --start --components=pkcs11")
   '("gnome-keyring-daemon --start --components=secrets")
   '("gnome-keyring-daemon --start --components=ssh")
   
   '("ibus-daemon" "--xim")                                  ;;input method
   '("numlockx" "on")
   '("remmina" "-i")
   ;;wallpaper setting
   (list "feh" "--bg-fill" (concat zzsawfish-path "wallpaper/" (nth 6 list-wallpaper)))
   ;;system info show
   ;(list "conky" (format nil "-x %d" (- (screen-width) 170)) (format nil "-y %d" (- (screen-height) 600)))
   ))

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
(setq decorate-transients t)

(setq workspace-names     '("work")) 
(setq place-window-mode   'first-fit)

;; Load gnome stuff even if we start before any gnome properties are set.
(require 'sawfish.wm.state.gnome)

;; Don't load a custom default file; it loses information about which
;; variables users have set, and it overrides site defaults.
(setq custom-default-file "/dev/null")

;; Define some of the settings from the sawfish custom default file as
;; site defaults.  What we left out was a setting to enable tooltips,
;; to disable showing of tooltip doc strings, and to set the worksapce
;; geometry to contain four workspaces.
(setq warp-to-selected-windows nil)
(setq cycle-warp-pointer nil)
(setq focus-mode 'click)
(bind-keys window-keymap "Button1-Click1" 'raise-and-pass-through-click)

;; Focus mode customizations
(require 'auto-raise)
(setq focus-windows-on-uniconify t)
(setq raise-window-timeout 0)

;; Menu customizations
(require 'sawfish.wm.menus)
(require 'sawfish.wm.ext.old-window-menu)
(setq menu-program-stays-running t)
(menu-start-process)

(setq  root-menu
    `((,(_ "_Windows")    .  window-menu)
      (,(_ "Work_spaces") .  workspace-menu)
      (,(_ "_Programs")   .  apps-menu)
      (,(_ "_Customize")  .  custom-menu)
      (,(_ "_Help")
       (,(_ "_FAQ...")           help:show-faq)
       (,(_ "_News...")          help:show-news)
       (,(_ "_WWW page...")      help:show-homepage)
       (,(_ "_Manual...")        help:show-programmer-manual)
       (,(_ "_About Sawfish...") help:about))
      ()
      (,(_ "_Restart")  restart)
      (,(_ "_Quit")     quit)))

(setq apps-menu  
      `((,(_ "_Terminal")        (system "gnome-terminal &"))  
        (,(_ "_Emacs")           (system "emacs &"))  
        (,(_ "_Firefox")         (system "firefox &"))  
        (,(_ "_Beyond Compare")  (system "bcompare &"))
        (,(_ "_Nautilus")        (system "nautilus --no-desktop ~ &"))
        (,(_ "_Remmina")         (system "remmina &"))
        (,(_ "_Evince")          (system "evince &"))
        (,(_ "_Monitor")         (system "gnome-system-monitor &"))
        (,(_ "_Tools")
         (,(_ "_Gnome Control Center")  (system "gnome-control-center &"))
         (,(_ "_Gnome Panel")           (open/close-gnome-panel))
         (,(_ "_Gconf Editor")          (system "gconf-editor &"))
         (,(_ "_Sound Control")         (system  (program-term "alsamixer")))
         (,(_ "_Gcolor2")               (system "gcolor2 &"))  
         (,(_ "_Gcalctool")             (system "gcalctool &")))
        (,(_ "_Capture")
         (,(_ "_Current Window") (capture-this-window))  
         (,(_ "_Region")         (capture-region))  
         (,(_ "_Full Screen")    (capture-root-window)))
        ()
        (,(_ "_Run")             (system "gmrun &"))
        (,(_ "_Lock")            (system "xscreensaver-command -lock &"))
        ))

(provide 'common-setting)
;;; common-setting.jl end here
