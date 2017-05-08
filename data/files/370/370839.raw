# *****************************************************************************
# Written by Ritchie Lee, ritchie.lee@sv.cmu.edu
# *****************************************************************************
# Copyright ã 2015, United States Government, as represented by the
# Administrator of the National Aeronautics and Space Administration. All
# rights reserved.  The Reinforcement Learning Encounter Simulator (RLES)
# platform is licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License. You
# may obtain a copy of the License at
# http://www.apache.org/licenses/LICENSE-2.0. Unless required by applicable
# law or agreed to in writing, software distributed under the License is
# distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied. See the License for the specific language
# governing permissions and limitations under the License.
# _____________________________________________________________________________
# Reinforcement Learning Encounter Simulator (RLES) includes the following
# third party software. The SISLES.jl package is licensed under the MIT Expat
# License: Copyright (c) 2014: Youngjun Kim.
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
# "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
# PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# *****************************************************************************

module CASInterface

export OwnInput, IntruderInput, Input, IntruderOutput, Output, reset!
export EQUIPAGE, EQUIPAGE_ATCRBS, EQUIPAGE_MODES, EQUIPAGE_TCASTA, EQUIPAGE_TCAS

#equipage enum
immutable EQUIPAGE
  val::Int32
end
const EQUIPAGE_ATCRBS = EQUIPAGE(0)
const EQUIPAGE_MODES = EQUIPAGE(1)
const EQUIPAGE_TCASTA = EQUIPAGE(2)
const EQUIPAGE_TCAS = EQUIPAGE(3)

type OwnInput
  dz::Float64
  z::Float64
  psi::Float64
  h::Float64
  modes::UInt32
end
OwnInput() = OwnInput(0.0, 0.0, 0.0, 0.0, UInt32(0))

type IntruderInput
  valid::Bool
  id::UInt32
  modes::UInt32
  sr::Float64
  chi::Float64
  z::Float64
  cvc::UInt8
  vrc::UInt8
  vsb::UInt8
  equipage::EQUIPAGE
  quant::UInt8
  sensitivity_index::UInt8
  protection_mode::UInt8
end
IntruderInput() = IntruderInput(false, UInt32(0), UInt32(0), 0.0, 0.0, 0.0, UInt8(0), UInt8(0), UInt8(0),
                                EQUIPAGE_TCAS, UInt8(0), UInt8(0), UInt8(0))

type Input
  ownInput::OwnInput
  intruders::Vector{IntruderInput}
end
Input(nintruders::Int) = Input(OwnInput(), IntruderInput[IntruderInput() for i = 1:nintruders])

type IntruderOutput
  id::UInt32
  cvc::UInt8
  vrc::UInt8
  vsb::UInt8
  tds::Float64
  code::UInt8
end
IntruderOutput() = IntruderOutput(UInt32(0), UInt8(0), UInt8(0), UInt8(0), 0., UInt8(0))

type Output
  cc::UInt8
  vc::UInt8
  ua::UInt8
  da::UInt8
  target_rate::Float64
  turn_off_aurals::Bool
  crossing::Bool
  alarm::Bool
  alert::Bool
  dh_min::Float64
  dh_max::Float64
  sensitivity_index::UInt8
  ddh::Float64
  intruders::Vector{IntruderOutput}
end
Output(nintruders::Int) = Output(UInt8(0), UInt8(0), UInt8(0), UInt8(0), 0.0, false, false, false, false,
                                 -9999.0, 9999.0, UInt8(0), 0.0,
                                 IntruderOutput[IntruderOutput() for i = 1:nintruders])

function reset!(ownInput::OwnInput)
  ownInput.dz = 0.0
  ownInput.z = 0.0
  ownInput.psi = 0.0
  ownInput.h = 0.0
  ownInput.modes = UInt32(0)
end

function reset!(iinput::IntruderInput)
  iinput.valid        = false
  iinput.id           = UInt32(0)
  iinput.modes        = UInt32(0)
  iinput.sr           = 0.0
  iinput.chi          = 0.0
  iinput.z            = 0.0
  iinput.cvc          = UInt8(0)
  iinput.vrc          = UInt8(0)
  iinput.vsb          = UInt8(0)
  iinput.equipage     = EQUIPAGE_TCAS
  iinput.quant        = UInt8(0)
  iinput.sensitivity_index = UInt8(0)
  iinput.protection_mode   = UInt8(0)
end

function reset!(input::Input)
  reset!(input.ownInput)

  for i = 1:endof(input.intruders)
    reset!(input.intruders[i])
  end
end

function reset!(iout::IntruderOutput)
  iout.id = UInt32(0)
  iout.cvc = UInt8(0)
  iout.vrc = UInt8(0)
  iout.vsb = UInt8(0)
  iout.tds = 0.0
  iout.code = UInt8(0)

  return
end

function reset!(out::Output)
  out.cc = UInt8(0)
  out.vc = UInt8(0)
  out.ua = UInt8(0)
  out.da = UInt8(0)
  out.target_rate = 0.0
  out.turn_off_aurals = false
  out.crossing = false
  out.alarm = false
  out.alert = false
  out.dh_min = -9999.0
  out.dh_max = 9999.0
  out.sensitivity_index = UInt8(0)
  out.ddh = 0.0

  for i = 1:endof(out.intruders)
    reset!(out.intruders[i])
  end

  return
end

end # module
