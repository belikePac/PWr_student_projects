classdef Signal < handle
    properties
        size
        bits
    end
    
    methods
        function this = Signal(parameter)   %konstruktor
            if (nargin ~= 0)    %je�li nie zero
                this.bits = logical.empty;  %ustawiamy bity na puste
                if (isnumeric(parameter))   %je�li parametr jest numeryczny
                    this.size = parameter;  %ilo�c bit�w 
                    for i = 1 : parameter
                        this.bits(i) = false;   %inicjalizacja fa�szem
                    end
                else
                    fromFile = importdata(parameter);  %je�li parametr jest plikiem
                    this.size = fromFile(1);           %pierwszy wiersz zawiera rozmiar
                    for i = 1 : this.size
                        this.bits(i) = (fromFile(k+1) == 0).*false + (fromFile(k+1) ~= 0).*true;  %this.bits(i) = (from_file(k+1) == 0) ? false : true
                    end
                end
            else
                this.size = 0;              %je�li brak parametru -> ilo�� bit�w = 0;
            end   
        end
        
        %funkcje operuj�ce bezpo�rednio na bitach
        
        function bit = getBitAt(this, i)    %getter bitu na pozycji i (zwraca jako warto�� liczbow�)
            if (i >= 1 && i <=this.size)
                bit = this.bits(i).*1 + ~this.bits(i).*0; %bit = (this.bits(i)) ? 1 : 0;
            else
                %disp('getBitAt(' + i +') Index out of bound! Signal is ' + this.size + 'b!');
                %bit = [];
                %lepiej b�dzie zwr�ci� warto�� sygnalizuj�c� brak bitu na
                %danej pozycji, szczeg�lnie dla mechanizmu resynchronizacji
                bit = -1;
            end
        end
        
        function setBitTrue(this, i)            %setter bitu na pozycji i (warto�ci� true)
            if (i >= 1 && i <=this.size)
                this.bits(i) = true;
            else
                disp("setBitTrue(" + i + ") Index out of bound! Signal is " + this.size + "b!");
            end
        end
        
        function setBitFalse(this, i)            %setter bitu na pozycji i (warto�ci� false)
            if (i >= 1 && i <=this.size)
                this.bits(i) = false;
            else
                disp("setBitFalse(" + i + ") Index out of bound! Signal is " + this.size + "b!");
            end
        end
        
        function setBitAt(this, i, value)         %setter bitu na pozycji i zadan� warto�ci�
            if (value == 1)
                this.setBitTrue(i);
            else
                this.setBitFalse(i);
            end
        end
        
        function negBitAt(this, i)              %negacja bitu na pozycji i
            if (i >= 1 && i <=this.size)
                this.bits(i) = ~this.bits(i);
            else
                %disp('negBitAt(' + i + ') Index out of bound! Signal is ' + this.size + 'b!');
            end
        end
        
        function removeBitAt(this, i)           %usuni�cie bitu na pozycji i
            if(i >= 1 && i <=this.size)
                 prevBits = this.bits(1 : i-1);              %bity na mniejszych indeksach do bitu poprzedzaj�cego i
                 nextBits = this.bits(i+1 : this.size);      %bity na wi�kszych indeksach do ko�ca sygna�u
           
                 this.bits = [prevBits nextBits];           %zestawienie nowego sygna�u bez i-tego bitu
                 this.size = this.size - 1;                   %dekrementacja ilo�ci bit�w
            end
        end
        
        function insertBitAt(this, i, value) %wstawienie bitu o warto�ci value na pozycj� PO danym indeksie
            prevBits = this.bits(1 : i);            %jak w funkcji removeBitAt
            nextBits = this.bits(i+1 : this.size);
            
            this.bits = [prevBits logical(value) nextBits];   %zestawienie nowego sygna�u z konwersj� value na warto�� logiczn�
            this.size = this.size + 1;                          %inkrementacja ilo�ci bit�w
        end
        
        %funkcje pomocnicze
        
        function size = getSize(this)       %getter rozmiaru
            size = this.size;
        end     
        
        function value = decimalValue(this) %zwraca warto�c decymaln� sygna�u
            value = 0;  %inicjalizacja zerem
            for i = 1 : this.size
                value = value + (2 ^ (i - 1)) * this.getBitAt(i);
            end
        end
        
        function cpy = copy(this)           %tworzy kopi� zadanego sygna�u
            cpy = Signal(this.size);        %cpy = new signal(this.size)
            for i = 1 : cpy.size
                cpy.bits(i) = this.bits(i); %przepisanie warto�ci
            end
        end
        
        function printSignal(this)          %wydruk sygna�u
            disp('Current Signal: ');
            fprintf('[\n');
            for i = 1 : this.size
               fprintf('%d ', this.bits(i));
               if(mod(i,64) == 0)
                   fprintf("\n");
               end
            end
            fprintf(']\n');
        end
        
        function signal = toString(this)    %konwersja sygna�u na string, u�ywamy
            signal = string();
            for i = 1 : this.size
                if(this.bits(i))
                    signal = strcat(signal, '1');
                else
                    signal = strcat(signal, '0');
                end
            end                       
        end 
    end
    
end