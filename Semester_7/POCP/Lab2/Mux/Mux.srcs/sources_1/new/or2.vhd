library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity or2 is
    Port ( a : in STD_LOGIC;
           b : in STD_LOGIC;
           z : out STD_LOGIC);
end or2;

architecture a_or2 of or2 is
begin
    z <= a or b;
end a_or2;
