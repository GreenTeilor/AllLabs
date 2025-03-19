library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task7_b is
    Port ( w : in STD_LOGIC;
           x : in STD_LOGIC;
           y : in STD_LOGIC;
           z : in STD_LOGIC;
           g : out STD_LOGIC);
end task7_b;

architecture a_task7_b of task7_b is

begin
    g <= (w AND x AND y) OR (y AND z);
end a_task7_b;
