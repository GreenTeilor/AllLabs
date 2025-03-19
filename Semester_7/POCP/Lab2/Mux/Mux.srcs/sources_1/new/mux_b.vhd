library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity mux_b is
    Port ( a : in STD_LOGIC;
           b : in STD_LOGIC;
           s : in STD_LOGIC;
           z : out STD_LOGIC);
end mux_b;

architecture a_mux_b of mux_b is
begin
    z <= a when s = '0' else b;
end a_mux_b;
