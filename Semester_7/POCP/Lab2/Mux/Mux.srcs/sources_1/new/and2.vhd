library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity and2 is
    Port ( a : in STD_LOGIC;
           b : in STD_LOGIC;
           z : out STD_LOGIC);
end and2;

architecture a_and2 of and2 is
begin
    z <= a and b;
end a_and2;
