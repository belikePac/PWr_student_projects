classdef Scrambler < handle
    
    properties (Access = private)
        defaultLSFR
        tempLSFR
    end
    
    methods
        function this = Scrambler(seed) %konstruktor
            if(nargin == 0)             %number of function input arguments = 0 -> konstruktor bezparametryczny
                this.defaultLSFR = [0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1];
                this.tempLSFR = this.defaultLSFR;
            else                        %seed z parametru
                this.defaultLSFR = seed;
                this.tempLSFR = seed;
            end
        end
        
        function resetLSFR(this)    %reset rejestru do stanu pocz�tkowego
            this.tempLSFR = this.defaultLSFR;
        end
        
        function scr = scrambleSignal(this, signal)                                   %funkcja scrambluj�ca
            for i = 1:signal.getSize()  
                x = xor(this.tempLSFR(1), xor(this.tempLSFR(21), this.tempLSFR(37))); %xor 1,21 i 37 indeksu lfsr
                x = xor(signal.getBitAt(i), x);                                       %xor danego bitu sygna�u oraz warto�ci z poprzedniego xora
                signal.setBitAt(i, x);                                                %ustawienie bitu sygna�u wyj�ciowego
                
                this.tempLSFR = [signal.getBitAt(i), this.tempLSFR(1:end-1)];         %przesuni�cie rejestru
            end
            %zwroc sygnal
            scr = signal;        
            %this.resetLSFR;
            %podczas przesy�u ramka nie b�dzie musia�a by� resetowana, bo w
            %scramblerze i descramblerze b�d� mia�y identyczn� zawarto��
            %i b�d� przesuwa� si� zawsze o tyle samo
        end
        
        function printLSFR(this)       %wydruk stanu rejestru tempLSFR
            fprintf('LSFR:\n[');
            for i = 1 : size(this.tempLSFR,2)
                fprintf('%d, ', this.tempLSFR(i));
            end
            fprintf(' ]\n');
        end
        
    end
end