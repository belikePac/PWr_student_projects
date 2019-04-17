classdef Encoder < handle

    properties
        preamble;
    end
    
    methods
        function this=Encoder()
            this.preamble = [0 1];
        end
        
        function encodedSignal = encode(this,signal)
            encodedSignal = signal; %bo funkcja musi mie� co zwr�ci�
            
            if class(signal) == "Signal"
                %w petli co 64 bity wstawimy preambule
                p = floor( signal.getSize() / 64);
                i = 0;
                while(p>0)
                    signal.insertBitAt(i, this.preamble(1));
                    signal.insertBitAt(i+1, this.preamble(2));
                    i = i + 66;
                    p = p - 1; %zmniejszamy ilosc preambul do wpisania
                end
            else
                return 
            end
            
            encodedSignal = signal; %nowy zmieniony, zakodowany sygna�
            
        end 
     
    end
end
