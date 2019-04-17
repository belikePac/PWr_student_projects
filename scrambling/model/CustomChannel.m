 classdef CustomChannel < Channel
    %CUSTOMCHANNEL Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Access = private)
        probability; %dla funkcjonalnosci bsc
        desynchNumOfBits; %ilosc bitow po ktorych sie desynchronizuje
        periodNumOfBits; %okresowe przeklamanie bitu
    end
    
    methods (Access = public)
        
        function this = CustomChannel(prob, desynch, period)
            
            if(prob<=1 && prob>=0)
                this.probability = prob;
            else
                this.probability = 0;
            end
            
            if(desynch>1)
                this.desynchNumOfBits = desynch;
            else
                this.desynchNumOfBits = 21; %tu nale�y przyj�� jedn� warto��, kt�ra b�dzie domyslna, a najlepiej niech pochodzi z jakiej�� normy ITU, czy ISO
            end
            
            if(period>0)
                this.periodNumOfBits = period;
            else
                this.periodNumOfBits = 0;
            end
            
        end
        
        function sendSig(this, signal)
            if (class(signal) == "Signal")      %tylko je�li wysy�any obiekt jest instancj� Signal
                this.signal = signal.copy;      %wysy�amy kopi� sygna�u do kana�u
                this.passThroughCC();             %przepuszczenie kopii sygna�u przez CC
            else
                return
            end
        end
       
        function received = receiveSig(this)
            if(~isempty(this.signal))    %je�eli signal jest, to go wy�lij
                received = this.signal;
            else                        % je�eli go nie ma to wyslij pusty wektor
                received = [];
            end
            this.signal = [];
        end 
        
    end
    
    methods (Access = private)
        
        function passThroughCC(this)
            this.BSC();
            this.periodicDistortion();
            this.desynchronization();
        end
        
        function BSC(this)
            if(this.probability ~= 0)
                temp_sig = zeros(1,this.signal.getSize()); %alokacja wektora o d�ugo�ci sygna�u
                for i=1 : this.signal.getSize()
                    temp_sig(i) = this.signal.getBitAt(i);
                end
                temp_sig = bsc(temp_sig, this.probability);
                for i=1 : this.signal.getSize()
                    this.signal.setBitAt(i, temp_sig(i));
                end
            end
        end
        
        function periodicDistortion(this)
            if(this.periodNumOfBits ~= 0)
                k = floor(this.signal.getSize()/this.periodNumOfBits);
                i = this.periodNumOfBits;
                while(k>0)
                    this.signal.negBitAt(i);
                    i = i + this.periodNumOfBits;
                    k = k - 1;
                end
            end
        end
        
        function desynchronization(this)
            counter = 0;
            currentDesynchBit = this.signal.getBitAt(1);
            i=1;
            while(i <= this.signal.getSize())
                
                if(this.signal.getBitAt(i) == currentDesynchBit)
                    counter = counter + 1;
                else
                    currentDesynchBit = this.signal.getBitAt(i);
                    counter = 1;
                end
                
                %je�eli pojawi si� k-te wyst�pienie bitu to
                %desynchronizacja, gdzie k wyznacza defacto desynchNumOfBits
                if(counter >= this.desynchNumOfBits)
                    %desynchronizacja b�dzie polega� na pseudoloswym
                    %wstawieniu lub usuni�ciu aktualnie przetwarzanego 
                    %bitu, kt�ry si� powt�rzy�
                    if(rand()>0.5)
                        %usuni�cie bitu
                        this.signal.removeBitAt(i);
                        %iterator i wskazuje na przesuni�tu o jeden w lewo
                        %bit, zatem nie trzeba modyfikowa� i
                    else
                        %wstawienie bitu powtarzaj�cego si� na pozycj�
                        %za indeksem i
                        this.signal.insertBitAt(i, currentDesynchBit);
                        %i wskazuje na bit przed nowym bitem zatem nale�y
                        %przesun�� i za nowo wstawiony bit
                        %inaczej na kolejny bit oryginalnego sygna�u
                        i = i + 2;
                    end
                else
                    %je�eli desynchNumOfBits nie zosta�a przekroczona
                    %to po prostu przechodzimy z i do nastepnego znaku
                    i = i + 1;
                end
                
            end
        end
        
    end
    
end

