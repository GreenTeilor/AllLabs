library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decoder_2_4_b is
    Port ( 
        s0, s1, c: in STD_LOGIC;
        z0, z1, z2, z3: out STD_LOGIC
    );
end decoder_2_4_b;

architecture a_decoder_2_4_b of decoder_2_4_b is
signal y0, x0: STD_LOGIC;
begin
    y0 <= not s0;
    x0 <= not s1;
    z0 <= y0 and x0 and c;
    z1 <= s0 and x0 and c;
    z2 <= y0 and s1 and c;
    z3 <= s0 and s1 and c;
end a_decoder_2_4_b;
