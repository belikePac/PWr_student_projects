clc;

esignal=randi([0,1],1,127); %generuje 127-bitowy sygna� w zakresie od 0 do 1. Normalnie b�dzie tu wchodzi� ca�y wygenerowany sygna�

disp(esignal); % wyswietlenie sygnalu przed kodowaniem
newesignal=[]; %bedzie zbierala 64 bitowe ramki

while(~isempty(esignal))
    if(length(esignal)<64)
        esignal=esignal(3:length(esignal));%odci�cie pocz�tkowych 2 bit�w ostatniej ramki
        newesignal=horzcat(newesignal,esignal(1:length(esignal))); %do��czenie ostatniej ramki
        break;
    end
    esignal=esignal(3:length(esignal));%odci�cie pocz�tkowych 2 bit�w
    newesignal=horzcat(newesignal,esignal(1:64));
    esignal=esignal(65:length(esignal)); %odci�cie pocz�tkowych 64 bit�w
end
disp(newesignal); % sprawdzenie po kodowaniu