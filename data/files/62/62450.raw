; QN-X11-blue/theme.jl

;; by Rowan Kerr <rowan@stasis.org>

(let*
    ;; Update window title pixel length
    ((title-width
      (lambda (w)
	(let
	    ((w-width (car (window-dimensions w))))
	  (max 0 (min (- w-width 100) (text-width (window-name w)))))))

     ;; fonts

     (font (get-font "-adobe-helvetica-bold-r-normal-*-*-120-*-*-p-*-iso8859-1"))
     (t-font (get-font "-adobe-helvetica-bold-r-normal-*-*-100-*-*-p-*-iso8859-1"))
     (font-colors (list "#300030003000" "#000000000000"))
     
     ;; images

     (border-images (make-image "black_border.png"))

     (bottom-images (make-image "border_bottom.png"))

     (top-left-images (list (make-image "title_left_0.png")
			    (make-image "title_left_1.png")))
     (top-left-shaped-images (list (make-image "title_left_s_0.png")
				   (make-image "title_left_s_1.png")))

     (top-title-images (list (make-image "title_text_0.png")
	 		     (make-image "title_text_1.png")))

     (top-notch-images (list (make-image "title_text_end_0.png")
			     (make-image "title_text_end_1.png")))

     (top-right-images (make-image "title_right.png"))
     (top-right-shaped-images (make-image "title_right_s.png"))

     (bottom-left-images (make-image "border_left_corner.png"))

     (bottom-right-images (make-image "border_right_corner.png"))

     (close-images (list (make-image "button_close_0.png")
			 (make-image "button_close_1.png") nil
			 (make-image "button_close_2.png")))

     (maximize-images (list (make-image "button_max_0.png")
			    (make-image "button_max_1.png") nil
			    (make-image "button_max_2.png")))

     (iconify-images (list (make-image "button_min_0.png")
			   (make-image "button_min_1.png") nil
			   (make-image "button_min_2.png")))

     (menu-images (list (make-image "button_menu_0.png")
			(make-image "button_menu_1.png") nil
			(make-image "button_menu_2.png")))

     (left-images (make-image "border_left.png"))

     (right-images (make-image "border_right.png"))


     (t-close-images (list (make-image "t_button_close_0.png")
			   (make-image "t_button_close_1.png") nil
			   (make-image "t_button_close_2.png")))

     (t-top-images (list (make-image "t_title_text_0.png")
                         (make-image "t_title_text_1.png")))

     (t-top-notch-images (list (make-image "t_title_text_end_0.png")
                               (make-image "t_title_text_end_1.png")))

     (t-top-left-images (list (make-image "t_title_left_0.png")
                              (make-image "t_title_left_1.png")))

     (t-top-right-images (make-image "t_title_right.png"))
     (t-top-right-shaped-images (make-image "t_title_right_s.png"))

     ;; frame layout

     (frame `(((background . ,top-left-images)
	       (left-edge . -6)
	       (top-edge . -22)
	       (cursor . left_ptr)
	       (class . title))

	      ;; top title
	      ((background . ,top-title-images)
	       (foreground . ,font-colors)
               (font . ,font)
	       (text . ,window-name)
	       (y-justify . 5)
	       (x-justify . 4)
	       (top-edge . -22)
	       (left-edge . 21)
               (right-edge . 59)
               (cursor . left_ptr)
	       (class . title))

	      ;; menu button
	      ((background . ,menu-images)
	       (top-edge . -22)
	       (left-edge . 0)
               (cursor . left_ptr)
	       (class . menu-button))

	      ;; top notch
	      ((background . ,top-notch-images)
               (right-edge . 51)
	       (top-edge . -22)
               (cursor . left_ptr)
	       (class . title))

	      ;; left border
	      ((background . ,left-images)
	       (left-edge . -6)
	       (top-edge . 1)
	       (bottom-edge . 0)
	       (class . left-border))

	      ;; top-right corner
	      ((background . ,top-right-images)
	       (right-edge . -6)
	       (top-edge . -22)
               (cursor . left_ptr)
	       (class . title))

	      ;; right border
	      ((background . ,right-images)
	       (right-edge . -6)
	       (top-edge . 0)
	       (bottom-edge . 0)
	       (class . right-border))

	      ;; bottom border
	      ((background . ,bottom-images)
	       (left-edge . 0)
	       (right-edge . 0)
	       (bottom-edge . -6)
	       (class . bottom-border))

	      ;; bottom-left corner
	      ((background . ,bottom-left-images)
	       (left-edge . -6)
	       (bottom-edge . -6)
	       (class . bottom-left-corner))

	      ;; bottom-right corner
	      ((background . ,bottom-right-images)
	       (right-edge . -6)
	       (bottom-edge . -6)
	       (class . bottom-right-corner))

	      ;; iconify button
	      ((background . ,iconify-images)
	       (right-edge . 15)
	       (top-edge . -22)
               (cursor . left_ptr)
	       (class . iconify-button))

	      ;; maximize button
	      ((background . ,maximize-images)
	       (right-edge . 35)
	       (top-edge . -22)
               (cursor . left_ptr)
	       (class . maximize-button))

	      ;; delete button
	      ((background . ,close-images)
	       (right-edge . 0)
	       (top-edge . -22)
               (cursor . left_ptr)
	       (class . close-button))))

       (shaped-frame `(((background . ,top-left-shaped-images)
			(left-edge . -6)
			(top-edge . -22)
			(height . 22)
	                (cursor . left_ptr)
			(class . title))

                       ;; menu button
                       ((background . ,menu-images)
                        (top-edge . -22)
                        (left-edge . 0)
                        (cursor . left_ptr)
                        (class . menu-button))

		       ;; top title
		       ((background . ,top-title-images)
			(foreground . ,font-colors)
                        (font . ,font)
			(text . ,window-name)
			(y-justify . 5)
			(x-justify . 4)
			(top-edge . -22)
			(left-edge . 21)
                        (right-edge . 59)
	                (cursor . left_ptr)
			(class . title))

		       ;; top notch
		       ((background . ,top-notch-images)
			(top-edge . -22)
                        (right-edge . 51)
	                (cursor . left_ptr)
			(class . title))

		       ;; top-right corner
		       ((background . ,top-right-shaped-images)
			(right-edge . -6)
			(top-edge . -22)
			(height . 22)
	                (cursor . left_ptr)
			(class . title))

		       ;; bottom 1px black border
                       ((background . ,border-images)
                        (left-edge . -6)
                        (right-edge . -6)
                        (top-edge . 0)
                        (cursor . left_ptr)
                        (class . title))

		       ;; iconify button
		       ((background . ,iconify-images)
			(right-edge . 15)
			(top-edge . -22)
	                (cursor . left_ptr)
			(class . iconify-button))

		       ;; maximize button
		       ((background . ,maximize-images)
			(right-edge . 35)
			(top-edge . -22)
	                (cursor . left_ptr)
			(class . maximize-button))

		       ;; delete button
		       ((background . ,close-images)
			(right-edge . 0)
			(top-edge . -22)
	                (cursor . left_ptr)
			(class . close-button))))

       (transient-frame `(((background . ,t-top-left-images)
			   (left-edge . -6)
			   (top-edge . -17)
	                   (cursor . left_ptr)
			   (class . title))

			  ;;top-right corner
			  ((background . ,t-top-right-images)
			   (right-edge . -6)
			   (top-edge . -17)
	                   (cursor . left_ptr)
			   (class . title))

                          ;; top title
                          ((background . ,t-top-images)
                           (foreground . ,font-colors)
                           (font . ,t-font)
                           (text . ,window-name)
			   (y-justify . 3)
                           (x-justify . 2)
                           (top-edge . -17)
                           (left-edge . 0)
                           (right-edge . 23)
                           (cursor . left_ptr)
                           (class . title))

                          ;; top notch
                          ((background . ,t-top-notch-images)
                           (top-edge . -17)
                           (right-edge . 11)
                           (cursor . left_ptr)
                           (class . title))

			  ;; left border
			  ((background . ,left-images)
			   (left-edge . -6)
			   (top-edge . 0)
			   (bottom-edge . 0)
	                   (cursor . left_ptr)
			   (class . title))

			  ;; right border
			  ((background . ,right-images)
			   (right-edge . -6)
			   (top-edge . 0)
			   (bottom-edge . 0)
	                   (cursor . left_ptr)
			   (class . title))

			  ;; bottom border
			  ((background . ,bottom-images)
			   (left-edge . 0)
			   (right-edge . 0)
			   (bottom-edge . -6)
	                   (cursor . left_ptr)
			   (class . title))

			  ;; bottom-left corner
			  ((background . ,bottom-left-images)
			   (left-edge . -6)
			   (bottom-edge . -6)
	                   (cursor . left_ptr)
			   (class . title))

			  ;; bottom-right corner
			  ((background . ,bottom-right-images)
			   (right-edge . -6)
			   (bottom-edge . -6)
	                   (cursor . left_ptr)
			   (class . title))

			  ;; delete button
			  ((background . ,t-close-images)
			   (right-edge . 0)
			   (top-edge . -17)
	                   (cursor . left_ptr)
			   (class . close-button))))

       (shaped-transient-frame `(((background . ,t-top-left-images)
                                  (left-edge . -6)
                                  (top-edge . -17)
                                  (cursor . left_ptr)
                                  (class . title))

                                 ((background . ,t-top-right-shaped-images)
				  (right-edge . -6)
				  (top-edge . -17)
		                  (cursor . left_ptr)
				  (class . title))

	                         ;; bottom 1px black border
	                         ((background . ,border-images)
	                          (left-edge . -6)
	                          (right-edge . -6)
	                          (top-edge . 0)
	                          (cursor . left_ptr)
	                          (class . title))

                                 ;; top title
                                 ((background . ,t-top-images)
                                  (foreground . ,font-colors)
                                  (font . ,t-font)
                                  (text . ,window-name)
				  (y-justify . 3)
                                  (x-justify . 2)
                                  (top-edge . -17)
                                  (left-edge . 0)
                                  (right-edge . 23)
                                  (cursor . left_ptr)
                                  (class . title))

                                 ;; top notch
                                 ((background . ,t-top-notch-images)
                                  (top-edge . -17)
                                  (right-edge . 11)
                                  (cursor . left_ptr)
                                  (class . title))

				 ;; delete button
				 ((background . ,t-close-images)
				  (right-edge . 0)
				  (top-edge . -17)
		                  (cursor . left_ptr)
				  (class . close-button)))))
  
  (add-frame-style 'QN-X11-blue
		   (lambda (w type)
		     (cond ((eq type 'shaped)
			    shaped-frame)
                           ((eq type 'shaded)
                            shaped-frame)
			   ((eq type 'transient)
			    transient-frame)
			   ((eq type 'shaped-transient)
			    shaped-transient-frame)
                           ((eq type 'shaded-transient)
                            shaded-transient-frame)
			   ((eq type 'unframed)
			    nil-frame)
			   (t
			    frame))))

  (call-after-property-changed
   'WM_NAME (lambda ()
	      (rebuild-frames-with-style 'QN-X11-blue))))
