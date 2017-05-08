immutable Platform{P}
end

AIRMOSS = Platform{:AIRMOSS}()
AIRSAR = Platform{:AIRSAR}()
ALOS = Platform{:ALOS}()
ERS1 = Platform{:ERS1}()
ERS2 = Platform{:ERS2}()
JERS1 = Platform{:JERS1}()
RADARSAT1 = Platform{:RADARSAT1}()
SEASAT = Platform{:SEASAT}()
Sentinel1A = Platform{:Sentinel1A}()
SMAP = Platform{:SMAP}()
UAVSAR = Platform{:UAVSAR}()

A3 = ALOS
AI = AIRMOSS
AS = AIRSAR
E1 = ERS1
E2 = ERS2
J1 = JERS1
R1 = RADARSAT1
SS = SEASAT
SA = Sentinel1A
SP = SMAP
UA = UAVSAR

Base.string{P}(p::Platform{P}) = string(P)
Base.string(p::Platform{:ERS1}) = "ERS-1"
Base.string(p::Platform{:ERS2}) = "ERS-2"
Base.string(p::Platform{:JERS1}) = "JERS-1"
Base.string(p::Platform{:RADARSAT1}) = "RADARSAT-1"
Base.string(p::Platform{:Sentinel1A}) = "Sentinel-1A"

            
