classdef Channel < handle

    properties (SetAccess = protected, GetAccess = protected) %klasa abstrakcyjna, zatem pola z modyfikatorem protected
        signal
    end
    
    methods (Abstract)
        sendSig(this, signal)       %tylko metody wsp�lne dla ka�dego kana�u
        receiveSig(this)
    end
end