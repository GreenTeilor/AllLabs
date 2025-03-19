library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity and5_b is
    Port (
    a : in STD_LOGIC_VECTOR(4 downto 0);
    z : out STD_LOGIC
);
end and5_b;

architecture a_and5_b of and5_b is
begin
    z <= a(4) and a(3) and a(2) and a(1) and a(0);
end a_and5_b;
