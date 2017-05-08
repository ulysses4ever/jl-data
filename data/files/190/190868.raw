;;  -*- sawfish -*-
;; A few commands to start programs by keypresses
;; by Friedrich Delgado Friedrichs <friedel@nomaden.org>
;Time-stamp: <01/08/27 11:43:04 friedel>

;; I wrote this for an older sawfish version that did not have
;; (run-shell-command), but i still use it, since this way is more
;; convenient than typing all the commands into the customization
;; tool.

;; Installation: Put this into ~/.sawfish/lisp and then edit it to
;; suit your needs! (Important point!) Then put (require 'commands)
;; into you're ~/.sawfishrc Afterwards you can bind these useful
;; commands to keystrokes of your choice.

(defmacro defprogram (name)
  `(defun ,(intern (format nil "program-%s" name)) ()
     ,(format nil "Starts the program %s without arguments.%~" name)
     (interactive)
     (system ,(format nil "%s &" name))))

(defmacro defprogram-with-command (name command)
  `(defun ,(intern (format nil "program-%s" name)) ()
     ,(format nil "Starts the program named %s with the commandline %s.%~"
     name command)
     (interactive)
     (system ,(format nil "%s &" command))))

(defmacro defsshterm (name)
  `(defun ,(intern (format nil "program-%s" name)) ()
     ,(format nil "Start a gnome-terminal with an ssh session to host %s%~" name)
     (interactive)
     (system ,(format nil "gnome-terminal --name=%s -t %s -x ssh %s &" name name name))))

;;define all the names in the list as programs
(defmacro defprograms (#!rest proglist)
  `(progn
     ,@(mapcar (lambda (x) `(defprogram ,x)) proglist)))

;;define all the seconds from the list-elements as commands, with the
;;  cars as name
(defmacro defprogram-command-list (#!rest proglist)
  `(progn
    ,@(mapcar (lambda (x)
		`(defprogram-with-command
		   ,(car x) ,(cadr x)))
	      proglist)))

;;define a sshterm command to all these hosts
(defmacro defsshterms (#!rest proglist)
  `(progn
     ,@(mapcar (lambda (x) `(defsshterm ,x)) proglist)))

;;; ---------- Now, let's use those macros ------------------ ;;;

(defprograms gnome-terminal muttmacs netscape xawtv root
nethack.gurke rootscreen rox opera galeon)

(defprogram-command-list
  (mutt "gnome-terminal --termname=gnome --name=mutt -t mutt -x mutt")
  (mc "gnome-terminal --name=mc -t mc -x mc")
  (gnome-terminalscreen
   "gnome-terminal -t screen --name=screen -x screen -xRR")
  (google "gnome-moz-remote http://www.google.com")
  (dict "gnome-moz-remote http://dict.leo.org")
  (alevt "alevt 333")
  (lock-screen "xscreensaver-command -lock")
  (eject-cdrom "sudo eject cdrom")
  (yast "gnome-terminal --name=yast -t yast -x su - root -c yast")
  (yast2 "kdesu yast2 menu"))

(defsshterms
  koffer gurke rzdspc3 public root@koffer root@gurke)

(provide 'friedel.commands)

