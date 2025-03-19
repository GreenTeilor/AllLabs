library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity inv is
    Port ( a : in STD_LOGIC;
           z : out STD_LOGIC);
end inv;

architecture inv_a of inv is
begin
    z <= not a;
end inv_a;
