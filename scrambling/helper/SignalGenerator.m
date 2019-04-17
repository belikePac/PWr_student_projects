classdef SignalGenerator < handle
    %generator sekwencji x * 64b
    %x to d�ugo�� ramki podawana przez u�ytkownika
    
    properties
        numOfFrames    %user defined values: number of frames 
        p              %probability
    end
    
    methods (Access  = public)
        function obj = SignalGenerator(num, prob)
            if((prob>=0 && prob<=1) && num >=0)
                obj.p = prob;
                obj.numOfFrames = num;
            else
                obj.p = 0;
                obj.numOfFrames = (-1) * num;
            end
        end
        
        function setProbability(obj, prob)
            if(prob>=0 && prob<=1)
                obj.p = prob;
            else
                obj.p = 0;
            end
        end
        
        function setFramesNumber(obj, num)
            if(num >= 0)
                obj.numOfFrames = num;
            else
                obj.numOfFrames = (-1) * num;
            end
        end
        
        function gen = generateSignal(obj)
            gen = Signal(obj.numOfFrames * 64); %d�ugo�� sygna�u to ilo�� ramek razy ilo�� bit�w (64b)
            
            for i = 1: gen.getSize()
                if( (0.5 + obj.p/2) >= rand)     %szansa �e z prawdopodobie�stwiem p wstawi si� jedynka
                    gen.setBitTrue(i);           %je�eli p = 0 to musi by� 0.5>=rand poniewa� rozk�ad 1/0 musi by� fifty-fifty                                               
                end                              %wymaga to wprowadzonego warunku, na jego podstawie b�dzie zwi�ksza� si�
            end                                  %liczba jedynek zawartych w sygnale
            
        end
    end
    
end

