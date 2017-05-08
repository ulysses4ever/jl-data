function ircms(J::Int,h::Vector)
    g::Vector = [0;1]
    for length = 3:J
        g_length::Int = max(g)
        bad_flag::Bool = true
        
        while bad_flag
            g_length += 1
            bad_flag = false
            
            for gi in g, gj in g
                if bad_flag
                    break
                end
                
                if gi == gj
                    break
                end
                
                for hl in h, hm in h, hn in h
                    if bad_flag
                        break
                    end
                    
                    if hl == hm || hl == hn || hm == hn
                        break
                    end
                    
                    if (g_length - gi)*(hn - hl) == (gj - gi)*(hm - hl)
                        bad_flag = true
                        break
                    end
                    
                end
            end    
        end
        
        g=[g;g_length]
    end
    g
end
