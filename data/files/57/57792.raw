#! /usr/bin/env julia

gear_ratio = 37/13

steps_per_rev = 200*16

bolt_diameter = 7.5

steps_per_bolt_rev = gear_ratio * steps_per_rev # steps/rev

bolt_circumference = bolt_diameter * pi # mm/rev

steps_per_mm = steps_per_bolt_rev/bolt_circumference

println("Steps per mm of filament: $steps_per_mm")
