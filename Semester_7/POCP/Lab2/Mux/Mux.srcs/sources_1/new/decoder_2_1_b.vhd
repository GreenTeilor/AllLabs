library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity decoder_2_1_b is
    Port ( s : in STD_LOGIC;
           z0 : out STD_LOGIC;
           z1 : out STD_LOGIC);
end decoder_2_1_b;

architecture a_decoder_2_1_b of decoder_2_1_b is
begin
    z0 <= not s;
    z1 <= s;
end a_decoder_2_1_b;
