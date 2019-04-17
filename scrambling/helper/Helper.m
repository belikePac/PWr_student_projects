classdef Helper
    %HELPER klasa zawiraj�ce niekt�re metody pomocnicze
    
    methods (Static)
        function ber = calculateBER(originalSignal, outputSignal)
            errors = max(originalSignal.getSize(), outputSignal.getSize()) - min(originalSignal.getSize(), outputSignal.getSize());
            %pocz�tkowo errors ma warto�� r�nicy mi�dzy sygna�ami, po zaimplementowaniu kana�u z duplikacjami, ta warto�� b�dzie r�na od zera
            totalBits = max(originalSignal.getSize(), outputSignal.getSize()); %0 < ber < 1.00, dlatego totalbits to d�ugo�� wi�kszego z sygna��w
            
            for i = 1 : min(originalSignal.getSize(), outputSignal.getSize())
                if(originalSignal.getBitAt(i) ~= outputSignal.getBitAt(i)) %je�li bity s� r�ne
                    errors = errors + 1;
                end
            end
            
            ber = errors/totalBits;
        end
        
        function o = insertToAlign64(signal)
            currentSize = signal.getSize();
            newSize = 64 * (floor((currentSize-1)/64) + 1);
            o = Signal(newSize);
            
            for i = 1 : currentSize
                o.setBitAt(i, signal.getBitAt(i));
            end
        end
    end
end