classdef Decoder2 < handle

    properties
        preamble = [0,1];
    end
    
    methods
        
        function this=Decoder2()
        end
        
        function decodedSignal = decode(this,signal)
            decodedSignal = signal; %funkcja musi miec co zwrocic
            
            if class(signal) == "Signal"
                %w petli co 64 bity usuwamy preambule
                p = floor( signal.getSize() / 66);  %ilosc potencjalnych preambul
                temp_preamble = [0,0];              %odczytana preambula na pozycji xx
                i = 1;
                
                while(i<=signal.getSize())
                    temp_preamble(1) = signal.getBitAt(i);
                    temp_preamble(2) = signal.getBitAt(i+1);
                    if(this.preamble == temp_preamble)
                        %jezeli preambula jest ok
                        %to po prostu j� usu�                     
                        signal.removeBitAt(i);
                        signal.removeBitAt(i);
                        i = i + 64;
                    else      
                        %PODEJSCIE NOWE - do�� naiwne, ale jakiekolwiek:
                        %usuwamy bity dop�ki nie odnajdziemy takiej
                        %sytaucji, �e na miejscu i, i+1 wyst�puje poprawna
                        %preabu�a oraz wyst�puje ona 64 bity dalej na
                        %miejscach i+64, i+65
                        %dla sygna�u o jednostanym rozk�adzie jedynek i zer
                        %prawdobodobie�stwo takiej sytaucji wynosi 
                        %1/4 * 1/4 = 1/16
                        %zatem je�eli j� napotkamy to s� to znaczne szanse,
                        %�e mechanizm resynchronizacji trafi� na w�a�ciwe
                        %bity preambu�
                        
                        still = true;           %odpowiada za iteracj� p�tli while kt�ra resynchronizuje sygna�                       
                        signal.removeBitAt(i);  %wpierw nale�y usun�� poprzedni� b��dn� preambu��
                        signal.removeBitAt(i);
                                                %dalej pozostajemy na
                                                %pozycji i gdzie powinna
                                                %by� preambu�a
                        while(still)
                            if(this.preamble(1) == signal.getBitAt(i) && this.preamble(2) == signal.getBitAt(i+1) && this.preamble(1) == signal.getBitAt(i+66) && this.preamble(2) == signal.getBitAt(i+67) )
                                signal.removeBitAt(i);
                                signal.removeBitAt(i);
                                %poniewa� trafili�my na sytuacj�
                                %sprzyjaj�c�, to przerywamy proces
                                %resynchronizacji 
                                %oraz przesuwamy si� 64 bity dalej
                                %tak jak ma to miejsce w prawid�owym
                                %uk�adzie bit�w preambu�y
                                still = false;
                                i = i + 64;
                            else
                                %je�eli nie jest to sytuacja sprzyjaj�ca
                                %jak w warunku if(...),
                                %to usuwamy nast�pne dwa przetoworzone bity,
                                %kt�re mog�y stanowi� prawid�ow� preambu��
                                signal.removeBitAt(i);
                                signal.removeBitAt(i);
                                %poniewa� istnia�a mo�liwo�� �e gdy i by�o
                                %ju� ostatni� lini� bit�w, to algorytm
                                %nigdy nie m�g� przecie� znale�� kolejnych
                                %64 bit�w, bo ich nie by�o
                                %a sam program wpada� w p�tl� niesko�czon�
                                %poni�szy if(...) sprawdza czy po usuwaniu
                                %element�w przypadkiem i nie przekroczy�
                                %ju� zakresu, kt�ry jest sens sprawdza�
                                if(i>signal.getSize())
                                    still = false;
                                end
                                %i dalej kontynuujemy szukanie sprzyjaj�cej
                                %nam sytaucji 01(64 bity dalej...)01...
                            end
                        end
                        
                    end
                    
                    %p = p - 1;
                    
                end
            else
                return
            end
            
            decodedSignal = signal; %odkodowany i zresynchronizowany sygna�
            
        end 
       
    end
    
end
