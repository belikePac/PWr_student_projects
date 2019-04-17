classdef BSChannel < Channel
          %BSC - binary symetric channel
    
    properties (Access = private)
        p %prawdopodobienstwo przek�amania
    end
    
    methods
        function obj = BSChannel(probability)
            if(nargin == 0)
                obj.p=0;
            else
                if(probability >= 0 & probability <=1)
                    obj.p = probability;
                else
                    obj.p = 0;
                end
            end
            obj.signal = [];
        end %koniec konstruktora
        
        function sendSig(obj, signal)
            if class(signal) == "Signal"        %tylko je�li wysy�any obiekt jest instancj� Signal
                obj.signal = signal.copy;       %wysy�amy kopi� sygna�u do kana�u
                obj.passThroughBSC;             %przepuszczenie kopii sygna�u przez kana� BSC
            else
                return
            end
        end
       
        function received = receiveSig(obj)
            if(~isempty(obj.signal))    %je�eli signal jest, to go wy�lij
                received = obj.signal;
                obj.signal = [];
            else                        % je�eli go nie ma to wyslij pusty wektor
                received = [];
                obj.signal = [];
            end
        end
        
    end
    
    methods (Access = private)
        function passThroughBSC(obj)
            %temp_sig b�dzie binarnym wektorem otrzymanego sygna�u 
            temp_sig = zeros(1,obj.signal.getSize()); %alokacja wektora o d�ugo�ci sygna�u
            for i=1 : obj.signal.getSize()
                temp_sig(i) = obj.signal.getBitAt(i);
            end
            
            %wektor ten mo�e by� przepuszczony przez funkcj� bsc
            temp_sig = bsc(temp_sig,obj.p); %do funkcji bsc przekazujemy ustawione prawdopodobie�stwo - p
            
            %nast�pnie nale�y ustawi� bity przechowywanego sygna�u, je�eli
            %w kanale zosta�y one zmienione
            for i=1 : obj.signal.getSize()
                obj.signal.setBitAt(i, temp_sig(i));
            end
        end
    end
    
end

