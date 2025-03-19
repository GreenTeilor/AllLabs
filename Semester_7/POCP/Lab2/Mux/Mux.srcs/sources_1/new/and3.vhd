library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity and3 is
    Port ( a, b, c : in STD_LOGIC;
           z : out STD_LOGIC
    );
end and3;

architecture a_and3 of and3 is
begin
    z <= a and b and c;
end a_and3;
