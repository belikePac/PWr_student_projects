clear;
%dodanie �cie�ek do folder�w, klasy w nich widoczne s� osi�galne
addpath(genpath('view'));
addpath(genpath('model'));
addpath(genpath('helper'));

%odpalenie g��wnego widoku aplikacji - czyli wywolanie funkcji
%zdefiniowanej w glownyWidok.m, kt�ra z kolei odpala figure
%glownyWidok.fig, stworzon� przy pomocy GUIDE (lewym na glownyWidok.fig i
%edytuj w GUIDE)
FinalView();

%UWAGA: zakomentowa�em wy�wietlanie sygna�y, gdy� chcia�em skupi� si� tylko
%na BER i rozmiarze sygna�y cop po procesie resynchronizacji

%LSFR musi miec d�ugo�� conajmniej 39 bit�w!!!
%LSFR = [0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1];
G = SignalGenerator(5, 0.5); %powtarzalno�� jedynek = 0.5
S = Scrambler();
D = Descrambler();
Enc = Encoder();
Dec = Decoder2();
CC = CustomChannel(0.01,0,0);%bsc = 0.01, desynch = 21, period=0
H = Helper();

%zakomnetowano procesy scramblingu/descramblingu
%w celu sprawdzenia algorytmu desynchronizacji i resynchronizacji
%UWAGA: w klasie CustomChannel domy�lnie przyj�to 21, jako liczb� bit�w,
%po kt�rej nast�puje desynch
%NALE�Y zastanowi� si�, czy jest to liczba odpowiednia, czy mo�e nale�y
%u�y� normy ITU/ISO, albo innej warto�ci, kt�ra przyniesie rezultaty w
%testach i pomiarach
%Cho� w zasadzie podczas test�w i tak b�dzie mo�na poda� t� warto��
%to jednak u�ytkownik, kt�ry po prostu wy�le sygna�, a nie da konkretnej
%ilo�ci desynchNumOfBits, to domy�lnie jaka� ona musi by� tak czy siak
%Kwestia jaka powinna by�?

fprintf("BEFORE ALL:\n");
sig = G.generateSignal();
sig.printSignal();

%fprintf("COPIED:\n");
cop = sig.copy();
%cop.printSignal();

%fprintf("SCRAMBLED:\n");
%cop = S.scrambleSignal(cop);
%cop.printSignal();

%fprintf("ENCODED:\n");
cop = Enc.encode(cop);
%cop.printSignal();

%CUSTOM CHANNEL
CC.sendSig(cop);
cop = CC.receiveSig();

%fprintf("DECODED:\n");
cop = Dec.decode(cop);
%cop.printSignal();

fprintf("AFTER ALL:\n");
%cop = D.descrambleSignal(cop);
cop.printSignal();

fprintf("BER: %f\n", H.calculateBER(sig,cop));

%mo�na zaobserwowa� strat� bit�w
sizeOrigin = sig.getSize();
sizeCopy = cop.getSize();